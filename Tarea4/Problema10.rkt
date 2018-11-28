#lang scheme
#|
Funcion: calculo
Descripcion: Calcula el costo de una expresion expr utilizando un conjunto de costos costs
Parametros:
costs (lista)
expr (lista)
Retorno: Retorna el costo de la expresion utilizando el conjunto de costos
|#
(define calculo
  (lambda (costs expr)
    (let var ((expr expr) (res 0))
      (if (null? expr)
          res
          (if (equal? (assq (car expr) costs) #f)
              (var (cdr expr) res)
              (var (cdr expr) (+ res (cdr (assq (car expr) costs))))
              )
          )
      )
    )
  )

;;Test
(calculo (list (cons 'a 20) (cons 'b 50) (cons 'n 10)) '(b a n a n a))
(calculo (list (cons '* 60) (cons '3 30) (cons 'a 10)) '(2 3 b 3 a *))


