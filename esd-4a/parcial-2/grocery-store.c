#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// Queue
typedef struct product
{
    int code;
    char name[50];
    float price;
    int quantity;
    char expiration[11];

    struct product *next;

} product;

// DLL
typedef struct category
{
    char name[100];

    struct category *next;
    struct category *previous;

    struct product *firstP;
    struct product *lastP;

} category;

void create_products (product **first, product **last);
void insert_end_p (product **first, product **last, int codeP, char *nameP, float priceP, int quantityP, char *expirationP);
void show_products (product *first);

void create_categories (category **first, category **last);
void insert_start_c (category **first, category **last, char *nameC);
void insert_end_c (category **first, category **last, char *nameC);
void show_categories (category *first);

int main (void)
{

    category *firstC, *lastC;
    create_categories(&firstC, &lastC);

    char nameC[100];
    int option;
    do
    {
        printf("Ingrese el nombre de la categoria: ");
        scanf("%s", nameC);
        insert_start_c(&firstC, &lastC, nameC);
        ////////////////////////////////////////77
        printf("Desea agregar categoria? (1 = si, 0 = no)\n");
        scanf("%d", &option);
    } while (option != 0);
    

    show_categories(firstC);
}

void create_categories (category **first, category **last)
{
    *first = NULL;
    *last = NULL;
}

void create_products (product **first, product **last)
{
    *first = NULL;
    *last = NULL;
}

void insert_end_p (product **first, product **last, int codeP, char *nameP, float priceP, int quantityP, char *expirationP)
{
    product *newProduct = (product *)malloc(sizeof(product));

    newProduct -> code = codeP;
    strcpy(newProduct -> name, nameP);
    newProduct -> price = priceP;
    newProduct -> quantity = quantityP;
    strcpy(newProduct -> expiration, expirationP);

    if(*last == NULL)
    {
        newProduct -> next = NULL;
        *first = *last = newProduct;
    }
    else
    {
        newProduct -> next = *last;
        *last = newProduct;
    }
}

void insert_start_c (category **first, category **last, char *nameC)
{
    category *newCategory = (category *)malloc(sizeof(category));

    strcpy(newCategory -> name, nameC);

    if(*first == NULL)
    {
        newCategory -> next = NULL;
        *first = *last = newCategory;
    }
    else
    {
        newCategory -> next = *first;
        (*first) -> previous = newCategory;
        *first = newCategory;
    }

    newCategory -> previous = NULL;

    newCategory -> firstP = NULL;
    newCategory -> lastP = NULL;

    //////////////////////////////

    int option;
    printf("Desea agregar producto? (1 = si, 0 = no)\n");
    scanf("%d", &option);
    while (option == 1)
    {
        int codeP;
        char nameP[50];
        float priceP;
        int quantityP;
        char expirationP[11];

        printf("Ingrese el codigo del producto: ");
        scanf("%d", &codeP);
        printf("Ingrese el nombre del producto: ");
        scanf("%s", nameP);
        printf("Ingrese el precio del producto: ");
        scanf("%f", &priceP);
        printf("Ingrese la cantidad del producto: ");
        scanf("%d", &quantityP);
        printf("Ingrese la fecha de expiracion del producto: ");
        scanf("%s", expirationP);
        insert_end_p(&(newCategory -> firstP), &(newCategory -> lastP), codeP, nameP, priceP, quantityP, expirationP);
        //////////////////////////////////////////////////////////////
        printf("Desea agregar producto? (1 = si, 0 = no)\n");
        scanf("%d", &option);
    }
    
}

void insert_end_c (category **first, category **last, char *nameC)
{
    category *newCategory = (category *)malloc(sizeof(category));

    strcpy(newCategory -> name, nameC);

    if(*last == NULL)
    {
        newCategory -> previous = NULL;
        *first = *last = newCategory;
    }
    else
    {
        newCategory -> previous = *last;
        (*last) -> next = newCategory;
        *last = newCategory;
    }

    newCategory -> next = NULL;
    newCategory -> firstP = NULL;
    newCategory -> lastP = NULL;
}

void show_categories (category *first)
{
    category *current = first;

    while (current != NULL)
    {
        printf("\nCATEGORIA:\n");
        printf("\n%s\n", current -> name);
        show_products(current -> lastP);
        current = current  -> next;
    }
    
}

void show_products (product *last)
{
    product *current = last;

    printf("\nPRODUCTOS:\n");
    while (current != NULL)
    {
        printf("\n----------------------------------\n");
        printf("%d\n", current -> code);
        printf("%s\n", current -> name);
        printf("%f\n", current -> price);
        printf("%d\n", current -> quantity);
        printf("%s\n", current -> expiration);
        printf("----------------------------------\n");

        current = current -> next;
    }
    
}