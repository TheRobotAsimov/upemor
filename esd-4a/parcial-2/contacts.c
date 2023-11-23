#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    char name[50];
    char number[15];
    struct node *next;
} node;

void createList (node **first, node **last);
void insert (node **first, node **last, char nameN[], char numberN[]);
void printList (node *first);
void removeNode (node **first, node **last, char nameN[]);

int main (void)
{
    node *first;
    node *last;

    createList(&first, &last);

    insert(&first, &last, "Juan", "777");
    insert(&first, &last, "Lucas", "654");
    insert(&first, &last, "Alan", "123");
    printList(first);

    printf("\n-----------------------------------\n");

    char nameSearch[50];
    printf("Ingrese el nombre: ");
    scanf(" %[^\n]", nameSearch);
    removeNode(&first, &last, nameSearch);
    printList(first);

    return 0;
}

void createList (node **first, node **last)
{
    *first = NULL;
    *last = NULL;
}

void insert (node **first, node **last, char nameN[], char numberN[])
{
    node *newNode = malloc(sizeof(node));

    if (newNode != NULL)
    {
        //newNode -> name = nameN;
        strcpy(newNode -> name, nameN);
        //newNode -> number = numberN;
        strcpy(newNode -> number, numberN);
        newNode -> next = NULL;

        if (*first == NULL)
            *first = *last = newNode;
        else
        {
            //(*last) -> next = newNode;
            node *current = *first;
            node *previous = NULL;
            
            while (current != NULL && strcmp(current -> name, nameN) < 0)
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
        printf("No se pudo insertar el contacto. No hay memoria disponible\n");
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
        printf("\nNombre: %s\n", current -> name);
        printf("Numero: %s\n\n", current -> number);
        printf("    |\n");
        printf("    v\n");
        current = current -> next;
    }
    printf("\n  NULL\n");
}

void removeNode (node **first, node **last, char nameN[])
{
    node *current = *first;
    node *previous = NULL;
    node *aux;

    // Busca el número a borrar
    while (current != NULL && strcmpi(current -> name, nameN) != 0)
    {
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