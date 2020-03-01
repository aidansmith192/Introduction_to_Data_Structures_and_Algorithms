

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 29th, 2019 *
 * pa4: Graph.c                              *
 *********************************************/

//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
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
   int source;
   int bfsCalled;
   int* color;
   int* dist;
   int* parent;
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
   G->dist = calloc(n, sizeof(int));
   G->parent = calloc(n, sizeof(int));
   G->order = n;
   G->size =  NIL;
   G->source = NIL;
   G->bfsCalled = NIL;
   for(int i = 0; i < n; i++){
      G->array[i] = newList();
   }
   for(int i = 0; i < n; i++){
      G->color[i] = WHITE;
   }
   for(int i = 0; i < n; i++){
      G->dist[i] = INF;
   }
   for(int i = 0; i < n; i++){
      G->parent[i] = NIL;
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
      free((*pG)->dist);
      free((*pG)->parent);
      free(*pG);
      *pG = NULL;
   }
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

// getSource() 
// Returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called. 
int getSource(Graph G){
   if( G==NULL ){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(1);
   }
   if(G->bfsCalled == 1){
      return G->source;
   }
   return NIL;
}

// getParent() 
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if 
// BFS() has not yet been called. 
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
   if(G->bfsCalled == 1){
      return G->parent[u-1];
   }
   return NIL;
}

// getDist() 
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// Precondition 1<= u <= getOrder(G).
int getDist(Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) ){
      printf("Graph Error: calling getDist() on inappropriate u\n");
      exit(1);
   }
   if(G->bfsCalled == 1){
      return G->dist[u-1];
   }
   return INF;
}

// getPath() 
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
// value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must
// be called before getPath(). 
// Precondition 1<= u <= getOrder(G). 
void getPath(List L, Graph G, int u){
   if( G==NULL ){
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(1);
   }
   if( G->source == NIL ){
      printf("Graph Error: calling getPath() without calling BFS first\n");
      exit(1);
   }
   if( ( u < 1 ) && ( u > G->order ) ){
      printf("Graph Error: calling getPath() on inappropriate u\n");
      exit(1);
   }
   if(G->bfsCalled == 1){
      List temp = newList();
      append(temp, u);
      int d = 0; // the next parent
      int i = u; // the current parent
      while( i != G->source && i != NIL){
         d = G->parent[i-1];
         prepend(temp, d);
         i = d;
      }
      if(i == G->source){ // if u is actually connected to source
         moveFront(temp);
         while(index(temp) != -1){ // since u is connected, append the path
            append(L, get(temp));
            moveNext(temp);
         }
         freeList(&temp);
         return;
      }else{ // if u is disconnected from source
         freeList(&temp); // dont append the path that doesnt even work
      }
   }
   append(L, NIL); // if either path doesnt exist or BFS doesnt exist
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
   G->source = NIL;
   G->bfsCalled = NIL;
   for(int i = 0; i < G->order; i++){
      clear((G->array)[i]);
      G->color[i] = WHITE;
      G->dist[i] = INF;
      G->parent[i] = NIL;
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
   G->bfsCalled = NIL;
}

// BFS() 
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly. 
void BFS(Graph G, int s){
   if( G==NULL ){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(1);
   }
   G->source = s;
   int x = 0;
   List X = NULL;            // the list of the current child vertex, of the source vertex
   for(int i = 0; i < G->order; i++){ // reset graph to unread state
      G->color[i] = WHITE; 
      G->dist[i] = INF;
      G->parent[i] = NIL;
   }
   G->color[s-1] = GRAY; // discover the source s
   G->dist[s-1] = 0;
   G->parent[s-1] = NIL;

   List queue = newList(); // queue
   append(queue, s);
   int y = 0;
   moveFront(queue);
   while(index(queue) != -1){
      x = front(queue);
      deleteFront(queue);
      X = (G->array)[x-1]; // The current parent vertex list
      moveFront(X);
      while(index(X) != -1){
         y = get(X);
         if( G->color[y-1] == WHITE ){ // y is undiscovered
            G->color[y-1] = GRAY; // discover y
            G->dist[y-1] = G->dist[x-1] + 1;
            G->parent[y-1] = x;
            append(queue, y);
         }
         G->color[x-1] = BLACK; // finish �
         moveNext(X);
      }
      moveFront(queue);
   }
   freeList(&queue);
   G->bfsCalled = 1;
}


/*** Other operations ***/

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


