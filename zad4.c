#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 20
#define MAX 1024

typedef struct _polinom *Pozicija;
typedef struct _polinom{
    int koef;
    int eksp;
    Pozicija next;
} polinom;


int UnosIzDatoteke(Pozicija, Pozicija);                                                 //uzima brojeve iz datoteke
int UnosUListu(Pozicija, char*);                                                        //unosi brojeve unesene iz datoteke i pravi listu
int Sortiraj(Pozicija);
int ZbrojiIsteEksp(Pozicija, Pozicija);
Pozicija NadiPrethodnog(Pozicija, int);
int Ispis(Pozicija);                                                                    
int ZbrojiPolinome(Pozicija, Pozicija, Pozicija);                                       //
int PomnoziPolinome(Pozicija, Pozicija, Pozicija);                                      //


int main()
{
    polinom headp1 = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headp2 = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headZbroj = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headUmnozak = {.koef = 0, .eksp = 0, .next = NULL};

    
    int a = 0;
    a = UnosIzDatoteke(&headp1, &headp2);
    if (a == EXIT_FAILURE)
    {
        return 0;
    }
    Sortiraj(&headp1);
    ZbrojiIsteEksp(headp1.next, &headp1);

    Sortiraj(&headp2);
    ZbrojiIsteEksp(headp2.next, &headp2);

    printf("Prvi polinom: ");
    Ispis(headp1.next);                                                                              //ispisujemo polinome
    puts("");
    printf("Drugi polinom: ");
    Ispis(headp2.next);
    puts("");


    ZbrojiPolinome(&headp1, &headp2, &headZbroj);
    Sortiraj(&headZbroj);
    ZbrojiIsteEksp(headZbroj.next, &headZbroj);
    printf("Zbroj polinoma: ");                                                                       //ispisujemo zbroj dva polinoma
    Ispis(headZbroj.next);
    puts("");


    PomnoziPolinome(&headp1, &headp2, &headUmnozak);
    Sortiraj(&headUmnozak);
    ZbrojiIsteEksp(headUmnozak.next, &headUmnozak);
    printf("Umnozak polinoma: ");                                                                   //ispisujemo umnozak dva polinoma
    Ispis(headUmnozak.next);
    puts("");


    return 0;
}


int UnosIzDatoteke(Pozicija pol1, Pozicija pol2)
{
    FILE *fp = fopen("pol.txt", "r");
    char line[MAX];
    int status = 0;
    
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return -1;
    }
    fgets(line, MAX, fp);                                                            
    status = UnosUListu(pol1, line);                                                    //prva lista
    if (status != 0)
    {
        printf("Neuspjesno unesen prvi polinom u listu\n");
        return -2;
    }
    fgets(line, MAX, fp); 
    status = UnosUListu(pol2, line);                                                    //druga lista
    if (status != 0)
    {
        printf("Neuspjesno unesen drugi polinom u listu\n");
        return -3;
    }


    fclose(fp);

    return 0;
}

int UnosUListu(Pozicija head, char *line)
{
    Pozicija R = NULL;
    int tempKoef = 0;
    int tempEksp = 0;
    int pomak = 0;
    int status = 2;                                                                         //paran broj brojeva u datoteci
    char *pomoc = line;
    while (strlen(pomoc) > 0)
    {
        status = sscanf(pomoc, " %d %d %n", &tempKoef, &tempEksp, &pomak);

        if (status != 2)
        {
            return -1;                                                                      //datoteka nije kakva bi trebala biti
        }

        R = (Pozicija)malloc(sizeof(polinom));
        if (!R)
        {
            perror("Alokacija memorije neuspjesna!\n");
            return -2;
        }
        R -> koef = tempKoef;
        R -> eksp = tempEksp;
        R -> next = head -> next;
        head -> next = R;
        pomoc = pomoc + pomak;
    }

    return 0;
}

int Sortiraj(Pozicija P) {													

	Pozicija j, prev_j, temp, end;

	end = NULL;

	while (P->next != end) {
		prev_j = P;
		j = P->next;
		
		while (j->next != end) {
			if (j->eksp > j->next->eksp) {
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}
    return 0;
}

int ZbrojiIsteEksp(Pozicija prvi, Pozicija head)
{
    Pozicija temp = NULL;
    Pozicija prethodni = NULL;
    Pozicija zbroj = NULL;
    while(temp -> next != NULL)
    {
        if (temp -> eksp == temp -> next -> eksp)
        {
            zbroj = (Pozicija)malloc(sizeof(polinom));
            if (!zbroj)
            {
                perror("\nAlokacija memorije neuspjesna!\n");
                return EXIT_FAILURE;
            }
            prethodni = NadiPrethodnog(head, temp -> eksp);
            zbroj -> eksp = temp -> eksp;
            zbroj -> koef = temp -> koef + temp -> next -> koef;
            zbroj -> next = temp -> next -> next;
            prethodni -> next = zbroj;
        }
        temp = temp -> next;
    }

    return 0;
}

Pozicija NadiPrethodnog(Pozicija head, int eksp)
{
    Pozicija preth = head; 
    Pozicija izaPreth = preth -> next;

    while (izaPreth != NULL && izaPreth -> eksp != eksp)
    {
        preth = izaPreth;
        izaPreth = preth -> next;
    }

    if (izaPreth == NULL)   return 0;

    return preth;
}

int Ispis(Pozicija prvi)
{
    Pozicija temp = NULL;
    temp = prvi;
    int br = 0;
    while (temp != NULL)
    {
        if (br != 0)
        {
            if (temp -> koef >= 0)  printf("  +  ");    
                                                                                            //ako je koeficijent pozitivan ispisujemo plus, u suprotnom ispisujemo minus,
            else    printf("  -  ");                                                        //a koeficijentu poslije ispisujemo apsolutnu vrijednost
        }
        

        if (temp -> eksp >= 0)
        {
            printf("%dx^%d", abs(temp -> koef), temp -> eksp);
        }

        else
        {
            printf("%dx^(%d)", abs(temp -> koef), temp -> eksp);
        }

        temp = temp -> next;
        br++;
    }

    return 0;
}
int ZbrojiPolinome(Pozicija headp1, Pozicija headp2, Pozicija headzbr)
{
    Pozicija pomocP1 = headp1 -> next;
    Pozicija pomocP2 = headp2 -> next;
    Pozicija noviEl = NULL;
    
    while(pomocP1 != NULL)
    {
        noviEl = (Pozicija)malloc(sizeof(polinom));
        if (!noviEl)
        {
            perror("Alokacija memorije neuspjesna!\n");
            return -1;
        }
        noviEl -> eksp = pomocP1 -> eksp;
        noviEl -> koef = pomocP1 -> koef;
        noviEl -> next = headzbr -> next;
        headzbr -> next = noviEl;
        pomocP1 = pomocP1 -> next;
    }
    while(pomocP2 != NULL)
    {
        noviEl = (Pozicija)malloc(sizeof(polinom));
        if (!noviEl)
        {
            perror("Alokacija memorije neuspjesna!\n");
            return -2;
        }
        noviEl -> eksp = pomocP2 -> eksp;
        noviEl -> koef = pomocP2 -> koef;
        noviEl -> next = headzbr -> next;
        headzbr -> next = noviEl;
        pomocP2 = pomocP2 -> next;
    }

    return 0;
}

int PomnoziPolinome(Pozicija headp1, Pozicija headp2, Pozicija headumn)
{
    Pozicija pomocP1 = headp1 -> next;
    Pozicija pomocP2 = headp2 -> next;
    Pozicija noviEl = NULL;
    while(pomocP1 != NULL)
    {
        while(pomocP2 != NULL)
        {
            noviEl = (Pozicija)malloc(sizeof(polinom));
            if (!noviEl)
            {
                perror("\nAlokacija memorije neuspjesna!\n");
                return -1;
            }
            noviEl -> eksp = pomocP1 -> eksp + pomocP2 -> eksp;
            noviEl -> koef = pomocP1 -> koef * pomocP2 -> koef;
            noviEl -> next = headumn -> next;
            headumn -> next = noviEl;
            pomocP2 = pomocP2 -> next;
        }
        pomocP1 = pomocP1 -> next;
    }

    return 0;
}