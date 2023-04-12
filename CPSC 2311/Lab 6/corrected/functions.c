/********************************/
/*Phillip Hedden                *
*CPSC 2310 Spring 23            *
*UserName: pchedde              *
*Email: pchedde@clemson.edu     *
*Instructor:  Dr. Yvon Feaster  */
/********************************/


#include "functions.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//Adds node to linked list.
void add(node_t **nodePtr, node_t **headPtr)
{
    //Makes sure headPtr is not NULL. If it is, sets to nodePtr.
    if (*headPtr == NULL)
    {
        *headPtr = *nodePtr;
        return;
    } 
  
    //Sets current equal to headPtr/
    node_t *current = (*headPtr);

    //Iterates through to the end of linked list.
    while (current != NULL && current->next != NULL) 
    {
        current = current->next;
    }

    //Sets last node to nodePtr.
    current->next = *nodePtr;

}

//Takes in data from input file and returns pointer to populated node.
node_t* readNodeInfo(FILE* input)
{
    //Allocates memory for node_t.
    node_t *newNode = (node_t*) malloc(sizeof(node_t));
    
    //Checks to make sure that memory allocation was successful.
    if (newNode == NULL) 
    {
        return NULL;
    }
    
    //Uses fscan to take in and assign information to node.
    fscanf(input, " %[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", 
        newNode->lastName, 
        newNode->firstName, 
        newNode->birthday.month,
        newNode->birthday.day,
        newNode->birthday.year,
        newNode->major, 
        newNode->classStanding);

    //Creates tail node that's NULL.
    newNode->next = NULL;
    return newNode;
}


//Creates linked list.
node_t* createList(FILE* input, node_t** headPtr)
{
    //Parses through entire file and adds in nodes.
    while (!feof(input)) 
    {
        //Sets node info using readNodeInfo and makes sure it is not NULL.
        node_t *newNode = readNodeInfo(input);
        assert(newNode != NULL);

        //Adds node to the end of the linked list.
        add(&newNode, headPtr);

    }

    return *headPtr;
}

//Prints 80 stars.
void printBorder(FILE* out)
{
    for(int i = 0; i < 80; i++)
        fprintf(out,"*");
    
    fprintf(out, "\n");
}

//Prints out the linked list and checks for duplicates.
void printList(FILE* output, node_t* head)
{
    //Creating node_t pointers.
    node_t *firstPtr;
    node_t *secondPtr; 
    node_t *thirdPtr;
    
    firstPtr = head;

    //Iterates though linked list to check for duplicates.
    while (firstPtr != NULL && firstPtr->next != NULL) 
    {
        secondPtr = firstPtr;

        //Continues until end of list is reached.
        while (secondPtr->next != NULL) 
        {
            //Compares firstPtr info to secondPtr info.
            if (strcmp(firstPtr->lastName, secondPtr->next->lastName) == 0 &&
                strcmp(firstPtr->firstName, secondPtr->next->firstName) == 0) 
            {
                thirdPtr = secondPtr->next;
                
                //Moves next pointer for secondPtr.
                secondPtr->next = secondPtr->next->next;
                
                //Frees up duplicate node.
                free(thirdPtr);
            }
            
            //Else just iterates.
            else 
            {
                secondPtr = secondPtr->next;
            }
        }
        
        //Moves firstPtr to next node.
        firstPtr = firstPtr->next;
    }
    
    //Sets current equal to head pointer.
    node_t *current = head;
    
    //Makes sure that if head node is empty, list is announced empty.
    if (head == NULL) 
    {
        fprintf(stderr, "LIST IS EMPTY\n");
        return;
    }

    //Formatting.
    printBorder(output);
    fprintf(output, "\n");

    //Prints out header for list.
    fprintf(output, "List Info:\n");
    
    //Iterates through list and prints all nodes.
    while (current != NULL) 
    {
        if(checkInvalidDate(current))
        {
            fprintf(output, "Name:\t%s %s\n", 
                    current->firstName, current->lastName);
            fprintf(output, "Date of Birth:\t%s %s, %s\n", 
            current->birthday.month, current->birthday.day, 
            current->birthday.year);
            fprintf(output, "Major:\t%s\n", current->major);
            fprintf(output, "Year:\t%s\n", current->classStanding);
            fprintf(output, "\n");
        }
        
        current = current->next;
    }
    
    printBorder(output);
}

//Deallocates memory used in linked list.
void deleteList(node_t** head)
{
    node_t *current = *head;
    node_t *prev;
    
    //Iterates through list and frees nodes.
    while (current->next != NULL) 
    {
        prev = current;
        current = current->next;
        free(prev);
    }

    //Frees remaining node.
    free(current);
}

//Checks if year is leap year. 
//Returns false if not leap year. True otherwise.
bool isLeapYear(int year) 
{
    //Checks if year is divisible by 4.
    if (year % 4 == 0) 
    {
        //Checks if year is divisible by 100 AND 400.
        if (year % 100 == 0) 
        {
            return year % 400 == 0;
        } 
        
        //If not divisible by 100, not leap year.
        else 
        {
            return true;
        }
    }

    return false;
}

//Makes sure birthday is a valid date.
bool checkInvalidDate(node_t* date) 
{
    //Variables to avoid magic numbers.
    int maxDays = 31;
    int minDays = 0;
    int maxMonths = 12;
    int minMonths = 0;
    int ajsnMaxDays = 30;
    int febMaxDays = 28;
    int febLeapDays = 29;
    
    //Converts day from string to number.
    int day = atoi(date->birthday.day);
    int month;
    
    //Assigns month number to corresponding month.
    if (strcmp(date->birthday.month, "January") == 0) 
    {
        month = 1;
    }

    else if (strcmp(date->birthday.month, "February") == 0) 
    {
        month = 2;
    }
    
    else if (strcmp(date->birthday.month, "March") == 0) 
    {
        month = 3;
    }
    
    else if (strcmp(date->birthday.month, "April") == 0) 
    {
        month = 4;
    }
    
    else if (strcmp(date->birthday.month, "May") == 0) 
    {

        month = 5;
    }
    
    else if (strcmp(date->birthday.month, "June") == 0) 
    {
        month = 6;
    }
    
    else if (strcmp(date->birthday.month, "July") == 0) 
    {
        month = 7;
    }
    
    else if (strcmp(date->birthday.month, "August") == 0) 
    {
        month = 8;
    }
    
    else if (strcmp(date->birthday.month, "September") == 0) 
    {
        month = 9;
    }
    
    else if (strcmp(date->birthday.month, "October") == 0) 
    {
        month = 10;
    }
    
    else if (strcmp(date->birthday.month, "November") == 0) 
    {
        month = 11;
    }
    
    else if (strcmp(date->birthday.month, "December") == 0) 
    {
        month = 12;
    }
    
    
    //Makes sure month falls in valid range.
    if (month < minMonths || month > maxMonths) 
    {
        return false;
    }
    
    //Makes sure day falls in valid range.
    if (day < minDays || day > maxDays) 
    {
        return false;
    }

    //Detects if month is a month containing 30 days.
    if (strcmp(date->birthday.month, "April") == 0 ||
        strcmp(date->birthday.month, "June") == 0 ||
        strcmp(date->birthday.month, "September") == 0 ||
        strcmp(date->birthday.month, "November") == 0) 
    {
        //Indicates input day is more than 30.
        if (day > ajsnMaxDays) 
        {
            return false;
        }
    }
    
    //Detects if February was input.
    else if (strcmp(date->birthday.month, "February") == 0) 
    {
        //Checks to see if year is a leap year.
        if (isLeapYear(atoi(date->birthday.year)) == true) 
        {
            //Checks if input day is more than 29.
            if (day > febLeapDays) 
            {
                return false;
            }
        }
        
        //For if year was not a leap year.
        else 
        {
            //Checks if input day is more than 28.
            if (day > febMaxDays) 
            {
                return false;
            }
        }
    }

    return true;
}


//Method to compare first names.
int compare_by_firstname(node_t* first, node_t* second) 
{
    return strcmp(first->firstName, second->firstName);
}

//Method to compare last names.
int compare_by_lastname(node_t* first, node_t* second) 
{
    return strcmp(first->lastName, second->lastName);
}


//Function to combine the left and right halves of merge sort.
node_t* combineLists(node_t *nodeOne, node_t *nodeTwo, 
int (*compareFunction)(node_t*, node_t*)) 
{
    node_t *newList = NULL;

    //If nodeOne is null, then nothing left to combine.
    if (nodeOne == NULL) 
    {
        return nodeTwo;
    }

    //If nodeTwo is null, then nothing left to combine.
    if (nodeTwo == NULL) 
    {
        return nodeOne;
    }

    //Indicates either strings are the same or nodeTwo is "greater"
    if (compareFunction(nodeOne, nodeTwo) <= 0) 
    {
        //Makes order of newList nodeOne, nodeTwo
        newList = nodeOne;
        newList->next = combineLists(nodeOne->next, nodeTwo, compareFunction);
    }
    
    //Indicates nodeOne is "greater"
    else 
    {
        //Makes order of newList nodeTwo, nodeOne
        newList = nodeTwo;
        newList->next = combineLists(nodeOne, nodeTwo->next, compareFunction);
    }

    return newList;
}

//Method to mergeSort given linked list.
void mergeSort(node_t **head, int (*compareFunction)(node_t*, node_t*)) 
{
    node_t *nodeOne = *head;
    node_t *nodeTwo = NULL;

    //Makes sure list has two or more elements.
    if (nodeOne->next == NULL || nodeOne == NULL) 
    {
        return;
    }

    //Seperates the list into a left and right half.
    while (nodeOne != NULL) 
    {
        //Moves nodeOne.
        nodeOne = nodeOne->next;

        if (nodeOne != NULL) 
        {
            //Makes nodeTwo head of list.
            if (nodeTwo == NULL) 
            {
                nodeTwo = *head;
            }
            
            //Otherwise, moves nodeTwo.
            else 
            {
                nodeTwo = nodeTwo->next;
            }

            //Moves nodeOne.
            nodeOne = nodeOne->next;
        }
    }
    
    //Moves nodeTwo to the head of the linked list.
    nodeOne = nodeTwo->next;
    nodeTwo->next = NULL;
    nodeTwo = *head;
    
    //Sorts right half of list
    mergeSort(&nodeTwo, compareFunction);

    //Sorts left half of list
    mergeSort(&nodeOne, compareFunction);
    
    //Combines both halves back into one final list.
    *head = combineLists(nodeTwo, nodeOne, compareFunction);
}

//Method to call mergeSort in order to sort linked list.
void sortList(node_t **head, int (*compareFunction)(node_t*, node_t*)) 
{
    mergeSort(head, compareFunction);
}

//This function will take in a pointer to the head of your list and 
//return a populated list_stats struct.
list_stats_t getListStats(node_t *head)
{
    //Avoiding magic numbers.
    int numMonths = 12;

    //Creates list of data.
    list_stats_t data;
    bool firstTimeThrough = true;

    //Sets nodes equal to the head of the list.
    data.oldestPerson = head;
    data.youngestPerson = head;

    //Creates currNode to use to iterate through list
    node_t *currNode = head;

    //Checks if list is empty.
    if (head == NULL) 
    {
        return data;
    }
    

    //Fills all month counts with zero.
    for(int i = 0; i < numMonths; i++)
    {
        data.birthdayCount[i] = 0;
    }

    while(currNode != NULL)
    {
        if(firstTimeThrough == true)
        {
            data.youngestPerson = currNode;
            data.oldestPerson = currNode;
            firstTimeThrough = false;
        }
        
        //Checks if year of tempNode is less than youngestPerson year.
        if(strcmp(currNode->birthday.year, 
                  data.youngestPerson->birthday.year) > 0)
        {
            data.youngestPerson = currNode;
        }

        //If years are the same, checks if month of tempNode is less
        //than youngestPerson month.
        else if(strcmp(currNode->birthday.year, 
                       data.youngestPerson->birthday.year) == 0 &&
                convertMonth(currNode->birthday.month) > 
                        convertMonth(data.youngestPerson->birthday.month))
        {
            data.youngestPerson = currNode;
        }

        //If years and months are same, checks if day of tempNode is less
        //than youngestPerson day.
        else if (strcmp(currNode->birthday.year, 
                        data.youngestPerson->birthday.year) == 0 &&
                 convertMonth(currNode->birthday.month) == 
                 convertMonth(data.youngestPerson->birthday.month) &&
                 atoi(currNode->birthday.day) > 
                 atoi(data.youngestPerson->birthday.day))
        {
            data.youngestPerson = currNode;
        }

        //Checks if year of tempNode is greater than oldestPerson year.
        if(strcmp(currNode->birthday.year, 
                  data.oldestPerson->birthday.year) < 0)
        {
            data.oldestPerson = currNode;
        }

        //If years are the same, checks if month of tempNode is greater
        //than oldestPerson month.
        else if(strcmp(currNode->birthday.year, 
                       data.oldestPerson->birthday.year) == 0 &&
                 convertMonth(currNode->birthday.month) < 
                        convertMonth(data.oldestPerson->birthday.month))
        {
            data.oldestPerson = currNode;
        }

        //If years and months are same, checks if day of tempNode is greater
        //than oldestPerson day.
        else if (strcmp(currNode->birthday.year, 
                        data.oldestPerson->birthday.year) == 0 &&
                 convertMonth(currNode->birthday.month) == 
                        convertMonth(data.oldestPerson->birthday.month) &&
                 atoi(currNode->birthday.day) < 
                        atoi(data.oldestPerson->birthday.day))
        {
            data.oldestPerson = currNode;
        }

        //Determines month of current tempNode and increments corresponding
        //location in birthdayCount array.
        if(strcmp(currNode->birthday.month, "January") == 0)
        {
            data.birthdayCount[0]++;
        }

        else if(strcmp(currNode->birthday.month, "February") == 0)
        {
            data.birthdayCount[1]++;
        }

        else if(strcmp(currNode->birthday.month, "March") == 0)
        {
            data.birthdayCount[2]++;
        }

        else if(strcmp(currNode->birthday.month, "April") == 0)
        {
            data.birthdayCount[3]++;
        }

        else if(strcmp(currNode->birthday.month, "May") == 0)
        {
            data.birthdayCount[4]++;
        }

        else if(strcmp(currNode->birthday.month, "June") == 0)
        {
            data.birthdayCount[5]++;
        }

        else if(strcmp(currNode->birthday.month, "July") == 0)
        {
            data.birthdayCount[6]++;
        }

        else if(strcmp(currNode->birthday.month, "August") == 0)
        {
            data.birthdayCount[7]++;
        }

        else if(strcmp(currNode->birthday.month, "September") == 0)
        {
            data.birthdayCount[8]++;
        }

        else if(strcmp(currNode->birthday.month, "October") == 0)
        {
            data.birthdayCount[9]++;
        }

        else if(strcmp(currNode->birthday.month, "November") == 0)
        {
            data.birthdayCount[10]++;
        }

        else if(strcmp(currNode->birthday.month, "December") == 0)
        {
            data.birthdayCount[11]++;
        }

        //Moves tempNode to the next node.
        currNode = currNode->next;
    }

    //Returns the now populated list.
    return data;
}

//This function will take in two parameters, a file pointer pointing at the 
//output file to print to and a pointer to the struct containing your stats.
void printStats(FILE* output, list_stats_t *data)
{
    
    //Makes sure that if head node is empty, list is announced empty.
    if (data->oldestPerson == NULL) 
    {
        fprintf(stderr, "None\n\n");
        return;
    }

    //Formatting.
    printBorder(output);

    //Prints out header for list.
    fprintf(output, "List Statistics:\n");

    //Prints out information for oldestPerson in list.
    fprintf(output, "----------Oldest Person----------\n");
    fprintf(output, "Name:\t%s %s\n", 
            data->oldestPerson->firstName, data->oldestPerson->lastName);
    fprintf(output, "Date of Birth:\t%s %s, %s\n", 
    data->oldestPerson->birthday.month, data->oldestPerson->birthday.day, 
    data->oldestPerson->birthday.year);
    fprintf(output, "Major:\t%s\n", data->oldestPerson->major);
    fprintf(output, "Year:\t%s\n", data->oldestPerson->classStanding);
    fprintf(output, "\n\n");

    //Prints out information for youngestPerson in list.
    fprintf(output, "----------Youngest Person----------\n");
    fprintf(output, "Name:\t%s %s\n", 
            data->youngestPerson->firstName, data->youngestPerson->lastName);
    fprintf(output, "Date of Birth:\t%s %s, %s\n", 
    data->youngestPerson->birthday.month, data->youngestPerson->birthday.day, 
    data->youngestPerson->birthday.year);
    fprintf(output, "Major:\t%s\n", data->youngestPerson->major);
    fprintf(output, "Year:\t%s\n", data->youngestPerson->classStanding);
    fprintf(output, "\n\n");

    //Prints out the birthdayCount array.
    fprintf(output, "----------Birthday Counts----------\n");
    fprintf(output, "January: %d\n", data->birthdayCount[0]);
    fprintf(output, "February: %d\n", data->birthdayCount[1]);
    fprintf(output, "March: %d\n", data->birthdayCount[2]);
    fprintf(output, "April: %d\n", data->birthdayCount[3]);
    fprintf(output, "May: %d\n", data->birthdayCount[4]);
    fprintf(output, "June: %d\n", data->birthdayCount[5]);
    fprintf(output, "July: %d\n", data->birthdayCount[6]);
    fprintf(output, "August: %d\n", data->birthdayCount[7]);
    fprintf(output, "September: %d\n", data->birthdayCount[8]);
    fprintf(output, "October: %d\n", data->birthdayCount[9]);
    fprintf(output, "November: %d\n", data->birthdayCount[10]);
    fprintf(output, "December: %d\n", data->birthdayCount[11]);

    //Prints star border.
    printBorder(output);
}

int convertMonth(char month[])
{
    //Assigns month number to corresponding month.
    if (strcmp(month, "January") == 0) 
    {
        return 1;
    }

    else if (strcmp(month, "February") == 0) 
    {
        return 2;
    }
    
    else if (strcmp(month, "March") == 0) 
    {
        return 3;
    }
    
    else if (strcmp(month, "April") == 0) 
    {
        return 4;
    }
    
    else if (strcmp(month, "May") == 0) 
    {

        return 5;
    }
    
    else if (strcmp(month, "June") == 0) 
    {
        return 6;
    }
    
    else if (strcmp(month, "July") == 0) 
    {
        return 7;
    }
    
    else if (strcmp(month, "August") == 0) 
    {
        return 8;
    }
    
    else if (strcmp(month, "September") == 0) 
    {
        return 9;
    }
    
    else if (strcmp(month, "October") == 0) 
    {
        return 10;
    }
    
    else if (strcmp(month, "November") == 0) 
    {
        return 11;
    }
    
    else if (strcmp(month, "December") == 0) 
    {
        return 12;
    }
}
