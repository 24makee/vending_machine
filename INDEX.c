#include <stdio.h>
#include <conio.h>
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
    int pret;
    int available_money=0;
    char pin[5];
    afisareProduse();
    printf("\t\t\tChoose your payment method\n");
    printf("\t\t\tPress 1 for CASH or 2 for CARD");
    tasta = getch();
    if(tasta == '1')
    {
        cash_payment(&available_money);
    }
    else if(tasta == '2')
    {
        printf("\t\t\tChoose your product\n");
        tasta = getch();
        if(tasta=='1' || tasta=='2' || tasta=='3' || tasta=='4' || tasta=='5' || tasta=='6')
            if(verificaStoc(tasta, &pret, nume))
            {
                printf("pin:\n");
                int p=0;
                do
                {
                    pin[p]=getch();
                    if(pin[p]!='\r')
                    {
                        printf("*");
                    }
                    p++;
                }
                while(pin[p-1]!='\r');
                pin[p-1]='\0';
                printf("\nYou have entered %s as pin.",pin);
                getch();
                card_payment(pret, pin);
            }

    }




    return 0;
}
