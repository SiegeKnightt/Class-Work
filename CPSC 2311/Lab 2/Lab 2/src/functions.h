/*************************
*Reeves Farrell
*Phillip Hedden
*CPSC 2311 005
*jrfarre@g.clemson.edu
*************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>

// Function prototypes

/* Prototype for numSentences:
* FILE* in is the input file pointer
* to read the file.
* FILE* out is the file pointer for
* the output file where the number
* of sentences going.
* This function reads an input file
* from the command line and counts
* the number of sentences present
* and outputs the number of 
* sentences to a new file.
* The funtion does not return anything
* as it is a void funtion.
*/
void numSentences(FILE* in, FILE* out);

/* Prototype for numWords:
* FILE* in is the input file pointer
* to read the file.
* FILE* out is the file pointer for
* the output file where the number
* of words going.
* This function reads an input file
* from the command line and counts
* the number of words present
* and outputs the number of 
* words to a new file.
* The funtion does not return anything
* as it is a void funtion.
*/
void numWords(FILE* in, FILE* out);

#endif