#include <stdio.h>

int main(){
    int fila=4, columna=12;
    printf("\033[1;31mIM RED\033[0m\n");

    for (int i = 0; i < fila; i++)
    {
        for (int j = 0; j < columna; j++)
        {
           if (j==i || j==i+5)
           {
            printf("* ");
           }else{
            printf("  ");
           }
           
        }
        printf("\n");
    }
    

    return 0;
}