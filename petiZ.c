#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

typedef struct _StackElement *Pozicija;
typedef struct _StackElement
{
    float element;
    Pozicija next;
} StackElement;


int CitajDatoteku(Pozicija);
Pozicija Push(Pozicija, float);
float Pop(Pozicija);
int Racunanje(Pozicija, char);


int main()
{
    StackElement head = {.element = 0, .next = NULL};
    Pozicija P = &head;
    int a=0;
    a = CitajDatoteku(P);
    if(a == EXIT_FAILURE)
    {
        return 0;
    }
    printf("\nRezultat:%.2f\n", P -> next -> element);

    return EXIT_SUCCESS;
}



Pozicija Push(Pozicija head, float broj)                                                                                    //stavlja broj na stog
{
    Pozicija q;
    q = (Pozicija)malloc(sizeof(StackElement));
    if (!q)
    {
        perror("\nAlokacija memorije neuspjesna!\n");                                                                               
        return NULL;
    }
    q->next = head->next;
    head->next = q;
    q->element = broj;

    return q;
}

float Pop(Pozicija head)                                                                                                    //mice broj sa stoga i vraca rezultat
{
    float Broj = 0.0;
    Pozicija temp;
    temp = head->next;

    Broj = temp->element;
    head->next = temp->next;
    free(temp);

    return Broj;
}

int CitajDatoteku(Pozicija head)                                                                                            //ako naleti na broj stavi ga na stog,
{                                                                                                                           //u suprotnon racuna operaciju u fji racunanje
    char *dat = {0};
    char buffer[MAX] = {0};
    char *ptr;
    FILE *fp = NULL;

    dat = (char*)malloc(sizeof(char) * MAX);
    ptr = buffer;

    printf("Unesi ime datoteke iz koje zelis ucitati: \n");
    scanf(" %s", dat);

    fp = fopen(dat, "r");

    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n", dat);
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX, fp);
    fclose(fp);
    while (strlen(ptr) > 0)
    {
        char operacija = 0;
        float broj = 0;
        int pomak = 0;
        if (sscanf(ptr, " %f %n", &broj, &pomak) == 1)
        {
            Push(head, broj);
            ptr += pomak;
        }
        else
        {
            sscanf(ptr, " %c %n", &operacija, &pomak);
            Racunanje(head, operacija);
            ptr += pomak;
        }
    }

    return EXIT_SUCCESS;
}

int Racunanje(Pozicija head, char operacija)                                                                                        //racuna zadanu operaciju i vraca rezultat na stog
{
    float br1 = 0.0;
    float br2 = 0.0;

    switch (operacija)
    {
    case '+':
        br1 = Pop(head);
        br2 = Pop(head);
        Push(head, br1 + br2);
        break;

    case '-':
        br1 = Pop(head);
        br2 = Pop(head);
        Push(head, br2 - br1);
        break;

    case '*':
        br1 = Pop(head);
        br2 = Pop(head);
        Push(head, br2 * br1);
        break;

    case '/':
        br1 = Pop(head);
        br2 = Pop(head);
        if (br2 == 0)
        {
            printf("\nDijeljenje s 0 nije dozvoljeno!");
        }
        else
        {
            Push(head, br1 / br2);
        }
        break;
    }

    return EXIT_SUCCESS;
}