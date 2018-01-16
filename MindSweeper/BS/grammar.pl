% File:  grammar.pl
%   - grammar for Battleship game

:- consult('aux').
:- consult('bs.pl').

init_sentence(What, Orient, [X, Y]) -->
  verb, det, orientation(Orient), ship(What), prep, where(X, Y).

init_sentence(quit, horiz, [null, null]) --> [quit].

verb --> [place] ; [put] ; [].
det --> [a] ; [an] ; [].
orientation(horiz) --> ([horizontal] ; []).
orientation(vert) --> [vertical].
prep --> [at] ; [].

ship(What) --> ( [a] ; [aircraft], [carrier] ; [carrier] ),
               { What = 'a' }.
ship(What) --> ( [b] ; [battleship] ),
               { What = 'b' }.
ship(What) --> ( [c] ; [cruiser] ),
               { What = 'c' }.
ship(What) --> ( [d] ; [destroyer] ; [tin], [can] ),
               { What = 'd' }.

ship(What) --> ( [s] ; [submarine] ; [tin], [can] ),
               { What = 's' }.

where(X, Y) -->
    [X], [Y], { number(X), number(Y) }.

fire_sentence([X, Y]) -->
    ([fire] ; [launch]), ([at] ; []), where(X, Y).
fire_sentence(quit) --> [quit].

