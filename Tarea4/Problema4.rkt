#lang scheme
; Problema 4, Replicacion de elementos de una lista

#|
Funcion: replicar
Descripcion: Se recibe una lista a replicar y otra lista que indica cuantas veces
             se debe replicar cada posicion de la primera lista
Parametros:
lista (lista a replicar)
lista_rep (lista indicando cantidad de veces a replicar la lista anterior)
Retorno: Retorna una lista que es el resultado de replicar la lista original con la cantidad de
         veces mencionadas en lista_rep, si lista < lista_rep, retorna null
         y si lista >= largo que lista_rep (los elementos sobrantes de lista son ignorados)
|#
(define (replicar lista lista_rep)
  (if (not (>= (length lista) (length lista_rep))) null
      (let aux ((ls lista) (lsr lista_rep) (outp (list)))
        (cond ((null? lsr) (reverse outp))
              ((<= (car lsr) 0) (aux (cdr ls) (cdr lsr) outp))
              (else (aux ls (list* (- (car lsr) 1) (cdr lsr)) (list* (car ls) outp)))))))

(define test1 (replicar '(a b c d e) '(1 2 3))) ; Elementos de lista en exceso son ignorados (d e)
(define test2 (replicar '(a b c) '(1 2 3 4))) ; Retorna null cuando lista_rep es mayor
(define test3 (replicar2 '(a b c) '(1 2 3)))
test1
test2
test3
