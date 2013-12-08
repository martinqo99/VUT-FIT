/*
 * Soubor:  proj1.c
 * Datum:
 * Autor:   Vladan Ryšavý, xrysav22@stud.fit.vutbr.cz
 * Projekt: IZP č. 1 - Počítání slov
 * Popis:   Program, který ve vstupním textu spočítá slova obsahující uživatelem specifikovaný znak a jejich počet vypíše.
 *          Uživatel specifikuje daný znak argumentem příkazové řádky.
 *          Uživatel navíc může specifikovat pozici znaku v počítaném slově dalším argumentem příkazové řádky.
 */
#include <stdio.h>
#include <stdlib.h>

int hledane_znaky (int argument,int vstup, int obsah);
int debug_rezim (int vstup,int i);
int prevod_argumentu (int argc,char*argv[]);

    /*  tisk napovedy */
void tisk_napovedy()
{
   printf("\n===========================* NAPOVEDA *===========================\n"
               "\nna vstupu argument \n--help\tvytiskne napovedu\n nebo\nX [N] [-d]\n"
               "\tX reprezentuje hledany znak\n\t\tspecialni znaky \n"
               "\t\t\t: libovolne cislo; \n\t\t\t^ libovolne velke pismeno; \n"
               "\t\t\t. libovolny znak;\n\t\N reprentuje pozici znaku ve slove (cele cislo kladne) (*)\n"
               "\t\-d zapina debug mod(*)\n\n\t\t(*)=volitelny argument\n"
               "==================================================================\n");

}

    /*  Hlavni program  */
int main(int argc, char*argv[]) {

int vstup ,obsah = 0,pocet = 0,omezeni_debugu=0,argument,pozice,pocet_pruchodu=0;
if (argc >= 2 ) argument = argv[1][0];

pozice=prevod_argumentu(argc,argv);

if (argc > 1 ) {
if (strcmp(argv[1],"--help")==0 || argc>=5) tisk_napovedy(); //volani funkce s napovedou kdyz je zadany pozadovany argument nebo je pocet argumnetu vyssi
else
{
while ((vstup=getchar())!='\n') // <- změna na EOF ve win cyklí
{
    if (argc>=3) if (argv[2][0]>='0' && argv[2][0]<='9')pocet_pruchodu++; // <- pocita pocty pruchodu kdyz je vyzadovana pozice
    if ((vstup !='-' && vstup !='_' )&& !(vstup >='a'&& vstup <= 'z') && !(vstup >='A'&& vstup <= 'Z') && !(vstup >='0' && vstup <='9')) // <-oddělovače slov
    {
    if (obsah>0) pocet++;
    obsah=0;
    if (argc>=3)
        if (argv[2][0]>='0' && argv[2][0]<='9')
            pocet_pruchodu=0; // <- nuluje pocty pruchodu kdyz je vyzadovana pozice
    }
    if (argc>=3)
        if (argv[2][0]>='0' && argv[2][0]<='9') if (pocet_pruchodu==pozice) // <- porovnava pruchody a pozice kdyz je vyzadovana pozice a kdyz je pocet argumentu vetsi jak 3
            obsah = hledane_znaky(argument,vstup,obsah);
    if (argc>=3)
        if (!(argv[2][0]>='0' && argv[2][0]<='9')) // <- pocita obsah je li zadany jeden argument
            obsah = hledane_znaky(argument,vstup,obsah);
    if (argc==2)
        obsah = hledane_znaky(argument,vstup,obsah); // <- pocita obsazena pismenka kdyz nejsou zadany zadny dalsi argumenty
    if (argc>=3) // <- kdyz hleda argument ktery nexistuje tak pada
        if (strcmp(argv[2],"-d")==0)
            omezeni_debugu = debug_rezim(vstup,omezeni_debugu);// <- vola funkci zajistujici debug rezim
    if (argc>=4) // <- kdyz hleda argument ktery nexistuje tak pada
        if (strcmp(argv[3],"-d")==0)
            omezeni_debugu = debug_rezim(vstup,omezeni_debugu);// <- vola funkci zajistujici debug rezim
}
}
if (omezeni_debugu>0) printf("\n"); // <- odradkuje nakonci debug rezimu

printf("%d\n",pocet);
}
else tisk_napovedy();
return 0;
}

    /*  Podminky pri hledani znaku ve slove */
int hledane_znaky (int argument,int vstup, int obsah)
{
    /* specialni znak ^ pocita libivolne velke pismeno */
if (argument=='^')
{
    if (vstup>='A'&& vstup <= 'Z')   // <- počítá počet hledaného znaku ve slově <- ošetřuje stav více hledanych pismen ve slově
    {
    obsah=1;
    }
}
    /* spoceilni znak . pocitajici vsechna slova */
if (argument=='.')
{
    if ((vstup =='-'|| vstup =='_' )|| (vstup >='a'&& vstup <= 'z') || (vstup>='A'&& vstup <= 'Z') || (vstup >='0'&& vstup <= '9'))   // <- počítá počet hledaného znaku ve slově <- ošetřuje stav více hledanych pismen ve slově
    {
    obsah=1;
    }
}
     /* spoceilni znak : pocitajici cisla */
if (argument ==':')
{
    if (vstup >='0' && vstup <='9') // <- počítá počet hledaného znaku ve slově <- ošetřuje stav více hledanych pismen ve slově
    {
    obsah=1;
    }
}
    /* obycejny znak    */
if ((argument =='-'|| argument =='_' )|| (argument >='a'&& argument <= 'z') || (argument>='A'&& argument <= 'Z') || (argument>='0'&& argument <= '9'))
{
    if (vstup==argument) // <- počítá počet hledaného znaku ve slově <- ošetřuje stav více hledanych pismen ve slově
    {
    obsah=1;
    }
}
return obsah;
}

    /*  debug rezim */
int debug_rezim (int vstup,int omezeni_debugu)
{
if (omezeni_debugu<80 && ((vstup =='-'|| vstup =='_' )|| (vstup >='a'&& vstup <= 'z') || (vstup >='A'&& vstup <= 'Z') || (vstup >='0'&& vstup <= '9')))
        {
        putchar(vstup);
        omezeni_debugu++;
        }
        if ((vstup !='-' && vstup !='_' )&& !(vstup >='a'&& vstup <= 'z') && !(vstup >='A'&& vstup <= 'Z') && !(vstup >='0' && vstup <='9')) {
           if (omezeni_debugu>0) printf("\n"); //<-podmnínka osetruje vice mezer mezi slovy -> odradkuje se pouze jednou
            omezeni_debugu=0;
        }
  return omezeni_debugu;
}

    /* převod argumentu vyjadrujici pozici na cislo int*/
int prevod_argumentu (int argc,char*argv[])
{
    int b=0,cykly=1,pole[b],pozice=0,a=0;

if (argc>=3) //<- kdyz hleda argument ktery nexistuje tak pada
{
    if (argv[2][0]>='0' && argv[2][0]<='9')
    {

    while (argv[2][a]>='0' && argv[2][a]<='9') // <- nacita do pole cislo
    {
        pole[b] = argv[2][a] - '0';
        a++;
        b++;
    }
    b=0;
    while (b<a) // <- scita pole a podle potreby dela mocniny cisla 10
    {
        while (cykly < a)
        {
        pole[b]=pole[b]*10;
        cykly++;
        }
        if (cykly>b)
        {
        pole[b]=pole[b];
        }
        cykly=b+2;
        pozice = pozice + pole[b]; // <- vysledne cislo v int
        b++;
    }
    }
}
return pozice;
}
