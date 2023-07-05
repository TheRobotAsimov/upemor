#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int data[], int size);
void print(int data[], int size);
void printRec(int data[], int ind);
void sort(int data[], int size);

int search(int num, int data[], int size);
int searchRec(int num, int data[], int size);
int binSearch(int num, int data[], int size);
int binSearchRec(int num, int data[], int limI, int limS);
int menu();

int main()
{
    int data[10], size=10, opc, num;
    srand(time(NULL));

    do{
        opc=menu();
        switch(opc){
            case 1: 
                init(data, size);
                break;
            case 2:
                sort(data, size);
                break;
            case 3:
                printf("\n");
                printRec(data, size-1);
                printf("\n");
                break;
            case 4:
                printf("Ingrese numero que desea buscar: ");
                scanf("%d", &num);
                if (binSearchRec(num, data, 0, size-1))
                    printf("Encontrado :D\n");
                else
                    printf("No encontrado :/\n");
                
                break;
            case 0:
                break;
            default:
                printf("Default");
        }
    }while (opc!=0);
    printf("\n");

    return 0;
}

void init(int data[], int size)
{
    for(int i=0; i<size; i++)
        data[i]=rand()%10+1;
}

void print(int data[], int size)
{
    for(int i=0; i<size; i++)
        printf("%5d", data[i]);
    printf("\n");
}

void sort(int data[], int size)
{
    int aux;
    for(int i=1; i<size; i++)
        for(int j=0; j<size-1; j++)
            if(data[j]>data[j+1]){
                aux=data[j];
                data[j]=data[j+1];
                data[j+1]=aux;
            }
}

int search(int num, int data[], int size)
{
    for(int i=0; i<size; i++){
        if(num==data[i])
            return 1;
        else if(num<data[i])
            return 0;
    }
    return 0;
}

int binSearch(int num, int data[], int size)
{
   
}

int binSearchRec(int num, int data[], int limI, int limS)
{
    if(limI > limS)
        return 0;
    
    int mitad = (limS-limI)/2 + limI;
    
    if(data[mitad]==num)
        return 1;
        
    if(num<data[mitad]){
        return binSearchRec(num, data, limI, mitad-1);
    }
    
    if(num>data[mitad]){
        return binSearchRec(num, data, mitad+1, limS);
    }
}

int menu(){
    int opc;
    printf("\nMenu de opciones\n");
    printf("1. Inicializar arreglo\n");
    printf("2. Ordenar\n");
    printf("3. Imprimir\n");
    printf("4. Buscar\n");
    printf("0. Salir \n");
    printf("Introduce la opcion: ");

    scanf("%d", &opc);
    return opc;
}

void printRec(int data[], int ind)
{
    if(ind<0){
        return;
    }
    printf("%5d", data[ind]);
    printRec(data, --ind);
}

int searchRec(int num, int data[], int ind)
{
    if(ind<0)
        return 0;
        
    if(num==data[ind])
        return 1;
    
    return searchRec(num, data, --ind);
}
