
#include <stdlib.h>
#include "lista.h"
#include "fun.h"


int fun(void* nodo) {
	tNodo*n = (tNodo*)nodo;
	return rand();
}
