#include <stdio.h>

int main() {
    int fila,i,col;

    printf("Ingrese las filas del triángulo: ");
    scanf("%d", &fila);
    col=fila*2-1;
    // Imprimir el triángulo equilatero sin relleno utilizando dos bucles anidados
    for ( i = 1; i <= fila; i++) {
        for (int j = 1; j <=col; j++) {
            if(i==fila || j==fila-i+1 || j==fila+i-1 ){
                 printf("%d ",j);
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
    
    printf("\n");
    
    
    // Imprimir el triángulo equilatero  relleno utilizando dos bucles anidados
    for ( i = 1; i <= fila; i++) {
        for (int j = 1; j <=fila; j++) {
            if( i==1 || j==fila || j==i ){
                 printf("* ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    
    
    printf("\n");
    
    printf("\n");
     // Imprimir el triángulo equilatero  relleno utilizando dos bucles anidados
    for ( i = 1; i <= fila; i++) {
        for (int j = 1; j <=fila; j++) {
            if( i==1 || j==fila || j>=i ){
                 printf("* ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    return 0;
}