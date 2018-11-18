#lang racket
; (biseccion funcion intervalo iter)  funcion
;((biseccion funcion) intervalo iter) decorador
#|(define (biseccion foo pair num)
  (let ((m (/ (- (car pair) (car(cdr pair))) 2))) (m)))|#

#|(define ((biseccion foo) pair iter)
  (let* ((a (car pair))
         (b (car (cdr pair)))
         (m (/ (- b a))))
    (if (foo m) (1) (0))))|#

(define (biseccion foo pair iter)
  (let* ((a (car pair))
         (b (car (cdr pair)))
         (m (/ (+ a b) 2)))
    (if (and (< a b) (negative? (* (foo a) (foo b)))) ; valid interval?
        (if (or (zero? iter) (zero? (foo m)))
            m ; Max iter or found
            (if (negative? (* (foo a) (foo m))) ; do function
                (biseccion foo (list a m) (- iter 1))
                (biseccion foo (list m b) (- iter 1))))
        null)))

(define test1 (biseccion (lambda(x)(+ (* x x) (* 2 x) -3)) '(0 2) 10)) ; x^2 + 2x - 3 ... x=-3 x=1 (simetric at -1)
(define (test2 a b) (biseccion (lambda(x)(+ (* x x x) (* 3 x x) -2)) (list a b) 100))
(define (test3 a b) (biseccion sin (list a b) 100))
(writeln (exact->inexact (test3 2 5)))
(writeln pi)