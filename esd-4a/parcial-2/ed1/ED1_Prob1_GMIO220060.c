#include <stdio.h>
#include <string.h>

void bubbleSort (char names[20][50], int quantity);
void linearSearch(char names[20][50], int quantity, char searching[50]);

void printNames (char names[20][50], int quantity);
int addNames (char names[20][50], int *quantity);
void searchName(char names[20][50], int quantity);

int main (void)
{
    int quantity, search=0;
    char names[20][50];

    if (addNames(names, &quantity) == 1)
        return 0;

    printNames(names, quantity);

    bubbleSort(names, quantity);

    printNames(names, quantity);

    printf("Desea buscar un nombre? (1 = si, otro numero = no)\n");
    scanf("%d", &search);
    if(search == 1)
        searchName(names, quantity);

    return 0;
}

void printNames (char names[20][50], int quantity)
{
    printf("\n");
    for (int i=0; i<quantity; i++)
    {
        printf("%s\n", names[i]);
    }
    printf("\n");
}

int addNames (char names[20][50], int *quantity)
{
    printf("Ingrese el numero de nombres (maximo 20): ");
    scanf("%d", quantity);

    if((*quantity) > 20)
    {
        printf("Superaste el limite\n");
        return 1;
    }

    for (int i=0; i<(*quantity); i++)
    {
        printf("Ingrese el nombre numero %d:\n", i+1);
        scanf(" %[^\n]", names[i]);
    }
    return 0;
}

 void bubbleSort (char names[20][50], int quantity)
{
    int swap;
    char aux[50];

    for (int i = 0; i < quantity - 1; i++)
    {
        swap = 0;
        for (int j = 0; j < quantity - i - 1; j++)
        {   
            if (strlen(names[j]) == strlen(names[j+1]) && strcmp(names[j], names[j+1]) > 0)
            {
                strcpy(aux, names[j]);
                strcpy(names[j], names[j+1]);
                strcpy(names[j+1], aux);
                swap = 1;
            }
            else if (strlen(names[j]) > strlen(names[j+1]))
            {
                strcpy(aux, names[j]);
                strcpy(names[j], names[j+1]);
                strcpy(names[j+1], aux);
                swap = 1;
            }
        }
        
        if (swap == 0)
            break;
    }
    
}

void linearSearch(char names[20][50], int quantity, char searching[50])
{
    int i = 0;
    int found = 0;
    
    while(found != 1 && i < quantity)
    {
        if (strcmp(names[i], searching) == 0)
            found = 1;
        i++;
    }
    
    if(found == 1)
        printf("El nombre se encuentra en el indice %d\n", i-1);
    else
        printf("Nombre no encontrado\n");   
}

void searchName(char names[20][50], int quantity)
{
    char name[50];

    printf("Ingrese el nombre que busca:\n");
    scanf(" %[^\n]", name);
    linearSearch(names, quantity, name);
}