%
% router_monitor.ql
%
% A simple message monitor.
%
% Other processes can send messages to this process setting the to
% address to the address of the real recipient.
% The monitor displays the message information and forwards the message on
% to the recipient.
%

main(_) :-
    router_monitor.

router_monitor :-
    repeat,
    ipc_recv(Msg , From),
    ( Msg == quit
      ->
        true
      ;
        Msg = to(RealMsg, To),
	From = FThread:FProcess@FMachine,
	To = ToThread:ToProcess@ToMachine,
        write('Message: '), write(Msg),
        write_term_list([nl, wa('From: '), w(FThread), tab(3),
                         wa(FProcess), tab(3), wa(FMachine)]),
        write_term_list([nl, wa('To: '), w(ToThread), tab(3),
                         wa(ToProcess), tab(3), wa(ToMachine)]),
        nl,
        ipc_send(from(RealMsg, From), To),
        fail
    ).
