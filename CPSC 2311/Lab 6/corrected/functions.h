/********************************/
/*Phillip Hedden                *
*CPSC 2310 Spring 23            *
*UserName: pchedde              *
*Email: pchedde@clemson.edu     *
*Instructor:  Dr. Yvon Feaster  */
/********************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>


//Struct that defines all of the student info for their birthdays.
typedef struct birthday 
{
  char day[50];
  char month[50];
  char year[50];
} birthday_t;


//Struct that defines all of student info as well as the *next pointer
// and birthday struct(above).
typedef struct node 
{
  char firstName[50];
  char lastName[50];
  char major[50];
  char classStanding[50];
  birthday_t birthday;
  struct node *next;
  struct node *data;
} node_t;

//Struct creates node pointers for the youngest and oldest person
//as well as an integer array for the number of birthdays per month.
typedef struct list_stats
{
  struct node *oldestPerson;
  struct node *youngestPerson;
  int birthdayCount[12];

} list_stats_t;

/* Parameters: **node - node_t node for storing student information.
 *             **head - node_t node at the head of the linked list.
 * Return:     No return.
 * This function adds nodes to the end of the linked list.
 */

void add(node_t **node, node_t **head);

/* Parameters: input - FILE* pointer to the input file containing student
 *                     information.
 * Return:        newNode - node_t pointer to populated node.
 * This function takes in data from the input file and inserts it into
 * newNode.
 */

node_t* readNodeInfo(FILE* input);

/* Parameters: input - FILE* pointer to the input file containing student
 *                     information.
 *             headPtr - node_t double pointer to a pointer pointing to
 *                       the head of the linked list.
 * Return:     headPtr - node_t double pointer to a pointer pointing to
 *                       the new head of the linked list.
 * This function creates the linked list and calls readNodeInfo()
 * and add().
 */

node_t* createList(FILE* input, node_t**);

/* Parameters: output - FILE* pointer to the output file.
 *             head - node_t pointer to the head of the linked list.
 * Return:     No return.
 * This function prints out all of the nodes of the linked list.
 */

void printList(FILE* ouput, node_t*);

/* Parameters: output - FILE* pointer to the output file.
 * Return:     No return.
 * This function prints a border of 80 stars.
 */

void printBorder(FILE* output);

/* Parameters: headPtr - node_t double pointer to a pointer pointing to
 *                       the head of the linked list.
 * Return:     No return.
 * This function deallocates all of the memory in the linked list.
 */

void deleteList(node_t** headPtr);

/* Parameters: year - integer containing year of birthday.
 *
 * Return: Returns true if not a leap year. Returns false otherwise.
 * 
 * This function takes in an integer for the year and checks to see if
 * year was a leap year.
 */
bool isLeapYear(int);

/* Parameters: node - pointer to node that should contain a date.
 *
 * Return:
 * 
 * This function takes in a node ptr and checks 
 * that the node being pointed contains a valid date.
 */
bool checkInvalidDate(node_t *node);

/* Parameters: head - double pointer to the head of the linked list
 *             comp - function pointer to the compare function to use in sort
 *
 * Return: No return.
 * 
 * This function uses a function pointer to the compare 
 * function to use in the sort.
 */
void sortList(node_t **head, int (*comp)(node_t*, node_t*));

/* Parameters: a - node pointer to first node to compare last name
 *             b - node pointer to second node to compare last name
 *
 * Return: 
 * 
 * This function compares two nodes by last name.
 */
int compare_by_lastname(node_t *a, node_t *b);

/* Parameters: a - node pointer to first node to compare first name
 *             b - node pointer to second node to compare first name
 *
 * Return:
 * 
 * This function compares two nodes by first name.
 */
int compare_by_firstname(node_t *a, node_t *b);

/* Parameters: head - double pointer to head of linked list
 *             CompareFunction - function pointer to the compare function.
 *
 * Return:
 * 
 * This function separates list into two halves and calls combineLists()
 * to help sort and rearrange them.
 */
void mergeSort(node_t **head, int (*CompareFunction)(node_t*, node_t*));
 
 /* Parameters: nodeOne - pointer to first input node
 *              nodeTwo - pointer to second input node
 *             CompareFunction - function pointer to the compare function.
 *
 * Return: newList - pointer to updated order of nodes
 * 
 * This is a helper function to mergeSort that rearranges order of nodes
 * and combines halves back into a list.
 */
node_t* combineLists(node_t *nodeOne, node_t *nodeTwo, 
                    int (*CompareFunction)(node_t*, node_t*));

/*
* typedef declaration for function pointer pointing to compareNames function.
*/
typedef int (*CompareFunction)(node_t* nodeOne, node_t* nodeTwo);

/* Parameters: head - node_t pointer to the head of the list
 *
 * Return: Populated list_stats struct
 * 
 * This function will take in a pointer to the head of the list and return a populated list_stats
 * struct.
 */
list_stats_t getListStats(node_t *head);

/* Parameters:  output - pointer to the output 
 *              list_stats_t - pointer to the struct containing student stats.
 *
 * Return:
 * 
 * Prints out list statistics of oldest person, youngest person, and birthday counts.
 */
void printStats(FILE* output, list_stats_t *);

#endif