CC = g++
CFLAGS = -Wall -c
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/HOST.o $(OBJ)/REGEXPROCESSOR.o $(OBJ)/URL.o $(OBJ)/main.o
HDRS = $(INC)/HOST.h $(INC)/REGEXPROCESSOR.h $(INC)/URL.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/HOST.o: $(HDRS) $(SRC)/HOST.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/HOST.o $(SRC)/HOST.cpp

$(OBJ)/REGEXPROCESSOR.o: $(HDRS) $(SRC)/REGEXPROCESSOR.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/REGEXPROCESSOR.o $(SRC)/REGEXPROCESSOR.cpp

$(OBJ)/URL.o: $(HDRS) $(SRC)/URL.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/URL.o $(SRC)/URL.cpp
	
clean:
	rm $(EXE) $(OBJS)