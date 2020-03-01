

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 29th, 2019 *
 * pa4: GraphTest.c                          *
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
   printf("getSource: %d, expected value: %d\n", getSource(G), NIL);
   printf("getParent: %d, expected value: %d\n", getParent(G, n/3), NIL);
   printf("getDist: %d, expected value: %d\n", getDist(G, n/3), INF);
   
   BFS(G, n/3);

   printf("getSource: %d, expected value: %d\n", getSource(G), n/3);
   printf("getParent: %d, expected value: %d\n", getParent(G, n/33), NIL);
   printf("getDist: %d, expected value: %d\n", getDist(G, n/33), INF);
   
   getPath(L, G, n/3 - 1);
   printf("Path: ");
   printList(stdout, L);
   printf(" expected path: 33 32\n");

   // Print adjacency list representation of G
   printGraph(stdout, G);

   makeNull(G);

   printf("getOrder: %d, expected value: %d\n", getOrder(G), n);
   printf("getSize: %d, expected value: %d\n", getSize(G), NIL);
   printf("getSource: %d, expected value: %d\n", getSource(G), NIL);
   printf("getParent: %d, expected value: %d\n", getParent(G, n/3), NIL);
   printf("getDist: %d, expected value: %d\n", getDist(G, n/3), INF);

   // Free objects 
   freeList(&L);
   freeGraph(&G);

   return(0);
}
