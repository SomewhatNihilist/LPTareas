
#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Para generar un seed aleatorio

struct tNodo {
	void* dato;
	char tipo; // 'i'=[0-9], 'c'=[A-F], 'b'=bit (0,1)
};

int t = time();
const int seed = ;

void* generarSolucion(int largo) {

}

void* copiar(void* Lista) {

}

void borrar(void* Lista);

void imprimirSolucion(void* Lista);

void cruceMedio(void* Lista1, void* Lista2);

void cruceIntercalado(void* Lista1, void* Lista2);

void mutacionRand(void* Lista);

void mutacionTipo(void* Lista);

int evaluacionLista(int (*fun)(void*), void* Lista);

void genetico(void (*muta)(void*), void (*cruce)(void*), int n, int iteraciones);
