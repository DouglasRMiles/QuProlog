%%
%% Simple tcp server - this starts a server on an unspecified port.
%% It outputs information to be used by a client - see tcp_client.ql
%%
%% For each connection it forks a thread that simply echos newline terminated
%% strings to the client.
%%
%% NOTE: The current implementation takes a simple view of blocking on
%% socket streams. Because of this read and read_term will block even if
%% there is some input available.
%% Consequently it is recommended that all reads be done using get or get_line.

server :-
    tcp_server(Socket,0),
    tcp_getsockname(Socket,Port,IP),
    write_term_list(['client(', Port, ', ', IP,').',nl]),
    repeat,
    tcp_accept(Socket, NewSocket),
    thread_fork(_, server_thread(NewSocket)),
    fail.

server_thread(NewSocket) :-
    open_socket_stream(NewSocket, read, ReadS),
    open_socket_stream(NewSocket, write, WriteS),
    repeat,
    get_line(ReadS, Line),
    ( Line = -1 ->                    % Client closes socket (EOF)
        tcp_close(NewSocket)  % NB closes ReadS and writeS streams
      ;
        string_concat("echo - ", Line, Out),
        put_line(WriteS, Out),
        flush_output(WriteS),    % NB - flush required
        fail
    ).
