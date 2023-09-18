p(A, B, X, Y1) :- s(B, A, X), d(B, A, Y, A), Y1 is Y-X.
s([A|As], [A|Bs], X) :- s(As, Bs, X1), X is X1+1, !.
s([_|As], [_|Bs], X) :- s(As, Bs, X).
s([], _, 0).
d([A|As], [A|_], Y, B) :- d(As, B, Y1, B), Y is Y1+1, !.
d(A, [_|Bs], Y, B) :- d(A, Bs, Y, B).
d([_|As], [], Y, B) :- d(As, B, Y, B).
d([], _, 0, _).
