'$init_interpreter'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('$thread_gui_set')
	set_integer(1)
	allocate(0)
	call_predicate('dynamic', 1, 0)
	put_constant('$indent_level', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	put_constant('$break_level', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	put_constant('$prompt', 0)
	put_constant('| ?- ', 1)
	pseudo_instr2(74, 0, 1)
	deallocate
	proceed
end('$init_interpreter'/0):



'interpreter'/0:


$1:
	put_constant('[]', 0)
	execute_predicate('$interpreter', 1)
end('interpreter'/0):



'$interpreter/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('[]', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$interpreter/1$0'/1):



'$interpreter'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(2, 0)
	put_constant('$locally_handled_exceptions', 1)
	pseudo_instr2(4, 1, 0)
	get_y_variable(1, 0)
	get_y_level(0)
	call_predicate('$interpreter/1$0', 1, 3)
	put_constant('$locally_handled_exceptions', 0)
	put_x_variable(1, 2)
	get_list(2)
	unify_x_ref(2)
	unify_y_value(1)
	get_structure('abort', 3, 2)
	unify_void(3)
	pseudo_instr2(3, 0, 1)
	put_structure(1, 0)
	set_constant('$fetch_execute')
	set_y_value(2)
	put_x_variable(3, 1)
	put_structure(1, 2)
	set_constant('$interpreter_catch')
	set_x_value(3)
	call_predicate('catch', 3, 2)
	put_constant('$locally_handled_exceptions', 0)
	pseudo_instr2(3, 0, 21)
	cut(0)
	deallocate
	proceed

$2:
	execute_predicate('$interpreter', 1)
end('$interpreter'/1):



'$fetch_execute/1$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(0)
	call_predicate('$exit_interpreter', 1, 0)
	deallocate
	execute_predicate('exit_debug_thread_gui', 0)

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('union_list', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$solve_query', 2)
end('$fetch_execute/1$0'/3):



'$fetch_execute'/1:


$1:
	allocate(6)
	get_y_variable(3, 0)
	put_constant('$prompt', 1)
	pseudo_instr2(73, 1, 0)
	get_y_variable(5, 0)
	get_y_level(0)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	call_predicate('repeat', 0, 6)
	pseudo_instr1(28, 0)
	get_y_value(4, 0)
	put_y_value(4, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('write_atom', 2, 4)
	call_predicate('flush_output', 0, 4)
	put_constant('$in_interpreter_query', 0)
	put_constant('true', 1)
	pseudo_instr2(3, 0, 1)
	put_y_value(2, 0)
	put_structure(1, 1)
	set_constant('remember_name')
	set_constant('true')
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 3)
	set_constant('variable_names')
	set_y_value(1)
	put_list(1)
	set_x_value(3)
	set_x_value(2)
	call_predicate('read_term', 2, 4)
	put_constant('$in_interpreter_query', 0)
	put_constant('fail', 1)
	pseudo_instr2(3, 0, 1)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	call_predicate('$fetch_execute/1$0', 3, 1)
	cut(0)
	deallocate
	proceed
end('$fetch_execute'/1):



'$redo_prompt'/0:

	try(0, $1)
	trust($2)

$1:
	put_constant('$in_interpreter_query', 1)
	pseudo_instr2(4, 1, 0)
	put_constant('true', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	put_constant('$prompt', 1)
	pseudo_instr2(73, 1, 0)
	allocate(2)
	get_y_variable(1, 0)
	pseudo_instr1(28, 0)
	get_y_variable(0, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 0)
	deallocate
	execute_predicate('flush_output', 0)

$2:
	proceed
end('$redo_prompt'/0):



'$interpreter_catch'/1:


$1:
	allocate(0)
	call_predicate('$interpreter_catch_msg', 1, 0)
	fail
end('$interpreter_catch'/1):



'$interpreter_catch_msg'/1:

	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	pseudo_instr1(46, 0)
	get_structure('$exception', 1, 0)
	unify_x_ref(0)
	get_structure('abort', 3, 0)
	unify_void(2)
	unify_x_ref(0)
	get_list(0)
	unify_x_variable(1)
	unify_constant('[]')
	neck_cut
	put_constant('stderr', 0)
	allocate(0)
	call_predicate('write_atom', 2, 0)
	put_constant('stderr', 0)
	put_constant('
', 1)
	deallocate
	execute_predicate('write_atom', 2)

$2:
	pseudo_instr1(46, 0)
	get_structure('exception', 1, 0)
	unify_x_ref(0)
	get_structure('undefined_predicate', 3, 0)
	unify_void(1)
	unify_x_variable(0)
	unify_void(1)
	allocate(2)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	pseudo_instr3(0, 0, 21, 20)
	neck_cut
	put_constant('stderr', 0)
	put_constant('no definition for ', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 1)
	put_constant('stderr', 0)
	call_predicate('write_atom', 2, 1)
	put_constant('stderr', 0)
	put_constant('/', 1)
	call_predicate('write_atom', 2, 1)
	put_constant('stderr', 0)
	pseudo_instr2(18, 0, 20)
	put_constant('stderr', 0)
	put_constant('
', 1)
	deallocate
	execute_predicate('write_atom', 2)

$3:
	pseudo_instr1(46, 0)
	get_structure('exception', 1, 0)
	allocate(8)
	unify_y_variable(7)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_value(7, 0)
	put_y_variable(6, 1)
	put_y_variable(1, 2)
	put_y_variable(5, 3)
	put_y_variable(4, 4)
	call_predicate('$valid_exception_term', 5, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(1, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	call_predicate('$get_exception_message', 6, 4)
	put_y_value(2, 1)
	put_constant('stderr', 0)
	call_predicate('$streamnum', 2, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$write_term_list', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	call_predicate('$exception_severity', 4, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$4:
	pseudo_instr1(46, 0)
	put_constant('ctrlC_reset', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$5:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('stderr', 0)
	put_constant('caught', 1)
	call_predicate('write_atom', 2, 1)
	put_constant('stderr', 0)
	put_constant(':', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('errornl', 1)
end('$interpreter_catch_msg'/1):



'$exit_interpreter'/1:


$1:
	put_constant('end_of_file', 1)
	pseudo_instr2(110, 0, 1)
	proceed
end('$exit_interpreter'/1):



'$solve_query'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 1)
	get_y_level(0)
	call_predicate('$interpreter_call', 1, 2)
	call_predicate('retry_delays', 0, 2)
	put_y_value(1, 0)
	call_predicate('$print_result', 1, 1)
	cut(0)
	fail

$2:
	pseudo_instr1(28, 0)
	allocate(1)
	get_y_variable(0, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 1)
	put_y_value(0, 0)
	put_constant('no', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 0)
	fail
end('$solve_query'/2):



'$interpreter_call'/1:

	switch_on_term(0, $25, $11, $11, $12, $11, $17)

$12:
	switch_on_structure(0, 8, ['$default':$11, '$'/0:$13, 'spy'/1:$14, 'nospy'/1:$15, 'leash'/1:$16])

$13:
	try(1, $7)
	retry($8)
	retry($10)
	trust($11)

$14:
	try(1, $7)
	trust($11)

$15:
	try(1, $8)
	trust($11)

$16:
	try(1, $10)
	trust($11)

$17:
	switch_on_constant(0, 16, ['$default':$11, 42:$18, 'debug':$19, 'nodebug':$20, 'debugging':$21, 'trace':$22, 'notrace':$23, 'nospyall':$24])

$18:
	try(1, $1)
	trust($11)

$19:
	try(1, $2)
	trust($11)

$20:
	try(1, $3)
	trust($11)

$21:
	try(1, $4)
	trust($11)

$22:
	try(1, $5)
	trust($11)

$23:
	try(1, $6)
	trust($11)

$24:
	try(1, $9)
	trust($11)

$25:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	trust($11)

$1:
	get_integer(42, 0)
	neck_cut
	proceed

$2:
	get_constant('debug', 0)
	neck_cut
	execute_predicate('debug', 0)

$3:
	get_constant('nodebug', 0)
	neck_cut
	execute_predicate('nodebug', 0)

$4:
	get_constant('debugging', 0)
	neck_cut
	execute_predicate('debugging', 0)

$5:
	get_constant('trace', 0)
	neck_cut
	execute_predicate('trace', 0)

$6:
	get_constant('notrace', 0)
	neck_cut
	execute_predicate('notrace', 0)

$7:
	get_structure('spy', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('spy', 1)

$8:
	get_structure('nospy', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('nospy', 1)

$9:
	get_constant('nospyall', 0)
	neck_cut
	execute_predicate('nospyall', 0)

$10:
	get_structure('leash', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('leash', 1)

$11:
	execute_predicate('call', 1)
end('$interpreter_call'/1):



'$print_result/1$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_constant('[]', 3)
	get_x_value(0, 3)
	put_constant('[]', 0)
	get_x_value(1, 0)
	put_constant('[]', 0)
	get_x_value(2, 0)
	neck_cut
	pseudo_instr1(28, 0)
	put_integer(10, 1)
	allocate(0)
	call_predicate('put_code', 2, 0)
	deallocate
	execute_predicate('flush_output', 0)

$2:
	put_constant('$allow_portray', 3)
	put_constant('true', 4)
	pseudo_instr2(74, 3, 4)
	allocate(0)
	call_predicate('$print_constraints_section', 3, 0)
	put_constant('$allow_portray', 0)
	put_constant('fail', 1)
	pseudo_instr2(74, 0, 1)
	call_predicate('flush_output', 0, 0)
	put_constant('[]', 0)
	deallocate
	execute_predicate('$interpreter_cont_section', 1)
end('$print_result/1$0'/3):



'$print_result/1$1'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	put_constant('[]', 3)
	get_x_value(0, 3)
	put_constant('[]', 0)
	get_x_value(1, 0)
	put_constant('[]', 0)
	get_x_value(2, 0)
	neck_cut
	proceed

$2:
	get_x_variable(2, 3)
	execute_predicate('$print_constraints_section', 3)
end('$print_result/1$1'/4):



'$print_result'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	put_constant('$allow_portray', 0)
	put_constant('true', 1)
	pseudo_instr2(74, 0, 1)
	allocate(4)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	call_predicate('$chr_print_constraints', 0, 4)
	put_constant('$allow_portray', 0)
	put_constant('fail', 1)
	pseudo_instr2(74, 0, 1)
	pseudo_instr1(28, 0)
	get_y_value(3, 0)
	put_y_value(3, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 4)
	put_y_value(3, 0)
	put_constant('yes', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_constant('[]', 0)
	call_predicate('collect_constraints', 4, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$print_result/1$0', 3)

$2:
	put_constant('$allow_portray', 1)
	put_constant('true', 2)
	pseudo_instr2(74, 1, 2)
	pseudo_instr2(111, 0, 1)
	allocate(5)
	get_y_variable(0, 1)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_value(0, 0)
	call_predicate('$print_bindings_section', 1, 5)
	pseudo_instr2(67, 20, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	call_predicate('collect_constraints', 4, 5)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$remove_chr_constraints', 2, 5)
	call_predicate('$chr_print_constraints', 0, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	call_predicate('$print_result/1$1', 4, 1)
	put_constant('$allow_portray', 0)
	put_constant('fail', 1)
	pseudo_instr2(74, 0, 1)
	call_predicate('flush_output', 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$interpreter_cont_section', 1)
end('$print_result'/1):



'$remove_chr_constraints'/2:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(2, $2)
	trust($3)

$5:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('delay_until', 2, 2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('bound', 1, 2)
	unify_x_variable(2)
	get_structure('$chr_process_var_delays', 2, 3)
	unify_x_value(2)
	unify_void(1)
	neck_cut
	execute_predicate('$remove_chr_constraints', 2)

$3:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$remove_chr_constraints', 2)
end('$remove_chr_constraints'/2):



'$print_bindings_section'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(4)
	unify_y_variable(0)
	get_structure('=', 2, 0)
	unify_y_variable(2)
	unify_y_variable(3)
	pseudo_instr1(28, 0)
	get_y_variable(1, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(1, 0)
	put_constant(' = ', 1)
	call_predicate('write_atom', 2, 3)
	pseudo_instr1(53, 22)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$write_t_q', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$print_bindings_section', 1)
end('$print_bindings_section'/1):



'$print_constraints_section'/3:


$1:
	allocate(4)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	get_y_variable(2, 2)
	pseudo_instr1(28, 0)
	get_y_variable(3, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 4)
	put_y_value(3, 0)
	put_constant('provided:', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 3)
	put_y_value(2, 0)
	call_predicate('$print_constraints', 1, 2)
	put_y_value(1, 0)
	call_predicate('$print_constraints', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$print_constraints', 1)
end('$print_constraints_section'/3):



'$print_constraints'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(0)
	pseudo_instr1(28, 0)
	get_y_variable(1, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 3)
	pseudo_instr1(53, 22)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$write_t_q', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$print_constraints', 1)
end('$print_constraints'/1):



'$interpreter_vars/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member_eq', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$interpreter_vars/3$0'/2):



'$interpreter_vars'/3:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(44, 22)
	call_predicate('$interpreter_vars/3$0', 2, 3)
	put_y_value(0, 0)
	get_list(0)
	unify_y_value(2)
	unify_y_value(1)
	deallocate
	proceed
end('$interpreter_vars'/3):



'$interpreter_cont_section/1$0'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	put_constant('[]', 2)
	get_x_value(0, 2)
	neck_cut
	put_integer(10, 0)
	get_x_value(1, 0)
	proceed

$2:
	get_list(0)
	unify_x_value(1)
	unify_void(1)
	proceed
end('$interpreter_cont_section/1$0'/2):



'$interpreter_cont_section'/1:


$1:
	allocate(4)
	get_y_variable(1, 0)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 0)
	call_predicate('get_line', 1, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('string_to_list', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$interpreter_cont_section/1$0', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$interpreter_cont', 2)
end('$interpreter_cont_section'/1):



'$interpreter_cont'/2:

	switch_on_term(0, $7, $3, $3, $3, $3, $4)

$4:
	switch_on_constant(0, 4, ['$default':$3, 10:$5, 44:$6])

$5:
	try(2, $1)
	trust($3)

$6:
	try(2, $2)
	trust($3)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_integer(10, 0)
	neck_cut
	proceed

$2:
	get_integer(44, 0)
	get_x_variable(0, 1)
	neck_cut
	execute_predicate('$interpreter_next_layer', 1)

$3:
	fail
end('$interpreter_cont'/2):



'$interpreter_next_layer'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('$indent_level', 1)
	pseudo_instr2(75, 1, 0)
	get_x_variable(1, 0)
	put_constant('$break_level', 2)
	pseudo_instr2(73, 2, 0)
	call_predicate('$set_interpreter_prompt', 2, 1)
	put_y_value(0, 0)
	call_predicate('$interpreter', 1, 0)
	put_constant('$indent_level', 1)
	pseudo_instr2(76, 1, 0)
	fail

$2:
	execute_predicate('$print_result', 1)
end('$interpreter_next_layer'/1):



'break'/0:

	try(0, $1)
	trust($2)

$1:
	put_constant('$break_level', 1)
	pseudo_instr2(75, 1, 0)
	put_constant('$indent_level', 2)
	pseudo_instr2(73, 2, 1)
	allocate(0)
	call_predicate('$set_interpreter_prompt', 2, 0)
	put_constant('[]', 0)
	call_predicate('$interpreter', 1, 0)
	put_constant('$break_level', 1)
	pseudo_instr2(76, 1, 0)
	fail

$2:
	proceed
end('break'/0):



'$set_interpreter_prompt'/2:

	switch_on_term(0, $8, $7, $7, $7, $7, $5)

$5:
	switch_on_constant(0, 4, ['$default':$7, 0:$6])

$6:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(2, $3)
	trust($4)

$8:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_integer(0, 0)
	get_integer(0, 1)
	neck_cut
	put_x_variable(0, 0)
	put_constant('| ?- ', 1)
	execute_predicate('prompt', 2)

$2:
	get_integer(0, 0)
	neck_cut
	put_x_variable(2, 3)
	get_list(3)
	unify_constant('[i')
	unify_x_ref(3)
	get_list(3)
	unify_x_value(1)
	unify_x_ref(1)
	get_list(1)
	unify_constant(']')
	unify_x_ref(1)
	get_list(1)
	unify_constant(' | ?- ')
	unify_constant('[]')
	pseudo_instr2(31, 2, 0)
	get_x_variable(1, 0)
	put_x_variable(0, 0)
	execute_predicate('prompt', 2)

$3:
	get_integer(0, 1)
	neck_cut
	put_x_variable(2, 3)
	get_list(3)
	unify_constant('[b')
	unify_x_ref(3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant(']')
	unify_x_ref(0)
	get_list(0)
	unify_constant(' | ?- ')
	unify_constant('[]')
	pseudo_instr2(31, 2, 1)
	put_x_variable(0, 0)
	execute_predicate('prompt', 2)

$4:
	put_x_variable(3, 4)
	get_list(4)
	unify_constant('[b')
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('i')
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_constant(']')
	unify_x_ref(0)
	get_list(0)
	unify_constant(' | ?- ')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_variable(1, 2)
	put_x_variable(0, 0)
	execute_predicate('prompt', 2)
end('$set_interpreter_prompt'/2):



'prompt/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('$prompt', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$2:
	put_constant('$prompt', 0)
	pseudo_instr2(74, 0, 1)
	fail
end('prompt/2$0'/2):



'prompt'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(2, 0)
	neck_cut
	put_constant('$prompt', 3)
	pseudo_instr2(73, 3, 1)
	get_x_value(2, 1)
	put_x_value(2, 1)
	execute_predicate('prompt/2$0', 2)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('prompt')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('prompt')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('prompt')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('prompt')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('prompt'/2):



