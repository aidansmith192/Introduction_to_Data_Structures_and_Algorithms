

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 30th, 2019 *
 * pa2: ListTest.c                           *
 *********************************************/

//-----------------------------------------------------------------------------
// ListTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include"List.h"

int main(int argc, char* argv[]){

   List A = newList();
   List B = newList();

   for(int i=1; i<=10;i++){
      append(A, &i);
      prepend(B, &i);
   }

   prepend(A, front(B));
   append(B, back(A));
   
   moveFront(A);
   moveBack(B);
   
   prepend(A, get(B));
   append(B, get(A));
   
   printf("length of A: %d, length of B: %d, index of A: %d, index of B: %d\n", length(A), length(B), index(A), index(B));
   
   moveNext(A);
   movePrev(B);

   printf("length of A: %d, length of B: %d, index of A: %d, index of B: %d\n", length(A), length(B), index(A), index(B));

   delete(A);
   delete(B);

   deleteFront(A);
   deleteBack(B);

   printf("length of A: %d, length of B: %d, index of A: %d, index of B: %d\n", length(A), length(B), index(A), index(B));
   
   clear(A);
   clear(B);

   printf("length of A: %d, length of B: %d, index of A: %d, index of B: %d\n", length(A), length(B), index(A), index(B));

   freeList(&A);
   freeList(&B);
   
   return(0);
}
