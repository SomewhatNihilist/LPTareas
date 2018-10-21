
#include <stdlib.h>

#include "lista.h"


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
	void *n;
	switch (list->curr->next->tipo) {
		case 'i':
			switch (tipo) {
				case 'i': // int -> int
					*(int*)list->curr->next->dato = *(int*)dato;
					break;
				case 'b':
				case 'c': // int -> char
					n = realloc(list->curr->next->dato, sizeof(char));
					if (n == NULL) return 1;
					*(char*)n = *(char*)dato;
					list->curr->next->dato = n;
					break;
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
					n = realloc(list->curr->next->dato, sizeof(int));
					if (n == NULL) return 1;
					*(int*)n = *(int*)dato;
					list->curr->next->dato = n;
					break;
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


//En retrospectiva, python ha hecho que mi estilo de codigo sea muy object oriented -Gonzalo
