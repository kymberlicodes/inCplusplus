#Kimberly Duffy - 1001607648
#makefile for C++ program
SRC = Code2_1001607648.cpp
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=.e)

HFILES = CokeMachine.h

CFLAGS = -g -std=c++11

all : $(EXE)
 
$(EXE): $(OBJ) 
	g++ $(CFLAGS) $(OBJ) -o $(EXE) 

$(OBJ) : $(SRC) $(HFILES)
	g++ -c $(CFLAGS) $(SRC) -o $(OBJ) 

