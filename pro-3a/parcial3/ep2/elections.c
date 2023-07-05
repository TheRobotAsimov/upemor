#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////////////////////
#include <time.h>

void initArray(int *array, int size);
void printArray(int *array, int size);

void setUpElections(int *vQuantity, int vSize, char **candNames, int cSize);
void elections(int *vQuantity, int **votes, int vSize, int cSize, char **candNames);
void closeElections(int *array, int size);

int menu();

int main()
{
    int option, sections, candidates, nameLen=50, block1=0, block2=0;
    int *vQuantity, **votes, *array, size=5;
    char **candNames;
    
    srand(time(NULL));
   
    /*printf("\n");
    initArray(array1, size1);
    printArray(array1, size1);
    printf("\n\n");*/
    
    printf(" Ingrese la cantidad de secciones: ");
    scanf("%d", &sections);
    printf(" Ingrese el maximo numero de candidatos: ");
    scanf("%d", &candidates);
    
    vQuantity = (int*)malloc(sections*sizeof(int));

    candNames = (char**)malloc(candidates*sizeof(char*));
    
    for(int i=0; i<candidates; i++)
        candNames[i] = (char*)malloc(nameLen*sizeof(char));

    votes = (int**)malloc(candidates*sizeof(int*));

    for(int i=0; i<candidates; i++)
        votes[i] = (int*)malloc(sections*sizeof(int));
    
    do{
        option = menu();
        switch(option)
        {
            case 1:
                setUpElections(vQuantity, sections, candNames, candidates);
                block1=1;
                break;
            case 2:
                if(block1){
                    elections(vQuantity, votes, sections, candidates, candNames);
                    block2=1;
                }else
                    printf("\n Primero debe realizar la opcion 1\n");
                break;
            case 3:
                if(block1 && block2)
                    closeElections(array, size);
                else
                    printf("\n Antes debe realizar las primeras 2 opciones\n");
                break;
            case 0:
                break;    
            default:
                printf("Default\n");
                break;
        }
    } while(option!=0);
    
    free(vQuantity);
    
    for(int i=0; i<candidates; i++)
        free(candNames[i]);
        
    free(candNames);
    
    return 0;
}

void initArray(int *array, int size)
{
    for(int i=0; i<size; i++)
        array[i]=rand()%50+1;
}

void printArray(int *array, int size)
{
    for(int i=0; i<size; i++)
        printf("%5d", array[i]);
}

void setUpElections(int *vQuantity, int vSize, char **candNames, int cSize)
{
    int size;
    
    for(int i=0; i<vSize; i++)
    {
        printf(" Ingrese el numero de votantes de la seccion %d: ", i+1);
        scanf("%d%*c", &vQuantity[i]);
    }
    printf("------------------------------------------------\n");
    for(int i=0; i<cSize; i++)
    {
        printf(" Ingrese el nombre completo del candidato %d: ", i+1);
        scanf(" %[^\n]", candNames[i]);
        
        size = strlen(candNames[i]);
        
        for(int j=0; j<size; j++)
            if(candNames[i][j]>32 && candNames[i][j]<65){   // Codigo ASCII
                printf(" No incluya caracteres especiales\n");
                i--;
            }
    }
}

void elections(int *vQuantity, int **votes, int vSize, int cSize, char **candNames)
{
    int section, candIndex=-1;
    char candidate[50];
    // votes[candidate][section]
    for(int i=0; i<cSize; i++)
        for(int j=0; j<vSize; j++)
            votes[i][j] = rand()%vQuantity[j];

    for(int i=0; i<cSize; i++){
        for(int j=0; j<vSize; j++)
            printf("%5d", votes[i][j]);
        printf("\n");
    }

    printf(" Ingrese la seccion: ");
    scanf("%d%*c", &section);
    section--;
    printf(" Ingrese el candidato: ");
    scanf(" %[^\n]", candidate);

    for(int i=0; i<cSize; i++){
        if(strcmp(candNames[i], candidate) == 0)
            candIndex = i;
    }

    if(candIndex != -1){
        votes[candIndex][section]++;

        for(int i=0; i<cSize; i++){
            for(int j=0; j<vSize; j++)
                printf("%5d", votes[i][j]);
            printf("\n");
        }
    }else
        printf("No encontrado\n");
}

void closeElections(int *array, int size)
{
    printf("\n yes\n");
}

int menu()
{
    int option;
    
    printf("\n MENU\n");
    printf(" 1. Preparar elecciones\n");
    printf(" 2. Realizar elecciones\n");
    printf(" 3. Cerrar elecciones\n");
    printf(" 0. Fin del programa\n\n");
    printf(" Ingrese la opcion que desee: ");
    scanf("%d", &option);
    
    return option;
}

