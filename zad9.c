#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree* Position;
typedef struct Tree{
    int number;
    Position left;
    Position right;
} tree;

Position InsertElement(Position root, int number);
Position CreateElement(int number);
int Replace(Position root);
int InOrderPrint(Position root);
int FindRandomNumber();

int main()
{
    Position root = NULL;
    int select;

    printf("Choose an action:\n");
    printf("1 - Numbers from the task\n");
    printf("2 - Random numbers\n");
    scanf(" %d", &select);

    if(select == 1)
    {
        root = InsertElement(root, 2);
        root = InsertElement(root, 5);
        root = InsertElement(root, 7);
        root = InsertElement(root, 8);
        root = InsertElement(root, 11);
        root = InsertElement(root, 1);
        root = InsertElement(root, 4);
        root = InsertElement(root, 2);
        root = InsertElement(root, 3);
        root = InsertElement(root, 7);

        printf("Numbers:    ");
        InOrderPrint(root);
        puts("");
        Replace(root);
        InOrderPrint(root);
    }

    else if(select == 2)
    {
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());
        root = InsertElement(root, FindRandomNumber());

        printf("Random numbers:    ");
        InOrderPrint(root);
        puts("");
        Replace(root);
        InOrderPrint(root);

    }
}

Position InsertElement(Position root, int number)
{
    Position temp = root;
    Position newEl = NULL;

    if(temp == NULL)
    {
        newEl = CreateElement(number);
        return newEl;
    }
    else if(number < temp -> number)
    {
        temp -> left = InsertElement(temp -> left, number);
    }
    else if(number >= temp -> number)
    {
        temp -> right = InsertElement(temp -> right, number);
    }

    return temp;
}

Position CreateElement(int number)
{
    Position newEl = NULL;
    newEl = (Position)malloc(sizeof(tree));

    if(!newEl)
    {
        perror("Memory not allocated!");
        return NULL;
    }

    newEl -> number = number;
    newEl -> left = NULL;
    newEl -> right = NULL;

    return newEl;
}

int Replace(Position root)
{
    Position temp = root;
    int sum = 0;
    int value = 0;

    if(temp -> left == NULL && temp -> right == NULL)
    {
        sum = temp -> number;
        temp -> number = 0;
        return sum;
    }
    else if(temp -> left == NULL && temp -> right != NULL)
    {
        sum = Replace(temp -> right);
        value = temp -> number + sum;
        temp -> number = sum;
        return value;
    }
    else if(temp -> left != NULL && temp -> right == NULL)
    {
        sum = Replace(temp -> left);
        value = temp -> number + sum;
        temp -> number = sum;
        return value;
    }
    else
    {
        sum = Replace(temp -> left) + Replace(temp -> right);
        value = temp -> number + sum;
        temp -> number = sum;
        return value;
    }

    return 0;
}

int InOrderPrint(Position root)
{
    Position temp = root;

    if(temp != NULL)
    {
        InOrderPrint(temp -> right);
        printf("%d ", temp -> number);                                    //??????????????????
        InOrderPrint(temp -> left); 
    }
    return 0;
}

int FindRandomNumber()
{
    int number;
    number = 10 + (rand() % (90 - 10 + 1));
}