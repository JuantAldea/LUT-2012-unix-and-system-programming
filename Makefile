

FLAGS := -Wall -pedantic -std=gnu99 -g
CC := gcc $(FLAGS)
LINKFLAGS := -lm

SRC := src
OBJ := obj
BIN := bin

FUNCTIONS_OBJ := $(OBJ)/cd.o $(OBJ)/sleep.o

all: build

build: shell

shell: $(SRC)/main.c $(SRC)/generic.h $(SRC)/parameters.h $(SRC)/functions.h $(FUNCTIONS_OBJ)
	@[ -d $(BIN) ] || mkdir $(BIN)
	$(CC) $(SRC)/main.c $(FUNCTIONS_OBJ) -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/generic.h $(SRC)/parameters.h
	@[ -d $(OBJ) ] || mkdir $(OBJ)
	$(CC) -c $(SRC)/$*.c -o $(OBJ)/$*.o

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/shell
