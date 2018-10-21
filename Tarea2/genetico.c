
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
	// srand(time(0));
	tLista *l = (tLista*)malloc(sizeof(tLista));
	if (l == NULL) return NULL;
	l_init(l);
	int r; char rc;
	for (int i = 0; i < largo; i++) {
		r = rand();
		switch (r%3) {
			case 0: //'i'
				r = rand()%10;
				l_append(l, 'i', (void*)&r);
				break;
			case 1: //'c'
				rc = 'A' + (char)(rand()%6);
				l_append(l, 'c', (void*)&rc);
				break;
			case 2:
				rc = (char)(rand()%2);
				l_append(l, 'b', (void*)&rc);
				break;
		}
		//TODO?
	}
	return (void*)l;
}

void* copiar(void* Lista) {
	return NULL;
}

void borrar(void* Lista);

void imprimirSolucion(void* Lista) {
	// "formato (dato,tipo)"... como "(1,i), (D,c), (0,b)" o separado por lineas?
	tLista *l = (tLista*)Lista;
	tNodo nd;
	for (l_moveToStart(l); l->pos < l->size; l_next(l)) {
		nd = l_getValue(l);
		switch (nd.tipo) {
			case 'i': printf("(%d, %c) ", *(int*)nd.dato, nd.tipo); break;
			case 'c': printf("(%c, %c) ", *(char*)nd.dato, nd.tipo); break;
			case 'b': printf("(%hhd, %c) ", *(int*)nd.dato, nd.tipo); break;
			default: printf("(!, %c) ", nd.tipo); break;
		}
	}
	printf("\n");
}

void cruceMedio(void* Lista1, void* Lista2);

void cruceIntercalado(void* Lista1, void* Lista2);

void mutacionRand(void* Lista);

void mutacionTipo(void* Lista);

int evaluacionLista(int (*fun)(void*), void* Lista);

void genetico(void (*muta)(void*), void (*cruce)(void*,void*), int n, int iteraciones);
