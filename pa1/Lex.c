
/*********************************************
 * Aidan Smith, aipsmith@ucsc.edu            *
 * CSE101, Fall Quarter, Octorber 13th, 2019 *
 * pa1: Lex.c                                *
 *********************************************/

//-----------------------------------------------------------------------------
// Lex.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];
   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   /* read each line of input file, and put in alphabetical order onto output file */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }
   rewind(in);
   char* strings[count];
   for(int i = 0; i < count; i++){
      strings[i] = calloc(MAX_LEN,sizeof(char));
   }
   int n = 0;
   while( fgets(strings[n], MAX_LEN, in) != NULL)  {
      n++;
   }
   List L = newList();
   append(L, 0);
   for(int i = 1; i < count; i++){
      moveFront(L);
      for(int k = 0; k < i; k++){
         if(strcmp(strings[get(L)], strings[i]) > 0){
            insertBefore(L, i);
            break;
         }
         if(k == i - 1){
            append(L, i);
            break;
         }
         if(back(L) == get(L)){
            break;
         }
         moveNext(L);
      }
   }
   moveFront(L);
   for(int i = 0; i < count; i++){
      fprintf(out, "%s", strings[get(L)]);
         if(back(L) == get(L)){
            break;
         }
      moveNext(L);
   }
   /* close files */
   fclose(in);
   fclose(out);
   
   for(int i = 0; i < count; i++){
      free(strings[i]);
   }
   freeList(&L);
   return(0);
}
