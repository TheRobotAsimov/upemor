#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **matrix;
    int row = 4, col = 6;

    printf("\n\n");

    //Solicitar memoria para las filas
    matrix=(int**)malloc(sizeof(int*)*row);

    if(matrix==NULL){
        return 0;
    }

    //Solicitar memoria para columnas
    for (int i = 0; i < row; i++)
    {
        matrix[i]=(int*)malloc(sizeof(int)*col); // Podría pedir un tamaño distinto para cada fila
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {   
            matrix[i][j]=i*col+j+1;
            //scanf("%d", &matrix[i][j]);
        }
        
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%5d", matrix[i][j]);
        }
        printf("\n\n");
    }
    
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]); // Liberar las columnas de las filas
    }
    free(matrix); // Liberar las filas

    return 0;
}