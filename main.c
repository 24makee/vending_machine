/* (c) segmentation fault team 2020
 * email: segmentationfault@mihneac.com
 *  - marius
 *  - make
 *  - mihneac
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#include <stdlib.h>
#include "func.c"
#include "vendingGraphicPrintf.c"
#include "management_bani.c"

int main()
{
    char tasta;
    char nume[20];
    int pret, codProdus, cpErr, int_pin, read_params;
    int available_money=0;
    char pin[5];
    PRODUS prod;
	while (1) {
    inceput:
	clrscr();
    afisareProduse();
	printf("\t\t\tCredit: $%d - waiting transaction\n", available_money);
    printf_3t("Choose your payment method");
    printf_3t("Press 1 for CASH or 2 for CARD or \n \t      'a' for maintenance or 'o' to turn machine off");
    tasta = getch();
    if(tasta == '1')
    {
		cpErr = cash_payment(&available_money);
		if ( cpErr == -1 ) {
		    //abort cash
		    if ( available_money > 0 ) {
			printf("\t\t\tReturning change: $%d\n", available_money);
			available_money = 0;
			printf_3t("Press any key to continue");
			getch();
		    }
		    continue;
		}
		printf_3t("Choose your product");
		tasta = getch();
		if ( eProdus(tasta) ) {
			if ( verificaStoc(tasta-'0', &pret, nume)) {
				// cumpara produs
				codProdus = tasta - '0';
				if ( pret <= available_money ) {
					if ( cumpara(codProdus) ) {
						available_money -= pret;
						log_transaction(codProdus, "cash");
						printf_3t("The product is being delivered");
						//printf("\t\t\tRemaining credit: $%d\n", available_money);
					} else {
						printf_3t("Error delivering product. You have not been charged for this");
					}
				} else {
					printf_3t("Not enough balance");
				}
			} else {
				printf_3t("Product is SOLD OUT");
			}
		} else { printf_3t("Please enter a valid product code"); }
		//printf("\t\t\tCredit remaining: $%d\n", available_money);
		//printf_3t("Buy another product? 1=YES, 2=NO");
		//tasta = getch();
		//if ( tasta != '1' ) {
		// rest
			if ( available_money > 0 ) {
				printf("\t\t\tChange: $%d being delivered\n", available_money);
				available_money = 0;
			} else { printf_3t("No credit remaining"); }
			printf_3t("Press any key to continue");
			getch();
			//break;
		//}

    } // endif
    else if(tasta == '2')
    {
        printf("\t\t\tChoose your product or press 'x' to restart\n");
        tasta = getch();
        if(tasta=='x')
            goto inceput;
        //if(tasta=='1' || tasta=='2' || tasta=='3' || tasta=='4' || tasta=='5' || tasta=='6')
		if ( eProdus(tasta) )
			codProdus = tasta - '0';
            if(verificaStoc(codProdus, &pret, nume))
            {
                printf("\t\t\tPIN: ");
                int p=0;
                do {
                    pin[p]=getch();
                    if(pin[p]=='x')
                    {   printf("\t\t\tPayment canceled!\n");
                        goto inceput;
                    }
			printf("*");
                    p++;
                } while(p<4);
                pin[p]='\0';
              //  printf("\nYou have entered %s as pin.",pin);
              //  getch();
              printf("\t\t\t\n");
              int_pin = atoi(pin);
               cpErr = card_payment(pret, int_pin);
			   switch ( cpErr ) {
					case 1:
						if ( cumpara(codProdus) ) {
							printf_3t("The product is being delivered");
							log_transaction(codProdus, "card");
						} else {
							printf_3t("Deliver error. Restoring money on card");
							card_restore(pret, int_pin);
						}
						break;
					case -1:
						printf_3t("Not enough balance on card.");
						break;
					case -2:
						printf_3t("Card error. No money has been withdrawn");
						break;
					case 0:
						printf_3t("Pin invalid!");
						break;
			   }
			   printf_3t("Press any key to restart!");
			   getch();
            }

    } else if ( tasta == 'a' ) {
	if ( !ask_admin_pw() ) continue;
	clrscr();
	show_items();
	printf("\n");
	printf("Do you want to add new products? y=YES, [n]=NO");
	tasta = getch();
	if ( tasta == 'y' ) {
	while ( tasta == 'y' ) {
	    clrscr();
	    show_items();
	    prod.pret = 0;
	    strcpy(prod.nume, "a");
	    printf("Insert product information: for existing products insert only code and number of added items.\nFor new products insert all details.:\n");
	    printf("code, stock, price, name: ");
	    read_params = scanf ( "%d, %d, %d, %s", &prod.cod, &prod.stoc, &prod.pret, prod.nume);
	    if(aprovizioneaza(prod.cod, prod.stoc, prod.pret, prod.nume)) {
		printf("product supplied\n");
	    } else  {
		printf("System error 3 - try again or contact developer");
	    }
	    printf("Add another product? y=YES, [n]=NO");
	    getch();
	    tasta = getch();
	    //if ( getch() != 'y' ) { break; } //iesire bucla aprovizionare
	}
	}
    } else if ( tasta == 'o' ) {
	exit(0);
    }



	} //endwhile
    return 0;
}
