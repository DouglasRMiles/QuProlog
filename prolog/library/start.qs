'$start/0$0/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$initialise_system_backtrackable', 0, 1)
	cut(0)
	fail

$2:
	proceed
end('$start/0$0/0$0'/0):



'$start/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$start/0$0/0$0', 0, 1)
	cut(0)
	fail

$2:
	proceed
end('$start/0$0'/0):



'$start'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	allocate(0)
	call_predicate('$initialise_system_non_backtrackable', 0, 0)
	call_predicate('$start/0$0', 0, 0)
	pseudo_instr1(11, 0)
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('$do_main')
	set_x_value(1)
	put_x_variable(3, 1)
	put_structure(1, 2)
	set_constant('$exception_at_start')
	set_x_value(3)
	call_predicate('catch', 3, 0)
	pseudo_instr0(8)
	deallocate
	proceed

$2:
	pseudo_instr0(8)
	proceed

$3:
	proceed
end('$start'/0):



'$exception_at_start'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('mismatch throw(', 0)
	call_predicate('error', 1, 1)
	put_y_value(0, 0)
	call_predicate('error', 1, 0)
	put_constant(')', 0)
	call_predicate('errornl', 1, 0)
	put_integer(2, 0)
	deallocate
	execute_predicate('halt', 1)
end('$exception_at_start'/1):



'$do_main'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('$query', 2)
	put_integer(0, 3)
	pseudo_instr3(33, 2, 3, 1)
	put_integer(0, 2)
	get_x_value(1, 2)
	neck_cut
	execute_predicate('main', 1)

$2:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$query', 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('main', 1)
end('$do_main'/1):



