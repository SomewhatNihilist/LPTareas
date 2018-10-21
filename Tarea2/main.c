
/* Este archivo es para probar funcionalidad de la libreria creada*/

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "genetico.h"
#include <time.h> // Para generar un seed aleatorio

int main(int argc, char const *argv[]) {
	void *a = generarSolucion(5);
	void *b = generarSolucion(5);
	imprimirSolucion(a); imprimirSolucion(b);
	srand(time(NULL));
	a = generarSolucion(5);
	b = generarSolucion(5);
	imprimirSolucion(a); imprimirSolucion(b);
	return EXIT_SUCCESS;
}
