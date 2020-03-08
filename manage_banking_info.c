#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int pin;
    int balance;
} CREDIT_CARD;


int main()
{
    FILE *f;
    int i;
    char tasta;
    int number_of_users=-1;
    int p;
    int pin;
    CREDIT_CARD card;
    while(1)
    {
        printf("Press 1 to ADD credit card info\n");
        printf("Press 2 to VIEW the existing credit card info\n");
        printf("If you want to exit press 'x'\n\n");

        tasta=getch();


        if(tasta=='1')
        {
            printf("Enter the number of credit cards that will be entered: ");
            scanf("%d",&number_of_users);
            f=fopen("banking_info.bin","wb");
            for(i=0; i<number_of_users; i++)
            {
                printf("Enter credit card info: \n");
                printf("Enter pin: ");
                scanf("%d",&card.pin);
                printf("\nEnter balance: ");
                scanf("%d",&card.balance);
                fwrite(&card,sizeof(CREDIT_CARD),1,f);
            }
            fclose(f);


            printf("The credit card info from the file is:\n");
            f=fopen("banking_info.bin","rb");
            for(i=0; i<number_of_users; i++)
            {
                fread(&card,sizeof(CREDIT_CARD),1,f);
                printf("Pin: %d : %d\n",i+1,card.pin);
                printf("Balance: %d : %d \n\n",i+1,card.balance);
            }
            fclose(f);

        }
        else if(tasta=='2')
        {

            printf("The credit card info from the file is:\n");

            f=fopen("banking_info.bin","rb");
            fseek(f,0L,2);
            number_of_users=(ftell(f)/sizeof(CREDIT_CARD));
            fseek(f,0L,0);
            for(i=0; i<number_of_users; i++)
            {
                fread(&card,sizeof(CREDIT_CARD),1,f);
                printf("Pin: %d : %d\n",i+1,card.pin);
                printf("Balance: %d : %d \n\n",i+1,card.balance);
            }
            fclose(f);
        }
        else if(tasta=='x')
            exit(1);
    }

    return 0;

}
