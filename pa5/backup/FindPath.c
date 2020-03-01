
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 29th, 2019 *
 * pa4: FindPath.c                           *
 *********************************************/

//-----------------------------------------------------------------------------
// FindPath.c
// Top level client for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

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
  
   fprintf(out, "Adjacency list representation of G:\n");
 
   // read file

   int numbers = 0;
   int a = 0;
   int b = 0;
   List L = newList();
   
   fscanf(in, "%d", &numbers);
   
   Graph G = newGraph(numbers);
   
   fscanf(in, "%d %d", &a, &b);
  
   // read all edges
   while(a != 0){
      addArc(G, a, b);
      fscanf(in, "%d %d", &a, &b);
   }

   printGraph(out, G); // prints all edges
   
   fprintf(out, "\n");

   for(int i = 0; i < numbers; i++){
      append(L, i);
   }
  
   DFS(G, L);

   Graph T = transpose(G);

   DFS(T, L);

/*   moveFront(L);
 
   fprintf(out, "List: %d\n", get(L));

   fprintf(out, "G contains %d strongly connected components:\n", c);

   for(int i = 1; i <= c; i++){
      fprintf(out, "Component %d: \n", i);
      
   }*/

// find number of strongly connected components
     int count = 0;
         for ( int i = 1; i <= getOrder(G); i++){
                 if(getParent(T, i) == NIL)
                         {
                                   count++;
                                             }
                                                 }
//                                                     // print components on reverse
                                                         fprintf(out, "\nG contains %d strongly connected components:\n", count);
                                                             List stack = newList();
                                                                 for (int i = 1; i<= count; i++){
                                                                         fprintf(out, "Component %d:", i);
//
                                                                                 while(getParent(T, back(L)) != NIL){
                                                                                             prepend(stack, back(L));                                                                                                deleteBack(L);
                                                                                                                 }
                                                                                                                         prepend(stack, back(L));
                                                                                                                                 deleteBack(L);
                                                                                                                                         printList(out, stack);
                                                                                                                                                 fprintf(out, "\n");
                                                                                                                                                         clear(stack);
                                                                                                                                                             }


   // close files
   fclose(in);
   fclose(out);
   
   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);
   
   return(0);
}
