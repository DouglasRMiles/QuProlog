'main'/1:


$1:
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$process_qg_options', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$expandfiles', 1)
end('main'/1):



'$process_qg_options'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_constant('-R')
	unify_x_ref(0)
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	call_predicate('$load_qg_rulefile', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$process_qg_options', 2)

$2:
	get_x_value(0, 1)
	proceed
end('$process_qg_options'/2):



'$load_qg_rulefile/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	execute_predicate('load', 1)

$2:
	proceed
end('$load_qg_rulefile/1$0'/1):



'$load_qg_rulefile/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	execute_predicate('consult', 1)

$2:
	proceed
end('$load_qg_rulefile/1$1'/1):



'$load_qg_rulefile'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr2(30, 0, 1)
	put_integer(2, 3)
	pseudo_instr3(3, 1, 3, 2)
	get_x_variable(1, 2)
	put_integer(3, 2)
	put_x_variable(3, 3)
	pseudo_instr4(2, 0, 1, 2, 3)
	put_constant('.qo', 1)
	get_x_value(3, 1)
	neck_cut
	allocate(1)
	get_y_level(0)
	call_predicate('$load_qg_rulefile/1$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_level(0)
	call_predicate('$load_qg_rulefile/1$1', 1, 1)
	cut(0)
	deallocate
	proceed
end('$load_qg_rulefile'/1):



'$query_qg1526442636_261/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(10, 0)
	set_constant('syntax_error')
	set_x_variable(1)
	set_x_variable(2)
	set_x_variable(3)
	set_x_variable(4)
	set_x_variable(5)
	set_x_variable(6)
	set_x_variable(7)
	set_x_variable(8)
	set_x_variable(9)
	set_x_variable(10)
	put_structure(10, 11)
	set_constant('syntax_error')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	set_x_value(6)
	set_x_value(7)
	set_x_value(8)
	set_x_value(9)
	set_x_value(10)
	put_structure(1, 1)
	set_constant('default_exception_error')
	set_x_value(11)
	call_predicate('add_global_exception_handler', 2, 1)
	cut(0)
	deallocate
	proceed
end('$query_qg1526442636_261/0$0'/0):



'$query_qg1526442636_261'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(0)
	call_predicate('$query_qg1526442636_261/0$0', 0, 0)
	fail

$2:
	proceed
end('$query_qg1526442636_261'/0):



'$query'/0:


$1:
	execute_predicate('$query_qg1526442636_261', 0)
end('$query'/0):



