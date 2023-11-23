#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

void createList (node **first, node **last);
void insert (node **first, node **last, int valueN);
void printList (node *first);
void removeNode (node **first, node **last, int valueN);

int main (void)
{
    srand(time(NULL));

    node *first;
    node *last;

    createList(&first, &last);

    for (int i=0; i<10; i++)
    {
        insert(&first, &last, rand()%100+1);
        //printf("first: %5d, last: %5d\n", first -> value, last -> value);
        printList(first);
    }

    int search;

    printf("Eliminar: ");
    scanf("%d", &search);

    removeNode(&first, &last, search);
    printList(first);

    return 0;
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
            *first = *last = newNode;
        else
        {
            //(*last) -> next = newNode;
            node *current = *first;
            node *previous = NULL;
            
            while (current != NULL && current -> value < valueN)
            {
                previous = current;
                current = current -> next;
            }

            if (previous == NULL)
            {
                newNode -> next = *first;
                *first = newNode;
            }
            else
            {
                previous -> next = newNode;
                newNode -> next = current;
                if (current == NULL)
                {
                    *last = newNode;
                }
            }
        }

        //*last = newNode;

    }   
    else
        printf("No se pudo insertar el valor %d. No hay memoria disponible\n", valueN);
}

void printList (node *first)
{
    if (first == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    node *current = first;

    while (current != NULL)
    {
        printf("%5d ->", current -> value);
        current = current -> next;
    }
    printf("  NULL\n");
}

void removeNode (node **first, node **last, int valueN)
{
    node *current = *first;
    node *previous = NULL;
    node *aux;

    // Busca el número a borrar
    while (current != NULL && current -> value != valueN)
    {
        if (current -> value == valueN)
            break;
            
        previous = current;
        current = current -> next;
    }

    if (current == NULL)
        return;

    // Si es el primer elemento
    if (previous == NULL)
    {
        aux = *first;
        *first = (*first) -> next;

        aux -> next = NULL;
        free(aux);
    }
    else
    {
        // Si no es el último
        if (current != *last)
        {
            aux = current -> next;
            previous -> next = aux;

            current -> next = NULL;
            free(current);
        } 
        // Si es el último
        else
        {
            previous -> next = NULL;
            aux = *last;
            free(aux);

            *last = previous;
        }
    }
}