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

node *listMiddle (node *start, node *last)
{
    node *fast;
    node *slow;

    slow = start;
    fast = start -> next;

    while (fast != last)
    {
        fast = fast -> next;

        if (fast != last)
        {
            slow = slow -> next;
            fast = fast -> next;
        }
    }

    return slow;
}

node *binarySearch (node *head, int searching)
{
    node *start = head;
    node *last = NULL;

    do
    {
        node *middle = listMiddle(start, last);

        if (middle == NULL)
            return NULL;
        if (middle -> value == searching)
            return middle;
        else if (middle -> value < searching)
            start = middle -> next;
        else
            last = middle;

    } while (last == NULL || last != start);
    
    return NULL;
}

int main (void)
{
    srand(time(NULL));

    node *head = NULL;
    int searching;

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

    printf("Type the number you're looking for: ");
    scanf("%d", &searching);
    if (binarySearch(head, searching) == NULL)
        printf("Value not present\n");
    else
        printf("Value present\n");

    return 0;
}