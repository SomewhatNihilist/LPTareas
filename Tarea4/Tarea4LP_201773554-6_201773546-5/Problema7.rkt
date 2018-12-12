#lang scheme
; Problema 7, Operaciones entre binarios

(define (operar func) (lambda(lista1 lista2) (map func lista1 lista2)))

;; Test
(define (xor a b) (if (not (= a b)) 1 0))
((operar xor) (list 0 1 1 1) (list 0 0 1 0))

