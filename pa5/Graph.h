

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, December 7th, 2019  *
 * pa5: Graph.h                              *
 *********************************************/

//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#pragma once

#include "List.h"

#define UNDEF -1
#define NIL 0

#define BLACK 1
#define GRAY 0
#define WHITE -1

// Exported type -------------------------------------------------------------
// BigInteger reference 
typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/

// newGraph() 
// Returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n);

// freeGraph() 
// Frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL. 
void freeGraph(Graph* pG);


/*** Access functions ***/

// getOrder()
// Returns the order.
int getOrder(Graph G);

// getSize() 
// Returns the size.
int getSize(Graph G);

// getParent() 
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if 
// BFS() has not yet been called. 
// Precondition 1<= u <= getOrder(G).
int getParent(Graph G, int u);

// getDiscover() 
// Returns the discovery time of vertex u in the Depth First tree created by DFS(), or UNDEF if 
// DFS() has not yet been called. 
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); 

// getFinish() 
// Returns the finish time of vertex u in the Depth First tree created by DFS(), or UNDEF if 
// DFS() has not yet been called. 
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); 


/*** Manipulation procedures ***/

// makeNull() 
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

// addEdge() 
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency 
// List of u. Your program is required to maintain these lists in sorted order by increasing labels. 
// Precondition 1<= u <= getOrder(G). 
void addEdge(Graph G, int u, int v);

// addArc() 
// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the 
// adjacency List of v). 
// Precondition 1<= u <= getOrder(G). 
void addArc(Graph G, int u, int v);

// DFS() 
// Runs the DFS algorithm on the Graph G with setting the color, discover and finish times, parent,
// and source fields of G accordingly. 
void DFS(Graph G, List S);


/*** Other operations ***/

// transpose()
// Eeturns a reference to a new graph object representing the transpose of G.
Graph transpose(Graph G);

// copyGraph()
// Eeturns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G);

// printGraph() 
// Prints the adjacency list representation of G to the file pointed to by out. The format of this 
// representation should match the above examples, so all that is required by the client is a 
// single call to printGraph().
void printGraph(FILE* out, Graph G);


