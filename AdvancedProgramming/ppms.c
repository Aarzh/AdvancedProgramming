#include "ppms.h"

void allocateMemory(ppm_t * image)
{
    // Allocate the memory for INDEX array
    image->pixels = malloc (image->height * sizeof(pixel_t *));
    // Allocate the memory for all the DATA array
    image->pixels[0] = calloc (image->height * image->width, sizeof(pixel_t));

    // Add the rest of the pointers to the INDEX array
    for (int i=1; i<image->height; i++)
    {
        // Add an offset from the beginning of the DATA array
        image->pixels[i] = image->pixels[0] + image->width * i;
    }
}

void freeMemory(ppm_t * image)
{
    // Free the DATA array
    free (image->pixels[0]);
    // Free the INDEX array
    free (image->pixels);
}

void getAsciiPixels(ppm_t * image, FILE * file_ptr)
{
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            fscanf (file_ptr, "%hu", &image->pixels[r][c].data[R]);
            fscanf (file_ptr, "%hu", &image->pixels[r][c].data[G]);
            fscanf (file_ptr, "%hu", &image->pixels[r][c].data[B]);
        }
    }
}

void putAsciiPixels(const ppm_t * image, FILE * file_ptr){
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            //WRITES EACH PIXEL IN EACH ROW AND COLUMN
            fprintf (file_ptr, "%hu ", image->pixels[r][c].data[R]);
            fprintf (file_ptr, "%hu ", image->pixels[r][c].data[G]);
            fprintf (file_ptr, "%hu\n", image->pixels[r][c].data[B]);
        }
    }
}

void getBinaryPixels(ppm_t * image, FILE * file_ptr)
{
    fread(image->pixels[0], sizeof(pixel_t), image->width * image->height, file_ptr);
}

void putBinaryPixels(const ppm_t * image, FILE * file_ptr)
{
    //WRITE ALL THE DATA IN THE FILE READEN
    fwrite(image->pixels[0], sizeof(pixel_t), image->width * image->height, file_ptr);
}

void readImageFile(char * filename, ppm_t * image){
    FILE* file_ptr = NULL;

    file_ptr = fopen(filename, "r");
    if (!file_ptr) {
        printf("Unable to open the file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fscanf(file_ptr, "%s", image->magic_number);
    fscanf(file_ptr, "%d", &image->width);
    fscanf(file_ptr, "%d", &image->height);
    fscanf(file_ptr, "%d", &image->max_value);

    allocateMemory(image);

    if (!strncmp(image->magic_number, "P3", 3))
    {
        getAsciiPixels(image, file_ptr);
    }
    else if (!strncmp(image->magic_number, "P6", 3))
    {
        getBinaryPixels(image, file_ptr);
    }
    else
    {
        printf("Not a correct PPM format");
    }
}
void writeImageFile(char * filename, const ppm_t * image){

    FILE* file_ptr = NULL;

    file_ptr = fopen(filename, "w");
    if (!file_ptr) {
        printf("Unable to find the file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    //WRITE WITH THE CORRECT FORMAT
    fprintf(file_ptr, "%s\n", image->magic_number);
    fprintf(file_ptr, "%hu\n", image->width);
    fprintf(file_ptr, "%hu\n", image->height);
    fprintf(file_ptr, "%hu\n", image->max_value);
    //IF ITS BINARY OR ASCII
    if (!strncmp(image->magic_number, "P3", 3))
    {
        putAsciiPixels(image, file_ptr);
    }
    else if (!strncmp(image->magic_number, "P6", 3))
    {
        putBinaryPixels(image, file_ptr);
    }
    else
    {
        printf("Not a correct PPM format");
    }
}
void getNegativeImage(ppm_t * image){
    //PRINT THE MAX VALUE AND THE MATRIX
    printf("%hu\n", image->max_value);
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            printf("%hu ", image->pixels[r][c].data[R]);
            printf("%hu ", image->pixels[r][c].data[G]);
            printf("%hu   ", image->pixels[r][c].data[B]);
        }
        printf("\n");
    }
    printf("\n");
    //DECREMENT THE MAX VALUE FORM EACH PIXEL
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            image->pixels[r][c].data[R] = image->max_value - image->pixels[r][c].data[R];
            image->pixels[r][c].data[G] = image->max_value - image->pixels[r][c].data[G];
            image->pixels[r][c].data[B] = image->max_value - image->pixels[r][c].data[B];
        }
    }
    //PRINT THE MAX VALUE AND THE MATRIX
    printf("%hu\n", image->max_value);
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            printf("%hu ", image->pixels[r][c].data[R]);
            printf("%hu ", image->pixels[r][c].data[G]);
            printf("%hu   ", image->pixels[r][c].data[B]);
        }
        printf("\n");
    }
}

void transpose(ppm_t * image){
    short temp;
    //THE SWAP FOR EACH PIXEL IN THE MATRIX
    for (int r=0; r<image->height; r++)
    {
        for (int c=r; c<image->width; c++)
        {
            temp = image->pixels[r][c].data[R];
            image->pixels[r][c].data[R] = image->pixels[c][r].data[R];
            image->pixels[c][r].data[R] = temp;

            temp = image->pixels[r][c].data[G];
            image->pixels[r][c].data[G] = image->pixels[c][r].data[G];
            image->pixels[c][r].data[G] = temp;

            temp = image->pixels[r][c].data[B];
            image->pixels[r][c].data[B] = image->pixels[c][r].data[B];
            image->pixels[c][r].data[B] = temp;
        }
    }
}
void revColumns(ppm_t * image){
    short temp;
    //CHANGE THE COLUMNS TO THE RIGHT POSITION
    for (int r=0; r<image->height; r++)
    {
        for(int c = 0, k = (image->height) - 1; c < k; c++, k--)
        {
            temp = image->pixels[c][r].data[R];
            image->pixels[c][r].data[R] = image->pixels[k][r].data[R];
            image->pixels[k][r].data[R] = temp;

            temp = image->pixels[c][r].data[G];
            image->pixels[c][r].data[G] = image->pixels[k][r].data[G];
            image->pixels[k][r].data[G] = temp;

            temp = image->pixels[c][r].data[B];
            image->pixels[c][r].data[B] = image->pixels[k][r].data[B];
            image->pixels[k][r].data[B] = temp;
        }
    }
}

void rotation(ppm_t * image){
    transpose(image);
    revColumns(image);
}

void rotate(ppm_t * image){
    //FIRST PRINT THE MATRIX
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            printf("%hu ", image->pixels[r][c].data[R]);
            printf("%hu ", image->pixels[r][c].data[G]);
            printf("%hu   ", image->pixels[r][c].data[B]);
        }
        printf("\n");
    }
    printf("\n");
    int grades;
    printf("90 180 270? \n");
    scanf("%i", &grades);
    if (grades == 90) {
        rotation(image);
    }else if(grades == 180){
        rotation(image);
        rotation(image);
    }else if (grades == 270) {
        rotation(image);
        rotation(image);
        rotation(image);
    }else{
        printf("WRONG!\n");
        return;
    }
    printf("\n");
    //PRINT THE MATRIX
    for (int r=0; r<image->height; r++)
    {
        for (int c=0; c<image->width; c++)
        {
            printf("%hu ", image->pixels[r][c].data[R]);
            printf("%hu ", image->pixels[r][c].data[G]);
            printf("%hu   ", image->pixels[r][c].data[B]);
        }
        printf("\n");
    }
}

int main(){
    //MAKE AN IMAGE
    ppm_t * pointer;
    pointer = malloc (sizeof(ppm_t));
    //MAKE A TEMPORAL IMAGE
    readImageFile("imagen.ppm", pointer);
    rotate(pointer);
    //getNegativeImage(pointer);
    writeImageFile("imga.ppm", pointer);
    //free(pointer);
    freeMemory(pointer);
    return 0;
}
