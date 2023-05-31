#include <stdio.h>

int main() {
    int altura, espacios, asteriscos;
    
    printf("Ingrese la altura del triángulo: ");
    scanf("%d", &altura);
    
    espacios = altura - 1;
    asteriscos = 1;
    
    // Imprimir las filas superiores del triángulo
    for (int i = 1; i < altura; i++) {
        for (int j = 1; j <= espacios; j++) {
            printf(" ");
        }
        
        printf("*");
        
        for (int j = 1; j < asteriscos - 1; j++) {
            printf(" ");
        }
        
        if (i != 1) {
            printf("*");
        }
        
        printf("\n");
        
        espacios--;
        asteriscos += 2;
    }
    
    // Imprimir la última fila del triángulo
    for (int i = 1; i <= asteriscos; i++) {
        printf("*");
    }
    
    printf("\n");
    
    return 0;
}
