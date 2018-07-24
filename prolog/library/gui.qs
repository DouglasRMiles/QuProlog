'reset_std_stream'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	put_integer(0, 1)
	pseudo_instr2(101, 1, 0)
	put_integer(0, 0)
	pseudo_instr1(95, 0)
	proceed

$2:
	pseudo_instr1(95, 0)
	proceed
end('reset_std_stream'/1):



'start_debug_thread_gui/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(88, 0)
	neck_cut
	fail

$2:
	proceed
end('start_debug_thread_gui/0$0'/0):



'start_debug_thread_gui'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(68, 0)
	allocate(1)
	get_y_level(0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	pseudo_instr1(88, 0)
	allocate(5)
	get_y_level(4)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_constant('$QPHOME/bin/xqpdebug', 0)
	put_integer(0, 1)
	put_integer(0, 2)
	call_predicate('access', 3, 5)
	cut(4)
	pseudo_instr1(68, 0)
	get_y_value(2, 0)
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_void(1)
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	pseudo_instr1(99, 2)
	pseudo_instr1(98, 3)
	pseudo_instr2(79, 3, 4)
	get_x_variable(3, 4)
	put_x_variable(5, 6)
	get_list(6)
	unify_constant('xqpdebug')
	unify_x_ref(6)
	get_list(6)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(3)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(2)
	unify_x_ref(0)
	get_list(0)
	unify_constant('&')
	unify_constant('[]')
	put_constant(' ', 0)
	pseudo_instr3(28, 5, 0, 4)
	get_x_variable(1, 4)
	put_structure(1, 0)
	set_constant('system')
	set_x_value(1)
	call_predicate('os', 1, 4)
	put_y_value(3, 0)
	call_predicate('debug_gui_handle', 1, 4)
	put_y_value(3, 0)
	put_y_value(1, 2)
	put_constant('read', 1)
	call_predicate('open_msgstream', 3, 4)
	put_y_value(3, 0)
	put_y_value(0, 2)
	put_constant('write', 1)
	call_predicate('open_msgstream', 3, 3)
	pseudo_instr1(102, 20)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$3:
	allocate(1)
	get_y_level(0)
	call_predicate('start_debug_thread_gui/0$0', 0, 1)
	cut(0)
	pseudo_instr1(68, 0)
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_x_value(1)
	set_integer(0)
	set_integer(2)
	deallocate
	execute_predicate('assert', 1)
end('start_debug_thread_gui'/0):



'exit_debug_thread_gui'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(68, 0)
	get_x_variable(1, 0)
	allocate(3)
	get_y_level(2)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_x_value(1)
	set_y_variable(1)
	set_y_variable(0)
	call_predicate('retract', 1, 3)
	put_integer(0, 0)
	pseudo_instr2(133, 21, 0)
	cut(2)
	put_y_value(0, 0)
	put_constant('$exit_gui', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 2)
	put_y_value(1, 0)
	call_predicate('close', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('close', 1)

$2:
	proceed
end('exit_debug_thread_gui'/0):



'debug_gui_handle'/1:


$1:
	pseudo_instr1(90, 1)
	get_structure('@', 2, 1)
	unify_x_ref(1)
	unify_x_variable(2)
	get_structure(':', 2, 1)
	unify_x_variable(1)
	unify_x_variable(3)
	put_x_variable(5, 6)
	get_list(6)
	unify_x_value(1)
	unify_x_ref(1)
	get_list(1)
	unify_x_value(3)
	unify_x_ref(1)
	get_list(1)
	unify_constant('debug_gui')
	unify_constant('[]')
	put_constant('_', 1)
	pseudo_instr3(28, 5, 1, 4)
	get_x_variable(1, 4)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(2)
	get_structure(':', 2, 0)
	unify_constant('')
	unify_x_value(1)
	proceed
end('debug_gui_handle'/1):



'write_debug_msg_term_list'/1:


$1:
	allocate(3)
	get_y_variable(1, 0)
	pseudo_instr1(68, 0)
	put_y_variable(0, 19)
	put_x_variable(1, 1)
	put_y_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$streamnum', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$write_term_list', 2)
end('write_debug_msg_term_list'/1):



'write_debug_msg_term'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	pseudo_instr1(68, 0)
	put_x_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('write_term', 3)
end('write_debug_msg_term'/2):



'read_debug_msg_codes'/1:


$1:
	allocate(4)
	get_y_variable(1, 0)
	pseudo_instr1(68, 0)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('get_line', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('string_to_list', 2, 2)
	put_y_value(0, 0)
	put_list(1)
	set_integer(10)
	set_constant('[]')
	put_y_value(1, 2)
	deallocate
	execute_predicate('append', 3)
end('read_debug_msg_codes'/1):



'read_debug_msg_term'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	pseudo_instr1(68, 0)
	put_y_variable(0, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('read_term', 3)
end('read_debug_msg_term'/2):



