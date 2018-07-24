'multifile'/1:


$1:
	get_structure('/', 2, 0)
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	put_structure(2, 0)
	set_constant('$multifile')
	set_y_value(1)
	set_y_value(0)
	call_predicate('assert', 1, 2)
	put_structure(2, 0)
	set_constant('/')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('dynamic', 1)
end('multifile'/1):



'dynamic/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(1, 1)
	proceed
end('dynamic/1$0'/2):



'dynamic'/1:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$4, '/'/2:$5])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$6:
	try(1, $1)
	trust($2)

$1:
	get_structure('/', 2, 0)
	allocate(3)
	unify_y_variable(1)
	unify_y_variable(0)
	get_y_level(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('dynamic/1$0', 2, 3)
	cut(2)
	put_structure(2, 1)
	set_constant('/')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 0)
	set_constant('dynamic')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('/')
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 2)
	set_constant('dynamic')
	set_x_value(3)
	put_integer(1, 1)
	deallocate
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	put_integer(1, 2)
	put_integer(4, 3)
	execute_predicate('$dynamic', 4)
end('dynamic'/1):



'dynamic/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(1, 1)
	proceed
end('dynamic/2$0'/2):



'dynamic'/2:

	switch_on_term(0, $7, 'fail', 'fail', $4, 'fail', 'fail')

$4:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$5, '/'/2:$6])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	retry($2)
	trust($3)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_structure('/', 2, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_level(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('dynamic/2$0', 2, 4)
	cut(3)
	put_structure(2, 1)
	set_constant('/')
	set_y_value(2)
	set_y_value(1)
	put_structure(2, 0)
	set_constant('dynamic')
	set_x_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('/')
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 2)
	set_constant('dynamic')
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	deallocate
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 3)
	set_constant('/')
	set_x_value(0)
	set_x_value(2)
	put_structure(2, 0)
	set_constant('dynamic')
	set_x_value(3)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('/')
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 2)
	set_constant('dynamic')
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	put_integer(4, 3)
	execute_predicate('$dynamic', 4)
end('dynamic'/2):



'dynamic'/3:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_x_variable(5, 1)
	get_x_variable(3, 2)
	put_x_value(4, 1)
	put_x_value(5, 2)
	execute_predicate('$dynamic', 4)
end('dynamic'/3):



'$dynamic'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_level(0)
	put_y_variable(4, 2)
	put_y_variable(3, 3)
	call_predicate('$correct_pred_arity', 4, 5)
	pseudo_instr4(0, 24, 23, 22, 21)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(2, 4)
	set_constant('/')
	set_x_value(0)
	set_x_value(1)
	put_structure(3, 1)
	set_constant('dynamic')
	set_x_value(4)
	set_x_value(2)
	set_x_value(3)
	put_structure(3, 0)
	set_constant('dynamic_code_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('$dynamic'/4):



'is_dynamic_call'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	put_integer(0, 2)
	pseudo_instr3(33, 0, 2, 1)
	put_integer(1, 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(0, 2)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 2, 0, 1)
	allocate(2)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 2)
	pseudo_instr3(33, 21, 20, 0)
	put_integer(1, 1)
	get_x_value(0, 1)
	deallocate
	proceed
end('is_dynamic_call'/1):



