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
void Prezime(char *prezime, Pozicija P);
void BrisiPoImenu(char *ime, Pozicija P);                                //brisanje po imenu

int main()
{
    char tempIme[MAX];
    char tempPrezime[MAX];
    int godRod;
    int odabir = MAX;
    osoba Head;
    Head.next = NULL;
    
    while(odabir != 0)
    {     
        printf("Odaberite radnju: \nUnesi osobu na pocetak liste - 1\n");
        printf("Ispisi listu - 2\n");
        printf("Dodaj element na kraj liste - 3\n");
        printf("Pronadi element po prezimenu - 4\n");
        printf("Izbrisi element po imenu - 5\n");
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

void Prezime(char *prezime, Pozicija P)
{
    int br;
    br = 0;

    while(P -> next != NULL)
    {
        if(strcmp(P -> prezime, prezime) == 0) break;
        P -> next = P;
        br++;
    }

    if(P -> next = NULL) puts("Trazeno prezime se ne nalazi u listi!");
    else printf("Prezime %s se nalazi na %d. mjestu.\n", prezime, br + 1);
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