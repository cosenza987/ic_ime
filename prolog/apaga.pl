apaga(L,N,L1) :- apaga(L,N,1,L1).
apaga([],_,_,[]).
apaga([_|L],N,I,R) :- I=N,apaga(L,N,1,R),!.
apaga([X|L],N,I,[X|R]) :- I1 is I+1, apaga(L,N,I1,R).
