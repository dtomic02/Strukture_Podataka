#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024



typedef struct _student{
    char ime[MAX];
    char prezime[MAX];
    int brojBodova;
} student;

int main()
{
    int brojStudenata;
    student *s = NULL;
    int i;
    FILE *fp;
    int maxBodovi = 0.0;
    double relativni = 0.0;

    fp = fopen("datoteka.txt", "r");


    while(!feof(fp))
    {
        if(fgetc(fp) == '\n') brojStudenata++;
    }

    s = (student*) malloc(brojStudenata * sizeof(student));

    rewind(fp);

    for(i = 0; i < brojStudenata; i++)
    {
        fscanf(fp, " %s %s %d", s[i].ime, s[i].prezime, &s[i].brojBodova);
    }

    for(i = 0; i < brojStudenata; i++)
    {
        if(s[i].brojBodova >= maxBodovi) maxBodovi = s[i].brojBodova;
    }

    
    for(i = 0; i < brojStudenata; i++)
    {
        printf("%d. STUDENT: ", i+1);
        relativni = (float)s[i].brojBodova/(float)maxBodovi * 100;
        printf("%s %s %d %lf\n", s[i].ime, s[i].prezime, s[i].brojBodova, relativni);
    }
}