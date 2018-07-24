% consumer.ql
% A simple example of using Pedro subscription/notification communication. 
% See producer.ql
% 

% Start the consumer - simply connect to the Pedro server on this machine 
% and add a subscription
start :-
    pedro_connect,   
    pedro_subscribe(producer(T), true, _),
    message_loop.

% Start a loop waiting for messages and display them on stdout - exit
% when a message with a quit field arrives

message_loop :-
    repeat,
    M <<- _,       % get the first message
    write(M), nl,
    M = producer(quit).

