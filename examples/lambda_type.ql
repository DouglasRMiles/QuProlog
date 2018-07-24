
% Type checker/evaluator for lambda terms.
%
% TypeAssign is an open list used to associate basic terms - 
% vars, obvars and atoms with their types.
%
% Note that the type of each bound variable is added to the front of
% the TypeAssign list to provide a local context for typing the body
% of each quantified term.

?- op(800, xfx, ~>).         %  for function types
?- op(500, quant, lambda).   % declare lambda as a quantifier
?- obvar_prefix(x).

type(A(B), Y, TypeAssign) :-
        !,
        type(A, X ~> Y, TypeAssign),
        type(B, X, TypeAssign).
type(lambda x A, T ~> TA, TypeAssign) :-
        !,
        type(A, TA, [x^T|TypeAssign]).
type(X, TX, TypeAssign) :-      % basic term
        in_type(X^TX, TypeAssign).

% in_type(X^Tx, TypeAssign) is true iff Tx is the type assigned to X
% in TypeAssign.

in_type(X^Tx, TypeAssign) :-    % not there - instantiate open list
        var(TypeAssign),
        !,
        TypeAssign = [X^Tx|_].
in_type(X^Tx, [Y^Ty|_]) :-      % found
        X == Y,
        !,
        Tx = Ty.
in_type(X^Tx, [_|TypeAssign]) :-
        in_type(X^Tx, TypeAssign).

