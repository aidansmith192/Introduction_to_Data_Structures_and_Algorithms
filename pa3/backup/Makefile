

#/***********************************************
# * Aidan Smith, aipsmith@ucsc.edu              *
# * CSE101, Fall Quarter, November 17th, 2019   *
# * pa3: Makefile                               *
# ***********************************************/

#--------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 3
#
#  make                     makes Arithmetic, rename CLIENT to w/e for other test
#  make clean               removes all binaries
#  make memcheck            runs Arithmetic Client under valgrind
#--------------------------------------------------------------------------------

CLIENT         = Arithmetic
ADT1           = BigInteger
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

