inverser(Xs,Ys) :- inverser(Xs,[],Ys).
inverser([],Ys,Ys).
inverser([X|Xs],Ts,Ys) :- inverser(Xs,[X|Ts],Ys).

palindrome(L) :- inverser(L, LR), L = LR.
