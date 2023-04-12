/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#include <stdio.h>
#include "ppm_utils.h"

int main(int argc, char *argv[]) {

    FILE* ptr[TEN];
    FILE* ptx;

    image_t* img[TEN];
    image_t* img3[NINE];
    image_t* img2;
    
    openInputFiles(argv[1], ptr);

    ptx = fopen(argv[2], "wb");

    if (strcmp(argv[1], "average") == 0) {

        for (int i = 0; i < TEN; i++) {

            img[i] = read_ppm(ptr[i]);
        }

        img2 = removeNoiseAverage(img);
    }
    else if (strcmp(argv[1], "median") == 0) {

        for (int i = 0; i < NINE; i++) {

            img3[i] = read_ppm(ptr[i]);
        }

        img2 = removeNoiseMedian(img3);
    }

    write_p6(ptx, img2);

    freeMem(img2);

    closeFiles(ptr, ptx, argv[1]);
    
    return 0;    
}