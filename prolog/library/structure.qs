'=..'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(43, 0)
	neck_cut
	get_list(1)
	unify_x_value(0)
	unify_constant('[]')
	proceed

$2:
	get_x_variable(3, 0)
	allocate(3)
	get_y_variable(2, 1)
	pseudo_instr1(0, 3)
	neck_cut
	put_y_variable(1, 19)
	put_x_variable(1, 1)
	pseudo_instr3(0, 3, 21, 1)
	put_y_variable(0, 2)
	put_integer(0, 0)
	call_predicate('$univ_arguments', 4, 3)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$3:
	allocate(5)
	get_y_variable(2, 0)
	get_list(1)
	unify_y_variable(3)
	unify_y_variable(1)
	get_y_level(4)
	put_y_variable(0, 19)
	put_y_value(1, 0)
	call_predicate('closed_list', 1, 5)
	put_y_value(1, 0)
	put_y_value(0, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 5)
	put_integer(256, 0)
	pseudo_instr2(1, 20, 0)
	cut(4)
	put_x_variable(3, 3)
	pseudo_instr3(0, 3, 23, 20)
	get_y_value(2, 3)
	put_y_value(0, 1)
	put_y_value(1, 2)
	put_integer(0, 0)
	deallocate
	execute_predicate('$univ_arguments', 4)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('=..')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('list')
	set_constant('term')
	put_structure(1, 3)
	set_constant('+')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('=..')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('list')
	set_constant('term')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('=..')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('type_exception', 3)
end('=..'/2):



'$univ_arguments'/4:

	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 2)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_list(2)
	unify_x_variable(4)
	unify_x_variable(2)
	put_integer(1, 6)
	pseudo_instr3(2, 0, 6, 5)
	get_x_variable(0, 5)
	pseudo_instr3(1, 0, 3, 5)
	get_x_value(5, 4)
	execute_predicate('$univ_arguments', 4)
end('$univ_arguments'/4):



'$higher_functor'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	allocate(3)
	get_y_variable(0, 2)
	pseudo_instr1(0, 3)
	neck_cut
	put_x_variable(0, 0)
	put_y_variable(2, 19)
	pseudo_instr3(0, 3, 0, 22)
	put_y_variable(1, 2)
	call_predicate('$higher_functor', 3, 3)
	pseudo_instr3(2, 22, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_integer(0, 2)
	get_x_value(0, 1)
	proceed
end('$higher_functor'/3):



