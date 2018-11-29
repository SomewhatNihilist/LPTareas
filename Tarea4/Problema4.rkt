#lang scheme
; Problema 4, Replicacion de elementos de una lista

; Por iteracion manual sobre listas
; Argumento lista >= largo que lista_rep (los elementos sobrantes de lista son ignorados)
; Si lista < lista_rep, retorna null
(define (replicar lista lista_rep)
  (if (not (>= (length lista) (length lista_rep))) null
      (let aux ((ls lista) (lsr lista_rep) (outp (list)))
        (cond ((null? lsr) (reverse outp))
              ((<= (car lsr) 0) (aux (cdr ls) (cdr lsr) outp))
              (else (aux ls (list* (- (car lsr) 1) (cdr lsr)) (list* (car ls) outp)))))))

; Por medio de map y append
; Ambos argumentos (lista lista_rep) tienen que ser del mismo largo.
(define (replicar2 lista lista_rep)
  (apply append (map ; genera una lista de listas, posteriormente unida por append
                 (lambda (val rep) ; genera una lista con rep veces val '(val val ...rep... val)
                   (let aux ((i rep) (acc (list)))
                     (if (<= i 0) acc
                         (aux (- i 1) (list* val acc)))))
                 lista lista_rep)))

(define test1 (replicar '(a b c d e) '(1 2 3))) ; Elementos de lista en exceso son ignorados (d e)
(define test2 (replicar '(a b c) '(1 2 3 4))) ; Retorna null cuando lista_rep es mayor
(define test3 (replicar2 '(a b c) '(1 2 3)))
test1
test2
test3
