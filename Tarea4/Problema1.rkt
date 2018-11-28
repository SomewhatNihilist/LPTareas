#lang scheme
; Problema 1, Biseccion
; (biseccion funcion intervalo iter)  funcion
;((biseccion funcion) intervalo iter) decorador? no funciona

#|
Funcion: biseccion
Descripcion: Genera una funcion que trata de encontrar un 0 de funcion por el metodo de biseccion.
Parametros: 
  funcion Funcion de un parametro
Retorno: Funcion que accepta un intervalo y un entero.
|#
(define (biseccion funcion) (lambda (intervalo iter) (bis funcion intervalo iter)))
#|
Funcion: bis
Descripcion: Trata de encontrar un cero de foo por medio del metodo de biseccion
Parametros:
  foo Funcion de un parametro
  pair Lista o equivalente con dos numeros correspondientes al intervalo
  iter Entero correspondiente al maximo de iteraciones
Retorno: null si el intervalo es invalido, sino,
         el numero correspondiente a un cero de la funcion foo.
|#
(define (bis foo pair iter)
  (let* ((a (car pair))       ; tecnicamente este let* es inecesario,
         (b (car (cdr pair))) ; pero resulta mas legible asi.
         (m (/ (+ a b) 2)))   ; a b m son solo para facilitar lectura
    (if (and (< a b) (negative? (* (foo a) (foo b)))) ; valid interval?
        (if (or (zero? iter) (zero? (foo m)))
            m ; Max iter or zero found
            (if (negative? (* (foo a) (foo m))) ; do next iter
                (bis foo (list a m) (- iter 1))
                (bis foo (list m b) (- iter 1))))
        null))) ; invalid interval

; Tests
(define test1 ((biseccion (lambda(x)(+ (* x x) (* 2 x) -3))) '(0 2) 10)) ; x^2 + 2x - 3 ... x=-3 x=1 (simetric at -1)
(define (test2 a b) ((biseccion (lambda(x)(+ (* x x x) (* 3 x x) -2))) (list a b) 100))
(define (test3 a b) ((biseccion sin) (list a b) 100))

test1
(writeln (exact->inexact (test3 2 5)))
(writeln pi)