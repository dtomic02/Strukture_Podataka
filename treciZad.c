#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct _osoba *Pozicija;
typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godinaRodenja;
    Pozicija next;
} osoba;

void UnosPocetak(char *ime, char *prezime, int godRod, Pozicija P);
void UnosKraj(char *ime, char *prezime, int godRod, Pozicija P);
void Ispis(Pozicija P);
Pozicija NadiZadnjeg(Pozicija P);
void DodajIza(Pozicija P, Pozicija zadnji);
Pozicija Prezime(char *prezime, Pozicija P);
void BrisiPoImenu(char *ime, Pozicija P);                                                                           //brisanje po imenu
void DodajIspredOdredenog(char *ime, char *prezime, int godRod, char* staroPrezime, Pozicija P);                    //3b
Pozicija NadiPrethodnog(char *prezime, Pozicija);                                                                   //3b
void DodajIzaOdredenog(char *ime, char *prezime, int godRod, char* staroPrezime, Pozicija P);                       //3a
void Sortiraj(Pozicija P);
void UnesiUDatoteku(Pozicija);
void CitajIzDatoteke(Pozicija P);                                                                                   //3e



int main()
{
    char tempIme[MAX];
    char tempPrezime[MAX];
    int godRod;
    int odabir = MAX;
    osoba Head;
    Head.next = NULL;
    char tempTempPrezime[MAX];                                                                      //za 3a i 3b

    
    while(odabir != 0)
    {     
        printf("Odaberite radnju: \nUnesi osobu na pocetak liste - 1\n");
        printf("Ispisi listu - 2\n");
        printf("Dodaj element na kraj liste - 3\n");
        printf("Pronadi element po prezimenu - 4\n");
        printf("Izbrisi element po imenu - 5\n");
        printf("Unesi ispred odredenog elementa - 6\n");
        printf("Unesi iza odredenog elementa - 7\n");
        printf("Prekid radnji - 0\n");
        
        printf("ODABIR: ");
        scanf("%d", &odabir);
        if(odabir == 1)
        {
            printf("Unesi podatke o osobi: \n");
            printf("Ime: ");                scanf(" %s", tempIme);
            printf("Prezime: ");            scanf(" %s", tempPrezime);
            printf("Godina rodenja: ");     scanf("%d", &godRod);
            UnosPocetak(tempIme, tempPrezime, godRod, &Head);
        }

        else if(odabir == 2)
        {
            Ispis(&Head);
            printf("\n\n");
        }

        else if(odabir == 3)
        {
            printf("Unesi podatke o osobi: \n");
            printf("Ime: ");            scanf(" %s", tempIme);
            printf("Prezime: ");        scanf(" %s", tempPrezime);
            printf("Godina rodenja: "); scanf("%d", &godRod);
            UnosKraj(tempIme, tempPrezime, godRod, &Head);
        }

        else if(odabir == 4)
        {
            printf("Unesi prezime koje zelis pronaci: \n");
            printf("PREZIME: ");    scanf(" %s", tempPrezime);
            Prezime(tempPrezime, &Head);
        }

        else if(odabir == 5)
        {
            printf("Unesi ime osobe koju zelis izbrisati: \n");
            printf("IME: ");    scanf(" %s", tempIme);
            BrisiPoImenu(tempIme, &Head);
        }
        else if(odabir == 6)
        {
            printf("Unesi prezime ispred kojeg zelis dodati osobu: ");
            scanf(" %s", tempTempPrezime);

            printf("Unesi podatke o osobi koju zelis dodati: \n");
            printf("Ime: ");            scanf(" %s", tempIme);
            printf("Prezime: ");        scanf(" %s", tempPrezime);
            printf("Godina rodenja: "); scanf("%d", &godRod);
            DodajIspredOdredenog(tempIme, tempPrezime, godRod, tempTempPrezime, &Head);
        }
        else if(odabir == 7)
        {
            printf("Unesi prezime ispred kojeg zelis dodati osobu: ");
            scanf(" %s", tempTempPrezime);

            printf("Unesi podatke o osobi koju zelis dodati: \n");
            printf("Ime: ");            scanf(" %s", tempIme);
            printf("Prezime: ");        scanf(" %s", tempPrezime);
            printf("Godina rodenja: "); scanf("%d", &godRod);
            DodajIzaOdredenog(tempIme, tempPrezime, godRod, tempTempPrezime, &Head);
        }
        else if(odabir == 8)       //3c
        {
            Sortiraj(&Head);
            puts("Lista je sortirana");
        }
        else if(odabir == 9)   //datoteka 3d
        {
            UnesiUDatoteku(&Head);
            printf("Lista je unesena u datoteku.\n");
        }

        else if(odabir == 10)
        {

        }

        else if(odabir == 0)
        {
            printf("KRAJ!\n");
            break;
        }

        else printf("KRIV UNOS!\n\n");

        puts("");
    }

}

void UnosPocetak(char *ime, char *prezime, int godRod, Pozicija P)
{
    Pozicija ptr;
    ptr = malloc(sizeof(Pozicija));
    
    strcpy(ptr -> ime, ime);
    strcpy(ptr -> prezime, prezime);
    ptr -> godinaRodenja = godRod;

    ptr -> next = P -> next;
    P -> next = ptr;
}

void Ispis(Pozicija P)
{
    
    printf("IME\tPREZIME\tGOD RODENJA\n");
    while(P != NULL)
    {
        printf("%s\t%s\t%d\n", P -> ime,
        P -> prezime, P -> godinaRodenja);
        P = P -> next;
    }
}

void UnosKraj(char *ime, char *prezime, int godRod, Pozicija P)
{
    Pozicija ptr;
    Pozicija zadnji = NULL;
    ptr = malloc(sizeof(Pozicija));

    strcpy(ptr -> ime, ime);
	strcpy(ptr -> prezime, prezime);
	ptr -> godinaRodenja = godRod;
	ptr -> next = NULL;    

    zadnji = NadiZadnjeg(P);
    DodajIza(ptr, zadnji);
}
Pozicija NadiZadnjeg(Pozicija P)
{
    Pozicija ptr = P;

    while(ptr -> next != NULL)
    {
        ptr = ptr -> next;
    }
    return ptr;
} 
void DodajIza(Pozicija P, Pozicija zadnji)
{
    P -> next = zadnji -> next;
    zadnji -> next = NULL;
}

Pozicija Prezime(char *prezime, Pozicija P)
{
    int br;
    br = 0;

    while(P -> next != NULL)
    {
        if(strcmp(P -> prezime, prezime) == 0) break;
        P -> next = P;
        br++;
    }

    return P;
}


void BrisiPoImenu(char *ime, Pozicija P)
{
    Pozicija prviPtr;
    //Pozicija drugiPtr;
    prviPtr = P;
    P = P -> next;
    while(P -> next != NULL)
        {
            if(strcmp(P -> ime, ime) == 0) break;
            prviPtr = P;
            P = P -> next;
        }

    if(prviPtr != NULL)
    {
        P = prviPtr -> next;
        prviPtr -> next = NULL;
        free(P);    
    }
    
}

void DodajIspredOdredenog(char *ime, char *prezime, int godRod, char* staroPrezime, Pozicija P)
{
    Pozicija R;
    Pozicija prethodni = NadiPrethodnog(staroPrezime, P);
    R = (Pozicija)malloc(sizeof(osoba));

    strcpy(R -> ime, ime);
	strcpy(R -> prezime, prezime);
    R -> godinaRodenja = godRod;
    R -> next = prethodni -> next;
    prethodni -> next = R;
}

Pozicija NadiPrethodnog(char *prezime, Pozicija P)
{
    Pozicija prethodni = P;
    P = P -> next;
    while(P != NULL)
    {
        if(strcmp(P -> prezime, prezime) == 0) break;
        else {prethodni = P; P = P -> next;}
    }

    if(P == NULL) printf("Pokusajte drugo prezime, ovo nije u listi!\n");

    return prethodni;
}


void DodajIzaOdredenog(char *ime, char *prezime, int godRod, char* staroPrezime, Pozicija P)
{
    Pozicija R;
    P = Prezime(staroPrezime, P);
    R = (Pozicija) malloc (sizeof(osoba));
    strcpy(R -> ime, ime);
	strcpy(R -> prezime, prezime);
    R -> godinaRodenja = godRod;
    R -> next = P -> next;
    P -> next = R;
}

void Sortiraj(Pozicija P) {												

	Pozicija R;
    Pozicija prethodni;
    Pozicija kraj;
	kraj = NULL;

    Pozicija pomoc;

	while (P->next != kraj) {
		prethodni = P;
		R = P->next;
		
		while (R -> next != kraj) {
			if (strcmp(R -> prezime, R -> next -> prezime) > 0) {
				pomoc = R -> next;
				prethodni -> next = pomoc;
				R -> next = pomoc -> next;
				pomoc -> next = R;
				R = pomoc;
			}

			prethodni = R;
			R = R -> next;
		}

		kraj = R;
	}

}

void UnesiUDatoteku(Pozicija P)
{
    FILE *lista;
    lista = fopen("lista.txt", "w");

    if(lista == NULL)
    {
        printf("Greska pri otvaranju!");
    }

    fprintf(lista, "Ime\tPrezime\tGodina rodenja\n");
    while(P !=  NULL)
    {
        fprintf(lista, "%s\t%s\t%d\n", P -> ime, P -> prezime, P -> godinaRodenja);
        P = P -> next;
    }

    fclose(lista);
}

void CitajIzDatoteke(Pozicija P)
{
    FILE *lista;
    Pozicija R;

    P -> next = NULL;
    lista = fopen("lista.txt", "r");
    if(lista == NULL) printf("Datoteka je prazna");

    rewind(lista);

    while(!feof(lista))
    {
        R = (Pozicija)malloc(sizeof(osoba));
        fscanf(lista, " %s %s %d", R -> ime, R -> prezime, &R -> godinaRodenja);

        R -> next = P -> next;
        P -> next = R;
        P = R; 
    }


    fclose(lista);
}
