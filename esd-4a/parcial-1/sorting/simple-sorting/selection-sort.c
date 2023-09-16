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

void selectionSort (int *array, int arraySize)
{
    int lowest, position;

    for (int i = 0; i < arraySize - 1; i++)
    {
        lowest = array[i];
        position = i;

        for (int j = i + 1; j < arraySize; j++)
        {
            if (array[j] < lowest)
            {
                lowest = array[j];
                position = j;
            }
        }
        
        if (position != i)
        {
            array[position] = array[i];
            array[i] = lowest;
        }
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
    selectionSort(array, arraySize);
    printArray(array, arraySize);

    return 0;
}