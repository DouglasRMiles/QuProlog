'$init_index'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('$index')
	set_integer(3)
	execute_predicate('dynamic', 1)
end('$init_index'/0):



'index/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('index/3$0'/1):



'index/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('index/3$1'/1):



'index'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	allocate(3)
	get_y_variable(2, 2)
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	pseudo_instr1(3, 22)
	put_integer(0, 2)
	pseudo_instr2(1, 2, 22)
	pseudo_instr2(2, 22, 1)
	neck_cut
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$index1', 3)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('index')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('index')
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
	set_constant('index')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('index')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('index')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('index')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('index/3$0', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('index')
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
	set_constant('integer')
	put_structure(3, 4)
	set_constant('index')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(1, 0)
	call_predicate('index/3$1', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('index')
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
	set_constant('integer')
	put_structure(3, 4)
	set_constant('index')
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

$7:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('index')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('index')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('index'/3):



'$index1/3$0'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 0:$1, 2:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(2, 1)
	get_x_value(0, 1)
	proceed
end('$index1/3$0'/1):



'$index1/3$1'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	put_structure(3, 0)
	set_constant('$index')
	set_x_value(2)
	set_x_value(1)
	set_void(1)
	put_constant('true', 1)
	execute_predicate('$retract', 2)

$2:
	proceed
end('$index1/3$1'/2):



'$index1'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$index', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr3(33, 22, 21, 0)
	get_y_level(3)
	call_predicate('$index1/3$0', 1, 4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$index1/3$1', 2, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('$index')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$3:
	put_structure(3, 3)
	set_constant('index')
	set_x_value(0)
	set_x_value(1)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('cannot change indexing argument')
	execute_predicate('exception', 1)
end('$index1'/3):



'$get_clause_index'/2:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ':-'/2:$5])

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
	get_structure(':-', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	neck_cut
	execute_predicate('$get_index', 2)

$2:
	execute_predicate('$get_index', 2)
end('$get_clause_index'/2):



'$get_index'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 3, 0, 1)
	execute_predicate('$get_pred_index', 3)
end('$get_index'/2):



'$get_pred_index'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$index', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_integer(1, 2)
	proceed
end('$get_pred_index'/3):



