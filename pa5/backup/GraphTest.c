

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, December 7th, 2019  *
 * pa5: GraphTest.c                          *
 *********************************************/

//-----------------------------------------------------------------------------
// GraphTest.c
// Test file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   
   Graph G = NULL;
   List L = newList();
   int n = 99;

   List temp = newList();
   for(int i = 0; i < n; i++){
      append(temp, i);
   }

   // Build graph G 
   G = newGraph(n);

   printf("getOrder: %d, expected value: %d\n", getOrder(G), n);
   printf("getSize: %d, expected value: %d\n", getSize(G), NIL);
   
   // add edges for graph
   for(int i=1; i<n; i++){
      if( i%3==0 ) addEdge(G, i, i-1);
      if( i%7==0 ) addArc(G, i-2, i+3);
   }

   printf("getSize: %d, expected value: %d\n", getSize(G), n/3 + n/7 - 1);
   printf("getParent: %d, expected value: %d\n", getParent(G, n/3), NIL);
   
   DFS(G, temp);

   printf("getSource: %d, expected value: %d\n", getSource(G), n/3);
   printf("getParent: %d, expected value: %d\n", getParent(G, n/33), NIL);
   printf("getDiscover: %d, expected value %d\N", getDiscover(G, n/3), 33);
   printf("getFinish: %d, expected value %d\N", getFinish(G, n/3), 33);
   
   // Print adjacency list representation of G
   printGraph(stdout, G);

   makeNull(G);

   printf("getOrder: %d, expected value: %d\n", getOrder(G), n);
   printf("getSize: %d, expected value: %d\n", getSize(G), NIL);
   printf("getParent: %d, expected value: %d\n", getParent(G, n/3), NIL);

   Graph T = transpose(G);

   // Free objects 
   freeList(&L);
   freeGraph(&G);
   freeGraph(&T);
   freeList(&temp);

   return(0);
}
