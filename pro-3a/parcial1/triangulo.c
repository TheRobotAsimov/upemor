#include <stdio.h>

int main(void){
    int fil, col;

    printf("Introduce el n%cmero de filas: ", 163);
    scanf("%d", &fil);
    printf("Introduce el n%cmero de columnas: ", 163);
    scanf("%d", &col);

    //Normal
    for(int i=0; i<fil; i++){
        for(int j=0; j<i; j++){
            if(j==0 || j==i-1 || i==fil-1)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }

    printf("\n------------------\n");

    // a
    for(int i=fil; i>0; i--){
        for(int j=i; j>0; j--){
            if(j==0 || j==i-1 || i==fil-1)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }

    printf("\n------------------\n");

    // b
    printf("b\n");
    for(int i=0; i<fil; i++){
            for(int j=0; j<fil; j++){
                if(j>=i)
                    printf("* ");
                else
                    printf("  ");
            }
            printf("\n");
        }

    printf("\n------------------\n");

    // c
    //int col = fil*2-1;
    for(int i=1; i<=fil; i++){
        for(int j=1; j<=col; j++){
            if(j>=fil-i+1 && j<=fil+i-1)
                printf("* ");
            else
                printf(" ");
            
        }
        printf("\n");
    }

    printf("\n------------------\n");

    

}