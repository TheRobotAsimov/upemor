#include <stdio.h>

int main(void){
    int num, i;

    printf("Introduce un n%cmero [1, 10]: ", 163);
    scanf("%d", &num);

    if(num >= 1 && num <=10){
        for(i=1; i<=10; i++){
            printf("%3d x %d = %d\n", num, i, num*i);
        }
    }else{printf("El n%cmero no est%c en el rango [1, 10]\n", 163, 160);}


}