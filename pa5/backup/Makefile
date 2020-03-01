

#/***********************************************
# * Aidan Smith, aipsmith@ucsc.edu              *
# * CSE101, Fall Quarter, December 7th, 2019    *
# * pa5: Makefile                               *
# ***********************************************/

#--------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 5
#
#  make                     makes FindComponents, rename CLIENT to w/e for other test
#  make clean               removes all binaries
#  make memcheck            runs FindPath Client under valgrind
#--------------------------------------------------------------------------------

CLIENT         = FindComponents
ADT1           = Graph
ADT2           = List
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -g -c -std=c99 -Wall
LINK           = gcc -g -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)

