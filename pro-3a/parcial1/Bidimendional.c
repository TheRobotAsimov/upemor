#include <stdio.h>

int main(){
    int row = 3, column = 5;
    float average, averArray[5]={0};
    int array[][5]={
        {1,4,5},
        {6,1,5,6,4},
        {8,9,3,4,7}
    };
    int array2[row][column];

    printf("\n");

    for(int i=0; i<row; i++){
        for(int j=0; j<column; j++){
            printf("array[%d][%d]: ", i, j);
            scanf("%d", &array2[i][j]);
            //          ^
            //Only strings doesn't require '&'
        }
        printf("\n");
    }

    printf("Array:\n\n");

    for(int i=0; i<row; i++){
        for(int j=0; j<column; j++){
            printf("%5d", array2[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for(int i=0; i<column; i++){
        average=0;
        for(int j=0; j<row; j++){
            average+=array2[j][i];

            averArray[i]+=array2[j][i];
        }
        average/=row;
        averArray[i]/=row;
        printf("Average of column %d:%6.2f", i, average);
        printf("\n");
    }

    printf("\n");

    for(int i=0; i<column; i++){
        printf("Average of column %d:%6.2f", i, averArray[i]);
        printf("\n");
    }



    return 0;
}