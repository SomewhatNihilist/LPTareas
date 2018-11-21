#lang scheme
; Problema 7, Operaciones entre binarios

(define (bin->bool b) (if (or (= b 0) (= b 1))
                          (if (zero? b) #f #t)
                          (raise-argument-error 'bin->bool
                                                "0 or 1"
                                                b)))
(define (bool->bin b) (if b 1 0))

(define (operar foo lst1 lst2)
  (if (= (length lst1) (length lst2))
      (map (lambda (a b) (bool->bin (foo (bin->bool a) (bin->bool b)))) lst1 lst2)
      (raise-argument-error 'operar
                            "(= (length lst1) (length lst2))"
                            (format "(= ~a ~a)" (length lst1) (length lst2)))))


(operar xor (list 0 1 1 1) (list 0 0 1 0))

