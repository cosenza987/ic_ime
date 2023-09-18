membro(X, [X|_]).
membro(X, [_|Ls]) :- membro(X, Ls).

rem(_, [], []).
rem(X, [X|Z], Z).
rem(X, [Y|Ys], [Y|Zs]) :- rem(X, Ys, Zs).

inter([], _, []).
inter([X|Xs],Y,[X|Zs]) :- membro(X, Y),rem(X,Y,Y1),!,inter(Xs, Y1, Zs).
inter([_|X],Y,Z) :- inter(X,Y,Z).
