%%
%% A client for the simple server (see tcp_server.ql).
%%

%% Set up connection and open streams
client(Port, IP) :-
    tcp_client(Port, IP, Socket),
    open_socket_stream(Socket, read, ReadS),
    open_socket_stream(Socket, write, WriteS),
    assert(client_socket(Socket)),
    assert(client_read(ReadS)),
    assert(client_write(WriteS)).

%% Close connection (tcp_close closes the streams)
close_client :-
    client_socket(Socket),
    tcp_close(Socket),
    retract(client_read(_)),
    retract(client_write(_)),
    retract(client_socket(_)).

%% Send a line to the server
client_put_line(List) :-
    client_write(WriteS),
    put_line(WriteS, List),
    flush_output(WriteS).

%% Read a line from the server.
client_get_line(List) :-
    client_read(ReadS),
    get_line(ReadS, List).

