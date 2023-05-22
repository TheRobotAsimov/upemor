//Estructuras selectivas en C

#include <stdio.h>

int main(void){
    int a = 20;
    int b = 0;

    printf("Ingresa un numero: ");
    scanf("%d", &b);

    if(a>50){
        printf("El numero es mayor a 50\n");
    }
    else{
        printf("El numero es menor a 50\n");
    }

    switch (b)  // No flotante
    {
    case 1:
        /* code */
        break;
    
    default:
        break;
    }

    for (size_t i = 0; i < 9; i++)
    {
        printf("%d\n", i);
    }
    
    while (a<10)
    {
        /* code */
    }
    
    do
    {
        /* code */
    } while (a<10);  // No olvidar el ; al final
    

    return 0;
}