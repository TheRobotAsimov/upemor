/* 
The elements to build up a linked list are:
- Auto referencial struct (Value and pointer)
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

int main (void)
{
    // head is NOT a node. It just points node's ubications
    node *head = NULL;

    head = addAtBeggining(head, 1);
    head = addAtBeggining(head, 2);
    head = addAtBeggining(head, 3);

    printNodeNum(head);
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