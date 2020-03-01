
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, November 17th, 2019 *
 * pa3: BigInteger.c                         *
 *********************************************/

//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 9 // max power allowed: 10^9
#define BASE 1000000000 // max base allowed: 1,000,000,000

// structs --------------------------------------------------------------------

// private BigInteger type
typedef struct BigIntegerObj{
   List list;
   int sign; // (1 or -1. Or 0 if in zero state)
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(void){
   BigInteger B;
   B = malloc(sizeof(BigIntegerObj));
   B->list = newList();
   append(B->list, 0);
   B->sign = 0;
   return(B);
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
   if(pN!=NULL && *pN!=NULL) { 
      freeList(&((*pN)->list)); // asterisk or not
      free(*pN);
      *pN = NULL;
   }
}


// Helper functions -----------------------------------------------------------

// power()
// Returns the value of 10 raised to the specified number.
int power(int pow){
   int ans = 1;
   for(int i = 0; i <= pow; i++){
      ans = ans * 10;
   }
   return ans;
}

// resizer()
// Fixes the size of nodes so that they are of size POWER
void resizer(BigInteger B){
   moveBack(B->list); // check that all the values have less digits than POWER
   while(index(B->list) != -1){
      if(get(B->list) >= BASE){ // bigger than 999,999,999 then its bigger than size allowed
         long excess = get(B->list) / BASE; // divide number by 1,000,000,000. gives excess
         long fix = get(B->list) - (excess * BASE);
         set(B->list, fix);
         if(index(B->list) == 0){ // this is the front, must add another before as number got bigger
            prepend(B->list, excess);
         }else{ // there is an index before this one
            movePrev(B->list);
            long temp = get(B->list) + excess;
            set(B->list, temp);
            moveNext(B->list);
         }
      }
      else if(get(B->list) <= -1 * BASE){ // smaller than -999,999,999 then its smaller than size allowed
         long excess = get(B->list) / BASE; // divide number by 1,000,000,000. gives excess
         long fix = get(B->list) - (excess * BASE);
         set(B->list, fix);
         if(index(B->list) == 0){ // this is the front, must add another before as number got bigger
            prepend(B->list, excess);
         }else{ // there is an index before this one
            movePrev(B->list);
            long temp = get(B->list) + excess;
            set(B->list, temp);
            moveNext(B->list);
         }
      }
      movePrev(B->list);
   }
}

// normalize()
// Fixes a BigInteger object so that it specifies the size of POWER for each element
// and contains the same sign for every node.
void normalize(BigInteger B){
   if(length(B->list) == 0){
      append(B->list, 0);
      B->sign = 0;
      return;
   }
   resizer(B);
   moveFront(B->list);
   if(length(B->list) == 1 && get(B->list) == 0){
      B->sign = 0;
      return;
   }
   if(B->sign == 0){
      B->sign = 1;
   }
   int sign = B->sign; // sign is to hold the old sign, 1 or 0 is positive, -1 is negative
   moveFront(B->list); // now make all the signs the same
   if(get(B->list) < 0){
      negate(B);
   } // else nothing, already good
   moveBack(B->list);
   if(sign != B->sign){ // sign swap if necessary
      while(index(B->list) != -1){
         set(B->list, -1 * get(B->list));
         movePrev(B->list);
      }
   }
   moveBack(B->list);
   while(index(B->list) != -1){ // check for remaining negatives
      if(get(B->list) < 0){
         set(B->list, BASE + get(B->list));
         if(index(B->list) == 0){ // this is the front, must add another before as number got bigger
            prepend(B->list, -1);
         }else{ // there is an index before this one
            movePrev(B->list);
            set(B->list, get(B->list) - 1);
            moveNext(B->list);
            }
      }
      movePrev(B->list);
   }
   resizer(B);
   moveFront(B->list);
   while(index(B->list) == 0){ // removes leading zeros
      if(front(B->list) == 0){
         deleteFront(B->list);
      }else{
         break;
      }
   }
   if(length(B->list) == 0){ // if the list is completely empty, aka only 0's were given, then make it a zero bigInt
      append(B->list, 0);
      B->sign = 0;
   }
}

// longLength()
// Gives the length of the long in the current index
int longLength(BigInteger N){
   int i = 1;
   while(power(i) < BASE){
      if(get(N->list) < power(i)){
         return i;
      } // no else, continue/
      i++;
   }
   return POWER;
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero 
// state.
int sign(BigInteger N){
   if( N==NULL ){
      printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
      exit(1);
   }
   return(N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      printf("BigInteger Error: calling compare() on NULL BigInteger reference\n");
      exit(1);
   }
   if(A->sign > B->sign){
      return 1;
   }
   else if(A->sign < B->sign){
      return -1;
   }
   else if(A->sign == 0){ // thus the signs must be the same, so if A->sign is 0, then so is B->sign
      return 0;
   }
   else if(A == B || equals(A, B)){
      return 0;
   }
   moveBack(A->list);
   moveBack(B->list);
   while(index(A->list) != -1 && index(B->list) != -1){
      movePrev(A->list);
      movePrev(B->list);
   }
   if(index(A->list) != index(B->list)){
      if(index(A->list) != -1){
         return 1;
      }else{ // (index(B->list) != -1){
         return -1;
      }
   }else{
      moveFront(A->list);
      moveFront(B->list);
      while(index(A->list) != -1){ // they are the same length, only need to check
         if(get(A->list) > get(B->list)){
            return 1;
         }
         else if(get(A->list) > get(B->list)){
            return -1;
         } // else: continue looping
         moveNext(A->list);
         moveNext(B->list);
      }
   }
   return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      printf("BigInteger Error: calling compare() on NULL BigInteger reference\n");
      exit(1);
   }
   if(A->sign != B->sign){
      return 0;
   }else{ //(A->sign == B->sign){
      if(A->sign == 0){
         return 1;
      }else{
         return sameList(A->list, B->list);
      }
   }
}


// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
   if( N==NULL ){
      printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
      exit(1);
   }
   N->sign = 0;
   clear(N->list);
   append(N->list, 0);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
   if( N==NULL ){
      printf("BigInteger Error: calling negate() on NULL BigInteger reference\n");
      exit(1);
   }
   if(N->sign == -1){
      N->sign = 1;
   }
   else if(N->sign == 1){
      N->sign = -1;
   }
}


// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s. 
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9} 
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
   int sign = 0; // tracks if there is a sign
   int i = 0;
   if(s[0] == '-'){
      sign = -1;
      i = 1;
   }
   else if(s[0] == '+' ){
      sign = 1;
      i = 1;
   }
   int k = i;
   BigInteger N = newBigInteger();
   deleteFront(N->list);
   while(s[i] != '\0'){ // loop through to find the length of it
      if(!isdigit(s[i])){
         printf("BigInteger Error: calling stringToBigInteger() on an improper string\n");
         exit(1);
      }
      i++; // make sure characters are only #'s with a possible prefix of -/+
   }
   long ans = 0;
   char* a = calloc(POWER + 1, sizeof(char));
   int j = (i - k) % POWER; // this finds the # of base 10 digits in the 10^POWER digits for the MSD
   if(k == 1){
      while((s[k] != '\0') && (k <= j)){  
         a[k-1] = s[k];
         k++;                            
      }
   }else{ // k == 0
      while((s[k] != '\0') && (k < j)){ // only diff is "<=" and "<", where the = is needed if k is 1
         a[k] = s[k];
         k++;                            
      }
   }
   a[k] = '\0';
   ans = atol(a);
   if(ans != 0){
      append(N->list, ans);
   }
   ans = 0;
   int l = 0;
   while(s[k] != '\0'){ // continue looping until the end, should end on a number k + a multiple of POWER, and should be a length of POWER
      a[l] = s[k];
      l++;
      if(l == POWER){
         ans = atol(a);
         if((ans != 0) || (length(N->list) != 0)){ // only add zeros if not leading zeros
            append(N->list, ans);
         }
         l = 0;
         ans = 0;
      }
      k++;
   }
   if(length(N->list) == 0){ // if the list is completely empty, aka only 0's were given, then make it a zero bigInt
      append(N->list, 0);
      N->sign = 0;
   }
   else if(sign == -1){ // the number has a negative sign
      N->sign = -1;
   }else{ // either the number exists without a sign or with a '+' sign as the final option
      N->sign = 1;
   }
   normalize(N);
   free(a);
   return N;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
   if( N==NULL ){
      printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
      exit(1);
   }
   BigInteger temp = newBigInteger();
   freeList(&(temp->list));
   temp->list = copyList(N->list);
   temp->sign = N->sign;
   return temp;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
   if( A==NULL || B==NULL || S==NULL){
      printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
      exit(1);
   }
   normalize(S);
   normalize(A);
   normalize(B);
   int ABsame = 0;
   int SAsame = 0;
   int SBsame = 0;
   if(A == B){ // if they are the same, use an identical one for the time being
      B = copy(A);
      ABsame = 1;
   }
   if(S == A){
      A = copy(S);
      SAsame = 1;
   }
   if(S == B){
      B = copy(S);
      SBsame = 1;
   }
   makeZero(S);
   if(A->sign == 0){
      if(B->sign == 0){ // if both A and B are 0
      }else{
         freeList(&(S->list));
         S->list = copyList(B->list);
         S->sign = B->sign;
      }
   }
   else if(B->sign == 0){ // if only B is 0
      freeList(&(S->list));
      S->list = copyList(A->list);
      S->sign = A->sign;
   }else{ // if both are non-zero
      moveBack(A->list);
      moveBack(B->list);
      clear(S->list);
      long sum;
      while(index(A->list) != -1 && index(B->list) != -1){ // loop through A and B until one or both end
         sum = (A->sign * get(A->list)) + (B->sign * get(B->list));
         prepend(S->list, sum);
         movePrev(A->list);
         movePrev(B->list);
      }
      if(index(A->list) != index(B->list)){
         if(index(A->list) == -1){ // thus A is done
            while(index(B->list) != -1){
               prepend(S->list, B->sign * get(B->list));
               movePrev(B->list);
            }
         }else{ // index(B) == -1, B is shorter than A
            while(index(A->list) != -1){
               prepend(S->list, A->sign * get(A->list));
               movePrev(A->list);
            }
         }
      } // no else, they both were the same length
   }
   normalize(S);
   if(SAsame){ // if they were the same to start with, return them to that state
      freeBigInteger(&A);
      A = S;
   }
   if(ABsame){ 
      freeBigInteger(&B);
      B = A;
   }
   if(SBsame){
      freeBigInteger(&B);
      B = S;
   }
   if(length(S->list) == 1){
      moveFront(S->list);
      if(get(S->list) == 0){
         S->sign = 0;
      }
   }
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
      exit(1);
   }
   BigInteger S = newBigInteger();
   add(S, A, B);
   return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting 
// its current state: D = A -B
void subtract(BigInteger D, BigInteger A, BigInteger B){
   if( A==NULL || B==NULL || D==NULL){
      printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
      exit(1);
   }
   BigInteger N = copy(B);
   negate(N);
   add(D, A, N);
   freeBigInteger(&N);
   normalize(D);
}

// diff()
// Returns a reference to a new BigInteger object representing A -B.
BigInteger diff(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL ){
      printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
      exit(1);
   }
   BigInteger D = newBigInteger();
   subtract(D, A, B);
   return D;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
   if( A==NULL || B==NULL || P==NULL ){
      printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
      exit(1);
   }
   int ABsame = 0;
   int PAsame = 0;
   int PBsame = 0;
   if(A == B){ // if they are the same, use an identical one for the time being
      B = copy(A);
      ABsame = 1;
   }
   if(P == A){
      A = copy(P);
      PAsame = 1;
   }
   if(P == B){
      B = copy(P);
      PBsame = 1;
   }
   makeZero(P);
   if(A->sign == 0 || B->sign == 0){
   }else{ // both are non-zero
      moveBack(A->list);
      moveBack(B->list);
      long prod = 0;
      int Aplace = 0;
      int Bplace = 0;
      while(index(A->list) != -1){ // loop through A until end
         while(index(B->list) != -1){
            prod = (A->sign * get(A->list)) * (B->sign * get(B->list));
            moveBack(P->list);
            for(int i = 0; i < Aplace + Bplace; i++){
               movePrev(P->list);
               if(index(P->list) == -1){
                  prepend(P->list, 0);
                  moveFront(P->list);
               }
            }
            set(P->list, prod + get(P->list));
            Bplace++;
            movePrev(B->list);
         }
         Bplace = 0;
         moveBack(B->list);
         Aplace++;
         movePrev(A->list);
         resizer(P); // incase it ever reaches the max amount in an index
      }
   }
   normalize(P);
   if(PAsame){ // if they were the same to start with, return them to that state
      freeBigInteger(&A);
      A = P;
   }
   if(ABsame){ 
      freeBigInteger(&B);
      B = A;
   }
   if(PBsame){
      freeBigInteger(&B);
      B = P;
   }
}  

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
   if( A==NULL || B==NULL){
      printf("BigInteger Error: calling prod() on NULL BigInteger reference\n");
      exit(1);
   }
   BigInteger P = newBigInteger();
   multiply(P, A, B);
   return P;
}


// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
   if( N==NULL ){
      printf("BigInteger Error: calling printBigInteger() on NULL BigInteger reference\n");
      exit(1);
   }
   while(length(N->list) != 0){
      if(front(N->list) == 0){
         deleteFront(N->list);
      }else{
         break;
      }
   }
   if(length(N->list) == 0){
      N->sign = 0;
      append(N->list, 0);
   }
   if(N->sign == -1){
      fprintf(out, "-");
   }
   else if(N->sign == 0){
      fprintf(out, "0\n");
      return;
   }
   moveFront(N->list);
   fprintf(out, "%ld", get(N->list));
   moveNext(N->list);
   while(index(N->list) != -1){
      int length = longLength(N);
      for(int i = 1; i < POWER - length; i++){
         fprintf(out, "0");
      }
      fprintf(out, "%ld", get(N->list));
      moveNext(N->list);
   }
   fprintf(out,"\n");
}




