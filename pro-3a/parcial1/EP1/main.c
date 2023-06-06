//////////////////////////////////////////////////////////7
//                                                       //
//       EP1. Uso de estructuras de control.             //
//                                                       //
//      Fecha de entrega:  05/06/2023                    // 
//                                                       //
//      Grupo 3ro A ITI                                  //                        
//                                                       //                                                
//      Alumnos:                                         //
//      García Mendoza Isaías     	GMIO220060           //
//      Gómez García José Alberto  	GGJO222091           //
//      Prado Acevedo Ian Marcus   	PAIO221489           //
//                                                       //
///////////////////////////////////////////////////////////

#include <stdio.h>

int main(){
    int opcion;
    // variables de Dibujar Figura
    int fila, columna, altura, espacios, i, j;
    char opcFig;
    // variables de Numeros Coprimos
    int numero, rango, rango1,a,b,temp;
    // variables de Cargos de Electricidad
    char nom[500][30];
    int ant, act, dif, dif1, dif2, opc;
    float cobro, bas, inter, exced;


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
            printf("Ingrese un número: ");
            scanf("%d", &numero);

            printf("Ingrese el rango minimo: ");
            scanf("%d", &rango);
            
            printf("Ingrese el rango maximo: ");
            scanf("%d", &rango1);

            printf("Números coprimos con %d en el rango de %d a %d:\n", numero, rango,rango1);

            for ( i = rango; i <= rango1; i++) {
                a = numero;
                b = i;
                while (b != 0) {
                    temp = b;
                    b = a % b;
                    a = temp;
                }
                if (a == 1) {
                    printf("el numero %d es coprimo de %d\n", i,numero);
                }
            }

            printf("\nDesea regresar al menu? (si=1, no=0): ");
            scanf("%d", &opcion);
            break;
        
        //-----------------------------------------------------//

        case 2:
            i=0;
            bas=0.945;
            inter=1.153;
            exced=3.200;
            do{
                printf("___________________________\n");
                printf("___________________________\n\n");
                printf("Nombre del cliente: ");
                scanf(" %[^\n]%*c", nom[i]);
                i=i++;
                
                printf("Ingresa la medicion de consumo anterior: kWh ");
                scanf("%d", &ant);
                printf("Ingresa la medición de consumo actual:   kWh ");
                scanf("%d", &act);
                
                dif=ant-act;
                
                if(dif<0){
                    dif=dif*-1;
                }
                
                if(dif<=150){
                    cobro=(float)(dif*bas);
                }
                if(dif>150){
                    dif1=dif-150;
                    if(dif1<200){
                        cobro=(float)((150*bas)+(dif1*inter));
                    }else{
                        dif2=dif1-200;
                        cobro=(float)((150*bas)+(200*inter)+(dif2*exced));
                    }
                }
                
                printf("\nNombre del cliente: %s\nConsumo total: %d\t", nom[i], dif);
                printf("\nCobro Final: %.3f", cobro);
                
                if(dif<=150){
                    printf("\tConsumo Basico");
                }
                if(dif>150){
                    dif1=dif-150;
                    if(dif1<200){
                        printf("\tConsumo Basico + Intermedio");
                    }else{
                        dif2=dif1-200;
                        printf("\tConsumo Basico + Intermedio + Excedente");
                    }
                }
                
                printf("\nVolver a realizar la accion (si=1 no=0): ");
                scanf("%d%*c", &opc);
            }while(opc==1);
            break;
        
        //-----------------------------------------------------//

        case 3:
            do{
                printf("Ingrese la altura del triangulo (Entre 4 y 10): ");
                scanf("%d", &altura);
            }while(!(altura >= 4 && altura <= 10));

            fila = altura*2-1;
            columna = fila*3-2;

            printf("Desea la figura vacia o semi rellena? (v/r): ");
            scanf(" %c", &opcFig);

            switch (opcFig){
            case 'v':
                for(i=0; i<fila; i++){
                    for(j=0; j<columna; j++){
                        //Ultima horiz  Ultima vert         Diagonal grande                    Linea horizontal superior                     Primera diagonal /              Segunda diagonal /             Primera \                  Segunda \                     Tercera \                   //  
                        if(i==fila-1 || j==columna-1 || j==fila-i-1+(fila*2-2) || i==fila-(altura) && j>=altura-1 && j<columna-altura || j==fila-i-1 && i>altura-1 || j==fila-i-1+(fila-1) && i>altura-1 || j==i && i>altura-1 || j==i+(fila-1) && i>altura-1 || j==i+(fila*2-2) && i>altura-1){
                            printf("* ");
                        }else{              
                            printf("  ");   
                        }
                    }
                    printf("\n");
                }
                break;
            case 'r':
                for(i=0; i<fila; i++){
                    for(j=0; j<columna; j++){
                        // Trapecio   (  diagonal /,      diagona \  )   Linea vertical      Diagonal grande                               //
                        if(i>=altura-1 && j>=fila-i-1 && j<=i+(fila*2-2) || j==columna-1 || j==fila-i-1+(fila*2-2)){
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