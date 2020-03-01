

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, December 7th, 2019  *
 * pa5: Graph.c                              *
 *********************************************/

//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT (DFS)
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "List.h"
#include "Graph.h"

// structs --------------------------------------------------------------------

// private Graph type
typedef struct GraphObj{
   List* array;
   int order;
   int size;
   int dfsCalled;
   int* color;
   int* parent;
   int* discover;
   int* finish;
} GraphObj;


/*** Constructors-Destructors ***/

// newGraph() 
// Returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n){
   Graph G;
   G = malloc(sizeof(GraphObj));
   G->array = calloc(n, sizeof(List));
   G->color = calloc(n, sizeof(int));
   G->parent = calloc(n, sizeof(int));
   G->discover = calloc(n, sizeof(int));
   G->finish = calloc(n, sizeof(int));
   G->order = n;
   G->size =  NIL;
   G->dfsCalled = NIL;
   for(int i = 0; i < n; i++){
      G->array[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   return(G);
}

// freeGraph() 
// Frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL. 
void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL) { 
      for(int i = 0; i < getOrder(*pG); i++){
         freeList(&(*pG)->array[i]);
      }
      free((*pG)->array);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->discover);
      free((*pG)->finish);
      free(*pG);
      *pG = NULL;
   }
}


/*** Helper functions ***/

// visit()
// Helper function to DFS.
// Returns the current value of time
int visit(Graph G, int x, int time, List L){ // keeping in mind x is actually 1 minus itself
   //x--;
   G->discover[x-1] = ++time; // discover x
   G->color[x-1] = GRAY;
   moveFront(G->array[x-1]);
   while(index(G->array[x-1]) != -1){
      if(G->color[get(G->array[x-1]) - 1] == WHITE){
         G->parent[get(G->array[x-1]) - 1] = x; // need plus 1 as x is 1 minus itself
         time = visit(G, get(G->array[x-1]), time, L);
      }
      moveNext(G->array[x-1]);
   }
   G->color[x-1] = BLACK;
   G->finish[x-1] = ++time; // finish x
   prepend(L, x-1);
   return time;
}


/*** Access functions ***/

// getOrder()
// Returns the order.
int getOrder(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(1);
   }
   return G->order;
}

// getSize() 
// Returns the size.
int getSize(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(1);
   }
   return G->size;
}

// getParent() 
// Returns the parent of vertex u in the BreadthFirst tree created by DFS(), or NIL if 
// DFS() has not yet been called. 
// Precondition 1<= u <= getOrder(G).
int getParent(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) ){
      printf("Graph Error: calling getParent() on inappropriate u\n");
      exit(1);
   }
   if(G->dfsCalled == 1){
      return G->parent[u-1];
   }
   return NIL;
}

// getDiscover() 
// Returns the discovery time of vertex u in the Depth First tree created by DFS(), or UNDEF if 
// DFS() has not yet been called. 
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) ){
      printf("Graph Error: calling getDiscover() on inappropriate vertex\n");
      exit(1);
   }
   if(G->dfsCalled == 1){
      return G->discover[u-1];
   }
   return UNDEF;
}

// getFinish() 
// Returns the finish time of vertex u in the Depth First tree created by DFS(), or UNDEF if 
// DFS() has not yet been called. 
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) ){
      printf("Graph Error: calling getFinish() on inappropriate vertex\n");
      exit(1);
   }
   if(G->dfsCalled == 1){
      return G->finish[u-1];
   }
   return UNDEF;
}


/*** Manipulation procedures ***/

// makeNull() 
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(1);
   }
   G->size =  NIL;
   G->dfsCalled = NIL;
   for(int i = 0; i < G->order; i++){
      clear((G->array)[i]);
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
}

// addEdge() 
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency 
// List of u. Your program is required to maintain these lists in sorted order by increasing labels. 
// Precondition 1<= u <= getOrder(G). 
void addEdge(Graph G, int u, int v){
   if( G==NULL ){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) && ( v < 1 ) && ( u > G->order ) ){
      printf("Graph Error: calling addEdge() on inappropriate u and/or v\n");
      exit(1);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--; // to correct for the double ++ by addArc
}

// addArc() 
// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the 
// adjacency List of v). 
// Precondition 1<= u <= getOrder(G). 
void addArc(Graph G, int u, int v){
   if( G==NULL ){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) && ( v < 1 ) && ( v > G->order ) ){
      printf("Graph Error: calling addArc() on inappropriate u and/or v\n");
      exit(1);
   }
   if(length(G->array[u-1]) == 0){ // aka it is the first node to be added
      append((G->array)[u-1], v);
   }else{ // list is not empty
      moveFront(G->array[u-1]);	
      while(index(G->array[u-1]) != -1){
         if(get(G->array[u-1]) > v){
            insertBefore(G->array[u-1], v);
            break;
         }
         moveNext(G->array[u-1]);
      }
      if(index(G->array[u-1]) == -1){ // v is larger than all current, thus put in back
         append(G->array[u-1], v);
      }
   }
   G->size++;
   G->dfsCalled = NIL;
}

// DFS() 
// Runs the DFS algorithm on the Graph G with list S, setting the color, discovery and finish time, parent,
// and source fields of G accordingly. 
// Precondition: length(S) == n.
void DFS(Graph G, List S){
   if( G==NULL ){
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(1);
   }
   if( S == NULL){
      printf("Graph Error: calling DFS() on NULL List reference\n");
      exit(1);
   }
   if(length(S) != G->order){
      printf("Graph Error: calling DFS() on an inappropriate list\n");
      exit(1);
   }
   int time = 0;
   for(int i = 0; i < G->order; i++){ // reset graph to unread state
      G->color[i] = WHITE; 
      G->parent[i] = NIL;
   }
   List L = newList();
   moveFront(S);
   while(index(S) != -1){
      if(G->color[get(S) - 1] == WHITE){
         time = visit(G, get(S), time, L);
      }
      moveNext(S);
   }
   for(int i = 0; i < G->order; i++){
      deleteBack(S);
   }
   moveFront(L);
   while(index(L) != -1){
      append(S, get(L) + 1); // just needed +1 for get, saved me so much time
      moveNext(L);
   }
   freeList(&L);
   G->dfsCalled = 1;
}


/*** Other operations ***/

// transpose()
// Eeturns a reference to a new graph object representing the transpose of G.
Graph transpose(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(1);
   }
   Graph T = newGraph(G->order);
   for(int i = 0; i < G->order; i++){ // loop through lists
      moveFront(G->array[i]);
      while(index(G->array[i]) != -1){ // loop through verticies
         int x = get(G->array[i]);
         addArc(T, x, i + 1);
         moveNext(G->array[i]);
      }
   }
   return T;
}

// copyGraph()
// Eeturns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(1);
   }
   Graph C = newGraph(G->order);
   for(int i = 0; i <= G->order; i++){ // loop through lists
      moveFront(G->array[i]);
      while(index(G->array[i]) != -1){ // loop through verticies
         int x = get(G->array[i]);
         addArc(C, i, x);
         moveNext(G->array[i]);
      }
   }
   return C;
}

// printGraph() 
// Prints the adjacency list representation of G to the file pointed to by out. The format of this 
// representation should match the above examples, so all that is required by the client is a 
// single call to printGraph().
void printGraph(FILE* out, Graph G){
   if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(1);
   }
   for(int i = 1; i <= G->order; i++){
      fprintf(out, "%d: ", i);
      moveFront(G->array[i-1]);
      if(index(G->array[i-1]) == -1){ // to make sure proper amount of spaces!
         fprintf(out, " ");
      }
      while(index(G->array[i-1]) != -1){
         fprintf(out, "%d", get(G->array[i-1]));
         moveNext(G->array[i-1]);
         if(index(G->array[i-1]) != -1){ // to make sure proper amount of spaces!
            fprintf(out, " ");
         }
      }
      fprintf(out, "\n");
   }
}


