#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stablo;
typedef struct Stablo* Position;
typedef struct Stablo{
    int num;
    Position left;
    Position right;
}cvor;

struct Queue;
typedef struct Queue* positionQ;
typedef struct Queue{
    Position leaf;
    positionQ next;
}queue;

int Push(positionQ, Position);
int Pop(positionQ);
Position Insert(Position, Position );
Position CreateElement();
int InOrderPrint(Position);
int PreOrderPrint(Position);
int PostOrderPrint(Position);
int LevelOrderPrint(Position);
int FreeTree(Position);

int main(){
    Position root = NULL;
    Position extra = NULL;
    int odabir = 0, provjera = 0;
    while(1){
        printf("1. Insert"
                "2. Inorder print\n"
                "3. Preorder print\n"
                "4. Postorder print\n"
                //"5. Levelorder print\n"
                "6. Exit\n"
                "Input command number: ");
        scanf(" %d", &odabir);

        switch(odabir){
            case 1: 
                extra = CreateElement();
                if(extra == NULL){
                    return -1;
                }
                root = Insert(root, extra);
                break;
            case 2:
                InOrderPrint(root);
                break;
            case 3:
                PreOrderPrint(root);
                break;
            case 4:
                PostOrderPrint(root);
                break;
            /*case 5:
                provjera = LevelOrderPrint(root);
                if(provjera < 0)
                    return 0;
                break;                                  */
            case 6:
                FreeTree(root);
                return 0;          
            default:
                printf("Wrong input!");
        }
    }

    return 0;
}

int Push(positionQ head, Position current){
    positionQ temp = head;
    positionQ newEl = NULL;

    newEl = (positionQ)malloc(sizeof(queue));
    if(newEl == NULL){
        return -1;
    }
    while(temp -> next){
        temp = temp -> next;
    }

    newEl -> next = temp -> next;
    temp -> next = newEl;

    newEl -> leaf = current;

    return 0;
}

int Pop(positionQ head){
    positionQ temp = NULL;
    if(head -> next != NULL){
        temp = head -> next;
        head -> next = temp -> next;
        free(temp);
    }
    return 0;
}

Position Insert(Position current, Position newEl){
    if(current == NULL){
        current = newEl;
    }
    else if(current -> num < newEl -> num){
        current -> right = Insert(current -> right, newEl);
    }
    else if(current -> num > newEl -> num){
        current -> left = Insert(current -> left, newEl);
    }
    else{
        printf("New element is a duplicate!");
        free(newEl);
    }
    return current;
}


Position CreateElement(){
    Position newEl = NULL;
    int number = 0;

    printf("Input new element number:\t");
    scanf(" %d", &number);

    newEl = (Position)malloc(sizeof(cvor));
    if(newEl == NULL){
        printf("Cannot allocate memory!");
        return NULL;
    }

    newEl -> num = number;
    newEl -> left = NULL;
    newEl -> right = NULL;

    return newEl;
}


int InOrderPrint(Position root){
    if(root != NULL){
        if(root -> left != NULL){
            InOrderPrint(root -> left);
        }

        printf(" %d", root -> num);

        if(root -> right != NULL){
            InOrderPrint(root -> right);
        }
    }
    else{
        printf("The tree is empty!");
    }
    return 0;
}

int PreOrderPrint(Position root){
    if(root != NULL){
        printf(" %d", root -> num);
        if(root -> left != NULL){
            PreOrderPrint(root -> left);
        }
        if(root -> right != NULL){
            PreOrderPrint(root -> right);
        }
    }
    else{
        printf("The tree is empty!");
    }
    return 0;
}

int PostOrderPrint(Position root){
    if(root != NULL){
        if(root -> left != NULL){
            PostOrderPrint(root -> left);
        }
        if(root -> right != NULL){
            PostOrderPrint(root -> right);
        }
        printf(" %d", root -> num);
    }
    else{
        printf("The tree is empty!");
    }
    return 0;
}

int FreeTree(Position root){
    if(root != NULL){
        if(root -> left != NULL){
            FreeTree(root -> left);
        }

        if(root -> right != NULL){
            FreeTree(root -> right);
        }
        free(root);
    }

    return 0;
}