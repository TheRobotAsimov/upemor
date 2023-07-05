#include <stdio.h>

int addProduct(char path[]);
int searchCode(char path[], int code);
void showAll(char path[]);

int showMenu();

int main()
{
    char path[] = "products.txt";
    int option, code = 123;

    do{
        option = showMenu();

        switch (option)
        {
            case 0:
                break;
            case 1:
                addProduct(path);
                break;
            case 2:
                searchCode(path, code);
                break;
            case 3:
                showAll(path);
                break;
            default:
                break;
        }
    } while (option != 0);
    

    return 0;
}

int showMenu()
{
    int option;

    printf("\nMENU\n");
    printf("1. Agregar producto\n");
    printf("2. Buscar clave\n");
    printf("3. Mostrar todo\n");
    printf("0. Salir\n");
    printf("\nIngrese la opcion que desea: ");
    scanf("%d", &option);

    return option;
}

int addProduct(char path[])
{
    int code, quantity;
    char description[50];
    float price;
    FILE *archPointer;

    printf("Introduce clave: ");
    scanf("%d%*c", &code);

    printf("Descripcion: ");
    scanf(" %[^\n]", description);

    printf("Cantidad: ");
    scanf("%d", &quantity);

    printf("Precio: ");
    scanf("%f", &price);

    archPointer = fopen(path, "at"); // agregar al final

    if(archPointer == NULL)
    {
        printf("Problemas con el archivo");
        return 0;
    }

    fprintf(archPointer, "%d; %s; %d; %.2f\n", code, description, quantity, price);
    
    fclose(archPointer);

    return 0;
}

int searchCode(char path[], int code)
{
    FILE *archPointer;



    fclose(archPointer);

    return 0;
}

void showAll(char path[])
{
    FILE *archPointer;
    int code, quantity;
    char description[50];
    float price;
    
    archPointer = fopen(path, "rt");

    if(archPointer == NULL)
    {
        printf("Error al cargar archivo");
        return;
    }

    printf("\nListado de productos:\n");

    fscanf(archPointer, "%d; %[^;]; %d; %f", &code, description, &quantity, &price); // %[^;] -> todo menos punto y coma

    while(!feof(archPointer)) // file end of
    {
        printf("- Clave: %d, Descripcion: %s, Cantidad: %d, Precio: %.2f\n", code, description, quantity, price);  // Imprime lo que leyó
        fscanf(archPointer, "%d; %[^;]; %d; %f", &code, description, &quantity, &price); // %[^;] -> todo menos punto y coma
    }


    fclose(archPointer);

    return;
}
