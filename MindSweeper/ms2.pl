/*
 * file: ms2.pl
 */
:- consult('auxTest.pl').

:- dynamic board/2.
:- op(900, yfx, <-).

/*Grammar 

init_sentance([X,Y]) -->
	verb, det, where(X, Y).
init_sentance(quit, [null, null]) --> [quit].

verb --> [reveal];[look];[check];[].
det --> [at];[].

where(X, Y) -->
	[X], [Y], {number(X), number(Y)}.

End of Grammar*/

Suf <- N :-
   (N == 1 -> Suf = 'st'; N == 2 -> Suf = 'nd';
    N == 3 -> Suf = 'rd'; Suf = 'th').

% checked(' ').
% unchecked('.').
mark('_').

checked(X, Y) :-
   located_at(visible,X,Y,B), (mark(B); number(B)).

unchecked(X, Y) :-
   \+ checked(X,Y).

bomb('b').
filter(_, [], []).
filter(P, [A |As], Cs) :-
    (
       call(P, A) -> B = [A]
    ;
       B = []
    )
    , filter(P, As, Bs), append(B, Bs, Cs).

maxX(10).
maxY(10).
legit([A,B]) :-
   maxX(MaxX), maxY(MaxY),
   1 =< A, A =< MaxX, 1 =< B, B =< MaxY.

board(visible,
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

board(hidden,
[
   ['.', 'b', 'b', '.', 'b', 'b', 'b', '.', '.', '.'],
   ['.', '.', 'b', '.', 'b', '.', 'b', '.', '.', '.'],
   ['.', '.', 'b', '.', 'b', '.', 'b', '.', '.', '.'],
   ['.', '.', 'b', '.', 'b', 'b', 'b', '.', '.', '.'],
   ['b', 'b', 'b', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', '.', '.', 'b', '.', '.', '.', 'b', '.'],
   ['.', '.', '.', '.', '.', '.', '.', '.', '.', '.'],
   ['b', 'b', 'b', '.', '.', 'b', '.', '.', '.', '.'],
   ['.', '.', 'b', '.', '.', '.', '.', '.', '.', '.'],
   ['.', '.', 'b', '.', '.', '.', '.', '.', '.', '.']
]).

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
located_at(Which, X, Y, C) :- 
   board(Which,Board),
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
 * place_at(+Which, +X, +Y, +Char)
 * Who is visible or hidden
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

retrieve(Prompt, Term) :-
   repeat,
      (
      write(Prompt),
      read_sentence(Sentence),
      write_sentence(Sentence), nl,
      butlast(Sentence, Sentenc),
      write(Sentenc), nl,
	  %Term = Sentenc, 
      phrase(sentence(Loc), Sentenc, []),
         (
         Loc == 'quit', write('quitting ...'), abort
         ;
         Term = Loc % note: in form [X, Y]
         )
      )
   .

play :-
   play(0).

play(M) :-
   N is M + 1,
   Suf <- N,
   display_board(visible), nl,
   format("Your ~d~a move~n", [N,Suf]),
   retrieve('Coordinates? ', [A,B]),
   format("DEBUG: probing at coordinates [~d,~d]~n", [A, B]),
   /*!, probe(A,B),*/
   probe(A,B),
   display_board(visible), nl,
   play(N).

/*
 * Be able to do this on exam 2
 */
count(_, [], 0).
count(X, [X|Ys], Z) :- count(X, Ys, W), Z is 1+W.
count(X, [_|Ys], W) :- count(X, Ys, W).

neighbors(X, Y, Nbrs) :-
   NWX is X-1, NWY is Y-1,
   NEX is X-1, NEY is Y+1,
   WX  is X,   WY  is Y-1,
   EX  is X,   EY  is Y+1,
   SWX is X+1, SWY is Y-1,
   SEX is X+1, SEY is Y+1,
   NX is X-1, NY is Y,
   SX is X+1, SY is Y,

   Nbrs_unfiltered =
   [[NWX, NWY],
    [NEX, NEY],
    [WX,  WY],
    [EX,  EY],
    [SWX, SWY],
    [SEX, SEY],
    [NX,  NY],
    [SX,  SY]],
   filter(legit, Nbrs_unfiltered, Nbrs).

has_bomb(X,Y) :- 
	located_at(hidden,X,Y,C),
	C == 'b'.
	
has_none(X,Y) :-
	located_at(hidden,X,Y,C),
	C == '.'.

get_head(H,[H|_]).
get_tail(T,[_|T]).	
bomb_count([],0).	
bomb_count([P|Points], Count) :- 
   
   get_head(X,P),
   get_tail(Y,P),
   (has_bomb(X,Y) -> 
		write('counting up\n'),
		bomb_count(Points, Count + 1)
		
	;	write('not counting\n'),
		bomb_count(Points, Count)	
	
	;	true
	).
	
/*   has_bomb(X,P), Count_Up is Count + 1 ,bomb_count([Points], Count_Up);
   bomb_count([Xs,Ys] Count).*/
print( [ ] ).
print( [ X | Y ] ):- nl, write(X), print( Y ).
   
bomb_count_neighbors([X, Y], Count) :-
	neighbors(X,Y,Nbrs),
	write('got the neighbors\n'),
	print(Nbrs),
	bomb_count(Nbrs,Count).
	/*count(X,Nbrs,Count).*/





bomb_count_neighbors2([X, Y], Count) :-
   neighbors(X, Y, Nbrs),
   count2('b', Nbrs, Count).
   /*getUnexposed_neghbors('.',Nbrs,UnCheckeds).*/
   
   
count2(_Char, [], 0).
count2(Char, [[X,Y]|Tail], Count) :-
   located_at(hidden, X, Y, Char),
   count2(Char, Tail, CountRest),
   Count is 1 + CountRest, !.
count2(Char, [_Stuff|Tail], Count) :-
		count2(Char, Tail, Count), !.
/*
getUnexposed_neghbors(_Char, [], []).
getUnexposed_neghbors(Char, [[X,Y]|Tail], UnCheckeds) :-
   located_at(hidden, X, Y, Char),
   located_at(visible, X, Y, Char),
   getUnexposed_neghbors(Char, Tail, NewUnCh),
   append([X,Y],UnCheckeds, NewUnCh), !.
getUnexposed_neghbors(Char, [_Head|Tail], UnCheckeds) :-
		getUnexposed_neghbors(Char, Tail, UnCheckeds), !.

expose_nbhrs([]).
expose_nbhrs([X,Y]|UnCheckeds):-
	bomb_count_neighbors2([X,Y],Count, UnCheckeds),
	Count == 0,
	probe(X,Y),
	expose_nbhrs(UnCheckeds).
expose_nbhrs(_DontCare|UnCheckeds):-
	expose_nbhrs(UnCheckeds).
*/
	
	
expose([X, Y],Char) :- 
	place_at(visible,X,Y,Char).
   
explode(X,Y) :- 
	has_bomb(X,Y),
	write('boom'),/*Doesnt print for some reason. Aborts first*/
	
	abort.

probe(X, Y) :-
	not(explode(X,Y)),
	write('didnt explode\n'),
	bomb_count_neighbors2([X,Y],Count),
	expose([X,Y],Count),
	write('\n').
	/*expose_nbhrs(UnCheckeds).*/
	
