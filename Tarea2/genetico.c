
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Para generar un seed aleatorio

#include "lista.h"

/* definidos en list_structs.h, importados por lista.h

typedef struct tNodo {
	void* dato; // Claramente todos los tipos de datos caben en un char, pero eso no es lo que se busca para la tarea
	char tipo; // 'i'=int=[0-9], 'c'=char=[A-F], 'b'=char=0,1
	tNodo *next;
} tNodo;

typedef struct tLista {
	int size;
	int pos;
	tNodo dummy; // Mucho mas facil de manejar el dummy node sin un malloc
	tNodo *head; // head = &dummy (tecnicamente inecesario, pero prefiero no referenciar a dummy)
	tNodo *curr;
	tNodo *tail;
} tLista;
*/

void* generarSolucion(int largo) {
	srand(time(0));
	return NULL;
}

void* copiar(void* Lista) {
	return NULL;
}

void borrar(void* Lista);

void imprimirSolucion(void* Lista) {
	// "formato (dato,tipo)"... como "(1,i), (D,c), (0,b)" o separado por lineas
}

void cruceMedio(void* Lista1, void* Lista2);

void cruceIntercalado(void* Lista1, void* Lista2);

void mutacionRand(void* Lista);

void mutacionTipo(void* Lista);

int evaluacionLista(int (*fun)(void*), void* Lista);

void genetico(void (*muta)(void*), void (*cruce)(void*,void*), int n, int iteraciones);
