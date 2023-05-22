#include <stdio.h>

int main(void){
    int aciertos;

    printf("Ingrese el n%cmero de aciertos: \n", 163);
    scanf("%d", &aciertos);

    if(aciertos >= 19 && aciertos <=20){
        printf("Nota: A");
    }
    if(aciertos >= 16 && aciertos <= 18){
        printf("Nota: B");
    }
    if(aciertos >= 13 && aciertos <= 15){
        printf("Nota: C");
    }
    if(aciertos >= 10 && aciertos <= 12){
        printf("Nota: D");
    }
    if(aciertos > 0 && aciertos <= 9){
        printf("Nota: E");
    }
    if(aciertos <= 0 || aciertos > 20){
        printf("N%cmero de aciertos no v%clido", 163, 160);
    }

    return 0;
}