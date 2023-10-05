#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void createQueue (node **front, node **last);
void addNode (node **front, node **last, int value);
void removeNode (node **front, node **last);
int isEmpty (node *front, node *last);
void printQueue (node *last);


int main (void)
{
    srand(time(NULL));

    node *front, *last;
    int size;

    createQueue(&front, &last);

    printf("Ingrese la cantidad de elementos de la cola: ");
    scanf("%d", &size);
    
    for(int i=1; i<=size; i++)
        addNode(&front, &last, rand()%20+1);

    printQueue(last);

    printf("Primero: %d, Ultimo: %d\n", front -> data, last -> data);

    removeNode(&front, &last);

    printQueue(last);

    return 0;
}

void createQueue (node **front, node **last)
{
    *front = NULL;
    *last = NULL;
}

void addNode (node **front, node **last, int value)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> data = value;
    newNode -> next = *last;

    if (*front == NULL && *last == NULL)
    {
        *front = *last = newNode;
    }
    else
    {
        *last = newNode;
    }
}

void removeNode (node **front, node **last)
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

        //printf("Current: %d\n", current -> data);

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

void printQueue (node *last)
{
    node *current = last;
    
    while (current != NULL)
    {
        printf("%5d -> ", current->data);
        current = current->next;
    }
    printf("   NULL\n");
}