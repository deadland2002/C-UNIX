#include <stdio.h>
#include <stdlib.h>

// Comparator function to sort the 2D matrix by the second column
int cmpfunc(const void *a, const void *b) {
    const int *arr1 = *(const int **)a;
    const int *arr2 = *(const int **)b;
    if(arr1[1] < arr2[1])
        return -1;
    else if(arr1[1] > arr2[1])
        return 1;
    else{
        if(arr1[2] < arr2[2])
            return -1;
        else
            return 1;
    }
}

int main() {
    int rows, cols=6;

    char headings [6][5] = {"PID","AT","BT","ET","TAT","WT"};

    printf("Enter the number of processes : ");
    scanf("%d", &rows);

    // Dynamically allocate memory for the 2D matrix
    int **matrix = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }

    // Take input for the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(j<3){
                printf("Enter the value of %s : ",headings[j%6]);
                scanf("%d", &matrix[i][j]);
            }else{
                matrix[i][j] = 0;
            }
        }
    }

    // Sort the matrix by the second column using qsort and the cmpfunc comparator function
    qsort(matrix, rows, sizeof(matrix[0]), cmpfunc);

    // Print the sorted matrix
    printf("\nThe sorted matrix is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
