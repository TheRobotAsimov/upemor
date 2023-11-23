#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    char value;
    struct node *next;
    struct node *previous;
}node;

void create_list (node **first, node **last);
void insert_beggining (node **first, node **last, char valueN);
void print_list (node *last);
void next_previous (node *first, node *last, char valueN);
void remove_node (node **first, node **last, char valueN);
void is_palindrome (node *first, node *last);
void string_to_dll (node **first, node **last, char *word);

int main (void)
{
    srand(time(NULL));

    node *first;
    node *last;
    char word[50];

    create_list(&first, &last);

    printf("Ingrese la palabra:\n");
    scanf(" %s", word);

    string_to_dll(&first, &last, word);

    print_list(last);

    is_palindrome(first, last);

    return 0;
}

void create_list (node **first, node **last)
{
    *first = NULL;
    *last = NULL;
}

void insert_beggining (node **first, node **last, char valueN)
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

void print_list (node *last)
{
    node *current = last;

    printf("\nNULL ");

    while (current != NULL)
    {
        printf(" <- %c -> ", current -> value);
        current = current -> previous;
    }

    printf(" NULL\n\n");
    
}

void next_previous (node *first, node *last, char valueN)
{
    node *current = first;

    while (current != NULL && current -> value != valueN)
    {
        current = current -> next;
    }
    
    if (current == NULL)
        return;

    if (current == first)
    {
        printf("Next: %c\n", current -> next -> value);
        printf("Previous: NULL\n");
    }
    else if (current == last)
    {
        printf("Next: NULL\n");
        printf("Previous: %c\n", current -> previous -> value);
    }
    else
    {
        printf("Next: %c\n", current -> next -> value);
        printf("Previous: %c\n", current -> previous -> value);
    }
}

void remove_node (node **first, node **last, char valueN)
{
    return;
}

void string_to_dll (node **first, node **last, char *word)
{
    int i = 0;
    while (*(word+i) != '\0')
    {
        insert_beggining(first, last, word[i]);
        i++;
    }
}

void is_palindrome (node *first, node *last)
{
    node *start = first, *end = last;
    while (start != NULL && start != end && start -> value == end -> value)
    {
        start = start -> next;
        end = end -> previous;
    }

    if (start == NULL || start == end)
        printf("Es palindromo\n");
    else
        printf("No es palindromo\n");
    
}