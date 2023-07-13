#include <stdio.h>

int addProduct(char path[]);
int searchCode(char path[], int code);
int addPrice(char path[], int code, float add);
int modifyPrice(char path[], int code, float newPrice);
void showAll(char path[]);

int showMenu();

int main()
{
    char path[] = "products.dat";
    int option, code = 123, add, newPrice;

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
                printf("Ingrese codigo: ");
                scanf("%d", &code);
                searchCode(path, code);
                break;
            case 3:
                showAll(path);
                break;
            case 4:
                printf("Ingrese codigo: ");
                scanf("%d", &code);
                printf("Ingrese aumento: ");
                scanf("%d", &add);
                addPrice(path, code, add);
                break;
            case 5:
                printf("Ingrese codigo: ");
                scanf("%d", &code);
                printf("Ingrese nuevo precio: ");
                scanf("%d", &newPrice);
                modifyPrice(path, code, newPrice);
                break;
            default:
                printf("Opcion invalida\n");
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
    printf("4. Aumentar precio\n");
    printf("5. Modificar precio\n");
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

    archPointer = fopen(path, "ab"); // agregar al final

    if(archPointer == NULL)
    {
        printf("Problemas con el archivo");
        return 0;
    }

    //fprintf(archPointer, "%d; %s; %d; %.2f\n", code, description, quantity, price);
    
    fwrite(&code, sizeof(int), 1, archPointer);
    fwrite(description, sizeof(description), 1, archPointer);
    fwrite(&quantity, sizeof(int), 1, archPointer);
    fwrite(&price, sizeof(float), 1, archPointer);

    fclose(archPointer);

    return 0;
}

int searchCode(char path[], int code)
{
    FILE *archPointer;
    int codeB, quantity;
    char description[50];
    float price;
    long int tamReg = sizeof(codeB) + sizeof(quantity) + sizeof(description) + sizeof(price);

    archPointer = fopen(path, "rb"); // agregar al final

    if (archPointer == NULL)
    {
        printf("Problemas con el archivo");
        return 0;
    }

    fread(&codeB, sizeof(int), 1, archPointer);

    while (!feof(archPointer))
    {
        if (codeB == code)
        {
            fread(description, sizeof(description), 1, archPointer);
            fread(&quantity, sizeof(int), 1, archPointer);
            fread(&price, sizeof(float), 1, archPointer);
            printf("Producto encontrado :D\n");
            printf("- Clave: %d, Descripcion: %s, Cantidad: %d, Precio: %.2f\n", codeB, description, quantity, price);
            fclose(archPointer);
            return 1;
        }
        fseek(archPointer, tamReg-sizeof(codeB), SEEK_CUR); // El tamaño total del registro menos lo que ya leí
        fread(&codeB, sizeof(int), 1, archPointer);
    }

    printf("Producto no encontrado :c\n");
    fclose(archPointer);

    return 0;
}

void showAll(char path[])
{
    FILE *archPointer;
    int code, quantity;
    char description[50];
    float price;
    
    archPointer = fopen(path, "rb");

    if(archPointer == NULL)
    {
        printf("Error al cargar archivo");
        return;
    }

    printf("\nListado de productos:\n");

    fread(&code, sizeof(int), 1, archPointer);

    while (!feof(archPointer))
    {
        fread(description, sizeof(description), 1, archPointer);
        fread(&quantity, sizeof(int), 1, archPointer);
        fread(&price, sizeof(float), 1, archPointer);
        printf("- Clave: %d, Descripcion: %s, Cantidad: %d, Precio: %.2f\n", code, description, quantity, price);
        fread(&code, sizeof(int), 1, archPointer);
    }

    fclose(archPointer);

    return;
}

int addPrice(char path[], int code, float add)
{
    FILE *archPointer;

    archPointer = fopen(path, "r+b"); // Leer y escribir

    if (archPointer == NULL)
    {
        printf("Problemas con el archivo\n");
        return 0;
    }

    int codeB, quantity;
    char description[50];
    float price;
    long int range = sizeof(codeB) + sizeof(quantity) + sizeof(description) + sizeof(price);

    fread(&codeB, sizeof(int), 1, archPointer);

    while (!feof(archPointer))
    {
        if (codeB == code)
        {
            fseek(archPointer, range - sizeof(codeB) - sizeof(price), SEEK_CUR); // 
            fread(&price, sizeof(float), 1, archPointer); // read hace avanzar al archivo

            price += add;

            fseek(archPointer, ftell(archPointer) - sizeof(price), SEEK_SET); // ftell da la posición en la está actualmente
            fwrite(&price, sizeof(float), 1, archPointer);
            printf("Precio modificado\n");

            fclose(archPointer);
            return 1;
        }
        fseek(archPointer, range - sizeof(codeB), SEEK_CUR);
        fread(&codeB, sizeof(int), 1, archPointer);
    }
    

    fclose(archPointer);

    return 0;
}

int modifyPrice(char path[], int code, float newPrice)
{
    FILE *archPointer;

    archPointer = fopen(path, "r+b"); // Leer y escribir

    if (archPointer == NULL)
    {
        printf("Problemas con el archivo\n");
        return 0;
    }

    int codeB, quantity;
    char description[50];
    float price;
    long int range = sizeof(codeB) + sizeof(quantity) + sizeof(description) + sizeof(price);

    fread(&codeB, sizeof(int), 1, archPointer);

    while (!feof(archPointer))
    {
        if (codeB == code)
        {
            fseek(archPointer, range - sizeof(codeB) - sizeof(price), SEEK_CUR); // Debes estar al final
            fread(&price, sizeof(float), 1, archPointer); // read hace avanzar al archivo

            price = newPrice;

            fseek(archPointer, ftell(archPointer) - sizeof(price), SEEK_SET); // ftell da la posición en la está actualmente
            fwrite(&price, sizeof(float), 1, archPointer);
            printf("Precio modificado\n");

            fclose(archPointer);
            return 1;
        }
        fseek(archPointer, range - sizeof(codeB), SEEK_CUR);
        fread(&codeB, sizeof(int), 1, archPointer);
    }
    

    fclose(archPointer);

    return 0;
}