/* 
The elements to build up a linked list are:
- Struct (Value and pointer)
- Initial pointer (head) and traverse pointer (current)
Actions:
- Add
- Remove
- Tranverse
 */

#include <stdio.h>
#include <stdlib.h>

// typedef for creating a new kind of data. It's more readable
typedef struct node
{
    int num;
    // As always, pointer goes before the variable, not before the kind of data
    struct node *next;
} node;

node *addAtBeggining (node *head, int value);
void printNodeNum (node *head);

node *rmNode (node *head, int value);
void addAtEnd (node *head, int value);
node *invert (node *head);
void freeNode (node *head);

int main (void)
{
    // head is NOT a node. It just points node's ubications
    node *head = NULL;

    head = addAtBeggining(head, 1);
    head = addAtBeggining(head, 2);
    head = addAtBeggining(head, 3);
    head = addAtBeggining(head, 4);
    head = addAtBeggining(head, 5);

    printNodeNum(head);
    
    printf("\n-------------\n");
    
    head = rmNode(head, 3);
    printf("\n");
    printNodeNum(head);
    
    printf("\n");
    addAtEnd(head, 0);
    addAtEnd(head, -1);
    addAtEnd(head, -2);
    head = addAtBeggining(head, 6); 
    printNodeNum(head);
    
    printf("\n");
    head = invert(head);
    printNodeNum(head);

    freeNode(head);
    
}


node *addAtBeggining (node *head, int value)
{
    // This IS a node, so we gotta set apart memory
    node *newNode = (node*)malloc(sizeof(node));
    newNode -> num = value;
    newNode -> next = head;
    return newNode;
}

void printNodeNum (node *head)
{
    node *current = head;

    while (current != NULL)
    {
        printf("%d\n", current -> num);
        current = current -> next;
    }
    printf("NULL\n");
}

node *rmNode (node *head, int value)
{
    node *current = head;
    node *previous;
    
    while (current != NULL && current -> num != value)
    {
        //printf("%d\n", current -> num);
        previous = current;
        current = current -> next;
    }
    
    if (current == NULL)
    {
        printf("No se encontro el valor\n");
        return head;
    }
    
    if (current -> num == value)
    {
        node *following = current -> next;
        
        if (current == head)
        {
            printf("Dato al inicio\n");
            free(current);
            return following;
        }
        
        if (current -> next == NULL)
        {
            printf("Dato al final\n");
            free(current);
            previous -> next = following;
            return head;
        }
        
        printf("Dato en medio\n");
        free(current);
        previous -> next = following;
        return head;
        
    }
}

void addAtEnd (node *head, int value)
{
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Problemas con la memoria");
        return;
    }
    newNode -> num = value;
    newNode -> next = NULL;
    
    node *current = head;
    node *previous;
    while (current != NULL)
    {
        previous = current;
        current = current -> next;
    }
    
    previous -> next = newNode;
    return;
}

node *invert (node *head)
{
    node *current = head;
    node *after = current -> next;
    node *previous;
    
    current -> next = NULL;
    
    while (current != NULL)
    {
        // next node
        previous = current;
        current = after;
        if (current != NULL)
        {
            after = current -> next;
            // change next
            current -> next = previous;
        }
    }
    
    return previous;
    
}

void freeNode (node *head)
{
    node *current = head;
    node *after = current -> next;

    while (current != NULL)
    {
        free(current);
        current = after;
        if (current != NULL)
            after = current -> next;
    }
    return;
}