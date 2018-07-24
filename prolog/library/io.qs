'see'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('see')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('see')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(1)
	get_y_level(0)
	call_predicate('$stdio', 1, 1)
	cut(0)
	put_integer(0, 0)
	deallocate
	execute_predicate('set_input', 1)

$3:
	pseudo_instr1(2, 0)
	neck_cut
	allocate(1)
	put_y_variable(0, 2)
	put_constant('read', 1)
	call_predicate('$exist_or_open', 3, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('set_input', 1)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('see')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('see')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('see'/1):



'seeing'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('$file_or_alias', 2)
end('seeing'/1):



'seen'/0:


$1:
	pseudo_instr1(27, 0)
	put_constant('[]', 1)
	allocate(0)
	call_predicate('$close2', 2, 0)
	put_integer(0, 0)
	deallocate
	execute_predicate('set_input', 1)
end('seen'/0):



'tell/1$0/1$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'stdout':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('stdout', 1)
	get_x_value(0, 1)
	proceed

$2:
	put_structure(1, 1)
	set_constant('alias')
	set_x_value(0)
	put_constant('stdout', 0)
	execute_predicate('stream_property', 2)
end('tell/1$0/1$0'/1):



'tell/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('tell/1$0/1$0', 1, 1)
	cut(0)
	put_constant('stdout', 0)
	deallocate
	execute_predicate('set_output', 1)

$2:
	put_constant('stderr', 0)
	execute_predicate('set_output', 1)
end('tell/1$0'/1):



'tell'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('tell')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('tell')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('$stdio', 1, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('tell/1$0', 1)

$3:
	pseudo_instr1(2, 0)
	neck_cut
	allocate(1)
	put_y_variable(0, 2)
	put_constant('write', 1)
	call_predicate('$exist_or_open', 3, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('set_output', 1)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('tell')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('tell')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('tell'/1):



'telling'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('$file_or_alias', 2)
end('telling'/1):



'told'/0:


$1:
	pseudo_instr1(28, 0)
	put_constant('[]', 1)
	allocate(0)
	call_predicate('$close2', 2, 0)
	put_integer(1, 0)
	deallocate
	execute_predicate('set_output', 1)
end('told'/0):



'$exist_or_open'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	get_x_variable(0, 2)
	allocate(1)
	get_y_level(0)
	put_structure(1, 1)
	set_constant('file_name')
	set_x_value(3)
	call_predicate('stream_property', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(3, 0)
	get_x_variable(0, 2)
	allocate(1)
	get_y_level(0)
	put_structure(1, 1)
	set_constant('alias')
	set_x_value(3)
	call_predicate('stream_property', 2, 1)
	cut(0)
	deallocate
	proceed

$3:
	execute_predicate('open', 3)
end('$exist_or_open'/3):



'$file_or_alias'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 1)
	allocate(1)
	get_y_level(0)
	put_structure(1, 1)
	set_constant('file_name')
	set_x_value(2)
	call_predicate('stream_property', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(2, 1)
	allocate(1)
	get_y_level(0)
	put_structure(1, 1)
	set_constant('alias')
	set_x_value(2)
	call_predicate('stream_property', 2, 1)
	cut(0)
	deallocate
	proceed
end('$file_or_alias'/2):



'get0'/1:


$1:
	execute_predicate('get_code', 1)
end('get0'/1):



'get0'/2:


$1:
	execute_predicate('get_code', 2)
end('get0'/2):



'get'/1:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_level(0)
	call_predicate('repeat', 0, 2)
	put_y_value(1, 0)
	call_predicate('get_code', 1, 2)
	put_integer(32, 0)
	pseudo_instr2(1, 0, 21)
	put_integer(126, 0)
	pseudo_instr2(2, 21, 0)
	cut(0)
	deallocate
	proceed
end('get'/1):



'get/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	call_predicate('get_code', 2, 3)
	cut(2)
	put_integer(32, 0)
	pseudo_instr2(1, 0, 21)
	put_integer(126, 0)
	pseudo_instr2(2, 21, 0)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 2)
	cut(0)
	fail
end('get/2$0'/3):



'get'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_level(0)
	call_predicate('repeat', 0, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('get/2$0', 3)
end('get'/2):



'put'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('put_code', 2)
end('put'/1):



'put'/2:


$1:
	execute_predicate('put_code', 2)
end('put'/2):



