

#/***********************************************
# * Aidan Smith, aipsmith@ucsc.edu              *
# * CSE101, Fall Quarter, October 13th, 2019    *
# * pa1: Makefile                               *
# *****************************************&*****/

#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o
 
