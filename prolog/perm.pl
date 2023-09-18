remv(X,[X|R],R).
remv(X,[F|R],[F|S]) :- remv(X,R,S).

perm([X|Y],Z) :- perm(Y,W), remv(X,Z,W).
perm([],[]).
