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
void insert2R (node **root, char *data);
void print_tree (node *tree, int space);
void print_leaf (node *tree);
void search_predecessor (node *tree, char *data);
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

    int times;
    char data[50];

    printf("Ingrese la cantidad de nodos: ");
    scanf("%d", &times);

    for (int i = 0; i < times; i++)
    {
        printf("Ingrese el dato: ");
        scanf(" %[^\n]", data);
        //insert2(&root, data);
        insert2R(&root, data);
    }

    print_tree(root, 0);

    printf("\n---------------------------------\n\n");

    preorder(root, 0);

    printf("\n---------------------------------\n\n");

    printf("Nodos hoja: ");
    print_leaf(root);
    printf("\n");

    printf("\n---------------------------------\n\n");

    printf("Predecesor de: ");
    scanf(" %[^\n]", data);

    printf("Respuesta: ");
    search_predecessor(root, data);
    printf("\n");
}

void create_tree (node **root)
{
    *root = NULL;
}

node *insert (char *data)
{
    node *new_node = (node *) malloc (sizeof (node));
    //new_node->data = data;
    strcpy (new_node -> data, data);
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
            scanf(" %d", &option);
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

void insert2R (node **root, char *data)
{
    int option;

    if (*root == NULL)
    {
        *root = insert (data);
        printf("\n Nodo creado\n\n");
    }
    else
    {
        printf("Crear hijo izquierdo (1) o derecho (0):\n");
        scanf("%d", &option);

        if (option == 1)
        {
            insert2R (&(*root) -> left, data);
        }
        else
        {
            insert2R (&(*root) -> right, data);
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
        printf("%s\n", tree -> data);
        preorder (tree -> left, ++space);
        preorder (tree -> right, space);
    }
}

void print_leaf (node *tree)
{
    if (tree)
    {
        if (tree -> left == NULL && tree -> right == NULL)
            printf("  %s  ", tree -> data);

        print_leaf (tree -> left);
        print_leaf (tree -> right);
    }
}

void search_predecessor (node *tree, char *data)
{
    if (tree -> left == NULL && tree -> right == NULL)
        return;

    if (tree -> left == NULL && tree -> right != NULL)
    {
        if (strcmp(tree -> right -> data, data) == 0)
        {
            printf("  %s  ", tree -> data);
            return;
        }
        
        search_predecessor (tree -> right, data);

        return;
    }
    
    if (tree -> left != NULL && tree -> right == NULL)
    {
        if (strcmp(tree -> left -> data, data) == 0)
        {
            printf("  %s  ", tree -> data);
            return;
        }

        search_predecessor (tree -> left, data);

        return;
    }


    if (strcmp(tree -> left -> data, data) == 0 || strcmp(tree -> right -> data, data) == 0)
    {
        printf("  %s  ", tree -> data);
        return;
    }
    search_predecessor (tree -> left, data);
    search_predecessor (tree -> right, data);
    
}