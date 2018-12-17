% Subconjuntos de suma dada
% Sea W un conjunto de enteros no negativos y M un número entero positivo.
% El problema consiste en implementar un algoritmo para encontrar todos los posibles
% subconjuntos de W cuya suma sea exactamente M


% subconjuntos(W, M, S)
% W = conjunto inicial de enteros no negativos
% M = entero positivo objetivo de los subconjuntos
% S = lista de listas de enteros no negativos con subconjuntos de W que suman M
subconjuntos(W,M,S):-predsort(comp_e,W,T),findall(C,(combina(T,C),suma(C,M)),L),sort(L,S),!.

% combina(L, C)
% L = Lista para la cual generar combinaciones
% C = Combinacion posible para L1
combina(_,[]).
combina([X|T],[X|C]):-combina(T,C).
combina([_|T],[X|C]):-combina(T,[X|C]).

% suma(L, X)
% L = Lista de enteros a sumar
% X = Resultado de la suma
suma([],0).
suma([H|T],X):-suma(T,Y),X is H+Y.

comp_e(<,Term1,Term2):-compare(=,Term1,Term2).
comp_e(<,Term1,Term2):-compare(<,Term1,Term2).
comp_e(>,Term1,Term2):-compare(>,Term1,Term2).

% Problemas de implementacion:
%   Altamente optimizable, ordenar input, sumar elementos hasta que el mayor es
%     demaciado grande, seguir iteracion con menos elementos iniciales.
%   El output puede incluir resultados repetidos cuando el input incluye mas
%     numeros repetidos (ej, ([2,1,2], 3) -> [[2,1],[1,2]])
%     ordenar el input resultaria en repetidos que siempre (?) comparen igual (por orden de los elementos),
%     facilitando limpieza del output final.
%     Eso no quita que el metodo presente sea exhaustivo e ineficiente.
