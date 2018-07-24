%%
%% A simple example of connecting to a web server
%%
%% Example use
%%
%% ?- [http_connect].
%%
%% ?- http_connect('www.itee.uq.edu.au').
%%
%% ?- http_command("GET /index.jsp HTTP/1.0\n").
%%
%% http_read_line(L) can now be used to read the contents of index.jsp
%%
 
http_connect(URL) :-
    tcp_host_to_ip_address(URL, IP),
    tcp_client(80, IP, Socket),
    open_socket_stream(Socket, read, ReadS),
    open_socket_stream(Socket, write, WriteS),
    assert(client_socket(Socket)),
    assert(client_read(ReadS)),
    assert(client_write(WriteS)).

http_command(Command) :-
    client_write(WriteS),
    put_line(WriteS, Command),
    flush_output(WriteS).

http_read_line(Line) :-
    client_read(ReadS),
    get_line(ReadS, Line).

http_close :-
    retract(client_socket(Socket)),
    retract(client_read(_)),
    retract(client_write(_)),
    tcp_close(Socket).

