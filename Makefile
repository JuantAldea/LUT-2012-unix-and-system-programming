

FLAGS := -Wall -pedantic -std=gnu99 -g
CC := gcc $(FLAGS)
LINKFLAGS := -lm

SRC := src
OBJ := obj
BIN := bin

FUNCTIONS_OBJ := $(OBJ)/cd.o $(OBJ)/history.o $(OBJ)/run_command.o $(OBJ)/param_split.o

all: build

build: shell

shell: $(SRC)/main.c $(SRC)/generic.h $(SRC)/parameters.h $(SRC)/functions.h $(SRC)/run_command.h $(FUNCTIONS_OBJ)
	@[ -d $(BIN) ] || mkdir $(BIN)
	$(CC) $(SRC)/main.c $(FUNCTIONS_OBJ) -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/generic.h $(SRC)/parameters.h
	@[ -d $(OBJ) ] || mkdir $(OBJ)
	$(CC) -c $(SRC)/$*.c -o $(OBJ)/$*.o

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)
