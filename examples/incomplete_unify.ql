
%% set_retry_depth(Depth).
%%
%%  Sets maximum depth for heuristic unification.
%%
%%  set_retry_depth(@integer).
%%
set_retry_depth(N) :-
    N > 0,
    retractall(incomplete_retry_depth(_)),
    asserta(incomplete_retry_depth(N)).


?- assert(incomplete_retry_depth(10)).


%% get_retry_depth(Depth).
%%
%%  Gets the current maximum depth for heuristic unification.
%%
%%  get_retry_depth(?integer).
%%
get_retry_depth(N) :-
    incomplete_retry_depth(N).

%% incomplete_retry_delays(Depth, Result).
%%
%%  Attempts to solve all the delayed unification problems.
%%  fails if it can't find any solution.
%%
%%  Depth is the supplied depth limit for search and Result is
%%  used to determine if the depth limit was exceeded. 
%%  The depth limit was exceeded if Result is the atom exceeded.
%%  Otherwise Result is a variable.
%%  Incomplete_retry_delays makes extensive use of incomplete_unify.
%%

%% Use default depth
incomplete_retry_delays :-
    get_retry_depth(Depth),
    incomplete_retry_delays(Depth, Result),
    (var(Result) ->
        true
    ;
        error('WARNING: Heuristic unification hit depth bound: '),
        errornl(Depth),
        errornl('You can use set_retry_depth(N) to change the bound.'),
        fail
    ).

%% Use supplied depth
incomplete_retry_delays(Depth) :-
    integer(Depth),!,
    incomplete_retry_delays(Depth, Result),
    (var(Result) ->
        true
    ;
        error('WARNING: Heuristic unification hit depth bound: '),
        errornl(Depth),
        errornl('You can use set_retry_depth(N) to change the bound.'),
        fail
    ).

%% Return result, use default depth
incomplete_retry_delays(Result) :-
    get_retry_depth(Depth),
    incomplete_retry_delays(Depth, Result1),
    Result = Result1.

%% Return result, use supplied depth
incomplete_retry_delays(Depth, Result) :-
    integer(Depth),
    retry_delays,
    get_unify_delays(Delays),
    (Delays = [] ->
        true
    ;
        ip_set(incomplete_retry_delay_depth, Depth),
        catch(incomplete_retry(Delays), 
              incomplete_retry_limit(Result), true)
    ).


incomplete_retry(Delays) :-
    ip_lookup(incomplete_retry_delay_depth, N),
    (N = 0 ->
        throw(incomplete_retry_limit(exceeded))
    ;
        (get_best_delay(Delays, T1, T2) ->
            incomplete_unify(T1, T2),
            retry_delays,
            get_unify_delays(Delays1),
            N1 is N - 1,
            ip_set(incomplete_retry_delay_depth, N1),
            incomplete_retry(Delays1)
        ;
            true
        )
    ).


%%  The aim of incomplete_unify is to solve a delayed
%%  unification problem by searching through possible
%%  ways of producing unifiers for this delayed problem.
%% 
%% 
%%  The possible delayed unification problems fall into
%%  the following groups (up to symmetry).
%%  (In this list A,B,... are meta-variables x,y, ...
%%   are object-variables and s, s1, s2, ...  are substitutions)
%% 
%%  (a) s*A = structured_term  (including constant)
%%          (s /= [])
%% 
%%  (b) s*x = structured_term  (including constant)
%%          (s /= [])
%% 
%%  (c) s1*A = s2*B    (not (s1 = [] & s2 = [])
%%
%%  (d) s1*x = s2*y    (not (s1 = [] & s2 = [])
%%
%%  (e) s1*x = s2*A    (not (s1 = [] & s2 = [])
%%
%%  
%%  The method used to find unifiers is to take a delayed
%%  problem, make a simplifying choice (as given below)
%%  and then rely on retry_delay (and hence unify) to do
%%  the real work of finishing off the problem.
%%  In some cases, a simplifying choice will not cause the
%%  current problem to be solved. In this case backtracking
%%  occurs and a different choice is made.
%% 
%%  Simplifying choices for delayed problems
%%  ----------------------------------------
%% 
%%  These follow the problem types above. NOTE that reordering
%%  these choices will cause different solutions to appear
%%  in different orders.
%% 
%%  In most of these cases failure might occur, the problem could
%%  be completly solved, or new (simpler) unification problems
%%  may be produced.
%% 
%%  (a) 1. A = t  where t is a 'skeletal' form of the structured term
%%        (e.g. if the structured term is f(t1, t2) then
%%         t is F(A1, A2) for new meta-variables)
%%      2. A = x  where x is a new object variable.
%% 
%%  (b) Let s = [t1/x1,....,tn/xn]
%% 
%%      x not_free_in xj (j = i+1,...,n) AND x = xi (leave out x = xi if i=0)
%%     (i = 1..n in turn)
%% 
%%  (c) Let s1 = [t1/x1,....,tn/xn], s2 = [u1/y1,....,uk/yk]
%% 
%%    1. If A /== B and A is not frozen bind A to [x1/z1,...,xn/zn]*s2*B, 
%%       where zi are new object vars. (Occurrences of A in s2 should be
%%       removed first.)
%% 
%%      2. if A /== B and B is not frozen do the flip of 1.
%% 
%%      3. if A == B  force s1 and s2 to have the same effect on A.
%% 
%%      4. A = x (new x) and B = y (new y).
%%      
%%  (d) Let s1 = [t1/x1,....,tn/xn], s2 = [u1/y1,....,uk/yk]
%% 
%%      1. x not_free_in xj (j = i+1,...,n) AND x = xi (leave out x=xi if i=0)
%%     (i = 1..n in turn)
%%    
%%      2. y not_free_in yj (j = i+1,...,k) AND y = yi (leave out y=yi if i=0)
%%     (i = 1..k in turn)
%% 
%%      3. y = x   +   force s1 and s2 to have the same effect on x.
%% 
%%  (e) Let s1 = [t1/x1,....,tn/xn], s2 = [u1/y1,....,uk/yk]
%% 
%%    1. If A is not frozen bind A to [y1/z1,...,yk/zk]*s1*x, 
%%       where zi are new object vars. (Occurrences of A in s1 should be
%%       removed first.)
%% 
%%      2. x not_free_in xj (j = i+1,...,n) AND x = xi (leave out x=xi if i=0)
%%     (i = 1..n in turn)
%% 
%%      3. A = z (for some new object variable)
%%     THEN do d(1,3)  - i.e. in d1 z is the variable used where x appears.
%%     NOTE that d2 is covered in case e.
%%    
%% 
incomplete_unify(T1, T2) :-
    simplify_term(T1, ST1),    % sequence of subs -> single sub
    simplify_term(T2, ST2),
    iu(ST1, ST2).

iu(T1, T2) :-
    var(T1),
    structure(T2),
    !,
    iu_case_a(T1, T2).
iu(T1, T2) :-
    var(T2),
    structure(T1),
    !,
    iu_case_a(T2, T1).
iu(T1, T2) :-
    obvar(T1),
    structure(T2),
    !,
    iu_case_b(T1, T2).
iu(T1, T2) :-
    obvar(T2),
    structure(T1),
    !,
    iu_case_b(T2, T1).
iu(T1, T2) :-
    var(T1),
    var(T2),
    !,
    iu_case_c(T1, T2).
iu(T1, T2) :-
    obvar(T1),
    obvar(T2),
    !,
    iu_case_d(T1, T2).
iu(T1, T2) :-
    obvar(T1),
    var(T2),
    !,
    iu_case_e(T1, T2).
iu(T1, T2) :-
    obvar(T2),
    var(T1),
    !,
    iu_case_e(T2, T1).

%%%%%%%%%%  Case a  %%%%%%%%%%

iu_case_a(X, T) :-
    break_term(X, _, BX),
    (var_occurs_in(BX, T) ->
        (
            BX = !_x            % case a2
        ;
            % This skeleton branch will generate an infinite number of
            % solutions.
            skeleton(T, BX)        % case a1
        )
    ;
        (
            skeleton(T, BX)        % case a1
        ;
            BX = !_x            % case a2
        )
    ).


%%%%%%%%%%  Case b  %%%%%%%%%%

iu_case_b(X, _) :-
    break_term(X, SX, BX),
    force_deref(SX, BX).

%%%%%%%%%%  Case c  %%%%%%%%%%

iu_case_c(X, Y) :-
    break_term(X, SX, BX),
    break_term(Y, SY, BY),
    (
        BX \== BY,
        thawed_var(BX),            % case c1
        (frozen_var(BY) ; SY \== []),
        (var_occurs_in(BX, Y) ->
            fix_occurs_check(BX, SY, BY),
            retry_delays
        ;
            true
        ),
        gen_new_sub(SX, GenSub),
        build_term(Term, GenSub, Y),
        BX = Term
    ;
        BX \== BY,
        thawed_var(BY),        % case c2
        (frozen_var(BX) ; SX \== []),
        (var_occurs_in(BY, X) ->
            fix_occurs_check(BY, SX, BX),
            retry_delays
        ;
            true
        ),
        gen_new_sub(SY, GenSub),
        build_term(Term, GenSub, X),
        BY = Term
    ;
        BX == BY,                % case c3
        force_identical(BX, SX, SY)
    ;
        BX \== BY,
        BX = !_x1,                % case c4
        force_deref(SX, BX)
    ;
        BX \== BY,
        BY = !_x2,
        force_deref(SY, BY)
    ).

%%%%%%%%%%  Case d  %%%%%%%%%%

iu_case_d(X, Y) :-
    break_term(X, SX, BX),
    break_term(Y, SY, BY),
    (
        BX == BY,
        force_identical(BX, SX, SY)
    ;
        BX \== BY,
        (
            force_deref(SX, BX)        % case d1
        ;
            force_deref(SY, BY),        % case d2
            retry_delays,
            (X == Y ->
                true
            ;
                reduce_range(Y, X, SX, BX) % avoid repeated cases
            )
        ;
            BX = BY                % case d3
        )
    ).


%%%%%%%%%%  Case e  %%%%%%%%%%

iu_case_e(X, Y) :-
    break_term(X, SX, BX),
    break_term(Y, SY, BY),
    (
        thawed_var(BY),
        (var_occurs_in(BY, X) ->       % case e1
            fix_occurs_check(BY, SX, BX),
            retry_delays
        ;
            true
        ),
        gen_new_sub(SY, GenSub),
        build_term(Term, GenSub, X),
        BY = Term
    ;
        force_deref(SX, BX)            % case e2
    ;
        BY = !_x,                   % case e3
        (
            force_deref(SY, BY)
        ;
            BX = BY,
            force_identical(BX, SX, SY)
        )
    ).


%% fix_occurs_check(Var, Sub, Term)
%%
%% Remove entries from Sub that has an occurence of Var.
%% This is done by applying not_free_in constraints.
%%
fix_occurs_check(_,[],_).
fix_occurs_check(Var, [(R/D)|Sub], V) :-
    \+ \+ var_occurs_in(Var, R),
    !,
    D not_free_in V,
    fix_occurs_check(Var, Sub, V).
fix_occurs_check(Var, [(_/_)|Sub], V) :-
    fix_occurs_check(Var, Sub, V).


var_occurs_in(V, Term) :-
    collect_vars(Term, VarList),
    member_eq(V, VarList).


%% private reduce_range(...).
%%
%%  reduce_range is used to partially reduce the subs in a range
%%  entry to avoid repeating cases
%%
%%  mode reduce_range(?,?,?).
%%
reduce_range(R, _ ,_ , _) :-
    structure(R),   % case handled in case b
    !,
    fail.
reduce_range(Y, X, SX, BX) :-
    var(Y),    % avoid e2 case
    !,
    break_term(Y, SY, BY),
    (
        thawed_var(BY),
        (var_occurs_in(BY, X) ->        % case e1
            fix_occurs_check(BY, SX, BX),
            retry_delays
        ;
            true
        ),
        gen_new_sub(SY, GenSub),
        build_term(Term, GenSub, X),
        BY = Term
     ;
         SY = !_x,                      % case e3
         (
             force_deref(SY, BY)
         ;
              BX = BY,
              force_identical(BX, SX, SY)
         )
    ).
reduce_range(Y, _X, SX, BX) :-
    obvar(Y),                % avoid d1 case
    !,
    break_term(Y, SY, BY),
    (
        force_deref(SY, BY)               % case d2
    ;
         BX = BY,                       % case d3
         force_identical(BX, SX, SY)
    ).


%% private break_term(Term, Sub, Body).
%%
%%  Break up a sub*term into its components flattening out the sub.
%%
%%  mode break_term(?,?,!).
%%
break_term(T, ST, BT) :-
    substitute(T, S1, BT),
    flatten_sub(S1, ST).

flatten_sub([], []) :- !.
flatten_sub([X], X).


%% private build_term(Term, Sub, Body).
%%
%%  Build Term from Sub and Body.
%%
%%  mode build_term(!,?,?).
%%
build_term(T, ST, BT) :-
    flatten_sub(S1, ST),
    substitute(T, S1, BT).


%% skeleton(T, Skeleton).
%%
%% Build a skeleton of a structured term T.

skeleton(T, SkelT) :-
    atomic(T),
    !,
    SkelT = T.
skeleton(T, SkelT) :-
    compound(T),
    !,
    functor(T, _, N),
    functor(SkelT, _, N).
skeleton(T, !!_ _ _) :-
    quant(T).

structure(T) :-
    nonvar(T),
    \+ obvar(T).


%% force_deref(...).
%%
%%  Try all possible ways in which an object var might deref through
%%  a sub - return the dereferenced term
%%
%%
force_deref([], _) :-
    !,
    fail.
force_deref(Sub, X) :-
    reverse(Sub, RSub),
    force_deref_rev(RSub, X).

force_deref_rev([], X).
force_deref_rev([(R/X)|_], X).
force_deref_rev([(_/D)|T], X) :-
    X not_free_in D,
    force_deref_rev(T, X).


%% get_best_delay(Delays, LHS, RHS).
%%
%%  Delays that involve structures typically have the least
%%  number of possible unifiers therefore they should be
%%  unified first.
%%  So get_best_delay selects a problem LHS=RHS from Delays,
%%  giving preference to problems that involve structures.
%%
%%  mode get_best_delay(@list(compound), -term, -term).
%%
get_best_delay(P, T1, T2) :-
    get_best_delay1(P, T1, T2),
    !.
get_best_delay([(T1=T2)|_], T1, T2).

get_best_delay1([(T1 = T2)|_], T1, T2) :-
    (
        structure(T1), 
        not_occurs_problem(T2, T1) 
    ; 
        structure(T2),
        not_occurs_problem(T1, T2) 
    ),
    !.
get_best_delay1([_|T], T1, T2) :-
    get_best_delay1(T, T1, T2).


%% not_occurs_problem(Var, Term)
%%
%% Check if a unification does not suffer from a potential occurs
%% check problem
%%
not_occurs_problem(Var, _) :-
    nonvar(Var),
    !.
not_occurs_problem(Var, Term) :-
    break_term(Var, _, V),
    \+ var_occurs_in(V, Term).


%% gen_new_sub(Sub, GenSub),
%%
%% Given a Sub of the form [t1/x1,...,tn/xn], 
%% generate GnSub of the form [x1/z1,...,xn/zn]
%% for new object vars z1,...,zn
%%
gen_new_sub([], []).
gen_new_sub([(_R/D)|Rest], [(D/!_x)|NewRest]) :-
    gen_new_sub(Rest, NewRest).


%% force_identical(X, Sub1, Sub2)
%%
%% Make the terms Sub1*X and Sub2*X (partially) identical.
%%
%%
%% If the domain list of Sub1 is the same as the last part of the
%% domain list of Sub2 (or visa versa) then simply make the subs
%% have the same effect.
%%
%% Otherwise the following is done.
%% The approach is to first generate 2 new subs that have the same effect
%% as the old subs but have domain elts (from both subs) in the same order.
%%
%% Then the new terms are simplified and the  new subs are made to
%% have the same effect.
%%
%% Note that in forcing the domain/range pairs to have the same effect more
%% delayed unification problems might be created. These problems are solved
%% before returning to the main problem. This is done by calling 
%% incomplete_retry_delays but with delay_avoid set so that only the
%% new problems are considered.
%%
force_identical(X, Sub1, Sub2) :-
    ( same_initial_segments(Sub1, Sub2) ->
        reverse(Sub1, RevS1),
        reverse(Sub2, RevS2),
        force_identical_subs(RevS1, RevS2, [], X)
    ;
        same_order_subs(Sub1, Sub2, NewSub1, NewSub2),
        build_term(T1, NewSub1, X),
        build_term(T2, NewSub2, X),
        force_identical_aux(T1, T2, X)
    ).

force_identical_aux(T1, T2, X) :-
    simplify_term(T1, SimpT1),
    simplify_term(T2, SimpT2),
    break_term(SimpT1, SimpS1, _),
    break_term(SimpT2, SimpS2, _),
    reverse(SimpS1, RevS1),
    reverse(SimpS2, RevS2),
    force_identical_subs(RevS1, RevS2, [], X).

same_initial_segments(Sub1, Sub2) :-
    parallel_sub(_, Dom1, Sub1),
    parallel_sub(_, Dom2, Sub2),
    collect_vars(Dom1, RevDom1),
    collect_vars(Dom2, RevDom2),
    same_initial_segments_aux(RevDom1, RevDom2).

same_initial_segments_aux([], _).
same_initial_segments_aux(_, []).
same_initial_segments_aux([H1|T1], [H2|T2]) :-
    H1 == H2,
    same_initial_segments_aux(T1, T2).
    
%% same_order_subs(Sub1, Sub2, NewSub1, NewSub2)
%%
%% generate subs NewSub1 and NewSub2 which have the
%% same behaviour as Sub1 and Sub2 but with domain
%% elements in the same order.
%%
same_order_subs(Sub1, Sub2, NewSub1, NewSub2) :-
    parallel_sub(_, Dom1, Sub1),
    parallel_sub(_, Dom2, Sub2),
    collect_vars([Dom1, Dom2], DU), % like union_list but faster
    collect_vars(DU,DomU),
    gen_sub_range(DomU, Sub1, SubRange1),
    gen_sub_range(DomU, Sub2, SubRange2),
    parallel_sub(SubRange1, DomU, NewSub1),
    parallel_sub(SubRange2, DomU, NewSub2).

%% gen_sub_range(DU, Sub, SubRange)
%%
%% This generates the range elements (SubRange)
%% for a sub whose domain elements are in DU. This
%% sub has the same behaviour as Sub.
%% Given DU is [x1,...,xn] then the required SubRange is
%% [Sub*x1, ..., Sub*xn]
%%
gen_sub_range([], _, []).
gen_sub_range([X|DU], Sub, [T|SubRange]) :-
    build_term(T, Sub, X),
    gen_sub_range(DU, Sub, SubRange).

%% force_identical_subs(S1, S2, Snfi, X)
%% 
%% Find the first conflict and force resolution of the conflict.
%%
force_identical_subs([], [], _, _) :-
    !.
force_identical_subs([], S2, Snfi, X) :-
    !,
    force_empty_sub(S2, Snfi, X).
force_identical_subs(S1, [], Snfi, X) :-
    !,
    force_empty_sub(S1, Snfi, X).
force_identical_subs([(R1/D1)|S1], [(R2/D2)|S2], Snfi, X) :-
    obvar(X),
    D1 == D2,
    X = D1,
    satisfy_unification(R1, R2).
force_identical_subs([(R1/D1)|S1], [(R2/D2)|S2], Snfi, X) :-
    D1 == D2,
    force_identical_entry(R1, R2, D1, Snfi, X),
    force_identical_subs(S1, S2, [(0/D1)|Snfi], X).

%% force_identical_entry(R1, R2, D, Snfi, X)
%%
%% Force sub entries R1/D and R2/D to have the same effect on Snfi*X.
%%
force_identical_entry(R1, R2, _D, _Snfi, _X) :-
    R1 == R2,
    !.
force_identical_entry(_R1, _R2, D, Snfi, X) :-
    build_term(T, Snfi, X),
    D is_not_free_in T,
    !.
force_identical_entry(R1, R2, _D, _Snfi, _X) :-
    R1 = R2,
    satisfy_unification(R1, R2).
force_identical_entry(_, _, D, Snfi, X) :-
    (thawed_var(D);thawed_var(X)),
    !,
    build_term(T, Snfi, X),
    D not_free_in T.

%% force_empty_sub(S, Snfi, X)
%% 
%% Make S have no effect on Snfi*X
%%
force_empty_sub([], _, _).
force_empty_sub([(_R/D)|S], Snfi, X) :-
    build_term(T, Snfi, X),
    D is_not_free_in T,
    !,
    force_empty_sub(S, Snfi, X).
force_empty_sub([(R/D)|S], _Snfi, X) :-
    obvar(X),
    X = D,
    satisfy_unification(R,D).
force_empty_sub([(R/D)|S], Snfi, X) :-
    R == D,
    !,
    force_empty_sub(S, [(0/D)|Snfi], X).
force_empty_sub([(R/D)|S], Snfi, X) :-
    R = D,
    satisfy_unification(R, D),
    force_empty_sub(S, [(0/D)|Snfi], X).
force_empty_sub([(_R/D)|S], Snfi, X) :-
    (thawed_var(D);thawed_var(X)),
    !,
    build_term(T, Snfi, X),
    D not_free_in T,
    force_empty_sub(S, Snfi, X).

%% satisfy_unification(T1, T2) checks if the unification has caused
%% a delayed problem and if so solve it and subsequent problems.
%%
satisfy_unification(T1, T2) :-
    T1 == T2,
    !.
satisfy_unification(T1, T2) :-
    incomplete_retry([T1 = T2]),
    retry_delays.

