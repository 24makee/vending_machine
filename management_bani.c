#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char filename_bank[]="banking_info.bin";
typedef struct
{
    int pin;
    int balance;
} CREDIT_CARD;


void bill(int pret)
{
    printf("\t\t\tTotal amount to be payed is: %.2d\n\n\n",pret);
}
int wait(int seconds)
{
    clock_t end_wait=(clock() + (seconds * CLOCKS_PER_SEC));
    while(clock()<end_wait)
    {}
    return 1;
}

/////////CAZUL CASH
int cash_payment(int *total_introdus)
{
    int bancnota=-1;
    int bani=0;
    char tasta;
start:
    printf("\t\t\tEnter your money: \n");
    printf("\t\t\t($5 $10 $20 $50 $100)\n");
    scanf("%d",&bancnota);
    getchar();
    if(bancnota==5 || bancnota==10 || bancnota==20 || bancnota==50 || bancnota==100 )
    {
        bani=bani+bancnota;
        printf("\t\t\tYou have entered $%d \n",bani);
        printf("\t\t\tDo you want to enter more money?\n");
        printf("\t\t\tPress 1 for YES or 2 for NO\n");
        getch(tasta);
        atoi(tasta);
        if(tasta==1)
            goto start;
        else
        {
            *total_introdus=bani;
            return 1;
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

}

int main()
{
    //card_payment(30,3657);
    //bill(40);
    if(cash_payment(40)==1)
    {
        printf("\t\t\tThe item is being delivered!\n");
        printf("\t\t\tThank you for the purchase!\n");
        printf("\t\t\tHave a nice day!\n");
    }
    FILE *f;
    CREDIT_CARD card;
    int i;
    f=fopen("banking_info.bin","rb");
    for(i=0; i<5; i++)
    {
        fread(&card,sizeof(CREDIT_CARD),1,f);
        printf("Pinul %d este: %d \n",i+1,card.pin);
        printf("Balanta %d este: %d \n",i+1,card.balance);
    }
    fclose(f);

}



