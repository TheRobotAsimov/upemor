#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void setArray (int *array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = rand()%20+1;
    }
}

void printArray (int *array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        printf("%5d", array[i]);
    }
    printf("\n");
}

int main (void)
{
    int array[10];
    int arraySize = 10;

    srand(time(NULL));

    setArray(array, arraySize);
    printArray(array, arraySize);
    // sort function
    printArray(array, arraySize);

    return 0;
}