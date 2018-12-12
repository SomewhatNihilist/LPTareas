#lang scheme
; Problema 3, Suma de nodos de un arbol
; Nodo: '(valor_nodo arbol_izquierdo arbol_derecho)

#|
Funcion: suma_arbol
Descripcion: el algoritmo busca un numero entregado y suma los nodos que recorrio
	     incluyendo la raiz y el numero buscado
Parametros:
arbol 
numero entero
Retorno: Retorna un entero indicando la suma mencionada en la descripcion de la funcion
|#
(define (suma_arbol arbol numero)
  (let aux ((node arbol) (sum numero))
    (cond ((null? node) null)
      ((= numero (car node)) sum)
      ((< numero (car node))
       (aux (cadr node) (+ sum (car node)))) ; get_left_node
      (else (aux (caddr node) (+ sum (car node))))))) ; get_right_node

(suma_arbol '(8 (3 (1 () ()) (6 (4 () ()))) (10 () ())) 1)
