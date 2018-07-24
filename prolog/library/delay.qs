'retry_woken_delays'/0:


$1:
	proceed
end('retry_woken_delays'/0):



'$ignore_delays'/0:


$1:
	put_constant('$delayed_problems', 0)
	put_constant('[]', 1)
	pseudo_instr2(3, 0, 1)
	proceed
end('$ignore_delays'/0):



'$init_retry'/0:


$1:
	put_constant('$delayed_problems', 0)
	put_constant('[]', 1)
	pseudo_instr2(3, 0, 1)
	put_constant('$doing_retry', 0)
	put_constant('fail', 1)
	pseudo_instr2(3, 0, 1)
	proceed
end('$init_retry'/0):



'delay/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(4, 0)
	proceed
end('delay/2$0'/1):



'delay/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	fail

$2:
	proceed
end('delay/2$1'/1):



'delay'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('delay/2$0', 1, 3)
	put_y_value(1, 0)
	call_predicate('delay/2$1', 1, 3)
	cut(2)
	pseudo_instr2(48, 21, 20)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('delay')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('+')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('delay')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('anyvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('nonvar')
	put_structure(2, 4)
	set_constant('delay')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(0, 1)
	execute_predicate('call_predicate', 1)
end('delay'/2):



'$do_fast_retry'/0:


$1:
	put_integer(0, 1)
	pseudo_instr2(11, 1, 0)
	put_integer(1, 1)
	get_x_value(0, 1)
	proceed
end('$do_fast_retry'/0):



'$clear_fast_retry'/0:


$1:
	put_integer(0, 0)
	put_integer(0, 1)
	pseudo_instr2(10, 0, 1)
	proceed
end('$clear_fast_retry'/0):



'retry_woken_delays'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$fast_retry_delay1', 0, 1)
	call_predicate('$compress_delays', 0, 1)
	put_integer(4, 0)
	put_integer(0, 1)
	pseudo_instr2(10, 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('retry_woken_delays'/1):



'$fast_retry_delay1/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$do_fast_retry', 0, 1)
	cut(0)
	call_predicate('$clear_fast_retry', 0, 0)
	deallocate
	execute_predicate('$fast_retry_delay1', 0)

$2:
	proceed
end('$fast_retry_delay1/0$0'/0):



'$fast_retry_delay1'/0:


$1:
	put_constant('$delayed_problems', 1)
	pseudo_instr2(4, 1, 0)
	allocate(0)
	call_predicate('$fast_process_delays', 1, 0)
	deallocate
	execute_predicate('$fast_retry_delay1/0$0', 0)
end('$fast_retry_delay1'/0):



'$fast_process_delays'/1:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(1, $2)
	trust($3)

$5:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(1)
	unify_y_variable(0)
	get_structure(',', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	pseudo_instr1(42, 0)
	neck_cut
	put_constant('solved', 2)
	get_x_value(0, 2)
	pseudo_instr2(49, 1, 0)
	call_predicate('$fast_do_delay_list', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$fast_process_delays', 1)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$fast_process_delays', 1)
end('$fast_process_delays'/1):



'$fast_do_delay_list/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(41, 2)
	neck_cut
	pseudo_instr1(40, 2)
	execute_predicate('call_predicate', 1)

$2:
	proceed
end('$fast_do_delay_list/1$0'/2):



'$fast_do_delay_list'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(1)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	call_predicate('$fast_do_delay_list', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$fast_do_delay_list/1$0', 2)
end('$fast_do_delay_list'/1):



'$compress_delays'/0:


$1:
	put_constant('$delayed_problems', 1)
	pseudo_instr2(4, 1, 0)
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$compress_delays1', 2, 1)
	put_constant('$delayed_problems', 0)
	pseudo_instr2(3, 0, 20)
	deallocate
	proceed
end('$compress_delays'/0):



'$compress_delays1'/2:

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
	get_structure(',', 2, 2)
	unify_x_variable(2)
	unify_void(1)
	put_constant('solved', 4)
	pseudo_instr3(6, 2, 4, 3)
	put_constant('true', 2)
	get_x_value(3, 2)
	neck_cut
	execute_predicate('$compress_delays1', 2)

$3:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$compress_delays1', 2)
end('$compress_delays1'/2):



'retry_delays'/0:


$1:
	put_constant('all', 0)
	allocate(0)
	call_predicate('$retry_delays', 1, 0)
	pseudo_instr0(4)
	deallocate
	proceed
end('retry_delays'/0):



'retry_nfi'/0:


$1:
	put_constant('nfi', 0)
	allocate(0)
	call_predicate('$retry_delays', 1, 0)
	pseudo_instr0(4)
	deallocate
	proceed
end('retry_nfi'/0):



'$retry_delays/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('$retry_make_progress', 1)
	pseudo_instr2(4, 1, 0)
	put_constant('fail', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('$retry_delays', 1)
end('$retry_delays/1$0'/1):



'$retry_delays'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('$delayed_problems', 1)
	pseudo_instr2(4, 1, 0)
	put_constant('$retry_make_progress', 1)
	put_constant('fail', 2)
	pseudo_instr2(3, 1, 2)
	put_y_value(0, 1)
	call_predicate('$process_delays', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$retry_delays/1$0', 1)
end('$retry_delays'/1):



'$process_delays'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(2)
	unify_y_variable(1)
	get_structure(',', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_y_variable(0, 1)
	pseudo_instr2(49, 0, 1)
	get_x_variable(0, 1)
	put_y_value(0, 1)
	call_predicate('$do_delay_list', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$process_delays', 2)
end('$process_delays'/2):



'$do_delay_list/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 3)
	call_predicate('$check_problem_type', 4, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$call_delayed_problem', 2)

$2:
	proceed
end('$do_delay_list/2$0'/3):



'$do_delay_list'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(',', 2, 2)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	call_predicate('$do_delay_list', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$do_delay_list/2$0', 3)
end('$do_delay_list'/2):



'$call_delayed_problem'/2:

	try(2, $1)
	trust($2)

$1:
	get_structure('=', 2, 1)
	unify_x_variable(1)
	unify_x_variable(2)
	pseudo_instr2(110, 1, 2)
	neck_cut
	pseudo_instr1(40, 0)
	proceed

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(40, 2)
	execute_predicate('call_predicate', 1)
end('$call_delayed_problem'/2):



'$check_problem_type'/4:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'all':$1, 'nfi':$2])

$4:
	try(4, $1)
	trust($2)

$1:
	get_constant('all', 0)
	get_x_value(2, 3)
	pseudo_instr1(41, 1)
	proceed

$2:
	get_constant('nfi', 0)
	get_x_value(2, 3)
	put_x_value(2, 0)
	get_structure('not_free_in', 2, 0)
	unify_void(2)
	pseudo_instr1(41, 1)
	proceed
end('$check_problem_type'/4):



'$delays_to_list'/1:


$1:
	get_x_variable(2, 0)
	put_constant('$delayed_problems', 1)
	pseudo_instr2(4, 1, 0)
	put_constant('[]', 1)
	execute_predicate('$delays_to_list1', 3)
end('$delays_to_list'/1):



'$delays_to_list1'/3:

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
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(2)
	get_structure(',', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$delays_to_list2', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$delays_to_list1', 3)
end('$delays_to_list1'/3):



'$delays_to_list2'/3:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(3, $2)
	trust($3)

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_x_ref(3)
	unify_x_variable(0)
	get_structure(',', 2, 3)
	unify_x_variable(3)
	unify_x_variable(4)
	get_list(2)
	unify_x_value(4)
	unify_x_variable(2)
	pseudo_instr1(41, 3)
	neck_cut
	execute_predicate('$delays_to_list2', 3)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$delays_to_list2', 3)
end('$delays_to_list2'/3):



'get_delays'/1:


$1:
	put_constant('all', 2)
	put_constant('[]', 3)
	pseudo_instr3(63, 1, 2, 3)
	get_x_value(0, 1)
	proceed
end('get_delays'/1):



'get_unify_delays'/1:


$1:
	put_constant('unify', 2)
	put_constant('[]', 3)
	pseudo_instr3(63, 1, 2, 3)
	get_x_value(0, 1)
	proceed
end('get_unify_delays'/1):



'get_unify_delays_avoid'/2:


$1:
	put_constant('unify', 3)
	pseudo_instr3(63, 2, 3, 1)
	get_x_value(0, 2)
	proceed
end('get_unify_delays_avoid'/2):



'$display_delay_info'/0:


$1:
	put_constant('$delayed_problems', 1)
	pseudo_instr2(4, 1, 0)
	allocate(1)
	get_y_variable(0, 0)
	put_constant('--------- delay info -------------', 0)
	call_predicate('errornl', 1, 1)
	put_y_value(0, 0)
	call_predicate('$display_delay_info', 1, 0)
	put_constant('--------- end delay info -------------', 0)
	deallocate
	execute_predicate('errornl', 1)
end('$display_delay_info'/0):



'$display_delay_info/1$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(41, 0)
	neck_cut
	put_constant('frozen - ', 0)
	execute_predicate('error', 1)

$2:
	put_constant('thawed - ', 0)
	execute_predicate('error', 1)
end('$display_delay_info/1$0/1$0'/1):



'$display_delay_info/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	execute_predicate('$display_delay_info/1$0/1$0', 1)

$2:
	put_constant('solved - ', 0)
	execute_predicate('error', 1)
end('$display_delay_info/1$0'/1):



'$display_delay_info'/1:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(1, $2)
	trust($3)

$5:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(2)
	unify_y_variable(0)
	get_structure(',', 2, 0)
	unify_x_variable(0)
	unify_y_variable(1)
	neck_cut
	call_predicate('$display_delay_info/1$0', 1, 2)
	put_constant(' ', 0)
	call_predicate('errornl', 1, 2)
	pseudo_instr2(49, 21, 0)
	call_predicate('$display_DL', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_delay_info', 1)

$3:
	get_list(0)
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	put_constant('weird list - ', 0)
	call_predicate('errornl', 1, 2)
	put_y_value(1, 1)
	put_constant('stderr', 0)
	call_predicate('write_canonical', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_delay_info', 1)
end('$display_delay_info'/1):



'$display_DL/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(41, 0)
	neck_cut
	put_constant('        frozen - ', 0)
	execute_predicate('error', 1)

$2:
	put_constant('        thawed - ', 0)
	execute_predicate('error', 1)
end('$display_DL/1$0'/1):



'$display_DL'/1:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(1, $2)
	trust($3)

$5:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(2)
	unify_y_variable(0)
	get_structure(',', 2, 0)
	unify_x_variable(0)
	unify_y_variable(1)
	neck_cut
	call_predicate('$display_DL/1$0', 1, 2)
	put_y_value(1, 1)
	put_constant('stderr', 0)
	call_predicate('write_canonical', 2, 1)
	put_constant(' ', 0)
	call_predicate('errornl', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_DL', 1)

$3:
	get_list(0)
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	put_constant('        weird problem - ', 0)
	call_predicate('error', 1, 2)
	put_y_value(1, 1)
	put_constant('stderr', 0)
	call_predicate('write_canonical', 2, 1)
	put_constant(' ', 0)
	call_predicate('errornl', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_DL', 1)
end('$display_DL'/1):



'collect_constraints'/4:


$1:
	allocate(8)
	get_y_variable(5, 0)
	get_y_variable(1, 1)
	get_y_variable(3, 2)
	get_y_variable(4, 3)
	put_y_variable(6, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(7, 0)
	call_predicate('get_delays', 1, 8)
	put_y_value(7, 0)
	put_y_value(2, 1)
	put_y_value(6, 2)
	call_predicate('$split_delays', 3, 7)
	pseudo_instr2(111, 26, 0)
	get_y_value(4, 0)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(5)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	put_y_value(2, 2)
	put_y_value(0, 3)
	put_y_value(3, 4)
	put_constant('[]', 1)
	call_predicate('$get_keep_nfis', 5, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$get_distinct_list', 2)
end('collect_constraints'/4):



'$get_keep_nfis/5$0'/6:

	try(6, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 2)
	get_x_value(3, 4)
	proceed

$2:
	get_x_variable(6, 1)
	get_x_variable(1, 2)
	get_x_variable(0, 4)
	get_x_variable(2, 5)
	put_x_value(6, 4)
	execute_predicate('$get_keep_nfis', 5)
end('$get_keep_nfis/5$0'/6):



'$get_keep_nfis'/5:


$1:
	get_x_variable(5, 0)
	get_x_variable(6, 1)
	get_x_variable(0, 2)
	allocate(6)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	put_x_value(5, 1)
	put_x_value(6, 2)
	put_y_variable(3, 3)
	put_y_variable(2, 5)
	put_y_variable(1, 6)
	put_y_variable(0, 7)
	put_constant('[]', 4)
	call_predicate('$extract_nfis', 8, 6)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(5, 3)
	put_y_value(1, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$get_keep_nfis/5$0', 6)
end('$get_keep_nfis'/5):



'$extract_nfis/8$0'/11:

	try(11, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(9)
	call_predicate('$dont_keep', 3, 10)
	cut(9)
	put_y_value(7, 0)
	put_y_value(8, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_list(4)
	set_y_value(4)
	set_y_value(3)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$extract_nfis', 8)

$2:
	get_x_variable(0, 1)
	allocate(11)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(6, 5)
	get_y_variable(5, 6)
	get_y_variable(4, 7)
	get_y_variable(3, 8)
	get_y_variable(2, 9)
	get_y_variable(1, 10)
	put_y_value(1, 1)
	get_constant('true', 1)
	put_y_variable(0, 19)
	put_y_variable(10, 1)
	call_predicate('substitution', 2, 11)
	pseudo_instr2(67, 30, 0)
	put_y_value(9, 1)
	put_y_value(0, 2)
	call_predicate('union_list', 3, 9)
	put_y_value(8, 0)
	put_y_value(0, 1)
	put_list(2)
	set_y_value(5)
	set_y_value(7)
	put_y_value(6, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	deallocate
	execute_predicate('$extract_nfis', 8)
end('$extract_nfis/8$0'/11):



'$extract_nfis'/8:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(8, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(2, 3)
	get_x_value(4, 5)
	get_x_value(1, 6)
	proceed

$2:
	get_list(0)
	unify_x_variable(11)
	unify_x_variable(12)
	get_x_variable(13, 1)
	get_x_variable(14, 2)
	get_x_variable(15, 3)
	get_x_variable(16, 4)
	get_x_variable(8, 5)
	get_x_variable(9, 6)
	get_x_variable(10, 7)
	put_x_value(11, 0)
	get_structure('not_free_in', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	put_x_value(13, 2)
	put_x_value(12, 3)
	put_x_value(14, 4)
	put_x_value(15, 5)
	put_x_value(11, 6)
	put_x_value(16, 7)
	execute_predicate('$extract_nfis/8$0', 11)
end('$extract_nfis'/8):



'$split_delays/3$0'/5:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'not_free_in'/2:$5])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$6:
	try(5, $1)
	trust($2)

$1:
	put_x_value(0, 5)
	get_structure('not_free_in', 2, 5)
	unify_void(2)
	neck_cut
	get_list(1)
	unify_x_value(0)
	unify_x_value(2)
	get_x_value(3, 4)
	proceed

$2:
	get_x_value(1, 2)
	put_x_value(3, 1)
	get_list(1)
	unify_x_value(0)
	unify_x_value(4)
	proceed
end('$split_delays/3$0'/5):



'$split_delays'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('[]', 2)
	proceed

$2:
	get_list(0)
	allocate(5)
	unify_y_variable(4)
	unify_x_variable(0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$split_delays', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$split_delays/3$0', 5)
end('$split_delays'/3):



'$dont_keep/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr1(5, 0)
	neck_cut
	pseudo_instr2(59, 0, 1)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('open_tail', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('member_eq', 2)

$2:
	execute_predicate('member_eq', 2)
end('$dont_keep/3$0'/2):



'$dont_keep'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_level(0)
	put_y_value(1, 1)
	call_predicate('member_eq', 2, 3)
	pseudo_instr2(25, 22, 0)
	put_y_value(1, 1)
	call_predicate('$dont_keep/3$0', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$dont_keep'/3):



'$get_distinct_list/2$0'/2:

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
	unify_x_variable(2)
	unify_x_variable(0)
	pseudo_instr1(4, 2)
	neck_cut
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$get_distinct_list/2$0', 2)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$get_distinct_list/2$0', 2)
end('$get_distinct_list/2$0'/2):



'$get_distinct_list'/2:


$1:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$get_distinct_list/2$0', 2, 2)
	put_y_value(0, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$get_distinct_list1', 3)
end('$get_distinct_list'/2):



'$get_distinct_list1/3$0'/4:

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
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	get_list(1)
	unify_x_ref(1)
	unify_x_value(2)
	get_structure('not_free_in', 2, 1)
	unify_x_value(3)
	unify_x_value(0)
	proceed
end('$get_distinct_list1/3$0'/4):



'$get_distinct_list1'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 2)
	proceed

$2:
	get_list(0)
	allocate(5)
	unify_y_variable(3)
	unify_x_variable(0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	put_y_variable(0, 19)
	put_y_variable(1, 2)
	call_predicate('$get_distinct_list1', 3, 5)
	pseudo_instr2(54, 23, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	call_predicate('intersect_list', 3, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$get_distinct_list1/3$0', 4)
end('$get_distinct_list1'/3):



'delay_until/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(0, 0)
	neck_cut
	fail

$2:
	proceed
end('delay_until/2$0'/1):



'delay_until/2$1'/2:

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
	unify_x_variable(2)
	unify_x_variable(0)
	pseudo_instr1(1, 2)
	neck_cut
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('delay_until/2$1', 2)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('delay_until/2$1', 2)
end('delay_until/2$1'/2):



'delay_until/2$2'/3:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(3, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(0)
	unify_void(1)
	neck_cut
	put_structure(1, 3)
	set_constant('ground')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('delay_until')
	set_x_value(3)
	set_x_value(2)
	execute_predicate('delay', 2)

$2:
	get_x_variable(0, 2)
	execute_predicate('call_predicate', 1)
end('delay_until/2$2'/3):



'delay_until/2$3'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	fail

$2:
	proceed
end('delay_until/2$3'/1):



'delay_until'/2:

	switch_on_term(0, $25, $24, $24, $15, $24, $24)

$15:
	switch_on_structure(0, 16, ['$default':$24, '$'/0:$16, 'or'/2:$17, 'and'/2:$18, 'nonvar'/1:$19, 'ground'/1:$20, 'bound'/1:$21, '$bound'/1:$22, 'identical_or_apart'/2:$23])

$16:
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
	trust($14)

$17:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$18:
	try(2, $1)
	retry($2)
	retry($3)
	trust($5)

$19:
	try(2, $1)
	retry($2)
	retry($3)
	retry($6)
	trust($7)

$20:
	try(2, $1)
	retry($2)
	retry($3)
	trust($8)

$21:
	try(2, $1)
	retry($2)
	retry($3)
	retry($9)
	trust($10)

$22:
	try(2, $1)
	retry($2)
	retry($3)
	retry($11)
	trust($12)

$23:
	try(2, $1)
	retry($2)
	retry($3)
	retry($13)
	trust($14)

$24:
	try(2, $1)
	retry($2)
	trust($3)

$25:
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
	trust($14)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('delay_until')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('+')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('delay_until')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('delay_until/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('delay_until')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('+')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('delay_until')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)

$3:
	get_structure('=', 2, 1)
	unify_x_variable(0)
	unify_x_variable(1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	proceed

$4:
	get_structure('or', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	allocate(2)
	get_y_variable(1, 1)
	put_x_value(2, 1)
	put_y_variable(0, 2)
	call_predicate('$delay_until_or', 3, 2)
	put_structure(1, 0)
	set_constant('nonvar')
	set_y_value(0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('delay_until', 2)

$5:
	get_structure('and', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_x_variable(3, 1)
	put_structure(2, 1)
	set_constant('delay_until')
	set_x_value(2)
	set_x_value(3)
	execute_predicate('delay_until', 2)

$6:
	get_structure('nonvar', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	pseudo_instr1(46, 2)
	neck_cut
	execute_predicate('call_predicate', 1)

$7:
	get_structure('nonvar', 1, 0)
	unify_x_variable(0)
	get_x_variable(2, 1)
	pseudo_instr2(25, 0, 1)
	put_x_value(1, 0)
	put_structure(1, 3)
	set_constant('nonvar')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('delay_until')
	set_x_value(3)
	set_x_value(2)
	execute_predicate('delay', 2)

$8:
	get_structure('ground', 1, 0)
	allocate(3)
	unify_y_variable(2)
	get_y_variable(1, 1)
	pseudo_instr2(111, 22, 0)
	pseudo_instr2(67, 0, 1)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('delay_until/2$1', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('delay_until/2$2', 3)

$9:
	get_structure('bound', 1, 0)
	allocate(3)
	unify_y_variable(1)
	get_y_variable(0, 1)
	pseudo_instr1(44, 21)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('delay_until/2$3', 1, 3)
	cut(2)
	pseudo_instr2(50, 21, 0)
	get_x_variable(2, 0)
	put_y_value(1, 0)
	put_structure(2, 1)
	set_constant('delay_until')
	set_x_value(2)
	set_y_value(0)
	deallocate
	execute_predicate('delay', 2)

$10:
	get_structure('bound', 1, 0)
	unify_void(1)
	get_x_variable(0, 1)
	execute_predicate('call_predicate', 1)

$11:
	get_structure('$bound', 1, 0)
	unify_x_variable(0)
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('call_predicate', 1, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$12:
	get_x_variable(2, 0)
	get_x_variable(3, 1)
	put_x_value(2, 0)
	get_structure('$bound', 1, 0)
	unify_x_variable(0)
	get_structure('bound', 1, 0)
	unify_x_variable(0)
	put_structure(2, 1)
	set_constant('delay_until')
	set_x_value(2)
	set_x_value(3)
	execute_predicate('delay', 2)

$13:
	get_structure('identical_or_apart', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	put_x_value(2, 1)
	call_predicate('identical_or_apart', 2, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$14:
	get_structure('identical_or_apart', 2, 0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_x_variable(4, 1)
	put_x_variable(1, 5)
	get_list(5)
	unify_x_value(2)
	unify_x_ref(5)
	get_list(5)
	unify_x_value(3)
	unify_constant('[]')
	pseudo_instr2(67, 1, 0)
	put_structure(2, 5)
	set_constant('identical_or_apart')
	set_x_value(2)
	set_x_value(3)
	put_structure(2, 1)
	set_constant('delay_until')
	set_x_value(5)
	set_x_value(4)
	execute_predicate('$delay_disjunctive_list', 2)
end('delay_until'/2):



'identical_or_apart/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_level(0)
	call_predicate('thaw_vars', 1, 3)
	put_y_value(1, 0)
	call_predicate('thaw_vars', 1, 3)
	put_y_value(2, 0)
	get_y_value(1, 0)
	cut(0)
	fail

$2:
	proceed
end('identical_or_apart/2$0'/2):



'identical_or_apart'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(110, 0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('identical_or_apart/2$0', 2)
end('identical_or_apart'/2):



'$delay_disjunctive_list'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$delay_disjunctive_list_link', 2, 2)
	put_structure(1, 0)
	set_constant('nonvar')
	set_y_value(0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('delay_until', 2)
end('$delay_disjunctive_list'/2):



'$delay_disjunctive_list_link'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(2)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	put_structure(1, 0)
	set_constant('bound')
	set_x_value(2)
	put_structure(2, 1)
	set_constant('=')
	set_y_value(0)
	set_constant('wakeup')
	call_predicate('delay_until', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$delay_disjunctive_list_link', 2)
end('$delay_disjunctive_list_link'/2):



'$delay_until_or'/3:

	switch_on_term(0, $9, $8, $8, $5, $8, $8)

$5:
	switch_on_structure(0, 4, ['$default':$8, '$'/0:$6, 'or'/2:$7])

$6:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$8:
	try(3, $3)
	trust($4)

$9:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure('or', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_structure('or', 2, 1)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(0, 2)
	neck_cut
	put_x_value(3, 1)
	call_predicate('$delay_until_or', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$delay_until_or', 3)

$2:
	get_structure('or', 2, 0)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_x_variable(0, 1)
	get_y_variable(0, 2)
	neck_cut
	put_structure(2, 1)
	set_constant('=')
	set_y_value(0)
	set_constant('wakeup')
	call_predicate('delay_until', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$delay_until_or', 3)

$3:
	get_structure('or', 2, 1)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(0, 2)
	neck_cut
	put_structure(2, 1)
	set_constant('=')
	set_y_value(0)
	set_constant('wakeup')
	call_predicate('delay_until', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$delay_until_or', 3)

$4:
	allocate(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_structure(2, 1)
	set_constant('=')
	set_y_value(0)
	set_constant('wakeup')
	call_predicate('delay_until', 2, 2)
	put_y_value(1, 0)
	put_structure(2, 1)
	set_constant('=')
	set_y_value(0)
	set_constant('wakeup')
	deallocate
	execute_predicate('delay_until', 2)
end('$delay_until_or'/3):



'retry_var_delays/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('$retry_make_progress', 1)
	pseudo_instr2(4, 1, 0)
	put_constant('fail', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('retry_var_delays', 1)
end('retry_var_delays/1$0'/1):



'retry_var_delays'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(1, 20)
	neck_cut
	put_constant('$retry_make_progress', 0)
	put_constant('fail', 1)
	pseudo_instr2(3, 0, 1)
	pseudo_instr2(49, 20, 0)
	put_constant('all', 1)
	call_predicate('$do_delay_list', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('retry_var_delays/1$0', 1)

$2:
	proceed
end('retry_var_delays'/1):



'get_var_delays'/2:


$1:
	pseudo_instr2(49, 0, 2)
	get_x_variable(0, 2)
	execute_predicate('$get_var_delays_aux', 2)
end('get_var_delays'/2):



'$get_var_delays_aux'/2:

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
	get_structure(',', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_list(1)
	unify_x_value(3)
	unify_x_variable(1)
	pseudo_instr1(41, 2)
	neck_cut
	execute_predicate('$get_var_delays_aux', 2)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$get_var_delays_aux', 2)
end('$get_var_delays_aux'/2):



