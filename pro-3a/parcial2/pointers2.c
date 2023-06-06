#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int *datos;
    int tam = 5;

    datos=(int*)malloc(sizeof(int)*tam); // Cuántos bytes necesito entre parentesis. Pidió memoria
                                         // Lo "convierte en arreglo" 
    printf("\n");
    printf("Ingrese 5 numeros\n");
    for (int i = 0; i < tam; i++)
    {
        scanf("%d", &datos[i]); //WTF
    }
    printf("\n");
    for (int i = 0; i < tam; i++)
    {
        printf("%5d", datos[i]); //WTF
    }
    printf("\n");

    free(datos); //Libera memoria. Ya se puede volver a prestar
    


    return 0;
}