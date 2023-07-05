#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pairsRec(int data[], int size);
unsigned long int multPairs(int data[], int size);
int multPairsRec(int data[], int size, int *multUnpair);
void initArray(int data[], int size);
void printArray(int data[], int size);

int sum3Mult(int data[], int size);
int sum3MultRec(int data[], int size);

int main()
{
    int data[5];
    int size = 5;

    int multUnpair = 1;

    srand(time(NULL));

    initArray(data, size);
    printf("\n");
    printArray(data, size);
    printf("\n\n");
    printf("\tNumero de pares: %d\n", pairsRec(data, size));
    printf("\n");
    int product = multPairsRec(data, size, &multUnpair);
    if(product == 1)
        product = 0;
    printf("  Resultado de multiplicar los pares: %d\n", product);
    printf("  Resultado de multiplicar los impares: %d\n", multUnpair);
     printf("  Resultado de sumar los multiplos de 3: %d\n\n", sum3MultRec(data, size));

    return 0;
}

///////// ARREGLO ///////////

void initArray(int data[], int size)
{
    for(int i=0; i<size; i++)
        data[i]=rand()%50+1;
}

void printArray(int data[], int size)
{
    for(int i=0; i<size; i++)
        printf("%5d ", data[i]);
}

//////////////////////////////

int pairsRec(int data[], int size)
{
    if(size-1<0)
        return 0;

    if(data[size-1]%2==0)
        return 1+pairsRec(data, --size);

    pairsRec(data, --size);
}

unsigned long int multPairs(int data[], int size)
{
    unsigned long int mult=1;
    for(int i=0; i<size; i++)
        if(data[i]%2==0)
            mult*=data[i];
    
    return mult;
}

int multPairsRec(int data[], int size, int *multUnpair)
{
    if(size-1<0)
        return 1;

    if(data[size-1]%2==0)
        return data[size-1]*multPairsRec(data, --size, multUnpair);
    else
        *multUnpair*=data[size-1];
        multPairsRec(data, --size, multUnpair);
}

int sum3Mult(int data[], int size)
{
    int sum=0;

    for(int i=0; i<size; i++)
        if(data[i]%3==0)
            sum+=data[i];

    return sum;
}

int sum3MultRec(int data[], int size)
{
    if(size-1<0)
        return 0;

    if(data[size-1]%3==0)
        return data[size-1]+sum3MultRec(data, --size);
    
    sum3MultRec(data, --size);
}
