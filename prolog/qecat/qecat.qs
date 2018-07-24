'main'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(0)
	put_y_variable(1, 2)
	put_constant('read', 1)
	call_predicate('open', 3, 2)
	put_y_value(1, 0)
	call_predicate('encoded_cat', 1, 2)
	put_y_value(1, 0)
	call_predicate('close', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('main', 1)
end('main'/1):



'encoded_cat/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	put_structure(1, 3)
	set_constant('remember_name')
	set_constant('true')
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	call_predicate('encoded_read_term', 3, 2)
	cut(1)
	put_y_value(0, 0)
	call_predicate('portray_clause', 1, 0)
	fail

$2:
	proceed
end('encoded_cat/1$0'/1):



'encoded_cat'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('repeat', 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('encoded_cat/1$0', 1)
end('encoded_cat'/1):



