#include <stdio.h>

int main(){
    int opcion;

    int fila, columna, altura, espacios;
    char opcFig;

    printf(" --------------------------------------------- \n");
    printf("|     EP1: Uso de estructuras de control      | \n");

    do{

        printf(" --------------------------------------------- \n");
        printf("|                   MENU                      | \n");
        printf("| Ingrese un numero segun la opcion que desee | \n");
        printf("|                                             | \n");
        printf("| (1) Numeros Coprimos                        | \n");
        printf("| (2) Cargos de Electricidad                  | \n");
        printf("| (3) Dibujar Figura                          | \n");
        printf("|                                             | \n");
        printf("| (0) Terminar ejecucion                      | \n");
        printf(" ---------------------------------------------  \n");

        printf("Ingrese la opcion: "); 
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion){
        case 0:
            break;

        //-----------------------------------------------------//

        case 1:
            printf("Opcion 1\n");
            break;
        
        //-----------------------------------------------------//

        case 2:
            printf("Opcion 2\n");
            break;
        
        //-----------------------------------------------------//

        case 3:
            do{
                printf("Ingrese la altura del triangulo (Entre 4 y 10): ");
                scanf("%d", &altura);
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
                        if(i==fila-1 || j==columna-1 || j==fila-i-1+(fila*2-2) || i==fila-(fila/2+1) && j>fila/2-1 && j<columna-fila/2 || j==fila-i-1 && i>fila/2 || j==fila-i-1+(fila-1) && i>fila/2 || j==i && i>fila/2 || j==i+(fila-1) && i>fila/2 || j==i+(fila*2-2) && i>fila/2){
                            printf("* ");//             ^
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
                            printf("* ");
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

            printf("\nDesea regresar al menu? (si=1, no=0): ");
            scanf("%d", &opcion);
            break;

        //-----------------------------------------------------//

        default:
            printf("Opcion invalida\n");
            break;
        }
    }while(opcion!=0);

    printf("\nFin del programa\n");

    return 0;
}