

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 30th, 2019 *
 * pa2: MatrixTest.c                         *
 *********************************************/

//-----------------------------------------------------------------------------
// MatrixTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
     
int main(){
    
   Matrix A = newMatrix(10);
   Matrix B = newMatrix(10);
   Matrix C, D, E, F, G, H;
   
   for(int i = 1; i <= 10; i++){
      changeEntry(A, i, 11 - i, i * 2.0);
      changeEntry(B, 11 - i, i, i * (-1.5));
   }

   printf("NNZ of A: %d, size of A: %d\n", NNZ(A), size(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("NNZ of B: %d, size of B: %d\n", NNZ(B), size(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(-2.9, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");
   
   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("Does A equal H? Algorithm's answer: %s. Correct answer: true.\n", equals(A, H)?"true":"false" );
   printf("Does A equal H? Algorithm's answer: %s. Correct answer: false.\n", equals(A, B)?"true":"false" );
   printf("Does A equal H? Algorithm's answer: %s. Correct answer: true.\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

