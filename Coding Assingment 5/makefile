# Kimberly Duffy - 1001607648
SRC1 = Code5_1001607648.cpp
SRC2 = CokeMachine.cpp
SRC3 = CokeLib.cpp
SRC4 = VendingMachine.cpp
OBJ1 = $(SRC1:.cpp=.o)
OBJ2 = $(SRC2:.cpp=.o)
OBJ3 = $(SRC3:.cpp=.o)
OBJ4 = $(SRC4:.cpp=.o)
EXE = $(SRC1:.cpp=.e)

HFILES =CokeMachine.h Cokelib.h VendingMachine.h

GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
CFLAGS = -g -std=c++11

all : $(EXE)
 
$(EXE): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	g++ $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) -o $(EXE) $(GTKFLAGS)

$(OBJ1) : $(SRC1) $(HFILES)
	g++ -c $(CFLAGS) $(SRC1) -o $(OBJ1) $(GTKFLAGS)

$(OBJ2) : $(SRC2) $(HFILES)
	g++ -c $(CFLAGS) $(SRC2) -o $(OBJ2) $(GTKFLAGS)

$(OBJ3) : $(SRC3) $(HFILES)
	g++ -c $(CFLAGS) $(SRC3) -o $(OBJ3) $(GTKFLAGS)

$(OBJ4) : $(SRC4) $(HFILES)
	g++ -c $(CFLAGS) $(SRC4) -o $(OBJ4) $(GTKFLAGS)


