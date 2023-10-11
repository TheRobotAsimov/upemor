#include <stdio.h>

typedef struct{
    int anio;
    int mes;
    float cantidad;
} venta;

void captura(venta *ventas, int size);
void consultar(venta *ventas, int size);
void quickSort (venta *ventas, int first, int last);
void searchSell (venta *ventas, int size);
int binarySearchR (venta *ventas, int first, int last, int anioS, int mesS);

int main (void)
{
    venta ventas[10];
    int size, search;

    printf("Ingrese el numero de ventas (maximo 10): ");
    scanf("%d", &size);

    if(size <= 10)
    {
        captura(ventas, size);
        consultar(ventas, size);
        quickSort(ventas, 0, size-1);
        consultar(ventas, size);
        printf("Desea buscar alguna venta? (1 = si, otro numero = no)\n");
        scanf("%d", &search);
        if(search == 1)
            searchSell(ventas, size);
    }
    else
        printf("Superaste el limite\n");


    return 0;
}

void captura(venta *ventas, int size)
{
    for(int i=0; i < size; i++)
    {
        printf("---------------\n");
        printf("Ingrese el anio de la venta %d:\n", i+1);
        scanf(" %d", &ventas[i].anio);
        printf("Ingrese el mes de la venta %d:\n", i+1);
        scanf(" %d", &ventas[i].mes);
        printf("Ingrese la cantidad de la venta %d:\n", i+1);
        scanf("%f", &ventas[i].cantidad);
    }
}

void quickSort (venta *ventas, int first, int last)
{
    
    int middle = first + (last - first) / 2;
    int i = first;
    int j = last;
    venta pivot = ventas[middle];
    venta aux;
    
    do
    {
        while ( ventas[i].anio < pivot.anio || 
                ventas[i].anio == pivot.anio && ventas[i].mes > pivot.mes || 
                ventas[i].anio == pivot.anio && ventas[i].mes == pivot.mes && ventas[i].cantidad < pivot.cantidad) 
            i++;
            
        while ( ventas[j].anio > pivot.anio || 
                ventas[j].anio == pivot.anio && ventas[j].mes < pivot.mes || 
                ventas[j].anio == pivot.anio && ventas[j].mes == pivot.mes && ventas[j].cantidad > pivot.cantidad) 
            j--;
            
        if (i <= j)
        {
            aux = ventas[i];
            ventas[i] = ventas[j];
            ventas[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    
    if (j > first)
        quickSort(ventas, first, j);
    if (i < last)
        quickSort(ventas, i, last);
}

void consultar(venta *ventas, int size)
{
    for(int i=0; i<size; i++)
    {
        printf("------------\n");
        printf("Anio: %d\n", ventas[i].anio);
        printf("Mes: %d\n", ventas[i].mes);
        printf("Cantidad: %.2f\n", ventas[i].cantidad);
    }
    printf("--------------------------\n");
    printf("--------------------------\n");
}

int binarySearchR (venta *ventas, int first, int last, int anioS, int mesS)
{

    if (first > last)
        return 0;
        
    int middle = first + (last - first) / 2;
    
    if (ventas[middle].anio == anioS && ventas[middle].mes == mesS)
    {
        printf("Anio: %d, Mes: %d, Cantidad: %.2f\n", ventas[middle].anio, ventas[middle].mes, ventas[middle].cantidad);
        binarySearchR(ventas, middle+1, last, anioS, mesS);
        binarySearchR(ventas, first, middle-1, anioS, mesS);
        return 1;
    }
        
    if(anioS > ventas[middle].anio || 
            anioS == ventas[middle].anio && mesS < ventas[middle].mes)
        binarySearchR(ventas, middle+1, last, anioS, mesS);
    if(anioS < ventas[middle].anio || 
            anioS == ventas[middle].anio && mesS > ventas[middle].mes)
        binarySearchR(ventas, first, middle-1, anioS, mesS);
}

void searchSell (venta *ventas, int size)
{
    int anioS, mesS;

    printf("Ingrese el anio de la venta:\n");
    scanf(" %d", &anioS);
    printf("Ingrese el mes de la venta:\n");
    scanf(" %d", &mesS);
    binarySearchR(ventas, 0, size-1, anioS, mesS);
}