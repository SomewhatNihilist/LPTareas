#Tarea 2 Lenguajes de Programacion
Integrantes:
  Gonzalo Cruz Masferrer   201773554-6
  Esteban Carrasco Galdame 201773546-5


##Compilacion:
1.-Preparar archivos de evaluacion: Notese que los contenidos son solo de referencia.
(DENTRO DE LA MISMA CARPETA QUE LOS DEMAS ARCHIVOS)
  fun.h :
    int fun(void* nodo);
  fun.c :
    #include "lista.h" \\ Contiene tNodo, pero la estructura pude ser copiada directamente
    int fun(void* nodo) {
      \* funcion de evaluacion de tNodo *\
    }
  main.c :
    #include <stdlib.h>
    #include <>
    #include "genetico.h"
    int main(int argc, char const *argv[]) {
      srand(time(0));
      /* codigo a ejecutar para evaluacion */
      return 0;
    }
2.-Ejecutar en terminal:
  make
  ./main
3.-???
4.-Profit.


##Supuestos:
La función de evaluación se llama "fun", definida como "int fun(void* nodo)" en "fun.c", con su header respectivo "fun.h".
El archivo fun.c, fun.h y main.c no seran evaluados. La funcion "int main()" no sera evaluada.
Ambos cruceMedio y cruceIntercalado modifican ambas listas entrantes, y ambas listas son de igual tamaño.
La funcion "genetico(m, c, n, i)" siempre se ejecuta con "n > 0" e "i > 0".
