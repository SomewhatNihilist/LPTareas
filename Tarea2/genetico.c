
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Para generar un seed aleatorio

/* TODO: Preguntar si se pueden tener lista.c y .h para que sea mas ordenado...
"Las funciones deben ser desarrolladas e implementadas en el archivo genetico.c, junto con sus propias definiciones de las listas a utilizar"
What does it mean...? */

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

void lista_init(tLista *list) {
	list->size = list->pos = 0;
	list->dummy.next = NULL;
	list->head = list->curr = list-> tail = &list->dummy;
}

void lista_clear(tLista *list) {
	if (!list->size) return; // Caso vacio
	tNodo *aux;
	while (list->head->next != NULL) { // Elimina la lista desde el primer nodo hacia adelante
		aux = list->head->next;
		list->head->next = aux->next;
		free(aux);
	}
	list->size = list->pos = 0;
	list->curr = list-> tail = list->head;
}

int lista_append(tLista *list, char tipo, void *dato) { // COPIA el dato recibido
	void *d;
	switch (tipo) {
		case 'i':
		d = malloc(sizeof(int));
		if (d == NULL) return 1;
		*(int*)d = *(int*)dato;
		break;
		case 'c': // Son el mismo tipo
		case 'b':
		d = malloc(sizeof(char));
		if (d == NULL) return 1;
		*(char*)d = *(char*)dato;
		break;
		default: return 1; // WTF did ya give me!?
	}
	tNodo *n = (tNodo*)malloc(sizeof(tNodo));
	if (n == NULL) {free(d); return 1;}
	n->tipo = tipo;
	n->dato = d;
	n->next = NULL;
	if (list->size) {
		list->tail = list->tail->next;
	}
	list->tail->next = n;
	list->size++;
	return 0;
}

int lista_insert(tLista *list, char tipo, void *dato) { // COPIA el dato recibido
	void *d;
	switch (tipo) {
		case 'i':                        // int
		d = malloc(sizeof(int));
		if (d == NULL) return 1;
		*(int*)d = *(int*)dato;
		break;
		case 'c': // Son el mismo tipo
		case 'b':                        // char
		d = malloc(sizeof(char));
		if (d == NULL) return 1;
		*(char*)d = *(char*)dato;
		break;
		default: return 1; // WTF did ya give me!?
	}
	tNodo *n = (tNodo*)malloc(sizeof(tNodo));
	if (n == NULL) {free(d); return 1;}
	n->tipo = tipo;
	n->dato = d;
	//TODO

	return 0;
}







// NOTE: Aqui comienzan las definiciones de genetico

void* generarSolucion(int largo) {
	srand(time(0));
	return NULL;
}

void* copiar(void* Lista) {
	return NULL;
}

void borrar(void* Lista);

void imprimirSolucion(void* Lista);

void cruceMedio(void* Lista1, void* Lista2);

void cruceIntercalado(void* Lista1, void* Lista2);

void mutacionRand(void* Lista);

void mutacionTipo(void* Lista);

int evaluacionLista(int (*fun)(void*), void* Lista);

void genetico(void (*muta)(void*), void (*cruce)(void*), int n, int iteraciones);
