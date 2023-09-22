#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

void insert (node **head)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> value = rand()%100+1;
    newNode -> next = *head;

    *head = newNode;
}

void printList (node *head)
{
    node *current = head;

    while (current != NULL)
    {
        printf("%5d", current -> value);
        current = current -> next;
    }
    printf("\n");
}

void FrontBackSplit (node *head, node **front, node **back)
{
    node *slow;
    node *fast;

    slow = head;
    fast = head -> next;

    while (fast != NULL)
    {
        fast = fast -> next;

        if (fast != NULL)
        {
            slow = slow -> next;
            fast = fast -> next;
        }
    }

    *front = head;
    *back = slow -> next;
    slow -> next = NULL;
}

node *merge (node *a, node *b)
{
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    node *result = NULL;

    if (a -> value <= b -> value)
    {
        result = a;
        result -> next = merge(a -> next, b);
    }
    else
    {
        result = b;
        result -> next = merge(a, b -> next);
    }
    
    return result;
}

void mergeSort (node **head)
{
    if (*head == NULL || (*head) -> next == NULL)
        return;
    
    node *a;
    node *b;

    FrontBackSplit(*head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *head = merge(a, b);
}

int main (void)
{
    srand(time(NULL));

    node *head = NULL;

    insert(&head);
    insert(&head);
    insert(&head);
    insert(&head);
    insert(&head);
    insert(&head);
    insert(&head);

    printList(head);

    mergeSort(&head);

    printList(head);

    return 0;
}