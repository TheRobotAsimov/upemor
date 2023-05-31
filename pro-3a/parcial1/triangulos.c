#include <stdio.h>

void main(){
    int fila, columna;

    fila = 8;
    columna = 8;

    for(int i=0; i<fila+1; i++){
        for(int j=0; j<i; j++){
            printf("* ");
        }
        printf("\n");
    }

    printf("\n");
    printf("-------------------");
    printf("\n");
    
    for(int i=0; i<fila; i++){
        for(int j=0; j<columna; j++){
            if(j>=fila-i){
                printf("* ");
            }else{ printf(" ");}
        }
        printf("\n");
    }
}