#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
typedef struct
{
    char nume[20];
    int pret, cod, stoc;
} PRODUS;
#include "func.c"

char *available( int cod )
{
    int pret;
    char nume[20];
    char *msg = malloc(20*sizeof(char));
    char *aux = malloc(20*sizeof(char));
    if ( msg == NULL )
    {
        return 0;
    }
    if ( verificaStoc(cod, &pret, nume) )
    {
        strcpy(aux, "   ");
        //strcpy(msg, strcat("   ", strcat(itoa(pret), "$   ")));
        itoa(pret, msg, 10);
        //msg = strcat("    ", msg);
        msg = strcat(aux, msg);
        msg = strcat(msg, "$   ");
        //strcpy( msg, itoa(pret));
       // strcpy(msg, "    PRET   ");
    }
    else
    {
        strcpy(msg, "SOLD  OUT");
    }
    return msg;
}
void afisareProduse()
{
    char sold[10] = "SOLD  OUT";
    int i;
    printf("\t\t ___________    ___________    ___________ \n");
    printf("\t\t|1          |  |2          |  |3          |\n");
    printf("\t\t|   Avira   |  | Antivirus |  |  Phantom  |\n");
    printf("\t\t|   Prime   |  |    PRO    |  |    VPN    |\n");
    printf("\t\t|           |  |           |  |           |\n");
    printf("\t\t| %s |  | %s |  | %s |\n", available(1), available(2), available(3));
    printf("\t\t|___________|  |___________|  |___________|\n");
    printf("\n");
    printf("\t\t ___________    ___________    ___________ \n");
    printf("\t\t|4          |  |5          |  |6          |\n");
    printf("\t\t|  Password |  |           |  |  System   |\n");
    printf("\t\t|  Manager  |  | Optimizer |  |  Speedup  |\n");
    printf("\t\t|           |  |           |  |           |\n");
    printf("\t\t| %s |  | %s |  | %s |\n", available(4), available(5), available(6));
    printf("\t\t|___________|  |___________|  |___________|\n");
}

