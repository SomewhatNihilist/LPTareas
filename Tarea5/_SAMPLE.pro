% 1
c(a, b, 5).
c(a, c, 4).
c(b, a, 6).
c(c, d, 3).
c(e, f, 5).
c(d, g, 6).
c(c, e, 3).
c(b, e, 4).
c(g, f, 6).

% 2
camino(X,Y,P):-camino(X,Y,P,[X]).
camino(X,Y,P,_):-c(X,Y,P).
camino(X,Y,P, Temp):-c(X,B,P1),not(member(B,Temp)),
    append(Temp,[B],Temp1),camino(B,Y,P2,Temp1), P is P1 + P2.


%--- Modelo visto en ayudantía:
todos_caminos(X, Y, List) :- todos_caminos(X, Y, [], List), !.
todos_caminos(X, Y, Temp, List) :- camino(X, Y, V), \+member(V, Temp), append(Temp, [V], Tempnew) ,todos_caminos(X, Y, Tempnew, List).
todos_caminos(_,_,Temp, Temp).

%--- Modelo Alternativo:
%enLista(X, [], [X]) :- !.
%enLista(C, [C|_], _) :- !, fail.
% enLista(X, [C|Resto], L) :- enLista(X, Resto, Resul), append(Resul,
% [C], L).
% todos_caminos(X, Y, Temp, List) :- camino(X, Y, V), enLista(V, Temp,
% Tempnew),todos_caminos(X, Y, Tempnew, List).

%--- Modelo que sale con una linea:
%todos_caminos(X, Y, L) :- findall(V,camino(X, Y, V),L).

% 3
menor(V1, V2, V1) :- V1 < V2, !.
menor(_, V2, V2).

minlist([X], X).
minlist([X|Resto], M) :- minlist(Resto, MinResto), menor(X, MinResto, M).

mas_corto(X, Y, V) :- todos_caminos(X, Y, L), minlist(L, V), !.
