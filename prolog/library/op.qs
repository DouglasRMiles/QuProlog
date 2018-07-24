'$init_op'/0:


$1:
	put_constant('$current_op_table', 0)
	put_constant('user', 1)
	pseudo_instr2(74, 0, 1)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$parent_op_table')
	set_integer(2)
	allocate(0)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$op_info')
	set_integer(5)
	deallocate
	execute_predicate('dynamic', 1)
end('$init_op'/0):



'op_table'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('$current_op_table', 2)
	pseudo_instr2(73, 2, 1)
	get_x_value(0, 1)
	proceed

$2:
	pseudo_instr1(2, 0)
	neck_cut
	put_constant('$current_op_table', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$3:
	put_structure(1, 0)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 1)
	set_constant('op_table')
	set_x_value(0)
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_constant('op_table', 0)
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('op_table'/1):



'op_table_inherit/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('op_table_inherit/2$0'/2):



'op_table_inherit/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$parent_op_table', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('op_table_inherit/2$1'/2):



'op_table_inherit/2$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('op_table_inherit/2$2'/1):



'op_table_inherit'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(2, 21)
	pseudo_instr1(2, 20)
	neck_cut
	call_predicate('op_table_inherit/2$0', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('op_table_inherit/2$1', 2, 2)
	put_structure(2, 0)
	set_constant('$parent_op_table')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('op_table_inherit')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('op_table_inherit')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('op_table_inherit')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('op_table_inherit')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('op_table_inherit/2$2', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('op_table_inherit')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('op_table_inherit')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('op_table_inherit')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('op_table_inherit')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('op_table_inherit'/2):



'op'/3:


$1:
	get_x_variable(4, 0)
	get_x_variable(5, 1)
	get_x_variable(3, 2)
	put_constant('$current_op_table', 1)
	pseudo_instr2(73, 1, 0)
	put_x_value(4, 1)
	put_x_value(5, 2)
	execute_predicate('op', 4)
end('op'/3):



'op/4$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('op/4$0'/1):



'op/4$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('op/4$1'/1):



'op/4$2'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(2, 1)
	allocate(1)
	get_y_level(0)
	put_constant('atom', 0)
	call_predicate('application', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('op/4$2'/1):



'op'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	pseudo_instr1(50, 20)
	pseudo_instr1(2, 23)
	pseudo_instr1(3, 22)
	put_integer(-1, 0)
	pseudo_instr2(1, 0, 22)
	put_integer(1201, 0)
	pseudo_instr2(1, 22, 0)
	pseudo_instr1(2, 21)
	get_y_level(4)
	put_y_value(0, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 5)
	cut(4)
	put_structure(3, 0)
	set_constant('$op_decl')
	set_y_value(3)
	set_y_value(2)
	set_y_value(1)
	put_y_value(0, 1)
	deallocate
	execute_predicate('application', 2)

$2:
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	put_integer(-1, 4)
	pseudo_instr2(1, 4, 1)
	put_integer(1201, 4)
	pseudo_instr2(1, 1, 4)
	pseudo_instr1(2, 2)
	pseudo_instr1(2, 3)
	neck_cut
	execute_predicate('$op_decl', 4)

$3:
	get_x_variable(4, 0)
	pseudo_instr1(1, 4)
	neck_cut
	put_structure(4, 0)
	set_constant('op')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(4, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(4, 0)
	set_constant('op')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	get_x_variable(4, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(4, 0)
	set_constant('op')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$6:
	get_x_variable(4, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(4, 0)
	set_constant('op')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(4, 1)
	execute_predicate('instantiation_exception', 3)

$7:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_level(4)
	call_predicate('op/4$0', 1, 5)
	cut(4)
	put_structure(4, 0)
	set_constant('op')
	set_y_value(3)
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$8:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_level(4)
	put_y_value(1, 0)
	call_predicate('op/4$1', 1, 5)
	cut(4)
	put_structure(4, 0)
	set_constant('op')
	set_y_value(3)
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(3, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$9:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_level(4)
	put_y_value(0, 0)
	call_predicate('op/4$2', 1, 5)
	cut(4)
	put_structure(4, 0)
	set_constant('op')
	set_y_value(3)
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(4, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$10:
	get_x_variable(4, 0)
	put_structure(4, 0)
	set_constant('op')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(2, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('op'/4):



'$op_decl'/4:

	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant(',', 3)
	neck_cut
	put_structure(4, 3)
	set_constant('$op_decl')
	set_x_value(0)
	set_x_value(1)
	set_x_value(2)
	set_constant(',')
	put_structure(3, 0)
	set_constant('error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('cannot redefine comma operator')
	execute_predicate('exception', 1)

$2:
	get_integer(0, 1)
	allocate(3)
	get_y_variable(2, 0)
	get_x_variable(0, 2)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$op_class', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	call_predicate('$remove_op', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$zero_parent_op', 3)

$3:
	allocate(6)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_level(5)
	put_y_value(2, 0)
	put_y_variable(0, 1)
	call_predicate('$op_class', 2, 6)
	cut(5)
	put_y_value(4, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	call_predicate('$remove_op', 3, 5)
	put_structure(5, 0)
	set_constant('$op_info')
	set_y_value(1)
	set_y_value(4)
	set_y_value(0)
	set_y_value(3)
	set_y_value(2)
	deallocate
	execute_predicate('asserta', 1)

$4:
	get_x_variable(4, 0)
	put_structure(4, 0)
	set_constant('op')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('op')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_constant('atom')
	put_structure(4, 6)
	set_constant('op')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(1)
	put_integer(4, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('$op_decl'/4):



'$op_class'/2:

	switch_on_term(0, $10, 'fail', 'fail', 'fail', 'fail', $9)

$9:
	switch_on_constant(0, 16, ['$default':'fail', 'fx':$1, 'fy':$2, 'quant':$3, 'xfx':$4, 'xfy':$5, 'yfx':$6, 'xf':$7, 'yf':$8])

$10:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_constant('fx', 0)
	get_constant('prefix', 1)
	proceed

$2:
	get_constant('fy', 0)
	get_constant('prefix', 1)
	proceed

$3:
	get_constant('quant', 0)
	get_constant('prefix', 1)
	proceed

$4:
	get_constant('xfx', 0)
	get_constant('infix', 1)
	proceed

$5:
	get_constant('xfy', 0)
	get_constant('infix', 1)
	proceed

$6:
	get_constant('yfx', 0)
	get_constant('infix', 1)
	proceed

$7:
	get_constant('xf', 0)
	get_constant('postfix', 1)
	proceed

$8:
	get_constant('yf', 0)
	get_constant('postfix', 1)
	proceed
end('$op_class'/2):



'current_op'/3:


$1:
	get_x_variable(4, 0)
	get_x_variable(5, 1)
	get_x_variable(3, 2)
	put_constant('$current_op_table', 1)
	pseudo_instr2(73, 1, 0)
	put_x_value(4, 1)
	put_x_value(5, 2)
	execute_predicate('current_op', 4)
end('current_op'/3):



'current_op/4$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('current_op/4$0'/1):



'current_op/4$1'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('current_op/4$1'/1):



'current_op/4$2'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$op_info', 5, 1)
	cut(0)
	fail

$2:
	proceed
end('current_op/4$2'/3):



'current_op/4$3'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 1)
	allocate(1)
	get_y_level(0)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_constant('user', 1)
	call_predicate('$op_info', 5, 1)
	cut(0)
	fail

$2:
	proceed
end('current_op/4$3'/2):



'current_op/4$4'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$op_info', 5, 1)
	cut(0)
	fail

$2:
	proceed
end('current_op/4$4'/3):



'current_op/4$5'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 1)
	allocate(1)
	get_y_level(0)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_constant('user', 1)
	call_predicate('$op_info', 5, 1)
	cut(0)
	fail

$2:
	proceed
end('current_op/4$5'/2):



'current_op'/4:

	switch_on_term(0, $9, $8, $8, $8, $8, $6)

$6:
	switch_on_constant(0, 4, ['$default':$8, 'user':$7])

$7:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$9:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	put_constant(',', 0)
	pseudo_instr2(110, 3, 0)
	neck_cut
	put_integer(1000, 0)
	get_x_value(1, 0)
	put_constant('xfy', 0)
	get_x_value(2, 0)
	proceed

$2:
	get_x_variable(5, 0)
	allocate(1)
	get_y_variable(0, 1)
	get_x_variable(4, 2)
	get_x_variable(0, 3)
	put_x_value(5, 1)
	put_x_variable(2, 2)
	put_y_value(0, 3)
	call_predicate('$op_info', 5, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('current_op/4$0', 1)

$3:
	allocate(6)
	get_y_variable(2, 0)
	get_y_variable(3, 1)
	get_y_variable(5, 2)
	get_y_variable(1, 3)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('$parent_op_table', 2, 6)
	put_y_value(1, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	put_y_value(5, 4)
	call_predicate('$op_info', 5, 4)
	put_y_value(3, 0)
	call_predicate('current_op/4$1', 1, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('current_op/4$2', 3)

$4:
	allocate(5)
	get_y_variable(2, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	put_y_variable(0, 19)
	put_constant('user', 1)
	call_predicate('$parent_op_table', 2, 5)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	call_predicate('$static_op_decl', 4, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('current_op/4$3', 2, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('current_op/4$4', 3)

$5:
	get_constant('user', 0)
	get_x_variable(4, 1)
	get_x_variable(5, 2)
	allocate(2)
	get_y_variable(1, 3)
	put_y_value(1, 0)
	put_y_variable(0, 1)
	put_x_value(4, 2)
	put_x_value(5, 3)
	call_predicate('$static_op_decl', 4, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('current_op/4$5', 2)
end('current_op'/4):



'$remove_op'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	allocate(1)
	get_y_level(0)
	put_structure(5, 0)
	set_constant('$op_info')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	set_void(2)
	call_predicate('retract', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	proceed
end('$remove_op'/3):



'$zero_parent_op/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	execute_predicate('$op_info', 5)

$2:
	get_x_variable(3, 1)
	get_x_variable(1, 2)
	put_constant('user', 2)
	get_x_value(3, 2)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	execute_predicate('$static_op_decl', 4)
end('$zero_parent_op/3$0'/3):



'$zero_parent_op'/3:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, 'user':$5])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$6:
	try(3, $2)
	trust($3)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('user', 0)
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	put_y_value(0, 0)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	call_predicate('$static_op_decl', 4, 3)
	cut(2)
	put_structure(5, 0)
	set_constant('$op_info')
	set_y_value(0)
	set_constant('user')
	set_y_value(1)
	set_integer(0)
	set_void(1)
	deallocate
	execute_predicate('asserta', 1)

$2:
	allocate(5)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_variable(4, 1)
	call_predicate('$parent_op_table', 2, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(1, 2)
	call_predicate('$zero_parent_op/3$0', 3, 4)
	cut(3)
	put_structure(5, 0)
	set_constant('$op_info')
	set_y_value(0)
	set_y_value(2)
	set_y_value(1)
	set_integer(0)
	set_void(1)
	deallocate
	execute_predicate('asserta', 1)

$3:
	proceed
end('$zero_parent_op'/3):



'$static_op_decl'/4:

	switch_on_term(0, $58, 'fail', 'fail', 'fail', 'fail', $53)

$53:
	switch_on_constant(0, 128, ['$default':'fail', ':-':$54, '-->':$2, '?-':$4, ';':$5, '|':$6, '->':$7, ',':$8, '\\+':$9, 'spy':$10, 'nospy':$11, '=':$12, '\\=':$13, '?=':$14, '==':$15, '\\==':$16, '@<':$17, '@=':$18, '@=<':$19, '@>':$20, '@>=':$21, '=..':$22, 'is':$23, '=:=':$24, '=\\=':$25, '<':$26, '=<':$27, '>':$28, '>=':$29, 'not_free_in':$30, 'is_free_in':$31, 'is_not_free_in':$32, '+':$55, '-':$56, '/\\':$35, '\\/':$36, '*':$37, '/':$38, '//':$39, 'rem':$40, 'mod':$41, '<<':$42, '>>':$43, '**':$44, '^':$45, '?':$46, '@':$57, '\\':$50, ':':$52])

$54:
	try(4, $1)
	trust($3)

$55:
	try(4, $33)
	trust($48)

$56:
	try(4, $34)
	trust($49)

$57:
	try(4, $47)
	trust($51)

$58:
	try(4, $1)
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
	retry($34)
	retry($35)
	retry($36)
	retry($37)
	retry($38)
	retry($39)
	retry($40)
	retry($41)
	retry($42)
	retry($43)
	retry($44)
	retry($45)
	retry($46)
	retry($47)
	retry($48)
	retry($49)
	retry($50)
	retry($51)
	trust($52)

$1:
	get_constant(':-', 0)
	get_constant('infix', 1)
	get_integer(1200, 2)
	get_constant('xfx', 3)
	proceed

$2:
	get_constant('-->', 0)
	get_constant('infix', 1)
	get_integer(1200, 2)
	get_constant('xfx', 3)
	proceed

$3:
	get_constant(':-', 0)
	get_constant('prefix', 1)
	get_integer(1200, 2)
	get_constant('fx', 3)
	proceed

$4:
	get_constant('?-', 0)
	get_constant('prefix', 1)
	get_integer(1200, 2)
	get_constant('fx', 3)
	proceed

$5:
	get_constant(';', 0)
	get_constant('infix', 1)
	get_integer(1100, 2)
	get_constant('xfy', 3)
	proceed

$6:
	get_constant('|', 0)
	get_constant('infix', 1)
	get_integer(1100, 2)
	get_constant('xfy', 3)
	proceed

$7:
	get_constant('->', 0)
	get_constant('infix', 1)
	get_integer(1050, 2)
	get_constant('xfy', 3)
	proceed

$8:
	get_constant(',', 0)
	get_constant('infix', 1)
	get_integer(1000, 2)
	get_constant('xfy', 3)
	proceed

$9:
	get_constant('\\+', 0)
	get_constant('prefix', 1)
	get_integer(900, 2)
	get_constant('fy', 3)
	proceed

$10:
	get_constant('spy', 0)
	get_constant('prefix', 1)
	get_integer(900, 2)
	get_constant('fy', 3)
	proceed

$11:
	get_constant('nospy', 0)
	get_constant('prefix', 1)
	get_integer(900, 2)
	get_constant('fy', 3)
	proceed

$12:
	get_constant('=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$13:
	get_constant('\\=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$14:
	get_constant('?=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$15:
	get_constant('==', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$16:
	get_constant('\\==', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$17:
	get_constant('@<', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$18:
	get_constant('@=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$19:
	get_constant('@=<', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$20:
	get_constant('@>', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$21:
	get_constant('@>=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$22:
	get_constant('=..', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$23:
	get_constant('is', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$24:
	get_constant('=:=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$25:
	get_constant('=\\=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$26:
	get_constant('<', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$27:
	get_constant('=<', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$28:
	get_constant('>', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$29:
	get_constant('>=', 0)
	get_constant('infix', 1)
	get_integer(700, 2)
	get_constant('xfx', 3)
	proceed

$30:
	get_constant('not_free_in', 0)
	get_constant('infix', 1)
	get_integer(600, 2)
	get_constant('xfx', 3)
	proceed

$31:
	get_constant('is_free_in', 0)
	get_constant('infix', 1)
	get_integer(600, 2)
	get_constant('xfx', 3)
	proceed

$32:
	get_constant('is_not_free_in', 0)
	get_constant('infix', 1)
	get_integer(600, 2)
	get_constant('xfx', 3)
	proceed

$33:
	get_constant('+', 0)
	get_constant('infix', 1)
	get_integer(500, 2)
	get_constant('yfx', 3)
	proceed

$34:
	get_constant('-', 0)
	get_constant('infix', 1)
	get_integer(500, 2)
	get_constant('yfx', 3)
	proceed

$35:
	get_constant('/\\', 0)
	get_constant('infix', 1)
	get_integer(500, 2)
	get_constant('yfx', 3)
	proceed

$36:
	get_constant('\\/', 0)
	get_constant('infix', 1)
	get_integer(500, 2)
	get_constant('yfx', 3)
	proceed

$37:
	get_constant('*', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$38:
	get_constant('/', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$39:
	get_constant('//', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$40:
	get_constant('rem', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$41:
	get_constant('mod', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$42:
	get_constant('<<', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$43:
	get_constant('>>', 0)
	get_constant('infix', 1)
	get_integer(400, 2)
	get_constant('yfx', 3)
	proceed

$44:
	get_constant('**', 0)
	get_constant('infix', 1)
	get_integer(200, 2)
	get_constant('xfx', 3)
	proceed

$45:
	get_constant('^', 0)
	get_constant('infix', 1)
	get_integer(200, 2)
	get_constant('xfy', 3)
	proceed

$46:
	get_constant('?', 0)
	get_constant('prefix', 1)
	get_integer(200, 2)
	get_constant('fy', 3)
	proceed

$47:
	get_constant('@', 0)
	get_constant('prefix', 1)
	get_integer(200, 2)
	get_constant('fy', 3)
	proceed

$48:
	get_constant('+', 0)
	get_constant('prefix', 1)
	get_integer(200, 2)
	get_constant('fy', 3)
	proceed

$49:
	get_constant('-', 0)
	get_constant('prefix', 1)
	get_integer(200, 2)
	get_constant('fy', 3)
	proceed

$50:
	get_constant('\\', 0)
	get_constant('prefix', 1)
	get_integer(200, 2)
	get_constant('fy', 3)
	proceed

$51:
	get_constant('@', 0)
	get_constant('infix', 1)
	get_integer(100, 2)
	get_constant('xfx', 3)
	proceed

$52:
	get_constant(':', 0)
	get_constant('infix', 1)
	get_integer(50, 2)
	get_constant('xfx', 3)
	proceed
end('$static_op_decl'/4):



