#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char letter;
    struct node *next;
} node;

void createQueue (node **front, node **last);
void addNodeToQueue (node **front, node **last, char value);
void removeNodeQueue (node **front, node **last);
int isEmpty (node *front, node *last);
void printNodes (node *last);

void strToQueue (node **front, node **last, char *word);

void isPalindrome (node **head, node **last, node **front);

void createStack (node **head);
void strToStack (node **head, char *phrase);
void push (node **head, char addLetter);

void pop (node **head);

int main (void)
{
    // Fila
    node *head;
    // Cola
    node *last, *front;

    char word[50];
    
    printf("Ingrese la palabra\n");
    scanf(" %s", word);

    createStack(&head);
    createQueue(&last, &front);

    strToStack(&head, word);
    strToQueue(&front, &last, word);
    
    printNodes(head);
    printNodes(last);
    printf("\tUltimo: %c, Primero: %c\n", last -> letter, front -> letter);

    isPalindrome(&head, &last, &front);

    return 0;
}

void createQueue (node **front, node **last)
{
    *front = NULL;
    *last = NULL;
}

void addNodeToQueue (node **front, node **last, char value)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> letter = value;
    newNode -> next = *last;

    if (isEmpty(*front, *last))
    {
        *front = *last = newNode;
    }
    else
    {
        *last = newNode;
    }
}

void removeNodeQueue (node **front, node **last)
{
    if (isEmpty(*front, *last))
    {
        printf("Cola vacia\n");
        return;
    }

    if (*front != *last)
    {
        node *current = *last;

        while (current -> next -> next != NULL)
        {
            current = current -> next;
        }

        //printf("Current: %d\n", current -> letter);

        current -> next = NULL;
        free(*front);
        *front = current;
        return;
    }

    if (*front == *last)
    {
        free(*front);
        *front = *last = NULL;
    }
    
}

int isEmpty (node *front, node *last)
{
    if (front == NULL || last == NULL)
    {
        return 1;
    }
    return 0;
}

void printNodes (node *last)
{
    node *current = last;
    
    printf("\n");
    while (current != NULL)
    {
        printf("%5c -> ", current->letter);
        current = current->next;
    }
    printf("   NULL\n");
}

void strToQueue (node **front, node **last, char *word)
{
    int i = 0;
    while (*(word+i) != '\0')
    {
        addNodeToQueue(front, last, word[i]);
        //printf("%d", i);
        i++;
    }
}

void isPalindrome (node **head, node **last, node **front)
{
    while (*head != NULL && (*head)->letter == (*front)->letter)
    {
        removeNodeQueue(front, last);
        pop(head);
    }

    if (*head == NULL)
    {
        printf("\nEs palindromo\n");
    }
    else
    {
        printf("\nNo es palindromo\n");
        printNodes(*head);
        printNodes(*last);
        printf("\tUltimo: %c, Primero: %c\n", (*last) -> letter, (*front) -> letter);
    }
}

///////////////////////////////////////
/////////////    STACK     ////////////
///////////////////////////////////////

void pop (node **head)
{
    node *current = *head;
    
    if (current == NULL)
    {
        printf("Pila vacia\n");
        return;
    }

    *head = current->next;
    current->next = NULL;
    
    free(current);
}

void createStack (node **head)
{
    *head = NULL;
}

void push (node **head, char addLetter)
{
    node *newNode = (node *)malloc(sizeof(node));
    
    newNode->letter = addLetter;
    newNode->next = *head;
    
    *head = newNode;
}

void strToStack (node **head, char *phrase)
{
    int i = 0;
    while (*(phrase+i) != '\0')
    {
        push(head, phrase[i]);
        //printf("%d", i);
        i++;
    }
}