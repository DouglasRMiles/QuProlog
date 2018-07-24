'repeat'/0:

	try(0, $1)
	trust($2)

$1:
	proceed

$2:
	execute_predicate('repeat', 0)
end('repeat'/0):



'between/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	pseudo_instr1(1, 3)
	neck_cut
	pseudo_instr2(2, 0, 1)
	put_x_value(3, 2)
	execute_predicate('$between', 3)

$2:
	pseudo_instr1(3, 0)
	neck_cut
	pseudo_instr2(2, 1, 0)
	pseudo_instr2(2, 0, 2)
	proceed
end('between/3$0'/3):



'between/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('between/3$1'/1):



'between/3$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('between/3$2'/1):



'between/3$3/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(3, 0)
	proceed
end('between/3$3/1$0'/1):



'between/3$3'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('between/3$3/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('between/3$3'/1):



'between'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_variable(3, 0)
	get_x_variable(4, 1)
	get_x_variable(0, 2)
	pseudo_instr1(3, 3)
	pseudo_instr1(3, 4)
	put_x_value(3, 1)
	put_x_value(4, 2)
	execute_predicate('between/3$0', 3)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('between')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('between')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('between')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('between')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('between/3$1', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('between')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('between')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('integer', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(1, 0)
	call_predicate('between/3$2', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('between')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('between')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('integer', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(0, 0)
	call_predicate('between/3$3', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('between')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('between')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	deallocate
	execute_predicate('type_exception', 3)
end('between'/3):



'$between'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_value(0, 2)
	proceed

$2:
	pseudo_instr2(1, 0, 1)
	pseudo_instr2(69, 0, 3)
	get_x_variable(0, 3)
	execute_predicate('$between', 3)
end('$between'/3):



'unwind_protect/2$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call_predicate', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('unwind_protect/2$0/1$0'/1):



'unwind_protect/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('unwind_protect/2$0/1$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	proceed
end('unwind_protect/2$0'/1):



'unwind_protect'/2:


$1:
	allocate(2)
	get_y_variable(1, 1)
	put_structure(1, 1)
	set_constant('call_predicate')
	set_x_value(0)
	put_structure(2, 0)
	set_constant('=')
	set_y_variable(0)
	set_constant('true')
	put_structure(2, 2)
	set_constant('->')
	set_x_value(1)
	set_x_value(0)
	put_structure(2, 1)
	set_constant('=')
	set_y_value(0)
	set_constant('fail')
	put_structure(2, 0)
	set_constant(';')
	set_x_value(2)
	set_x_value(1)
	put_x_variable(2, 1)
	put_structure(1, 3)
	set_constant('call_predicate')
	set_y_value(1)
	put_structure(1, 4)
	set_constant('\\+')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('->')
	set_x_value(4)
	set_constant('true')
	put_structure(2, 4)
	set_constant(';')
	set_x_value(3)
	set_constant('true')
	put_structure(1, 3)
	set_constant('throw')
	set_x_value(2)
	put_structure(2, 2)
	set_constant(',')
	set_x_value(4)
	set_x_value(3)
	call_predicate('catch', 3, 2)
	put_y_value(1, 0)
	call_predicate('unwind_protect/2$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('unwind_protect'/2):



'$occurs_check_on'/1:


$1:
	put_integer(1, 1)
	put_integer(1, 2)
	execute_predicate('$eval_goal', 3)
end('$occurs_check_on'/1):



'$occurs_check_off'/1:


$1:
	put_integer(1, 1)
	put_integer(0, 2)
	execute_predicate('$eval_goal', 3)
end('$occurs_check_off'/1):



'$heat_wave_on'/1:


$1:
	put_integer(2, 1)
	put_integer(1, 2)
	execute_predicate('$eval_goal', 3)
end('$heat_wave_on'/1):



'$heat_wave_off'/1:


$1:
	put_integer(2, 1)
	put_integer(0, 2)
	execute_predicate('$eval_goal', 3)
end('$heat_wave_off'/1):



'$eval_goal'/3:


$1:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr2(11, 21, 1)
	get_y_variable(0, 1)
	pseudo_instr2(10, 21, 2)
	call_predicate('call_predicate', 1, 2)
	pseudo_instr2(10, 21, 20)
	deallocate
	proceed
end('$eval_goal'/3):



'thread_atomic_goal'/1:


$1:
	put_integer(5, 1)
	put_integer(0, 2)
	execute_predicate('$eval_goal', 3)
end('thread_atomic_goal'/1):



'false'/0:


$1:
	fail
end('false'/0):



