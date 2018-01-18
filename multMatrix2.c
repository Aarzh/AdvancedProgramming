/*
    Aaron Zajac A01023376
*/
#include <stdio.h>
#include <stdlib.h>

/*struct typedef enum matrix{
    int rows;
    int columns;
    float data;
};
*/
int read(float **matrix, const char * filename){
    //static const char filename[] = "matrix_A.txt";
    int rows;
    int columns;
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
      char line [ 128 ]; //its the content of that line in the text
      fscanf(file, "%s", line);
      rows = atoi(line);
      fscanf(file, "%s", line);
      columns = atoi(line);

      for (int i = 0; i < rows; i++) {
          matrix = (float **) malloc(rows*sizeof (float *));
          for (int j = 0; j < columns; j++) {
              matrix = (float **) malloc(columns*sizeof (float *));
          }
      }

      for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
              fscanf(file, "%s", line);
              matrix[i][j] = atof(line);
              printf("%f\n", matrix[i][j]);
          }
      }
      fclose ( file );
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
   }
   return 0;
}
/*int mult(float *matrixA, float *matrixB){

    float matrixC;

    if (matrixA.columns == matrixB.rows) {
        for(int i=0; i<matrixA.rows; i++)
        {
          for(int j=0; j<matrixB.columns; j++)
          {
            matrixC.data[i][j] = 0;
            for(int k = 0; k<columns; k++)
            {
              matrixC.data[i][j] += matrixA.data[i][k] * matrixB.data[k][j];
            }
          }
        }
    }
    return 0;
}*/

int main() {
    float **matrix = NULL;
    read(&matrix, "matrix_A.txt");
    return 0;
}
