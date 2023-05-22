#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
    int num, intentos = 0, sup=100, inf=1;
    srand(time(NULL));
    int NUM_ELEGIDO = rand() % (sup - inf + 1) + inf;
    do
    {
        printf("Adivina el n%cmero: ", 163);
        scanf("%d", &num);

        if(num == NUM_ELEGIDO)
            printf("\nHas acertado!\n");
        else if(num < NUM_ELEGIDO)
            printf("El n%cmero es mayor\n", 163);
        else
            printf("El n%cmero es menor\n", 163);

        intentos++;
    } while (num != NUM_ELEGIDO);

    printf("Has necesitado %d intentos\n", intentos);

    if(intentos<5)
        printf("Enhorabuena!");
    if(intentos>=5 && intentos<=10)
        printf("No est%c mal", 160);
    if(intentos>10)
        printf("Debe practicar m%cs", 160);

    
}