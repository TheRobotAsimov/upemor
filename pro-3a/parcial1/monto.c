#include <stdio.h>

void main(){
    int cobrarI, recibidoI, devolverI, cambioI, iI;
    float cobrar, recibido, devolver, i;

    printf("Ingrese monto a cobrar: ");
    scanf("%f", &cobrar);

    printf("Ingrese monto recibido: ");
    scanf("%f", &recibido);

    devolver=recibido-cobrar; //La profesara multiplicó esto por 100 para tener enteros

    printf("Monto a devolver: %.2f \n", devolver);
    while (devolver>0.5)
    {
        if(devolver>=1000){ // 1000 * 100
            iI = (int)devolver/1000;
            devolver -= iI*1000;    // Y aquí usó módulo. En el caso de 50 centavos tuvo cuidado con el flotante
            printf("%d billete(s) de 1000 \n", iI);
        }
        if(devolver>=500 && devolver<1000){
            iI = (int)devolver/500;
            devolver -= iI*500;
            printf("%d billete(s) de 500 \n", iI);
        }
        printf("un ciclo \n");
    }
    printf("fin del ciclo \n");
    

}