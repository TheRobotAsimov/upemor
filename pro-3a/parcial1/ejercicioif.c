#include <stdio.h>

int main(void){
    int a,b;
    char u_acento = 163;

    do
    {
        printf("Ingrese el n%cmero a: \n", u_acento);
        scanf("%d", &a);
        printf("Ingrese el n%cmero b: \n", u_acento);
        scanf("%d", &b);

        if(a>b){
            printf("El n%cmero mayor es %d \n", u_acento, a);
            printf("Los n%cmeros ordenados son: %d, %d\n", u_acento, b, a);
        } else{
            if (b>a)
            {
                printf("El n%cmero mayor es %d \n", u_acento, b);
                printf("Los n%cmeros ordenados son: %d, %d\n", u_acento, a, b);
            }else{
                printf("Los n%cmeros son iguales\n", u_acento);
            }
            
        }
    } while (a != b);
    

    return 0;
}