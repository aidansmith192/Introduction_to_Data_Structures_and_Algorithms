
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, December 7th, 2019  *
 * pa5: FindComponents.c                     *
 *********************************************/

//-----------------------------------------------------------------------------
// FindComponents.c
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
  
   // First part printing
   
   fprintf(out, "Adjacency list representation of G:\n");
 
   // read file
   int num = 0;
   int a = 0;
   int b = 0;
   int c = 0;
   int l = 0;
   List L = newList();
   List* temp;
   
   fscanf(in, "%d", &num); // number of verticies
   
   Graph G = newGraph(num);
   
   fscanf(in, "%d %d", &a, &b);
  
   // read all edges
   while(a != 0){ // when a & b = 0, stop reading
      addArc(G, a, b);
      fscanf(in, "%d %d", &a, &b);
   }

   printGraph(out, G); // prints all edges
   
   // Part 2 of printing
   
   fprintf(out, "\n\n");
   
   for(int i = 0; i < num; i++){ // append all of the numbers to the list initially
      append(L, i);
   }
  
   DFS(G, L);

   Graph T = transpose(G);

   DFS(T, L);

   moveFront(L); // finds number of strongly connected components
   while(index(L) != -1){
      if(getParent(T, get(L)) == NIL){
         c++;
      }
      moveNext(L);
   }
   l = c;

   fprintf(out, "G contains %d strongly connected components:", c);

   temp = calloc(c, sizeof(List)); // array of lists, each used as a stack for each SCC 
   for(int i = 0; i < c; i++){
      temp[i] = newList();
   }

   moveFront(L); // fill the stacks
   while(index(L) != -1){
      if(getParent(T, get(L)) == NIL){
         l--;
      }
      append(temp[l], get(L));
      moveNext(L);
   }
 
   for(int i = 0; i < c; i++){ // printing components
      fprintf(out, "\n");
      fprintf(out, "Component %d: ", i + 1);
      printList(out, temp[i]);
   }
   
   // close files
   fclose(in);
   fclose(out);
   
   // free variables
   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);
   for(int i = 0; i < c; i++){
      freeList(&(temp[i]));
   }

   return(0);
}
