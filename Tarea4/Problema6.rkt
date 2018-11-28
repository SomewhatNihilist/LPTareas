#lang scheme
#|
Funcion: cruzar
Descripcion: Realiza el cruce de 2 listas dadas intercambiando el primer trozo de tamaño dado (n)
             de cada lista generando 2 listas nuevas
Parametros:
lista1 
lista2
n entero
Retorno: Retorna 2 listas que han sido cruzadas desde el primer trozo n
|#
(define cruzar
  (lambda (lista1 lista2 n)
    (let var ((S1 '()) (S2 '()) (ls1 lista1) (ls2 lista2))
      (cond
        ((null? ls1) (cons S2 (list S1)))
        (else
         (if (<= (length ls1) n)
             (var (append S1 (list (car ls2))) (append S2 (list (car ls1))) (cdr ls1) (cdr ls2))
             (var (append S1 (list (car ls1))) (append S2 (list (car ls2))) (cdr ls1) (cdr ls2))
             )
         )
        )
      )
    )
  )
;;Test
(cruzar '( a b a a b c) '(a c c b c a) 3)
