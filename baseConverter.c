/*
    Aaron Zajac
    A01023376
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum encoding_enum{INTEGER, CHAR} encoding_type;

typedef union num_union{
    unsigned char c[24];
    int i;
}num_type;

typedef struct conv_struct{
    int base;
    num_type buffer;
}

void base_ten()
