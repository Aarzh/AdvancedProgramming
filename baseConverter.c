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
}conversion;

void base_conv(char array[24], int b1, int b2)
{
     int r;
     int number;
     int k=0;
     int b=1;
     for(int i=strlen(s)-1; i>=0; --i)
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
     for(int i=index-1;i>=0;i--)
     {
          printf("%c",array[i]);
     }
     printf("\n");

}

int main(){
     char array[24] = "\0";
     int b1 = 0;
     int b2 = 0;
     base_conv(array, b1, b2);
     return 0;
}
