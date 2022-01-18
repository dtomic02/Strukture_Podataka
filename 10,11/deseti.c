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



int ReadFile(listPosition head, treePosition root, char* fileName);                                         ////
listPosition SortedListInsertion(listPosition head, char *countryName);                                     ////
treePosition ReadFileCity(treePosition root, char *newFileName);                                            ////
int InsertAfter(listPosition current, listPosition after);                                                  ////       10a
listPosition CreateListElement(char *countryName);                                                          ////
listPosition FindBefore(listPosition head, listPosition after);                                             ////
treePosition CreateTreeElement(char *cityName, int population);                                             ////       10a
treePosition SortedTreeInsertion(treePosition root, char *cityName, int population);                        ////
int PrintLinkedList(listPosition head,treePosition root);                                                   ////
int PrintTree(treePosition root);                                                                           ////
int SearchCountry(listPosition head);
int SearchCity(listPosition temp);
int PrintCitiesMoreThanPopulation(treePosition root, int minPopulation);


int main()
{
    int choice;

    listElement country = {.countryName = '\0', .next = NULL};
    listPosition head = &country;
    treePosition root = NULL;

    printf("CHOOSE AN ACTION: \n\n");
    printf("1 - Trees in List\n");
    printf("2 - Lists in Tree\n");
    printf("3 - Search a country and cities with certain population\n");
    printf("Your choice: ");    scanf(" %c", &choice);


    ReadFile(head, root, "drzave.txt");                             //?
    if(choice == 1)
    {
        
        
        printf("Linked list:\n");
        PrintLinkedList(head, root);
        
    }
    //else if(choice == 3)
}

int ReadFile(listPosition head, treePosition root, char* fileName)
{
    char countryName[MAX];
    char newFileName[MAX];
    FILE *fp = NULL;
    listPosition temp = NULL;

    fp = fopen(fileName, "r");

    if(!fp)
    {
        printf("File cannot be opened!");
    }
    while(!feof(fp))
    {
        fscanf(fp, " %s %s", countryName, newFileName);
        temp = SortedListInsertion(head, countryName);
        root = ReadFileCity(root, newFileName);

        temp -> tree = root;
        root = NULL;
    }
}

listPosition SortedListInsertion(listPosition head, char *countryName)
{
    listPosition temp = head -> next;
    listPosition newElement = NULL;
    listPosition before = NULL;
    newElement = CreateListElement(countryName);
    if(!newElement)
    {
        printf("Memory cannot be allocated!");
        return NULL;
    }
    if(!temp)
    {
        InsertAfter(head, newElement); return head -> next; //return newElement
    }
    else
    {
        while(strcmp(temp -> countryName, countryName) > 0)
            temp = temp -> next;

        before = FindBefore(head, temp);
        InsertAfter(before, newElement);
    }

    return before -> next;      //return newElement;
}

listPosition CreateListElement(char *countryName)
{
    listPosition newElement = NULL;
    newElement = (listPosition)malloc(sizeof(sizeof(listElement)));
    if(!newElement)
    {
        printf("Memory cannot be allocated!");
        return NULL;
    }
    strcpy(newElement -> countryName, countryName);
    newElement -> next = NULL;
    newElement -> tree = NULL;

    return newElement;
}

int InsertAfter(listPosition current, listPosition after)
{
    after -> next = current -> next;
    current -> next = after;
    return 0;
}

listPosition FindBefore(listPosition head, listPosition after)
{
    listPosition temp = NULL;
    temp = head;

    while(temp -> next != after)
        temp = temp -> next;

    return temp;
}

treePosition ReadFileCity(treePosition root, char *newFileName)
{
    char tempName[MAX];
    int tempPopulation;
    FILE* fp = NULL;
    fp = fopen(newFileName, "r"); 
    treePosition newElement = NULL;

    if(!fp)
    {
        printf("Neuspjelo otvaranje datoteke!\n");
        return NULL;
    }

    newElement = (treePosition)malloc(sizeof(treeElement));
    if(!newElement)
    {
        printf("Memory cannot be allocated!");
        return NULL;
    }
    newElement -> left = NULL;
    newElement -> right = NULL;

    while(!feof(fp))
    {
        fscanf(fp, " %s %d", tempName, &tempPopulation);
        newElement = SortedTreeInsertion(root, tempName, tempPopulation);
    }

    return 0;
}

treePosition SortedTreeInsertion(treePosition root, char* cityName, int population)
{
    treePosition newElement = NULL;
    

    if(!root)
    {
        newElement = CreateTreeElement(cityName, population);
        return newElement;
    }
    else if(root -> population > population)
    {
        root -> left = SortedTreeInsertion(root -> left, cityName, population);return root;
    }
    else if(root -> population < population)
    {
        root -> right = SortedTreeInsertion(root -> right, cityName, population);return root;
    }
    else                                                                                                    //ako gradovi imaju istu populaciju
    {
        if(strcmp(root -> cityName, cityName) > 0)
        {
            root -> left = SortedTreeInsertion(root -> left, cityName, population);
            return root;
        }
        else if(strcmp(root -> cityName, cityName) < 0)
        {
            root -> right = SortedTreeInsertion(root -> right, cityName, population);
            return root;
        }
        else
        {
            free(newElement);
            return root;
        }
    }

    return newElement;

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

int PrintTree(treePosition root)
{
    if(root)
    {
        PrintTree(root -> left);
        printf("%s ", root -> cityName);
        PrintTree(root -> right);
        puts("");
    }
    return 0;
}

int SearchCountry(listPosition head)
{
    char countryName[MAX] = {'\0'};
    while(countryName != "exit")
    {
        printf("Which country would you like to search?\n");
        printf("Type 'exit' when you are done!\n");
        scanf(" %s", countryName);
        if(countryName != "exit")
        {
            listPosition temp = head -> next;
            while(temp)
            {
                if(!strcmp(countryName, temp -> countryName))
                {
                    SearchCity(temp);
                }
                else
                {
                    temp = temp -> next;
                }
            }
            if(temp = NULL)
            {
                printf("%s is not available!", countryName);
            }
        }
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