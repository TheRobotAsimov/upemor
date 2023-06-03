#include <stdio.h>

void main(){
    int num, i=2, fact=0;

    printf("Ingrese un n%cmero: ", 163);
    scanf("%d", &num);

    printf("%d =", num);

    while (num>i)
    {
        if (num%i==0){
            num/=i;
            printf(" %d *", i);
            if (fact != i){       //Evita los factores repetidos
                printf("%d ", i);
                fact=i;
            }
        }
        else{
            i++;
        }
    }
    printf(" %d", i);
    
    
}