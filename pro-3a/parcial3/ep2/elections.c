#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////////////////////
#include <time.h>

void initArray(int *array, int size);
void printArray(int *array, int size);

void setUpElections(int *vQuantity, int vSize, char **candNames, int cSize);
void elections(int *vMax, int **votes, int vSize, int cSize, char **candNames);
void closeElections(int *vMax, int **votes, int vSize, int cSize, char **candNames);

int menu();

int main()
{
    int option, sections, candidates, nameLen=50, block1=0, block2=0;
    int *vQuantity, **votes;
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
                if(block1 && block2){
                    closeElections(vQuantity, votes, sections, candidates, candNames);
                    block1=0;
                    block2=0;
                }else
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

void elections(int *vMax, int **votes, int vSize, int cSize, char **candNames)
{
    int section, candIndex=-1, quantity;
    char candidate[50];
    // votes[candidate][section]
    for(int i=0; i<cSize; i++)
        for(int j=0; j<vSize; j++)
            votes[i][j] = rand()%(vMax[j]/2);   // Quitar /2

    for(int j=0; j<vSize; j++)
        printf("\tS%d", j+1);

    printf("\n\n");

    for(int i=0; i<cSize; i++){
        printf("%s: ", candNames[i]);
        for(int j=0; j<vSize; j++)
            printf("\t%d", votes[i][j]);
        printf("\n");
    }

    printf("\n");

    printf(" Ingrese la seccion: ");
    scanf("%d%*c", &section);
    section--;
    printf(" Ingrese el candidato: ");
    scanf(" %[^\n]", candidate);

    printf("\n");

    for(int i=0; i<cSize; i++){
        if(strcmp(candNames[i], candidate) == 0)
            candIndex = i;
    }

    if(candIndex != -1 || (section>=0 && section<vSize)){   // Cambiar if
        votes[candIndex][section]++;

        for(int j=0; j<vSize; j++)
            printf("\tS%d", j+1);

        printf("\n\n");

        for(int i=0; i<cSize; i++){
            printf("%s: ", candNames[i]);
            for(int j=0; j<vSize; j++)
                printf("\t%d", votes[i][j]);
            printf("\n");
        }
    }else
        printf(" No encontrado\n");

    candIndex = -1;

    printf("\n");

    printf(" Ingrese la seccion: ");
    scanf("%d%*c", &section);
    section--;
    printf(" Ingrese el candidato: ");
    scanf(" %[^\n]", candidate);

    for(int i=0; i<cSize; i++){
        if(strcmp(candNames[i], candidate) == 0)
            candIndex = i;
    }


    if(candIndex == -1 || section<0 || section>=vSize)
        printf(" No encontrado\n");
    else{
        printf(" Ingrese la cantidad de votos que desea agregar: ");
        scanf("%d%*c", &quantity);

        votes[candIndex][section] += quantity;

        printf("\n");

        for(int j=0; j<vSize; j++)
            printf("\tS%d", j+1);

        printf("\n\n");

        for(int i=0; i<cSize; i++){
            printf("%s: ", candNames[i]);
            for(int j=0; j<vSize; j++)
                printf("\t%d", votes[i][j]);
            printf("\n");
        }
    }
}

void closeElections(int *vMax, int **votes, int vSize, int cSize, char **candNames)
{
    int candSum[cSize], sectSum[vSize];

    for(int i=0; i<cSize; i++)
        candSum[i]=0;

    for(int i=0; i<vSize; i++)
        sectSum[i]=0;

    // Suma por candidatos
    for(int i=0; i<cSize; i++)
        for(int j=0; j<vSize; j++)
            candSum[i]+=votes[i][j];

    // Suma por seccion
    for(int i=0; i<vSize; i++)
        for(int j=0; j<cSize; j++)
            sectSum[i]+=votes[j][i];

    int max = 0, maxInd;  // Agregar empate

    for(int i=0; i<cSize; i++)
        if(candSum[i]>max){
            max = candSum[i];
            maxInd = i;   
        }

    int valido=1;

    printf("\n");

    for(int i=0; i<vSize; i++){
        if(sectSum[i]>vMax[i]){
            printf(" La seccion %d sobrepaso el limite de votos\n", i+1);
            valido=0;
        }
    }

    if(valido){
        printf(" El ganador fue %s\n", candNames[maxInd]);
        for(int i=0; i<cSize; i++)
            printf("  - %s tuvo %d votos\n", candNames[i], candSum[i]);
    }
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

