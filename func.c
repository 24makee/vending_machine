#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "struct.h"

// pentru prototipul functiei getch()
#ifdef __linux__
#include "termios.h"
static struct termios old, new;


void initTermios(int echo)
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch() {
    char ch;
    initTermios(0);
    ch = getchar();
    resetTermios();
    return ch;
}
#endif // __linux__




const char filename_catalog[] = "catalog.bin";
const char filename_adminpw[] = "admin_password.txt";
const char filename_buylog[] = "buy.csv";
const char filename_errorlog[] = "error.log";

void error ( char * msg ) {
    FILE * f = fopen(filename_errorlog, "at");
    fclose(f);
}


void clrscr() {
    system("@cls||clear");
}

void printf_3t ( char * s ) {
	printf("\t\t\t%s\n", s);
}

char* itoa(int value, char * buffer, int base) {
    sprintf(buffer,"%d",value);
    return buffer;
}

int ask_admin_pw() {
    clrscr();
    char password[30], entered_pw[30];
    int p=0;
    FILE * f = fopen(filename_adminpw, "rt");
    if ( f == NULL ) { error("admin:Unable to open password file"); return 0; }
    if ( !fscanf(f, "%s", password) ) { error("admin:Unable to read from file"); return 0; }
    fclose(f);
    printf_3t("MAINTENANCE");
    printf("Enter password: ");
    /*do {
	entered_pw[p] = getch();
	printf("*");
	p++;
    } while ( entered_pw[p-1]!='\n' || entered_pw[p-1]!='\r' || entered_pw[p-1]!= '\0' || p<=30 );*/
    scanf("%s", entered_pw);
    getch();
    if ( strcmp(entered_pw, password) == 0 ) { clrscr(); return 1; }
    else {
	printf_3t("Wrong password! Press any key to continue.");
//	getch();
    }
    clrscr();
    return 0;
}

void show_items() {
	printf_3t("MAINTENANCE");
	printf_3t("Current stock:");
	printf ( "%-7s%-20s%-10s%-10s\n", "Code", "Name", "Price", "Items in device");
	FILE * f = fopen(filename_catalog, "rb");
	if ( f == NULL ) { printf("Error code 2\n"); }
	PRODUS prod;
	while ( fread(&prod, sop, 1, f) ) {
	    printf("%-7d%-20s$%-10d%-10d\n", prod.cod, prod.nume, prod.pret, prod.stoc);
	}
	fclose(f);
}


int aprovizioneaza ( int codProdus, int cantitate, int pret, char numeProdus[] ) {
    FILE * f;
    if ( !(f=fopen(filename_catalog, "r+b")) ) {
	if ( !(f=fopen(filename_catalog, "w+b")) ) {
	    return 0;
	}
    }
    PRODUS prod;
    size_t sop = sizeof(PRODUS);
    int ret = 0, gasit=0;
    while ( fread(&prod, sop, 1, f) ) {
	if ( prod.cod == codProdus ) {
	    gasit = 1;
	    prod.stoc += cantitate;
	    fseek(f, -sop, SEEK_CUR);
	    if(fwrite(&prod, sop, 1, f)) {
		ret = 1;
	    }
	    break;
	}
    }
    if ( !gasit ) {
	prod.cod = codProdus;
	prod.stoc = cantitate;
	prod.pret = pret;
	strcpy(prod.nume, numeProdus);
	if(fwrite(&prod, sop, 1, f)) { ret = 1; }
    }
    fclose(f);
    return ret;
}

void log_transaction ( int productCode, char * payMethod ) {
    FILE * f = fopen ( filename_buylog, "a" );
    if ( f == NULL ) { error("csvLogger:Unable to open file"); return; }
    //get current date
    time_t t;
    time(&t);
    if ( !fprintf(f, "%s,%s,%d\n", ctime(t), payMethod, productCode) ) { error("csvLogger:Unable to write csv"); }
    fclose(f);
}


int verificaStoc ( int codProdus, int * pret, char * nume ) {
    FILE * f = fopen(filename_catalog, "rb");
    if ( f == NULL ) return 0;
    PRODUS prod;
    int ret = 0;
    while ( fread(&prod, sizeof(PRODUS), 1, f) ) {
		if ( prod.cod == codProdus ) {
			*pret = prod.pret;
			strcpy(nume, prod.nume);
			if ( prod.stoc > 0 ) {
			ret = 1;
			}
		}
    }
    fclose(f);
    return ret;
}

int eProdus ( char tasta ) {
	int cod = tasta - '0';
	FILE * f = fopen(filename_catalog, "rb");
	if ( f == NULL ) return 0;
    PRODUS prod;
	while ( fread(&prod, sizeof(PRODUS), 1, f) ) {
		if ( prod.cod == cod ) {
			fclose(f);
			return 1;
		}
	}
	fclose(f);
	return 0;
}

int cumpara ( int codProdus ) {
    // se cumpara cantitate 1
    int ret = 0;
    FILE * f = fopen(filename_catalog, "r+b");
    if ( f == NULL ) { error("buy:Unable to open catalog file"); return 0; }
    PRODUS prod;
    size_t sop = sizeof(PRODUS);
    while ( fread(&prod, sop, 1, f) ) {
	if ( prod.cod == codProdus ) {
	    prod.stoc -= 1;
	    fseek(f, -sop, SEEK_CUR);
	    if (fwrite(&prod, sop, 1, f)) { ret = 1; }
	    else { error("buy:Unable to write to catalog file"); }
	    break;
	}
    }
    fclose(f);
    return ret;
}



