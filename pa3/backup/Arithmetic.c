
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 17th, 2019 *
 * pa3: Arithmetic.c                         *
 *********************************************/

//-----------------------------------------------------------------------------
// Arithmetic.c
// Top level client for BigInteger
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

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
   
   // read file and create Big ints
   int Alength = 0;
   
   fscanf(in, "%d", &Alength);

   char* Astring = calloc(Alength + 2, sizeof(char));
   
   fscanf(in, "%s", Astring);

   int Blength = 0;
   
   fscanf(in, "%d", &Blength);
  
   char* Bstring = calloc(Blength + 2, sizeof(char));
   
   fscanf(in, "%s", Bstring);

   Astring[Alength + 1] = '\0';
   Bstring[Blength + 1] = '\0';

   BigInteger A = stringToBigInteger(Astring);
   BigInteger B = stringToBigInteger(Bstring);
   BigInteger C = newBigInteger();
   BigInteger D;
   BigInteger E;
  
   // printing
     
   printBigInteger(out, A);
   fprintf(out, "\n");
   
   printBigInteger(out, B);
   fprintf(out, "\n");

   add(C, A, B);
   printBigInteger(out, C);
   fprintf(out, "\n");

   subtract(C, A, B);
   printBigInteger(out, C);
   fprintf(out, "\n");
   
   subtract(C, A, A);
   printBigInteger(out, C);
   fprintf(out, "\n");
  
   D = stringToBigInteger("3");
   E = stringToBigInteger("2");
   multiply(D, A, D);
   multiply(E, B, E);
   subtract(C, D, E);
   printBigInteger(out, C);
   fprintf(out, "\n");

   multiply(C, A, B);
   printBigInteger(out, C);
   fprintf(out, "\n");

   multiply(C, A, A);
   printBigInteger(out, C);
   fprintf(out, "\n");

   multiply(C, B, B);
   printBigInteger(out, C);
   fprintf(out, "\n");

   multiply(D, A, A); // squared
   multiply(D, D, A); // cubed
   multiply(A, D, A); // 4th
   multiply(E, B, B); // squared
   multiply(E, E, B); // cubed
   multiply(E, E, B); // 4th
   multiply(B, E, B); // 5th
   freeBigInteger(&D);
   freeBigInteger(&E);
   D = stringToBigInteger("9");
   E = stringToBigInteger("16");
   multiply(D, A, D);
   multiply(E, B, E);
   add(C, D, E);
   printBigInteger(out, C);
   fprintf(out, "\n");

   // close files
   fclose(in);
   fclose(out);
   
   freeBigInteger(&A);
   freeBigInteger(&B);
   freeBigInteger(&C);
   freeBigInteger(&D);
   freeBigInteger(&E);
   
   free(Astring);
   free(Bstring);

   return(0);
}
