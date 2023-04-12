/**************************
*Reeves Farrell                 
*CPSC 2310 Spring 23
*UserName: jrfarre           
*Instructor:  Dr. Yvon Feaster  
*************************/

#include <stdbool.h>

int** readFile(FILE* fp, int *size);
void printMatrix (int** mat, int num);
int calculateVal(int** mat, int size);
_Bool IsRightDiagonal(int size, int row, int col);
_Bool IsLeftDiagonal(int row, int col);