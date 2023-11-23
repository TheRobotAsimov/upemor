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
void sumLists (node *first1, node *last1, node *first2, node *last2, node **first3, node **last3);
void insertAtBegining (node **first, node **last, int valueN);
void printSum (node *first, node *last);

int main (void)
{
    srand(time(NULL));

    node *first1, *first2, *first3;
    node *last1, *last2, *last3;
    int num1 = 0, num2 = 0, digits1 = 0, digits2 = 0;

    createList(&first1, &last1);
    createList(&first2, &last2);
    createList(&first3, &last3);

    printf("\nIngrese el primer numero:\n");
    while(num1 >= 0)
    {
        scanf("%d", &num1);
        if (num1 >= 0)
        {
            insertAtBegining(&first1, &last1, num1);
            digits1++;
            //printList(first1, last1);
        }
    }
    printf("\nPrimer numero en lista enlazada:\n");
    printList(first1, last1);

    printf("Ingrese el segundo numero:\n");
    while(num2 >= 0)
    {
        scanf("%d", &num2);
        if (num2 >= 0)
        {
            insertAtBegining(&first2, &last2, num2);
            digits2++;
            //printList(first2, last2);
        }
    }
    printf("\nSegundo numero en lista enlazada:\n");
    printList(first2, last2);

    if (digits1 > digits2)
    {
        for (int i = 0; i < digits1 - digits2; i++)
        {
            insert(&first2, &last2, 0);
        }
        printf("\nSegundo numero con 0's en lista enlazada:\n");
        printList(first2, last2);
    }
    else if (digits2 > digits1)
    {
        for (int i = 0; i < digits2 - digits1; i++)
        {
            insert(&first1, &last1, 0);
        }
        printf("\nPrimer numero con 0's en lista enlazada:\n");
        printList(first1, last1);
        
    }


    sumLists(first1, last1, first2, last2, &first3, &last3);
    printf("\nSuma de los numeros en lista enlazada:\n");
    printSum(first3, last3);

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

void insertAtBegining (node **first, node **last, int valueN)
{
    node *newNode = malloc(sizeof(node));

    if (newNode != NULL)
    {
        newNode -> value = valueN;
        newNode -> next = *first;
        *first = newNode;

        if (*last == NULL)
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

void sumLists (node *first1, node *last1, node *first2, node *last2, node **first3, node **last3)
{
    node *current1 = first1;
    node *current2 = first2;

    int sum, carry = 0;

    while (current1 != NULL || carry != 0)
    {
        if (current1 != NULL)
        {
            sum = current1 -> value + current2 -> value + carry;
            if (sum <= 9)
            {
                insertAtBegining(first3, last3, sum);
                carry = 0;
            }
            else
            {
                insertAtBegining(first3, last3, sum%10);
                carry = 1;
            }

            current1 = current1 -> next;
            current2 = current2 -> next;
        }
        else if (current1 == NULL && carry != 0)
        {
            insertAtBegining(first3, last3, carry);
            break;
        }
    }
    
}

void printSum (node *first, node *last)
{
    if (first == NULL)
    {
        printf("La lista esta vacia\n");
        return;
    }

    node *current = first;

    while (current != NULL)
    {
        printf("%d", current -> value);
        current = current -> next;
    }
    printf("\n");
}