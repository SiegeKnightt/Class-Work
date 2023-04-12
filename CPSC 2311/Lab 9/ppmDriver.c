/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#include <stdio.h>
#include "ppmUtil.h"

/*
The driver should have minimal amount of code in it.  
It should create and open the needed file pointers. 
It should create a header_t and a pointer of type pixel_t. 
The driver should then call the function read then write.  
The driver should then call the function to 
give the memory back to the OS and close the file pointers.  
*/
int main(int argc, char *argv[]) {

    // Creates a file pointer for the input file
    FILE* ptr = NULL;
    ptr = fopen(argv[1], "rb");

    // Creates a file pointer for the output file
    FILE* ptx = NULL;
    ptx = fopen(argv[2], "wb");

    header_t header;
    pixel_t* pixel;

    pixel = read(ptr, &header);

    write(ptx, header, pixel);
    
    freeMemory(pixel);

    fclose(ptx);
    fclose(ptr);

    return 0;    
}