rem3(_,[],[]).
rem3(X,[X|L],L1) :- rem3(X,L,L1).
rem3(X,[Y|L],[Y|L1]) :- not(X=Y),rem3(X,L,L1).
