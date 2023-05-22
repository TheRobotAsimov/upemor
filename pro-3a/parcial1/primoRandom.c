#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
    srand(time(NULL));
    int num, sup=10000, inf=1, div;
    do
    {
        div=0;
        num = rand() % (sup - inf + 1) + inf;
        printf("N%cmero aleatorio: %d\n", 163, num);
        //printf("Divisores: \n");
        for (int i = 2; i < num; i++)
        {
            if(num%i == 0){
                //printf("%d\n", i);
                div++;
                break;
            }
        }

        //printf("Tiene %d divisores\n", div);
        
    } while (div != 0);

    printf("El n%cmero primo es: %d\n", 163, num);
    
}