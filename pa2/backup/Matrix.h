

/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 30th, 2019 *
 * pa2: Matrix.h                             *
 *********************************************/

//-----------------------------------------------------------------------------
// Matrix.h
// Header file for Matrix ADT
//-----------------------------------------------------------------------------

#pragma once


// Exported type --------------------------------------------------------------

typedef struct MatrixObj* Matrix;


Matrix newMatrix(int n); // Returns a reference to a new nXn Matrix object in the zero state.

void freeMatrix(Matrix* pM); // Frees heap memory associated with *pM, sets *pM to NULL.

// Access functions------------------------------------------------------------ 

int size(Matrix M); // Return the size of square Matrix M.

int NNZ(Matrix M);// Return the number of non-zero elements in M.

int equals(Matrix A, Matrix B);// Return true (1) if matrices A and B are equal, false (0) otherwise.


// Manipulation procedures------------------------------------------------------------

void makeZero(Matrix M);// Re-sets M to the zero Matrix.

void changeEntry(Matrix M, int i, int j, double x); // Changes the ith row, jth column of M to the value x.
					            // Pre: 1<=i<=size(M), 1<=j<=size(M)


// Matrix Arithmetic operations------------------------------------------------------------ 

Matrix copy(Matrix A); // Returns a reference to a new Matrix object having the same entries as A.

Matrix transpose(Matrix A); // Returns a reference to a new Matrix object representing the transposeof A.

Matrix scalarMult(double x, Matrix A); // Returns a reference to a new Matrix object representing xA.

Matrix sum(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing A+B.
			        // pre: size(A)==size(B)

Matrix diff(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing A-B.
				 // pre: size(A)==size(B)

Matrix product(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing AB
				    // pre: size(A)==size(B)

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs"(col, val)" giving the column numbers and non-zero values 
// in that row.The double val will be rounded to 1 decimal point.
// void printMatrix(FILE* out, Matrix M);
