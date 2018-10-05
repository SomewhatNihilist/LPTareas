
CFLAGS=-I. -Wall
DEPS = genetico.h
OBJ = genetico.o main.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
