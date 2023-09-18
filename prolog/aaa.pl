beta(X,[X|_]).
beta(X,[_|Z]) :- beta(X,Z).
alpha([],Y,Y).
alpha([H|X],Y,Z):-beta(H,Y),alpha(X,Y,Z).
alpha([H|X],Y,[H|Z]):-alpha(X,Y,Z).
