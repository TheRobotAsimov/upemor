#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void setArray (int *array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = rand()%200+1;
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

void merge (int *array, int left, int middle, int right)
{
    int i, j, k;

    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[middle + j + 1];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort (int *array, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        //              0     0     1
        merge(array, left, middle, right);
    }
}

int binarySearch(int *array, int left, int right, int searching)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        if (array[middle] == searching)
        {
            //printf("array[%d] = %d = %d\n", middle, array[middle], searching);
            return middle;
        }
        
        if (array[middle] > searching)
            binarySearch(array, left, middle - 1, searching);
        else if (array[middle] < searching)
            binarySearch(array, middle + 1, right, searching);
    }
    else
    {
        return -1;
    }
}

int main (void)
{
    int array[10];
    int arraySize = 10;
    int searching;
    int index;

    srand(time(NULL));

    setArray(array, arraySize);
    printArray(array, arraySize);
    // sort function
    mergeSort(array, 0, arraySize - 1);
    printArray(array, arraySize);

    printf("Type the number you are looking for: ");
    scanf("%d", &searching);
    index = binarySearch(array, 0, arraySize - 1, searching);
    if (index != -1)
        printf("Your number is located in i = %d\n", index);
    else
        printf("Your number doesn't exist\n");

    return 0;
}