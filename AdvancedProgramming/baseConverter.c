/*
Aaron Zajac
A01023376
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum encoding_enum{INTEGER, CHAR} encoding_type;

typedef union num_union{
     unsigned char c[24];
     int i;
}num_type;

typedef struct conv_struct{
     int base;
     num_type buffer;
}conversion;

void base_conv(char array[24], int b1, int b2)
{
     int r;
     int number;
     int k=0;
     int b=1;
     int i;
     for(i = strlen(array)-1; i>=0; i--)
     {
          if(array[i]>='A' && array[i]<='Z')
          {
               number = array[i]-'0'-7;
          }
          else
          {
               number = array[i]-'0';
          }
          k = (number * b) + k;
          b=b*b1;
     }
     int index=0;
     while(k!=0)
     {
          r=k % b2;
          number='0'+r;
          if(number>'9')
          {
               number+=7;
          }
          array[index]=number;
          index++;
          k=k/b2;
     }
     for(i=index-1;i>=0;i--)
     {
          printf("%c",array[i]);
     }
     printf("\n");

}

int main(int argc, char* argv[]){
    char array[24] = "194";
    int b1 = 0;
    int b2 = 0;
    int opt;
    extern char *optarg;
    extern int optind;
    while ((opt = getopt (argc, argv, "i:o:")) != -1)
    {
        switch (opt)
        {
            case 'i':
            b1 = atoi(optarg);
            break;
            case 'o':
            b2 = atoi(optarg);
            break;
        }
    }
    //base_conv(argv[optind], b1, b2);
    base_conv(argv[optind], b1, b2);//doesnt work with the number as parametr
    //you need to put the number in to the array and then pass the array into the function
    return 0;
}
