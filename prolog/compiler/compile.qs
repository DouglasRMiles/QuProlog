'$compilefiles'/1:

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
	put_integer(1, 1)
	put_integer(0, 2)
	pseudo_instr2(10, 1, 2)
	call_predicate('$compilefile', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$compilefiles', 1)
end('$compilefiles'/1):



'$compilefile/1$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(6, 0)
	get_y_level(0)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(5, 1)
	put_y_variable(3, 2)
	put_y_variable(4, 3)
	call_predicate('$outfile', 4, 7)
	put_y_value(6, 0)
	put_y_value(2, 2)
	put_constant('read', 1)
	call_predicate('open', 3, 6)
	put_y_value(5, 0)
	put_y_value(1, 2)
	put_constant('write', 1)
	call_predicate('open', 3, 5)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	call_predicate('$compile', 3, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('$compile_query', 2, 3)
	put_y_value(2, 0)
	call_predicate('close', 1, 2)
	put_y_value(1, 0)
	call_predicate('close', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$compilefile/1$0/1$0'/1):



'$compilefile/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$compilefile/1$0/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$compilefile/1$0'/1):



'$compilefile'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$compilefile/1$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_integer(1, 0)
	execute_predicate('halt', 1)
end('$compilefile'/1):



'$outfile'/4:


$1:
	get_constant('normal', 3)
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('name', 2, 5)
	put_y_value(0, 0)
	put_list(1)
	set_integer(103)
	set_constant('[]')
	put_list(2)
	set_integer(113)
	set_x_value(1)
	put_list(1)
	set_integer(46)
	set_x_value(2)
	put_y_value(4, 2)
	call_predicate('append', 3, 4)
	put_y_value(0, 0)
	put_list(1)
	set_integer(115)
	set_constant('[]')
	put_list(2)
	set_integer(113)
	set_x_value(1)
	put_list(1)
	set_integer(46)
	set_x_value(2)
	put_y_value(2, 2)
	call_predicate('append', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('name', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$remove_path', 2)
end('$outfile'/4):



'$remove_path/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_integer(47, 0)
	call_predicate('member', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$remove_path/2$0'/1):



'$remove_path'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	allocate(1)
	get_y_level(0)
	call_predicate('$remove_path/2$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	allocate(2)
	get_y_variable(1, 1)
	put_x_variable(0, 0)
	put_list(1)
	set_integer(47)
	set_y_variable(0)
	call_predicate('append', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$remove_path', 2)
end('$remove_path'/2):



'$compile'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_level(4)
	put_y_value(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_one', 3, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$compileall', 4)

$2:
	execute_predicate('$compile', 3)
end('$compile'/3):



'$compileall/4$0'/7:

	switch_on_term(0, $8, $7, $7, $4, $7, $7)

$4:
	switch_on_structure(0, 4, ['$default':$7, '$'/0:$5, '/'/2:$6])

$5:
	try(7, $1)
	retry($2)
	trust($3)

$6:
	try(7, $1)
	retry($2)
	trust($3)

$7:
	try(7, $2)
	trust($3)

$8:
	try(7, $1)
	retry($2)
	trust($3)

$1:
	get_structure('/', 2, 0)
	unify_constant('end_of_file')
	unify_integer(0)
	neck_cut
	proceed

$2:
	allocate(7)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	get_y_level(6)
	call_predicate('$is_dynamic_pred', 1, 7)
	cut(6)
	put_list(0)
	set_y_value(5)
	set_y_value(4)
	call_predicate('$assert_pred', 1, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$compileall', 4)

$3:
	get_x_variable(7, 1)
	get_x_variable(8, 2)
	allocate(4)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	put_y_value(2, 1)
	put_list(2)
	set_x_value(7)
	set_x_value(8)
	call_predicate('$compile_pred', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$compileall', 4)
end('$compileall/4$0'/7):



'$compileall'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_x_variable(0, 3)
	get_y_level(4)
	put_y_variable(0, 19)
	call_predicate('$process_directive', 1, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	call_predicate('$read_one', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$compileall', 4)

$2:
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_variable(2, 1)
	call_predicate('get_name', 2, 7)
	put_y_value(6, 0)
	put_y_value(2, 1)
	put_y_value(4, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	call_predicate('$read_new_pred', 5, 7)
	put_y_value(2, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(0, 6)
	deallocate
	execute_predicate('$compileall/4$0', 7)
end('$compileall'/4):



'$process_directive'/1:

	switch_on_term(0, $5, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$4, '?-'/1:$1, ':-'/1:$2])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_structure('?-', 1, 0)
	unify_x_variable(0)
	execute_predicate('$process_directive1', 1)

$2:
	get_structure(':-', 1, 0)
	unify_x_variable(0)
	execute_predicate('$process_directive1', 1)
end('$process_directive'/1):



'$process_directive1/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$is_compiler_call', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call', 1)

$2:
	proceed
end('$process_directive1/1$0'/1):



'$process_directive1/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$for_compiler_only', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('$query')
	set_x_value(1)
	execute_predicate('assert', 1)
end('$process_directive1/1$1'/1):



'$process_directive1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_level(0)
	call_predicate('$process_directive1/1$0', 1, 2)
	cut(0)
	put_y_value(1, 0)
	call_predicate('$process_directive1/1$1', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	proceed
end('$process_directive1'/1):



'$is_dynamic_pred'/1:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(1)
	unify_x_variable(2)
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 1, 2)
	put_constant('dynamic', 1)
	execute_predicate('predicate_property', 2)
end('$is_dynamic_pred'/1):



'$assert_pred'/1:

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
	put_structure(1, 1)
	set_constant('assert')
	set_x_value(0)
	put_structure(1, 0)
	set_constant('$query')
	set_x_value(1)
	call_predicate('assert', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$assert_pred', 1)
end('$assert_pred'/1):



'$compile_query/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(4)
	put_y_variable(2, 19)
	put_y_variable(3, 1)
	call_predicate('$get_query', 2, 5)
	cut(4)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(1)
	set_constant('[]')
	put_y_value(2, 2)
	call_predicate('append', 3, 3)
	put_structure(2, 0)
	set_constant('/')
	set_y_value(1)
	set_integer(0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	call_predicate('$compile_pred', 3, 2)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$query')
	set_integer(0)
	put_y_value(0, 1)
	put_structure(2, 3)
	set_constant(':-')
	set_constant('$query')
	set_y_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	deallocate
	execute_predicate('$compile_pred', 3)

$2:
	proceed
end('$compile_query/2$0'/2):



'$compile_query'/2:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(1, 1)
	pseudo_instr1(113, 0)
	put_x_variable(2, 3)
	get_structure('floor', 1, 3)
	unify_x_value(0)
	pseudo_instr2(0, 1, 2)
	put_x_variable(3, 4)
	get_structure('floor', 1, 4)
	unify_x_ref(4)
	get_structure('*', 2, 4)
	unify_x_ref(4)
	unify_integer(1000)
	get_structure('-', 2, 4)
	unify_x_value(0)
	unify_x_value(1)
	pseudo_instr2(0, 2, 3)
	get_x_variable(0, 2)
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(1)
	unify_x_ref(1)
	get_list(1)
	unify_x_value(0)
	unify_constant('[]')
	put_constant('_', 0)
	pseudo_instr3(28, 3, 0, 2)
	get_x_variable(0, 2)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('name', 2, 6)
	put_list(0)
	set_integer(95)
	set_constant('[]')
	put_list(1)
	set_integer(121)
	set_x_value(0)
	put_list(0)
	set_integer(114)
	set_x_value(1)
	put_list(1)
	set_integer(101)
	set_x_value(0)
	put_list(0)
	set_integer(117)
	set_x_value(1)
	put_list(1)
	set_integer(113)
	set_x_value(0)
	put_list(0)
	set_integer(36)
	set_x_value(1)
	put_y_value(5, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 5)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	call_predicate('append', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('name', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$compile_query/2$0', 2)
end('$compile_query'/2):



'$get_query/2$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('[]', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$get_query/2$0'/1):



'$get_query'/2:


$1:
	get_x_variable(2, 0)
	allocate(2)
	get_y_variable(1, 1)
	get_y_level(0)
	put_structure(1, 0)
	set_constant('once')
	set_x_variable(1)
	put_structure(2, 3)
	set_constant(',')
	set_x_value(0)
	set_constant('fail')
	put_structure(2, 0)
	set_constant(':-')
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 2)
	set_constant('$query')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('retract')
	set_x_value(2)
	put_y_value(1, 2)
	call_predicate('bagof', 3, 2)
	put_y_value(1, 0)
	call_predicate('$get_query/2$0', 1, 1)
	cut(0)
	deallocate
	proceed
end('$get_query'/2):



'$read_new_pred/5$0'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(4, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	get_y_level(6)
	call_predicate('get_name', 2, 7)
	cut(6)
	put_y_value(4, 0)
	get_list(0)
	unify_y_value(5)
	unify_x_variable(3)
	put_y_value(2, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$read_new_pred', 5)

$2:
	put_constant('[]', 1)
	get_x_value(2, 1)
	get_x_value(5, 0)
	proceed
end('$read_new_pred/5$0'/6):



'$read_new_pred'/5:

	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 3)
	get_constant('end_of_file', 4)
	get_structure('/', 2, 1)
	unify_constant('end_of_file')
	unify_integer(0)
	neck_cut
	proceed

$2:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_level(6)
	put_y_value(3, 1)
	put_y_variable(0, 2)
	call_predicate('$read_one', 3, 7)
	cut(6)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(5, 3)
	put_y_value(3, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$read_new_pred/5$0', 6)

$3:
	execute_predicate('$read_new_pred', 5)
end('$read_new_pred'/5):



'$read_flatten_pred'/4:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(4, $1)
	trust($2)

$1:
	get_list(0)
	allocate(6)
	unify_y_variable(4)
	unify_y_variable(2)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_level(5)
	put_y_value(4, 0)
	put_y_value(1, 1)
	call_predicate('get_name', 2, 6)
	cut(5)
	put_y_value(3, 0)
	get_list(0)
	unify_y_value(4)
	unify_x_variable(1)
	put_y_value(2, 0)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$read_flatten_pred', 4)

$2:
	get_constant('[]', 1)
	get_x_value(0, 3)
	proceed
end('$read_flatten_pred'/4):



'$read_one/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_structure(1, 3)
	set_constant('singletons')
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	call_predicate('encoded_read_term', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_constant('end_of_file', 0)
	get_x_value(1, 0)
	proceed
end('$read_one/3$0'/3):



'$read_one'/3:

	try(3, $1)
	trust($2)

$1:
	get_constant('encoded', 1)
	allocate(3)
	get_y_variable(1, 2)
	put_y_variable(0, 1)
	put_y_variable(2, 2)
	call_predicate('$read_one/3$0', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$check_singletons', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_constant('normal', 1)
	allocate(3)
	get_y_variable(1, 2)
	put_y_variable(0, 1)
	put_structure(1, 3)
	set_constant('singletons')
	set_y_variable(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	call_predicate('read_term', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$check_singletons', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$read_one'/3):



'$is_compiler_call'/1:

	switch_on_term(0, $18, 'fail', 'fail', $16, 'fail', $15)

$16:
	switch_on_structure(0, 32, ['$default':'fail', '$'/0:$17, 'op'/3:$1, 'op'/4:$2, 'obvar_prefix'/1:$3, 'obvar_prefix'/2:$4, 'remove_obvar_prefix'/1:$5, 'remove_obvar_prefix'/2:$6, 'op_table'/1:$7, 'op_table_inherit'/2:$8, 'inline'/2:$9, 'inline'/3:$10, 'dynamic'/1:$11, 'abolish'/1:$12, 'index'/3:$13, 'compile_time_only'/1:$14])

$17:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	retry($13)
	trust($14)

$18:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	retry($13)
	retry($14)
	trust($15)

$1:
	get_structure('op', 3, 0)
	unify_void(3)
	proceed

$2:
	get_structure('op', 4, 0)
	unify_void(4)
	proceed

$3:
	get_structure('obvar_prefix', 1, 0)
	unify_void(1)
	proceed

$4:
	get_structure('obvar_prefix', 2, 0)
	unify_void(2)
	proceed

$5:
	get_structure('remove_obvar_prefix', 1, 0)
	unify_void(1)
	proceed

$6:
	get_structure('remove_obvar_prefix', 2, 0)
	unify_void(2)
	proceed

$7:
	get_structure('op_table', 1, 0)
	unify_void(1)
	proceed

$8:
	get_structure('op_table_inherit', 2, 0)
	unify_void(2)
	proceed

$9:
	get_structure('inline', 2, 0)
	unify_void(2)
	proceed

$10:
	get_structure('inline', 3, 0)
	unify_void(3)
	proceed

$11:
	get_structure('dynamic', 1, 0)
	unify_void(1)
	proceed

$12:
	get_structure('abolish', 1, 0)
	unify_void(1)
	proceed

$13:
	get_structure('index', 3, 0)
	unify_void(3)
	proceed

$14:
	get_structure('compile_time_only', 1, 0)
	unify_void(1)
	proceed

$15:
	get_constant('chr_init', 0)
	proceed
end('$is_compiler_call'/1):



'$for_compiler_only'/1:

	switch_on_term(0, $5, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$4, 'index'/3:$1, 'compile_time_only'/1:$2])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_structure('index', 3, 0)
	unify_void(3)
	proceed

$2:
	get_structure('compile_time_only', 1, 0)
	unify_void(1)
	proceed
end('$for_compiler_only'/1):



'compile_time_only'/1:


$1:
	execute_predicate('call', 1)
end('compile_time_only'/1):



