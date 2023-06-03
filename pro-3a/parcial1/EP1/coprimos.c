#include <stdio.h>

int main() {

int numero, rango, rango1,a,b,temp,i;

    printf("Ingrese un número: ");
    scanf("%d", &numero);

    printf("Ingrese el rango minimo: ");
    scanf("%d", &rango);
    
      printf("Ingrese el rango maximo: ");
    scanf("%d", &rango1);

    printf("Números coprimos con %d en el rango de %d a %d:\n", numero, rango,rango1);

    for ( i = rango; i <= rango1; i++) {
        a = numero;
        b = i;
        while (b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }
        if (a == 1 && i != 1) {
            printf("el numero %d es coprimo de %d\n", i,numero);
        }
    }

    printf("\n");

    return 0;
}