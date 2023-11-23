#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int value;
    struct node *next;
    struct node *previous;
}node;

void create_list (node **first, node **last);
void insert_start (node **first, node **last, int valueN);
void insert_end (node **first, node **last, int valueN);
void print_list (node *first);
void next_previous (node *first, node *last, node *current);
void remove_node (node **first, node **last, int valueN);
node *search_node (node *first, node *last, int valueN);

int main (void)
{
    srand(time(NULL));

    node *first;
    node *last;
    int value;

    create_list(&first, &last);

    for (int i = 0; i < 10; i++)
    {
        value = rand()%100+1;
        if (value%2 == 0)
            insert_start(&first, &last, value);
        else
            insert_end(&first, &last, value);
    }
        

    print_list(first);

    int search;

    printf("Eliminar: ");
    scanf("%d", &search);

    remove_node(&first, &last, search);

    print_list(first);

    return 0;
}

void create_list (node **first, node **last)
{
    *first = NULL;
    *last = NULL;
}

void insert_start (node **first, node **last, int valueN)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> value = valueN;
    newNode -> next = NULL;
    newNode -> previous = NULL;

    if (*first == NULL)
    {
        *first = *last = newNode;
    }
    else
    {
        newNode -> next = *first;
        (*first) -> previous = newNode;
        *first = newNode;
    }
}

void insert_end (node **first, node **last, int valueN)
{
    node *newNode = (node *)malloc(sizeof(node));

    newNode -> value = valueN;
    newNode -> next = NULL;
    newNode -> previous = NULL;

    if (*first == NULL)
    {
        *first = *last = newNode;
    }
    else
    {
        newNode -> previous = *last;
        (*last) -> next = newNode;
        *last = newNode;
    }
}

void print_list (node *first)
{
    node *current = first;

    printf("NULL ");

    while (current != NULL)
    {
        printf(" <- %d -> ", current -> value);
        current = current -> next;
    }

    printf(" NULL\n");
    
}

void next_previous (node *first, node *last, node *current)
{
    if (current == NULL)
        return;

    if (current == first)
    {
        printf("Next: %d\n", current -> next -> value);
        printf("Previous: NULL\n");
    }
    else if (current == last)
    {
        printf("Next: NULL\n");
        printf("Previous: %d\n", current -> previous -> value);
    }
    else
    {
        printf("Next: %d\n", current -> next -> value);
        printf("Previous: %d\n", current -> previous -> value);
    }
}

node *search_node (node *first, node *last, int valueN)
{
    node *current = first;

    while (current != NULL && current -> value != valueN)
    {
        current = current -> next;
    }

    if (current == NULL)
    {
        return NULL;
    }
    else
    {
        next_previous(first, last, current);
        return current;
    }
}

void remove_node (node **first, node **last, int valueN)
{
    node *current = search_node(*first, *last, valueN);

    if (current == NULL)
        return;


    if (current == *first)
    {
        *first = current -> next;
        (*first) -> previous = NULL;
        current -> next = NULL;

        free(current);
    }
    else if (current == *last)
    {
        *last = current -> previous;
        (*last) -> next = NULL;
        current -> previous = NULL;

        free(current);
    }
    else
    {
        node *before = current -> previous, *after = current -> next;

        before -> next = after;
        after -> previous = before;

        current -> next = NULL;
        current -> previous = NULL;
        free(current);
    }
}