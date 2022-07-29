CC = g++
CFLAGS = -Wall -c
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/heap.o $(OBJ)/processaheap.o $(OBJ)/quicksort.o $(OBJ)/main.o
HDRS = $(INC)/heap.h $(INC)/processaheap.h $(INC)/quicksort.h $(INC)/struct.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/heap.o: $(HDRS) $(SRC)/heap.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/heap.o $(SRC)/heap.cpp

$(OBJ)/quicksort.o: $(HDRS) $(SRC)/quicksort.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/quicksort.o $(SRC)/quicksort.cpp
	
$(OBJ)/processaheap.o: $(HDRS) $(SRC)/processaheap.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/processaheap.o $(SRC)/processaheap.cpp
	
clean:
	rm $(EXE) $(OBJS)
