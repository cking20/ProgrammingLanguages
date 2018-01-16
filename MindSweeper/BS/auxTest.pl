% File:  aux.pl
%      - just some auxiliary predicates

:- consult('io').

butlast([_],[]).
butlast([X|Xs],[X|Ys]) :-
  butlast(Xs,Ys).

doit(F) :-
   seeing(Keyboard),
   see(F),
   proc,
   see(Keyboard).

