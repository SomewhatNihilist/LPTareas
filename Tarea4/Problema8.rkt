#lang scheme
; Problema 8, Componentes de un grafo
#|
Funcion: componentes
Descripcion: Encuentra el numero de componentes de un grafo de la
       forma '((id_nodo (id_vecino ...)) ...) donde se asume que
       id_nodo (y consecuentememte id_vecino) son reconocibles
       por medio de eqv?
Parametros:
grafo Lista de listas que representa un grafo o '()
Retorno: Numero de componentes de grafo.
|#
(define (componentes grafo)
  (let comps ((gra grafo) (n 0)) ; Contamos componentes por eliminacion (y busqueda a lo ancho)
    (if (null? gra) n ; Caso base, grafo vacio, retorna cuenta total
        (do ((rev  (list (caar gra)); Nodos ya revisados
                   (cons (car pend) rev))
             (pend (cadar gra)      ; Nodos a revisar
                   (append (cdr pend) (filter (lambda(x)(not (or (memv x rev) (memv x pend))))
                                              (cadr (assv (car pend) g))))) ; Filtramos los nodos en rev y pend
             (g    (cdr gra)        ; Grafo que pierde nodos por iteracion
                   (remove (car pend) g (lambda (x y) (= x (car y)))))
             )
          ((null? pend) (comps g (+ n 1))))))) ; Contamos el componente eliminado y aplicamos al resto

; (componentes '((1 (2 3)) (2 (1 4)) (3 (1)) (4 (2)) (5 (6)) (6 (5)) (7 ())))