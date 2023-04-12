/**************************
*Reeves Farrell                 
*CPSC 2310 Spring 23
*UserName: jrfarre           
*Instructor:  Dr. Yvon Feaster  
*************************/

#include <stdio.h>
#include <assert.h>
#include "functions.h"

int main(int argc, char *argv[]) {

    // Creates a file pointer for the input file
    FILE* ptr = NULL;
    ptr = fopen(argv[1], "r");

    // Creates a file pointer for the output file
    FILE* ptx = NULL;
    ptx = fopen(argv[2], "w");

    // Creates a pointer for the head of the list
    node_t *head = NULL;
    
    // Checks to make sure file opened correctly
    // and that the command line arguments worked
    assert(ptr != NULL);
    assert(ptx != NULL);
    assert(argc != 2);
    
    // Creates the linked list from the csv file
    createList(ptr, &head);

    // Prints the list
    printList(ptx, head);

    // Deletes the list
    deleteList(&head);

    fclose(ptx);
    fclose(ptr);

    return 0;
}