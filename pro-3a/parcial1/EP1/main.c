#include <stdio.h>

int main(){
    int fila, columna, altura, espacios;
    char opcion, simbolo;

    simbolo = '*';

    printf("\n");

    do{
        printf("Ingrese la altura del triangulo (5, 7 o 9): ");
        scanf("%d", &altura);
        printf("\n");
    }while(altura != 5 && altura != 7 && altura != 9);

    fila = altura*2-1;
    columna = fila*3-2;

    printf("Desea la figura vacia o rellena? (v/r): ");
    scanf(" %c", &opcion);

    switch (opcion){
    case 'v':
        for(int i=0; i<fila; i++){
            for(int j=0; j<columna; j++){
                //Ultima horiz  Ultima vert         Diagonal grande                    Linea horizontal superior                     Primera diagonal /              Segunda diagonal /             Primera \                  Segunda \                     Tercera \                   //  
                if(i==fila-1 || j==columna-1 || j==fila-i-1+(fila*2-2) || i==fila-(fila/2+1) && j>fila/2-1 && j<columna-fila/2 || j==fila-i-1 && i>fila/2 || j==fila-i-1+(fila-1) && i>fila/2 || j==i && i>fila/2 || j==i+(fila-1) && i>fila/2 || j==i+(fila*2-2) && i>fila/2){
                    printf("%c ", simbolo);//             ^
                }else{              //       -1 para que inicie en la orilla
                    printf("  ");   // deberia ser fila*2-1, pero por el for se le resta 1
                }
            }
            printf("\n");
        }
        break;
    case 'r':
        for(int i=0; i<fila; i++){
            for(int j=0; j<columna; j++){
                // Trapecio   (  diagonal /,      diagona \  )   Linea vertical      Diagonal grande                               //
                if(i>=fila/2 && j>=fila-i-1 && j<=i+(fila*2-2) || j==columna-1 || j==fila-i-1+(fila*2-2)){
                    printf("%c ", simbolo);
                }else{
                    printf("  ");
                }
            }
            printf("\n");
        }
        break;
    
    default:
        printf("Opcion no valida\n");
        break;
    }

    return 0;
}