//#include <conio.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//biblioteci incluse in fisierul principal


char filename_bank[]="banking_info.bin";
/*typedef struct
{
    int pin;
    int balance;
} CREDIT_CARD;*/ 
//definita in struct.h


void bill(int pret)
{
    printf("\t\t\tTotal amount to be payed is: %.2d\n\n\n",pret);
}

/////////CAZUL CASH
void cash_payment(int *total_introdus)
{
    int bancnota=-1;
    int bani=0;
    char tasta;
start:
    printf("\t\t\tEnter one of the following bills: \n");
    printf("\t\t\t    ($1 $5 $10 $20 $50 $100)\n");
    printf("\t\t\t\t\t");
    scanf("%d",&bancnota);
    getchar();
    if(bancnota==1 || bancnota==5 || bancnota==10 || bancnota==20 || bancnota==50 || bancnota==100 )
    {
        bani=bani+bancnota;
        scan_tasta:
        printf("\t\t\tYou have entered $%d \n",bani);
        printf("\t\t\tDo you want to enter more money?\n");
        printf("\t\t\tPress 1 for YES or 2 for NO\n\n");
        //printf("\t\t\t\t");
        tasta=getch();
       // printf("\n");
        if(tasta=='1')
            goto start;
        else if(tasta=='2')
        {
            printf("\t\t\tYou have entered $%d \n",bani);
            *total_introdus=bani;
        }
        else{
            printf("\t\t\tInvalid input!\n");
            goto scan_tasta;
        }
    }
    else
    {
        printf("\t\t\tInvalid bill. Please try again\n");
        goto start;
    }

}


///////////CAZUL CARD
int card_payment(int pret, int entered_pin)
{
    CREDIT_CARD card;
    FILE *f;
    int pin;
    int ok=0;
    int balance;
    f=fopen(filename_bank,"r+b");

    while(ok==0)
    {
        fread(&card,sizeof(CREDIT_CARD),1,f);
        printf("%d %d\n",card.pin,card.balance);
        if(card.pin!=entered_pin)
            goto finish;
        if(card.balance<pret)
        {
            fclose(f);
            return 0;
        }
        else
        {
            card.balance=card.balance-pret;
            fseek(f,-sizeof(CREDIT_CARD),1);
            if(fwrite(&card,sizeof(CREDIT_CARD),1,f))
            {
                fclose(f);
                return 1;

            }

        }
finish:
        ;
    }
    fclose(f);
	return 0;

}

/*int main()
{
    //card_payment(30,3657);
    //bill(40);
    int available_money=0;
    cash_payment(&available_money);
    //printf("%d",available_money);
//    FILE *f;
//    CREDIT_CARD card;
//    int i;
//    f=fopen("banking_info.bin","rb");
//    for(i=0; i<5; i++)
//    {
//        fread(&card,sizeof(CREDIT_CARD),1,f);
//        printf("Pinul %d este: %d \n",i+1,card.pin);
//        printf("Balanta %d este: %d \n",i+1,card.balance);
//    }
//    fclose(f);

}*/



