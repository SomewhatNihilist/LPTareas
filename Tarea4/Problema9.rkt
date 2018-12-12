#lang scheme
; Problema 9, Generar permutaciones

(define (intercambiar n m lst)
  (let inter ((i 0) (frente '()) (medio '()) (ls lst))
    (
