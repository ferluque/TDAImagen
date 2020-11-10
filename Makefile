BIN = bin
OBJ = obj
SRC = src
INC = inc
LIB = lib

$(BIN)/1umbralizar: $(LIB)/libUmbralizar.a
	echo Creando 1umbralizar
	g++ -L./$(LIB)/ -lUmbralizar -o $@

$(BIN)/3zoom: $(LIB)/libZoom.a
	echo Creando 3zoom
	g++ -L./$(LIB)/ -lZoom -o $@

$(BIN)/5contraste: $(LIB)/libContraste.a
	echo Creando 5contraste
	g++ -L./$(LIB)/ -lContraste -o $@

$(BIN)/6morphing: $(LIB)/libMorphing.a
	echo Creando 6morphing
	g++ -L./$(LIB)/ -lMorphing -o $@

$(LIB)/libUmbralizar.a: $(OBJ)/1umbralizar.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	ar rvs $@ $^

$(LIB)/libZoom.a: $(OBJ)/3zoom.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	ar rvs $@ $^

$(LIB)/libContraste.a: $(OBJ)/5contraste.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	ar rvs $@ $^

$(LIB)/libMorphing.a: $(OBJ)/6morphing.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	ar rvs $@ $^

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
	-rm $(OBJ)/* $(BIN)/* $(LIB)/*

all: clean $(BIN)/1umbralizar $(BIN)/3zoom $(BIN)/5contraste $(BIN)/6morphing

documentacion:
	echo Creando documentacion
	doxygen Doxyfile
