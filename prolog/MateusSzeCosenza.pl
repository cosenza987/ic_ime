reverter(X,L) :- reverter(X,[],L).
reverter([],X,X).
reverter([X|L],Y,Z) :- reverter(L,[X|Y],Z).
