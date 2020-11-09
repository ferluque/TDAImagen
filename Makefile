BIN = bin
OBJ = obj
SRC = src
INC = inc

$(BIN)/1umbralizar: $(OBJ)/1umbralizar.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	echo Creando 1umbralizar
	g++ $^ -o $@

$(BIN)/3zoom: $(OBJ)/3zoom.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	echo Creando 3zoom
	g++ $^ -o $@

$(BIN)/5contraste: $(OBJ)/5contraste.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	echo Creando 5contraste
	g++ $^ -o $@

$(BIN)/6morphing: $(OBJ)/6morphing.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	echo Creando 6morphing
	g++ $^ -o $@

$(OBJ)/1umbralizar.o: $(SRC)/1umbralizar.cpp $(INC)/Imagen.h $(INC)/imagenES.h
	echo Creando 1umbralizar.o
	g++ -g -c -I./$(INC) $< -o $@

$(OBJ)/3zoom.o: $(SRC)/3zoom.cpp $(INC)/Imagen.h $(INC)/imagenES.h
	echo Creando 3zoom.o
	g++ -g -c -I./$(INC) $< -o $@

$(OBJ)/5contraste.o: $(SRC)/5contraste.cpp $(INC)/Imagen.h $(INC)/imagenES.h
	g++ -g -c -I./$(INC) $< -o $@

$(OBJ)/6morphing.o: $(SRC)/6morphing.cpp $(INC)/Imagen.h $(INC)/imagenES.h
	g++ -g -c -I./$(INC) $< -o $@

$(OBJ)/Imagen.o: $(SRC)/Imagen.cpp $(INC)/Imagen.h
	echo Creando Imagen.o
	g++ -g -c -I./$(INC) $< -o $@

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp $(INC)/imagenES.h
	echo Creando imagenEs.o
	g++ -g -c -I./$(INC) $< -o $@

clean:
	echo Limpiando
	-rm $(OBJ)/* $(BIN)/*

all: clean $(BIN)/1umbralizar $(BIN)/3zoom $(BIN)/5contraste $(BIN)/6morphing

documentacion:
	echo Creando documentacion
	doxygen Doxyfile
