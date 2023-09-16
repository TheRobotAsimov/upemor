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

void bubbleSort (int *array, int arraySize)
{
    int aux, swap;

    for (int i = 0; i < arraySize - 1; i++)
    {
        swap = 0;
        for (int j = 0; j < arraySize - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                aux = array[j];
                array[j] = array[j+1];
                array[j+1] = aux;
                swap = 1;
            }
        }
        
        if (swap == 0)
            break;
    }
    
}

int main (void)
{
    int array[10];
    int arraySize = 10;

    srand(time(NULL));

    setArray(array, arraySize);
    printArray(array, arraySize);
    // sort function
    bubbleSort(array, arraySize);
    printArray(array, arraySize);

    return 0;
}