//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include "struct.h"

// pentru prototipul functiei getch()
#include <termios.h>

char filename_catalog[] = "catalog.bin";

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
    return ret;
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
    PRODUS prod;
    size_t sop = sizeof(PRODUS);
    while ( fread(&prod, sop, 1, f) ) {
	if ( prod.cod == codProdus ) {
	    prod.stoc -= 1;
	    fseek(f, -sop, SEEK_CUR);
	    if (fwrite(&prod, sop, 1, f)) { ret = 1; }
	    break;
	}
    }
    fclose(f);
    return ret;
}


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
