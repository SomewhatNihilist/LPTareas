#lang scheme
#|
Funcion: fact
Descripcion: obtiene el factorial de un numero entero
Parametros:
x entero
Retorno: Retorna el factorial del numero entregado
|#
(define fact
  (lambda (x)
    (let var ((n x) (i 1))
      (if (= n 0) i (var (- n 1) (* i n))))))
#|
Funcion: rec_cos
Descripcion: Obtiene la aproximacion del coseno de un valor dado
             usando el Teorema de Maclaurin con un numero señalado de iteraciones
             la funcion es implementada con recursion de cola
Parametros:
valor real
iter entero
Retorno: Retorna la aproximacion del coseno del valor dado (valor) en una cantidad de iteraciones dadas (iter)
|#
(define rec_cos
  (lambda (val iter)
    (let var ((res 0) (n 0))
      (if (= n iter)
          res
          (var (+ res (/ (* (expt -1 n) (expt val (* 2 n))) (fact (* 2 n)))) (+ n 1))
          )
      )
    )
  )
#|
Funcion: iter_cos
Descripcion: Obtiene la aproximacion del coseno de un valor dado
             usando el Teorema de Maclaurin con un numero señalado de iteraciones
Parametros:
valor real
iter entero
Retorno: Retorna la aproximacion del coseno del valor dado (valor) en una cantidad de iteraciones dadas (iter)
|#
(define iter_cos
  (lambda (val iter)
    (do ((res 0 (+ res (/ (* (expt -1 n) (expt val (* 2 n))) (fact (* 2 n))))) (n 0 (+ n 1)))
      ((= n iter) res)
      )
    )
  )
;;Test
(rec_cos (/ pi 2) 3)
(iter_cos (/ pi 2) 3)
