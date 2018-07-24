'main/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(88, 0)
	allocate(1)
	get_y_level(0)
	put_constant('gui', 0)
	call_predicate('member', 2, 1)
	cut(0)
	put_constant('$gui_state', 0)
	put_constant('gui', 1)
	pseudo_instr2(74, 0, 1)
	deallocate
	execute_predicate('start_thread_gui', 0)

$2:
	put_constant('$gui_state', 0)
	put_constant('dumb', 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('main/1$0'/1):



'main'/1:


$1:
	allocate(3)
	get_y_variable(2, 0)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	put_constant('version', 0)
	call_predicate('current_prolog_flag', 2, 3)
	put_y_value(2, 0)
	call_predicate('main/1$0', 1, 2)
	put_x_variable(0, 1)
	put_structure(1, 2)
	set_constant('$catch_init_goal')
	set_x_value(0)
	put_constant('$process_initial_goal', 0)
	call_predicate('catch', 3, 2)
	pseudo_instr1(28, 0)
	get_y_value(0, 0)
	put_y_value(0, 0)
	put_constant('Qu-Prolog Version ', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('write', 2)
	call_predicate('$write_t', 3, 1)
	put_y_value(0, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 0)
	deallocate
	execute_predicate('interpreter', 0)
end('main'/1):



'$process_initial_goal'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(106, 0)
	get_x_variable(1, 0)
	allocate(3)
	get_y_level(0)
	put_y_variable(1, 19)
	put_structure(1, 0)
	set_constant('read')
	set_x_value(1)
	put_y_variable(2, 1)
	call_predicate('open_string', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('read', 2, 2)
	put_y_value(1, 0)
	call_predicate('call', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	proceed
end('$process_initial_goal'/0):



'$catch_init_goal'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'exception'/1:$5])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$6:
	try(1, $1)
	trust($2)

$1:
	get_structure('exception', 1, 0)
	allocate(7)
	unify_y_variable(6)
	neck_cut
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(6, 0)
	put_y_variable(5, 1)
	put_y_variable(4, 2)
	put_y_variable(3, 3)
	put_y_variable(2, 4)
	call_predicate('$valid_exception_term', 5, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	call_predicate('$get_exception_message', 6, 2)
	put_y_value(0, 1)
	put_constant('stderr', 0)
	call_predicate('$streamnum', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('$write_term_list', 2, 0)
	pseudo_instr0(8)
	deallocate
	proceed

$2:
	allocate(0)
	call_predicate('errornl', 1, 0)
	pseudo_instr0(8)
	deallocate
	proceed
end('$catch_init_goal'/1):



