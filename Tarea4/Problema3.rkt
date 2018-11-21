#lang scheme
; Problema 3, Suma de nodos de un arbol
; Nodo: '(valor_nodo arbol_izquierdo arbol_derecho)

(define (hoja? node) (andmap null? (cdr node))) ; Not used.

(define (gln node) (car (cdr node))) ; get_left_node
(define (grn node) (car (cdr (cdr node)))) ; get_right_node

(define (suma_arbol arbol numero)
  (let aux ((node arbol) (sum numero))
    (if (null? node) null
        (if (= numero (car node)) sum
            (if (< numero (car node))
                (aux (gln node) (+ sum (car node)))
                (aux (grn node) (+ sum (car node))))))))

(suma_arbol '(8 (3 (1 () ()) (6 (4 () ()))) (10 () ())) 1)
