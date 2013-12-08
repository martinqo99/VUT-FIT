/*
 * Soubor:  proj2.c
 * Datum:   20.11.2013
 * Autor:   Vladan Ryšavý, xrysav22@stud.fit.vutbr.cz
 * Projekt: IZP č. 2 - Iterační výpočty
 * Popis:   Vytvořte program, který vypočítá a vypíše úhly obecného trojúhelníku.
 *          Trojúhelník je dán jeho třemi vrcholy.
 *          Výpočet proveďte pouze pomocí matematických operací +,-,*,/.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIPUL 1.57079632679
#define HRANICE 0.70711  //takove cislo ktere dostaneme, kdyz od 1 odecteme mocninu tohoto cisla a to cele nasledne umocnime

void help();
double errors (char*argv[],double x,int argc);
double my_sqrt(double x);
double my_asin(double x);
double my_fabs(double x);
int my_triangle(char*argv[]);

int main(int argc, char*argv[])
{
double x;
int b=0;

if (argc >=2)
if (strcmp(argv[1],"--help")==0) help(); // <- tisk napovedy
if (!(strcmp(argv[1],"--help")==0))
    {
    while (argv[2][b]!='\0')
    {
        if (!(argv[2][b]<='9' && argv[2][b]>='0')&& argv[2][b]!='-' && argv[2][b]!='.')
        {
        printf("nan\n");
        return 1;
        }
        b++;
    }
    }
if (argc >2)  x = atof(argv[2]); // <- převod na číslo

if (errors(argv,x,argc)==0)
    {


    if (strcmp(argv[1],"--sqrt")==0) printf("%.10e\n",my_sqrt(x)); // <- volani funkce pro pocitani odmocnin

    if (strcmp(argv[1],"--asin")==0) printf("%.10e\n",my_asin(x)); // <- volani funkce pro pocitani arcus sinus

    if (strcmp(argv[1],"--triangle")==0) my_triangle(argv);
    }
    return 0;
}

void help()
{
     printf("\n===========================* NAPOVEDA *===========================\n"
            "Program se spousti v nasledujici podobe:\n"
            "./proj2 --help\n"
            "\tnebo\n"
            "./proj2 --sqrt X\n"
            "\tnebo\n"
            "./proj2 --asin X\n"
            "\tnebo\n"
            "./proj2 --triangle AX AY BX BY CX CY\n\n"
            "\tArgumenty programu:\n"
            "--help zpusobi, ze program vytiskne napovedu pouzivani programu a skonci.\n"
            "--sqrt vypocita a vypise druhou odmocninu z cisla X.\n"
            "\t odmocnovat jdou pouze kladna cisla !!! \n"
            "--asin vypocita a vypise arcus sinus z cisla X.\n"
            "\t zadane cislo musi byt v intervalu <-1,1> !!! \n"
            "--triangle vypocita a vypise tri uhly troujuhelniku, ktery je dan vrcholy \n"
            "A=AX,AY, B=BX,BY a C=CX,CY.\n\n"
            "==================================================================\n");
}

double my_sqrt(double x)
{
double predchozi=1,soucasny=0;

if(x>0)
    {
    soucasny=0.5*(x/predchozi+predchozi);
    while(my_fabs(soucasny-predchozi)>0)
    {
        predchozi=soucasny;
        soucasny=0.5*(x/predchozi+predchozi);
    }
}
return soucasny;
}

double my_asin(double x)
{
double d=2,prirustek=1,vysledek,old=0,bod=x;

if(bod>=HRANICE || bod<=-HRANICE)
x=1-(x*x);

if((bod>=HRANICE || bod<=-HRANICE) && x!=0)
x = my_sqrt(x);

vysledek=x;

while(my_fabs(prirustek-old)>0)
{
    if(d==2)
    prirustek = ((d-1)/d) * ((x*x*x)/(d+1));
    else
    prirustek = old*((d-1)/d)*((x*x)/(d+1));

    old=prirustek*((d+1)/1);

    d+=2;

    vysledek+=prirustek;
}

  if(bod>=HRANICE)
  vysledek= PIPUL  - vysledek;

  if(bod<=-HRANICE)
  vysledek= -1*PIPUL + vysledek;

  return vysledek;
}

int my_triangle(char*argv[])
{
double Ax = atof(argv[2]);
double Ay = atof(argv[3]);
double Bx = atof(argv[4]);
double By = atof(argv[5]);
double Cx = atof(argv[6]);
double Cy = atof(argv[7]);

double a,b,c;

double alfa,beta,gama;

    /* převod na strany */
a=my_sqrt((Cx-Bx)*(Cx-Bx)+(Cy-By)*(Cy-By));
b=my_sqrt((Ax-Cx)*(Ax-Cx)+(Ay-Cy)*(Ay-Cy));
c=my_sqrt((Bx-Ax)*(Bx-Ax)+(By-Ay)*(By-Ay));

if (!(a + b > c && a + c > b && b + c > a))
{
    printf("nan\n");
    return 1;
}


    /* cosinova veta */
alfa=((a*a)-(b*b)-(c*c))/(-2*b*c);
beta=((b*b)-(c*c)-(a*a))/(-2*c*a);
gama=((c*c)-(a*a)-(b*b))/(-2*a*b);

    /* chyba vnikla pri nasobeni a deleni */
if (alfa<0.000000000001 && alfa>-0.000000000001) alfa=0;
if (beta<0.000000000001 && beta>-0.000000000001) beta=0;
if (gama<0.000000000001 && gama>-0.000000000001) gama=0;

alfa=my_asin(alfa);
beta=my_asin(beta);
gama=my_asin(gama);

alfa=my_fabs(PIPUL-alfa);
beta=my_fabs(PIPUL-beta);
gama=my_fabs(PIPUL-gama);

printf("%.10e\n",alfa);
printf("%.10e\n",beta);
printf("%.10e\n",gama);

return 0;
}

double my_fabs(double x)
{
if (x<0) x*=-1;
return x;
}

double errors (char*argv[],double x,int argc)
{
if (argc==1)    //nezadany zadny argument
{
    help();
    return 1;
}

if (argc==2) if(strcmp(argv[1],"--help")!=0)     //nezadana hodnota
{
    help();
    return 1;
}

if (argc>=2) if(strcmp(argv[1],"--asin")==0)     if(!(x<=1 && x>=-1))    //funkce asin je v intervalu -1,1
{
    printf("nan\n");
    return 1;
}

if (argc>=2) if(strcmp(argv[1],"--triangle")!=0) if(argc>3) //pro více argumentu
{
    help();
    return 1;
}

if (argc>=2) if(strcmp(argv[1],"--triangle")==0) if(argc<8 || argc>8)   //pro funkci triangle kdy je zadano malo stran nebo zase moc
{
    help();
    return 1;
}

if (argc>=2) if(strcmp(argv[1],"--sqrt")==0) if(x<0)   //pro sqrt kdy je zaporne cislo zadane
{
    printf("nan\n");
    return 1;
}

if (argc>=2) if(strcmp(argv[1],"--triangle")==0) //otestuje jestli je zadené číslo u trianglu
   {
    int a=2,b=0;
     while (a<8)
     {
     while (argv[a][b]!='\0')
     {
     if (!(argv[a][b]<='9' &&argv[a][b]>='0')&& argv[a][b]!='-' && argv[a][b]!='.')
     {
         printf("nan\n");
         return 1;
     }
     b++;
     }
     a++;
     }
    }

return 0;
}
