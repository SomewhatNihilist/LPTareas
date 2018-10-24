
CFLAGS=-I. -Wall
DEPS = genetico.h lista.h fun.c
OBJ = lista.o genetico.o main.o fun.o
OUTPUT = main

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

#testdebug: $(OBJ)
#	gcc - $@ $^ $(CFLAGS) -D DEBUG

.PHONY: clean
#NOTE: remember to clean before using "git add ."!
clean:
	rm *.o $(OUTPUT)
