
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 30th, 2019 *
 * pa2: Sparse.c                             *
 *********************************************/

//-----------------------------------------------------------------------------
// Sparse.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"

#define MAX_LEN 10000

int main(int argc, char * argv[]){

   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   // read file and create matricies
   int i = 0;
   int j = 0;
   int n = 0;
   int a = 0;
   int b = 0;
   double x = 0;
   
   fscanf(in, "%d %d %d", &n, &a, &b);

   Matrix A = newMatrix(n);

   for(int k = 0; k < a; k++){
      fscanf(in, "%d %d %lf", &i, &j, &x);
      changeEntry(A, i, j, x);
   }

   Matrix B = newMatrix(n);

   for(int k = 0; k < b; k++){
      fscanf(in, "%d %d %lf", &i, &j, &x);
      changeEntry(B, i, j, x);
   }
   // printing
   fprintf(out, "A has %d non-zero entries:\n", a);
   printMatrix(out, A);
   fprintf(out, "\n");

   fprintf(out, "B has %d non-zero entries:\n", b);
   printMatrix(out, B);
   fprintf(out, "\n");

   fprintf(out, "(1.5)*A =\n");
   Matrix C = scalarMult(1.5, A);
   printMatrix(out, C);
   fprintf(out, "\n");

   fprintf(out, "A+B =\n");
   Matrix D = sum(A, B);
   printMatrix(out, D);
   fprintf(out, "\n");

   fprintf(out, "A+A =\n");
   Matrix E = sum(A, A);
   printMatrix(out, E);
   fprintf(out, "\n");
   
   fprintf(out, "B-A =\n");
   Matrix F = diff(B, A);
   printMatrix(out, F);
   fprintf(out, "\n");
   
   fprintf(out, "A-A =\n");
   Matrix G = diff(A, A);
   printMatrix(out, G);
   fprintf(out, "\n");

   fprintf(out, "Transpose(A) =\n");
   Matrix H = transpose(A);
   printMatrix(out, H);
   fprintf(out, "\n");

   fprintf(out, "A*B =\n");
   Matrix I = product(A, B);
   printMatrix(out, I);
   fprintf(out, "\n");

   fprintf(out, "B*B =\n");
   Matrix J = product(B, B);
   printMatrix(out, J);

   // close files
   fclose(in);
   fclose(out);
   
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);

   return(0);
}
