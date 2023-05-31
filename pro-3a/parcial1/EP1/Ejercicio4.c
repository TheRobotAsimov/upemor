#include <stdio.h>

int main() {
    int altura, espacios, asteriscos, fila, columna;
    // fila == 5 || fila == 7 || fila == 9
    fila=7;
    columna=fila*3-2; //19
    
    for(int i=0; i<fila; i++){
        for(int j=0; j<columna; j++){//     Diagonal grande         Linea horizontal superior                                Primera diagonal /        Segunda diagonal /    Primera \      Segunda \         Tercera \       //  
            if(i==fila-1 || j==columna-1 || j==fila-i+(fila*2-3) || i==fila-(fila/2+1) && j>fila/2-1 && j<columna-fila/2 || j==fila-i-1 && i>fila/2 || j==fila-i+5 && i>3 || j==i && i>3 || j==i+6 && i>3 || j==i+12 && i>3){
                printf("* ");//                                                 ^               ^                                   ^
            }else{           //                                               altura        horizontal          Se le resta 1 para que inicie desde la orilla
                printf("  ");
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("---------------------------------------------"); 
    printf("\n");

    for(int i=0; i<fila; i++){
        for(int j=0; j<columna; j++){
            // Trapecio, diagonal /, diagona \   Linea vertical  Diagonal grande                               //
            if(i>=3 && j>=fila-i-1 && j<=i+12 || j==columna-1 || j==fila-i+11){
                printf("* ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("---------------------------------------------"); 
    printf("\n");

    int pseudofila = 4; // altura de los triangulos chiquitos

    fila = pseudofila*2 -1; // altura de la linea vertical derecha
    columna = fila*3-2; // -2 por los puntos que comparten los triangulos chiquitos

    for(int i=0; i<fila; i++){
        for(int j=0; j<columna; j++){//     Diagonal grande           Linea horizontal superior                              Primera diagonal /        Segunda diagonal /                    Primera \          Segunda \                     Tercera \                   //  
            if(i==fila-1 || j==columna-1 || j==fila-i-1+(fila*2-2) || i==fila-(fila/2+1) && j>fila/2-1 && j<columna-fila/2 || j==fila-i-1 && i>fila/2 || j==fila-i-1+(fila-1) && i>fila/2 || j==i && i>fila/2 || j==i+(fila-1) && i>fila/2 || j==i+(fila*2-2) && i>fila/2){
                printf("* ");   //                    ^
            }else{              //       -1 para que inicie en la orilla
                printf("  ");   // deberia ser fila*2-1, pero por el for se le resta 1
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("---------------------------------------------"); 
    printf("\n");

    for(int i=0; i<fila; i++){
        for(int j=0; j<columna; j++){
            // Trapecio, diagonal /, diagona \              Linea vertical  Diagonal grande                               //
            if(i>=fila/2 && j>=fila-i-1 && j<=i+(fila*2-2) || j==columna-1 || j==fila-i-1+(fila*2-2)){
                printf("* ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }

    
    return 0;
}
