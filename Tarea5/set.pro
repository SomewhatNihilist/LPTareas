% Para este problema se pide emular el funcionamiento de métodos de un diccionario
% de Python a través de consultas.
  % Agregar: Se pide agregar un elemento con su llave correspondiente al diccionario.
  % Obtener valor: Dado una llave retornar el valor relacionado.
  % Obtener llaves: Retornar todas las llaves que se han agregado hasta el momento.
  % Obtener todos los valores: Retornar todos los valores que se han agregado hasta el momento .
  % Largo: Retornar la cantidad de relaciones que se tienen en el diccionario.



% agregar(D, K, V, Dret).
% D = diccionario a modificar
% K = llave a agregar/modificar
% V = valor a agregar/modificar
% Dret = diccionario resultante de agregar/modificar la realacion de K
agregar([], K, V, [[K,V]]).
agregar([[K,_]|T], K, V, [[K,V]|T]).
agregar([[X,Y]|T], K, V, [[X,Y]|Tp]):-dif(X,K),agregar(T, K, V, Tp).

% obtener(D, K, V).
% D = diccionario a leer
obtener([[K,V]|_], K, V).
obtener([_|T], K, V):-obtener(T, K, V).

% llaves(D, L).
% D = diccionario a leer
% L = Lista de llaves en el diccionario
llaves([], []).
llaves([[K,_]|T], [K|Y]):-llaves(T,Y).

% valores(D, L).
% D = diccionario a leer
% L = Lista de valores en el diccionario
valores([], []).
valores([[_,V]|T], [V|Y]):-valores(T,Y).

% largo(D, N).
% D = diccionario a leer
% N = Numero de relaciones en el diccionario
largo([], 0).
largo([_|T], N):-largo(T,M), N is M + 1.
