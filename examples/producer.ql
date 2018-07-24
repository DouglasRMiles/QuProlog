% producer.ql
% A simple example of using Pedro communication. The file consumer.ql 
% contains code for receiving notifications from the producer.
%

% Start the producer
start :-
    pedro_connect.

% send a notification 
send(Msg) :-
    pedro_notify(producer(Msg)).

