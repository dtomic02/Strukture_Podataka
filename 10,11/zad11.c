#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct _tree* treePosition;
typedef struct _tree {
    char cityName[MAX];
    int population;
    treePosition right;
    treePosition left;
} treeElement;

typedef struct _list* listPosition;
typedef struct _list {
    char countryName[MAX];
    listPosition next;
    treePosition tree;
} listElement;

typedef struct _hashTable* hashPosition;
typedef struct _hashTable {
    listPosition head;
} hashTable;

listPosition CreateHead();
int ReadFile(char *fileName, hashTable hashArray[]);
listPosition CreateListElement(char *countryName);  
int CalculateHashIndex(char* countryName);
int InsertIntoList(listPosition newElement, listPosition head);
int ReadNewFile(listPosition, char *newFileName);
treePosition CreateTreeElement(char *cityName, int population);
treePosition InsertIntoTree(treePosition root, treePosition newElement);
int PrintLinkedList(listPosition newElement, treePosition root);
int PrintTree(treePosition root);
int SearchCountry(listPosition head);
int SearchCity(listPosition temp);
int PrintCitiesMoreThanPopulation(treePosition root, int minPopulation);



int main()
{
    char choice = '\0';
    hashTable hashArray[11];
    int i = 0;
    for(i = 0; i < 11; i++)
    {
        hashArray[i].head = NULL;
    }
    for(i = 0; i < 11; i++)
    {
        hashArray[i].head = CreateHead();
    }
    ReadFile("drzave.txt", hashArray);

    printf("CHOOSE AN ACTION:\n");
    printf("1 - Print countries with cities\n");
    printf("2 - Find cities with certain population\n");
    printf("YOUR CHOICE: ");    scanf(" %c", &choice);

    /*if(choice = '1')
    {
        PrintLinkedList(hashArray)
    }*/
}

listPosition CreateHead()
{
    listPosition head = NULL;
    head = (listPosition)malloc(sizeof(listElement));
    if(!head)
    {
        printf("Memory cannot be allocated!");
        return NULL;
    }

    strcpy(head -> countryName, "");
    head ->next = NULL;
    head -> tree = NULL;

    return head;
}

int ReadFile(char *fileName, hashTable hashArray[])
{
    char *line;
    char countryName[MAX];
    char newFileName[MAX];
    int numberOfBytes = 0;
    int index = 0;
    FILE *fp = NULL;
    char CountryName[MAX] = {'\0'};
    listPosition newElement = NULL;


    fp = fopen(fileName, "r");
    if(!fp)
    {
        printf("File cannot be opened!\n");
        return -5;
    }
    while(!feof(fp))
    {
        fgets(line, MAX, fp);
        if(sscanf(line, "%s %s %n", countryName, newFileName, numberOfBytes))
        {
            index = CalculateHashIndex(countryName);

            newElement = CreateListElement(countryName);
            InsertIntoList(newElement, hashArray[index].head);

            ReadNewFile(newElement, newFileName);
            line = line + numberOfBytes;
        }
    }

    fclose(fp);
}

int CalculateHashIndex(char* countryName)
{
    int index = 0;
    int i = 0;

    for(i = 0; i < 5; i++)
    {
        index = index + countryName[i];
    }
    return (index % 11);
}

listPosition CreateListElement(char *countryName)
{
    listPosition newElement = NULL;
    newElement = (listPosition)malloc(sizeof(listElement));

    if(!newElement)
    {
        printf("Memory cannot be allocated!\n");
        return NULL;
    }

    newElement -> tree = NULL;
    newElement -> next = NULL;
    strcpy(newElement -> countryName, countryName);
    return newElement;
}

int InsertIntoList(listPosition newElement, listPosition head)
{
    //listPosition temp = head;
    if(head -> next == NULL)
    {
        head -> next = newElement;
        newElement -> next = NULL;
    }
    else
    {
        while(head -> next != NULL && (strcmp(head -> next -> countryName, newElement -> countryName)) < 0)
        {
            head = head -> next;
        }
        
        newElement -> next = head -> next;
        head -> next = newElement;

    }
    return 0;
}

int ReadNewFile(listPosition newElement, char* newFileName)
{
    char *line;
    char cityName[MAX];
    int population = 0;
    int numberOfBytes = 0;
    int index = 0;
    FILE *fp = NULL;
    treePosition newElementTree;

    fp = fopen(newFileName, "r");
    if(!fp)
    {
        printf("File cannot be opened!\n");
        return -1;
    }
    while(!feof(fp))
    {
        fgets(line, MAX, fp);
        if(sscanf(line, "%s %d %n", cityName, population, numberOfBytes))
        {
            newElementTree = CreateTreeElement(cityName, population);

            newElementTree = InsertIntoTree(newElement -> tree, newElementTree);
            line = line + numberOfBytes;
        }
    }

    fclose(fp);

    return 0;
}

treePosition CreateTreeElement(char *cityName, int population)
{
    treePosition newElement = NULL;
    newElement = (treePosition)malloc(sizeof(treeElement));
    if(!newElement)
    {
        printf("Memory cannot be allocated!");
        return NULL;
    }
    newElement -> left = NULL;
    newElement -> right = NULL;
    strcpy(newElement -> cityName, cityName);
    newElement -> population = population;

    return newElement;
}

treePosition InsertIntoTree(treePosition root, treePosition newElement)
{
    if(root == NULL)
    {
        root = newElement;
    }
    else if(root -> population > newElement -> population)
    {
        root -> left = InsertIntoTree(root -> left, newElement);
    }
    else if(root -> population < newElement -> population)
    {
        root -> right = InsertIntoTree(root -> right, newElement);
    }
    else
    {
        free(newElement);
    }
    return root;
}

int PrintTree(treePosition root)
{
    if(root)
    {
        PrintTree(root -> left);
        printf("%s %d\n", root -> cityName, root -> population);
        PrintTree(root -> right);
        puts("");
    }
    return 0;
}

int SearchCity(listPosition temp)
{
    int minPopulation;
    printf("Enter the minimal population of a city in %s: ",temp -> countryName);
    scanf("%d", &minPopulation);

    PrintCitiesMoreThanPopulation(temp -> tree, minPopulation);
}

int PrintCitiesMoreThanPopulation(treePosition root, int minPopulation)
{
    treePosition temp = root;
    if(root != NULL)
    {
        if(temp -> population <= minPopulation)
        {
            PrintCitiesMoreThanPopulation(temp -> right, minPopulation);
        }
        else
        {
            PrintCitiesMoreThanPopulation(temp -> left, minPopulation);
            printf("%s with population of %d",temp -> cityName, temp ->population);
            PrintCitiesMoreThanPopulation(temp -> right, minPopulation);
        }
    }
    return 0;
}

int PrintLinkedList(listPosition head, treePosition root)
{
    listPosition temp = head -> next;
    while(temp)
    {
        printf("%s\n", temp -> countryName);
        PrintTree(root);
        temp = temp -> next;
    }
    return 0;
}