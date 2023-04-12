/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <assert.h>
#include "ppm_utils.h"

void openInputFiles(char* argv, FILE* inPut[]) {

    int j = 1;

    if (strcmp(argv, "average") == 0) {

        for (int i = 0; i < TEN; i++) {

            char buffer[20];

            sprintf(buffer, "%s_%03d.ppm", argv, j);

            //printf("%s\n", buffer);
        
            inPut[i] = fopen(buffer, "rb");

            // Check if file opened
            assert(inPut[i] != NULL);

            j++;
        }
    }
    else if (strcmp(argv,"median") == 0) {

        for (int i = 0; i < NINE; i++) {

            char buffer[20];

            sprintf(buffer, "%s_%03d.ppm", argv, j);
            
            //printf("%s\n", buffer);
        
            inPut[i] = fopen(buffer, "rb");

            // Check if file opened
            assert(inPut[i] != NULL);

            j++;
        }
    }
}

image_t* removeNoiseAverage(image_t* img[]) {

    image_t* newValues;

    newValues = allocateMemory(&img[0]->header);

    for (int i = 0; i < newValues->header.HEIGHT; i++) {

        for (int j = 0; j < newValues->header.WIDTH; j++) {

            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            // Sum of all pixel values from every image
            for (int k = 0; k < TEN; k++) {

                sumR = sumR + img[k]->pixels[i][j].R;
                sumG = sumG + img[k]->pixels[i][j].G;
                sumB = sumB + img[k]->pixels[i][j].B;
            }

            // Calculate average
            sumR = sumR / TEN;
            sumG = sumG / TEN;
            sumB = sumB / TEN;

            // Type cast to new values
            newValues->pixels[i][j].R = (unsigned char)(sumR);
            newValues->pixels[i][j].G = (unsigned char)(sumG);
            newValues->pixels[i][j].B = (unsigned char)(sumB);
        }
    }

    return newValues;
}

image_t* removeNoiseMedian(image_t* image[]) {

    image_t* newValues;

    newValues = allocateMemory(&image[0]->header);

    for (int i = 0; i < newValues->header.HEIGHT; i++) {

        for (int j = 0; j < newValues->header.WIDTH; j++) {

            unsigned int r[NINE];
            unsigned int g[NINE];
            unsigned int b[NINE];

            for (int k = 0; k < NINE; k++) {

                r[k] = image[k]->pixels[i][j].R;
                g[k] = image[k]->pixels[i][j].G;
                b[k] = image[k]->pixels[i][j].B;
            }

            // Sort the images
            sort(r, NINE);
            sort(g, NINE);
            sort(b, NINE);

            // Type cast to new values
            newValues->pixels[i][j].R = (unsigned char)(r[4]);
            newValues->pixels[i][j].G = (unsigned char)(g[4]);
            newValues->pixels[i][j].B = (unsigned char)(b[4]);
        }
    }

    return newValues;
}

pixel_t readPixel(FILE* in, image_t* img) {

    pixel_t pixel;

    fread(&pixel, sizeof(pixel_t), 1, in);

    if (feof(in)) {

        exit(1);
    }

    return pixel;
}

header_t read_header(FILE* image_file) {

    header_t h;

    // Scans in the magic number
    fscanf(image_file, "%2s", h.MAGIC_NUMBER);

    // Scans in the width
    fscanf(image_file, "%d", &h.WIDTH);

    // Scans in the height
    fscanf(image_file, "%d", &h.HEIGHT);

    // Scans in the max value for rgb
    fscanf(image_file, "%d\n", &h.MAX_VAL);

    //printf("%2s\n%d %d\n%d\n", h.MAGIC_NUMBER, h.WIDTH, h.HEIGHT, h.MAX_VAL);

    return h;
}

image_t* read_ppm(FILE* image_file) {

    image_t* img;
    header_t h;

    h = read_header(image_file);

    img = allocateMemory(&h);

    for (int i = 0; i < img->header.HEIGHT; i++) {

        for (int j = 0; j < img->header.WIDTH; j++) {

            img->pixels[i][j] = readPixel(image_file, img);
        }
    }

    return img;
}

void write_header(FILE* out_file, header_t header) {

    fprintf(out_file, "%2s\n", header.MAGIC_NUMBER);
    fprintf(out_file, "%d %d\n", header.WIDTH, header.HEIGHT);
    fprintf(out_file, "%d\n", header.MAX_VAL);
}

void write_p6(FILE* out_file, image_t* image) {

    header_t h;

    h = image->header;
    
    write_header(out_file, h);
    
    for (int i = 0; i < h.HEIGHT; i++) {

        fwrite(image->pixels[i], sizeof(pixel_t), h.WIDTH, out_file);
    }
}

void sort(unsigned int* arr, int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            if (arr[i] > arr[j]) {

                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void swap(unsigned int* a, unsigned int* b) {

    unsigned int temp = *a;

    *a = *b;

    *b = temp;
}

// 2D Allocation
image_t* allocateMemory(header_t* h) {
    
    image_t* img;

    img = (image_t*)malloc(sizeof(image_t));

    img->header = *h;

    img->pixels = (pixel_t**)malloc(h->HEIGHT * sizeof(pixel_t*));

    for (int i = 0; i < h->HEIGHT; i++) {

        img->pixels[i] = (pixel_t*)malloc(h->WIDTH * sizeof(pixel_t));
    }

    return img;
}

void freeMem(image_t* img) {

    free(img);
}

void closeFiles(FILE* in[], FILE* out, char *argv) {

    if (strcmp(argv, "average") == 0) {

        for (int i = 0; i < TEN; i++) {

            fclose(in[i]);
        }
    }
    else if (strcmp(argv, "median") == 0) {

        for (int i = 0; i < NINE; i++) {

            fclose(in[i]);
        }
    }

    fclose(out);
}