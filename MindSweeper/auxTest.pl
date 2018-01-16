
:- consult('io2').
:- consult('grammar').

butlast([_],[]).
butlast([X|Xs],[X|Ys]) :-
  butlast(Xs,Ys).

doit(F) :-
   seeing(Keyboard),
   see(F),
   proc,
   see(Keyboard).

