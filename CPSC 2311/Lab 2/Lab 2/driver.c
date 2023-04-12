/*************************
*Reeves Farrell
*Phillip Hedden
*CPSC 2311 005
*jrfarre@g.clemson.edu
*************************/

#include <stdio.h>
#include ".\src\functions.h"

int main(int argc, char* argv[]) {
    
    // Declares a file pointer
    FILE *fp;

    // Creates an output file
    FILE *fx = fopen("output.txt", "w");

    // Opens the command line argument
    fp = fopen(argv[1], "r");

    // Counts the number of sentences in the file
    numSentences(fp, fx);

    // Moves the file pointer to the beginning
    fseek(fp, 0, SEEK_SET);

    // Counts the number of words in the file
    numWords(fp, fx);

    // Closes the files
    fclose(fp);
    fclose(fx);

    return 0;
}