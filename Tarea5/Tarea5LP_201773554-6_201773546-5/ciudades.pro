% Alcance de ciudades
% Se tiene una cantidad de combustible limitada con la que se quiere viajar.
% El problema trata de encontrar todas las ciudades alcanzables desde una ciudad
%   inicial con la cantidad de combustible disponible.
% Para esto se pide implementar un grafo dirigido donde el peso de cada arco es
%   la cantidad de combustible que se consume desde una ciudad a otra.
% El mapa de las ciudades debe ser diseñado por el grupo, cumpliendo las siguientes condiciones:
  % Mı́nimo 10 ciudades.
  % Mı́nimo 15 arcos.
  % Todas las ciudades deben ser alcanzables desde cada una.
  % Los pesos de los arcos no pueden ser todos iguales.
  % Debe presentar al menos un ciclo.
  % No se permitirá tener hechos que indiquen explı́citamente todos los posibles
  %   peso_rutas o peso total desde una ciudad a otra.

ed(a,b,3).
ed(b,c,4).
ed(c,d,5).
ed(d,e,6).
ed(e,f,2).
ed(f,g,3).
ed(g,h,9).
ed(h,i,4).
ed(i,j,12).
ed(j,a,1).
ed(a,k,15).
ed(k,l,13).
ed(l,d,15).
ed(k,m,8).
ed(m,g,7).

peso_ruta(X,Y,P):-peso_ruta(X,Y,P,[X]).
peso_ruta(X,Y,P,_):-ed(X,Y,P).
peso_ruta(X,Y,P, T):-ed(X,B,P1),\+member(B,T),
    append(T,[B],T1),peso_ruta(B,Y,P2,T1), P is P1 + P2.

% alcanzables(X, C, D).
% X = Ciudad inicial
% C = Combustible disponible
% D = Lista de ciudades destino alcanzables
alcanzables(X, C, D):-findall(Y,(peso_ruta(X, Y, V), V =< C),L),sort(L,D).
