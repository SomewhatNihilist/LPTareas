
#ifndef LISTA_H_DEFINIDO
#define LISTA_H_DEFINIDO

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

void l_init(tLista *list);
void l_clear(tLista *list);

int l_append(tLista *list, char tipo, void *dato); // COPIA el dato recibido
int l_insert(tLista *list, char tipo, void *dato); // COPIA el dato recibido
tNodo l_remove(tLista *list);

tNodo l_getValue(tLista *list);
int l_setValue(tLista *list, char tipo, void *dato);

void l_moveToStart(tLista *list);
void l_moveToEnd(tLista *list);

void l_next(tLista *list);
void l_moveToPos(tLista *list, int pos);

// int l_length(tLista *list)
// int l_currPos(tLista *list) we'll be doing these directly.

#endif
