#include <stdio.h>

int main(void){
    int dia, mes;

    printf("Ingrese el d%ca: \n", 161);
    scanf("%d", &dia);
    printf("Ingrese el mes: \n");
    scanf("%d", &mes);

    switch (mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:  // Meses con 31 dias
        if(dia >= 1 && dia <= 31){
            printf("Fecha v%clida\n", 160);
        }else{printf("Fecha no v%clida\n", 160);}
        break;
    
    case 4:
    case 6:
    case 9:
    case 11:  // Meses con 30 dias
        if(dia >= 1 && dia <= 30){
            printf("Fecha v%clida\n", 160);
        }else{printf("Fecha no v%clida\n", 160);}
        break;

    case 2: // Febrero
        if(dia >= 1 && dia <= 28){
            printf("Fecha v%clida\n", 160);
        }else{printf("Fecha no v%clida\n", 160);}
        break;

    default:
        printf("Mes no v%clido\n", 160);
        break;
    }
}