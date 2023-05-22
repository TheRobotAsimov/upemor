// Mostrar los divisores propios de un número

#include <stdio.h>

int main(void){
    int num1, num2=0, i, sum=0;

    printf("Introduce un n%cmero: ", 163);
    scanf("%d", &num1);

    /*printf("Introduce un n%cmero: ", 163);
    scanf("%d", &num2);*/

    for(i=1; i<=num1/2; i++){
        if(num1%i == 0){
            //printf("%d\n", i);
            num2+=i; // suma de divisores propios
        }
    }
    printf("La suma de los divisores propios de %d es: %d\n", num1, num2);
    for(i=1; i<=num2/2; i++){
        if(num2%i == 0){
            //printf("%d\n", i);
            sum+=i; // suma de divisores propios
        }
    }
    printf("La suma de los divisores propios de %d es: %d\n", num2, sum);
    if(num1 == sum){
        printf("El n%cmero amigo de %d es: %d\n", 163, num1, num2);
    }else{printf("El n%cmero %d no tiene n%cmero amigo\n", 163, num1, 163);}
}