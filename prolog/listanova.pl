concat([],Y,Y).
concat([X|XR],Y,[X|Z]) :- concat(XR,Y,Z).

lista_nova([],L)  :- L = [].
lista_nova([X|XR],Y) :- lista_nova(X,X2),lista_nova(XR,XR2),concat(X2,XR2,Y).
lista_nova([X],L) :- L = [X].
