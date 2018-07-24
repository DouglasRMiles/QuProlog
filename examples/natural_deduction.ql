/*
 * A simple Natural Deduction theorem prover.
 *
 * Note: This prover can overconstrain the theorem being proved
 * by adding not_free_in conditions involving variables occurring
 * in the statement of the theorem. Typically, this happens during
 * incomplete_retry_delays. This could be fixed by maintaining a list
 * of constraints that are part of the statement of the theorem and
 * by checking the current set of constraints against this set
 * immediately after calling incomplete_retry_delays.
 *
 */


/*
 * Operator declarations
 */


?-op(500, quant, all).
?-op(500, quant, ex).

?-op(480, fy, ~).
?-op(520, xfy, and).
?-op(530, xfy, or).
?-op(540, xfy, =>).

?-op(580, xfx, -->).

?-op(710, xfy, then).
?-op(710, xfy, orelse).
?-op(700, fy, repeat_tac).

?-obvar_prefix(x).

/*
 * Database of ND rules
 *
 *  E.G.          [Gamma --> A, Gammma --> B]
 *      (and_i)   -----------------------------
 *                       Gamma --> A and B
 */

rule(discharge(N), Gamma --> A, [[] --> true]) :- 
	nth_item(N, A, Gamma).
rule(and_i, Gamma --> A and B, [(Gamma --> A), (Gamma --> B)]).
rule(or_i1, Gamma --> A or B, [Gamma --> A]).
rule(or_i2, Gamma --> A or B, [Gamma --> B]).
rule(imp_i, Gamma --> A => B, [[A|Gamma] --> B]).
rule(neg_i, Gamma --> ~A , [[A|Gamma] --> false]).
rule(all_i, Gamma --> all x A, [Gamma --> A]) :- 
	x not_free_in Gamma.
rule(ex_i, Gamma --> ex x A, [Gamma --> [T/x]A]).
rule(false_i, Gamma --> A, [Gamma --> false]).

rule(and_e(N), Gamma --> C, [[A,B|NewGamma] --> C]) :- 
	nth_and_rest(N, A and B, Gamma, NewGamma).
rule(imp_e(N), Gamma --> C, [NewGamma --> A, ([B|NewGamma] --> C)]) :-
	nth_and_rest(N, A => B, Gamma, NewGamma).
rule(or_e(N), Gamma --> C, [[A|NewGamma] --> C, ([B|NewGamma] --> C)]) :-
	nth_and_rest(N, A or B, Gamma, NewGamma).
rule(neg_e(N), Gamma --> C, [(NewGamma --> A), ([false|NewGamma] --> C)]) :-
	nth_and_rest(N, ~A, Gamma, NewGamma).
rule(all_e(N), Gamma --> C, [[[T/x]A | Gamma] --> C]) :-
	nth_item(N, all x A, Gamma).
rule(ex_e(N), Gamma --> C, [[A|NewGamma] --> C]) :-
	nth_and_rest(N, ex x A, Gamma, NewGamma),
	x not_free_in NewGamma,
	x not_free_in C. 

rule(modus_ponens, Gamma --> C, [(Gamma --> Lemma), ([Lemma|Gamma] --> C)]).

/*******************************************************************
 * Library routines 
 *******************************************************************/

nth_item(1, A, [B|_]) :- A = B.
nth_item(N, A, [_|T]) :- nth_item(M, A, T), N is M + 1.

nth_and_rest(1, A, [A|T], T).
nth_and_rest(N, A, [H|T], [H|NT]) :- nth_and_rest(M, A, T, NT), N is M + 1.

save_theorem(Name, Theorem) :-
	collect_vars(Theorem, Vars),
	retry_delays,
	collect_constraints(Vars, Distinct, NFI, Others),
	list_to_conj(Distinct, true, C1),
	list_to_conj(NFI, C1, C2),
	list_to_conj(Others, C2, Conjunction),
	assert((theorem(Name, Theorem) :- Conjunction)).

list_to_conj([H|T], true, C) :-
	!, 
	list_to_conj1(T, H, C).
list_to_conj(List, C0, C) :-
	list_to_conj1(List, C0, C).

list_to_conj1([], X, X).
list_to_conj1([H|T], C0, C) :-
	list_to_conj1(T, (H, C0), C).


/********************************************************************
 * Proof commands - the system kernel.
 * Interfaces and tactics should access the proof state
 * only through these commands.
 ********************************************************************/

/* Create a new proof state */
new_proof(Name, T) :-
	ip_set(statement, theorem(Name, T)),
	ip_set(proof_state, [([] --> T)]).

/* End a proof */
end_proof  :-
	ip_lookup(proof_state, []),
	ip_lookup(statement, theorem(Name, T)),
	save_theorem(Name, T).

/* End a proof branch */
end_branch :-
	ip_lookup(proof_state, [([] --> true)|R]),
	ip_set(proof_state, R).

/* Apply inference rule to 1st problem of the proof state */
trans(Rule) :-
	ip_lookup(proof_state, [HeadProblem|OtherProblems]),
	rule(Rule, HeadProblem, NewHead),
	incomplete_retry_delays,
	append(NewHead, OtherProblems, Problems),
	ip_set(proof_state, Problems).

/* Look up the 1st problem of the proof state */
head_problem(P) :-
	ip_lookup(proof_state, [P|_]).

/* Look up all the problems of the proof state */
all_problems(P) :-
	ip_lookup(proof_state, P).

/* Extract the name and statement of the theorem */
statement(T) :-
	ip_lookup(statement,T).

/* A simple recursive interpreter for proofs */

get_command(C) :-
	auto,
	nl,
	display_head_problem,
	nl, nl,
        write(':: '),
        flush_output(stdout),
        readR(C).

prove(Name, T) :-
	new_proof(Name, T),
	freeze_vars(T),
	get_command(C),
	proof_interpreter(C).

proof_interpreter(quit). 
proof_interpreter(end_proof) :-
	end_proof, !.
proof_interpreter(show_constraints) :-
	!,
	show_constraints,
	get_command(NewC),
	proof_interpreter(NewC).
proof_interpreter(undo) :-
	!, fail.
proof_interpreter(hint) :-
	!,
	hint,
	get_command(NewC),
	proof_interpreter(NewC).
proof_interpreter(C) :-
	call(C),
	get_command(NewC),
	proof_interpreter(NewC).
proof_interpreter(C) :-
	writeR(C),
	write(' failed'),
	nl,
	fail.
proof_interpreter(_) :-
	get_command(NewC),
	proof_interpreter(NewC).


/* turn rule names into interpreter proof commands */

discharge_theorem(N) :- trans(discharge_theorem(N)).
discharge(N) :- trans(discharge(N)).
and_i :- trans(and_i).
or_i1 :- trans(or_i1).
or_i2 :- trans(or_i2).
imp_i :- trans(imp_i).
neg_i :- trans(neg_i).
all_i :- trans(all_i).
ex_i :- trans(ex_i).
false_i :- trans(false_i).
and_e(N) :- trans(and_e(N)).
imp_e(N) :- trans(imp_e(N)).
or_e(N) :- trans(or_e(N)).
neg_e(N) :- trans(neg_e(N)).
all_e(N) :- trans(all_e(N)).
ex_e(N) :- trans(ex_e(N)).
modus_ponens :- trans(modus_ponens).


/**************************************************************
 * Examples of "tactics" 
 **************************************************************/

/* Suggestions for the user */

hint :-
	head_problem(P),
	rule(R, P, NP),
	write('rule - '),
	writeR(R),
	write(' transforms 1st problem to :'),
	nl,
	writeR(NP),
	nl,
	fail.
hint.
	
/* display the current problem */

display_head_problem :-
	(   head_problem(Gamma --> P)
	    ->
		display_gamma(0, Gamma),
		write('---------------------------------------------------'),
		nl,
		simplify_term(P, SimpP),
		writeR(SimpP)
            ; 
                write('no branches left')
        ).
show_constraints :-
	all_problems(All),
	statement(Theorem),
	retry_delays,
	simplify_term(All, SimpAll),
	collect_vars([Theorem, SimpAll], AllVars),
	collect_constraints(AllVars, Distinct, NFI, Others),
	display_constraints(Distinct, NFI, Others),
	nl.
	
display_gamma(_, []).
display_gamma(N, [H|T]) :-
	M is N + 1,
	write(M),
	write(':  '),
	simplify_term(H, SimpH),
	writeR(SimpH),
	nl,
	display_gamma(M, T).

display_constraints([], [], []) :- !.
display_constraints(L1, L2, L3) :-
	nl,
	disp_list(L1),
	disp_list(L2),
	disp_list(L3).
disp_list([]).
disp_list([H|T]) :-
	nl,
	writeR(H),
	disp_list(T).


/* some tacticals (as in e.g. Isabelle) */

A then B :-
	call(A),
	call(B).

A orelse B :-
	call(A);call(B).

id_tac.

repeat_tac A :-
	(A then repeat_tac A) orelse id_tac.

/*****************************************************************
 * A simple (semi-)automated proof strategy. 
 * Alternatively it can be thought of as an automatic simplification
 * tactic.
 *****************************************************************/

auto :-
	heuristic_table(Code, Message),
	call(Code),
	!,
	write(auto:Message),
	nl,
	auto.
auto.

heuristic_table(end_branch, end_branch).
heuristic_table(trans(discharge(N)), discharge(N)).
heuristic_table(trans(all_i), all_i).
heuristic_table(trans(and_i), and_i).
heuristic_table(trans(imp_i), imp_i).
heuristic_table(trans(neg_i), neg_i).
heuristic_table(trans(imp_e(N)), imp_e(N)).
heuristic_table(trans(or_e(N)), or_e(N)).
heuristic_table(trans(and_e(N)), and_e(N)).
heuristic_table(trans(ex_e(N)), ex_e(N)).
