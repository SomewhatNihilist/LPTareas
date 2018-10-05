
CC=gcc
CFLAGS=-I. -Wall
DEPS = genetico.h
OBJ = genetico.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
