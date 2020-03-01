

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 17th, 2019 *
 * pa3: List.h                               *
 *********************************************/

//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#pragma once

// Exported type --------------------------------------------------------------

typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

List newList(void); // Creates and returns a new empty List.

void freeList(List* pL); // Frees all heap memory associated with *pL, and sets
			 // *pL to NULL.


// Access functions -----------------------------------------------------------

int length(List L);// Returns the number of elements in L.

int index(List L); // Returns index of cursor element if defined, -1 otherwise.

long front(List L);// Returns front element of L. Pre: length()>0

long back(List L);// Returns back element of L. Pre: length()>0

long get(List L);// Returns cursor element of L. Pre: length()>0, index()>=0

int sameList(List A, List B);// Returns true (1) iff Lists A and B are in same
			   // state, and returns false (0) otherwise.


// Manipulation procedures ----------------------------------------------------

void clear(List L);// Resets L to its original empty state.

void moveFront(List L);// If L is non-empty, sets cursor under the front element,
		       // otherwise does nothing.

void moveBack(List L);// If L is non-empty, sets cursor under the back element,
		      //otherwise does nothing.

void movePrev(List L);// If cursor is defined and not at front, move cursor one 
		      // step toward the front of L; if cursor is defined and at 
		      // front, cursor becomes undefined; if cursor is undefined 
		      // do nothing

void moveNext(List L);// If cursor is defined and not at back, move cursor one 
		      // step toward the back of L; if cursor is defined and at 
		      // back, cursor becomes undefined; if cursor is undefined 
		      // do nothing

void prepend(List L, long data);// Insert new element into L. If L is non-empty, 
			       //  insertion takes place before front element.

void append(List L, long data);// Insert new element into L. If L is non-empty, 
			      // insertion takes place after back element.

void insertBefore(List L, long data);// Insert new element before cursor. 
				    // Pre: length()>0, index()>=0

void insertAfter(List L, long data);// Insert new element after cursor. 
				   // Pre: length()>0, index()>=0

void deleteFront(List L);// Delete the front element. Pre: length()>0

void deleteBack(List L);// Delete the backelement. Pre: length()>0

void delete(List L);// Delete cursor element, making cursor undefined.
		    // Pre: length()>0, index()>=0

// set()
// Overwrites the cursor elementwith x. Pre: length()>0, index()>=0
void set(List L, long x);

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L);// Prints to the file pointed to by out, a 
				  // string representation of L consisting 
				  // of a space separated sequence of integers,
				  // with front on left.

List copyList(List L);// Returns a new List representing the same integer 
		      // sequence as L. The cursor in the new list is undefined,
		      // regardless of the state of the cursor in L. The state 
		      // of L is unchanged.

//EXTRA
//List concatList(List A, List B);  // Returns a new List which is the concatenation of 
				  // A and B.  The cursor in the new Listis undefined,
				  // regardless of the states of the cursorsin A and B.
				  // The states ofA and B areunchanged.
