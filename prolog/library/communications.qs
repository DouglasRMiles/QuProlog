'??'/2:


$1:
	proceed
end('??'/2):



'->>'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('pedro', 2)
	pseudo_instr2(110, 1, 2)
	neck_cut
	execute_predicate('pedro_notify', 1)

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('$full_handle', 2, 2)
	pseudo_instr1(90, 0)
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('p2pmsg')
	set_y_value(0)
	set_x_value(1)
	set_y_value(1)
	deallocate
	execute_predicate('$pedro_p2p', 1)
end('->>'/2):



'$same_host/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('localhost', 1)
	pseudo_instr2(110, 0, 1)
	proceed

$2:
	put_constant('LOCALHOST', 1)
	pseudo_instr2(110, 0, 1)
	proceed
end('$same_host/2$0'/1):



'$same_host/2$1'/2:

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
	put_constant('127.0.0.1', 0)
	execute_predicate('$same_host', 2)

$2:
	execute_predicate('$same_host', 2)
end('$same_host/2$1'/2):



'$same_host/2$2'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('localhost', 1)
	pseudo_instr2(110, 0, 1)
	proceed

$2:
	put_constant('LOCALHOST', 1)
	pseudo_instr2(110, 0, 1)
	proceed
end('$same_host/2$2'/1):



'$same_host/2$3'/2:

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
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('localhost', 1)
	get_x_value(2, 1)
	neck_cut
	put_constant('127.0.0.1', 1)
	execute_predicate('$same_host', 2)

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_value(2, 1)
	execute_predicate('$same_host', 2)
end('$same_host/2$3'/2):



'$same_host'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('$same_host/2$0', 1, 2)
	cut(1)
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_host/2$1', 2)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	get_y_level(1)
	call_predicate('$same_host/2$2', 1, 2)
	cut(1)
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_host/2$3', 2)

$3:
	get_x_value(0, 1)
	neck_cut
	proceed

$4:
	pseudo_instr2(79, 0, 2)
	get_x_variable(0, 2)
	pseudo_instr2(79, 1, 2)
	get_x_value(0, 2)
	proceed
end('$same_host'/2):



'same_handle'/2:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, 'pedro':$5])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	trust($3)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr2(67, 2, 0)
	get_list(0)
	unify_void(2)
	neck_cut
	put_structure(2, 0)
	set_constant('same_handle')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('term')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(2, 3)
	set_constant('same_handle')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_constant('pedro', 0)
	get_constant('pedro', 1)
	neck_cut
	proceed

$3:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$full_handle', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$full_handle', 2)
end('same_handle'/2):



'$full_handle'/2:

	switch_on_term(0, $14, $13, $13, $9, $13, $13)

$9:
	switch_on_structure(0, 8, ['$default':$13, '$'/0:$10, '@'/2:$11, ':'/2:$12])

$10:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$11:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($7)
	trust($8)

$12:
	try(2, $1)
	retry($2)
	retry($4)
	retry($5)
	trust($6)

$13:
	try(2, $1)
	retry($2)
	trust($4)

$14:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	put_constant('pedro', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	put_constant('self', 2)
	pseudo_instr2(110, 0, 2)
	neck_cut
	pseudo_instr1(90, 0)
	get_x_value(1, 0)
	proceed

$3:
	get_structure('@', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_structure('@', 2, 1)
	unify_x_ref(3)
	unify_x_variable(1)
	get_structure(':', 2, 3)
	unify_void(1)
	unify_x_value(2)
	pseudo_instr1(1, 2)
	neck_cut
	execute_predicate('$same_host', 2)

$4:
	get_structure('@', 2, 1)
	unify_x_ref(1)
	unify_x_variable(2)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_variable(1)
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(2)
	get_structure(':', 2, 0)
	unify_void(1)
	unify_x_value(1)
	proceed

$5:
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('@', 2, 1)
	unify_x_ref(1)
	unify_x_variable(3)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	pseudo_instr1(1, 0)
	neck_cut
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(3)
	get_structure(':', 2, 0)
	unify_void(2)
	proceed

$6:
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('@', 2, 1)
	unify_x_ref(1)
	unify_x_variable(3)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(3)
	get_structure(':', 2, 0)
	unify_void(2)
	proceed

$7:
	get_structure('@', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_structure('@', 2, 1)
	unify_x_value(2)
	unify_x_variable(1)
	pseudo_instr1(2, 2)
	neck_cut
	execute_predicate('$same_host', 2)

$8:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('@', 2, 1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure(':', 2, 4)
	unify_x_value(2)
	unify_x_value(3)
	execute_predicate('$same_host', 2)
end('$full_handle'/2):



'$same_handle_from'/2:

	switch_on_term(0, $14, $13, $13, $8, $13, $11)

$8:
	switch_on_structure(0, 4, ['$default':$13, '$'/0:$9, '@'/2:$10])

$9:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$10:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$11:
	switch_on_constant(0, 4, ['$default':$13, 'pedro':$12])

$12:
	try(2, $1)
	retry($2)
	trust($3)

$13:
	try(2, $1)
	trust($3)

$14:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	get_x_value(0, 1)
	proceed

$2:
	get_constant('pedro', 0)
	neck_cut
	put_constant('pedro', 0)
	get_x_value(1, 0)
	proceed

$3:
	get_constant('self', 1)
	pseudo_instr1(90, 1)
	get_x_value(0, 1)
	proceed

$4:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_x_value(2, 1)
	pseudo_instr1(2, 2)
	neck_cut
	pseudo_instr1(90, 1)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_void(1)
	unify_x_value(3)
	execute_predicate('$same_host', 2)

$5:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure(':', 2, 1)
	unify_x_value(2)
	unify_x_value(3)
	pseudo_instr1(90, 1)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_void(2)
	execute_predicate('$same_host', 2)

$6:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_constant('thread0')
	unify_x_variable(2)
	get_structure('@', 2, 1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$same_host', 2)

$7:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('@', 2, 1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure(':', 2, 4)
	unify_x_value(2)
	unify_x_value(3)
	execute_predicate('$same_host', 2)
end('$same_handle_from'/2):



'<<-'/2:


$1:
	allocate(6)
	get_y_variable(1, 0)
	get_y_variable(3, 1)
	get_y_level(4)
	put_y_variable(0, 0)
	put_y_variable(5, 1)
	put_y_variable(2, 2)
	put_constant('block', 3)
	put_constant('false', 4)
	call_predicate('$ipc_peek', 5, 6)
	pseudo_instr1(55, 25)
	cut(4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$same_handle_from', 2, 2)
	pseudo_instr2(65, 20, 0)
	put_y_value(1, 1)
	get_y_value(0, 1)
	pseudo_instr1(52, 0)
	deallocate
	proceed
end('<<-'/2):



'<<='/2:


$1:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(5, 1)
	get_y_level(0)
	put_y_variable(2, 0)
	put_y_variable(1, 1)
	put_y_variable(4, 2)
	put_constant('block', 3)
	put_constant('false', 4)
	call_predicate('$ipc_peek', 5, 6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('$same_handle_from', 2, 4)
	pseudo_instr2(65, 22, 0)
	put_y_value(3, 1)
	get_y_value(2, 1)
	pseudo_instr1(52, 0)
	pseudo_instr1(55, 21)
	cut(0)
	deallocate
	proceed
end('<<='/2):



'$is_timeout'/1:


$1:
	get_constant('$$ipc_timeout$$', 0)
	proceed
end('$is_timeout'/1):



'$mc_inline/2$0'/8:

	try(8, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$ipc_peek', 5, 0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_constant('block')
	unify_constant('false')
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_x_value(6)
	get_structure('$get_level', 1, 0)
	unify_x_value(5)
	proceed

$2:
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(8)
	get_structure('$ipc_peek', 5, 1)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(0)
	unify_constant('false')
	get_structure(',', 2, 8)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$get_level', 1, 0)
	unify_x_value(5)
	get_structure(';', 2, 1)
	unify_x_ref(0)
	unify_x_value(6)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$is_timeout', 1, 0)
	unify_x_value(2)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_x_value(7)
	get_structure('$cut', 1, 0)
	unify_x_value(5)
	proceed
end('$mc_inline/2$0'/8):



'$mc_inline'/2:


$1:
	allocate(8)
	get_y_variable(7, 1)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	put_y_variable(4, 3)
	put_y_variable(3, 4)
	put_y_variable(2, 5)
	put_y_variable(1, 6)
	put_y_variable(0, 7)
	call_predicate('$mc_gen_choices', 8, 8)
	put_y_value(2, 0)
	put_y_value(7, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(0, 5)
	put_y_value(6, 6)
	put_y_value(1, 7)
	deallocate
	execute_predicate('$mc_inline/2$0', 8)
end('$mc_inline'/2):



'$mc_gen_choices'/8:

	switch_on_term(0, $11, $6, $6, $7, $6, $6)

$7:
	switch_on_structure(0, 8, ['$default':$6, '$'/0:$8, ';'/2:$9, '->'/2:$10])

$8:
	try(8, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$9:
	try(8, $1)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$10:
	try(8, $2)
	trust($6)

$11:
	try(8, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_structure(';', 2, 0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_variable(8)
	get_structure('timeout', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 5)
	get_x_value(8, 6)
	put_constant('true', 0)
	get_x_value(1, 0)
	neck_cut
	proceed

$2:
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_variable(8)
	get_structure('timeout', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 5)
	get_x_value(8, 6)
	put_constant('true', 0)
	get_x_value(1, 0)
	neck_cut
	proceed

$3:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	unify_x_ref(8)
	get_structure(';', 2, 8)
	unify_x_ref(8)
	unify_void(1)
	get_structure('->', 2, 8)
	unify_x_ref(8)
	unify_x_variable(9)
	get_structure('timeout', 1, 8)
	unify_x_variable(8)
	get_x_value(8, 5)
	get_x_value(9, 6)
	get_x_variable(5, 7)
	allocate(1)
	get_y_level(0)
	put_x_variable(1, 1)
	call_predicate('$mc_choice_to_code', 6, 1)
	cut(0)
	deallocate
	proceed

$4:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	unify_x_ref(8)
	get_structure('->', 2, 8)
	unify_x_ref(8)
	unify_x_variable(9)
	get_structure('timeout', 1, 8)
	unify_x_variable(8)
	get_x_value(8, 5)
	get_x_value(9, 6)
	get_x_variable(5, 7)
	allocate(1)
	get_y_level(0)
	call_predicate('$mc_choice_to_code', 6, 1)
	cut(0)
	deallocate
	proceed

$5:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(8)
	unify_y_variable(7)
	get_structure(';', 2, 1)
	unify_x_variable(1)
	unify_y_variable(6)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	neck_cut
	put_y_value(0, 5)
	call_predicate('$mc_choice_to_code', 6, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$mc_gen_choices', 8)

$6:
	get_constant('fail', 6)
	get_x_variable(5, 7)
	neck_cut
	execute_predicate('$mc_choice_to_code', 6)
end('$mc_gen_choices'/8):



'$mc_choice_to_code'/6:

	switch_on_term(0, $7, 'fail', 'fail', $4, 'fail', 'fail')

$4:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$5, '->'/2:$6])

$5:
	try(6, $1)
	retry($2)
	trust($3)

$6:
	try(6, $1)
	retry($2)
	trust($3)

$7:
	try(6, $1)
	retry($2)
	trust($3)

$1:
	get_structure('->', 2, 0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(4)
	get_structure('::', 2, 0)
	unify_x_variable(0)
	unify_y_variable(5)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	get_y_variable(1, 5)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 5, 6)
	put_y_value(3, 0)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(5)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$cut', 1, 0)
	unify_y_value(1)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_y_value(4)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(2)
	deallocate
	proceed

$2:
	get_structure('->', 2, 0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(4)
	get_structure('??', 2, 0)
	unify_x_variable(0)
	unify_y_variable(5)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	get_y_variable(1, 5)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 5, 6)
	put_y_value(3, 0)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(5)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$cut', 1, 0)
	unify_y_value(1)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_y_value(4)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(2)
	deallocate
	proceed

$3:
	get_structure('->', 2, 0)
	unify_x_variable(0)
	allocate(5)
	unify_y_variable(4)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	get_y_variable(1, 5)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 5, 5)
	put_y_value(3, 0)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$cut', 1, 0)
	unify_y_value(1)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_y_value(4)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(2)
	deallocate
	proceed
end('$mc_choice_to_code'/6):



'$mc_get_msg_addr_code'/5:


$1:
	get_structure('<<-', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('$same_handle_from', 2, 1)
	unify_x_value(4)
	unify_x_value(5)
	get_structure(',', 2, 3)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('freeze_term', 2, 1)
	unify_x_value(2)
	unify_x_variable(1)
	get_structure(',', 2, 3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('=', 2, 3)
	unify_x_value(0)
	unify_x_value(2)
	get_structure('thaw_term', 1, 4)
	unify_x_value(1)
	proceed
end('$mc_get_msg_addr_code'/5):



'$query_communications1526442632_57/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('->>', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$0'/0):



'$query_communications1526442632_57/0$1'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('+>>', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$1'/0):



'$query_communications1526442632_57/0$2'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('<<-', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$2'/0):



'$query_communications1526442632_57/0$3'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('<<=', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$3'/0):



'$query_communications1526442632_57/0$4'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(451, 0)
	put_constant('xfx', 1)
	put_constant('reply_to', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$4'/0):



'$query_communications1526442632_57/0$5'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(500, 0)
	put_constant('fy', 1)
	put_constant('message_choice', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$5'/0):



'$query_communications1526442632_57/0$6'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(50, 0)
	put_constant('xfx', 1)
	put_constant(':', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$6'/0):



'$query_communications1526442632_57/0$7'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(1024, 0)
	put_constant('xfx', 1)
	put_constant('::', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$7'/0):



'$query_communications1526442632_57/0$8'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(1024, 0)
	put_constant('xfx', 1)
	put_constant('??', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$8'/0):



'$query_communications1526442632_57/0$9'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(100, 0)
	put_constant('xfx', 1)
	put_constant('@', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications1526442632_57/0$9'/0):



'$query_communications1526442632_57'/0:

	try(0, $1)
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
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$1', 0, 0)
	fail

$3:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$2', 0, 0)
	fail

$4:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$3', 0, 0)
	fail

$5:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$4', 0, 0)
	fail

$6:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$5', 0, 0)
	fail

$7:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$6', 0, 0)
	fail

$8:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$7', 0, 0)
	fail

$9:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$8', 0, 0)
	fail

$10:
	allocate(0)
	call_predicate('$query_communications1526442632_57/0$9', 0, 0)
	fail

$11:
	proceed
end('$query_communications1526442632_57'/0):



'$query'/0:


$1:
	execute_predicate('$query_communications1526442632_57', 0)
end('$query'/0):



