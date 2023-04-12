/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//add birthday struct here
typedef struct birthday {

    char day[50];
    char year[50];
    char month[50];
} birthday;

//add node_t struct here (this struct will represent a node in the
//linked list)
typedef struct node {

    char firstName[50];
    char lastName[50];
    char major[50];
    char classStanding[50];
    birthday birth;
    struct node *next;
} node_t;

//implement these:
void add(node_t **node, node_t **head);
node_t* readNodeInfo(FILE* input);
node_t* createList(FILE*, node_t**);
void printList(FILE*, node_t*);
void printBorder(FILE*);
void deleteList(node_t** );

// New functions for lab 5
_Bool checkInvalidDate(node_t *node);
void sortList(node_t **head, int (*fptr)(node_t*, node_t*));
int compare_by_lastname(node_t *a, node_t *b);
int compare_by_firstname(node_t *a, node_t *b);

// Helper functions
node_t* merge(node_t *a, node_t *b, int (*fptr)(node_t*, node_t*));
void mergeSort(node_t **head, int (*fptr)(node_t*, node_t*));
int monthConvertor(char month[]);

#endif