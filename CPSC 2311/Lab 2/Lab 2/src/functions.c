/*************************
*Reeves Farrell
*Phillip Hedden
*CPSC 2311 005
*jrfarre@g.clemson.edu
*************************/

#include <stdio.h>
#include "functions.h"

void numSentences(FILE* in, FILE* out) {
    
    int count = 0;
    char c = fgetc(in);
    char prevC = c;

    // Loops through file by reading each character
    while (c != EOF) {
        
        // Sets position of c
        c = fgetc(in);

        // Checks if character is some punctuation
        // If so, increments count by 1
        // Checks for double punctuation
        if (c == '.' && prevC != '.') {
            
            ++count;
        }
        else if (c == '?' && prevC != '?') {

            ++count;
        }
        else if (c == '!' && prevC != '!') {

            ++count;
        }

        // Sets position of previous c
        prevC = c;
    }

    // Writes number of sentences to the output file
    fprintf(out, "Total number of sentences: %d\n", count);
}

void numWords(FILE* in, FILE* out) {
    
    int count = 0;
    char c = fgetc(in);

    // Loops through file by reading each character
    while (c != EOF) {

        // Sets position of c
        c = fgetc(in);
        
        // Checks if character is a space or newline
        // If so, increments count by 1
        if (c == ' ' || c == '\n') {
            ++count;
        }
    }

    // Writes number of characters to the output file
    fprintf(out, "Total number of words: %d", count + 1);
}