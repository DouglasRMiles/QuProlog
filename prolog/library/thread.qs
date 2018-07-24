'$thread_id'/1:


$1:
	pseudo_instr1(3, 0)
	proceed
end('$thread_id'/1):



'thread_symbol'/1:


$1:
	pseudo_instr1(68, 1)
	pseudo_instr2(82, 1, 0)
	proceed
end('thread_symbol'/1):



'thread_fork'/2:


$1:
	put_constant('fail', 2)
	put_constant('[]', 3)
	execute_predicate('thread_fork', 4)
end('thread_fork'/2):



'thread_fork/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_list(1)
	set_constant('[]')
	set_constant('[]')
	put_list(2)
	set_constant('')
	set_x_value(1)
	put_list(3)
	set_constant('self')
	set_x_value(2)
	put_list(1)
	set_constant('pedro')
	set_x_value(3)
	call_predicate('member', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('thread_fork/3$0'/1):



'thread_fork'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(2, 20)
	pseudo_instr1(1, 22)
	get_y_level(3)
	put_y_value(0, 0)
	call_predicate('thread_fork/3$0', 1, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('[]', 3)
	deallocate
	execute_predicate('thread_fork', 4)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('thread_fork')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('comp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('list')
	put_structure(3, 4)
	set_constant('thread_fork')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('comp')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('thread_fork')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 2)
	put_constant('fail', 2)
	execute_predicate('thread_fork', 4)
end('thread_fork'/3):



'thread_fork'/4:


$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(4, 3)
	put_y_variable(0, 19)
	call_predicate('$thread_fork_ok', 1, 5)
	put_y_value(4, 0)
	put_y_value(0, 1)
	call_predicate('$thread_decode_sizes', 2, 4)
	pseudo_instr4(20, 23, 22, 21, 20)
	deallocate
	proceed
end('thread_fork'/4):



'$thread_fork_ok'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	put_constant('self', 1)
	pseudo_instr2(133, 0, 1)
	put_constant('', 1)
	pseudo_instr2(133, 0, 1)
	put_constant('pedro', 1)
	pseudo_instr2(133, 0, 1)
	pseudo_instr1(2, 0)
	proceed
end('$thread_fork_ok'/1):



'thread_suspend'/0:


$1:
	pseudo_instr1(68, 0)
	pseudo_instr1(69, 0)
	proceed
end('thread_suspend'/0):



'thread_wait'/0:


$1:
	put_constant('[]', 0)
	execute_predicate('thread_wait', 1)
end('thread_wait'/0):



'thread_wait'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(3)
	get_y_level(2)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$thread_wait_conditions', 3, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$thread_wait_aux', 2)

$2:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('thread_wait')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('list')
	put_structure(1, 2)
	set_constant('thread_wait')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('list', 3)
	execute_predicate('type_exception', 4)
end('thread_wait'/1):



'$thread_wait_aux/2$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'false':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('false', 2)
	get_x_value(0, 2)
	neck_cut
	pseudo_instr1(71, 1)
	proceed

$2:
	put_constant('[]', 2)
	put_integer(-1, 3)
	pseudo_instr4(21, 2, 1, 3, 0)
	pseudo_instr1(110, 0)
	pseudo_instr1(109, 0)
	proceed
end('$thread_wait_aux/2$0'/2):



'$thread_wait_aux'/2:


$1:
	execute_predicate('$thread_wait_aux/2$0', 2)
end('$thread_wait_aux'/2):



'$thread_wait_conditions/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('true', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$thread_wait_conditions/3$0'/1):



'$thread_wait_conditions/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_integer(-1, 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$thread_wait_conditions/3$1'/1):



'$thread_wait_conditions/3$2/3$0'/3:

	switch_on_term(0, $8, $3, $3, $4, $3, $3)

$4:
	switch_on_structure(0, 8, ['$default':$3, '$'/0:$5, 'db'/1:$6, 'timeout'/1:$7])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$6:
	try(3, $1)
	trust($3)

$7:
	try(3, $2)
	trust($3)

$8:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_structure('db', 1, 0)
	unify_x_value(1)
	proceed

$2:
	get_structure('timeout', 1, 0)
	unify_x_value(2)
	proceed

$3:
	fail
end('$thread_wait_conditions/3$2/3$0'/3):



'$thread_wait_conditions/3$2'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	execute_predicate('$thread_wait_conditions/3$2/3$0', 3)
end('$thread_wait_conditions/3$2'/3):



'$thread_wait_conditions'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_variable(0, 2)
	neck_cut
	call_predicate('$thread_wait_conditions/3$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$thread_wait_conditions/3$1', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	neck_cut
	get_y_level(3)
	call_predicate('$thread_wait_conditions/3$2', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$thread_wait_conditions', 3)
end('$thread_wait_conditions'/3):



'thread_wait_on_goal'/1:


$1:
	put_constant('[]', 1)
	execute_predicate('thread_wait_on_goal', 2)
end('thread_wait_on_goal'/1):



'thread_wait_on_goal'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_level(5)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	put_y_variable(1, 3)
	put_y_variable(0, 4)
	call_predicate('$process_twg_options', 5, 6)
	cut(5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$thread_wait_on_goal', 5)

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('thread_wait_on_goal')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('goal')
	put_structure(1, 3)
	set_constant('@')
	set_constant('list')
	put_structure(2, 2)
	set_constant('thread_wait_on_goal')
	set_x_value(1)
	set_x_value(3)
	put_integer(2, 1)
	put_constant('list', 3)
	execute_predicate('type_exception', 4)
end('thread_wait_on_goal'/2):



'$process_twg_options/5$0'/1:

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
end('$process_twg_options/5$0'/1):



'$process_twg_options/5$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_integer(-1, 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$process_twg_options/5$1'/1):



'$process_twg_options/5$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_integer(-1, 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$process_twg_options/5$2'/1):



'$process_twg_options'/5:

	switch_on_term(0, $8, 'fail', $7, 'fail', 'fail', $1)

$7:
	try(5, $2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$8:
	try(5, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	call_predicate('$process_twg_options/5$0', 1, 2)
	put_y_value(1, 0)
	call_predicate('$process_twg_options/5$1', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$process_twg_options/5$2', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	unify_void(1)
	pseudo_instr1(1, 0)
	neck_cut
	fail

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(3)
	get_structure('wait_preds', 1, 0)
	unify_y_variable(4)
	get_y_value(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	neck_cut
	put_y_value(4, 0)
	put_x_variable(1, 1)
	call_predicate('$check_preds', 2, 5)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$process_twg_options', 5)

$4:
	get_list(0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(2)
	get_structure('wait_preds', 2, 0)
	unify_y_variable(4)
	unify_y_variable(3)
	get_y_value(4, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_value(3, 4)
	neck_cut
	put_y_value(4, 0)
	put_x_variable(1, 1)
	call_predicate('$check_preds', 2, 5)
	pseudo_instr1(1, 23)
	put_y_value(2, 0)
	put_y_value(4, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_y_value(3, 4)
	deallocate
	execute_predicate('$process_twg_options', 5)

$5:
	get_list(0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(3)
	get_structure('wait_for', 1, 0)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_y_value(4, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	neck_cut
	put_y_value(4, 0)
	call_predicate('number', 1, 5)
	put_integer(0, 0)
	pseudo_instr2(2, 0, 24)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(4, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$process_twg_options', 5)

$6:
	get_list(0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(3)
	get_structure('retry_every', 1, 0)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_value(4, 3)
	get_y_variable(0, 4)
	neck_cut
	put_y_value(4, 0)
	call_predicate('number', 1, 5)
	put_integer(0, 0)
	pseudo_instr2(2, 0, 24)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(4, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$process_twg_options', 5)
end('$process_twg_options'/5):



'$check_preds'/2:

	switch_on_term(0, $9, 'fail', $8, 'fail', 'fail', $1)

$8:
	try(2, $2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$9:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('*', 2, 2)
	unify_x_ref(2)
	unify_void(1)
	get_structure('/', 2, 2)
	unify_x_ref(2)
	unify_x_variable(3)
	get_structure('-', 1, 2)
	unify_x_variable(2)
	neck_cut
	put_constant('true', 4)
	get_x_value(1, 4)
	pseudo_instr3(33, 2, 3, 4)
	put_integer(1, 2)
	get_x_value(4, 2)
	execute_predicate('$check_preds', 2)

$3:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('*', 2, 2)
	unify_x_ref(2)
	unify_void(1)
	get_structure('/', 2, 2)
	unify_x_ref(2)
	unify_x_variable(3)
	get_structure('+', 1, 2)
	unify_x_variable(2)
	neck_cut
	put_constant('true', 4)
	get_x_value(1, 4)
	pseudo_instr3(33, 2, 3, 4)
	put_integer(1, 2)
	get_x_value(4, 2)
	execute_predicate('$check_preds', 2)

$4:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('*', 2, 2)
	unify_x_ref(2)
	unify_void(1)
	get_structure('/', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	neck_cut
	put_constant('true', 4)
	get_x_value(1, 4)
	pseudo_instr3(33, 2, 3, 4)
	put_integer(1, 2)
	get_x_value(4, 2)
	execute_predicate('$check_preds', 2)

$5:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('/', 2, 2)
	unify_x_ref(2)
	unify_x_variable(3)
	get_structure('-', 1, 2)
	unify_x_variable(2)
	neck_cut
	put_constant('fail', 4)
	get_x_value(1, 4)
	pseudo_instr3(33, 2, 3, 4)
	put_integer(1, 2)
	get_x_value(4, 2)
	execute_predicate('$check_preds', 2)

$6:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('/', 2, 2)
	unify_x_ref(2)
	unify_x_variable(3)
	get_structure('+', 1, 2)
	unify_x_variable(2)
	neck_cut
	put_constant('fail', 4)
	get_x_value(1, 4)
	pseudo_instr3(33, 2, 3, 4)
	put_integer(1, 2)
	get_x_value(4, 2)
	execute_predicate('$check_preds', 2)

$7:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('/', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	neck_cut
	put_constant('fail', 4)
	get_x_value(1, 4)
	pseudo_instr3(33, 2, 3, 4)
	put_integer(1, 2)
	get_x_value(4, 2)
	execute_predicate('$check_preds', 2)
end('$check_preds'/2):



'$thread_wait_on_goal/5$0'/4:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, 'true':$5])

$5:
	try(4, $1)
	retry($2)
	trust($3)

$6:
	try(4, $2)
	trust($3)

$7:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	put_constant('true', 2)
	get_x_value(0, 2)
	neck_cut
	pseudo_instr1(109, 1)
	proceed

$2:
	allocate(2)
	get_y_variable(0, 1)
	get_x_variable(0, 2)
	get_x_variable(2, 3)
	get_y_level(1)
	call_predicate('$_wait_', 3, 2)
	cut(1)
	pseudo_instr1(109, 20)
	deallocate
	proceed

$3:
	pseudo_instr1(109, 1)
	fail
end('$thread_wait_on_goal/5$0'/4):



'$thread_wait_on_goal'/5:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 4)
	put_structure(6, 0)
	set_constant('$thread_wait_on_goal_atomic')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_y_variable(1)
	set_y_value(3)
	set_y_variable(0)
	call_predicate('thread_atomic_goal', 1, 4)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$thread_wait_on_goal/5$0', 4)
end('$thread_wait_on_goal'/5):



'$thread_wait_on_goal_atomic'/6:


$1:
	get_x_variable(6, 1)
	get_x_variable(7, 2)
	get_x_variable(1, 4)
	get_x_variable(2, 5)
	pseudo_instr4(21, 0, 6, 7, 4)
	get_x_value(3, 4)
	execute_predicate('$thread_wait_on_goal_atomic_aux', 3)
end('$thread_wait_on_goal_atomic'/6):



'$thread_wait_on_goal_atomic_aux'/3:

	switch_on_term(0, $5, $4, $5, $4, $4, $4)

$4:
	try(3, $2)
	trust($3)

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('fail', 2)
	get_list(0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('*', 2, 0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('/', 2, 0)
	unify_void(2)
	neck_cut
	proceed

$2:
	get_constant('true', 2)
	get_x_variable(0, 1)
	allocate(1)
	get_y_level(0)
	call_predicate('call', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_constant('fail', 2)
	proceed
end('$thread_wait_on_goal_atomic_aux'/3):



'$_wait_/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(110, 0)
	neck_cut
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	fail
end('$_wait_/3$0'/2):



'$_wait_'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_level(0)
	call_predicate('repeat', 0, 4)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$_wait_/3$0', 2, 4)
	put_structure(3, 0)
	set_constant('$_wait_atomic')
	set_y_value(3)
	set_y_value(2)
	set_y_value(1)
	call_predicate('thread_atomic_goal', 1, 1)
	cut(0)
	deallocate
	proceed
end('$_wait_'/3):



'$_wait_atomic'/3:


$1:
	pseudo_instr1(111, 1)
	pseudo_instr2(128, 1, 3)
	get_x_value(2, 3)
	execute_predicate('call', 1)
end('$_wait_atomic'/3):



'get_predicate_timestamps'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('/', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_list(1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure('*', 2, 4)
	unify_x_ref(4)
	unify_x_variable(5)
	get_structure('/', 2, 4)
	unify_x_value(2)
	unify_x_value(3)
	pseudo_instr3(66, 2, 3, 4)
	get_x_value(5, 4)
	execute_predicate('get_predicate_timestamps', 2)
end('get_predicate_timestamps'/2):



'update_predicate_timestamps'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('*', 2, 2)
	unify_x_ref(2)
	unify_void(1)
	get_structure('/', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_list(1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure('*', 2, 4)
	unify_x_ref(4)
	unify_x_variable(5)
	get_structure('/', 2, 4)
	unify_x_value(2)
	unify_x_value(3)
	pseudo_instr3(66, 2, 3, 4)
	get_x_value(5, 4)
	execute_predicate('update_predicate_timestamps', 2)
end('update_predicate_timestamps'/2):



'thread_sleep/1$0'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('thread_sleep')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('thread_sleep')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('number', 1, 2)
	cut(1)
	pseudo_instr1(71, 20)
	deallocate
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('thread_sleep')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('number')
	put_structure(1, 2)
	set_constant('thread_sleep')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('number', 3)
	execute_predicate('type_exception', 4)
end('thread_sleep/1$0'/1):



'thread_sleep'/1:


$1:
	execute_predicate('thread_sleep/1$0', 1)
end('thread_sleep'/1):



'thread_sleep_until/1$0'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(1, 0)
	set_constant('thread_sleep_until')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('thread_sleep_until')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	pseudo_instr2(1, 1, 0)
	neck_cut
	pseudo_instr3(3, 0, 1, 2)
	get_x_variable(0, 2)
	pseudo_instr1(71, 0)
	proceed

$3:
	get_x_variable(2, 0)
	put_structure(1, 0)
	set_constant('thread_sleep_until')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('thread_sleep_until')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('thread_sleep_until/1$0'/2):



'thread_sleep_until'/1:


$1:
	pseudo_instr1(59, 1)
	execute_predicate('thread_sleep_until/1$0', 2)
end('thread_sleep_until'/1):



'thread_defaults'/1:


$1:
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('heap_size', 1, 0)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('scratchpad_size', 1, 1)
	unify_x_variable(1)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('binding_trail_size', 1, 2)
	unify_x_variable(2)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('other_trail_size', 1, 3)
	unify_x_variable(3)
	get_list(4)
	unify_x_ref(4)
	unify_x_ref(5)
	get_structure('env_size', 1, 4)
	unify_x_variable(4)
	get_list(5)
	unify_x_ref(5)
	unify_x_ref(6)
	get_structure('choice_size', 1, 5)
	unify_x_variable(5)
	get_list(6)
	unify_x_ref(6)
	unify_x_ref(7)
	get_structure('name_table_size', 1, 6)
	unify_x_variable(6)
	get_list(7)
	unify_x_ref(7)
	unify_constant('[]')
	get_structure('ip_table_size', 1, 7)
	unify_x_variable(7)
	pseudo_instr1(72, 8)
	get_structure('$thread_defaults', 8, 8)
	unify_x_value(0)
	unify_x_value(1)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(6)
	unify_x_value(7)
	proceed
end('thread_defaults'/1):



'thread_set_defaults'/1:


$1:
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$thread_decode_sizes', 2, 1)
	pseudo_instr1(73, 20)
	deallocate
	proceed
end('thread_set_defaults'/1):



'$thread_decode_sizes'/2:


$1:
	put_x_value(1, 2)
	get_structure('$thread_defaults', 8, 2)
	unify_void(8)
	execute_predicate('$thread_decode_sizes1', 2)
end('$thread_decode_sizes'/2):



'$thread_decode_sizes1'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	pseudo_instr1(72, 0)
	get_x_variable(2, 0)
	put_integer(8, 0)
	execute_predicate('$try_unify_thread_args', 3)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(1)
	get_y_variable(0, 1)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$thread_arg_num', 3, 4)
	pseudo_instr3(1, 23, 20, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$thread_decode_sizes1', 2)
end('$thread_decode_sizes1'/2):



'$try_unify_thread_args/3$0/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$try_unify_thread_args/3$0/2$0'/2):



'$try_unify_thread_args/3$0'/2:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$try_unify_thread_args/3$0/2$0', 2, 1)
	cut(0)
	deallocate
	proceed
end('$try_unify_thread_args/3$0'/2):



'$try_unify_thread_args'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr3(1, 22, 21, 0)
	get_x_variable(1, 0)
	pseudo_instr3(1, 22, 20, 0)
	call_predicate('$try_unify_thread_args/3$0', 2, 3)
	pseudo_instr2(70, 22, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$try_unify_thread_args', 3)
end('$try_unify_thread_args'/3):



'$thread_arg_num'/3:

	switch_on_term(0, $11, 'fail', 'fail', $9, 'fail', 'fail')

$9:
	switch_on_structure(0, 32, ['$default':'fail', '$'/0:$10, 'heap_size'/1:$1, 'scratchpad_size'/1:$2, 'binding_trail_size'/1:$3, 'other_trail_size'/1:$4, 'env_size'/1:$5, 'choice_size'/1:$6, 'name_table_size'/1:$7, 'ip_table_size'/1:$8])

$10:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$11:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_integer(1, 1)
	get_structure('heap_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$2:
	get_integer(2, 1)
	get_structure('scratchpad_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$3:
	get_integer(3, 1)
	get_structure('binding_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$4:
	get_integer(4, 1)
	get_structure('other_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$5:
	get_integer(5, 1)
	get_structure('env_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$6:
	get_integer(6, 1)
	get_structure('choice_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$7:
	get_integer(7, 1)
	get_structure('name_table_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$8:
	get_integer(8, 1)
	get_structure('ip_table_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed
end('$thread_arg_num'/3):



'$thread_start/0$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_structure(1, 1)
	set_constant('call')
	set_x_value(0)
	put_structure(2, 0)
	set_constant(',')
	set_constant('$initialise_system_non_backtrackable')
	set_x_value(1)
	put_x_variable(3, 1)
	put_structure(1, 2)
	set_constant('$thread_exception')
	set_x_value(3)
	execute_predicate('catch', 3)

$2:
	proceed
end('$thread_start/0$0'/1):



'$thread_start'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(64, 0)
	neck_cut
	allocate(0)
	call_predicate('$thread_start/0$0', 1, 0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	pseudo_instr0(8)
	deallocate
	proceed

$2:
	allocate(0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	pseudo_instr0(8)
	deallocate
	proceed
end('$thread_start'/0):



'$thread_exception'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('Uncaught throw in thread: ', 0)
	call_predicate('error', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('errornl', 1)
end('$thread_exception'/1):



'$handle_push_goal'/2:


$1:
	get_x_variable(2, 1)
	put_x_value(0, 1)
	put_constant('$handle_push_goal_aux', 0)
	execute_predicate('call_predicate', 3)
end('$handle_push_goal'/2):



'$handle_push_goal_aux'/2:


$1:
	allocate(1)
	get_y_variable(0, 1)
	call_predicate('call_predicate', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('$handle_push_goal_aux'/2):



'$call_timer_goals'/1:


$1:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('$call_timer_goals1')
	set_x_value(1)
	execute_predicate('call_predicate', 1)
end('$call_timer_goals'/1):



'$call_timer_goals1'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('$call_timer_goals_aux')
	set_x_value(1)
	put_x_variable(3, 1)
	put_structure(1, 2)
	set_constant('$call_timer_goals_handler')
	set_x_value(3)
	allocate(0)
	call_predicate('catch', 3, 0)
	fail

$2:
	pseudo_instr0(7)
	proceed
end('$call_timer_goals1'/1):



'$call_timer_goals_aux/1$0'/1:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call_predicate', 1, 1)
	cut(0)
	deallocate
	proceed
end('$call_timer_goals_aux/1$0'/1):



'$call_timer_goals_aux'/1:


$1:
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 0)
	call_predicate('member', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$call_timer_goals_aux/1$0', 1)
end('$call_timer_goals_aux'/1):



'$call_timer_goals_handler'/1:

	try(1, $1)
	trust($2)

$1:
	execute_predicate('$interpreter_catch', 1)

$2:
	pseudo_instr0(8)
	proceed
end('$call_timer_goals_handler'/1):



'schedule_threads_now'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(114, 0)
	neck_cut
	proceed

$2:
	put_structure(1, 1)
	set_constant('schedule_threads_now')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('context_exception')
	set_constant('fatal')
	set_x_value(1)
	set_constant('Calling schedule_threads_now recursively')
	execute_predicate('exception', 1)
end('schedule_threads_now'/1):



