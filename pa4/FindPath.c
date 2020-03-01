
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
   
   // read file

   int num = 0;
   int a = 0;
   int b = 0;
   int c = 0;
   List temp = newList();
   
   fscanf(in, "%d", &num);
   
   Graph G = newGraph(num);
   
   fscanf(in, "%d %d", &a, &b);
  
   // read all edges
   while(a != 0){
      addEdge(G, a, b);
      fscanf(in, "%d %d", &a, &b);
   }

   printGraph(out, G); // prints all edges

   fscanf(in, "%d %d", &a, &b); // move on from 0 0
  
   // reads and prints all paths requested
   while(a != 0){
      fprintf(out, "\n"); // adds new line
      BFS(G, a);
      c = getDist(G, b);
      fprintf(out, "The distance from %d to %d is ", a, b);
      if(getDist(G, b) != INF){ // is not part of tree
         fprintf(out, "%d\n", c);
      }else{ // is white
         fprintf(out, "infinity\n");
         fprintf(out, "No %d-%d path exists\n", a, b);
         fscanf(in, "%d %d", &a, &b); // reads paths
         continue;
      }
      fprintf(out, "A shortest %d-%d path is: ", a, b);
      getPath(temp, G, b);
      moveFront(temp);
      while(index(temp) != -1){
         fprintf(out, " %d", get(temp));
         moveNext(temp);
      }
      fprintf(out, "\n");
      fscanf(in, "%d %d", &a, &b); // reads paths
      clear(temp);
   }
  
   // close files
   fclose(in);
   fclose(out);
   
   freeGraph(&G);
   freeList(&temp);
   
   return(0);
}
