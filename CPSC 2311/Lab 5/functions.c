/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
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

        free(temp2);
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

            // Doesn't print invalid dates to the output file
            if (checkInvalidDate(temp)) {

                fprintf(output, "Name:\t%s %s\n", temp->firstName, 
                temp->lastName);
                fprintf(output, "Date of Birth:\t%s %s, %s\n", temp->birth.month, 
                temp->birth.day, temp->birth.year);
                fprintf(output, "Major:\t%s\n", temp->major);
                fprintf(output, "Year:\t%s\n", temp->classStanding);
                fprintf(output, "\n");
            }

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

// Determines if a date is valid or not 
// Returns true if valid, false if not
bool checkInvalidDate(node_t *node) {

    int day = atoi(node->birth.day);
    int month;
    int year = atoi(node->birth.year);

    // Converts the month to an integer
    if (strcmp(node->birth.month, "January") == 0) {

        month = 1;
    }
    if (strcmp(node->birth.month, "February") == 0) {

        month = 2;
    }
    if (strcmp(node->birth.month, "March") == 0) {

        month = 3;
    }
    if (strcmp(node->birth.month, "April") == 0) {

        month = 4;
    }
    if (strcmp(node->birth.month, "May") == 0) {

        month = 5;
    }
    if (strcmp(node->birth.month, "June") == 0) {

        month = 6;
    }
    if (strcmp(node->birth.month, "July") == 0) {

        month = 7;
    }
    if (strcmp(node->birth.month, "August") == 0) {

        month = 8;
    }
    if (strcmp(node->birth.month, "September") == 0) {

        month = 9;
    }
    if (strcmp(node->birth.month, "October") == 0) {

        month = 10;
    }
    if (strcmp(node->birth.month, "November") == 0) {

        month = 11;
    }
    if (strcmp(node->birth.month, "December") == 0) {

        month = 12;
    }

    // Checks for valid month
    if (month < 1 || month > 12) {

        return false;
    }
    
    // Checks for valid day
    if (day < 1 || day > 31) {
        
        return false;
    }

    // Condition for months with 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11) {

        if (day > 30) {

            return false;
        }
    }
    
    // Condition for February
    if (month == 2) {

        // Checks for leap year
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {

            if (day > 29) {

                return false;
            }
        }
        else {
            
            if (day > 28) {

                return false;
            }
        }
    }

    return true;
}

// Merge helper function for mergeSort
node_t* merge(node_t *a, node_t *b, int (*fptr)(node_t*, node_t*)) {
    
    node_t *output = NULL;

    if (a == NULL) {

        return b;
    }

    if (b == NULL) {

        return a;
    }

    // Compares head of each list
    if (fptr(a, b) <= 0) {
        
        output = a;
        output->next = merge(a->next, b, fptr);
    } 
    else {
        
        output = b;
        output->next = merge(a, b->next, fptr);
    }

    return output;
}

// Merge sort algorithm helper function
void mergeSort(node_t **head, int (*fptr)(node_t*, node_t*)) {
    
    node_t *a = *head;
    node_t *b = NULL;

    // Checks for empty or 1 element list
    if (a == NULL || a->next == NULL) {
        
        return;
    }

    // Splits the list
    while (a != NULL) {
        
        a = a->next;

        if (a != NULL) {

            if (b == NULL) {

                b = *head;
            }
            else {

                b = b->next;
            }

            a = a->next;
        }
    }

    a = b->next;
    b->next = NULL;
    b = *head;

    // Sorts each half
    mergeSort(&b, fptr);
    mergeSort(&a, fptr);

    // Merges both halves into one list
    *head = merge(b, a, fptr);
}

// Calls mergeSort to sort the list
void sortList(node_t **head, int (*fptr)(node_t*, node_t*)) {
    
    mergeSort(head, fptr);
}

// Compares last names
int compare_by_lastname(node_t *a, node_t *b) {

    return strcmp(a->lastName, b->lastName);
}

// Compares first names
int compare_by_firstname(node_t *a, node_t *b) {

    return strcmp(a->firstName, b->firstName);
}

int monthConvertor(char month[]) {

    if (strcmp(month, "January") == 0) {
        
        return 1;
    }
    if (strcmp(month, "February") == 0) {
        
        return 2;
    }
    if (strcmp(month, "March") == 0) {
        
        return 3;
    }
    if (strcmp(month, "April") == 0) {
        
        return 4;
    }
    if (strcmp(month, "May") == 0) {

        return 5;
    }
    if (strcmp(month, "June") == 0) {
       
        return 6;
    }
    if (strcmp(month, "July") == 0) {
        
        return 7;
    }
    if (strcmp(month, "August") == 0) {
        
        return 8;
    }
    if (strcmp(month, "September") == 0) {
        
        return 9;
    }
    if (strcmp(month, "October") == 0) {
        
        return 10;
    }
    if (strcmp(month, "November") == 0) {
        
        return 11;
    }
    if (strcmp(month, "December") == 0) {
        
        return 12;
    }
}