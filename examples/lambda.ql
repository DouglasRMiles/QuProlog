%
% A simple lambda term recogniser and evaluator
%

%
% Quantifier and operator declarations.
%
?- op(500, quant, lambda).   % declare lambda as a quantifier

?- op(800, xfx, =>).       % single reduction

?- op(800, xfx, =>*).      % zero or more reductions

?- obvar_prefix(x).

% a recogniser for lambda terms

lambda_term(x).              % object variables are lambda terms

lambda_term(A(B)) :-
	lambda_term(A),
	lambda_term(B).

lambda_term(lambda x A) :-
	lambda_term(A).

% lambda evaluation

A =>* C :-
	A => B,
	B =>* C, !.
A =>* A.

(lambda x A)(B) => [B/x]A.    		% beta rule

A(B) => C(B) :- A => C.       		% evaluation within a subterm

A(B) => A(C) :- B => C.       		% evaluation within a subterm

lambda x A => lambda x B :- A => B.     % evaluation within a subterm

lambda x A(x) => A :- x not_free_in A.  % eta rule (optional)

