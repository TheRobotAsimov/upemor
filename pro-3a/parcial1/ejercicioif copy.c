#include <stdio.h>

int main(void){
    int a,b,c;
    char u_acento = 163;

    printf("Ingrese el n%cmero a: \n", u_acento);
    scanf("%d", &a);
    printf("Ingrese el n%cmero b: \n", u_acento);
    scanf("%d", &b);
    printf("Ingrese el n%cmero c: \n", u_acento);
    scanf("%d", &c);

    // Único número mayor
    if(a>b && a>c){
        printf("El n%cmero mayor es a con valor de %d \n", u_acento, a);
    }
    if(b>a && b>c){
        printf("El n%cmero mayor es b con valor de %d \n", u_acento, b);
    }
    if(c>a && c>b){
        printf("El n%cmero mayor es c con valor de %d \n", u_acento, c);
    }
    // Dos números mayores
    if(a==b && a>c){
        printf("Los n%cmeros mayores son a y b con valor de %d \n", u_acento, a);
    }
    if(a==c && a>b){
        printf("Los n%cmeros mayores son a y c con valor de %d \n", u_acento, a);
    }
    if(b==c && b>a){
        printf("Los n%cmeros mayores son b y c con valor de %d \n", u_acento, b);
    }
    // Tres números iguales
    if(a==b && a==c){
        printf("Los n%cmeros son iguales\n", u_acento);
    }

    return 0;
}