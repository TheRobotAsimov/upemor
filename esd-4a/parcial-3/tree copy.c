#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

void create_tree (node **root);
node *insert (int data);
void insert2 (node **root, int data);
void insert2R (node **root, int data);
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

    int data, times;

    printf("Ingrese la cantidad de nodos: ");
    scanf("%d", &times);

    for (int i = 0; i < times; i++)
    {
        printf("Ingrese el dato: ");
        scanf("%d", &data);
        insert2(&root, data);
    }

    print_tree(root, 0);

    printf("\n---------------------------------\n\n");

    preorder(root, 0);
}

void create_tree (node **root)
{
    *root = NULL;
}

node *insert (int data)
{
    node *new_node = (node *) malloc (sizeof (node));
    new_node->data = data;
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
        printf ("%d\n", tree -> data);
        print_tree (tree -> left, space + 1);
    }
}

void insert2 (node **root, int data)
{
    // aux is equal to current and aux2 is equal to previous
    node *aux, *aux2;
    int option;

    if (*root == NULL)
    {
        *root = insert (data);
    }
    else
    {
        aux = *root;
        while (aux != NULL)
        {
            aux2 = aux;
            printf("Crear hijo izquierdo (1) o derecho (2)\n");
            scanf("%d", &option);
            if (option == 1)
            {
                aux = aux -> left;
            }
            else
            {
                aux = aux -> right;
            }

        }

        if (option == 1)
        {
            aux2 -> left = insert (data);
        }
        else
        {
            aux2 -> right = insert (data);
        }
        
    }

    printf("\n Nodo creado\n\n");
}

void insert2R (node **root, int data)
{
    int option;

    if (*root == NULL)
    {
        *root = insert (data);
    }
    else
    {
        printf("Crear hijo izquierdo (1) o derecho (0):\n");
        scanf("%d", &option);

        if (option == 1)
        {
            insert2R ((*root) -> left, data);
        }
        else
        {
            insert2R ((*root) -> right, data);
        }
    }
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
        printf("%d\n", tree -> data);
        preorder (tree -> left, ++space);
        preorder (tree -> right, space);
    }
}