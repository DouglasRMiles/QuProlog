'$signal_handler'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'SIGINT':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_constant('SIGINT', 0)
	put_integer(5, 0)
	put_integer(0, 1)
	pseudo_instr2(10, 0, 1)
	allocate(2)
	get_y_level(0)
	put_y_variable(1, 0)
	call_predicate('$read_option', 1, 2)
	put_y_value(1, 0)
	call_predicate('$SIGINT_handler', 1, 1)
	put_integer(5, 0)
	put_integer(1, 1)
	pseudo_instr2(10, 0, 1)
	cut(0)
	deallocate
	proceed

$2:
	execute_predicate('default_signal_handler', 1)
end('$signal_handler'/1):



'$read_option/1$0'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_value(1)
	unify_void(1)
	neck_cut
	proceed

$2:
	put_integer(99, 0)
	get_x_value(1, 0)
	proceed
end('$read_option/1$0'/2):



'$read_option'/1:


$1:
	allocate(3)
	get_y_variable(1, 0)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	call_predicate('errornl', 0, 3)
	call_predicate('repeat', 0, 3)
	put_constant('SIGINT interrupt [cehprtx?] ? ', 0)
	call_predicate('error', 1, 3)
	put_constant('stderr', 0)
	pseudo_instr1(31, 0)
	put_y_value(2, 0)
	call_predicate('get_line', 1, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('string_to_list', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$read_option/1$0', 2)
end('$read_option'/1):



'$SIGINT_handler'/1:

	switch_on_term(0, $10, 'fail', 'fail', 'fail', 'fail', $9)

$9:
	switch_on_constant(0, 16, ['$default':'fail', 99:$1, 101:$2, 104:$3, 116:$4, 112:$5, 114:$6, 120:$7, 63:$8])

$10:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_integer(99, 0)
	execute_predicate('errornl', 0)

$2:
	get_integer(101, 0)
	execute_predicate('halt', 0)

$3:
	get_integer(104, 0)
	allocate(0)
	call_predicate('errornl', 0, 0)
	put_constant('c)ontinue current execution', 0)
	call_predicate('errornl', 1, 0)
	put_constant('e)xit Qu-Prolog', 0)
	call_predicate('errornl', 1, 0)
	put_constant('h)elp message', 0)
	call_predicate('errornl', 1, 0)
	put_constant('p)ush a goal into a thread', 0)
	call_predicate('errornl', 1, 0)
	put_constant('t)hread info', 0)
	call_predicate('errornl', 1, 0)
	put_constant('r)eset: kill all threads (except thread0) and throw ctrlC_reset in thread0', 0)
	call_predicate('errornl', 1, 0)
	put_constant('e(x)it a given thread', 0)
	call_predicate('errornl', 1, 0)
	put_constant('? help message', 0)
	call_predicate('errornl', 1, 0)
	call_predicate('errornl', 0, 0)
	put_constant('stderr', 0)
	pseudo_instr1(31, 0)
	fail

$4:
	get_integer(116, 0)
	allocate(0)
	call_predicate('display_thread_info', 0, 0)
	fail

$5:
	get_integer(112, 0)
	allocate(2)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_constant('Enter thread id  (terminate with .) ', 0)
	call_predicate('error', 1, 2)
	put_constant('stderr', 0)
	pseudo_instr1(31, 0)
	put_y_value(1, 0)
	call_predicate('read', 1, 2)
	put_constant('Enter the goal to push (terminate with .) ', 0)
	call_predicate('error', 1, 2)
	put_constant('stderr', 0)
	pseudo_instr1(31, 0)
	put_y_value(0, 0)
	call_predicate('read', 1, 2)
	pseudo_instr2(103, 21, 20)
	fail

$6:
	get_integer(114, 0)
	pseudo_instr1(96, 0)
	allocate(0)
	call_predicate('$exit_threads', 1, 0)
	put_constant('thread0', 0)
	put_x_variable(1, 2)
	get_structure('throw', 1, 2)
	unify_constant('ctrlC_reset')
	pseudo_instr2(103, 0, 1)
	deallocate
	execute_predicate('errornl', 0)

$7:
	get_integer(120, 0)
	allocate(3)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_constant('Enter thread id to exit', 0)
	call_predicate('error', 1, 3)
	put_constant('stderr', 0)
	pseudo_instr1(31, 0)
	put_y_value(2, 0)
	call_predicate('get_line', 1, 3)
	put_y_value(1, 0)
	put_y_value(2, 2)
	put_string("
", 1)
	call_predicate('string_concat', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('string_to_atom', 2, 1)
	pseudo_instr1(97, 20)
	fail

$8:
	get_integer(63, 0)
	put_integer(104, 0)
	execute_predicate('$SIGINT_handler', 1)
end('$SIGINT_handler'/1):



'$exit_threads'/1:

	switch_on_term(0, $6, 'fail', $5, 'fail', 'fail', $1)

$5:
	try(1, $2)
	retry($3)
	trust($4)

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_integer(0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$exit_threads', 1)

$3:
	get_list(0)
	unify_x_variable(1)
	unify_x_variable(0)
	put_x_variable(2, 2)
	pseudo_instr2(82, 1, 2)
	neck_cut
	pseudo_instr1(97, 2)
	execute_predicate('$exit_threads', 1)

$4:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$exit_threads', 1)
end('$exit_threads'/1):



'display_thread_info'/0:


$1:
	pseudo_instr1(96, 0)
	allocate(2)
	get_y_variable(0, 0)
	put_y_variable(1, 1)
	put_constant('stderr', 0)
	call_predicate('$streamnum', 2, 2)
	put_y_value(1, 0)
	put_constant('Status', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	put_integer(6, 1)
	call_predicate('$tab', 2, 2)
	put_y_value(1, 0)
	put_constant('ThreadName', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	put_integer(3, 1)
	call_predicate('$tab', 2, 2)
	put_y_value(1, 0)
	put_constant('InitialGoal', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_thread_info', 1)
end('display_thread_info'/0):



'$display_thread_info/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(66, 0)
	neck_cut
	put_constant('r', 0)
	get_x_value(1, 0)
	proceed

$2:
	put_constant('e', 0)
	get_x_value(1, 0)
	proceed
end('$display_thread_info/1$0'/2):



'$display_thread_info/1$1'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(82, 0, 1)
	neck_cut
	proceed

$2:
	put_constant('none', 0)
	get_x_value(1, 0)
	proceed
end('$display_thread_info/1$1'/2):



'$display_thread_info'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	allocate(5)
	unify_y_variable(2)
	unify_y_variable(0)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_value(2, 0)
	put_y_variable(4, 1)
	call_predicate('$display_thread_info/1$0', 2, 5)
	put_constant('stderr', 0)
	put_integer(5, 1)
	call_predicate('tab', 2, 5)
	put_y_value(4, 0)
	call_predicate('error', 1, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$display_thread_info/1$1', 2, 4)
	put_y_value(3, 1)
	put_integer(16, 0)
	call_predicate('$format', 2, 3)
	pseudo_instr2(78, 22, 0)
	get_y_value(1, 0)
	put_constant('stderr', 0)
	put_integer(3, 1)
	call_predicate('tab', 2, 2)
	put_y_value(1, 0)
	call_predicate('errornl', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_thread_info', 1)
end('$display_thread_info'/1):



'$format'/2:


$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(0, 1)
	put_y_variable(1, 19)
	put_y_value(0, 0)
	put_y_variable(3, 1)
	call_predicate('name', 2, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('length', 2, 3)
	pseudo_instr3(3, 22, 21, 0)
	get_x_variable(1, 0)
	put_constant('stderr', 0)
	call_predicate('tab', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('error', 1)
end('$format'/2):



'$signal_number'/2:

	switch_on_term(0, $36, 'fail', 'fail', 'fail', 'fail', $35)

$35:
	switch_on_constant(0, 128, ['$default':'fail', 'SIGHUP':$1, 'SIGINT':$2, 'SIGQUIT':$3, 'SIGILL':$4, 'SIGTRAP':$5, 'SIGIOT':$6, 'SIGABRT':$7, 'SIGBUS':$8, 'SIGFPE':$9, 'SIGKILL':$10, 'SIGUSR1':$11, 'SIGSEGV':$12, 'SIGUSR2':$13, 'SIGPIPE':$14, 'SIGALRM':$15, 'SIGTERM':$16, 'SIGSTKFLT':$17, 'SIGCLD':$18, 'SIGCHLD':$19, 'SIGCONT':$20, 'SIGSTOP':$21, 'SIGTSTP':$22, 'SIGTTIN':$23, 'SIGTTOU':$24, 'SIGURG':$25, 'SIGXCPU':$26, 'SIGXFSZ':$27, 'SIGVTALRM':$28, 'SIGPROF':$29, 'SIGWINCH':$30, 'SIGPOLL':$31, 'SIGIO':$32, 'SIGPWR':$33, 'SIGUNUSED':$34])

$36:
	try(2, $1)
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
	retry($22)
	retry($23)
	retry($24)
	retry($25)
	retry($26)
	retry($27)
	retry($28)
	retry($29)
	retry($30)
	retry($31)
	retry($32)
	retry($33)
	trust($34)

$1:
	get_constant('SIGHUP', 0)
	get_integer(1, 1)
	proceed

$2:
	get_constant('SIGINT', 0)
	get_integer(2, 1)
	proceed

$3:
	get_constant('SIGQUIT', 0)
	get_integer(3, 1)
	proceed

$4:
	get_constant('SIGILL', 0)
	get_integer(4, 1)
	proceed

$5:
	get_constant('SIGTRAP', 0)
	get_integer(5, 1)
	proceed

$6:
	get_constant('SIGIOT', 0)
	get_integer(6, 1)
	proceed

$7:
	get_constant('SIGABRT', 0)
	get_integer(6, 1)
	proceed

$8:
	get_constant('SIGBUS', 0)
	get_integer(7, 1)
	proceed

$9:
	get_constant('SIGFPE', 0)
	get_integer(8, 1)
	proceed

$10:
	get_constant('SIGKILL', 0)
	get_integer(9, 1)
	proceed

$11:
	get_constant('SIGUSR1', 0)
	get_integer(10, 1)
	proceed

$12:
	get_constant('SIGSEGV', 0)
	get_integer(11, 1)
	proceed

$13:
	get_constant('SIGUSR2', 0)
	get_integer(12, 1)
	proceed

$14:
	get_constant('SIGPIPE', 0)
	get_integer(13, 1)
	proceed

$15:
	get_constant('SIGALRM', 0)
	get_integer(14, 1)
	proceed

$16:
	get_constant('SIGTERM', 0)
	get_integer(15, 1)
	proceed

$17:
	get_constant('SIGSTKFLT', 0)
	get_integer(16, 1)
	proceed

$18:
	get_constant('SIGCLD', 0)
	get_integer(17, 1)
	proceed

$19:
	get_constant('SIGCHLD', 0)
	get_integer(17, 1)
	proceed

$20:
	get_constant('SIGCONT', 0)
	get_integer(18, 1)
	proceed

$21:
	get_constant('SIGSTOP', 0)
	get_integer(19, 1)
	proceed

$22:
	get_constant('SIGTSTP', 0)
	get_integer(20, 1)
	proceed

$23:
	get_constant('SIGTTIN', 0)
	get_integer(21, 1)
	proceed

$24:
	get_constant('SIGTTOU', 0)
	get_integer(22, 1)
	proceed

$25:
	get_constant('SIGURG', 0)
	get_integer(23, 1)
	proceed

$26:
	get_constant('SIGXCPU', 0)
	get_integer(24, 1)
	proceed

$27:
	get_constant('SIGXFSZ', 0)
	get_integer(25, 1)
	proceed

$28:
	get_constant('SIGVTALRM', 0)
	get_integer(26, 1)
	proceed

$29:
	get_constant('SIGPROF', 0)
	get_integer(27, 1)
	proceed

$30:
	get_constant('SIGWINCH', 0)
	get_integer(28, 1)
	proceed

$31:
	get_constant('SIGPOLL', 0)
	get_integer(29, 1)
	proceed

$32:
	get_constant('SIGIO', 0)
	get_integer(29, 1)
	proceed

$33:
	get_constant('SIGPWR', 0)
	get_integer(30, 1)
	proceed

$34:
	get_constant('SIGUNUSED', 0)
	get_integer(31, 1)
	proceed
end('$signal_number'/2):



'get_signals_flag'/1:


$1:
	get_x_variable(1, 0)
	put_integer(3, 2)
	pseudo_instr2(11, 2, 0)
	execute_predicate('$get_signals_flag', 2)
end('get_signals_flag'/1):



'$get_signals_flag'/2:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 0:$1, 1:$2])

$4:
	try(2, $1)
	trust($2)

$1:
	get_integer(0, 0)
	get_constant('off', 1)
	proceed

$2:
	get_integer(1, 0)
	get_constant('on', 1)
	proceed
end('$get_signals_flag'/2):



'clear_signal'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(2, 0)
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$signal_number', 2, 2)
	cut(1)
	pseudo_instr1(25, 20)
	deallocate
	proceed

$2:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('clear_signal')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('clear_signal')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('clear_signal')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('clear_signal')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('clear_signal'/1):



'default_signal_handler'/1:

	switch_on_term(0, $8, $7, $7, $7, $7, $5)

$5:
	switch_on_constant(0, 4, ['$default':$7, 'SIGINT':$6])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(1, $2)
	retry($3)
	trust($4)

$8:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('SIGINT', 0)
	neck_cut
	put_constant('SIGINT', 0)
	execute_predicate('$signal_handler', 1)

$2:
	pseudo_instr1(2, 0)
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$signal_number', 2, 2)
	cut(1)
	pseudo_instr1(26, 20)
	deallocate
	proceed

$3:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('default_signal_handler')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('default_signal_handler')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('default_signal_handler')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('default_signal_handler')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('default_signal_handler'/1):



'$psi0_error_handler/4$0'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 5)
	get_y_level(2)
	put_y_variable(0, 5)
	call_predicate('$psi0_special_exception_handler', 6, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$psi0_general_exception_handler', 6)
end('$psi0_error_handler/4$0'/6):



'$psi0_error_handler'/4:


$1:
	allocate(7)
	get_y_variable(0, 0)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	put_y_variable(1, 19)
	put_y_value(4, 0)
	put_y_variable(3, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_y_variable(2, 4)
	call_predicate('$psi0_decl', 5, 7)
	put_y_value(4, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(2, 3)
	put_y_value(3, 4)
	put_y_value(1, 5)
	call_predicate('$psi0_error_handler/4$0', 6, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi0_error_handler'/4):



'$psi1_error_handler/5$0'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 6)
	get_y_level(2)
	put_y_variable(0, 6)
	call_predicate('$psi1_special_exception_handler', 7, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$psi1_general_exception_handler', 7)
end('$psi1_error_handler/5$0'/7):



'$psi1_error_handler'/5:


$1:
	allocate(8)
	get_y_variable(0, 0)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	put_y_variable(1, 19)
	put_y_value(5, 0)
	put_y_variable(3, 1)
	put_y_value(4, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_y_variable(2, 5)
	call_predicate('$psi1_decl', 6, 8)
	put_y_value(5, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(2, 3)
	put_y_value(3, 4)
	put_y_value(4, 5)
	put_y_value(1, 6)
	call_predicate('$psi1_error_handler/5$0', 7, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi1_error_handler'/5):



'$psi2_error_handler/6$0'/8:

	try(8, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 7)
	get_y_level(2)
	put_y_variable(0, 7)
	call_predicate('$psi2_special_exception_handler', 8, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$psi2_general_exception_handler', 8)
end('$psi2_error_handler/6$0'/8):



'$psi2_error_handler'/6:


$1:
	allocate(9)
	get_y_variable(0, 0)
	get_y_variable(8, 1)
	get_y_variable(7, 2)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	put_y_variable(1, 19)
	put_y_value(6, 0)
	put_y_variable(3, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	put_y_variable(2, 6)
	call_predicate('$psi2_decl', 7, 9)
	put_y_value(6, 0)
	put_y_value(8, 1)
	put_y_value(7, 2)
	put_y_value(2, 3)
	put_y_value(3, 4)
	put_y_value(5, 5)
	put_y_value(4, 6)
	put_y_value(1, 7)
	call_predicate('$psi2_error_handler/6$0', 8, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi2_error_handler'/6):



'$psi3_error_handler/7$0'/9:

	try(9, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 8)
	get_y_level(2)
	put_y_variable(0, 8)
	call_predicate('$psi3_special_exception_handler', 9, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$psi3_general_exception_handler', 9)
end('$psi3_error_handler/7$0'/9):



'$psi3_error_handler'/7:


$1:
	allocate(10)
	get_y_variable(0, 0)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	put_y_variable(1, 19)
	put_y_value(7, 0)
	put_y_variable(3, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	put_y_variable(2, 7)
	call_predicate('$psi3_decl', 8, 10)
	put_y_value(7, 0)
	put_y_value(9, 1)
	put_y_value(8, 2)
	put_y_value(2, 3)
	put_y_value(3, 4)
	put_y_value(6, 5)
	put_y_value(5, 6)
	put_y_value(4, 7)
	put_y_value(1, 8)
	call_predicate('$psi3_error_handler/7$0', 9, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi3_error_handler'/7):



'$psi4_error_handler/8$0'/10:

	try(10, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 9)
	get_y_level(2)
	put_y_variable(0, 9)
	call_predicate('$psi4_special_exception_handler', 10, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$psi4_general_exception_handler', 10)
end('$psi4_error_handler/8$0'/10):



'$psi4_error_handler'/8:


$1:
	allocate(11)
	get_y_variable(0, 0)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(6, 5)
	get_y_variable(5, 6)
	get_y_variable(4, 7)
	put_y_variable(1, 19)
	put_y_value(8, 0)
	put_y_variable(3, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	put_y_variable(2, 8)
	call_predicate('$psi4_decl', 9, 11)
	put_y_value(8, 0)
	put_y_value(10, 1)
	put_y_value(9, 2)
	put_y_value(2, 3)
	put_y_value(3, 4)
	put_y_value(7, 5)
	put_y_value(6, 6)
	put_y_value(5, 7)
	put_y_value(4, 8)
	put_y_value(1, 9)
	call_predicate('$psi4_error_handler/8$0', 10, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi4_error_handler'/8):



'$psi5_error_handler/9$0'/11:

	try(11, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 10)
	get_y_level(2)
	put_y_variable(0, 10)
	call_predicate('$psi5_special_exception_handler', 11, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$psi5_general_exception_handler', 11)
end('$psi5_error_handler/9$0'/11):



'$psi5_error_handler'/9:


$1:
	allocate(12)
	get_y_variable(0, 0)
	get_y_variable(11, 1)
	get_y_variable(10, 2)
	get_y_variable(9, 3)
	get_y_variable(8, 4)
	get_y_variable(7, 5)
	get_y_variable(6, 6)
	get_y_variable(5, 7)
	get_y_variable(4, 8)
	put_y_variable(1, 19)
	put_y_value(9, 0)
	put_y_variable(3, 1)
	put_y_value(8, 2)
	put_y_value(7, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	put_y_value(4, 6)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	put_y_variable(2, 9)
	call_predicate('$psi5_decl', 10, 12)
	put_y_value(9, 0)
	put_y_value(11, 1)
	put_y_value(10, 2)
	put_y_value(2, 3)
	put_y_value(3, 4)
	put_y_value(8, 5)
	put_y_value(7, 6)
	put_y_value(6, 7)
	put_y_value(5, 8)
	put_y_value(4, 9)
	put_y_value(1, 10)
	call_predicate('$psi5_error_handler/9$0', 11, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi5_error_handler'/9):



'$psi0_resume'/2:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$psi0_decl', 5, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi0_resume'/2):



'$psi1_resume'/3:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	call_predicate('$psi1_decl', 6, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi1_resume'/3):



'$psi2_resume'/4:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	call_predicate('$psi2_decl', 7, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi2_resume'/4):



'$psi3_resume'/5:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	call_predicate('$psi3_decl', 8, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi3_resume'/5):



'$psi4_resume'/6:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	call_predicate('$psi4_decl', 9, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi4_resume'/6):



'$psi5_resume'/7:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	put_x_variable(9, 9)
	call_predicate('$psi5_decl', 10, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_constant('true', 0)
	call_predicate('call_predicate', 1, 1)
	pseudo_instr1(23, 20)
	deallocate
	proceed
end('$psi5_resume'/7):



'$query_handlers1593041820_486/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$psi0_special_exception_handler')
	set_integer(6)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_handlers1593041820_486/0$0'/0):



'$query_handlers1593041820_486/0$1'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$psi1_special_exception_handler')
	set_integer(7)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_handlers1593041820_486/0$1'/0):



'$query_handlers1593041820_486/0$2'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$psi2_special_exception_handler')
	set_integer(8)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_handlers1593041820_486/0$2'/0):



'$query_handlers1593041820_486/0$3'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$psi3_special_exception_handler')
	set_integer(9)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_handlers1593041820_486/0$3'/0):



'$query_handlers1593041820_486/0$4'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$psi4_special_exception_handler')
	set_integer(10)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_handlers1593041820_486/0$4'/0):



'$query_handlers1593041820_486/0$5'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$psi5_special_exception_handler')
	set_integer(11)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_handlers1593041820_486/0$5'/0):



'$query_handlers1593041820_486'/0:

	try(0, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	allocate(0)
	call_predicate('$query_handlers1593041820_486/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_handlers1593041820_486/0$1', 0, 0)
	fail

$3:
	allocate(0)
	call_predicate('$query_handlers1593041820_486/0$2', 0, 0)
	fail

$4:
	allocate(0)
	call_predicate('$query_handlers1593041820_486/0$3', 0, 0)
	fail

$5:
	allocate(0)
	call_predicate('$query_handlers1593041820_486/0$4', 0, 0)
	fail

$6:
	allocate(0)
	call_predicate('$query_handlers1593041820_486/0$5', 0, 0)
	fail

$7:
	proceed
end('$query_handlers1593041820_486'/0):



'$query'/0:


$1:
	execute_predicate('$query_handlers1593041820_486', 0)
end('$query'/0):



