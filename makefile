#compiler and flag options
CC = g++
FLAG = -std=c++14

# files directories
SRC = src
OBJ = obj
HDR = header
BIN = bin

$(BIN)/driver: $(OBJ)/driver.o $(OBJ)/data_structures.o  $(OBJ)/algo.o $(OBJ)/vhdl_gen.o
	$(CC) $(FLAG) -o $(BIN)/driver $(OBJ)/driver.o $(OBJ)/data_structures.o $(OBJ)/algo.o $(OBJ)/vhdl_gen.o

$(OBJ)/driver.o: $(SRC)/driver.cpp $(HDR)/data_structures.h $(HDR)/algo.h
	$(CC) $(FLAG) -o $(OBJ)/driver.o -c $(SRC)/driver.cpp 

$(OBJ)/data_structures.o: $(SRC)/data_structures.cpp $(HDR)/data_structures.h
	$(CC) $(FLAG) -o $(OBJ)/data_structures.o -c $(SRC)/data_structures.cpp 

$(OBJ)/algo.o: $(SRC)/algo.cpp $(HDR)/algo.h $(HDR)/data_structures.h $(SRC)/clique_partition.c
	$(CC) $(FLAG) -o $(OBJ)/algo.o -c $(SRC)/algo.cpp

$(OBJ)/vhdl_gen.o: $(SRC)/vhdl_gen.cpp $(HDR)/vhdl_gen.h $(HDR)/data_structures.h
	$(CC) $(FLAG) -o $(OBJ)/vhdl_gen.o -c $(SRC)/vhdl_gen.cpp 
