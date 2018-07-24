'main'/1:


$1:
	execute_predicate('$compilefiles', 1)
end('main'/1):



'$query_qc11526442636_220/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(10, 0)
	set_constant('syntax_error')
	set_x_variable(1)
	set_x_variable(2)
	set_x_variable(3)
	set_x_variable(4)
	set_x_variable(5)
	set_x_variable(6)
	set_x_variable(7)
	set_x_variable(8)
	set_x_variable(9)
	set_x_variable(10)
	put_structure(10, 11)
	set_constant('syntax_error')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	set_x_value(6)
	set_x_value(7)
	set_x_value(8)
	set_x_value(9)
	set_x_value(10)
	put_structure(1, 1)
	set_constant('default_exception_error')
	set_x_value(11)
	call_predicate('add_global_exception_handler', 2, 1)
	cut(0)
	deallocate
	proceed
end('$query_qc11526442636_220/0$0'/0):



'$query_qc11526442636_220'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(0)
	call_predicate('$query_qc11526442636_220/0$0', 0, 0)
	fail

$2:
	proceed
end('$query_qc11526442636_220'/0):



'$query'/0:


$1:
	execute_predicate('$query_qc11526442636_220', 0)
end('$query'/0):



