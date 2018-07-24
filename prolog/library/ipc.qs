'ipc_send'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('$full_handle', 2, 2)
	pseudo_instr1(90, 0)
	get_x_variable(2, 0)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 3)
	deallocate
	execute_predicate('$ipc_send1', 4)
end('ipc_send'/2):



'ipc_send'/3:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	pseudo_instr1(50, 21)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$full_handle', 2, 3)
	pseudo_instr1(90, 0)
	get_x_variable(2, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$ipc_send1', 4)
end('ipc_send'/3):



'$ipc_send1/4$0'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'true':$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	put_constant('true', 4)
	get_x_value(0, 4)
	neck_cut
	pseudo_instr1(53, 1)
	put_structure(3, 0)
	set_constant('p2pmsg')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	execute_predicate('$pedro_p2p', 1)

$2:
	put_structure(3, 0)
	set_constant('p2pmsg')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	execute_predicate('$pedro_p2p', 1)
end('$ipc_send1/4$0'/4):



'$ipc_send1'/4:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_x_variable(0, 3)
	put_y_variable(0, 1)
	call_predicate('$ipc_options', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$ipc_send1/4$0', 4)
end('$ipc_send1'/4):



'$ipc_options'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('remember_names', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed
end('$ipc_options'/2):



'ipc_recv'/1:


$1:
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_constant('[]', 3)
	execute_predicate('ipc_recv', 4)
end('ipc_recv'/1):



'ipc_recv'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('ipc_recv', 3)
end('ipc_recv'/2):



'ipc_recv/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$is_timeout', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('ipc_recv/3$0'/1):



'ipc_recv'/3:


$1:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_x_variable(0, 2)
	get_y_level(0)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	call_predicate('$ipc_decode_peek_options', 3, 7)
	put_y_value(4, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	call_predicate('$ipc_peek', 5, 5)
	put_y_value(4, 0)
	call_predicate('ipc_recv/3$0', 1, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$same_handle_from', 2, 2)
	pseudo_instr1(55, 21)
	cut(0)
	deallocate
	proceed
end('ipc_recv'/3):



'ipc_peek'/1:


$1:
	put_x_variable(1, 1)
	put_constant('[]', 2)
	execute_predicate('ipc_peek', 3)
end('ipc_peek'/1):



'ipc_peek'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('ipc_peek', 3)
end('ipc_peek'/2):



'ipc_peek/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$is_timeout', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('ipc_peek/3$0'/1):



'ipc_peek'/3:


$1:
	allocate(5)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_x_variable(0, 2)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	put_y_variable(3, 2)
	call_predicate('$ipc_decode_peek_options', 3, 5)
	put_y_value(2, 0)
	put_x_variable(1, 1)
	put_y_value(0, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	call_predicate('$ipc_peek', 5, 3)
	put_y_value(2, 0)
	call_predicate('ipc_peek/3$0', 1, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$same_handle_from', 2)
end('ipc_peek'/3):



'$ipc_peek/5$0'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'timeout':$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	put_constant('timeout', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('$$ipc_timeout$$', 0)
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr4(18, 4, 0, 5, 3)
	get_x_variable(0, 4)
	get_x_value(2, 5)
	pseudo_instr2(65, 0, 2)
	get_x_value(1, 0)
	pseudo_instr1(52, 2)
	proceed
end('$ipc_peek/5$0'/4):



'$ipc_peek'/5:


$1:
	allocate(7)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(6, 3)
	get_y_variable(0, 4)
	pseudo_instr1(113, 0)
	get_y_variable(5, 0)
	pseudo_instr1(101, 0)
	put_y_value(6, 1)
	put_y_variable(4, 2)
	call_predicate('$ipc_first_timeout', 3, 7)
	put_y_value(4, 0)
	put_y_value(2, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	call_predicate('$ipc_peek1', 4, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$ipc_peek/5$0', 4)
end('$ipc_peek'/5):



'$ipc_first_timeout'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr3(68, 0, 1, 3)
	get_x_value(2, 3)
	neck_cut
	proceed

$2:
	get_constant('timeout', 2)
	proceed
end('$ipc_first_timeout'/3):



'$ipc_next_timeout/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_x_variable(1, 2)
	get_structure('$', 1, 2)
	unify_constant('$')
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('$ipc_next_timeout/3$0'/1):



'$ipc_next_timeout'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr3(42, 0, 3, 2)
	get_x_value(1, 3)
	neck_cut
	proceed

$2:
	get_constant('timeout', 1)
	execute_predicate('$ipc_next_timeout/3$0', 1)
end('$ipc_next_timeout'/3):



'$ipc_peek1/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_variable(4, 2)
	call_predicate('$ipc_peek_get_delay', 3, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	put_y_value(4, 2)
	call_predicate('$ipc_next_timeout', 3, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$ipc_peek1', 4)
end('$ipc_peek1/4$0'/4):



'$ipc_peek1'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'timeout':$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	get_constant('timeout', 0)
	get_constant('timeout', 1)
	neck_cut
	proceed

$2:
	execute_predicate('$ipc_peek1/4$0', 4)
end('$ipc_peek1'/4):



'$ipc_peek_get_delay/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_integer(0, 2)
	pseudo_instr2(1, 0, 2)
	neck_cut
	put_integer(0, 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_value(1, 0)
	proceed
end('$ipc_peek_get_delay/3$0'/2):



'$ipc_peek_get_delay'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'block':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_constant('block', 0)
	get_constant('block', 2)
	neck_cut
	proceed

$2:
	get_x_variable(3, 1)
	get_x_variable(1, 2)
	pseudo_instr1(113, 2)
	put_x_variable(5, 6)
	get_structure('-', 2, 6)
	unify_x_value(0)
	unify_x_value(2)
	pseudo_instr3(2, 5, 3, 4)
	get_x_variable(0, 4)
	execute_predicate('$ipc_peek_get_delay/3$0', 2)
end('$ipc_peek_get_delay'/3):



'$ipc_decode_peek_options/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('block', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$ipc_decode_peek_options/3$0'/1):



'$ipc_decode_peek_options/3$1'/1:

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
end('$ipc_decode_peek_options/3$1'/1):



'$ipc_decode_peek_options/3$2/3$0'/3:

	switch_on_term(0, $9, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, 'timeout'/1:$7, 'remember_names'/1:$8])

$6:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(3, $1)
	retry($2)
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
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	put_x_value(3, 1)
	get_structure('timeout', 1, 1)
	unify_x_value(0)
	execute_predicate('number', 1)

$2:
	get_structure('timeout', 1, 0)
	unify_constant('poll')
	put_integer(0, 0)
	get_x_value(1, 0)
	proceed

$3:
	get_structure('remember_names', 1, 0)
	unify_x_value(2)
	proceed

$4:
	fail
end('$ipc_decode_peek_options/3$2/3$0'/3):



'$ipc_decode_peek_options/3$2'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	execute_predicate('$ipc_decode_peek_options/3$2/3$0', 3)
end('$ipc_decode_peek_options/3$2'/3):



'$ipc_decode_peek_options'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_variable(0, 2)
	call_predicate('$ipc_decode_peek_options/3$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$ipc_decode_peek_options/3$1', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('$ipc_decode_peek_options/3$2', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$ipc_decode_peek_options', 3)
end('$ipc_decode_peek_options'/3):



'broadcast'/1:


$1:
	pseudo_instr1(90, 1)
	put_x_variable(2, 3)
	get_structure('p2pmsg', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	pseudo_instr1(104, 2)
	proceed
end('broadcast'/1):



