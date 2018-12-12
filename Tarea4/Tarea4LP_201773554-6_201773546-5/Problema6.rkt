#lang scheme
#|
Funcion: cruzar
Descripcion: Realiza el cruce de 2 listas dadas intercambiando el primer trozo de tamaño dado (n)
             de cada lista generando 2 listas nuevas
Parametros:
lista1 
lista2
n entero
Retorno: Retorna una lista con las 2 listas que han sido cruzadas desde el primer trozo n
|#
(define (cruzar lista1 lista2 n)
  (if (<= (length lista1) n) (list lista2 lista1) ; Edge-case optimisation
      (let cutl ((S1 '()) (S2 '()) (ls1 lista1) (ls2 lista2))
        (if (>= (length S1) n) (list (append (reverse S2) ls1) (append (reverse S1) ls2))
            (cutl (cons (car ls1) S1) (cons (car ls2) S2) (cdr ls1) (cdr ls2))))))
#|
(define (cruzar2 lista1 lista2 n)
  (if (<= (length lista1) n) (list lista2 lista1) ; Edge-case optimisation
      (let var ((S1 '()) (S2 '()) (ls1 lista1) (ls2 lista2))
        (cond
          ((null? ls1) (list S2 S1))
          ((<= (length ls1) n) (var (append S1 (list (car ls2))) (append S2 (list (car ls1))) (cdr ls1) (cdr ls2)))
          (else                (var (append S1 (list (car ls1))) (append S2 (list (car ls2))) (cdr ls1) (cdr ls2)))
          ))))|#
;;Test
#|
(cruzar '( a b a a b c) '(a c c b c a) 1)
(cruzar '( a b a a b c) '(a c c b c a) 2)
(cruzar '( a b a a b c) '(a c c b c a) 3)
(cruzar '( a b a a b c) '(a c c b c a) 4)
(cruzar '( a b a a b c) '(a c c b c a) 5)
(cruzar '( a b a a b c) '(a c c b c a) 6)
(cruzar '( a b a a b c) '(a c c b c a) 7)
|#