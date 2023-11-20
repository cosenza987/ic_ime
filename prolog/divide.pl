membro(X,[X|_]) :- !.
membro(X,[_|L]) :- membro(X,L),!.
divide(_,[],[],[]).
divide(X,[X1|L],L1,L2) :- X1=X, divide(X,L,L1,L2), membro(X1,L1),!.
divide(X,[X1|L],L1,L2) :- X1<X, divide(X,L,L1,L2), membro(X1,L1),!.
divide(X,[X1|L],L1,L2) :- X1>X, divide(X,L,L1,L2), membro(X1,L2),!.
divide(X,[X1|L],[X1|L1],L2) :- X1=X, divide(X,L,L1,L2),!.
divide(X,[X1|L],[X1|L1],L2) :- X1<X, divide(X,L,L1,L2),!.
divide(X,[X1|L],L1,[X1|L2]) :- X1>X, divide(X,L,L1,L2),!.

