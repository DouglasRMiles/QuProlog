'open_socket_stream/3$0'/5:

	try(5, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	allocate(1)
	get_y_level(0)
	call_predicate('$iomode', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(5, 0)
	put_structure(3, 0)
	set_constant('open_socket_stream')
	set_x_value(3)
	set_x_value(5)
	set_x_value(4)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('open_socket_stream')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('open_socket_stream/3$0'/5):



'open_socket_stream/3$1/4$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_integer(-1, 3)
	get_x_value(0, 3)
	neck_cut
	put_x_variable(3, 4)
	get_structure('open_socket_stream', 3, 4)
	unify_x_value(1)
	unify_x_value(2)
	unify_x_value(0)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(3)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened stream ')
	set_x_value(2)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('open_socket_stream/3$1/4$0'/3):



'open_socket_stream/3$1'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 2)
	get_x_variable(2, 3)
	pseudo_instr3(48, 4, 1, 3)
	get_x_value(0, 3)
	neck_cut
	put_x_value(4, 1)
	execute_predicate('open_socket_stream/3$1/4$0', 3)

$2:
	put_structure(3, 1)
	set_constant('open_socket_stream')
	set_x_value(0)
	set_x_value(3)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('open_socket_stream/3$1'/4):



'open_socket_stream/3$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('open_socket_stream/3$2'/1):



'open_socket_stream'/3:

	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('open_socket_stream')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('open_socket_stream')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	pseudo_instr1(3, 24)
	get_y_level(6)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_variable(2, 1)
	put_y_variable(5, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	call_predicate('open_socket_stream/3$0', 5, 7)
	cut(6)
	put_y_value(0, 0)
	get_structure('$prop', 7, 0)
	unify_y_value(3)
	unify_y_value(5)
	unify_constant('file')
	unify_constant('none')
	unify_constant('reset')
	unify_constant('false')
	unify_constant('text')
	put_y_value(4, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	call_predicate('open_socket_stream/3$1', 4, 2)
	pseudo_instr2(100, 21, 20)
	deallocate
	proceed

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('open_socket_stream')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('open_socket_stream')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('open_socket_stream/3$2', 1, 4)
	cut(3)
	put_structure(4, 0)
	set_constant('open_socket_stream')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	set_void(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('open_socket_stream')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)
end('open_socket_stream'/3):



'tcp_server'/2:


$1:
	put_constant('inaddr_any', 2)
	execute_predicate('tcp_server', 3)
end('tcp_server'/2):



'tcp_server/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'localhost':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('inaddr_any', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_value(1, 0)
	proceed
end('tcp_server/3$0'/2):



'tcp_server/3$1'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr3(46, 0, 1, 2)
	pseudo_instr1(56, 0)
	proceed

$2:
	pseudo_instr1(58, 0)
	fail
end('tcp_server/3$1'/3):



'tcp_server'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_y_level(0)
	put_y_variable(1, 1)
	call_predicate('tcp_server/3$0', 2, 4)
	put_y_value(3, 0)
	call_predicate('tcp_open', 1, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	call_predicate('tcp_server/3$1', 3, 1)
	cut(0)
	deallocate
	proceed
end('tcp_server'/3):



'tcp_client/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	execute_predicate('tcp_connect', 3)

$2:
	pseudo_instr1(58, 0)
	fail
end('tcp_client/3$0'/3):



'tcp_client'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_level(0)
	put_y_value(1, 0)
	call_predicate('tcp_open', 1, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	call_predicate('tcp_client/3$0', 3, 1)
	cut(0)
	deallocate
	proceed
end('tcp_client'/3):



'tcp_open'/1:


$1:
	put_constant('sock_stream', 2)
	put_constant('ipproto_ip', 3)
	pseudo_instr3(43, 1, 2, 3)
	get_x_value(0, 1)
	proceed
end('tcp_open'/1):



'tcp_bind'/2:


$1:
	put_constant('inaddr_any', 2)
	pseudo_instr3(46, 0, 1, 2)
	proceed
end('tcp_bind'/2):



'tcp_accept'/2:


$1:
	pseudo_instr4(9, 0, 2, 3, 4)
	get_x_value(1, 2)
	proceed
end('tcp_accept'/2):



'tcp_connect/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'localhost':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('localhost', 2)
	pseudo_instr2(79, 2, 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_value(1, 0)
	proceed
end('tcp_connect/3$0'/2):



'tcp_connect'/3:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_x_variable(0, 2)
	put_y_variable(0, 1)
	call_predicate('tcp_connect/3$0', 2, 3)
	pseudo_instr3(47, 22, 21, 20)
	deallocate
	proceed
end('tcp_connect'/3):



'tcp_getservbyname/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	pseudo_instr3(52, 1, 3, 4)
	get_x_value(0, 3)
	get_x_value(2, 4)
	proceed

$2:
	pseudo_instr3(53, 1, 0, 3)
	get_x_value(2, 3)
	proceed
end('tcp_getservbyname/3$0'/3):



'tcp_getservbyname'/3:


$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	put_x_value(3, 1)
	execute_predicate('tcp_getservbyname/3$0', 3)
end('tcp_getservbyname'/3):



'tcp_getservbyport/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	pseudo_instr3(55, 3, 4, 2)
	get_x_value(1, 3)
	get_x_value(0, 4)
	proceed

$2:
	pseudo_instr3(54, 3, 0, 2)
	get_x_value(1, 3)
	proceed
end('tcp_getservbyport/3$0'/3):



'tcp_getservbyport'/3:


$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	put_x_value(3, 1)
	execute_predicate('tcp_getservbyport/3$0', 3)
end('tcp_getservbyport'/3):



