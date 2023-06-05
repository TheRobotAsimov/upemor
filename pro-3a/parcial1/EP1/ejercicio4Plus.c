#include <stdio.h>

int main(){
    int fila, columna, altura, espacios;
    char opcFig, simbolo;

    simbolo = '*';

    printf("\n");

    do{
        printf("Ingrese la altura del triangulo (Entre 4 y 10): ");
        scanf("%d", &altura);
        printf("\n");
    }while(!(altura >= 4 && altura <= 10));

    fila = altura*2-1;
    columna = fila*3-2;

    printf("Desea la figura vacia o rellena? (v/r): ");
    scanf(" %c", &opcFig);

    switch (opcFig){
    case 'v':
        for(int i=0; i<fila; i++){
            for(int j=0; j<columna; j++){
                //Ultima horiz  Ultima vert         Diagonal grande                    Linea horizontal superior                     Primera diagonal /              Segunda diagonal /             Primera \                  Segunda \                     Tercera \                   //  
                if(i==fila-1 || j==columna-1 || j==fila-i-1+(fila*2-2) || i==fila-(altura) && j>=altura-1 && j<columna-altura || j==fila-i-1 && i>altura-1 || j==fila-i-1+(fila-1) && i>altura-1 || j==i && i>altura-1 || j==i+(fila-1) && i>altura-1 || j==i+(fila*2-2) && i>altura-1){
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
                if(i>=altura-1 && j>=fila-i-1 && j<=i+(fila*2-2) || j==columna-1 || j==fila-i-1+(fila*2-2)){
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

    int opcion;

    printf("Desea regresar al menu? (si=1, no=0): ");
    scanf("%d", &opcion);

    return 0;
}