

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 17th, 2019 *
 * pa3: BigIntegerTest.c                     *
 *********************************************/

//-----------------------------------------------------------------------------
// BigIntegerTest.c
// A test client for BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include "List.h"
#include "BigInteger.h"

int main(){
   
   BigInteger A = newBigInteger();
   
   A = stringToBigInteger("123456789");
   
   add(A, A, A);
  
   printBigInteger(stdout, A);

   freeBigInteger(&A);

   BigInteger pA = newBigInteger();
   
   pA = stringToBigInteger("111122223333");
   
   BigInteger pB = stringToBigInteger("111122223333");
   BigInteger pC = newBigInteger();

   multiply(pC, pA, pB);

   printBigInteger(stdout, pC);

   negate(pB);
   
   subtract(pC, pA, pB);

   printBigInteger(stdout, pC);
   
   BigInteger A = stringToBigInteger("161471857301735873015");
   BigInteger B = stringToBigInteger("9351851518401561761573817");
   BigInteger C = newBigInteger();
   BigInteger D;
   BigInteger E;
  
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
  
   D = stringToBigInteger("13");
   E = stringToBigInteger("8");
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
   multiply(D, D, A); // 4th
   multiply(D, D, A); // 5th
   multiply(A, D, A); // 6th
   multiply(E, B, B); // squared
   multiply(E, E, B); // cubed
   multiply(E, E, B); // 4th
   freeBigInteger(&D);
   freeBigInteger(&E);
   D = stringToBigInteger("3");
   E = stringToBigInteger("9");
   multiply(D, A, D);
   multiply(E, B, E);
   add(C, D, E);
   printBigInteger(out, C);
   fprintf(out, "\n");

   freeBigInteger(&A);
   freeBigInteger(&B);
   freeBigInteger(&C);
   freeBigInteger(&D);
   freeBigInteger(&E);
   freeBigInteger(&pA);
   freeBigInteger(&pB);
   freeBigInteger(&pC);
  
   return 1;
}
