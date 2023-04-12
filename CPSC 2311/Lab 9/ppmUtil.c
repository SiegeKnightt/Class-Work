/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#include <stdio.h>
#include "ppmUtil.h"

// FILE* points to the input file
// header_t* used to store info read from the input image
// Read in each of the 4 header parts for the ppm image
// Use fscanf when reading
// Read one part of the header then call the function
// to check for comments (as disucssed in class)
void readHeader(FILE* f, header_t* h) {

    // Scans in the magic number for the ppm file
    fscanf(f, "%2s", h->type);
    ckComment(f);

    // Scans in the width
    fscanf(f, "%d\n", &h->width);
    ckComment(f);

    // Scans in the height
    fscanf(f, "%d\n", &h->height);
    ckComment(f);

    // Scans in the max value for rgb
    fscanf(f, "%d\n", &h->maxVal);
    ckComment(f);

    //printf("%s %d %d %d", h->type, h->width, h->height, h->maxVal);
}

// FILE* points to the input file
// header_t contains the info needed to 
// read in the pixels for the image
// Call the funciton allocatePixMemory to allocate memory
// for each of the pixels
// Use fread to read the pixels, storing them in allocated memory
// Return the allocated memory
pixel_t* readPixels(FILE* f, header_t h) {

    pixel_t* pixel;

    pixel = allocatePixMemory(h);

    unsigned char color[3];

    for (int i = 0; i < h.width * h.height; i++) {

        fread(color, sizeof(unsigned char), 3, f);

        pixel[i].r = color[0];

        pixel[i].g = color[1];

        pixel[i].b = color[2];
    }

    return pixel;
}

// FILE* points to the output file
// header_t contains the info needed to write
// the header for the output image
// Use fprintf to write the header info
// to the output file
void writeHeader(FILE* f, header_t h) {

    fprintf(f, "%s\n", h.type);
    fprintf(f, "%d %d\n", h.width, h.height);
    fprintf(f, "%d\n", h.maxVal);
}

// FILE* points to the output file
// pixel_t* contains the pixels read from input image
// header_t contains the header info from input image
// Use fwrite to write the data from input image to output image
void writePixels(FILE* f, pixel_t* p, header_t h) {

    fwrite(p, sizeof(pixel_t), h.width * h.height, f);
}

// FILE* is the input image
// header_t* is the header data of the input image
// Calls readHeader
// Calls readPixels
// Returns the pixel_t pointer created for readPixels
pixel_t* read(FILE* f, header_t* h) {

    readHeader(f, h);

    return readPixels(f, *h);
}

// FILE* represents the output file
// header_t is the header data for the output image
// pixel_t* contains the pixel data to write
// Calls writeHeader;
// Calls writePixels;
void write(FILE* f, header_t h, pixel_t* p) {

    writeHeader(f, h);

    writePixels(f, p, h);
}

// header_t contains the info about the header
// Allocates memory for the pixels of the image
// Returns the allocated memory
pixel_t* allocatePixMemory(header_t h) {

    return (pixel_t*)calloc(h.width * h.height, sizeof(pixel_t*));
}

// pixel_t* is the memory that contains the pixel info
// Gives the memory back to the operating system
void freeMemory(pixel_t* p) {

    free(p);
}

// FILE* points to the input file
// Checks for and ignores the ppm header comments
void ckComment(FILE* f) {

    char comment;

    comment = fgetc(f);

    while (comment == '#' || isspace(comment)) {

        comment = fgetc(f);

        while (comment != '\n' && comment != EOF) {
            
            comment = fgetc(f);
        }

        comment = fgetc(f);
    }

    fseek(f, -1, SEEK_CUR);
}