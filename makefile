#compiler and flag options
CC = g++
FLAG = -std=c++14

# files directories
SRC = src
OBJ = obj
HDR = header
BIN = bin

$(BIN)/driver: $(OBJ)/driver.o $(OBJ)/graph.o $(OBJ)/algo.o $(OBJ)/datapath_vhdl.o $(OBJ)/edge.o $(OBJ)/operation.o $(OBJ)/datapath.o
	$(CC) $(FLAG) -o $(BIN)/driver $(OBJ)/driver.o $(OBJ)/graph.o $(OBJ)/algo.o $(OBJ)/datapath_vhdl.o $(OBJ)/edge.o $(OBJ)/operation.o $(OBJ)/datapath.o

$(OBJ)/driver.o: $(SRC)/driver.cpp $(HDR)/graph.h $(HDR)/algo.h $(HDR)/datapath.h $(HDR)/operation.h $(HDR)/datapath_vhdl.h
	$(CC) $(FLAG) -o $(OBJ)/driver.o -c $(SRC)/driver.cpp 

$(OBJ)/graph.o: $(SRC)/graph.cpp $(HDR)/graph.h $(HDR)/edge.h $(HDR)/operation.h $(HDR)/reg_unit.h $(HDR)/fu_unit.h $(HDR)
	$(CC) $(FLAG) -o $(OBJ)/graph.o -c $(SRC)/graph.cpp 

$(OBJ)/edge.o: $(SRC)/edge.cpp $(HDR)/edge.h
	$(CC) $(FLAG) -o $(OBJ)/edge.o -c $(SRC)/edge.cpp

$(OBJ)/operation.o: $(SRC)/operation.cpp $(HDR)/operation.h
	$(CC) $(FLAG) -o $(OBJ)/operation.o -c $(SRC)/operation.cpp

$(OBJ)/datapath.o: $(SRC)/datapath.cpp $(HDR)/datapath.h $(HDR)/graph.h $(HDR)/reg_unit.h $(HDR)/fu_unit.h $(HDR)/rmux_unit.h $(HDR)/fmux_unit.h
	$(CC) $(FLAG) -o $(OBJ)/datapath.o -c $(SRC)/datapath.cpp

$(OBJ)/algo.o: $(SRC)/algo.cpp $(HDR)/algo.h $(HDR)/graph.h $(SRC)/clique_partition.c
	$(CC) $(FLAG) -o $(OBJ)/algo.o -c $(SRC)/algo.cpp

$(OBJ)/datapath_vhdl.o: $(SRC)/datapath_vhdl.cpp $(HDR)/datapath_vhdl.h $(HDR)/graph.h
	$(CC) $(FLAG) -o $(OBJ)/datapath_vhdl.o -c $(SRC)/datapath_vhdl.cpp 
