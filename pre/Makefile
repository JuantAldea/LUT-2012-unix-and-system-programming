###############################################
#   CT50A3000 - Unix and System Programming   #
#         Pre-assignment: Linked List         #
#   Juan Antonio Aldea Armenteros (0404450)   #
#        juan.aldea.armenteros@lut.fi         #
#                   Makefile                  #
###############################################

CC := gcc
CFLAGS := -W -Wall -Wextra -pedantic -std=gnu99 -O2 -pipe -g
TARGET := main
OBJ := main.o linked_list.o

build: all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm -f *.o $(TARGET)
