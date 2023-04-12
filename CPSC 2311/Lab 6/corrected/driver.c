/********************************/
/*Phillip Hedden                *
*CPSC 2310 Spring 23            *
*UserName: pchedde              *
*Email: pchedde@clemson.edu     *
*Instructor:  Dr. Yvon Feaster  */
/********************************/

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[]) 
{
    //Opens input and output files and makes sure they open successfully.
    FILE* input = fopen(argv[1], "r");
        assert(input != NULL); 
    FILE* output = fopen(argv[2], "w+");
        assert(output != NULL);

    assert(argc != 2);
    //Declares nodes for head and head Ptr.
    struct node* head = NULL;
    struct node** headPtr = &head;

    //Calls createList function to create list.
    createList(input, headPtr);

    //If 1 is input, compares first names
    /*if (atoi(argv[3]) == 1) 
    {
        sortList(&head, compare_by_firstname);
    }
    //If 2 is input, compares last names
    if (atoi(argv[3]) == 2) 
    {
        sortList(&head, compare_by_lastname);
    }*/

    //Assigns head equal to headPtr.
    *head = **headPtr;

    //Retrieves list stats.
    list_stats_t data = getListStats(head);


    //Prints out linked list.
    //printList(output, head);
    printStats(output, &data);

    //Deallocates memory from linked list.
    deleteList(headPtr);

    //Closes input and output files.
    fclose(input);
    fclose(output);
    
    return 0;
}
