#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void create_stack (node **head);
void push (node **head, int value);
void pop (node **head);
void empty (node **head);

void printStack (node *head);

void splitEvenOdd (node **head, node **head1, node **head2);

int main()
{
    srand(time(NULL));

    node *head;
    // int items = 0;
    int size;

    /// CREATE STACK ///
    
    create_stack(&head);

    printf("Ingrese la cantidad de elementos de la pila: ");
    scanf("%d", &size);
    
    printf("\nNumero: \t");
    for(int i=1; i<=size; i++)
    {
        push(&head, rand()%20+1);
        printf("%5d    ", i);
    }
    printf("\n");

    for(int i=1; i<=size*12; i++)
        printf("-");
    printf("\n");
    
    printf("Pila: \t\t");
    printStack(head);
    
    /// SPLIT STACK INTO EVEN STACK AND ODD STACK ///

    node *headEven, *headOdd;
    
    create_stack(&headEven);
    create_stack(&headOdd);
    
    splitEvenOdd(&head, &headEven, &headOdd);
    
    printf("Pila Par: \t");
    printStack(headEven);
    //empty(&headOdd);
    printf("Pila Impar: \t");
    printStack(headOdd);
    
    /// ORIGINAL STACK IS EMPTY ///

    printf("Pila: \t\t");
    printStack(head);

    //pop(&head);
    
    return 0;
}

void create_stack (node **head)
{
    *head = NULL;
}

void push (node **head, int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    
    newNode->data = value;
    newNode->next = *head;
    
    *head = newNode;
}

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

void printStack (node *head)
{
    node *current = head;
    
    while (current != NULL)
    {
        printf("%5d -> ", current->data);
        current = current->next;
    }
    printf("   NULL\n");
}

void splitEvenOdd (node **head, node **headEven, node **headOdd)
{
    node *current = *head;
    
    while (current != NULL)
    {
        if(current->data % 2 == 0)
            push(headEven, current->data);
        else
            push(headOdd, current->data);
        
        current = current->next;
        pop(head);
    }
}

void empty (node **head)
{
    while(*head != NULL)
    {
        pop(head);
    }
}
