'$compile_pred/3$0/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(11)
	get_y_variable(9, 0)
	get_y_variable(8, 1)
	get_y_variable(10, 2)
	get_y_variable(1, 3)
	get_y_level(0)
	put_y_variable(7, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(6, 2)
	put_y_variable(5, 3)
	call_predicate('$correct_pred_arity', 4, 11)
	put_y_value(2, 0)
	get_structure('/', 2, 0)
	unify_y_value(6)
	unify_y_value(5)
	put_y_value(10, 0)
	put_y_value(7, 1)
	call_predicate('$pretrans_clauses', 2, 10)
	put_y_value(7, 0)
	put_y_value(9, 1)
	put_y_value(8, 2)
	put_y_value(3, 3)
	put_y_value(1, 4)
	call_predicate('$flatten_clauses', 5, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_constant('[]', 4)
	call_predicate('$compile_index', 5, 5)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$warg', 2, 5)
	put_y_value(1, 0)
	call_predicate('$colon', 1, 5)
	put_y_value(1, 0)
	call_predicate('nl', 1, 5)
	put_y_value(1, 0)
	call_predicate('nl', 1, 5)
	put_y_value(4, 0)
	put_y_value(1, 1)
	call_predicate('$write_instr_nice', 2, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('$compileclauses', 2, 3)
	put_y_value(1, 0)
	put_constant('end(', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$warg', 2, 2)
	put_y_value(1, 0)
	put_integer(41, 1)
	call_predicate('put', 2, 2)
	put_y_value(1, 0)
	call_predicate('$colon', 1, 2)
	put_y_value(1, 0)
	call_predicate('nl', 1, 2)
	put_y_value(1, 0)
	call_predicate('nl', 1, 2)
	put_y_value(1, 0)
	call_predicate('nl', 1, 2)
	put_y_value(1, 0)
	call_predicate('nl', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$compile_pred/3$0/4$0'/4):



'$compile_pred/3$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$compile_pred/3$0/4$0', 4, 1)
	cut(0)
	fail

$2:
	proceed
end('$compile_pred/3$0'/4):



'$compile_pred'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '/'/2:$5])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$6:
	try(3, $1)
	trust($2)

$1:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_x_variable(3, 1)
	pseudo_instr0(16)
	allocate(1)
	get_y_level(0)
	put_x_value(4, 1)
	call_predicate('$compile_pred/3$0', 4, 1)
	pseudo_instr0(17)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(3, 0)
	pseudo_instr0(17)
	put_structure(2, 0)
	set_constant(':')
	set_constant('fail to compile predicate')
	set_x_value(3)
	allocate(0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$compile_pred'/3):



'$compileclauses'/2:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(2, $2)
	trust($3)

$5:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('clause', 2, 0)
	allocate(2)
	unify_y_variable(1)
	unify_x_variable(2)
	get_y_variable(0, 1)
	put_structure(1, 0)
	set_constant('comment')
	set_y_value(1)
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	put_y_value(0, 1)
	call_predicate('$write_instr_nice', 2, 2)
	pseudo_instr2(95, 21, 0)
	put_y_value(0, 1)
	call_predicate('$compileclause', 2, 0)
	fail

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$compileclauses', 2)
end('$compileclauses'/2):



'$compileclause'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(1, 1)
	get_y_level(0)
	put_y_variable(2, 19)
	call_predicate('$ignore_delays', 0, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$internal_form', 2, 3)
	put_constant('compile', 1)
	pseudo_instr4(12, 22, 1, 21, 0)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant(':')
	set_constant('fail to compile clause')
	set_x_value(2)
	allocate(0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$compileclause'/2):



