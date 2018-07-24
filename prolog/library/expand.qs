'$expandfiles'/1:

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
	allocate(1)
	unify_y_variable(0)
	call_predicate('$expandfile', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$expandfiles', 1)
end('$expandfiles'/1):



'$expandfile/1$0/1$0/1$0'/6:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'le':$4])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$1:
	put_constant('le', 5)
	get_x_value(0, 5)
	neck_cut
	put_integer(2, 5)
	pseudo_instr3(3, 1, 5, 0)
	put_integer(1, 1)
	pseudo_instr4(2, 2, 1, 0, 3)
	put_constant('encoded', 0)
	get_x_value(4, 0)
	proceed

$2:
	put_integer(1, 0)
	pseudo_instr4(2, 2, 0, 5, 3)
	put_constant('normal', 0)
	get_x_value(4, 0)
	proceed
end('$expandfile/1$0/1$0/1$0'/6):



'$expandfile/1$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(5, 0)
	pseudo_instr2(30, 25, 0)
	get_x_variable(1, 0)
	pseudo_instr2(70, 1, 0)
	get_x_variable(5, 0)
	put_integer(2, 0)
	get_x_variable(2, 0)
	put_x_variable(0, 0)
	pseudo_instr4(2, 25, 5, 2, 0)
	get_y_level(0)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_value(5, 2)
	put_y_variable(6, 3)
	put_y_variable(3, 4)
	call_predicate('$expandfile/1$0/1$0/1$0', 6, 7)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_constant('g')
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	get_y_value(4, 0)
	put_y_value(5, 0)
	put_y_value(1, 2)
	put_constant('read', 1)
	call_predicate('open', 3, 5)
	put_y_value(4, 0)
	put_y_value(2, 2)
	put_constant('write', 1)
	call_predicate('open', 3, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	call_predicate('$expand', 3, 3)
	put_y_value(2, 0)
	call_predicate('close', 1, 2)
	put_y_value(1, 0)
	call_predicate('close', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$expandfile/1$0/1$0'/1):



'$expandfile/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$expandfile/1$0/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$expandfile/1$0'/1):



'$expandfile'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$expandfile/1$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_integer(1, 0)
	execute_predicate('halt', 1)
end('$expandfile'/1):



'$expand/3$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_structure(1, 4)
	set_constant('singletons')
	set_x_value(3)
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('variable_names')
	set_x_value(2)
	put_list(5)
	set_x_value(4)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('remember_name')
	set_constant('true')
	put_list(2)
	set_x_value(3)
	set_x_value(5)
	call_predicate('encoded_read_term', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_constant('end_of_file', 0)
	get_x_value(1, 0)
	proceed
end('$expand/3$0'/4):



'$expand'/3:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'encoded':$1, 'normal':$2])

$4:
	try(3, $1)
	trust($2)

$1:
	get_constant('encoded', 0)
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(1, 2)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	call_predicate('repeat', 0, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	call_predicate('$expand/3$0', 4, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	call_predicate('$check_singletons', 2, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	call_predicate('expand_term', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$expand_output', 2)

$2:
	get_constant('normal', 0)
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(1, 2)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	call_predicate('repeat', 0, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_structure(1, 2)
	set_constant('singletons')
	set_y_value(4)
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('variable_names')
	set_y_value(2)
	put_list(4)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('remember_name')
	set_constant('true')
	put_list(2)
	set_x_value(3)
	set_x_value(4)
	call_predicate('read_term', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	call_predicate('$check_singletons', 2, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	call_predicate('expand_term', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$expand_output', 2)
end('$expand'/3):



'$expand_output'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr1(50, 2)
	neck_cut
	put_y_variable(0, 0)
	put_x_value(2, 1)
	call_predicate('member', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$expand_write', 2)

$2:
	execute_predicate('$expand_write', 2)
end('$expand_output'/2):



'$expand_write/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$is_compiler_call', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$2:
	proceed
end('$expand_write/2$0'/1):



'$expand_write/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$is_compiler_call', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$2:
	proceed
end('$expand_write/2$1'/1):



'$expand_write'/2:

	switch_on_term(0, $11, $4, $4, $5, $4, $9)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, ':-'/1:$7, '?-'/1:$8])

$6:
	try(2, $2)
	retry($3)
	trust($4)

$7:
	try(2, $2)
	trust($4)

$8:
	try(2, $3)
	trust($4)

$9:
	switch_on_constant(0, 4, ['$default':$4, 'end_of_file':$10])

$10:
	try(2, $1)
	trust($4)

$11:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('end_of_file', 0)
	neck_cut
	proceed

$2:
	get_structure(':-', 1, 0)
	allocate(3)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$expand_write/2$0', 1, 3)
	cut(2)
	put_y_value(0, 0)
	put_structure(1, 1)
	set_constant(':-')
	set_y_value(1)
	put_structure(1, 2)
	set_constant('quoted')
	set_constant('true')
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('ignore_ops')
	set_constant('true')
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	call_predicate('write_term', 3, 1)
	put_y_value(0, 0)
	put_constant('.
', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 0)
	fail

$3:
	get_structure('?-', 1, 0)
	allocate(3)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$expand_write/2$1', 1, 3)
	cut(2)
	put_y_value(0, 0)
	put_structure(1, 1)
	set_constant('?-')
	set_y_value(1)
	put_structure(1, 2)
	set_constant('quoted')
	set_constant('true')
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('ignore_ops')
	set_constant('true')
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	call_predicate('write_term', 3, 1)
	put_y_value(0, 0)
	put_constant('.
', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 0)
	fail

$4:
	get_x_variable(2, 0)
	allocate(1)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	put_x_value(2, 1)
	put_structure(1, 2)
	set_constant('quoted')
	set_constant('true')
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('ignore_ops')
	set_constant('true')
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	call_predicate('write_term', 3, 1)
	put_y_value(0, 0)
	put_constant('.
', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 0)
	fail
end('$expand_write'/2):



