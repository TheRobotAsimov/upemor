#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void main(){
    srand(time(NULL));

    int matrix[3][3] = {{1,2,3},
                        {4,5,6},
                        {7,8,9}};

    int matrix2[3][3] = {1,2,3,4,5,6,7,8,9};

    char name[20] = "John";
                //= {'J', 'o', 'h', 'n', '\0'};
    char names[5][20] = {"John", "Mary", "Peter", "Paul", "George"};

    printf("%s\n", names[3]);
    printf("%c\n", names[3][2]);

    printf("\n");

    printf("%d\n", matrix[1][2]);
    printf("%d\n", matrix2[1][2]);

    printf("\n");

    int size=10, i, j, aux;
    int data[size];
    int average, median, mode;

    //Get array values and Average
    for(i=0; i<size; i++){
        //printf("Enter a number: ");
        //scanf("%d", &data[i]);
        data[i] = rand()%100+1;
        printf("data[%d] = %d ", i, data[i]);
                                    //data without [i] is the address of the array
        average += data[i];
    }

    //Bubblesorting
    for(i=1; i<size; i++){
        for (j = 0; j < size-1; j++)
        {
            if (data[j]>data[j+1])
            {
                aux = data[j];
                data[j] = data[j+1];
                data[j+1] = aux;
            }   
        }
    }

    printf("\n");

    //Show sorted array
    for(i=0; i<size; i++){
        printf("data[%d] = %d ", i, data[i]);
    }

    //Get Median
    if(size%2==0)
            median = (data[size/2] + data[size/2-1])/2;
        else
            median = data[size/2];

    average /= size;
    printf("\nAverage: %d\n", average);
    printf("Median: %d\n", median);
    

}