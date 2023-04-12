/**************************
*Reeves Farrell                 
*CPSC 2310 Spring 23
*UserName: jrfarre           
*Instructor:  Dr. Yvon Feaster  
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int** readFile(FILE* fp, int *size) {

    fscanf(fp, "%d", size);

    int num = *size;

    int index = 0;
    
    int** mat = (int**)malloc(num * sizeof(int*));

    for(index = 0; index < num; index++) {

        mat[index] = (int*)malloc(num * sizeof(int*)); 
    }

    int row = 0; 
    int col = 0;

    for(row = 0; row < num; row++) {

        for(col = 0; col < num; col++) {
            
            fscanf(fp, "%d", &mat[row][col]);
        }
    }

    return mat;
}


void printMatrix (int** mat, int num) {

    int row = 0; 
    int col = 0;

    for(row = 0; row < num; row++) {

        for(col = 0; col < num; col++) {

            printf("%.2d\t", mat[row][col]);
        }

        printf("\n");
    }
}

// Returns true if the element is part of the right diag
_Bool isRightDiagonal(int size, int row, int col) {

    return (size - 1 - col) == row ? true : false; 
}

// Returns true if the element is part of the left diag
_Bool isLeftDiagonal(int row, int col) {


    return (row == col) ? true : false;
}

// Returns total of all values in the matrix except
// values on the left and right diagonals
int calculateVal(int **mat, int size) {

    int total;
    total = 0;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            if (isRightDiagonal(size, i, j) || isLeftDiagonal(i, j)) {

                continue;
            }
            else if (isRightDiagonal(size, i, j) && isLeftDiagonal(i, j)) {

                continue;
            }

            total = total + mat[i][j];
        }
    }

    return total;
}