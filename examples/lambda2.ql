%
% An eager evaluator for lambda terms
%

?- op(500, quant, lambda).   % declare lambda as a quantifier

?- op(800, xfx, =>).       % single reduction

?- op(800, xfx, =>*).      % zero or more reductions

?- obvar_prefix(x).


% lambda evaluation

A =>* Result :-
	reduce(A, B, IsReduced),
	(   IsReduced == true
	    ->
		simplify_term(B, Result)
	    ;
		Result = B
	).


reduce(A(B), Result, IsReduced) :- 
	reduce(A, C, IsReduced),
	reduce(B, D, BIsReduced),
	IsReduced = BIsReduced,
	reduce_application(C, D, Result, IsReduced),
	!.
reduce(lambda x A, Result, IsReduced) :-
	reduce(A, B, IsReduced),
	IsReduced == true,
	!,
	Result = lambda x B.
reduce(X, X, _).
	

reduce_application(lambda x F, A, Result, true) :-
	!,
	(   quant(A)
	    ->
		reduce([A/x]F, Result, _)  % A is a lambda abstraction
	    ;
		Result = [A/x]F
	).
reduce_application(F, A, Result, IsReduced) :-
	IsReduced == true,
	Result = F(A).
		
	

