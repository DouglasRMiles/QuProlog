'save/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_structure(2, 0)
	set_constant('$stream_property')
	set_void(2)
	put_constant('true', 1)
	call_predicate('clause', 2, 2)
	cut(1)
	put_structure(1, 1)
	set_constant('save')
	set_y_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('recoverable')
	set_x_value(1)
	set_constant('default')
	deallocate
	execute_predicate('exception', 1)

$2:
	allocate(4)
	get_y_variable(3, 0)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	put_x_variable(2, 2)
	put_constant('write', 0)
	call_predicate('$iomode', 3, 4)
	pseudo_instr3(31, 23, 22, 0)
	get_y_value(1, 0)
	pseudo_instr1(13, 21)
	put_y_value(0, 1)
	put_constant('false', 0)
	call_predicate('$boolnum', 2, 2)
	pseudo_instr2(40, 21, 20)
	deallocate
	proceed
end('save/1$0'/1):



'save'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	execute_predicate('save/1$0', 1)

$2:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('save')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('save')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('save')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('save')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('save'/1):



'restore/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_structure(2, 0)
	set_constant('$stream_property')
	set_void(2)
	put_constant('true', 1)
	call_predicate('clause', 2, 2)
	cut(1)
	put_structure(1, 1)
	set_constant('restore')
	set_y_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('recoverable')
	set_x_value(1)
	set_constant('default')
	deallocate
	execute_predicate('exception', 1)

$2:
	allocate(4)
	get_y_variable(3, 0)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	put_x_variable(2, 2)
	put_constant('read', 0)
	call_predicate('$iomode', 3, 4)
	pseudo_instr3(31, 23, 22, 0)
	get_y_value(1, 0)
	pseudo_instr1(14, 21)
	put_y_value(0, 1)
	put_constant('false', 0)
	call_predicate('$boolnum', 2, 2)
	pseudo_instr2(40, 21, 20)
	deallocate
	proceed
end('restore/1$0'/1):



'restore'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	execute_predicate('restore/1$0', 1)

$2:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('restore')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('restore')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('restore')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('restore')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('restore'/1):



'hash_table_search'/3:


$1:
	get_x_variable(3, 0)
	get_x_variable(4, 1)
	pseudo_instr3(30, 3, 4, 0)
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('$')
	set_x_value(3)
	set_x_value(4)
	set_x_value(2)
	execute_predicate('member', 2)
end('hash_table_search'/3):



