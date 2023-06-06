#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){

    char lista[5][30], aux[30];
    int tam = 5, numCarac;

    for(int i=0; i<tam; i++){
        printf("Introduce el nombre %d: ", i+1);
        //scanf("%s", lista[i]); // %s caracteres sin espacio
        scanf(" %[^\n]", lista[i]); // Toma en cuenta todo menos saltos de linea
        numCarac = strlen(lista[i]);
        for(int j=0; j<numCarac; j++){
            if(isdigit(lista[i][j])){
                printf("El nombre no debe tener numeros\n");
                i--;
                break;
            }
        }
    }

    for(int i=0; i<tam-1; i++){
        printf("%s, ", lista[i]);
    }
    printf("%s", lista[tam-1]);

    for (int i = 1; i < tam; i++){
        for(int j=0; j<tam-1; j++){
            if (strcmp(lista[j],lista[j+1])>0){
                strcpy(aux, lista[j]);
                strcpy(lista[j], lista[j+1]);
                strcpy(lista[j+1], aux);
            }
            
        }
    }

    printf("\n");
    
    for(int i=0; i<tam-1; i++){
        printf("%s, ", lista[i]);
    }
    printf("%s", lista[tam-1]);

    return 0;
}

/*
string.h

strcpy(array, "x")

strncpy(aux, lista[], 4);
   ^
number

strlen(aux) -> caracteres que ocupa

strcat() -> concatena arrays

strstr() -> buscar parte de la cadena

*/

/*
ctype.h



*/