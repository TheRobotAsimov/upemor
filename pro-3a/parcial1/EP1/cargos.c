#include <stdio.h>

int main()
{
    
    char nom[500][30];
    int i, ant, act, dif, dif1, dif2, opc;
    float cobro, bas, inter, exced;
    i=0;
    bas=0.945;
    inter=1.153;
    exced=3.200;
    
    do{
        printf("___________________________\n");
        printf("___________________________\n\n");
        printf("\tNombre del cliente: ");
        scanf("%[^\n]%*c", nom[i]);
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
        
        printf("\nVolver a realizar la accion (si=0 no=1): ");
        scanf("%d%*c", &opc);
    }while(opc==0);

    return 0;
}