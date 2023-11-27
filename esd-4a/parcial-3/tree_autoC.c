#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    char data[50];
    struct node *left;
    struct node *right;
} node;

void create_tree (node **root);
node *insert (char *data);
void insert2 (node **root, char *data);
void print_tree (node *tree, int space);

// Traversals
/* 
    Preorder:
    - Node
    - Left
    - Right

    Inorder:
    - Left
    - Node
    - Right

    Postorder:
    - Left
    - Right
    - Node

 */

void preorder (node *tree, int space);
void inorder (node *tree, int space);

int main (void)
{
    node *root;

    create_tree (&root);

    /* root = insert (5);
    root -> left = insert (10);
    root -> right = insert (20);
    root -> left -> left = insert (30);
    root -> left -> right = insert (40);
    root -> right -> left = insert (50);
    root -> right -> right = insert (60); */

    int times;
    char data[50];

    printf("Ingrese la cantidad de nodos: ");
    scanf("%d", &times);

    for (int i = 0; i < times; i++)
    {
        printf("Ingrese el dato: ");
        scanf(" %[^\n]", data);
        insert2(&root, data);
    }

    printf("\n");

    print_tree(root, 0);

    printf("\n---------------------------------\n\n");

    printf("PREORDEN:\n\n ");
    preorder(root, 0);

    printf("\n---------------------------------\n\n");

    printf("INORDEN:\n\n ");
    inorder(root, 0);
}

void create_tree (node **root)
{
    *root = NULL;
}

node *insert (char *data)
{
    node *new_node = (node *) malloc (sizeof (node));
    //new_node->data = data;
    strcpy(new_node -> data, data);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void print_tree (node *tree, int space)
{
    if (tree != NULL)
    {
        print_tree (tree -> right, space + 1);
        for (int i = 0; i < space; i++)
        {
            printf("\t");
        }
        printf ("%s\n", tree -> data);
        print_tree (tree -> left, space + 1);
    }
}

void insert2 (node **root, char *data)
{
    // aux is equal to current and aux2 is equal to previous
    //node *aux, *aux2;
    char phrase[50];
    //int option;

    if (*root == NULL)
    {
        *root = insert (data);
    }
    else
    {
        //aux = *root;
        //number = (*root) -> data;
        strcpy(phrase, (*root) -> data);

        if (strcmp(phrase, data) < 0)
        {
            insert2 (&(*root) -> left, data);
        }
        else
        {
            insert2 (&(*root) -> right, data);
        }
    }

    //printf("\n Nodo creado\n\n");
}

void preorder (node *tree, int space)
{
    // Very important the conditional
    if (tree)
    {
        for (int i = 0; i < space; i++)
        {
            printf("\t");
        }
        printf("%s\n", tree -> data);
        preorder (tree -> left, ++space);
        preorder (tree -> right, space);
    }
}

void inorder (node *tree, int space)
{
    if (tree)
    {
        inorder(tree -> left, space + 1);
        for (int i = 0; i < space; i++)
        {
            printf("\t");
        }
        printf("%s\n", tree -> data);
        inorder(tree -> right, space + 1);
    }
}