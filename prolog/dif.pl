membro([X|_],X) :- !.
membro([_|Xs],X) :- membro(Xs,X),!.

rem([X|A],X,A).
rem([Y|A],X,[Y|C]) :- rem(A,X,C),!.

diff([],_,[]).
diff([X|A],B,C) :- membro(B,X),!,rem(B,X,B1),diff(A,B1,C).
diff([X|A],B,[X|C]) :- diff(A,B,C),!.
