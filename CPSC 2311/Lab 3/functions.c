/**************************
*Reeves Farrell                 
*CPSC 2310 Spring 23
*UserName: jrfarre           
*Instructor:  Dr. Yvon Feaster  
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "functions.h"

// Prints the border for the output
void printBorder(FILE* out)
{
    int i = 0;
    for(i = 0; i < 80; i++)
        fprintf(out,"*");
    
    fprintf(out, "\n");
}

// Adds a node to the end of the linked list
// Checks if list is empty first
void add(node_t **node, node_t **head) {

    node_t *temp = NULL;
    temp = (node_t *) malloc(sizeof(node_t));

    // Check for if list is empty
    if (*head == NULL) {

        *head = temp;
        (*head)->next = NULL;
    }
    else {

        (*node)->next = temp;
        temp->next = NULL;
    }

    assert(temp != NULL);

    *node = temp;
}

// Reads the data from the input file
// and returns a pointer to the node
// using scanset conversion
node_t* readNodeInfo(FILE* input) {

    // Creates the node needed for the linked list
    node_t *node = NULL;
    node = (node_t *) malloc(sizeof(node_t));

    // Reads in all the data from the input file
    // using scanset conversion
    fscanf(input, " %[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
        node->lastName, node->firstName, node->birth.month,
        node->birth.day, node->birth.year, node->major,
        node->classStanding);

    assert(node != NULL);

    return node;
}

// Creates the linked list by calling
// readNodeInfo() and add()
// Returns a pointer to the head of the list
node_t* createList(FILE* input, node_t** head) {

    node_t *temp = *head;

    // Creates the linked list
    while (!feof(input)) {

        node_t *temp2 = readNodeInfo(input);
        add(&temp, head);
        *temp = *temp2;
    }

    return *head;
}

// Prints out the linked list
// or prints an error message 
// if the list is empty
/* Example output:
********************************************************************************

List Info:
Name: Eliza Sorber
Date of Birth: March 12, 2002
Major: CS/BS
Year: Junior

Name: Logan Baker
Date of Birth: February 8, 2003
Major: CS/BA
Year: Sophomore

********************************************************************************

AKA:
printBorder()
\n
List Info:\n
Name:\t<firstname> <lastname>\n
Date of Birth:\t<month> <day>, <year>\n
Major:\t<major>\n
Year:\t<class standing>\n
\n
printBorder()
*/
void printList(FILE* output, node_t* head) {

    node_t *temp = head;

    node_t *ptr, *ptr2, *ptr3;
    ptr = head;

    // Removes duplicates if first and last name
    // are the same
    while (ptr != NULL && ptr->next != NULL) {

        ptr2 = ptr;

        while (ptr2->next != NULL) {

            int compare = strcmp(ptr->firstName, ptr2->next->firstName);
            int compare2 = strcmp(ptr->lastName, ptr2->next->lastName);

            if (compare == 0 && compare2 == 0) {

                ptr3 = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(ptr3);
            }
            else {
                
                ptr2 = ptr2->next;
            }
        }

        ptr = ptr->next;
    }

    if (temp == NULL) {

        fprintf(stderr, "LIST IS EMPTY\n");
    }
    else {

        printBorder(output);
        fprintf(output, "\n");
        fprintf(output, "List Info:\n");

       while (temp != NULL) {

            fprintf(output, "Name:\t%s %s\n", temp->firstName, 
            temp->lastName);
            fprintf(output, "Date of Birth:\t%s %s, %s\n", temp->birth.month, 
            temp->birth.day, temp->birth.year);
            fprintf(output, "Major:\t%s\n", temp->major);
            fprintf(output, "Year:\t%s\n", temp->classStanding);
            fprintf(output, "\n");

            temp = temp->next;
        }

        printBorder(output);
    }
}

// Deallocates memory used for the linked list
void deleteList(node_t** head) {

    node_t *temp = *head;
    node_t *temp2;

    assert (temp!= NULL);

    while (temp != NULL) {

        temp2 = temp->next;

        free(temp);

        temp = temp2;
    }

    *head = NULL;
}
