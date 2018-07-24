'pedro_connect'/0:


$1:
	put_constant('localhost', 0)
	put_integer(4550, 1)
	execute_predicate('pedro_connect', 2)
end('pedro_connect'/0):



'pedro_connect'/1:


$1:
	put_integer(4550, 1)
	execute_predicate('pedro_connect', 2)
end('pedro_connect'/1):



'pedro_connect/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('pedro_connect/2$0'/1):



'pedro_connect/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('pedro_connect/2$1'/1):



'pedro_connect'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr0(13)
	neck_cut
	put_constant('Warning: Pedro is already connected', 0)
	allocate(0)
	call_predicate('errornl', 1, 0)
	fail

$2:
	pseudo_instr1(3, 1)
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(124, 1, 0)
	proceed

$3:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	call_predicate('pedro_connect/2$0', 1, 2)
	put_structure(2, 0)
	set_constant('pedro_connect')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('pedro_connect')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	deallocate
	execute_predicate('type_exception', 3)

$4:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	call_predicate('pedro_connect/2$1', 1, 2)
	put_structure(2, 0)
	set_constant('pedro_connect')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('pedro_connect')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)
end('pedro_connect'/2):



'pedro_subscribe'/3:


$1:
	get_x_variable(3, 0)
	allocate(1)
	get_y_variable(0, 2)
	pseudo_instr1(68, 0)
	get_x_variable(2, 0)
	put_structure(3, 0)
	set_constant('subscribe')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_y_value(0, 1)
	call_predicate('$pedro_subscribe_aux', 2, 1)
	put_integer(0, 0)
	pseudo_instr2(133, 20, 0)
	deallocate
	proceed
end('pedro_subscribe'/3):



'$pedro_subscribe_aux/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(125, 0, 1)
	get_x_variable(0, 1)
	neck_cut
	put_constant('$pedro_subscribe_id', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	deallocate
	proceed
end('$pedro_subscribe_aux/2$0'/2):



'$pedro_subscribe_aux'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	pseudo_instr1(53, 0)
	put_constant('$pedro_subscribe_id', 1)
	put_integer(0, 2)
	pseudo_instr2(74, 1, 2)
	put_y_value(0, 1)
	call_predicate('$pedro_subscribe_aux/2$0', 2, 0)
	fail

$2:
	put_constant('$pedro_subscribe_id', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed
end('$pedro_subscribe_aux'/2):



'pedro_unsubscribe'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('pedro_unsubscribe')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('pedro_unsubscribe')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	neck_cut
	pseudo_instr1(68, 1)
	put_x_variable(2, 3)
	get_structure('unsubscribe', 1, 3)
	unify_x_value(0)
	pseudo_instr2(91, 1, 2)
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('pedro_unsubscribe')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('pedro_unsubscribe')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('pedro_unsubscribe'/1):



'pedro_notify'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(53, 0)
	pseudo_instr1(87, 0)
	fail

$2:
	proceed
end('pedro_notify'/1):



'pedro_register'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('pedro_register')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('pedro_register')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr1(89, 0)
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('pedro_register')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('pedro_register')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('pedro_register'/1):



'$pedro_p2p'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'p2pmsg'/3:$5])

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
	get_structure('p2pmsg', 3, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_level(3)
	put_y_variable(0, 1)
	call_predicate('$is_local_p2p', 2, 4)
	cut(3)
	put_x_variable(0, 1)
	get_structure('p2pmsg', 2, 1)
	unify_y_value(2)
	unify_y_value(1)
	pseudo_instr2(81, 20, 0)
	deallocate
	proceed

$2:
	execute_predicate('pedro_notify', 1)
end('$pedro_p2p'/1):



'$is_local_p2p'/2:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$4, '@'/2:$5])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$6:
	try(2, $1)
	trust($2)

$1:
	get_structure('@', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_x_value(2, 1)
	put_constant('', 1)
	pseudo_instr2(133, 2, 1)
	pseudo_instr1(90, 1)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_void(1)
	unify_x_value(3)
	execute_predicate('$same_host', 2)
end('$is_local_p2p'/2):



