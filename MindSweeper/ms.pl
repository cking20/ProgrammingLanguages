:- dynamic num_bombs/1.
num_bombs(0).

def_board(
[
	['.','.','.','.','.','.','.','.','.','.'],
	['.','.','.','.','.','.','.','.','.','.'],
	['.','.','.','.','.','.','.','.','.','.'],
	['.','.','.','.','.','.','.','.','.','.'],
	['.','.','.','.','.','.','.','.','.','.']
]).

board(0,
[
	['b','.','.','.','.','.','b','.','.','.'],
	['.','b','.','.','b','.','.','.','b','.'],
	['.','b','b','.','.','.','.','.','.','.'],
	['.','.','.','.','.','.','b','.','b','.'],
	['b','.','.','b','.','b','.','.','.','b']
]).

board(1,
[
	['b','b','b','b','.','b','.','.','.','b'],
	['.','b','.','.','.','b','b','b','b','.'],
	['.','.','.','b','b','.','.','.','.','b'],
	['.','b','.','.','.','b','.','b','.','.'],
	['b','.','.','b','.','.','.','b','.','b']
]).

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
char('b').   
check_bombs(Who, X, Y) :-
   char(Char),
   retract(num_bombs()),
   assertz(num_bombs(0)),
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
   located_at(Who, SX, SY, CS).
   
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
   filter(legit, Nbrs_unfiltered, Nbrs),
   print(Nbrs).
   
filter(_, [], []).
filter(P, [A |As], Cs) :-
    (
       call(P, A) -> B = [A]
    ;
       B = []
    )
    , filter(P, As, Bs), append(B, Bs, Cs).

inc :-
   retract(num_bombs(C)),
   succ(C,C1),
   assertz(num_bombs(C1)).


