
#ifndef LISTA_H_DEFINIDO
#define LISTA_H_DEFINIDO

typedef struct tNodo {
	void* dato; // Claramente todos los tipos de datos caben en un char, pero eso no es lo que se busca para la tarea
	char tipo; // 'i'=int=[0-9], 'c'=char=[A-F], 'b'=char=0,1
	struct tNodo *next;
} tNodo;

typedef struct tLista {
	int size;
	int pos;
	tNodo dummy; // Mucho mas facil de manejar el dummy node sin usar malloc
	tNodo *head; // head = &dummy (tecnicamente inecesario, pero prefiero no referenciar a dummy)
	tNodo *curr;
	tNodo *tail;
} tLista;

/*l_init:
	Inicializa los valores de una tLista "list"
		tLista *list: puntero de lista a inicializar
	Salida:
		void: Sin retorno. */
void l_init(tLista *list);
/*l_clear:
	Elimina los contenidos de una tLista "list" y la re-inicializa
		tLista *list: puntero de lista a reiniciar
	Salida:
		void: Sin retorno. */
void l_clear(tLista *list);

/*l_append:
	Agrega un valor al final de la lista
		tLista *list: puntero de lista a modificar
		char    tipo: tipo del dato a copiar
		void   *dato: puntero del dato a copiar
	Salida:
		int: 0 si funciona, 1 si hubo un error de memoria. */
int l_append(tLista *list, char tipo, void *dato); // COPIA el dato recibido
/*l_insert:
	Agrega un valor a la pocicion presente en la lista
		tLista *list: puntero de lista a modificar
		char    tipo: tipo del dato a copiar
		void   *dato: puntero del dato a copiar
	Salida:
		int: 0 si funciona, 1 si hubo un error de memoria. */
int l_insert(tLista *list, char tipo, void *dato); // COPIA el dato recibido
/*l_getValue:
	Remueve el valor a la pocicion presente de la lista
		tLista *list: puntero de lista a modificar
	Salida:
		tNodo: . */
tNodo l_remove(tLista *list);

/*l_getValue:

		tLista *list: puntero de lista a leer
	Salida:
		tNodo: . */
tNodo l_getValue(tLista *list);
/*l_setValue:

		tLista *list: puntero de lista a modificar
		char    tipo: tipo del dato a copiar
		void   *dato: puntero del dato a copiar
	Salida:
		int: 0 si funciona, 1 si hubo un error de memoria. */
int l_setValue(tLista *list, char tipo, void *dato);

/*l_moveToStart:
	Cambia la pocision de tLista "list" al inicio de esta.
		tLista *list: puntero de lista a modificar
	Salida:
		void: Sin retorno. */
void l_moveToStart(tLista *list);
/*l_moveToEnd:
	Cambia la pocision de tLista "list" al ultimo nodo accesible. Esto es list.pos == list.size - 1
		tLista *list: puntero de lista a modificar
	Salida:
		void: Sin retorno. */
void l_moveToEnd(tLista *list);


/*l_next:
	Avanza la pocision de tLista "list" en 1. Notese que el valor maximo es list.size
		tLista *list: puntero de lista a modificar
	Salida:
		void: Sin retorno. */
void l_next(tLista *list);
/*l_moveToPos:
	Cambia la pocision de tLista "list" a "pos". Notese que el valor maximo es list.size
		tLista *list: puntero de lista a modificar
		int     pos : valor de la pocicion final. pos <= 0 resulta en 0 y pos >= list.size resulta en list.size
	Salida:
		void: Sin retorno. */
void l_moveToPos(tLista *list, int pos);

// int l_length(tLista *list)
// int l_currPos(tLista *list) we'll be doing these directly.

// Any lower level operations we'll be doing directly

#endif
