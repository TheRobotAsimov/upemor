#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void insert_start (node **head, node **tail, int value);
void insert_end (node **head, node **tail, int value);
void printList (node *head, node *tail, int times);
node *search_node (node *head, int value);
void remove_node (node **head, node **tail, int value);

int main (void)
{
    node *head = NULL, *tail = NULL;

    int option, value;

    do
    {
        printf("\n\tMENU\n");
        printf("1. Agregar al inicio\n");
        printf("2. Agregar al final\n");
        printf("3. Borrar dato\n");
        printf("4. Imprimir x veces\n");
        printf("0. Salir\n\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &option);
        printf("\n");

        switch (option)
        {
        case 1:
            printf("Ingresar dato: ");
            scanf("%d", &value);
            insert_start(&head, &tail, value);
            printList(head, tail, 1);
            break;
        case 2:
            printf("Ingresar dato: ");
            scanf("%d", &value);
            insert_end(&head, &tail, value);
            printList(head, tail, 1);
            break;
        case 3:
            printf("Ingresar dato: ");
            scanf("%d", &value);
            remove_node(&head, &tail, value);
            printList(head, tail, 1);
            break;
        case 4:
            printf("Veces que se repitan: ");
            scanf("%d", &value);
            printList(head, tail, value);
        case 0:
            printf("Saliendo...\n\n");
            break;
        default:
            break;
        }
    } while (option != 0);
    
}

void insert_start (node **head, node **tail, int value)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> data = value;

    if(*head == NULL)
    {
        newNode -> next = newNode;
        *tail = newNode;
    }
    else
    {
        newNode -> next = *head;
        (*tail) -> next = newNode;
    }

    *head = newNode;
}

void insert_end (node **head, node **tail, int value)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> data = value;

    if(*head == NULL)
    {
        newNode -> next = newNode;
        *head = newNode;
    }
    else
    {
        newNode -> next = *head;
        (*tail) -> next = newNode;
    }

    *tail = newNode;
}

void printList (node *head, node *tail, int times)
{
    if (head == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    node *current = head;
    printf("\nLista:\n\n");

    printf("... ->");
    for (int i = 0; i < times; i++)
    {
        do
        {
            printf("%5d ->", current -> data);
            current = current -> next;
        } while (current != head);
        printf("_");
    }
    printf("  ...");
    

    printf("\n\nPrimer elemento: %d\n", head -> data);
    printf("Ultimo elemento: %d\n\n", tail -> data);
}

node *search_node (node *head, int value)
{
    node *current = head;

    do
    {
        current = current -> next;
    } while (current != head && value != current -> data);
    
    if (value == current -> data)
    {
        printf("\n%5d\n", current -> data);
        return current;
    }
    else
    {
        printf("\nNo se encontro\n");
        return NULL;
    }
}

void remove_node (node **head, node **tail, int value)
{
    node *current = search_node(*head, value);

    if (current == NULL)
    {
        return;
    }

    // Buscar el nodo anterior
    node *previous = *head;

    while (previous -> next != current)
    {
        previous = previous -> next;
    }

    // Si es el primer nodo
    if (current == *head)
    {
        // Si tiene más de un elemento
        if (current -> next != current)
        {
            *head = (*tail) -> next = current -> next;
        }
        else
        {
            *head = *tail = NULL;
        }
    } // Si es el último nodo
    else if (current == *tail)
    {
        previous -> next = *head;
        *tail = previous;
    } // Si está en medio
    else
    {
        previous -> next = current -> next;
    }

    current -> next = NULL;
    free(current);
}