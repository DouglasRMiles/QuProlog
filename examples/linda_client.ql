/*
 * Linda client support
 *
 * The corresponding linda server code is in linda_server.ql
 */


%
% linda_connect initiates a connection with the Linda server.
% The returning connected message comes from the Linda thread created
% to process this client's Linda queries.
% The address of the server thread is stored in the record DB so that
% this client can send Linda queries to the correct server thread.
% Note that the thread ID of the client is also recorded so that
% multiple clients within the same process can be used.
%
linda_connect :-
	connect ->> linda_server_thread:linda_server_process,
	connected <<= A,
	thread_symbol(TID),
	assert(idaddr(TID,A)). 
%
% disconnect from the Linda server and remove the recorded address.
%
linda_disconnect :-
	thread_symbol(TID),
        retract(idaddr(TID,A)),
        disconnect ->> A.

%
% The Linda queries.
%
linda_out(T) :-
	thread_symbol(TID),
        idaddr(TID,A),
	out(T) ->> A,
	inserted <<= A.

linda_in(T) :-
	thread_symbol(TID),
        idaddr(TID,A),
	in(T) ->> A,
	ok(T) <<= A.
	
linda_rd(T) :-
	thread_symbol(TID),
        idaddr(TID,A),
	rd(T) ->> A,
	ok(T) <<= A.

linda_inp(T) :-
	thread_symbol(TID),
        idaddr(TID,A),
	inp(T) ->> A,
	M <<= A,
	M = ok(T).
	
linda_rdp(T) :-
	thread_symbol(TID),
        idaddr(TID,A),
	rdp(T) ->> A,
	M <<= A,
	M = ok(T).

%
% A notify query - this call returns immediately.
%
linda_notify(T) :-
	thread_symbol(TID),
        idaddr(TID,A), 
	notify(T) ->> A,
	notified <<= A.

%
% linda_check_notify succeeds and returns the instantiated notify pattern if
% a notify message is received, otherwise fails.
%
% mode linda_check_notify(-Term).
%
linda_check_notify(T) :-
        message_choice (
            notify_match(T) <<- _ -> true
            ;
            timeout(0) -> fail
        ).
	
