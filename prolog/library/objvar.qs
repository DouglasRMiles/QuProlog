'$init_objvar'/0:


$1:
	put_constant('$current_obvar_prefix_table', 0)
	put_constant('user', 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('$init_objvar'/0):



'obvar_prefix_table'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	pseudo_instr1(2, 0)
	neck_cut
	put_constant('$current_obvar_prefix_table', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('obvar_prefix_table')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('obvar_prefix_table')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('obvar_prefix_table'/1):



'obvar_prefix'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	execute_predicate('obvar_prefix', 2)
end('obvar_prefix'/1):



'obvar_prefix'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(50, 1)
	pseudo_instr1(2, 2)
	neck_cut
	put_structure(1, 0)
	set_constant('$obvar_prefix_decl')
	set_x_value(2)
	execute_predicate('application', 2)

$2:
	pseudo_instr1(2, 0)
	neck_cut
	execute_predicate('$obvar_prefix_decl', 2)

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('obvar_prefix')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 4)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('obvar_prefix')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 4)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('obvar_prefix')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 4)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('obvar_prefix'/2):



'$obvar_prefix_decl/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('$dynamic_obvar_prefix_decl', 3)
	put_integer(2, 4)
	pseudo_instr3(33, 3, 4, 2)
	put_integer(1, 3)
	get_x_value(2, 3)
	allocate(1)
	get_y_level(0)
	call_predicate('$dynamic_obvar_prefix_decl', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('$dynamic_obvar_prefix_decl')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('assert', 1)
end('$obvar_prefix_decl/2$0'/2):



'$obvar_prefix_decl'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(4, 1)
	neck_cut
	proceed

$2:
	pseudo_instr1(2, 1)
	pseudo_instr1(37, 1)
	neck_cut
	execute_predicate('$obvar_prefix_decl/2$0', 2)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('obvar_prefix')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 4)
	set_constant('obvar_prefix')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('$obvar_prefix_decl'/2):



'$add_obvar_prefix'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_integer(1, 3)
	put_constant('_', 4)
	pseudo_instr4(1, 2, 3, 4, 1)
	neck_cut
	pseudo_instr2(70, 1, 3)
	put_integer(1, 1)
	get_x_variable(4, 1)
	put_x_variable(1, 1)
	pseudo_instr4(2, 2, 4, 3, 1)
	execute_predicate('$obvar_prefix_decl', 2)

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_value(2, 1)
	execute_predicate('$obvar_prefix_decl', 2)
end('$add_obvar_prefix'/2):



'current_obvar_prefix'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	execute_predicate('current_obvar_prefix', 2)
end('current_obvar_prefix'/1):



'current_obvar_prefix'/2:


$1:
	put_constant('$dynamic_obvar_prefix_decl', 3)
	put_integer(2, 4)
	pseudo_instr3(33, 3, 4, 2)
	put_integer(1, 3)
	get_x_value(2, 3)
	execute_predicate('$dynamic_obvar_prefix_decl', 2)
end('current_obvar_prefix'/2):



'remove_obvar_prefix'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	execute_predicate('remove_obvar_prefix', 2)
end('remove_obvar_prefix'/1):



'remove_obvar_prefix/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	proceed

$2:
	pseudo_instr1(1, 0)
	proceed
end('remove_obvar_prefix/2$0'/1):



'remove_obvar_prefix/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('remove_obvar_prefix/2$1'/1):



'remove_obvar_prefix'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(2, 21)
	get_y_level(2)
	put_y_value(0, 0)
	call_predicate('remove_obvar_prefix/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('$dynamic_obvar_prefix_decl')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('retract', 1)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('remove_obvar_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('remove_obvar_prefix')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('remove_obvar_prefix/2$1', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('remove_obvar_prefix')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('remove_obvar_prefix')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('remove_obvar_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('remove_obvar_prefix')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('type_exception', 3)
end('remove_obvar_prefix'/2):



'obvar_name_to_prefix'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(55, 0, 2)
	get_x_value(1, 2)
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('obvar_name_to_prefix')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('obvar_name_to_prefix')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('obvar_name_to_prefix'/2):



'$check_obvar_syntax'/2:


$1:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('obvar_name_to_prefix', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('current_obvar_prefix', 2)
end('$check_obvar_syntax'/2):



