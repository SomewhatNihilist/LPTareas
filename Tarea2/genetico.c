
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

void l_init(tLista *list) {
	list->size = list->pos = 0;
	list->dummy.next = NULL;
	list->head = list->curr = list-> tail = &list->dummy;
}

void l_clear(tLista *list) {
	if (!list->size) return; // Caso vacio
	tNodo *aux;
	while (list->head->next != NULL) { // Elimina la lista desde el primer nodo hacia adelante
		aux = list->head->next;
		list->head->next = aux->next;
		free(aux->dato);
		free(aux);
	}
	list->size = list->pos = 0;
	list->curr = list-> tail = list->head;
}

int l_append(tLista *list, char tipo, void *dato) { // COPIA el dato recibido
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

int l_insert(tLista *list, char tipo, void *dato) { // COPIA el dato recibido
	if (list->pos == list->size) {
		return l_append(list, tipo, dato);
	}
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
	n->next = list->curr->next;
	list->curr->next = n;
	if (list->curr == list->tail) list->tail = n;
	list->size++;
	return 0;
}

tNodo l_remove(tLista *list) {
	tNodo n, *aux;
	n.next = NULL;
	if (list->size <= list->pos) { // Empty or past end of list
		n.tipo = 'x';
		n.dato = NULL;
	} else {
		aux = list->curr->next;
		n.tipo = aux->tipo;
		n.dato = aux->dato;
		list->curr->next = aux->next;
		free(aux);
	}
	return n;
}

tNodo l_getValue(tLista *list) {
	tNodo n;
	n.next = NULL;
	if (list->size <= list->pos) { // Empty or past end of list
		n.tipo = 'x';
		n.dato = NULL;
	} else {
		n.tipo = list->curr->next->tipo;
		n.dato = list->curr->next->dato; // Porfavor no alterar el contenido
	}
	return n;
}

int l_setValue(tLista *list, char tipo, void *dato) {
	if (list->size <= list->pos) { // Empty or past end of list
		return 1;
	}
	// TODO:Reducir esto a algo mas ordenado!
	switch (list->curr->next->tipo) {
		case 'i':
		switch (tipo) {
			case 'i': // int -> int
			*(int*)list->curr->next->dato = *(int*)dato;
			break;
			case 'b':
			case 'c': // int -> char
			void *n = realloc(list->curr->next->dato, sizeof(char));
			if (n == NULL) return 1;
			*(char*)n = *(char*)dato;
			list->curr->next->dato = n;
		}
		break;
		case 'b':
		case 'c':
		switch (tipo) {
			case 'b':
			case 'c': // char -> char
			*(char*)list->curr->next->dato = *(char*)dato;
			break;
			case 'i': // char -> int
			void *n = realloc(list->curr->next->dato, sizeof(int));
			if (n == NULL) return 1;
			*(int*)n = *(int*)dato;
			list->curr->next->dato = n;
		}
	}
	list->curr->next->tipo = tipo;
	return 0;
}

void l_moveToStart(tLista *list) {
	list->curr = list->head;
	list->pos = 0;
}
void l_moveToEnd(tLista *list) {
	list->curr = list->tail;
	list->pos = list->size - 1;
}
void l_next(tLista *list) {
	if (list->size > list->pos) {
		list->curr = list->curr->next;
		list->pos++;
	}
}
void l_moveToPos(tLista *list, int pos) {
	if (pos <= list->size) {
		// TODO
	}
}
// int l_length(tLista *list)
// int l_currPos(tLista *list) we'll be doing these directly.


/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *  NOTE: Aqui comienzan las definiciones de genetico  *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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

void genetico(void (*muta)(void*), void (*cruce)(void*), int n, int iteraciones);
