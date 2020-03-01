

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 29th, 2019 *
 * pa4: Graph.h                              *
 *********************************************/

//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#pragma once

#include "List.h"

#define INF -1
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

// getSource() 
// Returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called. 
int getSource(Graph G);

// getParent() 
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if 
// BFS() has not yet been called. 
// Precondition 1<= u <= getOrder(G).
int getParent(Graph G, int u);

// getDist() 
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// Precondition 1<= u <= getOrder(G).
int getDist(Graph G, int u);

// getPath() 
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
// value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must
// be called before getPath(). 
// Precondition 1<= u <= getOrder(G). 
void getPath(List L, Graph G, int u);


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

// BFS() 
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly. 
void BFS(Graph G, int s);


/*** Other operations ***/

// printGraph() 
// Prints the adjacency list representation of G to the file pointed to by out. The format of this 
// representation should match the above examples, so all that is required by the client is a 
// single call to printGraph().
void printGraph(FILE* out, Graph G);


