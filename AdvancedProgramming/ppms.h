#ifndef PPMS_H
#define PPMS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assign constants to the colors
typedef enum color_enum {R, G, B} color_t;

// Structure to store a single pixel
typedef struct pixel_struct {
    /*
    unsigned short red;
    unsigned short green;
    unsigned short blue;
    */
    unsigned short data[3];
} pixel_t;

// Structure for the PPM image
typedef struct ppm_struct {
    char magic_number[3];
    int width;
    int height;
    int max_value;
    pixel_t ** pixels;
} ppm_t;

///// FUNCTION DECLARATIONS

void allocateMemory(ppm_t * image);
void freeMemory(ppm_t * image);
void getAsciiPixels(ppm_t * image, FILE * file_ptr);
void putAsciiPixels(ppm_t * image, FILE * file_ptr);
void getBinaryPixels(ppm_t * image, FILE * file_ptr);
void putBinaryPixels(ppm_t * image, FILE * file_ptr);
void readImageFile(char * filename, ppm_t * image);
void writeImageFile(char * filename, const ppm_t * image);
void getNegativeImage(ppm_t * image);
void swap(ppm_t * first, ppm_t * second , ppm_t * temp);
void rotate90(ppm_t * image, ppm_t * temp);

#endif  /* NOT PPMS_H */
