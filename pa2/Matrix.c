

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 30th, 2019 *
 * pa2: Matrix.c                             *
 *********************************************/

//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"

// structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj{
   int col;
   double value;
} EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj{
   int size;
   int nnz;
   List* array;
} MatrixObj;

// Constructors-Destructors---------------------------------------------------

// newEntry()
// Returns reference to new Entry object. Initializes next and data fields.
// Private.
Entry newEntry(int col, double value){
   Entry E = malloc(sizeof(EntryObj));
   E->col = col;
   E->value = value;
   return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
// Private.
void freeEntry(Entry* pE){
   if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
   }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
   Matrix M;
   M = malloc(sizeof(MatrixObj));
   M->array = calloc((n+1),sizeof(List)); // XXX May cause memory errors
   M->nnz = 0;
   M->size = n;
   for(int i = 1; i <= n; i++){
      M->array[i] = newList();
   }
   return(M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
   if(pM!=NULL && *pM!=NULL) { 
      makeZero(*pM);
      for(int i = 1; i <= size(*pM); i++){
         freeList(&(*pM)->array[i]);
      }
      free((*pM)->array);
      free(*pM);
      *pM = NULL;
   }
}


// Private helper functions---------------------------------------------------

// vectorDot()
// computes the vector dot product of two matrix rows represented by Lists P and Q. 
// Use this function together with function transpose() to help implement product(). 
double vectorDot(List P, List Q){
   double product;
   moveFront(P);
   moveFront(Q);
   while((index(P) != -1) && (index(Q) != -1)){ // loop through entries
      Entry entP = get(P);
      Entry entQ = get(Q);
      if(entP->col == entQ->col){ // case 1: A and B have element at (i,col)
         product += entP->value * entQ->value;
         moveNext(P);
         moveNext(Q);
      }
      else if(entP->col > entQ->col){ // case 2: A->col > B->col in row i
            moveNext(Q);
      }else{ // case 3: A->col < B->col
         moveNext(P);
      }
   }
   return product;
}

// Access functions---------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
   if( M==NULL ){
      printf("Matrix Error: calling size() on NULL Matrix reference\n");
      exit(1);
   }
   return(M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
   if( M==NULL ){
      printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(1);
   }
   return(M->nnz);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
   if( A==NULL || B==NULL){
      printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(1);
   }
   if(size(A) != size(B)){
      return 0;
   }else{
      for(int i = 1; i <= size(A); i++){
         moveFront(A->array[i]);
         moveFront(B->array[i]);
         while((index(A->array[i]) != -1) && (index(B->array[i]) != -1)){
            Entry entA = get(A->array[i]);
            Entry entB = get(B->array[i]);
            if(length(A->array[i]) != length(B->array[i])){
               return 0;
            }
            else if((entA->col != entB->col) || (entA->value != entB->value)){
               return 0;
            }
            if(A != B)
               moveNext(A->array[i]);
            moveNext(B->array[i]);
         }
         if(index(A->array[i]) != index(B->array[i])){
            return 0;
         }   
      }
   }
   return 1;
}


// Manipulation procedures---------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
   if( M==NULL ){
      printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(1);
   }
   for(int i = 1; i <= size(M); i++){
      clear(M->array[i]); // free entries?
   }
  M->nnz = 0; 
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
   if( M==NULL ){
      printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(1);
   }
   if(( i < 0 ) || ( i > M->size )){
      printf("Matrix Error: calling changeEntry() on Matrix where i does not fit in the range 1<=i<=size(M)\n");
      exit(1);
   }
   if(( j < 0 ) || ( j > M->size )){
      printf("Matrix Error: calling changeEntry() on Matrix where j does not fit in the range 1<=j<=size(M)\n");
      exit(1);
   }
   List L = M->array[i]; // already been initalized
   if(length(L) == 0){ 
      if((double)((int)(x + 0.5)) != 0.0){ // if entry value is 0, do nothing (sparse matrix)
         Entry E = newEntry(j, x);
         append(L, E); // list empty, add entry
         M->nnz++;
      }
   }else{ // length > 0
      moveFront(L);
      Entry temp;
      while(index(L) != -1){ // while current index exists
         temp = get(L);
         if(temp->col < j){ // while the column currently looked at in List is less than the col of E
            moveNext(L);
         }else{
            break; // avoid infinite loop
         }
      }
      if(index(L) == -1){
         if((double)((int)(x + 0.5)) != 0.0){
            Entry E = newEntry(j, x);
            append(L, E); // entry col larger than others in row, add to end
            M->nnz++;
         }
         return;
      }
      temp = get(L);
      if(temp->col > j){
         if((double)((int)(x + 0.5)) != 0.0){
            Entry E = newEntry(j, x);
            insertBefore(L, E); // if entry is less than current and greater than before, insert before current
            M->nnz++;
         }
      }else{ // (get(L))->col == j
         if((double)((int)(x + 0.5)) != 0.0){
            Entry E = newEntry(j, x);
            insertBefore(L, E); // if entry is at same colum as current, replace
         }else{
            M->nnz--;
         }
         free(temp);
         delete(L); // deletes cursor, if x was 0 then no entry remains, otherwise entry replaces cursor
      }
   }
}


// Matrix Arithmetic operations--------------------------------------------------- 

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
   if( A==NULL ){
      printf("Matrix Error: calling copy() on NULL Matrix reference\n");
      exit(1);
   }
   Matrix M = newMatrix(size(A));
   for(int i = 1; i <= size(A); i++){ // loop through lists
      moveFront(A->array[i]);
      List L = M->array[i];
      while(index(A->array[i]) != -1){ // loop through entries
         Entry temp = get(A->array[i]);
         int col = temp->col; // XXX could instead call changeEntry?
         double value = temp->value;
         Entry E = newEntry(col, value);
         append(L, E);
         moveNext(A->array[i]);
      }
   }
   M->nnz = A->nnz;
   return M;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
   if( A==NULL ){
      printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
      exit(1);
   }
   Matrix M = newMatrix(size(A));
   for(int i = 1; i <= size(A); i++){ // loop through lists
      moveFront(A->array[i]);
      while(index(A->array[i]) != -1){ // loop through entries
         Entry temp = get(A->array[i]);
         List L = M->array[temp->col];
         int col = i;
         double value = temp->value;
         Entry E = newEntry(col, value);
         append(L, E);
         moveNext(A->array[i]);
      }
   }
   M->nnz = A->nnz;
   return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
   if( A==NULL ){
      printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      exit(1);
   }
   Matrix M = newMatrix(size(A));
   for(int i = 1; i <= size(A); i++){ // loop through lists
      moveFront(A->array[i]);
      List L = M->array[i];
      while(index(A->array[i]) != -1){ // loop through entries
         Entry temp = get(A->array[i]);
         int col = temp->col;
         double value = x * (temp->value);
         Entry E = newEntry(col, value);
         append(L, E);
         moveNext(A->array[i]);
      }
   }
   M->nnz = A->nnz;
   return M;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
   if( A==NULL || B == NULL){
      printf("Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(1);
   }
   if(size(A) != size(B)){
      printf("Matrix Error: calling sum() on two matricies of different sizes\n");
      exit(1);
   }
   Matrix M = newMatrix(size(A));
   for(int i = 1; i <= size(A); i++){
      moveFront(A->array[i]);
      moveFront(B->array[i]);
      while((index(A->array[i]) != -1) && (index(B->array[i]) != -1)){ // first checks if there are elements in list
         Entry entA = get(A->array[i]);
         Entry entB = get(B->array[i]);
         if(entA->col == entB->col){ // case 1: A and B have element at (i,col)
            changeEntry(M, i, entA->col, entA->value + entB->value);
            if(A != B)
               moveNext(A->array[i]);
            moveNext(B->array[i]);
         }
         else if(entA->col > entB->col){ // case 2: A->col > B->col in row i
            changeEntry(M, i, entB->col, entB->value);
            moveNext(B->array[i]);
         }else{ // case 3: A->col < B->col
            changeEntry(M, i, entA->col, entA->value);
            moveNext(A->array[i]);
         }
      }
      while(index(A->array[i]) != index(B->array[i])){ // one still has nodes remaining in list
         if(index(A->array[i]) != -1){
            Entry entA = get(A->array[i]);
            changeEntry(M, i, entA->col, entA->value);
            moveNext(A->array[i]);
         }else{ // B has index greater than -1
            Entry entB = get(B->array[i]);
            changeEntry(M, i, entB->col, entB->value);
            moveNext(B->array[i]);
         }
      }  
   }
   return M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
   if( A==NULL || B==NULL){
      printf("Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(1);
   }
   if(size(A) != size(B)){
      printf("Matrix Error: calling diff() on two matricies of different sizes\n");
      exit(1);
   }
   Matrix M = newMatrix(size(A));
   for(int i = 1; i <= size(A); i++){
      moveFront(A->array[i]);
      moveFront(B->array[i]);
      while((index(A->array[i]) != -1) && (index(B->array[i]) != -1)){ // first checks if there are elements in list
         Entry entA = get(A->array[i]);
         Entry entB = get(B->array[i]);
         if(entA->col == entB->col){ // case 1: A and B have element at (i,col)
            changeEntry(M, i, entA->col, entA->value - entB->value);
            moveNext(A->array[i]);
            moveNext(B->array[i]);
         }
         else if(entA->col > entB->col){ // case 2: A->col > B->col in row i
            changeEntry(M, i, entB->col, -(entB->value));
            moveNext(B->array[i]);
         }else{ // case 3: A->col < B->col
            changeEntry(M, i, entA->col, entA->value);
            moveNext(A->array[i]);
         }
      }
      while(index(A->array[i]) != index(B->array[i])){ // one still has nodes remaining in list
         if(index(A->array[i]) != -1){
            Entry entA = get(A->array[i]);
            changeEntry(M, i, entA->col, entA->value);
            moveNext(A->array[i]);
         }else{ // B has index greater than -1
            Entry entB = get(B->array[i]);
            changeEntry(M, i, entB->col, -(entB->value));
            moveNext(B->array[i]);
         }
      }  
   }
   return M;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
   if( A==NULL || B==NULL){
      printf("Matrix Error: calling product() on NULL Matrix reference\n");
      exit(1);
   }
   if(size(A) != size(B)){
      printf("Matrix Error: calling product() on two matricies of different sizes\n");
      exit(1);
   }
   Matrix M = newMatrix(size(A));
   Matrix T = transpose(B);
   for(int i = 1; i <= size(A); i++){
      if(length(A->array[i]) != 0){
         for(int j = 1; j <= size(T); j++){
            if(length(T->array[j]) != 0){
               double temp = vectorDot(A->array[i], T->array[j]);
               changeEntry(M, i, j, temp);
            }
         }
      }
   }
   return M;
}


// Optional functions--------------------------------------------------------

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs"(col, val)" giving the column numbers and non-zero values 
// in that row.The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
   if( M==NULL ){
      printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
      exit(1);
   }
   for(int i = 1; i <= M->size; i++){
      moveFront(M->array[i]);
      int k = 0;
      if(index(M->array[i]) != -1){
         fprintf(out, "%d: ", i);
      }
      while(index(M->array[i]) != -1){ // loop through entries
         Entry E = get(M->array[i]);
         fprintf(out, "(%d, %.1f) ", E->col, E->value);
         k = 1;
         moveNext(M->array[i]);
      }
      if(k == 1){
         fprintf(out, "\n");
      }
   }
}



