#include <stdio.h>

int main(void){

    int menor, suma=0, num, cont, i=0;
    float promedio;

    do
    {
        printf("Ingrese el n%cmero: \n", 163); // O ponga 0 para terminar
        scanf("%d", &num);

        if (i == 0 || num < menor) // && num != 0
            menor = num;

        suma += num;

        printf("Desea continuar? (si = 1 / no = 0): "); // Se eliminarían estas dos líneas si se pone el 0 para terminar
        scanf("%d", &cont);

        i++;

    } while (cont!=0);

    // i--; // Para que no cuente el 0

    printf("La suma es: %d\n", suma);
    printf("i es: %d\n", i);

    promedio = (float)suma / (float)i;
    
    printf("El promedio es: %.2f\n", promedio);
    printf("El menor es: %d\n", menor);

}