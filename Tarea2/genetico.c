
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Para generar un seed aleatorio
#include "lista.h"

#include "genetico.h"

/* definidos en lista.h

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
		switch (rand()%3) {
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
	}
	return (void*)l;
}

void* copiar(void* Lista) {
	tLista *l = (tLista*)Lista;
	tLista *out = (tLista*)malloc(sizeof(tLista));
	if (out == NULL) return NULL;
	l_init(out);
	tNodo curr;
	for (l_moveToStart(l); l->pos < l->size; l_next(l)) {
		curr = l_getValue(l);
		l_append(out, curr.tipo, curr.dato);
	}
	return (void*)out;
}

void borrar(void* Lista) {
	l_clear((tLista*)Lista);
	free(Lista);
}

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

void cruceMedio(void* Lista1, void* Lista2) {
	tLista *l1, *l2 = (tLista*)Lista2; l1 = (tLista*)Lista1; // More readable
	tNodo *aux;
	// Ahora, podriamos usar el TDA lista desde afuera...
	//o podemos abusar nuestro acceso de la funcionalidad interna, mas facil y eficiente
	if (l1->size < 2) { //Nada que cambiar
	} else {
		l_moveToPos(l1, l1->size/2); l_moveToPos(l2, l1->size/2); // Se asume que ambas tienen mismo tamaño
		aux = l1->curr->next;
		l1->curr->next = l2->curr->next;
		l2->curr->next = aux;
		aux = l1->head->next;
		l1->head->next = l2->head->next;
		l2->head->next = aux;
		l_moveToStart(l1); l_moveToStart(l2);
		//if (l1->size > 1) { //size == 1 entonces tail == head que es constante
	}
}

void cruceIntercalado(void* Lista1, void* Lista2) {
	//Se podria crear un helper de cruce en pos X y cruceIntercalado solo seria cruzar cada pocision de las listas (partiendo de 0)
	//size = 4        tail
	//headdummy--1--0-t1--0--||
	//                tail cambia cuando size es par
	//size = 5           tail
	//headdummy--1--0--1-t0--1--||
	//                   tail NO cambia cuando size es impar
	//size = 1 tail=head
	//headtaildummy--1--||
	//               tail NO cambia cuando size es impar

	//0. cambiamos tail si es necesario
	//1. hacemos lo mismo que en cruce medio por cada pocision en la lista
	//2. ???
	//3. Profit
	tLista *l1, *l2 = (tLista*)Lista2; l1 = (tLista*)Lista1; // More readable
	tNodo *aux;
	if (l1->size == 0) {
	} else {
		if (l1->size % 2 == 0) {
			aux = l1->tail;
			l1->tail = l2->tail;
			l2->tail = aux;
		}
		for (l_moveToStart(l1), l_moveToStart(l2); l1->pos < l1->size; l_next(l1), l_next(l2)) {
			aux = l1->curr->next;
			l1->curr->next = l2->curr->next;
			l2->curr->next = aux;
		}
	}
}

void mutacionRand(void* Lista);

void mutacionTipo(void* Lista);

int evaluacionLista(int (*fun)(void*), void* Lista) {
	tLista *l = (tLista*)Lista;
	tNodo nd; int sum = 0;
	for (l_moveToStart(l); l->pos < l->size; l_next(l)) {
		nd = l_getValue(l);
		sum += (*fun)((void*)&nd);
	}
	return sum;
}

void genetico(void (*muta)(void*), void (*cruce)(void*,void*), int n, int iteraciones);
