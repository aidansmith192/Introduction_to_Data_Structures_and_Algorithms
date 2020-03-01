
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 30th, 2019 *
 * pa2: List.c                               *
 *********************************************/

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   void* data; // Entry object
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while(length(*pL) > 0) { 
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of Q.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->index);
}

// front()
// Returns the value at the front of L.
// Pre: length()>0
void* front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns back element of L. 
// Pre: length()>0
void* back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L. 
// Pre: length()>0, index()>=0
void* get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling get() on an empty List\n");
      exit(1);
   }
   if(L->cursor == NULL){
      printf("List Error: calling get() on a NULL cursor\n");
      exit(1);
   }
   return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L){
   if( L==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   while(L->front != NULL){
      deleteFront(L);
   }
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(length(L) > 0){
      L->cursor = L->front;
      L->index = 0;
   }
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
//otherwise does nothing.
void moveBack(List L){
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}

// movePrev()
// If cursor is defined and not at front, move cursor one 
// step toward the front of L; if cursor is defined and at 
// front, cursor becomes undefined; if cursor is undefined 
// do nothing
void movePrev(List L){
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->index == 0){
      L->cursor = NULL;
      L->index = -1;
   }
   else if(L->index > 0){
      L->cursor = L->cursor->prev;
      L->index--;
   }
}

// moveNext()
// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
void moveNext(List L){
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->index == L->length - 1){
      L->cursor = NULL;
      L->index = -1;
   }
   else if((L->index < L->length - 1) && (L->index >= 0)){
      L->cursor = L->cursor->next;
      L->index++;
   }
}

// prepend()
// Insert new element into L. If L is non-empty, 
//  insertion takes place before front element.
void prepend(List L, void* data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0 ) { 
      L->front = L->back = N; 
   }else{ 
      N->next = L->front;
      L->front->prev = N; 
      L->front = N; 
   }
   L->length++;
   if(L->index != -1){
      L->index++;
   }
}

// append()
// Insert new element into L. If L is non-empty, 
// insertion takes place after back element.
void append(List L, void* data)
{
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0 ) { 
      L->front = L->back = N; 
   }else{ 
      N->prev = L->back;
      L->back->next = N; 
      L->back = N; 
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, void* data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling insetBefore() on an empty List\n");
      exit(1);
   }
   if(L->cursor == NULL){
      printf("List Error: calling insertBefore() on a NULL cursor\n");
      exit(1);
   }
   N->next = L->cursor;
   if(L->cursor->prev != NULL){
      L->cursor->prev->next = N;
      N->prev = L->cursor->prev;
   }else{
      L->front = N;
   }
   L->cursor->prev = N; 
   L->length++;
   L->index++;
}

// insertAfter()
// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, void* data){
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(1);
   }
   if(L->cursor == NULL){
      printf("List Error: calling insertAfter() on a NULL cursor\n");
      exit(1);
   }
   N->prev = L->cursor;
   if(L->cursor->next != NULL){
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
   }else{
      L->back = N;
   }
   L->cursor->next = N; 
   L->length++;
}

// deleteFront()
// Delete the front element. 
// Pre: length()>0
void deleteFront(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   N = L->front;
   if(L->cursor == L->front){
      L->cursor = NULL;
      L->index = -1;
   }else if(L->index != -1){
      L->index--;
   }
   if( L->length>1 ) { 
      L->front = L->front->next;
   }else{ 
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// deleteBack()
// Delete the back element. 
// Pre: length()>0
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   N = L->back;
   if(L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   if( L->length>1 ) { 
      L->back = L->back->prev; 
   }else{ 
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   Node N = NULL;
   
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: calling delete() on an empty List\n");
      exit(1);
   }
   if(L->cursor == NULL){
      printf("List Error: calling delete() on a NULL cursor\n");
      exit(1);
   }
   N = L->cursor;
   if(L->length == 1){
      L->front = L->back = NULL;
   }else{
      if(L->cursor == L->front){
         deleteFront(L);
      }else if(L->cursor == L->back){
         deleteBack(L);
      }else{
         L->cursor->next->prev = L->cursor->prev;
         L->cursor->prev->next = L->cursor->next;
         freeNode(&N);
         L->length--;
      }
   }
   L->index = -1;
   L->cursor = NULL;
}


// Other Functions ------------------------------------------------------------
/*
// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}
*/
