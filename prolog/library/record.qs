'$init_record'/0:


$1:
	put_constant('$recordDBcounter', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('$init_record'/0):



'recorded/3$0/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(3, 0)
	proceed
end('recorded/3$0/3$0'/1):



'recorded/3$0'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('recorded')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('recorded')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(2, 22)
	get_y_level(3)
	put_y_value(0, 0)
	call_predicate('recorded/3$0/3$0', 1, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$recordDB', 3)

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('recorded')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('recorded')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('recorded/3$0'/3):



'recorded'/3:


$1:
	execute_predicate('recorded/3$0', 3)
end('recorded'/3):



'recorda/3$0'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('recorda')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('recorda')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_execption', 3)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(2, 3)
	pseudo_instr1(1, 2)
	neck_cut
	put_constant('$recordDBcounter', 4)
	pseudo_instr2(75, 4, 0)
	get_x_value(2, 0)
	put_structure(3, 0)
	set_constant('$recordDB')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	execute_predicate('asserta', 1)

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('recorda')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('recorda')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('recorda/3$0'/3):



'recorda'/3:


$1:
	execute_predicate('recorda/3$0', 3)
end('recorda'/3):



'recordz/3$0'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('recordz')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('recordz')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_execption', 3)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(2, 3)
	pseudo_instr1(1, 2)
	neck_cut
	put_constant('$recordDBcounter', 4)
	pseudo_instr2(75, 4, 0)
	get_x_value(2, 0)
	put_structure(3, 0)
	set_constant('$recordDB')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	execute_predicate('assertz', 1)

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('recordz')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('recordz')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('recordz/3$0'/3):



'recordz'/3:


$1:
	execute_predicate('recordz/3$0', 3)
end('recordz'/3):



'erase/1$0'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('erase')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('erase')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(1, 0)
	pseudo_instr1(3, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('$recordDB')
	set_void(2)
	set_x_value(1)
	execute_predicate('retract', 1)

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('erase')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('erase')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('erase/1$0'/1):



'erase'/1:


$1:
	execute_predicate('erase/1$0', 1)
end('erase'/1):



'instance/2$0'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('instance')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(2, 3)
	set_constant('instance')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(3, 2)
	neck_cut
	put_x_variable(0, 0)
	execute_predicate('$recordDB', 3)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('instance')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('gcomp')
	put_structure(2, 3)
	set_constant('instance')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('instance/2$0'/2):



'instance'/2:


$1:
	execute_predicate('instance/2$0', 2)
end('instance'/2):



