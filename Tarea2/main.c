
/* Este archivo es para probar funcionalidad de la libreria creada*/

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "genetico.h"
#include <time.h> // Para generar un seed aleatorio

void printNodo(tNodo node);

int testing_functionality();

int main(int argc, char const *argv[]) {
	return testing_functionality();
}

int testing_functionality() {
	int testi = 8; char testc = 'D'; char testb = 0; tNodo nodo;
	srand(0);
	void *a = generarSolucion(5);
	void *b = generarSolucion(5);

	//Tests basicos
	printf("a: "); imprimirSolucion(a); //(E, c) (5, i) (1, b) (A, c) (1, i)
	printf("b: "); imprimirSolucion(b); //(1, b) (1, b) (0, b) (6, i) (E, c)
	printf("Movement: %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); //5 (!, x) //imprimirSolucion no resetea la pocicion cuando termina.
	l_moveToStart((tLista*)a); printNodo(l_getValue((tLista*)a)); //(E, c)
	l_moveToPos((tLista*)a, 3); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 3 (A, c)
	l_moveToEnd((tLista*)a); printNodo(l_getValue((tLista*)a)); //(1, i)
	l_moveToPos((tLista*)a, 1); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 1 (5, i)
	//  Test remove
	printf("\nRemove       : "); nodo = l_remove((tLista*)a); printNodo(nodo); // (5, i)
	printf(" pos:%d, size:%d ", ((tLista*)a)->pos, ((tLista*)a)->size); printNodo(l_getValue((tLista*)a)); // pos:1, size:4 (1, b)
	printf("\n    result: ");imprimirSolucion(a); //(E, c) (1, b) (A, c) (1, i)
	printf("  remove last: "); l_moveToEnd((tLista*)a); nodo = l_remove((tLista*)a); printNodo(nodo); //(1, i)
	printf(" pos:%d, size:%d ", ((tLista*)a)->pos, ((tLista*)a)->size); printNodo(l_getValue((tLista*)a)); // pos:3, size:3 (!, x)
	printf("\n    result: ");imprimirSolucion(a); //(E, c) (1, b) (A, c)
	//  Test insert
	l_moveToPos((tLista*)a, 1);
	printf("\nInsert: "); l_insert((tLista*)a, 'i', &testi); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 1 (8, i)
	l_next((tLista*)a); l_next((tLista*)a); l_insert((tLista*)a, 'c', &testc); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 3 (D, c)
	l_moveToEnd((tLista*)a); l_next((tLista*)a); l_insert((tLista*)a, 'b', &testb); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 5 (0, b)
	l_moveToStart((tLista*)a); l_insert((tLista*)a, 'b', &testb); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 0 (0, b)
	printf("\n    a: "); imprimirSolucion(a); //(0, b) (E, c) (8, i) (1, b) (D, c) (A, c) (0, b)
	//Test de copia
	borrar(a); a = copiar(b);
	printf("\na = copia(b): (a)%p %c= (b)%p\n", a, a==b?'=':'!', b); printf("a: "); imprimirSolucion(a);
	borrar(a); borrar(b);

	srand(0);
	a = generarSolucion(6);
	b = generarSolucion(6);
	void *c = copiar(a);
	void *d = copiar(b);
	//Test cruces:
	printf("\nCruces:\n    a: "); imprimirSolucion(a); //(E, c) (5, i) (1, b) (A, c) (1, i)
	printf("    b: "); imprimirSolucion(b); //(1, b) (1, b) (0, b) (6, i) (E, c)
	printf("\n medio:\n    a: "); cruceMedio(a, b); imprimirSolucion(a);
	printf("    b: "); imprimirSolucion(b);
	printf("\n inter:\n    a: "); cruceIntercalado(c, d); imprimirSolucion(c);
	printf("    b: "); imprimirSolucion(d);

	l_moveToStart((tLista*)a); printNodo(l_getValue((tLista*)a)); //(E, c)
	l_moveToPos((tLista*)a, 3); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 3 (A, c)
	l_moveToEnd((tLista*)a); printNodo(l_getValue((tLista*)a)); //(1, i)
	l_moveToPos((tLista*)a, 1); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 1 (5, i)
	//  Test remove
	printf("\nRemove       : "); nodo = l_remove((tLista*)a); printNodo(nodo); // (5, i)
	printf(" pos:%d, size:%d ", ((tLista*)a)->pos, ((tLista*)a)->size); printNodo(l_getValue((tLista*)a)); // pos:1, size:4 (1, b)
	printf("\n    result: ");imprimirSolucion(a); //(E, c) (1, b) (A, c) (1, i)
	printf("  remove last: "); l_moveToEnd((tLista*)a); nodo = l_remove((tLista*)a); printNodo(nodo); //(1, i)
	printf(" pos:%d, size:%d ", ((tLista*)a)->pos, ((tLista*)a)->size); printNodo(l_getValue((tLista*)a)); // pos:3, size:3 (!, x)
	printf("\n    result: ");imprimirSolucion(a); //(E, c) (1, b) (A, c)
	//  Test insert
	l_moveToPos((tLista*)a, 1);
	printf("\nInsert: "); l_insert((tLista*)a, 'i', &testi); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 1 (8, i)
	l_next((tLista*)a); l_next((tLista*)a); l_insert((tLista*)a, 'c', &testc); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 3 (D, c)
	l_moveToEnd((tLista*)a); l_next((tLista*)a); l_insert((tLista*)a, 'b', &testb); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 5 (0, b)
	l_moveToStart((tLista*)a); l_insert((tLista*)a, 'b', &testb); printf(" %d ", ((tLista*)a)->pos); printNodo(l_getValue((tLista*)a)); // 0 (0, b)
	printf("\n    a: "); imprimirSolucion(a); //(0, b) (E, c) (8, i) (1, b) (D, c) (A, c) (0, b)
	//Test de copia
	borrar(a); a = copiar(b);
	printf("\na = copia(b): (a)%p %c= (b)%p\n", a, a==b?'=':'!', b); printf("a: "); imprimirSolucion(a);

	borrar(a); borrar(b); borrar(c); borrar(d);
	return EXIT_SUCCESS;
}


void printNodo(tNodo node) {
	switch (node.tipo) {
		case 'i': printf("(%d, %c)", *(int*)node.dato, node.tipo); break;
		case 'c': printf("(%c, %c)", *(char*)node.dato, node.tipo); break;
		case 'b': printf("(%hhd, %c)", *(int*)node.dato, node.tipo); break;
		default: printf("(!, %c)", node.tipo); break;
	}
}
