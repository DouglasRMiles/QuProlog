'$init_debug'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('$thread_debug_set')
	set_integer(3)
	allocate(0)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$spypoint')
	set_integer(2)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$spy_cond')
	set_integer(3)
	call_predicate('dynamic', 1, 0)
	put_constant('$debugger_status', 0)
	put_constant('off', 1)
	pseudo_instr2(74, 0, 1)
	put_constant('$leashing', 0)
	put_integer(31, 1)
	pseudo_instr2(74, 0, 1)
	deallocate
	proceed
end('$init_debug'/0):



'$set_basic_debugger_state'/3:


$1:
	put_constant('$debug_id', 3)
	pseudo_instr2(74, 3, 0)
	put_constant('$debug_path', 0)
	pseudo_instr2(3, 0, 1)
	put_constant('$skip_retry_fail', 0)
	pseudo_instr2(74, 0, 2)
	proceed
end('$set_basic_debugger_state'/3):



'$set_debugger_state'/1:


$1:
	get_structure('$debug_state', 6, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_x_variable(5)
	put_constant('$debugger_status', 6)
	pseudo_instr2(74, 6, 0)
	put_constant('$leashing', 0)
	pseudo_instr2(74, 0, 1)
	put_constant('$debug_id', 0)
	pseudo_instr2(74, 0, 2)
	put_constant('$debug_path', 0)
	pseudo_instr2(3, 0, 3)
	put_constant('$debug_print', 0)
	pseudo_instr2(74, 0, 4)
	put_constant('$skip_retry_fail', 0)
	pseudo_instr2(74, 0, 5)
	proceed
end('$set_debugger_state'/1):



'$get_basic_debugger_state'/3:


$1:
	put_constant('$debug_id', 4)
	pseudo_instr2(73, 4, 3)
	get_x_value(0, 3)
	put_constant('$debug_path', 3)
	pseudo_instr2(4, 3, 0)
	get_x_value(1, 0)
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(73, 1, 0)
	get_x_value(2, 0)
	proceed
end('$get_basic_debugger_state'/3):



'$get_debugger_state'/1:


$1:
	get_structure('$debug_state', 6, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_x_variable(5)
	put_constant('$debugger_status', 7)
	pseudo_instr2(73, 7, 6)
	get_x_value(0, 6)
	put_constant('$leashing', 6)
	pseudo_instr2(73, 6, 0)
	get_x_value(1, 0)
	put_constant('$debug_id', 1)
	pseudo_instr2(73, 1, 0)
	get_x_value(2, 0)
	put_constant('$debug_path', 1)
	pseudo_instr2(4, 1, 0)
	get_x_value(3, 0)
	put_constant('$debug_print', 1)
	pseudo_instr2(73, 1, 0)
	get_x_value(4, 0)
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(73, 1, 0)
	get_x_value(5, 0)
	proceed
end('$get_debugger_state'/1):



'debug/0$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 1)
	cut(0)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('debug')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	deallocate
	execute_predicate('$set_debugger_state', 1)

$2:
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_x_value(1)
	set_integer(0)
	set_integer(2)
	allocate(0)
	call_predicate('assert', 1, 0)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('debug')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	deallocate
	execute_predicate('$set_debugger_state', 1)
end('debug/0$0'/1):



'debug'/0:


$1:
	pseudo_instr1(68, 0)
	execute_predicate('debug/0$0', 1)
end('debug'/0):



'xdebug'/0:


$1:
	allocate(0)
	call_predicate('nodebug', 0, 0)
	call_predicate('start_debug_thread_gui', 0, 0)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('debug')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	deallocate
	execute_predicate('$set_debugger_state', 1)
end('xdebug'/0):



'nodebug/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_constant('$debugger_status', 0)
	put_constant('off', 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('nodebug/0$0'/0):



'nodebug'/0:


$1:
	allocate(0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	deallocate
	execute_predicate('nodebug/0$0', 0)
end('nodebug'/0):



'debugging'/0:


$1:
	allocate(0)
	call_predicate('$print_debugger_status', 0, 0)
	call_predicate('$print_spy_points', 0, 0)
	deallocate
	execute_predicate('$print_leash_mode', 0)
end('debugging'/0):



'$print_debugger_status'/0:


$1:
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	put_list(1)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('.')
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('wa')
	set_x_value(0)
	put_list(2)
	set_x_value(1)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('The debugger is switched to ')
	put_list(0)
	set_x_value(1)
	set_x_value(2)
	execute_predicate('write_debug_msg_term_list', 1)
end('$print_debugger_status'/0):



'$print_spy_points/0$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(3, 21)
	neck_cut
	put_structure(1, 0)
	set_constant('wi')
	set_y_value(1)
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('/')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	call_predicate('write_debug_msg_term_list', 1, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$print_spy_conds', 2)

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	put_y_variable(0, 19)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 3)
	put_y_value(2, 0)
	put_structure(3, 1)
	set_constant('$spy_cond')
	set_x_variable(2)
	set_x_variable(3)
	set_x_variable(4)
	put_structure(3, 5)
	set_constant('functor')
	set_x_value(2)
	set_y_value(1)
	set_y_value(2)
	put_structure(2, 6)
	set_constant(',')
	set_x_value(1)
	set_x_value(5)
	put_structure(2, 1)
	set_constant('^')
	set_x_value(4)
	set_x_value(6)
	put_structure(2, 4)
	set_constant('^')
	set_x_value(3)
	set_x_value(1)
	put_structure(2, 1)
	set_constant('^')
	set_x_value(2)
	set_x_value(4)
	put_y_value(0, 2)
	call_predicate('setof', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$print_spy_conds', 2)
end('$print_spy_points/0$0'/2):



'$print_spy_points'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(2)
	put_y_variable(1, 0)
	put_y_variable(0, 1)
	call_predicate('$spypoint', 2, 2)
	put_structure(1, 0)
	set_constant('wa')
	set_y_value(1)
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 0)
	set_constant('wa')
	set_constant('    ')
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_list(1)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('wa')
	set_constant('Spy points:')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	call_predicate('write_debug_msg_term_list', 1, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('$print_spy_points/0$0', 2, 0)
	fail

$2:
	proceed
end('$print_spy_points'/0):



'$print_spy_conds'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_list(1)
	unify_y_variable(2)
	unify_y_variable(0)
	put_structure(1, 0)
	set_constant('wi')
	set_y_value(2)
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 0)
	set_constant('wa')
	set_constant('/')
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_structure(1, 0)
	set_constant('wa')
	set_y_value(1)
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_structure(1, 2)
	set_constant('wa')
	set_constant('    ')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	call_predicate('write_debug_msg_term_list', 1, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$print_spy_conds', 2, 2)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$print_spy_conds', 2)

$2:
	pseudo_instr1(3, 1)
	allocate(3)
	put_y_variable(2, 19)
	pseudo_instr3(0, 22, 0, 1)
	put_y_value(2, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$spy_cond', 3, 3)
	put_structure(1, 0)
	set_constant('w')
	set_y_value(0)
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 0)
	set_constant('wa')
	set_constant('      Cond: ')
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('w')
	set_y_value(1)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_structure(1, 0)
	set_constant('wa')
	set_constant('      Port: ')
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_list(0)
	set_constant('nl')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('w')
	set_y_value(2)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_structure(1, 0)
	set_constant('wa')
	set_constant('      Goal: ')
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_list(2)
	set_constant('nl')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('wa')
	set_constant(' (conditional): ')
	put_list(0)
	set_x_value(1)
	set_x_value(2)
	call_predicate('write_debug_msg_term_list', 1, 0)
	fail

$3:
	proceed
end('$print_spy_conds'/2):



'$print_leash_mode'/0:

	try(0, $1)
	trust($2)

$1:
	put_structure(1, 1)
	set_constant('wa')
	set_constant('Leashing at [')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	allocate(0)
	call_predicate('write_debug_msg_term_list', 1, 0)
	put_constant('$leashing', 1)
	pseudo_instr2(73, 1, 0)
	deallocate
	execute_predicate('$print_leash_port', 1)

$2:
	put_list(1)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('] ports.')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	execute_predicate('write_debug_msg_term_list', 1)
end('$print_leash_mode'/0):



'$print_leash_port'/1:


$1:
	allocate(3)
	get_y_variable(2, 0)
	put_y_variable(0, 0)
	put_y_variable(1, 1)
	call_predicate('$leash_name', 2, 3)
	put_x_variable(1, 2)
	get_structure('/\\', 2, 2)
	unify_y_value(2)
	unify_y_value(1)
	pseudo_instr2(0, 0, 1)
	get_y_value(1, 0)
	put_list(1)
	set_constant('sp')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_y_value(0)
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	call_predicate('write_debug_msg_term_list', 1, 0)
	fail
end('$print_leash_port'/1):



'trace/0$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 1)
	cut(0)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('trace')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	deallocate
	execute_predicate('$set_debugger_state', 1)

$2:
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_x_value(1)
	set_integer(0)
	set_integer(2)
	allocate(0)
	call_predicate('assert', 1, 0)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('trace')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	deallocate
	execute_predicate('$set_debugger_state', 1)
end('trace/0$0'/1):



'trace'/0:


$1:
	pseudo_instr1(68, 0)
	execute_predicate('trace/0$0', 1)
end('trace'/0):



'xtrace'/0:


$1:
	allocate(0)
	call_predicate('nodebug', 0, 0)
	call_predicate('start_debug_thread_gui', 0, 0)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('trace')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	deallocate
	execute_predicate('$set_debugger_state', 1)
end('xtrace'/0):



'notrace'/0:


$1:
	execute_predicate('nodebug', 0)
end('notrace'/0):



'spy'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(50, 1)
	neck_cut
	put_constant('$spy_pred', 0)
	allocate(0)
	call_predicate('application', 2, 0)
	deallocate
	execute_predicate('debug', 0)

$2:
	allocate(0)
	call_predicate('$spy_pred', 1, 0)
	deallocate
	execute_predicate('debug', 0)
end('spy'/1):



'$spy_pred/1$0/3$0/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('$spypoint', 2)

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('assert', 1)
end('$spy_pred/1$0/3$0/2$0'/2):



'$spy_pred/1$0/3$0'/2:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$spy_pred/1$0/3$0/2$0', 2, 1)
	cut(0)
	deallocate
	proceed
end('$spy_pred/1$0/3$0'/2):



'$spy_pred/1$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('between', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$spy_pred/1$0/3$0', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$del_all_spy_conds', 2, 0)
	fail

$2:
	proceed
end('$spy_pred/1$0'/3):



'$spy_pred/1$1'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('$spypoint', 2)

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('assert', 1)
end('$spy_pred/1$1'/2):



'$spy_pred/1$2'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$spypoint', 2, 1)
	pseudo_instr1(1, 20)
	deallocate
	proceed

$2:
	get_x_variable(1, 0)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_x_value(1)
	set_void(1)
	execute_predicate('assert', 1)
end('$spy_pred/1$2'/1):



'$spy_pred'/1:

	switch_on_term(0, $11, $10, $10, $6, $10, $10)

$6:
	switch_on_structure(0, 8, ['$default':$10, '$'/0:$7, '-'/2:$8, '/'/2:$9])

$7:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(1, $1)
	retry($2)
	retry($4)
	trust($5)

$9:
	try(1, $1)
	retry($3)
	retry($4)
	trust($5)

$10:
	try(1, $1)
	retry($4)
	trust($5)

$11:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('spy')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('spy')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('spy')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure('-', 2, 0)
	unify_x_ref(0)
	unify_x_variable(1)
	get_structure('/', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$spy_pred/1$0', 3)

$3:
	get_structure('/', 2, 0)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_level(0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$spy_pred/1$1', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$del_all_spy_conds', 2, 1)
	cut(0)
	deallocate
	proceed

$4:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(2, 20)
	neck_cut
	call_predicate('$spy_pred/1$2', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$del_all_spy_conds', 1)

$5:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('spy')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('spy')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('spy')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('$spy_pred'/1):



'nospy'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(50, 1)
	neck_cut
	put_constant('$nospy_pred', 0)
	execute_predicate('application', 2)

$2:
	execute_predicate('$nospy_pred', 1)
end('nospy'/1):



'$nospy_pred/1$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('between', 3, 2)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_y_value(1)
	set_y_value(0)
	put_constant('true', 1)
	call_predicate('$retract', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$del_all_spy_conds', 2, 0)
	fail

$2:
	proceed
end('$nospy_pred/1$0'/3):



'$nospy_pred/1$1'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_x_value(2)
	set_x_value(1)
	put_constant('true', 1)
	execute_predicate('$retract', 2)

$2:
	proceed
end('$nospy_pred/1$1'/2):



'$nospy_pred/1$2'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_x_value(1)
	set_void(1)
	put_constant('true', 1)
	allocate(0)
	call_predicate('$retract', 2, 0)
	fail

$2:
	proceed
end('$nospy_pred/1$2'/1):



'$nospy_pred'/1:

	switch_on_term(0, $11, $10, $10, $6, $10, $10)

$6:
	switch_on_structure(0, 8, ['$default':$10, '$'/0:$7, '-'/2:$8, '/'/2:$9])

$7:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(1, $1)
	retry($2)
	retry($4)
	trust($5)

$9:
	try(1, $1)
	retry($3)
	retry($4)
	trust($5)

$10:
	try(1, $1)
	retry($4)
	trust($5)

$11:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('nospy')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('nospy')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('nospy')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure('-', 2, 0)
	unify_x_ref(0)
	unify_x_variable(1)
	get_structure('/', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	allocate(1)
	get_y_level(0)
	call_predicate('$nospy_pred/1$0', 3, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_structure('/', 2, 0)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_level(0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$nospy_pred/1$1', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$del_all_spy_conds', 2, 1)
	cut(0)
	deallocate
	proceed

$4:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(2, 20)
	neck_cut
	call_predicate('$nospy_pred/1$2', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$del_all_spy_conds', 1)

$5:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('nospy')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('nospy')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('nospy')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('$nospy_pred'/1):



'nospyall'/0:


$1:
	put_structure(2, 0)
	set_constant('$spypoint')
	set_void(2)
	allocate(0)
	call_predicate('retractall', 1, 0)
	put_structure(3, 0)
	set_constant('$spy_cond')
	set_void(3)
	deallocate
	execute_predicate('retractall', 1)
end('nospyall'/0):



'$read_spy_cond'/0:


$1:
	allocate(3)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('Goal? ')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 3)
	put_y_value(2, 0)
	put_structure(1, 2)
	set_constant('remember_name')
	set_constant('true')
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	call_predicate('read_debug_msg_term', 2, 3)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('Port? ')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 3)
	put_y_value(1, 0)
	put_structure(1, 2)
	set_constant('remember_name')
	set_constant('true')
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	call_predicate('read_debug_msg_term', 2, 3)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('Condition? ')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 3)
	put_y_value(0, 0)
	put_structure(1, 2)
	set_constant('remember_name')
	set_constant('true')
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	call_predicate('read_debug_msg_term', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('spy_cond', 3)
end('$read_spy_cond'/0):



'spy_cond/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('$spypoint')
	set_x_value(2)
	set_x_value(1)
	put_x_variable(1, 1)
	call_predicate('clause', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('$spy_pred', 1)
end('spy_cond/3$0'/2):



'spy_cond/3$1'/0:

	try(0, $1)
	trust($2)

$1:
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('off', 1)
	get_x_value(0, 1)
	neck_cut
	execute_predicate('debug', 0)

$2:
	proceed
end('spy_cond/3$1'/0):



'spy_cond'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	pseudo_instr1(46, 0)
	pseudo_instr1(46, 21)
	neck_cut
	pseudo_instr2(92, 0, 1)
	get_y_variable(0, 1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 20, 0, 1)
	call_predicate('spy_cond/3$0', 2, 3)
	call_predicate('spy_cond/3$1', 0, 3)
	put_structure(3, 0)
	set_constant('$spy_cond')
	set_y_value(0)
	set_y_value(2)
	set_y_value(1)
	deallocate
	execute_predicate('assert', 1)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('spy_cond')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('nonvar')
	put_structure(3, 4)
	set_constant('spy')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('spy_cond')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('nonvar')
	put_structure(3, 4)
	set_constant('spy')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)
end('spy_cond'/3):



'$del_all_spy_conds'/2:


$1:
	put_x_variable(2, 2)
	pseudo_instr3(0, 2, 0, 1)
	put_structure(3, 0)
	set_constant('$spy_cond')
	set_x_value(2)
	set_void(2)
	execute_predicate('retractall', 1)
end('$del_all_spy_conds'/2):



'$del_all_spy_conds'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(3, 0)
	put_structure(3, 0)
	set_constant('$spy_cond')
	set_y_variable(2)
	set_y_variable(1)
	set_y_variable(0)
	put_x_variable(1, 1)
	call_predicate('clause', 2, 4)
	put_x_variable(0, 0)
	pseudo_instr3(0, 22, 23, 0)
	put_structure(3, 0)
	set_constant('$spy_cond')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	call_predicate('retract', 1, 0)
	fail

$2:
	proceed
end('$del_all_spy_conds'/1):



'leash'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('leash')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('leash')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('leash')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$leash', 2, 2)
	cut(1)
	put_constant('$leashing', 0)
	pseudo_instr2(74, 0, 20)
	deallocate
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('leash')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('leash')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('leash')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('leash'/1):



'$leash/2$0'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$leash/2$0', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$leash_port', 3)
end('$leash/2$0'/3):



'$leash/2$1'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$leash/2$1', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$leash_port', 3)
end('$leash/2$1'/3):



'$leash/2$2'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$leash/2$2', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$leash_port', 3)
end('$leash/2$2'/3):



'$leash/2$3'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$leash/2$3', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$leash_port', 3)
end('$leash/2$3'/3):



'$leash/2$4'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$leash/2$4', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$leash_port', 3)
end('$leash/2$4'/3):



'$leash'/2:

	switch_on_term(0, $13, $6, $6, $6, $6, $7)

$7:
	switch_on_constant(0, 16, ['$default':$6, 'half':$8, 'full':$9, 'loose':$10, 'none':$11, 'tight':$12])

$8:
	try(2, $1)
	trust($6)

$9:
	try(2, $2)
	trust($6)

$10:
	try(2, $3)
	trust($6)

$11:
	try(2, $4)
	trust($6)

$12:
	try(2, $5)
	trust($6)

$13:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_constant('half', 0)
	get_x_variable(2, 1)
	neck_cut
	put_list(1)
	set_constant('redo')
	set_constant('[]')
	put_list(0)
	set_constant('call')
	set_x_value(1)
	put_integer(0, 1)
	execute_predicate('$leash/2$0', 3)

$2:
	get_constant('full', 0)
	get_x_variable(2, 1)
	neck_cut
	put_list(0)
	set_constant('exception')
	set_constant('[]')
	put_list(1)
	set_constant('fail')
	set_x_value(0)
	put_list(0)
	set_constant('redo')
	set_x_value(1)
	put_list(1)
	set_constant('exit')
	set_x_value(0)
	put_list(0)
	set_constant('call')
	set_x_value(1)
	put_integer(0, 1)
	execute_predicate('$leash/2$1', 3)

$3:
	get_constant('loose', 0)
	get_x_variable(2, 1)
	neck_cut
	put_list(0)
	set_constant('call')
	set_constant('[]')
	put_integer(0, 1)
	execute_predicate('$leash/2$2', 3)

$4:
	get_constant('none', 0)
	get_integer(0, 1)
	neck_cut
	proceed

$5:
	get_constant('tight', 0)
	get_x_variable(2, 1)
	neck_cut
	put_list(0)
	set_constant('exception')
	set_constant('[]')
	put_list(1)
	set_constant('fail')
	set_x_value(0)
	put_list(3)
	set_constant('redo')
	set_x_value(1)
	put_list(0)
	set_constant('call')
	set_x_value(3)
	put_integer(0, 1)
	execute_predicate('$leash/2$3', 3)

$6:
	get_x_variable(2, 1)
	pseudo_instr1(50, 0)
	put_integer(0, 1)
	execute_predicate('$leash/2$4', 3)
end('$leash'/2):



'$leash_port'/3:


$1:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	put_y_variable(1, 1)
	call_predicate('$leash_name', 2, 3)
	put_x_variable(1, 2)
	get_structure('\\/', 2, 2)
	unify_y_value(2)
	unify_y_value(1)
	pseudo_instr2(0, 0, 1)
	get_y_value(0, 0)
	deallocate
	proceed
end('$leash_port'/3):



'$leash_name'/2:

	switch_on_term(0, $7, 'fail', 'fail', 'fail', 'fail', $6)

$6:
	switch_on_constant(0, 16, ['$default':'fail', 'call':$1, 'exit':$2, 'redo':$3, 'fail':$4, 'exception':$5])

$7:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('call', 0)
	get_integer(8, 1)
	proceed

$2:
	get_constant('exit', 0)
	get_integer(4, 1)
	proceed

$3:
	get_constant('redo', 0)
	get_integer(2, 1)
	proceed

$4:
	get_constant('fail', 0)
	get_integer(1, 1)
	proceed

$5:
	get_constant('exception', 0)
	get_integer(16, 1)
	proceed
end('$leash_name'/2):



'with_debugging_off'/1:


$1:
	allocate(2)
	get_y_variable(1, 0)
	put_y_variable(0, 0)
	call_predicate('$get_debugger_state', 1, 2)
	put_structure(6, 0)
	set_constant('$debug_state')
	set_constant('off')
	set_integer(31)
	set_integer(0)
	set_constant('[]')
	set_integer(10)
	set_integer(0)
	call_predicate('$set_debugger_state', 1, 2)
	put_y_value(1, 0)
	call_predicate('call', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$set_debugger_state', 1)
end('with_debugging_off'/1):



'$debug_call/1$0/4$0/2$0/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('true', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('$call_2', 2)
end('$debug_call/1$0/4$0/2$0/1$0'/2):



'$debug_call/1$0/4$0/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_level(3)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	call_predicate('is_dynamic_call', 1, 4)
	cut(3)
	pseudo_instr1(7, 0)
	get_y_value(1, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('clause', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$debug_call/1$0/4$0/2$0/1$0', 2)

$2:
	execute_predicate('call_predicate', 1)
end('$debug_call/1$0/4$0/2$0'/1):



'$debug_call/1$0/4$0/2$1/2$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'ctrlC_reset':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('ctrlC_reset', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_x_variable(0, 1)
	put_constant('throw', 1)
	execute_predicate('$print_port', 2)
end('$debug_call/1$0/4$0/2$1/2$0'/2):



'$debug_call/1$0/4$0/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_structure(2, 0)
	set_constant('$throw_pattern')
	set_x_value(2)
	set_y_variable(0)
	put_constant('true', 1)
	call_predicate('clause', 2, 3)
	cut(2)
	call_predicate('$skip_complete', 0, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('$debug_call/1$0/4$0/2$1/2$0', 2, 0)
	put_constant('$debug_id', 1)
	pseudo_instr2(76, 1, 0)
	put_constant('$skip_retry_fail', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	pseudo_instr0(1)
	deallocate
	proceed

$2:
	proceed
end('$debug_call/1$0/4$0/2$1'/2):



'$debug_call/1$0/4$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr0(0)
	pseudo_instr1(21, 1)
	get_y_variable(0, 1)
	call_predicate('$debug_call/1$0/4$0/2$0', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$exit_catch', 2)

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(2, 1)
	put_y_variable(0, 0)
	call_predicate('thread_symbol', 1, 3)
	pseudo_instr1(22, 22)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('$debug_call/1$0/4$0/2$1', 2, 0)
	fail
end('$debug_call/1$0/4$0'/2):



'$debug_call/1$0/4$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 1)
	call_predicate('$fail_back', 1, 1)
	call_predicate('$skip_complete', 0, 1)
	put_y_value(0, 0)
	put_constant('fail', 1)
	deallocate
	execute_predicate('$print_port', 2)

$2:
	proceed
end('$debug_call/1$0/4$1'/2):



'$debug_call/1$0'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_variable(0, 2)
	put_constant('$debug_path', 1)
	pseudo_instr2(3, 1, 4)
	call_predicate('$retry_from_this', 1, 1)
	put_y_value(0, 0)
	put_constant('call', 1)
	call_predicate('$print_port', 2, 1)
	pseudo_instr1(21, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$debug_call/1$0/4$0', 2)

$2:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(1)
	get_y_variable(0, 3)
	call_predicate('$debug_call/1$0/4$1', 2, 1)
	cut(0)
	put_constant('$debug_id', 1)
	pseudo_instr2(76, 1, 0)
	fail
end('$debug_call/1$0'/4):



'$debug_call/1$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	call_predicate('$skip_complete', 0, 2)
	put_y_value(1, 0)
	put_constant('exit', 1)
	call_predicate('$print_port', 2, 1)
	put_constant('$debug_path', 0)
	pseudo_instr2(3, 0, 20)
	deallocate
	proceed

$2:
	put_constant('$skip_retry_fail', 2)
	pseudo_instr2(73, 2, 1)
	put_integer(0, 2)
	get_x_value(1, 2)
	put_constant('redo', 1)
	allocate(0)
	call_predicate('$print_port', 2, 0)
	fail
end('$debug_call/1$1'/2):



'$debug_call'/1:


$1:
	allocate(6)
	get_y_variable(4, 0)
	get_y_level(3)
	put_constant('$debug_id', 1)
	pseudo_instr2(75, 1, 0)
	get_y_variable(2, 0)
	put_constant('$debug_path', 1)
	pseudo_instr2(4, 1, 0)
	get_y_variable(1, 0)
	put_y_variable(0, 19)
	put_y_variable(5, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 6)
	pseudo_instr2(69, 25, 0)
	get_x_variable(1, 0)
	pseudo_instr2(92, 24, 0)
	get_y_value(0, 0)
	put_x_variable(0, 2)
	get_list(2)
	unify_x_ref(2)
	unify_y_value(1)
	get_structure('goal', 3, 2)
	unify_y_value(2)
	unify_x_value(1)
	unify_y_value(0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	call_predicate('$debug_call/1$0', 4, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$debug_call/1$1', 2)
end('$debug_call'/1):



'$print_port/2$0/4$0/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$check_spy_conds', 4, 1)
	cut(0)
	fail

$2:
	proceed
end('$print_port/2$0/4$0/4$0'/4):



'$print_port/2$0/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$print_port/2$0/4$0/4$0', 4, 1)
	cut(0)
	fail

$2:
	proceed
end('$print_port/2$0/4$0'/4):



'$print_port/2$0'/4:

	try(4, $1)
	trust($2)

$1:
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('trace', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('debug', 1)
	get_x_value(0, 1)
	neck_cut
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$spypoint', 2, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$print_port/2$0/4$0', 4)
end('$print_port/2$0'/4):



'$print_port'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	pseudo_instr3(0, 21, 24, 23)
	get_y_level(2)
	put_y_value(4, 0)
	call_predicate('$debug_internal', 1, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	call_predicate('$print_port/2$0', 4, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$2:
	proceed
end('$print_port'/2):



'$check_spy_conds/4$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$spy_cond', 3, 1)
	cut(0)
	fail

$2:
	proceed
end('$check_spy_conds/4$0'/1):



'$check_spy_conds/4$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('call_predicate', 1, 2)
	cut(1)
	put_constant('$debugger_status', 0)
	pseudo_instr2(74, 0, 20)
	deallocate
	proceed

$2:
	put_constant('$debugger_status', 0)
	pseudo_instr2(74, 0, 1)
	fail
end('$check_spy_conds/4$1'/2):



'$check_spy_conds'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 4, 1)
	execute_predicate('$check_spy_conds/4$0', 1)

$2:
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 2)
	call_predicate('$spy_cond', 3, 2)
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(1, 0)
	put_constant('$debugger_status', 0)
	put_constant('off', 2)
	pseudo_instr2(74, 0, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$check_spy_conds/4$1', 2)
end('$check_spy_conds'/4):



'$trace_interact/4$0'/7:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'yes':$4])

$4:
	try(7, $1)
	trust($2)

$5:
	try(7, $1)
	trust($2)

$1:
	allocate(8)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(1, 6)
	put_constant('yes', 1)
	get_x_value(0, 1)
	get_y_level(4)
	put_y_variable(0, 19)
	put_structure(4, 0)
	set_constant('debugger_hook')
	set_void(4)
	put_x_variable(1, 1)
	call_predicate('predicate_property', 2, 8)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_structure(5, 2)
	set_constant('debug_state')
	set_y_value(7)
	set_y_value(6)
	set_y_value(5)
	set_void(1)
	set_y_value(1)
	put_y_value(0, 3)
	call_predicate('$check_port_hook', 4, 5)
	cut(4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_constant('debugger_hook', 4)
	put_integer(4, 5)
	deallocate
	execute_predicate('$trace_action', 6)

$2:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_x_variable(2, 6)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$print_trace', 6, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$debug_interact', 3)
end('$trace_interact/4$0'/7):



'$trace_interact'/4:


$1:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 24, 0, 1)
	put_y_variable(0, 2)
	call_predicate('$check_spied', 3, 5)
	put_constant('$debug_path', 1)
	pseudo_instr2(4, 1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('goal', 3, 0)
	unify_x_variable(4)
	unify_x_variable(5)
	unify_void(1)
	put_y_value(1, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	put_y_value(2, 6)
	deallocate
	execute_predicate('$trace_interact/4$0', 7)
end('$trace_interact'/4):



'$check_port_hook/4$0'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 4)
	get_y_level(1)
	call_predicate('debugger_hook', 4, 2)
	cut(1)
	put_constant('$debugger_status', 0)
	pseudo_instr2(74, 0, 20)
	deallocate
	proceed

$2:
	put_constant('$debugger_status', 0)
	pseudo_instr2(74, 0, 4)
	fail
end('$check_port_hook/4$0'/5):



'$check_port_hook'/4:


$1:
	put_constant('$debugger_status', 5)
	pseudo_instr2(73, 5, 4)
	put_constant('$debugger_status', 5)
	put_constant('off', 6)
	pseudo_instr2(74, 5, 6)
	execute_predicate('$check_port_hook/4$0', 5)
end('$check_port_hook'/4):



'$trace_action'/6:

	switch_on_term(0, $11, $5, $5, $5, $5, $6)

$6:
	switch_on_constant(0, 8, ['$default':$5, 'interact':$7, 'creep':$8, 'continue':$9, 'fail':$10])

$7:
	try(6, $1)
	trust($5)

$8:
	try(6, $2)
	trust($5)

$9:
	try(6, $3)
	trust($5)

$10:
	try(6, $4)
	trust($5)

$11:
	try(6, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('interact', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	neck_cut
	put_constant('no', 3)
	execute_predicate('$trace_interact', 4)

$2:
	get_constant('creep', 0)
	neck_cut
	execute_predicate('$debug_creep', 0)

$3:
	get_constant('continue', 0)
	neck_cut
	proceed

$4:
	get_constant('fail', 0)
	neck_cut
	put_constant('$debug_id', 1)
	pseudo_instr2(73, 1, 0)
	put_x_variable(2, 3)
	get_structure('-', 1, 3)
	unify_x_value(0)
	pseudo_instr2(0, 1, 2)
	get_x_variable(0, 1)
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(74, 1, 0)
	fail

$5:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_list(0)
	set_constant('fail')
	set_constant('[]')
	put_list(1)
	set_constant('continue')
	set_x_value(0)
	put_list(0)
	set_constant('creep')
	set_x_value(1)
	put_list(1)
	set_constant('interact')
	set_x_value(0)
	put_structure(5, 0)
	set_constant('range_error')
	set_constant('recoverable')
	set_x_value(4)
	set_constant('default')
	set_x_value(5)
	set_x_value(1)
	call_predicate('exception', 1, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)
end('$trace_action'/6):



'$print_trace/6$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'spy':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('spy', 1)
	get_x_value(0, 1)
	neck_cut
	put_structure(1, 1)
	set_constant('wa')
	set_constant('+')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	execute_predicate('write_debug_msg_term_list', 1)

$2:
	put_list(0)
	set_constant('sp')
	set_constant('[]')
	execute_predicate('write_debug_msg_term_list', 1)
end('$print_trace/6$0'/1):



'$print_trace/6$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_structure(1, 0)
	set_constant('max_depth')
	set_void(1)
	put_y_value(1, 1)
	call_predicate('member', 2, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('write_debug_msg_term', 2)

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('$debug_print', 3)
	pseudo_instr2(73, 3, 1)
	put_structure(1, 3)
	set_constant('max_depth')
	set_x_value(1)
	put_list(1)
	set_x_value(3)
	set_x_value(2)
	execute_predicate('write_debug_msg_term', 2)
end('$print_trace/6$1'/2):



'$print_trace'/6:


$1:
	allocate(5)
	get_y_variable(1, 0)
	get_y_variable(4, 1)
	get_y_variable(0, 2)
	get_x_variable(0, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	call_predicate('$print_trace/6$0', 1, 5)
	put_structure(1, 0)
	set_constant('wa')
	set_constant(': ')
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 0)
	set_constant('wa')
	set_y_value(4)
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_structure(1, 0)
	set_constant('wa')
	set_constant('    ')
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_structure(1, 0)
	set_constant('wi')
	set_y_value(2)
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_structure(1, 0)
	set_constant('wa')
	set_constant('    ')
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_structure(1, 0)
	set_constant('wi')
	set_y_value(3)
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_list(0)
	set_constant('sp')
	set_x_value(2)
	call_predicate('write_debug_msg_term_list', 1, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$print_trace/6$1', 2)
end('$print_trace'/6):



'$debug_internal'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('$trace_internal', 2)
	put_integer(0, 3)
	pseudo_instr3(33, 2, 3, 1)
	put_integer(0, 2)
	get_x_value(1, 2)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$debug_internal'/1):



'$check_spied'/3:

	try(3, $1)
	trust($2)

$1:
	get_constant('spy', 2)
	allocate(1)
	get_y_level(0)
	call_predicate('$spypoint', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_constant('nospy', 2)
	proceed
end('$check_spied'/3):



'$debug_interact'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_level(4)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	call_predicate('$is_interact', 2, 5)
	cut(4)
	put_structure(1, 1)
	set_constant('wa')
	set_constant(' ? ')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 4)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$get_debug_command', 2, 4)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$execute_debug_command', 4)

$2:
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	execute_predicate('write_debug_msg_term_list', 1)
end('$debug_interact'/3):



'$is_interact'/2:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'spy':$1, 'nospy':$2])

$4:
	try(2, $1)
	trust($2)

$1:
	get_constant('spy', 0)
	neck_cut
	proceed

$2:
	get_constant('nospy', 0)
	get_x_variable(0, 1)
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$leash_name', 2, 1)
	put_constant('$leashing', 1)
	pseudo_instr2(73, 1, 0)
	put_x_variable(2, 3)
	get_structure('/\\', 2, 3)
	unify_x_value(0)
	unify_y_value(0)
	pseudo_instr2(0, 1, 2)
	get_y_value(0, 1)
	deallocate
	proceed
end('$is_interact'/2):



'$get_debug_command/2$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 10:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_integer(10, 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_x_variable(0, 1)
	allocate(3)
	get_y_variable(1, 2)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	call_predicate('$skip_space', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$get_argument', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('name', 2)
end('$get_debug_command/2$0'/3):



'$get_debug_command'/2:


$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_y_variable(2, 0)
	call_predicate('read_debug_msg_codes', 1, 3)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(1)
	unify_x_variable(1)
	put_y_value(1, 0)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$get_debug_command/2$0', 3)
end('$get_debug_command'/2):



'$skip_space/2$0'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 32:$1, 9:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_integer(32, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(9, 1)
	get_x_value(0, 1)
	proceed
end('$skip_space/2$0'/1):



'$skip_space'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('$skip_space/2$0', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$skip_space', 2)

$2:
	get_x_value(0, 1)
	proceed
end('$skip_space'/2):



'$get_argument/2$0'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 32:$1, 9:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_integer(32, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(9, 1)
	get_x_value(0, 1)
	proceed
end('$get_argument/2$0'/1):



'$get_argument'/2:

	switch_on_term(0, $4, 'fail', $4, 'fail', 'fail', 'fail')

$4:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	get_list(0)
	unify_integer(10)
	unify_void(1)
	neck_cut
	proceed

$2:
	get_constant('[]', 1)
	get_list(0)
	unify_x_variable(0)
	unify_void(1)
	allocate(1)
	get_y_level(0)
	call_predicate('$get_argument/2$0', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$get_argument', 2)
end('$get_argument'/2):



'$execute_debug_command/4$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_constant('', 3)
	get_x_value(0, 3)
	neck_cut
	put_structure(2, 0)
	set_constant('/')
	set_x_value(1)
	set_x_value(2)
	execute_predicate('$spy_pred', 1)

$2:
	execute_predicate('$read_spy_cond', 0)
end('$execute_debug_command/4$0'/3):



'$execute_debug_command/4$1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call_predicate', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	proceed
end('$execute_debug_command/4$1'/1):



'$execute_debug_command/4$2'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('', 1)
	get_x_value(0, 1)
	neck_cut
	put_constant('$debug_print', 0)
	put_integer(10, 1)
	pseudo_instr2(74, 0, 1)
	proceed

$2:
	put_constant('$debug_print', 1)
	pseudo_instr2(74, 1, 0)
	proceed
end('$execute_debug_command/4$2'/1):



'$execute_debug_command/4$3'/2:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, '':$5])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $2)
	trust($3)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	put_constant('', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('$debug_id', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr1(3, 0)
	put_integer(0, 2)
	pseudo_instr2(1, 2, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$3:
	put_list(1)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('invocation must be a positive integer')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	allocate(0)
	call_predicate('write_debug_msg_term_list', 1, 0)
	fail
end('$execute_debug_command/4$3'/2):



'$execute_debug_command/4$4'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('', 1)
	get_x_value(2, 1)
	neck_cut
	put_integer(-1, 1)
	execute_predicate('$print_ancestor', 2)

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_value(2, 1)
	execute_predicate('$print_ancestor', 2)
end('$execute_debug_command/4$4'/2):



'$execute_debug_command/4$5'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	put_constant('', 2)
	get_x_value(3, 2)
	neck_cut
	put_constant('[]', 2)
	put_constant('yes', 3)
	execute_predicate('$trace_interact', 4)

$2:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	put_structure(1, 4)
	set_constant('max_depth')
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_constant('yes', 3)
	execute_predicate('$trace_interact', 4)
end('$execute_debug_command/4$5'/3):



'$execute_debug_command/4$6'/2:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, '':$5])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $2)
	trust($3)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	put_constant('', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('$debug_id', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr1(3, 0)
	put_integer(0, 2)
	pseudo_instr2(1, 2, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$3:
	put_list(1)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('invocation must be a positive integer')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	allocate(0)
	call_predicate('write_debug_msg_term_list', 1, 0)
	fail
end('$execute_debug_command/4$6'/2):



'$execute_debug_command/4$7/2$0'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'fail':$1, 'exit':$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_constant('fail', 1)
	get_x_value(0, 1)
	proceed

$2:
	put_constant('exit', 1)
	get_x_value(0, 1)
	proceed
end('$execute_debug_command/4$7/2$0'/1):



'$execute_debug_command/4$7'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('$execute_debug_command/4$7/2$0', 1, 3)
	cut(2)
	put_list(1)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('skip is unavailable at this port')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	call_predicate('write_debug_msg_term_list', 1, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$2:
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(74, 1, 0)
	put_constant('$debugger_status', 0)
	put_constant('off', 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('$execute_debug_command/4$7'/2):



'$execute_debug_command'/4:

	switch_on_term(0, $45, $44, $44, $44, $44, $23)

$23:
	switch_on_constant(0, 64, ['$default':$44, 10:$24, 61:$25, 43:$26, 45:$27, 64:$28, 60:$29, 63:$30, 97:$31, 98:$32, 99:$33, 100:$34, 102:$35, 103:$36, 104:$37, 108:$38, 110:$39, 112:$40, 114:$41, 115:$42, 119:$43])

$24:
	try(4, $1)
	retry($2)
	trust($22)

$25:
	try(4, $1)
	retry($3)
	trust($22)

$26:
	try(4, $1)
	retry($4)
	trust($22)

$27:
	try(4, $1)
	retry($5)
	trust($22)

$28:
	try(4, $1)
	retry($6)
	trust($22)

$29:
	try(4, $1)
	retry($7)
	trust($22)

$30:
	try(4, $1)
	retry($8)
	trust($22)

$31:
	try(4, $1)
	retry($9)
	trust($22)

$32:
	try(4, $1)
	retry($10)
	trust($22)

$33:
	try(4, $1)
	retry($11)
	trust($22)

$34:
	try(4, $1)
	retry($12)
	trust($22)

$35:
	try(4, $1)
	retry($13)
	trust($22)

$36:
	try(4, $1)
	retry($14)
	trust($22)

$37:
	try(4, $1)
	retry($15)
	trust($22)

$38:
	try(4, $1)
	retry($16)
	trust($22)

$39:
	try(4, $1)
	retry($17)
	trust($22)

$40:
	try(4, $1)
	retry($18)
	trust($22)

$41:
	try(4, $1)
	retry($19)
	trust($22)

$42:
	try(4, $1)
	retry($20)
	trust($22)

$43:
	try(4, $1)
	retry($21)
	trust($22)

$44:
	try(4, $1)
	trust($22)

$45:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	retry($13)
	retry($14)
	retry($15)
	retry($16)
	retry($17)
	retry($18)
	retry($19)
	retry($20)
	retry($21)
	trust($22)

$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_level(3)
	put_y_variable(0, 19)
	put_structure(5, 0)
	set_constant('debugger_cmd_hook')
	set_void(5)
	put_x_variable(1, 1)
	call_predicate('predicate_property', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	call_predicate('$check_cmd_hook', 5, 4)
	cut(3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_constant('[]', 3)
	put_constant('debugger_cmd_hook', 4)
	put_integer(5, 5)
	deallocate
	execute_predicate('$trace_action', 6)

$2:
	get_integer(10, 0)
	neck_cut
	execute_predicate('$debug_creep', 0)

$3:
	get_integer(61, 0)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	call_predicate('debugging', 0, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$4:
	get_integer(43, 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	pseudo_instr3(0, 21, 1, 2)
	call_predicate('$execute_debug_command/4$0', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$5:
	get_integer(45, 0)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	pseudo_instr3(0, 21, 1, 2)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(1)
	set_x_value(2)
	call_predicate('$nospy_pred', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$6:
	get_integer(64, 0)
	allocate(7)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	get_y_level(2)
	put_y_variable(6, 19)
	put_y_variable(5, 0)
	put_y_variable(4, 1)
	put_y_variable(3, 2)
	call_predicate('$get_basic_debugger_state', 3, 7)
	put_integer(0, 0)
	put_constant('[]', 1)
	put_integer(0, 2)
	call_predicate('$set_basic_debugger_state', 3, 7)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('| :- ')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	call_predicate('write_debug_msg_term_list', 1, 7)
	put_y_value(6, 0)
	put_structure(1, 2)
	set_constant('remember_name')
	set_constant('true')
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	call_predicate('read_debug_msg_term', 2, 7)
	put_y_value(6, 0)
	call_predicate('$execute_debug_command/4$1', 1, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('$set_basic_debugger_state', 3, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$7:
	get_integer(60, 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	call_predicate('$execute_debug_command/4$2', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$8:
	get_integer(63, 0)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	call_predicate('$debug_help', 0, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$9:
	get_integer(97, 0)
	neck_cut
	put_constant('$debugger_status', 0)
	put_constant('off', 1)
	pseudo_instr2(74, 0, 1)
	execute_predicate('abort', 0)

$10:
	get_integer(98, 0)
	allocate(5)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	put_y_variable(4, 0)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$get_basic_debugger_state', 3, 5)
	put_integer(0, 0)
	put_constant('[]', 1)
	put_integer(0, 2)
	call_predicate('$set_basic_debugger_state', 3, 5)
	call_predicate('break', 0, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	call_predicate('$set_basic_debugger_state', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$11:
	get_integer(99, 0)
	neck_cut
	execute_predicate('$debug_creep', 0)

$12:
	get_integer(100, 0)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	neck_cut
	put_structure(1, 3)
	set_constant('ignore_ops')
	set_constant('true')
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_constant('yes', 3)
	execute_predicate('$trace_interact', 4)

$13:
	get_integer(102, 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$execute_debug_command/4$3', 2, 2)
	cut(1)
	put_x_variable(1, 2)
	get_structure('-', 1, 2)
	unify_y_value(0)
	pseudo_instr2(0, 0, 1)
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(74, 1, 0)
	fail

$14:
	get_integer(103, 0)
	allocate(4)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	put_y_variable(2, 0)
	call_predicate('$ancestor', 1, 4)
	put_list(1)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 2)
	set_constant('wa')
	set_constant('Ancestors:')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	call_predicate('write_debug_msg_term_list', 1, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$execute_debug_command/4$4', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$15:
	get_integer(104, 0)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	call_predicate('$debug_help', 0, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)

$16:
	get_integer(108, 0)
	neck_cut
	put_constant('$debugger_status', 0)
	put_constant('debug', 1)
	pseudo_instr2(74, 0, 1)
	proceed

$17:
	get_integer(110, 0)
	neck_cut
	execute_predicate('nodebug', 0)

$18:
	get_integer(112, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	neck_cut
	execute_predicate('$execute_debug_command/4$5', 3)

$19:
	get_integer(114, 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$execute_debug_command/4$6', 2, 2)
	cut(1)
	put_constant('$skip_retry_fail', 0)
	pseudo_instr2(74, 0, 20)
	fail

$20:
	get_integer(115, 0)
	get_x_variable(1, 2)
	get_x_variable(0, 3)
	neck_cut
	execute_predicate('$execute_debug_command/4$7', 2)

$21:
	get_integer(119, 0)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	neck_cut
	put_constant('[]', 2)
	put_constant('yes', 3)
	execute_predicate('$trace_interact', 4)

$22:
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_list(2)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 3)
	set_constant('wa')
	set_constant(' is an illegal command sequence')
	put_list(4)
	set_x_value(3)
	set_x_value(2)
	put_structure(1, 2)
	set_constant('w')
	set_x_value(1)
	put_list(1)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_constant('sp')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('w')
	set_x_value(0)
	put_list(0)
	set_x_value(1)
	set_x_value(2)
	call_predicate('write_debug_msg_term_list', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	put_constant('yes', 3)
	deallocate
	execute_predicate('$trace_interact', 4)
end('$execute_debug_command'/4):



'$check_cmd_hook/5$0'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 5)
	get_y_level(1)
	call_predicate('debugger_cmd_hook', 5, 2)
	cut(1)
	put_constant('$debugger_status', 0)
	pseudo_instr2(74, 0, 20)
	deallocate
	proceed

$2:
	put_constant('$debugger_status', 0)
	pseudo_instr2(74, 0, 5)
	fail
end('$check_cmd_hook/5$0'/6):



'$check_cmd_hook'/5:


$1:
	put_constant('$debugger_status', 6)
	pseudo_instr2(73, 6, 5)
	put_constant('$debugger_status', 6)
	put_constant('off', 7)
	pseudo_instr2(74, 6, 7)
	execute_predicate('$check_cmd_hook/5$0', 6)
end('$check_cmd_hook'/5):



'$debug_creep'/0:

	try(0, $1)
	trust($2)

$1:
	put_constant('$debugger_status', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('debug', 1)
	get_x_value(0, 1)
	neck_cut
	put_constant('$debugger_status', 0)
	put_constant('trace', 1)
	pseudo_instr2(74, 0, 1)
	proceed

$2:
	proceed
end('$debug_creep'/0):



'$ancestor'/1:


$1:
	put_constant('$debug_path', 2)
	pseudo_instr2(4, 2, 1)
	get_list(1)
	unify_void(1)
	unify_x_value(0)
	proceed
end('$ancestor'/1):



'$print_ancestor'/2:

	switch_on_term(0, $7, $2, $4, $2, $2, $5)

$4:
	try(2, $2)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$2, '[]':$6])

$6:
	try(2, $1)
	trust($2)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_integer(0, 1)
	neck_cut
	proceed

$3:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('goal', 3, 2)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr2(70, 1, 2)
	get_x_variable(1, 2)
	call_predicate('$print_ancestor', 2, 3)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 20, 0, 1)
	put_x_variable(2, 2)
	call_predicate('$print_spy_indicator', 3, 3)
	put_structure(1, 0)
	set_constant('wa')
	set_constant('    ')
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 0)
	set_constant('wi')
	set_y_value(1)
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_structure(1, 0)
	set_constant('wa')
	set_constant('    ')
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_structure(1, 0)
	set_constant('wi')
	set_y_value(2)
	put_list(2)
	set_x_value(0)
	set_x_value(1)
	put_list(0)
	set_constant('sp')
	set_x_value(2)
	call_predicate('write_debug_msg_term_list', 1, 3)
	put_constant(' ', 0)
	call_predicate('$stdout_atom', 1, 3)
	put_y_value(2, 0)
	call_predicate('$stdout_int', 1, 2)
	put_constant('    ', 0)
	call_predicate('$stdout_atom', 1, 2)
	put_y_value(1, 0)
	call_predicate('$stdout_int', 1, 1)
	put_constant('    ', 0)
	call_predicate('$stdout_atom', 1, 1)
	put_constant('$debug_print', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	put_structure(1, 2)
	set_constant('max_depth')
	set_x_value(1)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	call_predicate('write_debug_msg_term', 2, 0)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	deallocate
	execute_predicate('write_debug_msg_term_list', 1)
end('$print_ancestor'/2):



'$print_spy_indicator/3$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'spy':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('spy', 1)
	get_x_value(0, 1)
	neck_cut
	put_structure(1, 1)
	set_constant('wa')
	set_constant('+')
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	execute_predicate('write_debug_msg_term_list', 1)

$2:
	put_list(0)
	set_constant('sp')
	set_constant('[]')
	execute_predicate('write_debug_msg_term_list', 1)
end('$print_spy_indicator/3$0'/1):



'$print_spy_indicator'/3:


$1:
	allocate(1)
	get_y_variable(0, 2)
	call_predicate('$check_spied', 3, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$print_spy_indicator/3$0', 1)
end('$print_spy_indicator'/3):



'$debug_help'/0:


$1:
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('wa')
	set_constant('?   help        h   help')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('a   abort')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('@   command     b   break')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('=   debugging   n   nodebug')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('+   spy         -   nospy')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('g   all ancestors   g N N-th ancestor')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('p   print       p N print with depth=N')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('d   display     w   write')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('<   printdepth=10   < N printdepth=N')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('r   retry       r ID    retry at ID')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('f   fail        f ID    fail to ID')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('l   leap        s   skip')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('wa')
	set_constant('RETURN  creep       c   creep')
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('nl')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('wa')
	set_constant('Available commands:')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	execute_predicate('write_debug_msg_term_list', 1)
end('$debug_help'/0):



'$skip_complete/0$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	put_constant('$skip_retry_fail', 1)
	put_integer(0, 2)
	pseudo_instr2(74, 1, 2)
	put_constant('$debugger_status', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$2:
	proceed
end('$skip_complete/0$0'/1):



'$skip_complete'/0:


$1:
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(73, 1, 0)
	execute_predicate('$skip_complete/0$0', 1)
end('$skip_complete'/0):



'$fail_back/1$0'/1:

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
	put_integer(0, 1)
	get_x_value(0, 1)
	proceed

$2:
	pseudo_instr1(2, 0)
	proceed
end('$fail_back/1$0'/1):



'$fail_back'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('$skip_retry_fail', 2)
	pseudo_instr2(73, 2, 1)
	pseudo_instr1(3, 1)
	put_integer(0, 2)
	pseudo_instr2(1, 1, 2)
	neck_cut
	put_x_variable(3, 4)
	get_structure('-', 1, 4)
	unify_x_value(1)
	pseudo_instr2(0, 2, 3)
	get_x_variable(1, 2)
	pseudo_instr2(2, 0, 1)
	put_constant('$skip_retry_fail', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	proceed

$2:
	put_constant('$skip_retry_fail', 1)
	pseudo_instr2(73, 1, 0)
	allocate(1)
	get_y_level(0)
	call_predicate('$fail_back/1$0', 1, 1)
	cut(0)
	deallocate
	proceed
end('$fail_back'/1):



'$retry_from_this'/1:

	try(1, $1)
	trust($2)

$1:
	proceed

$2:
	put_constant('$skip_retry_fail', 2)
	pseudo_instr2(73, 2, 1)
	pseudo_instr1(3, 1)
	put_integer(0, 2)
	pseudo_instr2(1, 2, 1)
	get_x_value(1, 0)
	put_constant('$skip_retry_fail', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('$retry_from_this'/1):



'$retry_from_child'/1:

	try(1, $1)
	trust($2)

$1:
	proceed

$2:
	put_constant('$skip_retry_fail', 2)
	pseudo_instr2(73, 2, 1)
	pseudo_instr1(3, 1)
	put_integer(0, 2)
	pseudo_instr2(1, 2, 1)
	pseudo_instr2(1, 0, 1)
	put_constant('$skip_retry_fail', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('$retry_from_child'/1):



