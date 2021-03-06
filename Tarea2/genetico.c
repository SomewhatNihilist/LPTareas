
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Para generar un seed aleatorio
#include "lista.h"
#include "fun.h"

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
			case 2: //'b'
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

void mutacionRand(void* Lista) {
	tLista *l = (tLista*)Lista;
	if (l->size == 0) return;
	l_moveToPos(l, rand() % l->size);
	int r; char rc;
	switch (rand()%3) {
		case 0: //'i'
			if (l_getValue(l).tipo == 'i') {
				r = rand()%9; //Evitamos el valor previo
				r = (r < *((int*)l_getValue(l).dato))?r:r+1;
			} else {
				r = rand()%10;
			}
			l_setValue(l, 'i', (void*)(&r));
			break;
		case 1: //'c'
			if (l_getValue(l).tipo == 'c') {
				rc = rand()%5; //Evitamos el valor previo
				rc = ((rc+'A' < *((char*)l_getValue(l).dato))?rc:rc+1) + 'A';
			} else {
				rc = rand()%6 + 'A';
			}
			l_setValue(l, 'c', (void*)(&rc));
			break;
		case 2: //'b'
			if (l_getValue(l).tipo == 'b') { //Si era 'b', solo niega el valor
				*(char*)l_getValue(l).dato = !(*(char*)l_getValue(l).dato);
			} else {
				rc = rand()%2;
				l_setValue(l, 'b', (void*)(&rc));
			}
	}
}

void mutacionTipo(void* Lista) {
	tLista *l = (tLista*)Lista;
	if (l->size == 0) return;
	l_moveToPos(l, rand() % l->size);
	int r; char rc;
	switch (l_getValue(l).tipo) {
		case 'i':
			r = rand()%9; //Evitamos el valor previo
			r = (r < *((int*)l_getValue(l).dato))?r:r+1;
			l_setValue(l, 'i', (void*)(&r));
			break;
		case 'c':
			rc = rand()%5; //Evitamos el valor previo
			rc = ((rc+'A' < *((char*)l_getValue(l).dato))?rc:rc+1) + 'A';
			l_setValue(l, 'c', (void*)(&rc));
			break;
		case 'b':
			*(char*)l_getValue(l).dato = !(*(char*)l_getValue(l).dato);//Negamos
		default:;
	}
}

int evaluacionLista(int (*fun)(void*), void* Lista) {
	//Simplemente iteramos sobre la lista y acumulamos FUN
	tLista *l = (tLista*)Lista;
	tNodo nd; int sum = 0;
	for (l_moveToStart(l); l->pos < l->size; l_next(l)) {
		nd = l_getValue(l);
		sum += (*fun)((void*)&nd);
	}
	return sum;
}

void genetico(void (*muta)(void*), void (*cruce)(void*,void*), int n, int iteraciones) {

	int score_list1, score_list2, score_hijo1, score_hijo2, scoreMutList1, scoreMutList2;
	int bestScore1, bestScore2; // Aqui se guardan los mejores puntajes
	void *list1, *list2, *hijo1, *hijo2, *muta1, *muta2;
	list1 = generarSolucion(n); // Se crea lista 1
	list2 = generarSolucion(n); // Se crea lista 2
	int i;
	for (i = 0 ; i < iteraciones ; i++) { // Se realizan las operaciones dado el numero de iteraciones

		score_list1 = evaluacionLista(fun,list1); // Se obtienen los puntajes de los padres con la funcion evaluacion "fun"
		score_list2 = evaluacionLista(fun,list2);

		hijo1 = copiar(list1);
		hijo2 = copiar(list2);
		cruce(hijo1,hijo2); // Se crean los hijos realizando el cruce
		score_hijo1 = evaluacionLista(fun,hijo1); // Se obtienen los puntajes de los hijos con la funcion evaluacion "fun"
		score_hijo2 = evaluacionLista(fun,hijo2);

		muta1 = copiar(hijo1);
		muta2 = copiar(hijo2);
		muta(muta1); // Se crean hijos mutados realizando las mutaciones
		muta(muta2);
		scoreMutList1 = evaluacionLista(fun,muta1); // Se obtiene el puntaje de las mutaciones usando la funcion evaluacion "fun"
		scoreMutList2 = evaluacionLista(fun,muta2);

		if (score_hijo1 > score_list1 && score_hijo2 > score_list2) {
			//Si los puntajes de ambos hijos son mayores que el de los padres, se reemplazan los padres por los hijos
			borrar(list1);
			borrar(list2);
			list1 = hijo1;
			list2 = hijo2;
			bestScore1 = score_hijo1;
			bestScore2 = score_hijo2;
		} else {
			//En caso contrario, se mantienen los puntajes de los padres
			borrar(hijo1);
			borrar(hijo2);
			bestScore1 = score_list1;
			bestScore2 = score_list2;
		}


		//Si el puntaje de cada mutacion es mejor a su padre, se reemplaza por su padre correspondiente
		if (scoreMutList1 > bestScore1) {
			borrar(list1);
			list1 = muta1;
			bestScore1 = scoreMutList1;
		} else {
			borrar(muta1);
		}
		if (scoreMutList2 > bestScore2) {
			borrar(list2);
			list2 = muta2;
			bestScore2 = scoreMutList2;
		} else {
			borrar(muta2);
		}
	}
	//Se muestra en pantalla los resultados finales
	printf("Lista 1: \n");
	imprimirSolucion(list1);
	printf("Puntaje: %d\n", bestScore1);
	printf("\nLista2: \n");
	imprimirSolucion(list2);
	printf("Puntaje: %d\n", bestScore2);

}

int main_temp() {

	int largo,answer_c,answer_e,answer_b,answer_cruce,answer_mutacion,answer_g;
	void *lista;
	int score_lista;
	printf("Ingrese largo: ");
	scanf("%d",&largo);
	lista = generarSolucion(largo);
	printf("Solucion generada: \n");
	imprimirSolucion(lista);
	printf("Desea copiar la lista: Si(1) No(2): ");
	scanf("%d",&answer_c);
	if (answer_c == 1) {
		void *copia = copiar(lista);
		printf("Copia generada:\n");
		imprimirSolucion(copia);
	}
	printf("Desea evaluar la lista: Si(1) No(2): ");
	scanf("%d",&answer_e);
	if (answer_e == 1) {
		score_lista = evaluacionLista(fun,lista);
		printf("Puntaje obtenido: %d\n",score_lista);
	}
	printf("Desea borrar la lista: Si(1) No(2): ");
	scanf("%d",&answer_b);
	if (answer_b == 1) {
		borrar(lista);
		printf("Lista borrada\n");
	}
	printf("Desea realizar cruces: Si(1) No(2): ");
	scanf("%d",&answer_cruce);
	if (answer_cruce == 1) {
		int len_1,len_2;
		printf("Ingrese largo lista 1: ");
		scanf("%d",&len_1);
		printf("Ingrese largo lista 2: ");
		scanf("%d",&len_2);
		void *lista_1 = generarSolucion(len_1);
		void *lista_2 = generarSolucion(len_2);
		void *copia_1 = copiar(lista_1);
		void *copia_2 = copiar(lista_2);
		printf("Listas generadas:\n");
		imprimirSolucion(lista_1);
		imprimirSolucion(lista_2);
		printf("Se aplica cruce intercalado y medio a las listas dadas\n");
		cruceIntercalado(lista_1,lista_2);
		cruceMedio(copia_1,copia_2);
		printf("Cruce intercalado:\n");
		imprimirSolucion(lista_1);
		imprimirSolucion(lista_2);
		printf("Cruce medio:\n");
		imprimirSolucion(copia_1);
		imprimirSolucion(copia_2);
		borrar(lista_1);
		borrar(lista_2);
		borrar(copia_1);
		borrar(copia_2);
	}
	printf("Desea realizar mutaciones: Si(1) No(2): ");
	scanf("%d",&answer_mutacion);
	if (answer_mutacion == 1) {
		int len_lista;
		printf("Ingrese largo lista : ");
		scanf("%d",&len_lista);
		void *lista_mut = generarSolucion(len_lista);
		void *copia_mut = copiar(lista_mut);
		printf("Lista generada:\n");
		imprimirSolucion(lista_mut);
		printf("Se aplica mutacion random y de tipo a la lista dada\n");
		mutacionRand(lista_mut);
		mutacionTipo(copia_mut);
		printf("Mutacion random:\n");
		imprimirSolucion(lista_mut);
		printf("Mutacion de tipo:\n");
		imprimirSolucion(copia_mut);
		borrar(lista_mut);
		borrar(copia_mut);
	}
	printf("Desea ejecutar la funcion genetico: Si(1) No(2)");
	scanf("%d",&answer_g);
	int len_g,n_iter,mutacion,cruce;
	while(answer_g != 2) {
		printf("Ingrese largo de las listas: ");
		scanf("%d",&len_g);
		printf("Ingrese cantidad de iteraciones: ");
		scanf("%d",&n_iter);
		printf("Elija mutacion: Rand(1) Tipo(2): ");
		scanf("%d",&mutacion);
		printf("Elija cruce: Intercalado(1) Medio(2)\n");
		scanf("%d",&cruce);
		if (mutacion == 1 && cruce == 1) {
			genetico(mutacionRand,cruceIntercalado,len_g,n_iter);
		} else if (mutacion == 1 && cruce == 2) {
			genetico(mutacionRand,cruceMedio,len_g,n_iter);
		} else if (mutacion == 2 && cruce == 1) {
			genetico(mutacionTipo,cruceIntercalado,len_g,n_iter);
		} else if (mutacion == 2 && cruce == 2) {
			genetico(mutacionTipo,cruceMedio,len_g,n_iter);
		}
		printf("Desea ejecutar genetico otra vez: Si(1) No(2): ");
		scanf("%d",&answer_g);
	}
	return 0;
}
