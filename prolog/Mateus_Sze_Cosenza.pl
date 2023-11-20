membro(X,[X|_]).
membro(X,[_|R]) :- membro(X,R).
concat([],Y,Y).
concat([X|Xs],Ys,[X|Zs]) :- concat(Xs,Ys,Zs).
duprem([],[]).
duprem([X|A],B) :- membro(X,A),!,duprem(A,B).
duprem([X|A],[X|B]) :- duprem(A,B).
p2(L1,L2,L3) :- concat(L1,L2,L4), duprem(L4,L3).









