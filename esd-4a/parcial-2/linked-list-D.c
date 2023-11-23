#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

void createList (node **first, node **last);
void insert (node **first, node **last, int value);
void printList (node *first, node *last);
void printPair (node *first, node *last);

int main (void)
{
    srand(time(NULL));

    node *first;
    node *last;

    createList(&first, &last);

    for (int i=0; i<10; i++)
    {
        insert(&first, &last, rand()%100+1);
        printList(first, last);
    }

    printPair(first, last);

}

void createList (node **first, node **last)
{
    *first = NULL;
    *last = NULL;
}

void insert (node **first, node **last, int valueN)
{
    node *newNode = malloc(sizeof(node));

    if (newNode != NULL)
    {
        newNode -> value = valueN;
        newNode -> next = NULL;

        if (*first == NULL)
            *first = newNode;
        else
            (*last) -> next = newNode;

        *last = newNode;

    }   
    else
        printf("No se pudo insertar el valor %d. No hay memoria disponible\n", valueN);
}

void printList (node *first, node *last)
{
    if (first == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    node *current = first;
    printf("Lista:");

    while (current != NULL)
    {
        printf("%5d ->", current -> value);
        current = current -> next;
    }
    printf("  NULL\n");

    printf("Primer elemento: %d\n", first -> value);
    printf("Ultimo elemento: %d\n\n", last -> value);
}

void printPair (node *first, node *last)
{
    if (first == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    node *current = first;

    printf("Pares:");

    while (current != NULL)
    {
        if (current -> value % 2 == 0)
            printf("%5d ->", current -> value);
        current = current -> next;
    }
    printf("  NULL\n");
}