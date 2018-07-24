'encoded_write_term'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(28, 0)
	put_x_value(3, 1)
	execute_predicate('encoded_write_term', 3)
end('encoded_write_term'/2):



'encoded_write_term'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('encoded_write_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('encoded_write_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('encoded_write_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(5)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(3, 2)
	pseudo_instr2(101, 22, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	get_y_level(4)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	call_predicate('closed_list', 1, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	call_predicate('$set_encoded_write_options', 2, 3)
	pseudo_instr3(36, 22, 21, 20)
	deallocate
	proceed

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('encoded_write_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('encoded_write_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('encoded_write_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('encoded_write_term'/3):



'$set_encoded_write_options'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	put_structure(1, 0)
	set_constant('remember_name')
	set_void(1)
	put_x_value(3, 1)
	put_constant('false', 3)
	execute_predicate('$process_encoded_options', 4)
end('$set_encoded_write_options'/2):



'encoded_read_term'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(27, 0)
	put_x_value(3, 1)
	execute_predicate('encoded_read_term', 3)
end('encoded_read_term'/2):



'encoded_read_term'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('encoded_read_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('encoded_read_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('encoded_read_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(5)
	get_y_variable(2, 0)
	get_y_variable(0, 1)
	get_y_variable(3, 2)
	pseudo_instr2(101, 22, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	get_y_level(4)
	put_y_variable(1, 19)
	put_y_value(3, 0)
	call_predicate('closed_list', 1, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_x_variable(2, 2)
	call_predicate('$set_encoded_read_options', 3, 3)
	pseudo_instr4(6, 22, 0, 1, 21)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('encoded_read_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('encoded_read_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('encoded_read_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('encoded_read_term'/3):



'$set_encoded_read_options'/3:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(3, 1)
	get_y_variable(0, 2)
	put_structure(1, 0)
	set_constant('remember_name')
	set_void(1)
	put_y_value(1, 1)
	put_x_value(3, 2)
	put_constant('false', 3)
	call_predicate('$process_encoded_options', 4, 2)
	put_constant('$current_obvar_prefix_table', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(3, 0)
	put_structure(1, 0)
	set_constant('obvar_prefix_table')
	set_void(1)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$process_encoded_options', 4)
end('$set_encoded_read_options'/3):



'$process_encoded_options'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 2)
	get_y_level(2)
	call_predicate('member', 2, 3)
	cut(2)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_value(2, 3)
	proceed
end('$process_encoded_options'/4):



'$add_encoded_obvar_prefix'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	call_predicate('$add_obvar_prefix', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$add_encoded_obvar_prefix', 2)
end('$add_encoded_obvar_prefix'/2):



