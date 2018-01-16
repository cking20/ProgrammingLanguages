
sentence(quit) --> [quit].
sentence([X, Y]) --> [probe];[check];[look];[], [X], [Y], {number(X), number(Y)}.
/*this for some reason doesnt work*/
init_sentance([X,Y]) -->
	verb, det, where(X, Y).
init_sentance(quit, [null, null]) --> [quit].

verb --> [reveal];[look];[check];[].
det --> [at];[].

where(X, Y) -->
	[X], [Y], {number(X), number(Y)}.
