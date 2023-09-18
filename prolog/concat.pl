concat([],Y,Y).
concat([X|Xs],Ys,[X|Zs]) :- concat(Xs,Ys,Zs).
