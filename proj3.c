/*
 * Soubor:  proj3.c
 * Datum:   5.12.2013
 * Autor:   Vladan Ryšavý, xrysav22@stud.fit.vutbr.cz
 * Projekt: IZP č. 3 - Hledání obrazců
 * Popis:   Program, který v daném monochromatickém obrázku hledá nejdelší vodorovné a svislé úsečky a největší čtverce.
 *          Obrázek je uložen jako bitmapa v textovém souboru ve formě obdélníkové matice nul a jedniček.
 *          Cílem programu je výpis počáteční a koncové souřadnice nalezené úsečky nebo čtverce.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int rows;       // rady
    int cols;       // sloupce
    char *cells;    //ukazatel na 1D pole radku
} Bitmap;

int find_vline(Bitmap * bitmap, int *x1, int *y1, int *x2, int *y2);
int find_hline(Bitmap * bitmap, int *x1, int *y1, int *x2, int *y2);
int find_square(Bitmap * bitmap, int *x1, int *y1, int *x2, int *y2);
char getcolor(Bitmap *bitmap, int x, int y);
int test(Bitmap * bitmap);
void help();

int main(int argc,char*argv[])
{
int x1,x2,y1,y2;
int navrat=2;
char *bitmap;

Bitmap *ukazatel;
ukazatel = (Bitmap*)malloc(sizeof(Bitmap));

FILE *soubor;
char c;
int a,b,i=0;

if(argc==2)
    if(strcmp(argv[1],"--help")==0)
    {
        help();
        return 0;
    }

if (argc==3)
{
    if ((soubor = fopen(argv[2], "r"))==NULL)      //za predpokladu ze existuje soubor ho otevre, jinak vypisuje hlasku ze se otevreni nezdarilo
    {
        printf("soubor %s se nepodarilo otevrit\n",argv[2]);
        return 1;
    }

    fscanf(soubor,"%d %d", &a,&b);
    ukazatel->rows=a;
    ukazatel->cols=b;

    bitmap=malloc(a*b*sizeof(char));

    while((c=fgetc(soubor))!=EOF)
    {
        if(c!=' ' && c !='\t'&& c!='\n' && c!='v' && c !='f'&& c!='r')
        bitmap[i++]=c;
    }
    bitmap[i++]='\0';

    ukazatel->cells=bitmap;

    fclose(soubor);

    if(strcmp(argv[1],"--test")==0)
    {
        if(test(ukazatel)==1) printf("Invalid\n");
        else printf("Valid\n");
    }

    if(strcmp(argv[1],"--hline")==0) navrat=find_hline(ukazatel,&x1,&y1,&x2,&y2);
    if(strcmp(argv[1],"--vline")==0) navrat=find_vline(ukazatel,&x1,&y1,&x2,&y2);
    if(strcmp(argv[1],"--square")==0) navrat=find_square(ukazatel,&x1,&y1,&x2,&y2);

    if(navrat==1)
        printf("%d %d %d %d\n",x1,y1,x2,y2);
    if(navrat==0)
        printf("obrazec nenalezen\n");

    free(ukazatel);
    free(bitmap);
}
return 0;

}


void help()
{
printf( "Program se spousti v nasledujici podobe:\n\n"
        "./proj3 --help\n"
        "\tnebo\n"
        "./proj3 --test soubor.txt\n"
        "\tnebo\n"
        "./proj3 --hline obrazek.txt\n"
        "\tnebo\n"
        "./proj3 --vline obrazek.txt\n"
        "\tnebo\n"
        "./proj3 --square obrazek.txt\n"
        "\nArgumenty programu:\n"
        "--help program vytiskne napovedu pouzivani programu a skonci.\n"
        "--test pouze zkontroluje, ze soubor dany druhym argumentem programu\n"
        "\tobsahuje radnou definici bitmapoveho obrazku.\n"
        "--hline v danem obrazku nalezne a vytiskne pocatecni a koncovou souradnici \n\tprvni nejdelsi horizontalni usecky.\n"
        "--vline v danem obrazku nalezne a vytiskne pocatecni a koncovou souradnici \n\tprvni nejdelsi vertikalni usecky.\n"
        "--square v danem obrazku nalezne a vytiskne pocatecni a koncovou souradnici \n\tprvniho nejvetsiho ctverce.\n");

}

int test(Bitmap *bitmap)
{
int velikost,i=0;
velikost=bitmap->rows*bitmap->cols;

while (bitmap->cells[i]!='\0')
{
    if(bitmap->cells[i]!='1' && bitmap->cells[i]!='0')
        return 1;
    i++;
}
if(velikost!=i)
        return 1;
return 0;
}

int find_vline(Bitmap *bitmap, int *x1, int *y1, int *x2, int *y2)
{
int color;
int i=0;

int pocitadlo=0;
int pocitadlo_rad=0;
int pocitadlo_sloupcu=0;

int nejdelsi=0;
int soucasna_delka=0;

int testovane_x=0, testovane_y=0;
int konecne_testovane_x=0, konecne_testovane_y=0;

while(pocitadlo_sloupcu<bitmap->cols)
{
    while(pocitadlo_rad<bitmap->rows)
    {
        color=getcolor(bitmap,pocitadlo_sloupcu,pocitadlo_rad);
        if (color=='1')
        {
            if(pocitadlo==0)
            {
            testovane_x=pocitadlo_rad;
            testovane_y=pocitadlo_sloupcu;
            }
        pocitadlo=1;
        soucasna_delka++;
        konecne_testovane_x=pocitadlo_rad;
        konecne_testovane_y=pocitadlo_sloupcu;
        }

        if (color=='0' || pocitadlo_rad+1==bitmap->rows)
        {
            if(soucasna_delka>nejdelsi)
            {
            *x1=testovane_x;
            *y1=testovane_y;
            *x2=konecne_testovane_x;
            *y2=konecne_testovane_y;
            nejdelsi=soucasna_delka;
            }
        pocitadlo=0;
        soucasna_delka=0;
        }
    pocitadlo_rad++;
    i++;
    }
soucasna_delka=0;
pocitadlo_sloupcu++;
pocitadlo_rad=0;
}


return 1;
}

int find_hline(Bitmap *bitmap, int *x1, int *y1, int *x2, int *y2)
{
int color;
int i=0;

int pocitadlo=0;
int pocitadlo_rad=0;
int pocitadlo_sloupcu=0;

int nejdelsi=0;
int soucasna_delka=0;


int testovane_x=0, testovane_y=0;
int konecne_testovane_x=0, konecne_testovane_y=0;


while(pocitadlo_rad<bitmap->rows)
{
    while(pocitadlo_sloupcu<bitmap->cols)
    {
        color=getcolor(bitmap,pocitadlo_sloupcu,pocitadlo_rad);
        if (color=='1')
        {
            if(pocitadlo==0)
            {
            testovane_x=pocitadlo_rad;
            testovane_y=pocitadlo_sloupcu;
            }
        pocitadlo=1;
        soucasna_delka++;
        konecne_testovane_x=pocitadlo_rad;
        konecne_testovane_y=pocitadlo_sloupcu;
        }

        if (color=='0' || pocitadlo_sloupcu+1==bitmap->cols)
        {
            if(soucasna_delka>nejdelsi)
            {
            *x1=testovane_x;
            *y1=testovane_y;
            *x2=konecne_testovane_x;
            *y2=konecne_testovane_y;
            nejdelsi=soucasna_delka;
            }
        pocitadlo=0;
        soucasna_delka=0;
        }
    pocitadlo_sloupcu++;
    i++;
    }
soucasna_delka=0;
pocitadlo_rad++;
pocitadlo_sloupcu=0;
}

return 1;
}

int find_square(Bitmap *bitmap, int *x1, int *y1, int *x2, int *y2)
{
int color;
int kroky;
int mezi;
int y;
int soucet1,soucet2;

int pocitadlo_rad=0;
int pocitadlo_sloupcu=0;

if (bitmap->rows>bitmap->cols) kroky=bitmap->cols;
else kroky=bitmap->rows;

while (kroky>0)
{
    while(pocitadlo_rad<bitmap->rows)
    {
        while(pocitadlo_sloupcu<bitmap->cols)
        {
                y = kroky;
                soucet1=kroky+pocitadlo_sloupcu;
                soucet2=kroky+pocitadlo_rad;

                if(soucet2<bitmap->rows && soucet1<bitmap->cols)
                {
                    color=getcolor(bitmap,pocitadlo_sloupcu,pocitadlo_rad);
                    if (color=='1')
                    {
                        do{
                        mezi=getcolor(bitmap,pocitadlo_sloupcu+y,pocitadlo_rad); //testovaní z leva do prava
                        if(mezi=='0') break;
                        mezi=getcolor(bitmap,pocitadlo_sloupcu,pocitadlo_rad+y); //testovaní zhora dolu
                        if(mezi=='0') break;
                        mezi=getcolor(bitmap,pocitadlo_sloupcu+kroky,pocitadlo_rad+y); //testovaní z prava do leve
                        if(mezi=='0') break;
                        mezi=getcolor(bitmap,pocitadlo_sloupcu+y,pocitadlo_rad+kroky); //testovaní z dola nahoru
                        if(mezi=='0') break;
                        y--;
                        }while(mezi=='1' && y>0);

                        if (mezi=='1')
                        {
                            *x1=pocitadlo_rad;
                            *y1=pocitadlo_sloupcu;
                            *x2=pocitadlo_rad+kroky;
                            *y2=pocitadlo_sloupcu+kroky;
                            return 1;
                        }
                    }
                }
                pocitadlo_sloupcu++;
        }
        pocitadlo_rad++;
        pocitadlo_sloupcu=0;
    }
    pocitadlo_rad=0;
    kroky--;
}

return 0;
}

char getcolor(Bitmap *bitmap, int x, int y)
{
int color;
color=(bitmap->cols*y)+(x);
color=bitmap->cells[color];

return color;
}

