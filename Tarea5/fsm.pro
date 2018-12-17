% Un autómata finito o maquina de estados finitos, es un modelo matemático de una
%   máquina que acepta cadenas de un lenguaje definido sobre un alfabeto.
% Consiste en un conjunto finito de estados y un conjunto de transiciones entre
%   esos estados, que dependen de los sı́mbolos de la cadena de entrada.
% El autómata finito acepta una cadena x si la secuencia de transiciones
%   correspondientes a los sı́mbolos de x conduce desde el estado inicial a un estado final.
% Se pide diseñar un autómata que cumpla las siguientes condiciones:
  % Mı́nimo 10 estados.
  % Mı́nimo 2 estados de aceptación.
  % El alfabeto debe contener mı́nimo 3 sı́mbolos.
  % Mı́nimo un ciclo (mı́nimo de tres estados).
  % Todas los sı́mbolos del alfabeto deben ocuparse en al menos una transición.
% Además, se debe poder realizar una consulta, dado una cadena de sı́mbolos, saber
% si esta pertenece al lenguaje o no, entregando el estado en que se detuvo

e(q0,d,q1).
e(q1,b,q2).
e(q2,a,q3).
e(q3,b,q3).
e(q3,a,q4).
e(q4,b,q2).
e(q4,d,q6).
e(q6,b,q7).
e(q4,c,q5).
e(q5,b,q8).
e(q8,d,q9).
e(q9,c,q10).

alfabeto(a).
alfabeto(b).
alfabeto(c).
alfabeto(d).

es_lenguaje(L, Q, B):-es_lenguaje(L, q0, Q, B).
es_lenguaje([], q7, q7, true):-!.
es_lenguaje([], q10, q10, true):-!.
es_lenguaje([X|T], S, Q, B):- alfabeto(X), e(S, X, S1), es_lenguaje(T, S1, Q, B),!;
                              Q = S, B = false,!.
