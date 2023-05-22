#include <stdio.h>

int main(void){
    int fil, col;

    printf("Introduce el n%cmero de filas: ", 163);
    scanf("%d", &fil);
    printf("Introduce el n%cmero de columnas: ", 163);
    scanf("%d", &col);

    for(int i=0; i<fil; i++){
        for(int j=0; j<col; j++){
            if(i==0 || i==fil-1 || j==0 || j==col-1){
                printf("* ");
            }else{printf("  ");}
        }
        printf("\n");
    }
}