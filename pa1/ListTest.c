//-----------------------------------------------------------------------------
// ListTest.c
// A test client for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include"List.h"

int main(int argc, char* argv[]){

   int i;
   List A = newList();
   List B = newList();

   for(i=1; i<=10; i++){
      append(A, i);
      append(B, 11-i);
   }
   FILE* test1 = fopen("test1", "w");
   FILE* test2 = fopen("test2", "w");
   FILE* test3 = fopen("test3", "w");
   FILE* test4 = fopen("test4", "w");
   FILE* test5 = fopen("test5", "w");
   FILE* test6 = fopen("test6", "w");
   printList(test1, A);
   printList(test2, B);
   for(i=1; i<=6; i++){
      append(A, front(B));
      deleteFront(B);
   }
   
   printList(test3, A);
   printList(test4, B);
   printf("\n");

   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(A,A)?"true":"false");

   printList(test5, A);
   printList(test6, B);

   freeList(&A);
   freeList(&B);

   fclose(test1);
   fclose(test2);
   fclose(test3);
   fclose(test4);
   fclose(test5);
   fclose(test6);
   return(0);
}
