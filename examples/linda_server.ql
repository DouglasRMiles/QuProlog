/*
 * The Linda server
 *
 * The corresponding linda client code is in linda_client.ql
 *
 * This process needs a -A linda_server_process switch when the process
 * is started in order to name it.
 */


% 
% Start the linda server
%
linda :-
	thread_set_symbol(linda_server_thread),  % name the main thread
	linda_loop.

%
% The linda repeat-fail loop that processes client connect messages by
% forking a thread to deal with the client.
%
linda_loop :-
	repeat,
	connect <<- RtAddr,		% wait for a connect message
errornl(RtAddr),
	thread_fork(_, linda_thread(RtAddr)),
	fail.

%
% The initial goal of the forked thread - one thread per client.
% The address of the client is passed to the thread so that the thread
% can finish the connection handshake with the client.
%
linda_thread(A) :-
	connected ->> A,		% finish the handshake
	thread_loop(A).

%
% The main message processing loop for the thread - only messages from its
% client are processed - all other messages are ignored.
%
thread_loop(A) :-
	repeat,
	message_choice
	(
	    out(T) <<- A ->  % an out message is received from the client
			assert(T),
			inserted ->> A
	    ;
	    in(T) <<- A ->
			thread_wait_on_goal(retract(T)),
			ok(T) ->> A
	    ;
	    rd(T) <<- A ->
			thread_wait_on_goal(clause(T, true)),
			ok(T) ->> A
	    ;
	    inp(T) <<- A ->
			(   retract(T)
			    ->
				ok(T) ->> A
			    ;
				fail ->> A
			)
	    ;
	    rdp(T) <<- A ->
			(   clause(T, true)
			    ->
				ok(T) ->> A
			    ;
				fail ->> A
			)
	    ;
	    disconnect <<- A ->         % a disconnect message is received
			thread_exit    % and so the thread is terminated.
	    ;
	    notify(T) <<- A ->
                        thread_fork(_, notify_thread(T,A))
			
	),
	fail.


%
% notify is not in the Linda model but is added to given an example
% of a thread that watches the DB. The difference between a rd message
% and a notify message is that the rd message causes the client processing
% thread to block whereas, by forking a notify thread, the client processing
% thread does not block and so the client does not block.
%
notify_thread(T,A) :-
	notified >> A,
	thread_wait_on_goal(clause(T, true)),
	notify_match(T) ->> A.


