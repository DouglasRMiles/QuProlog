
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% An external shared database
%%
%% This file contains 2 parts.
%% The first part is some definitions for the database.
%% The second part is some support definitions for DB clients.
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%
%% The database server.
%%
%% listener starts the database server. The database is
%% named db_thread:db_server. If this is to be used over a network of
%% machines then the machine name on which the server is running needs
%% to be added to the addresses used in the client messages.
%% This process needs to be started with a -A db_server switch.
%%
listener :-
	thread_set_symbol(db_thread),
	listener_loop.

%%
%% The listener_loop is used to process queries as messages from clients.
%% The possible queries are:
%% add_fact(Fact)    - asserts Fact to the database.
%% remove_fact(Fact) - retracts Fact from the database.
%% ask_all(Query)    - sends the client the list of all the answers to Query.
%% stand_by(Query)   - forks a thread that sends answers to Query to the
%%                     client on request.

listener_loop :-
repeat,
  message_choice (
    add_fact(Fact) <<- _ -> assert(Fact)
    ;
    remove_fact(Fact) <<- _ -> retract(Fact)
    ;
    ask_all(Query) <<- Address ->
	findall(Query, Query, Ans),
	answers(Ans) ->> Address
    ;
    stand_by(Query) <<-  Address ->
	thread_fork(_, ans_gen(Query, Address))
  ),
  fail.

%%
%% ans_gen(Query, Address) is the initial query for the thread created
%% in order to send solutions of Query to the client at Address upon request.
%%
ans_gen(Query, Address) :-
    generator ->> Address, % handshake so that the client knows my address
    ( call(Query), QueryAns = Query ; QueryAns = fail ; true),
    message_choice 
    (
      next <<- Address ->
          next_soln(QueryAns) ->> Address,
          fail
  ;
      die <<- Address ->
          true
    ).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%% Client support
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%
%% db_add(P) sends an add_fact(P) message to the DB server.
%%
db_add(P) :-
    add_fact(P) ->> db_thread:db_server.
%%
%% db_remove(P) sends an remove_fact(P) message to the DB server.
%%
db_remove(P) :-
    remove_fact(P) ->> db_thread:db_server.

%%
%% eager_client_query(Query) asks the server to return all solutions of
%% Query and then locally uses member to extract them one at a time.
%%
eager_client_query(Query) :-
    ask_all(Query) ->> db_thread:db_server,
    answers(Ans) <<= db_thread:db_server,
    member(Query, Ans).

%%
%% lazy_client_query(Query) asks the server to return answers one at a time
%% on request.
%% The call_cleanup will send the 'die' message as soon as get_an_answer
%% fails or succeeds deterministically - deleting the server thread created
%% to manage this query.
lazy_client_query(Query) :-
    stand_by(Query) ->> db_thread:db_server,
    generator <<= Generator_address,   % now I know the server threads address
    call_cleanup(get_an_answer(Query, Generator_address), 
                 die ->> Generator_address).

%%
%% get_an_answer(Query, Generator_address), on backtracking, requests
%% the next solution to the query.
%%
get_an_answer(Query, Generator_address) :-
    next ->> Generator_address,
    next_soln(Q) <<= Generator_address,
    (   Q == fail
	->
	    !,fail
	;
	    Query = Q
    ).
get_an_answer(Query, Generator_address) :-
    get_an_answer(Query, Generator_address).

