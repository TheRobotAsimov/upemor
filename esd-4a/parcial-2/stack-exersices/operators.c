#include <stdio.h>
#include <stdlib.h>

// ([(A+B)*(C+D)])

typedef struct node
{
    char letter;
    struct node *next;
} node;

void strToStack (node **head, char *phrase);
void push (node **head, char letter);
void pop (node **head);
void empty (node **head);
void printNode (node *head);
void reverseNode (node *head, node **headReverse);
void isPalindrome (node *head, node *headReverse);

int main()
{
    char phrase[50];
    
    printf("Ingrese la operacion\n");
    scanf(" %s", phrase);
    
    node *head = NULL;
    
    strToStack(&head, phrase);
    printNode(head);

    if(head == NULL)
        printf("Operacion correcta\n");
    else
        printf("Operacion incorrecta\n");

    return 0;
}

void strToStack (node **head, char *phrase)
{
    int i = 0;
    while (*(phrase+i) != '\0')
    {
        if (phrase[i] == '[' || phrase[i] == '(')
            push(head, phrase[i]);
        else if (phrase[i] == ')' && (*head)->letter == '(' || phrase[i] == ']' && (*head)->letter == '[')
            pop(head);
        //printf("%d", i);
        i++;
    }
}

void push (node **head, char addLetter)
{
    node *newNode = (node *)malloc(sizeof(node));
    
    newNode->letter = addLetter;
    newNode->next = *head;
    
    *head = newNode;
}

void pop (node **head)
{
    node *current = *head;
    
    *head = current->next;
    current->next = NULL;
    
    free(current);
}

void empty (node **head)
{
    while(*head != NULL)
    {
        pop(head);
    }
}

void printNode (node *head)
{
    node *current = head;
    
    while (current != NULL)
    {
        printf("%c", current->letter);   
        current = current->next;
    }
    printf("\n");
}

void reverseNode (node *head, node **headReverse)
{
    node *current = head;
    
    while(current != NULL)
    {
        push(headReverse, current->letter);
        current = current->next;
    }
}

void isPalindrome (node *head, node *headReverse)
{
    node *current = head;
    node *currentR = headReverse;
    
    while (current != NULL && currentR != NULL && current->letter == currentR->letter)
    {
        current = current->next;
        currentR = currentR->next;
    }
    
    if(current == NULL && currentR == NULL)
    {
        printf("Es palindromo\n");
    }
    else
    {
        printf("No es palindromo\n");
    }
}