
#include "lista.h"
#include "fun.h"


int fun(void* nodo) {
	tNodo*n = (tNodo*)nodo;
	switch (n->tipo) {
		case 'i': return *(int*)n->dato;
		case 'c': return *(char*)n->dato - 'A' + 10;
		case 'b': return *(char*)n->dato+17;
		default: return 0;
	} //En teoria, termina con numeros altos, donde 'i'<'c'<'b'
}
