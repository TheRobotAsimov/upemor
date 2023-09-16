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

void quickSort (int *array, int start, int end)
{
    int i, j, half, pivot, aux;

    i = start;
    j = end;
    half = start + (end - start) / 2;
    pivot = array[half];

    do
    {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;

        if (i <= j)
        {
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;

            i++;
            j--;
        }
        
    } while (i <= j);

    if (i < end)
        quickSort(array, i, end);
    if (start < j)
        quickSort(array, start, j);
}

int main (void)
{
    int array[10];
    int arraySize = 10;

    srand(time(NULL));

    setArray(array, arraySize);
    printArray(array, arraySize);
    // sort function
    quickSort(array, 0, arraySize - 1);
    printArray(array, arraySize);

    return 0;
}