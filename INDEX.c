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
    int pret, codProdus;
    int available_money=0;
    char pin[5];
	while (1) {
	clrscr();
    afisareProduse();
	printf("\t\t\tCredit: $%d - waiting transaction\n", available_money);
    printf_3t("Choose your payment method");
    printf_3t("Press 1 for CASH or 2 for CARD");
    tasta = getch();
    if(tasta == '1')
    {
		cash_payment(&available_money);
		printf_3t("Choose your product");
		tasta = getch();
		if ( eProdus(tasta) ) {
			if ( verificaStoc(tasta-'0', &pret, nume)) {
				// cumpara produs
				codProdus = tasta - '0';
				if ( pret <= available_money ) {
					if ( cumpara(codProdus) ) {
						available_money -= pret;
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
			getch();
			//break;
		//}

    } // endif
    else if(tasta == '2')
    {
        printf("\t\t\tChoose your product\n");
        tasta = getch();
        //if(tasta=='1' || tasta=='2' || tasta=='3' || tasta=='4' || tasta=='5' || tasta=='6')
		if ( eProdus(tasta) )
            if(verificaStoc(tasta-'0', &pret, nume))
            {
                printf("\t\t\tPIN: ");
                int p=0;
                do
                {
                    pin[p]=getch();
                    /*if(pin[p]!='\r')
                    {
                        printf("*");
                    }*/
					if ( pin[p] == '\n' || pin[p] == '\r' ) {
						break;
					}
					printf("*");
                    p++;
                }
                while(pin[p-1]!='\r');
                pin[p-1]='\0';
                printf("\nYou have entered %s as pin.",pin);
                getch();
                card_payment(pret, pin);
            }

    }



	}
    return 0;
}
