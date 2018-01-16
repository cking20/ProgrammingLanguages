/*
 * file: bs-v2.pl - 2nd attempt at "battleship" playing program
 */

:- dynamic board/2.
:- dynamic vessel_choices/2.
:- dynamic navy/2.

default_board(
[
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
]).

board(0,
[
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', 'd', 'd', '.', '.', '.'],
   ['.', '.', 'c', 'c', '.', '.', '.', '.', '.', '.'],
   ['.', '.', 'c', 'c', 'b', 'b', 'b', '.', '.', '.'],
   ['.', '.', '.', '.', 'b', 'b', 'b', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['a', 'a', 'a', 'a', '.', '.', '.', 's', 's', '.'],
   ['a', 'a', 'a', 'a', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
]).
board(1,
[
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', 'b', 'b', 'b', '.', '.'],
   ['.', 'a', 'a', 'a', 'a', 'b', 'b', 'b', '.', '.'],
   ['.', 'a', 'a', 'a', 'a', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', 'c', 'c', '.', '.', '.', '.'],
   ['.', '.', '.', '.', 'c', 'c', '.', '.', '.', '.'],
   ['.', 's', 's', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', 'd', 'd', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
]).
board(simple,
[
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', 'd', 'd', '.', '.', '.'],
   ['.', '.', 's', 's', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.']
]).

navy(0, [a, b, c, d, s]).
navy(1, [a, b, c, d, s]).

test(X, Y, Board) :-
   default_board(B1),
   ship(a, Ship),
   place_boat(B1, X, Y, Ship, Board).

test(Board) :-
   default_board(B1),
   ship(a, Ship),
   place_boat(B1, 1, 1, Ship, Board).

write_ship(C) :-
   C == 'a', write('carrier') ;
   C == 'b', write('battleship') ;
   C == 'c', write('cruiser') ;
   C == 'd', write('destroyer') ;
   C == 's', write('submarine') ;
   write('vessel of unknown type').

ship(a,
   [ ['a', 'a', 'a', 'a'],
     ['a', 'a', 'a', 'a'] ]).
ship(b,
   [ ['b', 'b', 'b'],
     ['b', 'b', 'b'] ]).
ship(c,
   [ ['c', 'c'],
     ['c', 'c'] ]).
ship(d,
   [ ['d', 'd'] ]).
ship(s,
   [ ['s', 's'] ]).

place_boat(Board, _X, _Y, [], Board).
place_boat(Board, X, Y, [BoatRow|BoatRows], NewBoard) :-
   % write('DEBUG: in place_boat'), nl,
   % display_a_board(Board), nl,
   place_boat_find_row(Board, X, Y, 1, BoatRow, Board2),
   % display_a_board(Board), nl,
   % display_a_board(Board2), nl,
   X2 is X+1,
   place_boat(Board2, X2, Y, BoatRows, NewBoard).

place_boat_find_row(Board, _, _, _, [], Board).
place_boat_find_row([Row|Rows], X, Y, X, BoatRow, [NewRow|Rows]) :-
   % write('DEBUG: in place_boat_find_row 2'), nl,
   place_boat_find_col(Row, Y, 1, BoatRow, NewRow).
place_boat_find_row([Row|Rows], X, Y, N, BoatRow, [Row|NewRows]) :-
   % write('DEBUG: in place_boat_find_row 3'), nl,
   N < X, M is N+1, place_boat_find_row(Rows, X, Y, M, BoatRow, NewRows). 

place_boat_find_col(Row, _, _, [], Row).
/*
place_boat_find_col([_Col|Cols], Y, Y, [Char|Chars], [Char|NewCols]) :-
   % write('DEBUG: in place_boat_find_col 2'), nl,
   place_boat_find_col(Cols, Y, Y, Chars, NewCols).
*/
place_boat_find_col(['.'|Cols], Y, Y, [Char|Chars], [Char|NewCols]) :-
   % write('DEBUG: in place_boat_find_col 2'), nl,
   place_boat_find_col(Cols, Y, Y, Chars, NewCols).

place_boat_find_col([Col|Cols], Y, N, BoatRow, [Col|NewCols]) :-
   N < Y, M is N+1, place_boat_find_col(Cols, Y, M, BoatRow, NewCols).

display_a_board(Board) :-
   do_display_board(Board).

default_vessel_choices([a, b, c, d, s]).

display_board(Who) :-
   board(Who,Board),
   do_display_board(Board).
do_display_board([]) :-
   nl, nl.
do_display_board([Row|Rows]) :-
   display_row(Row), nl,
   do_display_board(Rows).
display_row([]).
display_row([X|Xs]) :-
   write(' '), write(X), write(' '),
   display_row(Xs).

% returns character at location X,Y
located_at(Who,X,Y,C) :-
   board(Who,Board),
   located_in_row(X,Y,1,C,Board).

located_in_row(_,_,_,_,[]) :- fail.
located_in_row(X,Y,X,C,[Row|_]) :-
   located_in_col(Y,1,C,Row).
located_in_row(X,Y,M,C,[_|Rows]) :-
   N is M + 1,
   located_in_row(X,Y,N,C,Rows).

located_in_col(_,_,_,[]) :- fail.
located_in_col(Y,Y,C,[C|_]).
located_in_col(Y,M,C,[_|Cols]) :-
   N is M + 1,
   located_in_col(Y,N,C,Cols).

/*
 * place_at(+Player, +X, +Y, +Char)
 * 1 <= X <= 3
 * 1 <= Y <= 3
 */
place_at(Who,X,Y,Char) :-
   board(Who,Board),
   place_in_row(X,Y,1,Char,Board,NewBoard),
   retract(board(Who,Board)),
   assert(board(Who,NewBoard)).

place_in_row(_,_,_,_,[],_) :- fail.
place_in_row(X,Y,X,C,[Row|Rest],[NewRow|Rest]) :-
   place_in_col(Y,1,C,Row,NewRow).
place_in_row(X,Y,M,C,[Row|Rows],[Row|NewRows]) :-
   N is M + 1,
   place_in_row(X,Y,N,C,Rows,NewRows).

place_in_col(_,_,_,[],_) :- fail.
place_in_col(Y,Y,C,[D|Cols],NewCols) :-
    !, (
        D == '.', NewCols = [C|Cols];
        NewCols = [D|Cols]
       ).
place_in_col(Y,M,C,[Col|Cols],[Col|NewCols]) :-
   N is M + 1,
   place_in_col(Y,N,C,Cols,NewCols).

place_at_remove(Who,X,Y,Char) :-
   board(Who,Board),
   place_in_row_remove(X,Y,1,Char,Board,NewBoard),
   retract(board(Who,Board)),
   assert(board(Who,NewBoard)).

place_in_row_remove(_,_,_,_,[],_) :- fail.
place_in_row_remove(X,Y,X,C,[Row|Rest],[NewRow|Rest]) :-
   place_in_col_remove(Y,1,C,Row,NewRow).
place_in_row_remove(X,Y,M,C,[Row|Rows],[Row|NewRows]) :-
   N is M + 1,
   place_in_row_remove(X,Y,N,C,Rows,NewRows).

place_in_col_remove(_,_,_,[],_) :- fail.
place_in_col_remove(Y,Y,C,[_|Cols],NewCols) :-
    NewCols = [C|Cols].
place_in_col_remove(Y,M,C,[Col|Cols],[Col|NewCols]) :-
   N is M + 1,
   place_in_col_remove(Y,N,C,Cols,NewCols).

retrieve(Prompt, Vessels, Char, Orient, Term) :-
   repeat,
      (
      write('Choose from these ships '),
      write(Vessels), nl,
      write(Prompt),
      % read(Value),
      read_sentence(Sentence),
      % write_sentence(Sentence), nl,
      butlast(Sentence, Sentenc),
      % write(Sentenc), nl,
      phrase(init_sentence(What, Or, Loc), Sentenc, []),
         (
         What == 'quit', write('quitting ...'), abort
         ;
         member(What, Vessels),
         Char = What, Orient = Or, Term = Loc % [X, Y]
         )
      )
   .

retrieve(Prompt, Term) :-
   repeat,
      (
      write(Prompt),
      read_sentence(Sentence),
      % write_sentence(Sentence), nl,
      butlast(Sentence, Sentenc),
      % write(Sentenc), nl,
      phrase(fire_sentence(Loc), Sentenc, []),
         (
         Loc == 'quit', write('quitting ...'), abort
         ;
         Term = Loc % [X, Y]
         )
      )
   .

play :-
   default_board(Board),
   (retract(board(0, _)); true),
   (retract(board(1, _)); true),
   assert(board(0, Board)),
   assert(board(1, Board)),
   default_vessel_choices(Vessels),
   (retract(vessel_choices(0, _)); true),
   (retract(vessel_choices(1, _)); true),
   assert(vessel_choices(0, Vessels)),
   assert(vessel_choices(1, Vessels)),
   (retract(navy(0, _)); true),
   (retract(navy(1, _)); true),
   initialize(0),
   initialize(1),
   play(0).

play1 :-
   play(0).
play_simple :-
   (retract(board(0, _)); true),
   (retract(board(1, _)); true),
   (retract(navy(0, _)); true),
   (retract(navy(1, _)); true),
   board(simple, Board),
   assert(board(0, Board)),
   assert(board(1, Board)),
   assert(navy(0, [d,s])),
   assert(navy(1, [d,s])),
   play(0).

initialize(M) :-
   N is M + 1,
   format("Player # ~d's selections~n", [N]),
   write('Your board:'), nl,
   display_board(M),
   vessel_choices(M, Vs),
   (
      Vs == []
   ;
      write('player '), write(N), nl,
      repeat,
          (
          % write(' coordinates to put ship? '),
          % read(Value),
          % [A,B] = Value,
          retrieve('Ship and coordinates? ', Vs, Char, Orient, [A,B])
          % 1 =< A, A =< 3, 1 =< B, B =< 3
          ),
          (
          % place_at(M, A, B, Char),
          ship(Char, Ship_),
          (
              Orient == vert, transpos(Ship_, Ship)
              ;
              Ship = Ship_
          ),
          board(M, Board),
          place_boat(Board, A, B, Ship, NewBoard),
          % display_a_board(NewBoard),
          retract(board(M, _)), assert(board(M, NewBoard)),
          % subtract(Vs, [Char], Ws), this removes all occurrences
          ord_subtract(Vs, [Char], Ws),
          retract(vessel_choices(M, Vs)),
          assert(vessel_choices(M, Ws)),
          navy(M, Navy),
          (retract(navy(M, _)); true),
          append(Navy, [Char], Navy_post),
          assert(navy(M, Navy_post))
          ;
          true
          ),
      % write('DEBUG:: board is'), nl,
      % display_board(M),
      initialize(M)
   )
   .

play(M) :-
   N is M + 1,
   Opp is (M + 1) mod 2,
   write('DEBUG: opponent''s board: '), nl,
   display_board(Opp),
   format("Player ~d's move~n", [N]),
   % read(Value),
   % [A,B] = Value,
   retrieve('Coordinates? ', [A,B]),
   format("DEBUG: attacking at coordinates [~d,~d]~n", [A, B]),
   attack(Opp,A,B),
   check_loss(Opp),
   play(Opp).

play(M) :-
   write('player '), N is M + 1, write(N), write(' loses'), nl.

remove(Who, Vessel, X, Y) :-
   located_at(Who, X, Y, Vessel),
   Vessel \== '.',
   place_at_remove(Who,X,Y,'.').
hit_remove(Who, Vessel, X, Y) :-
   located_at(Who, X, Y, Vessel),
   Vessel \== '.',
   place_at_remove(Who,X,Y,'x'),
   (check_sunk(Who, X, Y, Vessel); true).

/*
   check_sunk(+Who, +X, +Y) - record if hit here completes a sinking;
   means checking all adjacent cells for matching character.
   [NW ,  N , NE ]
   [ W ,  T ,  E ]
   [SW ,  S , SE ]
*/
check_sunk(Who, X, Y, Char) :-
   NWX is X-1, NWY is Y-1,
   NEX is X-1, NEY is Y+1,
   WX  is X,   WY  is Y-1,
   EX  is X,   EY  is Y+1,
   SWX is X+1, SWY is Y-1,
   SEX is X+1, SEY is Y+1,
   NX is X-1, NY is Y,
   SX is X+1, SY is Y,
   
   located_at(Who, NWX, NWY, CNW),
   located_at(Who, NEX, NEY, CNE),
   located_at(Who, WX, WY, CW),
   located_at(Who, EX, EY, CE),
   located_at(Who, SWX, SWY, CSW),
   located_at(Who, SEX, SEY, CSE),
   located_at(Who, NX, NY, CN),
   located_at(Who, SX, SY, CS),
   CNW \== Char, CNE \== Char, CW \== Char, CE \== Char,
   CSW \== Char, CSE \== Char, CN \== Char, CS \== Char,
   navy(Who, Navy),
   ord_subtract(Navy, [Char], Navy_post),
   retract(navy(Who, _)),
   assert(navy(Who, Navy_post)),
   write('sunk '), write_ship(Char), nl.

check_loss(Who) :-
   navy(Who, Navy),
   Navy == [],
   WhoN is Who + 1,
   write(WhoN), write(' has lost the greatest sea battle in history.'),
   nl, abort
   ;
   true.

% attack(_, _, _).
attack(Who, X, Y) :-
   located_at(Who, X, Y, C),
   (
       C \== '.',
       C \== 'x',
       hit_remove(Who, Vessel, X, Y),
       write('hit on ship of type '), write(Vessel), nl ;
       write('miss'), nl
   ).

transpos([], []).
transpos(X, Y) :-
   transpos(X, [], Y).

transpos([[] | _Rest], X, X).
transpos(Rows, SoFar, Trans) :-
   firsts(Rows, FirstsOfRows),
   append(SoFar, [FirstsOfRows], SoFar2),
   tails(Rows, TailsOfRows),
   transpos(TailsOfRows, SoFar2, Trans).

firsts([], []).
firsts([[X|_Xs]| Rows], [X|RestFirsts]) :-
   firsts(Rows, RestFirsts).
tails([], []).
tails([[_X|Xs]| Rows], [Xs|Tails]) :-
   tails(Rows, Tails).

