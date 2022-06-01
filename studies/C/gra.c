#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//*     DEKLARACJE  FUNKCJI    *//

// GRA //
#define N 5

int gracze();
int decyzja(char);
void TuraRunda(int*, int, int*);
void losowanie(int[]);
void zmiana(int[]);
void sumowanie(int[][14], int);
void koniec(int[][14], int);
void dodanieranking();

// MENU I RANKING //
typedef struct      // struktura gracza z rankingu //
{
    char nazwa[21];
    int wygrana;
} Graczr;

int menu();
int graj();
void ranking();

// TABELA WYNIKÓW GRACZY //
void tablica(int[][14], int);
void wybor(int[][14],int, int[]);
void lista1(int[][14], int, int, int[]);
void lista2(int[][14], int, int, int[]);
void trzyjednakowe(int[][14], int, int, int[]);
void czteryjednakowe(int[][14], int, int, int[]);
void ful(int[][14], int, int, int[]);
void malystrit(int[][14], int, int, int[]);
void duzystrit(int[][14], int, int, int[]);
void general(int[][14], int, int, int[]);
void szansa(int[][14], int, int, int[]);

//*     MENU        *//


int main()
{
    int opcja;
    do
    {
        opcja = menu();
        switch(opcja)
        {
            case 1: graj();break;
            case 2: ranking();break;
        }
    }
    while (opcja!=3);
    return 0;
    
}

int menu()
{
    int opcja;
    printf("||||||||||||||||||||||||||||||||||\n");
    printf("||\t\tMENU\t\t||\n");
    printf("||\t  1 - NOWA GRA\t\t||\n");
    printf("||\t  2 - RANKING\t\t||\n");
    printf("||\t  3 - WYJSCIE\t\t||\n");
    printf("||||||||||||||||||||||||||||||||||\n");
    scanf("%d", &opcja);
    return opcja;
}

void ranking()
{
    Graczr ob;
    printf("|||||||||||||||||||||||||||||||||||||\n");
    printf("||\t\tRANKING\t\t   ||\n");
    printf("||Nick\t\t\tI.wygranych||\n");

    FILE* plik=fopen("ranking.txt","rt");

    while(fscanf(plik,"%s\t%d",ob.nazwa, &ob.wygrana)==2)
        printf("||%-21s\t\t%-3d||\n",ob.nazwa, ob.wygrana);

    fclose(plik);
    printf("|||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
}
//*     GRA     *//

int graj()
{
    int lgraczy=gracze();
    int gracz=1;
    int runda=1;
    int kosci[N];
    int wyniki[4][14]={{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0}, {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0}, {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0}, {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0}};
    char decyzja1, decyzja2;
    while(runda!=14)
    {
        printf("||||||||||||||||||||||||||||||||||\n");
        printf("||\t     RUNDA %-2d \t\t||\n", runda);
        printf("||\t   TURA GRACZA %d \t||\n", gracz);
        printf("||\tWYLOSOWANE KOSCI TO:\t||\n");
        losowanie(kosci);
        printf("||||||||||||||||||||||||||||||||||\n");

        printf("CZY CHCESZ WYMIENIC KOSCI?(T LUB N)\n");
        scanf("\n%c", &decyzja1);

        if(decyzja(decyzja1)==1)
        {
            zmiana(kosci);
            printf("\nCZY CHCESZ WYMIENIC KOSCI PONOWNIE?(T LUB N)\n");
            scanf("\n%c", &decyzja2);
            if(decyzja(decyzja2)==1)
                zmiana(kosci);
        }
        tablica(wyniki, lgraczy);
        wybor(wyniki, gracz, kosci);
        sumowanie(wyniki, lgraczy);
        TuraRunda(&gracz, lgraczy, &runda);
    }
    tablica(wyniki, lgraczy);
    koniec(wyniki, lgraczy);
    dodanieranking();
    return 0;
}

int gracze()    // Wybieranie ilości graczy, która będzie uczestniczyć w danej rozgrywce //
{
    int lgraczy;

    printf("||||||||||||||||||||||||||||||||||\n");
    printf("||\t   LICZBA GRACZY\t||\n");
    printf("||\t\t\t\t||\n");
    printf("||\t2\t3\t4\t||\n");
    printf("||\t\t\t\t||\n");
    printf("||||||||||||||||||||||||||||||||||\n");
    scanf("%d", &lgraczy);

    while(lgraczy>4 || lgraczy<2)
    {
        printf("BLAD: ZLA LICZBA GRACZY. PODAJ PONOWNIE LICZBE GRACZY:\n");
        scanf("%d", &lgraczy);
    }
    return lgraczy;
}

void TuraRunda(int* gracz, int lgraczy, int* runda) // Zmiana gracza oraz rundy //
{
    *gracz+=1;
    if(*gracz>lgraczy)
    {
        *gracz=1;
        *runda+=1;
    }
}

void losowanie(int kosci[]) // Losowanie kości gracza //
{
    srand( time(0) );
    printf("||\t    ");

    for(int i=0;i<N;i++)
    {
        kosci[i]=rand()%6+1;
        printf("%d ", kosci[i]);
    }

    printf("\t\t||\n");
}

int decyzja(char decyzja) // Gracz wybiera, czy chce wymienić kości //
{
    if(decyzja=='T' || decyzja=='t')
        return 1;
    else
        return 0;
}

void zmiana(int kosci[]) // Funkcja odpowiada za wybranie kości, które gracz chce wymienić oraz ponowny rzut nimi //
{
    int nkosci, i=0;
    int k1, k2, k3, k4, k5;
    k1=k2=k3=k4=k5=0;

    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||                                                                                                                                            ||\n");
    printf("||MOZESZ WYMIENIC MAKSYMALNIE 5 KOSCI. WYBIERANIE ZAKONCZY SIE W MOMENCIE WYBRANIA WSZYSTKICH KOSCI LUB WPISANIA 0. JAKA KOSC CHCESZ WYMIENIC?||\n");
    printf("||                                                                                                                                            ||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    scanf("%d", &nkosci);

    while(i<N)
    {
        if(nkosci==0)
            break;
        switch(nkosci)
        {
            case 1:
            {
                if(k1>0)
                {
                    printf("BLAD: TA KOSC ZOSTALA JUZ WYMIENIONA\n");
                    break;
                }
            kosci[nkosci-1]=rand()%6+1;
            k1=1;
            i++;
            break;
            }
            case 2:
            {
                if(k2>0)
                {
                    printf("BLAD: TA KOSC ZOSTALA JUZ WYMIENIONA\n");
                    break;
                }
            kosci[nkosci-1]=rand()%6+1;
            k2=1;
            i++;
            break;
            }
            case 3:
            {
                if(k3>0)
                {
                    printf("BLAD: TA KOSC ZOSTALA JUZ WYMIENIONA\n");
                    break;
                }
            kosci[nkosci-1]=rand()%6+1;
            k3=1;
            i++;
            break;
            }
            case 4:
            {
                if(k4>0)
                {
                    printf("BLAD: TA KOSC ZOSTALA JUZ WYMIENIONA\n");
                    break;
                }
            kosci[nkosci-1]=rand()%6+1;
            k4=1;
            i++;
            break;
            }
            case 5:
            {
                if(k5>0)
                {
                    printf("BLAD: TA KOSC ZOSTALA JUZ WYMIENIONA\n");
                    break;
                }
            kosci[nkosci-1]=rand()%6+1;
            k5=1;
            i++;
            break;
            }
            default:printf("BLAD: PODANO ZLY NUMER KOSCI\n");break;
        }
        if(i!=N)
            scanf("%d", &nkosci);
    }

    printf("||||||||||||||||||||||||||||||||||\n");
    printf("||\tNOWE KOSCI TO:\t\t||\n");
    printf("||\t   ");

    for(int j=0;j<N;j++)
            printf("%d ", kosci[j]);

    printf("\t\t||\n");
    printf("||\t\t\t\t||\n");
    printf("||||||||||||||||||||||||||||||||||\n");
}

void sumowanie(int wyniki[][14], int lgraczy) // Sumowanie aktualnych punktów, które posiadają gracze //
{
    for(int i=0;i<lgraczy;i++)
        wyniki[i][13]=0;

    for(int i=0;i<lgraczy;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(wyniki[i][j]>0)
                wyniki[i][13]+=wyniki[i][j];

            if(j==5 && wyniki[i][13]>=63)
                wyniki[i][13]+=35;
        }
    }
}

void koniec(int wyniki[][14], int lgraczy) // Wybór zwyciężcy //
{
    int zwyciezca=0, max=0;

    for(int i=0;i<lgraczy;i++)
    {
        if(wyniki[i][13]>max)
        {
            max=wyniki[i][13];
            zwyciezca=i+1;
        }
    }
    printf("\n");
    printf("||||||||||||||||||||||||||||||||||\n");
    printf("||\t    KONIEC GRY\t\t||\n");
    printf("||ZWYCIEZYL GRACZ %d! GRATULACJE!||\n", zwyciezca);
    printf("||\t    PODAJ NICK\t\t||\n");
    printf("||||||||||||||||||||||||||||||||||\n");
}

void dodanieranking() // Dodanie nicku gracza do rankingu lub dodanie mu jednej wygranej //
{
    char nazwa[21];
    bool warunek=false;
    Graczr ob, po, tmp;
    scanf("%s", &nazwa);
    
    while(strlen(nazwa)>20 || strlen(nazwa)<4)
    {
        printf("BLAD: ZLA DLUGOSC NICKU. NICK POWINEN MIEC OD 4 DO 20 ZNAKOW\n");
        scanf("%s", &nazwa);
    }

    FILE* plik=fopen("ranking.txt","rt");
    FILE* zapis1=fopen("rankingkopia.txt","wt");
    while(fscanf(plik,"%s\t%d",ob.nazwa, &ob.wygrana)==2)
    {
        if(strcmp(nazwa, ob.nazwa)==0)
        {
            if(ob.wygrana<999)
                ob.wygrana+=1;
            warunek=true;
        }
        fprintf(zapis1,"%-21s\t%5d\n",ob.nazwa, ob.wygrana);
    }

    fclose(plik);
    fclose(zapis1);

    FILE* plik2=fopen("rankingkopia.txt","rt");
    FILE* zapis2=fopen("ranking.txt","wt");
    while(fscanf(plik2,"%s\t%d", ob.nazwa, &ob.wygrana)==2)
        fprintf(zapis2,"%-21s\t%5d\n", ob.nazwa, ob.wygrana);

    fclose(plik2);
    fclose(zapis2);

    FILE* nowy=fopen("ranking.txt","at");
    if(warunek==false)
    {
        fprintf(nowy,"%-21s\t%5d\n",nazwa, 1);
    }

    fclose(nowy);
}

/*      TABLICA WYNIKÓW       */
void tablica(int wyniki[][14], int lgraczy) // Wyświetlanie tablicy wyników graczy // 
{
    char napisy[][20]={"1. JEDYNKI","2. DWOJKI","3. TROJKI","4. CZWORKI","5. PIATKI","6. SZOSTKI","7. 3 JEDNAKOWE","8. 4 JEDNAKOWE","9. FUL","10. MALY STRIT","11. DUZY STRIT","12. GENERAL","13. SZANSA","SUMA",'\0'};
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||\t\t     TABLICA WYNIKOW\t\t      ||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||\tGracz\t  ||");

    for(int i=0;i<lgraczy;i++)
        printf("   %d   ||", i+1);

    printf("\n");
    
    for(int i=0;i<14;i++)
    {
        printf("||%-14s  ||", napisy[i]);
        for(int j=0;j<lgraczy;j++)
        {
            printf("  %-4d ||", wyniki[j][i]);
        }
        printf("\n");
    }
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
}

void wybor(int wyniki[][14], int gracz, int kosci[]) // Gracz wybiera kategorię, do której chce przypisać dany wynik z kości //
{
    int wybor=0;
    printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||                                                                                                                                       ||\n");
    printf("||PROSZE WYBRAC KATEGORIE, DO KTOREJ CHCESZ PRZYPISAC SWOJE KOSCI (LICZBA -1 MOWI O TYM, ZE TA KATEGORIA ZOSTALA JESZCZE NIE WYKORZYSTANA||\n");
    printf("||                                                                                                                                       ||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    scanf("%d", &wybor);

    while(wybor<1 || wybor>13 || wyniki[gracz-1][wybor-1]>=0)
    {
        printf("BLAD: PODANO NUMER KATEGORII, KTORA NIE ISTNIEJE LUB JUZ ZOSTALA WYKORZYSTANA. PROSZE PODAC NUMER PONOWNIE\n");
        scanf("%d", &wybor);
    }

    if(wybor>0 && wybor<7)
        lista1(wyniki, gracz, wybor, kosci);
    else
        lista2(wyniki, gracz, wybor, kosci);
}

void lista1(int wyniki[][14], int gracz, int wybor, int kosci[]) // Pierwsze 6 kategorii //
{
    int sum=0;

    for(int i=0;i<N;i++)
    {
        if(kosci[i]==wybor)
            sum+=wybor;
    }

    wyniki[gracz-1][wybor-1]=sum;
}

void lista2(int wyniki[][14], int gracz, int wybor, int kosci[]) // Pozostałe 7 kategorii //
{
    switch(wybor)
    {
        case 7:trzyjednakowe(wyniki, gracz, wybor, kosci);break;
        case 8:czteryjednakowe(wyniki, gracz, wybor, kosci);break;
        case 9:ful(wyniki, gracz, wybor, kosci);break;
        case 10:malystrit(wyniki, gracz, wybor, kosci);break;
        case 11:duzystrit(wyniki, gracz, wybor, kosci);break;
        case 12:general(wyniki, gracz, wybor, kosci);break;
        case 13:szansa(wyniki, gracz, wybor, kosci);break;
    }
}

// Poniższe 7 funkcji odpowiadają za sprawdzanie oraz przypisywanie wyniku dla kategorii, którą wybrał gracz //
void trzyjednakowe(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    int sum=0, l=0;
    bool warunek=false;

    for(int i=0;i<N+1;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(kosci[j]==i+1)
                l+=1;
        }
        if(l==3)
        {
            warunek = true;
            break;
        }
        else
            l=0;
    }

    if(warunek == true)
    {
        for(int i=0;i<N;i++)
            sum+=kosci[i];
    }
    else
        sum=0;
    
    wyniki[gracz-1][wybor-1]=sum;
}

void czteryjednakowe(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    int sum=0, l=0;
    bool warunek=false;

    for(int i=0;i<N+1;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(kosci[j]==i+1)
                l+=1;
        }
        if(l==4)
        {
            warunek=true;
            break;
        }
        else
            l=0;
    }

    if(warunek==true)
        for(int i=0;i<N;i++)
            sum+=kosci[i];
            
    wyniki[gracz-1][wybor-1]=sum;
}

void ful(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    int sum=0, l=0, k=0, d=0;
    bool warunek=false;

    for(int i=0;i<N+1;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(kosci[j]==i+1)
                l++;
        }
        if(l==3)
        {
            k=i+1;
            break;
        }
        else
            l=0;
    }

    if(l==3)
    {
        for(int i=0;i<N+1;i++)
        {
            if(i+1!=k)
            {
                for(int j=0;j<N;j++)
                {
                    if(kosci[j]==i+1)
                        d++;
                }

            }
            if(d==2)
            {
                warunek=true;
                break;
            }
            else
                d=0;
        }
    }

    if(warunek==true)
        sum=25;

    wyniki[gracz-1][wybor-1]=sum;
}

void malystrit(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    int sum=0, l=1;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N-1-i;j++)
        {
            if(kosci[j]>kosci[j+1])
            {
                int temp=kosci[j+1];
                kosci[j+1]=kosci[j];
                kosci[j]=temp;
            }
        }
    }

    for(int i=1;i<N;i++)
    {
        if(kosci[i]-kosci[i-1]==1)
            l++;
    }

    if(l>=4)
        sum=30;

    wyniki[gracz-1][wybor-1]=sum;
}

void duzystrit(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    int sum=0;
    bool warunek = false;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N-1-i;j++)
        {
            if(kosci[j]>kosci[j+1])
            {
                int temp=kosci[j+1];
                kosci[j+1]=kosci[j];
                kosci[j]=temp;
            }
        }
    }

    for(int i=1;i<N;i++)
    {
        if((kosci[i]-kosci[i-1])!=1)
        {
            warunek=false;
            break;
        }
        warunek=true;    
    }

    if(warunek==true)
        sum=40;

    wyniki[gracz-1][wybor-1]=sum;
}

void general(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    bool sum=true;

    for(int i=1;i<N;i++)
    {
        if(kosci[0]!=kosci[i])
        {
            sum=false;
            break;
        }
    }

    if(sum==true)
        wyniki[gracz-1][wybor-1]=50;
    else
        wyniki[gracz-1][wybor-1]=0;
}

void szansa(int wyniki[][14], int gracz, int wybor, int kosci[])
{
    int sum=0;

    for(int i=0;i<N;i++)
        sum+=kosci[i];

    wyniki[gracz-1][wybor-1]=sum;
}