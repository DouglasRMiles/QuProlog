'read'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('read', 2)
end('read'/1):



'read'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('read_term', 3)
end('read'/2):



'read_1_term'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(27, 0)
	put_x_value(3, 1)
	execute_predicate('read_1_term', 3)
end('read_1_term'/2):



'read_1_term'/3:


$1:
	put_structure(1, 3)
	set_constant('variable_names')
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	execute_predicate('read_term', 3)
end('read_1_term'/3):



'readR'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('readR', 2)
end('readR'/1):



'readR_1_term'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(27, 0)
	put_x_value(3, 1)
	execute_predicate('readR_1_term', 3)
end('readR_1_term'/2):



'readR'/2:


$1:
	put_structure(1, 3)
	set_constant('remember_name')
	set_constant('true')
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	execute_predicate('read_term', 3)
end('readR'/2):



'readR_1_term'/3:


$1:
	put_structure(1, 3)
	set_constant('remember_name')
	set_constant('true')
	put_list(4)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 3)
	set_constant('variable_names')
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_x_value(4)
	execute_predicate('read_term', 3)
end('readR_1_term'/3):



'read_term'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(27, 0)
	put_x_value(3, 1)
	execute_predicate('read_term', 3)
end('read_term'/2):



'read_term/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('closed_list', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('read_term/3$0'/1):



'read_term'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('read_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('read_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('read_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(14)
	get_y_variable(2, 1)
	get_y_variable(12, 2)
	get_y_level(13)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 14)
	pseudo_instr2(101, 21, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	put_y_value(1, 0)
	put_constant('input', 1)
	call_predicate('stream_property', 2, 14)
	put_y_value(12, 0)
	call_predicate('closed_list', 1, 14)
	cut(13)
	put_y_value(0, 0)
	get_structure('rflags', 6, 0)
	unify_y_value(11)
	unify_y_value(9)
	unify_y_value(7)
	unify_y_value(5)
	unify_y_value(4)
	unify_y_value(3)
	put_y_value(12, 0)
	put_y_value(10, 1)
	put_y_value(8, 2)
	put_y_value(6, 3)
	put_y_value(11, 4)
	put_y_value(9, 5)
	put_y_value(7, 6)
	put_y_value(5, 7)
	put_y_value(4, 8)
	put_y_value(3, 9)
	call_predicate('$set_read_options', 10, 12)
	put_structure(2, 0)
	set_constant(',')
	set_y_value(10)
	set_y_value(11)
	put_structure(2, 1)
	set_constant(',')
	set_constant('fail')
	set_constant('[]')
	call_predicate('$io_try_eq', 2, 10)
	put_structure(2, 0)
	set_constant(',')
	set_y_value(8)
	set_y_value(9)
	put_structure(2, 1)
	set_constant(',')
	set_constant('fail')
	set_constant('[]')
	call_predicate('$io_try_eq', 2, 8)
	put_structure(2, 0)
	set_constant(',')
	set_y_value(6)
	set_y_value(7)
	put_structure(2, 1)
	set_constant(',')
	set_constant('fail')
	set_constant('[]')
	call_predicate('$io_try_eq', 2, 6)
	put_y_value(5, 0)
	put_constant('false', 1)
	call_predicate('$io_try_eq', 2, 5)
	put_constant('$current_obvar_prefix_table', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(1, 0)
	put_y_value(4, 0)
	call_predicate('$io_try_eq', 2, 4)
	put_constant('$current_op_table', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(1, 0)
	put_y_value(3, 0)
	call_predicate('$io_try_eq', 2, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$read_term', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('read_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('read_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('read_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(0, 0)
	call_predicate('read_term/3$0', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('read_term')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('read_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('read_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(3, 1)
	put_constant('stream', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('read_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('read_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('read_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('read_term'/3):



'$set_read_options'/10:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(10, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(10)
	unify_y_variable(9)
	get_y_variable(8, 1)
	get_y_variable(7, 2)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	get_y_variable(1, 8)
	get_y_variable(0, 9)
	call_predicate('$set_read_options1', 10, 10)
	put_y_value(9, 0)
	put_y_value(8, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	put_y_value(1, 8)
	put_y_value(0, 9)
	deallocate
	execute_predicate('$set_read_options', 10)
end('$set_read_options'/10):



'$set_read_options1'/10:

	switch_on_term(0, $9, 'fail', 'fail', $7, 'fail', 'fail')

$7:
	switch_on_structure(0, 16, ['$default':'fail', '$'/0:$8, 'variables'/1:$1, 'variable_names'/1:$2, 'singletons'/1:$3, 'remember_name'/1:$4, 'obvar_prefix_table'/1:$5, 'op_table'/1:$6])

$8:
	try(10, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$9:
	try(10, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_constant('true', 1)
	get_structure('variables', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 4)
	proceed

$2:
	get_constant('true', 2)
	get_structure('variable_names', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 5)
	proceed

$3:
	get_constant('true', 3)
	get_structure('singletons', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 6)
	proceed

$4:
	get_structure('remember_name', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 7)
	proceed

$5:
	get_structure('obvar_prefix_table', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 8)
	proceed

$6:
	get_structure('op_table', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 9)
	proceed
end('$set_read_options1'/10):



'$read_term/3$0'/5:

	switch_on_term(0, $5, $4, $5, $4, $4, $4)

$4:
	try(5, $2)
	trust($3)

$5:
	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_list(0)
	unify_x_value(1)
	unify_constant('[]')
	put_constant('end_of_file', 0)
	get_x_value(1, 0)
	proceed

$2:
	put_x_value(1, 3)
	allocate(1)
	put_y_variable(0, 4)
	put_integer(1200, 1)
	call_predicate('$parse_term', 5, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$check_left_over', 1)

$3:
	get_x_variable(1, 4)
	pseudo_instr2(43, 3, 2)
	execute_predicate('$report_syntax_error', 3)
end('$read_term/3$0'/5):



'$read_term'/3:


$1:
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(2, 1)
	get_y_variable(5, 2)
	pseudo_instr2(43, 26, 0)
	get_y_variable(4, 0)
	get_y_level(0)
	put_y_variable(1, 19)
	put_y_value(6, 0)
	put_y_variable(3, 1)
	put_y_value(4, 3)
	call_predicate('$read_tokens', 4, 7)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(5, 2)
	put_y_value(6, 3)
	put_y_value(4, 4)
	call_predicate('$read_term/3$0', 5, 3)
	put_y_value(2, 0)
	get_y_value(1, 0)
	cut(0)
	deallocate
	proceed
end('$read_term'/3):



'$check_left_over'/1:

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
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_x_variable(1, 0)
	put_integer(7, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$check_left_over'/1):



'$read_tokens/4$0'/6:

	try(6, $1)
	trust($2)

$1:
	get_x_variable(6, 0)
	get_x_variable(7, 1)
	get_x_variable(0, 2)
	pseudo_instr1(1, 6)
	neck_cut
	put_integer(1, 2)
	pseudo_instr3(1, 2, 7, 1)
	put_integer(2, 3)
	pseudo_instr3(1, 3, 7, 2)
	put_integer(3, 4)
	pseudo_instr3(1, 4, 7, 3)
	put_constant('[]', 4)
	execute_predicate('$collect_var_tables', 5)

$2:
	get_x_variable(0, 4)
	get_x_variable(1, 5)
	pseudo_instr2(43, 3, 2)
	execute_predicate('$report_syntax_error', 3)
end('$read_tokens/4$0'/6):



'$read_tokens'/4:


$1:
	allocate(8)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(7, 1)
	put_y_variable(6, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(4, 2)
	put_y_value(1, 3)
	put_y_value(5, 4)
	put_y_value(3, 5)
	put_y_value(0, 6)
	put_integer(0, 7)
	call_predicate('$collect_tokens', 8, 6)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$read_tokens/4$0', 6)
end('$read_tokens'/4):



'$collect_tokens/8$0'/3:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', 5:$1, 8:$2, 0:$3])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	put_integer(5, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(8, 1)
	get_x_value(0, 1)
	proceed

$3:
	put_integer(0, 3)
	get_x_value(0, 3)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_constant('true', 0)
	get_x_value(2, 0)
	proceed
end('$collect_tokens/8$0'/3):



'$collect_tokens/8$1/7$0'/8:

	try(8, $1)
	trust($2)

$1:
	allocate(8)
	get_y_variable(7, 2)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	put_constant('}', 2)
	pseudo_instr2(110, 0, 2)
	neck_cut
	put_x_value(1, 0)
	get_list(0)
	unify_constant('{')
	unify_x_ref(0)
	get_list(0)
	unify_constant('}')
	unify_y_variable(2)
	put_y_value(7, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(7, 4)
	put_y_value(5, 5)
	put_y_value(4, 6)
	put_y_value(3, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$2:
	get_x_variable(8, 0)
	get_x_variable(9, 2)
	get_x_variable(10, 4)
	get_x_variable(11, 5)
	get_x_variable(0, 7)
	pseudo_instr2(69, 6, 2)
	get_x_variable(7, 2)
	get_list(1)
	unify_constant('{')
	unify_x_ref(1)
	get_list(1)
	unify_constant('(')
	unify_x_variable(2)
	put_x_value(8, 1)
	put_x_value(9, 4)
	put_x_value(10, 5)
	put_x_value(11, 6)
	execute_predicate('$collect_tokens', 8)
end('$collect_tokens/8$1/7$0'/8):



'$collect_tokens/8$1'/7:

	try(7, $1)
	retry($2)
	trust($3)

$1:
	allocate(8)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	put_constant('{', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	put_y_value(7, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(0, 0)
	put_y_value(6, 1)
	put_y_value(7, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	deallocate
	execute_predicate('$collect_tokens/8$1/7$0', 8)

$2:
	allocate(8)
	get_y_variable(7, 1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	put_constant('}', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	pseudo_instr2(70, 6, 0)
	get_y_variable(3, 0)
	put_x_value(2, 0)
	get_list(0)
	unify_constant(')')
	unify_x_ref(0)
	get_list(0)
	unify_constant('}')
	unify_y_variable(2)
	put_y_value(7, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(7, 4)
	put_y_value(5, 5)
	put_y_value(4, 6)
	put_y_value(3, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$3:
	allocate(8)
	get_y_variable(7, 1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	put_x_value(2, 1)
	get_list(1)
	unify_x_value(0)
	unify_y_variable(2)
	put_y_value(7, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(7, 4)
	put_y_value(5, 5)
	put_y_value(4, 6)
	put_y_value(3, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)
end('$collect_tokens/8$1'/7):



'$collect_tokens/8$2'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_integer(5, 1)
	pseudo_instr3(1, 1, 23, 0)
	get_x_variable(1, 0)
	get_y_level(4)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	call_predicate('$check_obvar_syntax', 2, 5)
	cut(4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	call_predicate('$read_obvar', 3, 3)
	put_y_value(1, 0)
	get_structure('obvar', 2, 0)
	unify_y_value(0)
	unify_y_value(2)
	deallocate
	proceed

$2:
	get_x_variable(3, 0)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(0, 0)
	put_x_value(3, 2)
	call_predicate('$read_var', 3, 3)
	put_y_value(1, 0)
	get_structure('var', 2, 0)
	unify_y_value(0)
	unify_y_value(2)
	deallocate
	proceed
end('$collect_tokens/8$2'/3):



'$collect_tokens/8$3'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('member', 2)

$2:
	proceed
end('$collect_tokens/8$3'/2):



'$collect_tokens/8$4/5$0/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('member', 2)

$2:
	proceed
end('$collect_tokens/8$4/5$0/2$0'/2):



'$collect_tokens/8$4/5$0'/2:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$collect_tokens/8$4/5$0/2$0', 2, 1)
	cut(0)
	deallocate
	proceed
end('$collect_tokens/8$4/5$0'/2):



'$collect_tokens/8$4'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	put_integer(5, 1)
	pseudo_instr3(1, 1, 25, 0)
	get_x_variable(1, 0)
	get_y_level(6)
	put_y_variable(3, 19)
	put_y_value(4, 0)
	call_predicate('$check_obvar_syntax', 2, 7)
	cut(6)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(5, 2)
	call_predicate('$read_obvar', 3, 5)
	put_y_value(2, 0)
	get_structure('obvar', 2, 0)
	unify_y_value(3)
	unify_y_value(4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$collect_tokens/8$4/5$0', 2, 3)
	put_y_value(0, 0)
	get_list(0)
	unify_y_value(2)
	unify_y_value(1)
	deallocate
	proceed

$2:
	put_x_value(2, 0)
	get_structure('atom', 1, 0)
	unify_x_value(1)
	get_x_value(4, 3)
	proceed
end('$collect_tokens/8$4'/5):



'$collect_tokens/8$5/6$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '}':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_constant('}', 3)
	get_x_value(0, 3)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_constant(')')
	unify_x_ref(0)
	get_list(0)
	unify_constant(',')
	unify_x_ref(0)
	get_list(0)
	unify_constant('(')
	unify_x_value(2)
	proceed
end('$collect_tokens/8$5/6$0'/3):



'$collect_tokens/8$5'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(9)
	get_y_variable(7, 0)
	get_y_variable(6, 1)
	get_y_variable(8, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 27)
	neck_cut
	put_y_variable(0, 19)
	put_y_value(6, 0)
	put_y_variable(2, 1)
	put_y_variable(1, 2)
	call_predicate('$read_next_token_or_nl', 3, 9)
	put_y_value(1, 0)
	put_y_value(8, 1)
	put_y_value(0, 2)
	call_predicate('$collect_tokens/8$5/6$0', 3, 8)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_y_value(5, 3)
	put_y_value(6, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(7, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$2:
	put_constant('[]', 0)
	get_x_value(2, 0)
	put_constant('[]', 0)
	get_x_value(3, 0)
	proceed
end('$collect_tokens/8$5'/6):



'$collect_tokens/8$6'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('member', 2)

$2:
	proceed
end('$collect_tokens/8$6'/2):



'$collect_tokens/8$7/7$0'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	put_integer(2, 1)
	pseudo_instr2(110, 0, 1)
	proceed

$2:
	put_integer(4, 1)
	pseudo_instr2(110, 0, 1)
	proceed

$3:
	put_integer(6, 1)
	pseudo_instr2(110, 0, 1)
	proceed

$4:
	put_integer(7, 1)
	pseudo_instr2(110, 0, 1)
	proceed
end('$collect_tokens/8$7/7$0'/1):



'$collect_tokens/8$7/7$1/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('member', 2)

$2:
	proceed
end('$collect_tokens/8$7/7$1/2$0'/2):



'$collect_tokens/8$7/7$1'/2:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$collect_tokens/8$7/7$1/2$0', 2, 1)
	cut(0)
	deallocate
	proceed
end('$collect_tokens/8$7/7$1'/2):



'$collect_tokens/8$7'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(4, 1)
	get_y_variable(5, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	get_y_level(6)
	put_y_variable(3, 19)
	call_predicate('$collect_tokens/8$7/7$0', 1, 7)
	cut(6)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(5, 2)
	call_predicate('$read_obvar', 3, 5)
	put_y_value(2, 0)
	get_structure('obvar', 2, 0)
	unify_y_value(3)
	unify_y_value(4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$collect_tokens/8$7/7$1', 2, 3)
	put_y_value(0, 0)
	get_list(0)
	unify_y_value(2)
	unify_y_value(1)
	deallocate
	proceed

$2:
	put_list(0)
	set_x_value(1)
	set_x_value(6)
	put_list(1)
	set_constant('!')
	set_x_value(0)
	put_integer(15, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$collect_tokens/8$7'/7):



'$collect_tokens'/8:

	switch_on_term(0, $19, 'fail', 'fail', 'fail', 'fail', $17)

$17:
	switch_on_constant(0, 32, ['$default':'fail', 0:$18, 1:$3, 3:$4, 2:$5, 4:$6, 5:$7, 6:$8, 7:$9, 8:$10, 9:$11, 10:$12, 11:$13, 12:$14, 13:$15, 14:$16])

$18:
	try(8, $1)
	trust($2)

$19:
	try(8, $1)
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
	retry($15)
	trust($16)

$1:
	get_integer(0, 0)
	get_integer(0, 1)
	neck_cut
	fail

$2:
	get_integer(0, 0)
	get_constant('[]', 2)
	get_constant('[]', 3)
	get_constant('true', 6)
	allocate(6)
	get_y_variable(0, 1)
	get_y_variable(5, 4)
	get_y_level(2)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	call_predicate('repeat', 0, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('$read_next_token_or_nl', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	call_predicate('$collect_tokens/8$0', 3, 3)
	cut(2)
	pseudo_instr1(1, 21)
	put_constant('$read_error_code', 0)
	pseudo_instr2(74, 0, 20)
	put_constant('$read_error_left', 0)
	put_integer(0, 1)
	pseudo_instr2(74, 0, 1)
	deallocate
	proceed

$3:
	get_integer(1, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 4)
	get_x_variable(4, 5)
	get_x_variable(5, 6)
	get_x_variable(6, 7)
	execute_predicate('$collect_tokens/8$1', 7)

$4:
	get_integer(3, 0)
	get_list(2)
	unify_x_ref(0)
	allocate(8)
	unify_y_variable(7)
	get_structure('number', 1, 0)
	unify_x_value(1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$5:
	get_integer(2, 0)
	allocate(11)
	get_y_variable(4, 1)
	get_list(2)
	unify_y_variable(2)
	unify_y_variable(10)
	get_list(3)
	unify_y_value(2)
	unify_y_variable(1)
	get_y_variable(9, 4)
	get_y_variable(3, 5)
	get_y_variable(8, 6)
	get_y_variable(7, 7)
	get_y_level(0)
	put_y_value(9, 0)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	call_predicate('$read_next_token_or_nl', 3, 11)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(10, 2)
	put_y_value(1, 3)
	put_y_value(9, 4)
	put_y_value(3, 5)
	put_y_value(8, 6)
	put_y_value(7, 7)
	call_predicate('$collect_tokens', 8, 5)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	call_predicate('$collect_tokens/8$2', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$collect_tokens/8$3', 2, 1)
	cut(0)
	deallocate
	proceed

$6:
	get_integer(4, 0)
	allocate(11)
	get_y_variable(4, 1)
	get_list(2)
	unify_y_variable(3)
	unify_y_variable(10)
	get_y_variable(2, 3)
	get_y_variable(9, 4)
	get_y_variable(1, 5)
	get_y_variable(8, 6)
	get_y_variable(7, 7)
	put_y_variable(0, 19)
	put_y_value(9, 0)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	call_predicate('$read_next_token_or_nl', 3, 11)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(10, 2)
	put_y_value(0, 3)
	put_y_value(9, 4)
	put_y_value(1, 5)
	put_y_value(8, 6)
	put_y_value(7, 7)
	call_predicate('$collect_tokens', 8, 5)
	put_y_value(1, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	deallocate
	execute_predicate('$collect_tokens/8$4', 5)

$7:
	get_integer(5, 0)
	get_x_variable(1, 4)
	get_x_variable(4, 5)
	get_x_variable(5, 6)
	get_x_variable(0, 7)
	execute_predicate('$collect_tokens/8$5', 6)

$8:
	get_integer(6, 0)
	get_list(2)
	unify_x_variable(0)
	allocate(8)
	unify_y_variable(7)
	get_list(3)
	unify_x_value(0)
	unify_y_variable(6)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	get_structure('var', 2, 0)
	unify_void(1)
	unify_x_value(1)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$9:
	get_integer(7, 0)
	get_list(2)
	unify_x_ref(0)
	allocate(8)
	unify_y_variable(7)
	get_structure('atom', 1, 0)
	unify_x_value(1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$10:
	get_integer(8, 0)
	get_constant('[]', 3)
	get_list(2)
	unify_constant('end_of_file')
	unify_constant('[]')
	proceed

$11:
	get_integer(9, 0)
	get_list(2)
	unify_x_ref(0)
	allocate(8)
	unify_y_variable(7)
	get_structure('string', 1, 0)
	unify_x_value(1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$12:
	get_integer(10, 0)
	allocate(13)
	get_y_variable(5, 1)
	get_list(2)
	unify_y_variable(2)
	unify_y_variable(12)
	get_y_variable(1, 3)
	get_y_variable(11, 4)
	get_y_variable(6, 5)
	get_y_variable(10, 6)
	get_y_variable(9, 7)
	get_y_level(3)
	put_y_variable(4, 19)
	put_y_variable(0, 19)
	put_y_value(11, 0)
	put_y_variable(8, 1)
	put_y_variable(7, 2)
	call_predicate('$read_next_token_or_nl', 3, 13)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(12, 2)
	put_y_value(0, 3)
	put_y_value(11, 4)
	put_y_value(6, 5)
	put_y_value(10, 6)
	put_y_value(9, 7)
	call_predicate('$collect_tokens', 8, 7)
	put_y_value(4, 0)
	put_y_value(5, 1)
	put_y_value(6, 2)
	call_predicate('$read_obvar', 3, 6)
	put_y_value(2, 0)
	get_structure('obvar', 2, 0)
	unify_y_value(4)
	unify_y_value(5)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$collect_tokens/8$6', 2, 4)
	cut(3)
	put_y_value(1, 0)
	get_list(0)
	unify_y_value(2)
	unify_y_value(0)
	deallocate
	proceed

$13:
	get_integer(11, 0)
	get_list(2)
	allocate(12)
	unify_y_variable(6)
	unify_y_variable(5)
	get_y_variable(4, 3)
	get_y_variable(11, 4)
	get_y_variable(3, 5)
	get_y_variable(10, 6)
	get_y_variable(9, 7)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(0, 19)
	put_y_value(11, 0)
	put_y_variable(2, 1)
	put_y_variable(1, 2)
	call_predicate('$read_next_token_or_nl', 3, 12)
	put_y_value(11, 0)
	put_y_value(8, 1)
	put_y_value(7, 2)
	call_predicate('$read_next_token_or_nl', 3, 12)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(5, 2)
	put_y_value(0, 3)
	put_y_value(11, 4)
	put_y_value(3, 5)
	put_y_value(10, 6)
	put_y_value(9, 7)
	call_predicate('$collect_tokens', 8, 7)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(6, 3)
	put_y_value(0, 4)
	put_y_value(4, 5)
	put_y_value(5, 6)
	deallocate
	execute_predicate('$collect_tokens/8$7', 7)

$14:
	get_integer(12, 0)
	get_list(2)
	unify_constant('quant_escape')
	allocate(8)
	unify_y_variable(7)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$15:
	get_integer(13, 0)
	allocate(8)
	get_y_variable(7, 2)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)

$16:
	get_integer(14, 0)
	get_list(2)
	unify_x_ref(0)
	allocate(8)
	unify_y_variable(7)
	get_structure('double', 1, 0)
	unify_x_value(1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_next_token_or_nl', 3, 8)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$collect_tokens', 8)
end('$collect_tokens'/8):



'$read_next_token_or_nl'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(1, 1)
	get_y_variable(2, 2)
	get_y_level(0)
	call_predicate('repeat', 0, 4)
	pseudo_instr3(35, 23, 0, 1)
	get_y_value(1, 0)
	get_y_value(2, 1)
	put_integer(13, 0)
	pseudo_instr2(133, 21, 0)
	cut(0)
	deallocate
	proceed
end('$read_next_token_or_nl'/3):



'$read_var'/3:

	try(3, $1)
	trust($2)

$1:
	put_integer(4, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_x_variable(2, 3)
	put_constant('true', 3)
	get_x_value(2, 3)
	neck_cut
	pseudo_instr2(56, 2, 1)
	get_x_value(0, 2)
	proceed

$2:
	proceed
end('$read_var'/3):



'$read_obvar'/3:

	try(3, $1)
	trust($2)

$1:
	put_integer(4, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_x_variable(2, 3)
	put_constant('true', 3)
	get_x_value(2, 3)
	neck_cut
	pseudo_instr2(57, 2, 1)
	get_x_value(0, 2)
	proceed

$2:
	pseudo_instr1(36, 1)
	get_x_value(0, 1)
	proceed
end('$read_obvar'/3):



'$collect_var_tables/5$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('[]', 2)
	pseudo_instr3(6, 0, 2, 1)
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_value(2, 1)
	execute_predicate('search_insert', 2)
end('$collect_var_tables/5$0'/2):



'$collect_var_tables/5$1/3$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '_':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('_', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$collect_var_tables/5$1/3$0'/1):



'$collect_var_tables/5$1'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	put_constant('[]', 2)
	pseudo_instr3(6, 0, 2, 1)
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_y_value(1, 0)
	call_predicate('$collect_var_tables/5$1/3$0', 1, 3)
	put_structure(2, 0)
	set_constant('=')
	set_y_value(0)
	set_y_value(1)
	put_y_value(2, 1)
	deallocate
	execute_predicate('search_insert', 2)

$3:
	proceed
end('$collect_var_tables/5$1'/3):



'$collect_var_tables/5$2/6$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_integer(1, 2)
	put_constant('_', 3)
	pseudo_instr4(1, 0, 2, 3, 1)
	put_integer(1, 0)
	get_x_value(1, 0)
	neck_cut
	fail

$2:
	proceed
end('$collect_var_tables/5$2/6$0'/1):



'$collect_var_tables/5$2/6$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$collect_var_tables/5$2/6$1'/2):



'$collect_var_tables/5$2/6$2'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$collect_var_tables/5$2/6$2'/2):



'$collect_var_tables/5$2'/6:

	try(6, $1)
	retry($2)
	trust($3)

$1:
	put_constant('[]', 2)
	pseudo_instr3(6, 0, 2, 1)
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	allocate(6)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(0, 5)
	put_y_value(1, 0)
	call_predicate('$collect_var_tables/5$2/6$0', 1, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	call_predicate('$collect_var_tables/5$2/6$1', 2, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	call_predicate('$collect_var_tables/5$2/6$2', 2, 3)
	put_structure(2, 0)
	set_constant('=')
	set_y_value(0)
	set_y_value(1)
	put_y_value(2, 1)
	deallocate
	execute_predicate('search_insert', 2)

$3:
	proceed
end('$collect_var_tables/5$2'/6):



'$collect_var_tables'/5:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(5, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	call_predicate('open_to_closed', 1, 2)
	put_y_value(1, 0)
	call_predicate('open_to_closed', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('open_to_closed', 1)

$2:
	get_list(0)
	allocate(9)
	unify_y_variable(8)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_variable(5, 4)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 28, 0)
	get_y_variable(7, 0)
	put_integer(2, 1)
	pseudo_instr3(1, 1, 28, 0)
	get_y_variable(4, 0)
	get_y_level(6)
	put_y_value(2, 0)
	put_y_value(7, 1)
	call_predicate('$collect_var_tables/5$0', 2, 9)
	put_y_value(1, 0)
	put_y_value(4, 1)
	put_y_value(7, 2)
	call_predicate('$collect_var_tables/5$1', 3, 9)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(8, 2)
	put_y_value(3, 3)
	put_y_value(5, 4)
	put_y_value(7, 5)
	call_predicate('$collect_var_tables/5$2', 6, 7)
	cut(6)
	put_x_variable(4, 0)
	get_list(0)
	unify_y_value(4)
	unify_y_value(5)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$collect_var_tables', 5)
end('$collect_var_tables'/5):



'$parse_term'/5:

	switch_on_term(0, $3, 'fail', $1, 'fail', 'fail', $2)

$3:
	try(5, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(6)
	get_x_variable(7, 1)
	get_x_variable(8, 2)
	get_x_variable(9, 3)
	get_x_variable(5, 4)
	put_x_value(6, 1)
	put_x_value(7, 2)
	put_x_value(8, 3)
	put_x_value(9, 4)
	execute_predicate('$parse_start_term', 6)

$2:
	get_constant('[]', 0)
	put_integer(8, 0)
	put_constant('[]', 1)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_term'/5):



'$parse_start_term/6$0'/6:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'atom'/1:$5])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$6:
	try(6, $1)
	trust($2)

$1:
	get_x_variable(6, 0)
	get_x_variable(0, 1)
	allocate(7)
	get_y_variable(5, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	put_x_value(6, 1)
	get_structure('atom', 1, 1)
	unify_y_variable(2)
	get_y_level(6)
	put_y_value(2, 1)
	put_y_variable(4, 2)
	call_predicate('$check_quantop', 3, 7)
	cut(6)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(6, 0)
	get_x_variable(7, 1)
	get_x_variable(1, 2)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_list(0)
	set_x_value(6)
	set_x_value(5)
	put_x_value(7, 2)
	execute_predicate('$parse_term', 5)
end('$parse_start_term/6$0'/6):



'$parse_start_term/6$1'/1:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(1, $1)
	trust($2)

$1:
	get_list(0)
	unify_constant('(')
	unify_void(1)
	neck_cut
	fail

$2:
	proceed
end('$parse_start_term/6$1'/1):



'$parse_start_term'/6:

	switch_on_term(0, $35, $20, $20, $21, $20, $29)

$21:
	switch_on_structure(0, 16, ['$default':$20, '$'/0:$22, 'var'/2:$23, 'string'/1:$24, 'atom'/1:$25, 'number'/1:$26, 'double'/1:$27, 'obvar'/2:$28])

$22:
	try(6, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($11)
	retry($12)
	retry($13)
	trust($20)

$23:
	try(6, $1)
	trust($20)

$24:
	try(6, $2)
	trust($20)

$25:
	try(6, $3)
	retry($4)
	retry($5)
	retry($6)
	retry($11)
	retry($12)
	retry($13)
	trust($20)

$26:
	try(6, $7)
	trust($20)

$27:
	try(6, $8)
	trust($20)

$28:
	try(6, $9)
	trust($20)

$29:
	switch_on_constant(0, 16, ['$default':$20, 'quant_escape':$30, '[':$31, '(':$32, ' (':$33, '{':$34])

$30:
	try(6, $10)
	trust($20)

$31:
	try(6, $14)
	retry($15)
	trust($20)

$32:
	try(6, $16)
	trust($20)

$33:
	try(6, $17)
	trust($20)

$34:
	try(6, $18)
	retry($19)
	trust($20)

$35:
	try(6, $1)
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
	retry($15)
	retry($16)
	retry($17)
	retry($18)
	retry($19)
	trust($20)

$1:
	get_structure('var', 2, 0)
	unify_x_variable(7)
	unify_void(1)
	get_x_variable(0, 1)
	get_x_variable(8, 3)
	get_x_variable(9, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(7, 1)
	put_x_value(2, 3)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$2:
	get_structure('string', 1, 0)
	unify_x_variable(7)
	get_x_variable(0, 1)
	get_x_variable(8, 3)
	get_x_variable(9, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(7, 1)
	put_x_value(2, 3)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$3:
	get_structure('atom', 1, 0)
	unify_constant('-')
	get_list(1)
	unify_x_ref(1)
	unify_x_variable(0)
	get_structure('number', 1, 1)
	unify_x_variable(1)
	get_x_variable(7, 3)
	get_x_variable(8, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_variable(4, 5)
	get_structure('-', 1, 5)
	unify_x_value(1)
	pseudo_instr2(0, 3, 4)
	get_x_variable(1, 3)
	put_x_value(2, 3)
	put_x_value(7, 4)
	put_x_value(8, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$4:
	get_structure('atom', 1, 0)
	unify_constant('-')
	get_list(1)
	unify_x_ref(1)
	unify_x_variable(0)
	get_structure('double', 1, 1)
	unify_x_variable(1)
	get_x_variable(7, 3)
	get_x_variable(8, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_variable(4, 5)
	get_structure('-', 1, 5)
	unify_x_value(1)
	pseudo_instr2(0, 3, 4)
	get_x_variable(1, 3)
	put_x_value(2, 3)
	put_x_value(7, 4)
	put_x_value(8, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$5:
	get_structure('atom', 1, 0)
	unify_constant('+')
	get_list(1)
	unify_x_ref(1)
	unify_x_variable(0)
	get_structure('number', 1, 1)
	unify_x_variable(1)
	get_x_variable(7, 3)
	get_x_variable(8, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(2, 3)
	put_x_value(7, 4)
	put_x_value(8, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$6:
	get_structure('atom', 1, 0)
	unify_constant('+')
	get_list(1)
	unify_x_ref(1)
	unify_x_variable(0)
	get_structure('double', 1, 1)
	unify_x_variable(1)
	get_x_variable(7, 3)
	get_x_variable(8, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(2, 3)
	put_x_value(7, 4)
	put_x_value(8, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$7:
	get_structure('number', 1, 0)
	unify_x_variable(7)
	get_x_variable(0, 1)
	get_x_variable(8, 3)
	get_x_variable(9, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(7, 1)
	put_x_value(2, 3)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$8:
	get_structure('double', 1, 0)
	unify_x_variable(7)
	get_x_variable(0, 1)
	get_x_variable(8, 3)
	get_x_variable(9, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(7, 1)
	put_x_value(2, 3)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$9:
	get_structure('obvar', 2, 0)
	unify_x_variable(7)
	unify_void(1)
	get_x_variable(0, 1)
	get_x_variable(8, 3)
	get_x_variable(9, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(7, 1)
	put_x_value(2, 3)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$10:
	get_constant('quant_escape', 0)
	get_list(1)
	unify_x_variable(0)
	unify_x_variable(6)
	allocate(10)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_level(7)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(5, 1)
	put_y_variable(2, 2)
	put_y_variable(9, 3)
	put_y_variable(8, 4)
	put_x_value(6, 5)
	call_predicate('$parse_start_term/6$0', 6, 10)
	put_y_value(9, 0)
	put_y_value(2, 1)
	put_y_value(8, 2)
	put_y_value(5, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	call_predicate('$parse_quant', 6, 8)
	cut(7)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	deallocate
	execute_predicate('$parse_after_term', 7)

$11:
	get_structure('atom', 1, 0)
	allocate(10)
	unify_y_variable(9)
	get_y_variable(8, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_level(7)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(5, 0)
	put_y_value(9, 1)
	put_y_variable(2, 2)
	call_predicate('$check_quantop', 3, 10)
	put_y_value(9, 0)
	put_y_value(2, 1)
	put_y_value(8, 2)
	put_y_value(5, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	call_predicate('$parse_quant', 6, 8)
	cut(7)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	deallocate
	execute_predicate('$parse_after_term', 7)

$12:
	get_structure('atom', 1, 0)
	allocate(10)
	unify_y_variable(9)
	get_y_variable(8, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(5, 0)
	put_y_value(9, 1)
	put_y_variable(2, 2)
	put_y_variable(7, 3)
	call_predicate('$check_prefixop', 4, 10)
	put_y_value(8, 0)
	call_predicate('$parse_start_term/6$1', 1, 10)
	put_y_value(9, 0)
	put_y_value(2, 1)
	put_y_value(7, 2)
	put_y_value(8, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	call_predicate('$parse_prefix', 8, 7)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	deallocate
	execute_predicate('$parse_after_term', 7)

$13:
	get_structure('atom', 1, 0)
	unify_x_variable(7)
	get_x_variable(0, 1)
	get_x_variable(8, 3)
	get_x_variable(9, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(7, 1)
	put_x_value(2, 3)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$14:
	get_constant('[', 0)
	get_list(1)
	unify_constant(']')
	unify_x_variable(0)
	get_x_variable(1, 3)
	get_x_variable(7, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(2, 3)
	put_x_value(1, 4)
	put_x_value(7, 5)
	put_constant('[]', 1)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$15:
	get_constant('[', 0)
	get_x_variable(0, 1)
	allocate(9)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	neck_cut
	get_y_level(7)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(5, 2)
	put_y_variable(2, 3)
	put_y_variable(8, 4)
	put_integer(999, 1)
	call_predicate('$parse_term', 5, 9)
	put_y_value(8, 0)
	put_y_value(1, 1)
	put_y_value(5, 2)
	put_y_value(0, 3)
	call_predicate('$parse_list_args', 4, 8)
	cut(7)
	put_y_value(0, 0)
	put_list(1)
	set_y_value(2)
	set_y_value(1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	deallocate
	execute_predicate('$parse_substitution_or_list', 6)

$16:
	get_constant('(', 0)
	get_x_variable(0, 1)
	allocate(7)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	neck_cut
	put_y_variable(0, 19)
	put_y_value(4, 2)
	put_y_variable(1, 3)
	put_y_variable(6, 4)
	put_integer(1200, 1)
	call_predicate('$parse_term', 5, 7)
	put_y_value(6, 1)
	put_y_value(0, 2)
	put_constant(')', 0)
	call_predicate('$parse_expect', 3, 6)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_integer(0, 2)
	deallocate
	execute_predicate('$parse_after_term', 7)

$17:
	get_constant(' (', 0)
	get_x_variable(0, 1)
	allocate(7)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	neck_cut
	put_y_variable(0, 19)
	put_y_value(4, 2)
	put_y_variable(1, 3)
	put_y_variable(6, 4)
	put_integer(1200, 1)
	call_predicate('$parse_term', 5, 7)
	put_y_value(6, 1)
	put_y_value(0, 2)
	put_constant(')', 0)
	call_predicate('$parse_expect', 3, 6)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_integer(0, 2)
	deallocate
	execute_predicate('$parse_after_term', 7)

$18:
	get_constant('{', 0)
	get_list(1)
	unify_constant('}')
	unify_x_variable(0)
	get_x_variable(1, 3)
	get_x_variable(7, 4)
	get_x_variable(6, 5)
	neck_cut
	put_x_value(2, 3)
	put_x_value(1, 4)
	put_x_value(7, 5)
	put_constant('{}', 1)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)

$19:
	get_constant('{', 0)
	get_x_variable(0, 1)
	allocate(7)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	neck_cut
	put_y_variable(0, 19)
	put_y_value(4, 2)
	put_y_variable(1, 3)
	put_y_variable(6, 4)
	put_integer(1200, 1)
	call_predicate('$parse_term', 5, 7)
	put_y_value(6, 1)
	put_y_value(0, 2)
	put_constant('}', 0)
	call_predicate('$parse_expect', 3, 6)
	put_y_value(0, 0)
	put_structure(1, 1)
	set_constant('{}')
	set_y_value(1)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_integer(0, 2)
	deallocate
	execute_predicate('$parse_after_term', 7)

$20:
	get_x_variable(6, 1)
	put_list(1)
	set_x_value(0)
	set_x_value(6)
	put_integer(9, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_start_term'/6):



'$parse_after_term/7$0'/12:

	try(12, $1)
	trust($2)

$1:
	get_x_variable(12, 1)
	get_x_variable(13, 2)
	get_x_variable(14, 3)
	get_x_variable(15, 4)
	get_x_variable(1, 5)
	get_x_variable(2, 6)
	get_x_variable(3, 7)
	get_x_variable(4, 8)
	get_x_variable(5, 9)
	put_structure(4, 6)
	set_constant('infix')
	set_x_value(0)
	set_x_value(12)
	set_x_value(13)
	set_x_value(14)
	put_list(0)
	set_x_value(6)
	set_x_value(15)
	execute_predicate('$parse_infix', 6)

$2:
	get_x_variable(12, 4)
	get_x_variable(1, 5)
	get_x_variable(2, 6)
	get_x_variable(3, 7)
	get_x_variable(4, 8)
	get_x_variable(5, 9)
	put_structure(3, 6)
	set_constant('postfix')
	set_x_value(0)
	set_x_value(10)
	set_x_value(11)
	put_list(0)
	set_x_value(6)
	set_x_value(12)
	execute_predicate('$parse_postfix', 6)
end('$parse_after_term/7$0'/12):



'$parse_after_term/7$1'/10:

	try(10, $1)
	trust($2)

$1:
	get_x_variable(10, 1)
	get_x_variable(11, 2)
	get_x_variable(12, 3)
	get_x_variable(1, 4)
	get_x_variable(2, 5)
	get_x_variable(3, 6)
	get_x_variable(4, 7)
	get_x_variable(5, 8)
	pseudo_instr2(2, 0, 10)
	neck_cut
	put_list(0)
	set_x_value(11)
	set_x_value(12)
	execute_predicate('$parse_infix', 6)

$2:
	put_structure(1, 0)
	set_constant('atom')
	set_x_value(9)
	put_list(1)
	set_x_value(0)
	set_x_value(3)
	put_integer(13, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_after_term/7$1'/10):



'$parse_after_term/7$2'/10:

	try(10, $1)
	trust($2)

$1:
	get_x_variable(10, 1)
	get_x_variable(11, 2)
	get_x_variable(12, 3)
	get_x_variable(1, 4)
	get_x_variable(2, 5)
	get_x_variable(3, 6)
	get_x_variable(4, 7)
	get_x_variable(5, 8)
	pseudo_instr2(2, 0, 10)
	neck_cut
	put_list(0)
	set_x_value(11)
	set_x_value(12)
	execute_predicate('$parse_postfix', 6)

$2:
	put_structure(1, 0)
	set_constant('atom')
	set_x_value(9)
	put_list(1)
	set_x_value(0)
	set_x_value(3)
	put_integer(13, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_after_term/7$2'/10):



'$parse_after_term/7$3/7$0'/9:

	try(9, $1)
	trust($2)

$1:
	get_x_variable(9, 1)
	allocate(6)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	get_y_variable(1, 8)
	put_integer(255, 1)
	pseudo_instr2(1, 0, 1)
	neck_cut
	put_y_variable(0, 0)
	put_list(4)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(9)
	set_x_value(4)
	call_predicate('=..', 2, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_integer(0, 2)
	deallocate
	execute_predicate('$parse_after_term', 7)

$2:
	get_x_variable(1, 4)
	put_integer(14, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_after_term/7$3/7$0'/9):



'$parse_after_term/7$3'/7:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(7, $1)
	trust($2)

$5:
	try(7, $1)
	trust($2)

$1:
	get_x_variable(7, 0)
	get_x_variable(0, 1)
	allocate(10)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	put_integer(0, 1)
	get_x_value(7, 1)
	neck_cut
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 3)
	put_y_variable(9, 4)
	put_integer(999, 1)
	call_predicate('$parse_term', 5, 10)
	put_y_value(9, 0)
	put_y_value(2, 1)
	put_y_value(8, 2)
	put_y_value(1, 3)
	call_predicate('$parse_args', 4, 9)
	put_y_value(2, 0)
	put_y_value(0, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 9)
	put_y_value(0, 0)
	put_y_value(7, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(6, 5)
	put_y_value(8, 6)
	put_y_value(5, 7)
	put_y_value(4, 8)
	deallocate
	execute_predicate('$parse_after_term/7$3/7$0', 9)

$2:
	get_x_variable(0, 1)
	put_list(1)
	set_constant('(')
	set_x_value(0)
	put_integer(7, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_after_term/7$3'/7):



'$parse_after_term/7$4'/7:

	try(7, $1)
	trust($2)

$1:
	get_x_variable(7, 0)
	get_x_variable(0, 1)
	allocate(7)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	put_integer(999, 1)
	pseudo_instr2(2, 7, 1)
	neck_cut
	put_y_variable(1, 3)
	put_y_variable(0, 4)
	put_integer(1000, 1)
	call_predicate('$parse_term', 5, 7)
	put_y_value(0, 0)
	put_structure(2, 1)
	set_constant(',')
	set_y_value(5)
	set_y_value(1)
	put_y_value(4, 3)
	put_y_value(6, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_integer(0, 2)
	deallocate
	execute_predicate('$parse_after_term', 7)

$2:
	get_x_variable(0, 1)
	put_list(1)
	set_constant(',')
	set_x_value(0)
	put_integer(13, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_after_term/7$4'/7):



'$parse_after_term'/7:

	switch_on_term(0, $9, $8, $9, $8, $8, $8)

$9:
	try(7, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_list(0)
	unify_x_ref(0)
	allocate(13)
	unify_y_variable(10)
	get_structure('atom', 1, 0)
	unify_y_variable(11)
	get_y_variable(9, 1)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(6, 5)
	get_y_variable(5, 6)
	get_y_level(12)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(7, 0)
	put_y_value(11, 1)
	put_y_variable(4, 2)
	put_y_variable(3, 3)
	put_y_variable(2, 4)
	call_predicate('$check_infixop', 5, 13)
	put_y_value(7, 0)
	put_y_value(11, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	call_predicate('$check_postfixop', 4, 13)
	cut(12)
	put_y_value(11, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(10, 4)
	put_y_value(9, 5)
	put_y_value(8, 6)
	put_y_value(7, 7)
	put_y_value(6, 8)
	put_y_value(5, 9)
	put_y_value(1, 10)
	put_y_value(0, 11)
	deallocate
	execute_predicate('$parse_after_term/7$0', 12)

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(11)
	unify_y_variable(8)
	get_structure('atom', 1, 0)
	unify_y_variable(9)
	get_y_variable(7, 1)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_level(10)
	put_y_value(5, 0)
	put_y_value(9, 1)
	put_y_variable(2, 2)
	put_y_variable(1, 3)
	put_y_variable(0, 4)
	call_predicate('$check_infixop', 5, 11)
	cut(10)
	put_structure(4, 1)
	set_constant('infix')
	set_y_value(9)
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_list(0)
	set_x_value(1)
	set_y_value(8)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	deallocate
	execute_predicate('$parse_infix', 6)

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(10)
	unify_y_variable(7)
	get_structure('atom', 1, 0)
	unify_y_variable(8)
	get_y_variable(6, 1)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	get_y_level(9)
	put_y_value(4, 0)
	put_y_value(8, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$check_postfixop', 4, 10)
	cut(9)
	put_structure(3, 1)
	set_constant('postfix')
	set_y_value(8)
	set_y_value(1)
	set_y_value(0)
	put_list(0)
	set_x_value(1)
	set_y_value(7)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$parse_postfix', 6)

$4:
	get_list(0)
	unify_x_variable(10)
	unify_x_variable(11)
	get_x_variable(12, 1)
	get_x_variable(0, 2)
	get_x_variable(13, 3)
	get_x_variable(14, 4)
	get_x_variable(7, 5)
	get_x_variable(8, 6)
	put_x_value(10, 1)
	get_structure('infix', 4, 1)
	unify_x_variable(9)
	unify_x_variable(1)
	unify_void(2)
	neck_cut
	put_x_value(10, 2)
	put_x_value(11, 3)
	put_x_value(12, 4)
	put_x_value(13, 5)
	put_x_value(14, 6)
	execute_predicate('$parse_after_term/7$1', 10)

$5:
	get_list(0)
	unify_x_variable(10)
	unify_x_variable(11)
	get_x_variable(12, 1)
	get_x_variable(0, 2)
	get_x_variable(13, 3)
	get_x_variable(14, 4)
	get_x_variable(7, 5)
	get_x_variable(8, 6)
	put_x_value(10, 1)
	get_structure('postfix', 3, 1)
	unify_x_variable(9)
	unify_x_variable(1)
	unify_void(1)
	neck_cut
	put_x_value(10, 2)
	put_x_value(11, 3)
	put_x_value(12, 4)
	put_x_value(13, 5)
	put_x_value(14, 6)
	execute_predicate('$parse_after_term/7$2', 10)

$6:
	get_list(0)
	unify_constant('(')
	unify_x_variable(7)
	get_x_variable(8, 1)
	get_x_variable(0, 2)
	get_x_variable(9, 3)
	get_x_variable(2, 4)
	neck_cut
	put_x_value(7, 1)
	put_x_value(8, 3)
	put_x_value(9, 4)
	execute_predicate('$parse_after_term/7$3', 7)

$7:
	get_list(0)
	unify_constant(',')
	unify_x_variable(7)
	get_x_variable(8, 1)
	get_x_variable(0, 2)
	get_x_variable(9, 3)
	get_x_variable(2, 4)
	put_integer(1000, 1)
	pseudo_instr2(2, 1, 9)
	neck_cut
	put_x_value(7, 1)
	put_x_value(8, 3)
	put_x_value(9, 4)
	execute_predicate('$parse_after_term/7$4', 7)

$8:
	get_x_value(1, 5)
	get_x_value(0, 6)
	proceed
end('$parse_after_term'/7):



'$parse_args'/4:

	switch_on_term(0, $4, $3, $4, $3, $3, $3)

$4:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_list(0)
	unify_constant(',')
	unify_x_variable(0)
	get_list(1)
	unify_x_variable(1)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	neck_cut
	put_x_value(1, 3)
	put_y_variable(0, 4)
	put_integer(999, 1)
	call_predicate('$parse_term', 5, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$parse_args', 4)

$2:
	get_constant('[]', 1)
	get_list(0)
	unify_constant(')')
	unify_x_variable(0)
	get_x_value(0, 3)
	neck_cut
	proceed

$3:
	put_x_value(0, 1)
	put_integer(10, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_args'/4):



'$parse_list_args'/4:

	switch_on_term(0, $5, $4, $5, $4, $4, $4)

$5:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_list(0)
	unify_constant(',')
	unify_x_variable(0)
	get_list(1)
	unify_x_variable(1)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	neck_cut
	put_x_value(1, 3)
	put_y_variable(0, 4)
	put_integer(999, 1)
	call_predicate('$parse_term', 5, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$parse_list_args', 4)

$2:
	get_list(0)
	unify_x_ref(4)
	unify_x_variable(0)
	get_structure('infix', 4, 4)
	unify_constant('|')
	unify_void(3)
	allocate(2)
	get_y_variable(1, 3)
	neck_cut
	put_x_value(1, 3)
	put_y_variable(0, 4)
	put_integer(999, 1)
	call_predicate('$parse_term', 5, 2)
	put_y_value(0, 1)
	put_y_value(1, 2)
	put_constant(']', 0)
	deallocate
	execute_predicate('$parse_expect', 3)

$3:
	get_constant('[]', 1)
	get_list(0)
	unify_constant(']')
	unify_x_variable(0)
	get_x_value(0, 3)
	neck_cut
	proceed

$4:
	put_x_value(0, 1)
	put_integer(11, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_list_args'/4):



'$parse_expect'/3:

	try(3, $1)
	trust($2)

$1:
	get_list(1)
	unify_x_value(0)
	unify_x_variable(0)
	get_x_value(0, 2)
	neck_cut
	proceed

$2:
	put_integer(12, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_expect'/3):



'$check_prefixop'/4:


$1:
	get_x_variable(4, 1)
	allocate(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	put_integer(6, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_variable(0, 1)
	put_y_value(2, 1)
	put_y_variable(0, 2)
	put_x_value(4, 3)
	call_predicate('current_op', 4, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$prefix_prec', 3)
end('$check_prefixop'/4):



'$prefix_prec'/3:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'fy':$1, 'fx':$2])

$4:
	try(3, $1)
	trust($2)

$1:
	get_constant('fy', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_constant('fx', 0)
	pseudo_instr2(70, 1, 0)
	get_x_value(2, 0)
	proceed
end('$prefix_prec'/3):



'$parse_prefix'/8:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_x_variable(8, 1)
	get_x_variable(1, 2)
	get_x_variable(0, 3)
	get_x_variable(3, 4)
	get_x_variable(2, 5)
	get_y_variable(1, 6)
	get_x_variable(4, 7)
	pseudo_instr2(2, 8, 3)
	put_y_variable(0, 3)
	call_predicate('$parse_term', 5, 3)
	put_integer(1, 0)
	pseudo_instr3(0, 21, 22, 0)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$parse_prefix'/8):



'$check_infixop'/5:


$1:
	get_x_variable(5, 1)
	allocate(4)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	put_integer(6, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_variable(0, 1)
	put_y_value(2, 1)
	put_y_variable(0, 2)
	put_x_value(5, 3)
	call_predicate('current_op', 4, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$infix_prec', 4)
end('$check_infixop'/5):



'$infix_prec'/4:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', 'xfx':$1, 'xfy':$2, 'yfx':$3])

$5:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_constant('xfx', 0)
	get_x_value(2, 3)
	pseudo_instr2(70, 1, 0)
	get_x_value(2, 0)
	proceed

$2:
	get_constant('xfy', 0)
	get_x_value(1, 3)
	pseudo_instr2(70, 1, 0)
	get_x_value(2, 0)
	proceed

$3:
	get_constant('yfx', 0)
	get_x_value(1, 2)
	pseudo_instr2(70, 1, 0)
	get_x_value(3, 0)
	proceed
end('$infix_prec'/4):



'$parse_infix'/6:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(6, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_ref(6)
	unify_x_variable(0)
	get_structure('infix', 4, 6)
	allocate(9)
	unify_y_variable(8)
	unify_void(1)
	unify_y_variable(5)
	unify_x_variable(6)
	get_y_variable(7, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	pseudo_instr2(2, 25, 24)
	neck_cut
	put_x_value(6, 1)
	put_y_value(3, 2)
	put_y_variable(6, 3)
	put_y_variable(0, 4)
	call_predicate('$parse_term', 5, 9)
	put_x_variable(1, 1)
	put_integer(2, 0)
	pseudo_instr3(0, 1, 28, 0)
	put_integer(1, 2)
	pseudo_instr3(1, 2, 1, 0)
	put_integer(2, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_y_value(7, 0)
	get_y_value(6, 2)
	put_y_value(0, 0)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	deallocate
	execute_predicate('$parse_after_term', 7)

$2:
	get_x_value(1, 4)
	get_x_value(0, 5)
	proceed
end('$parse_infix'/6):



'$check_postfixop'/4:


$1:
	get_x_variable(4, 1)
	allocate(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	put_integer(6, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_variable(0, 1)
	put_y_value(1, 1)
	put_y_variable(0, 2)
	put_x_value(4, 3)
	call_predicate('current_op', 4, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$postfix_prec', 3)
end('$check_postfixop'/4):



'$postfix_prec'/3:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'yf':$1, 'xf':$2])

$4:
	try(3, $1)
	trust($2)

$1:
	get_constant('yf', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_constant('xf', 0)
	pseudo_instr2(70, 1, 0)
	get_x_value(2, 0)
	proceed
end('$postfix_prec'/3):



'$parse_postfix'/6:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(6, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_ref(6)
	unify_x_variable(0)
	get_structure('postfix', 3, 6)
	unify_x_variable(7)
	unify_void(1)
	unify_x_variable(8)
	get_x_variable(9, 1)
	get_x_variable(10, 2)
	get_x_variable(11, 3)
	get_x_variable(12, 4)
	get_x_variable(6, 5)
	pseudo_instr2(2, 8, 10)
	neck_cut
	put_x_variable(1, 1)
	put_integer(1, 2)
	pseudo_instr3(0, 1, 7, 2)
	put_integer(1, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_x_value(2, 9)
	put_x_value(8, 2)
	put_x_value(10, 3)
	put_x_value(11, 4)
	put_x_value(12, 5)
	execute_predicate('$parse_after_term', 7)

$2:
	get_x_value(1, 4)
	get_x_value(0, 5)
	proceed
end('$parse_postfix'/6):



'$parse_substitution_or_list'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(9, 0)
	get_y_variable(8, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(8, 0)
	call_predicate('$check_sub', 1, 10)
	put_y_value(9, 0)
	put_y_value(4, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(1, 4)
	call_predicate('$parse_substitution', 5, 9)
	put_list(0)
	set_y_value(8)
	set_y_value(7)
	put_y_value(6, 1)
	put_y_value(0, 2)
	call_predicate('$build_substitute', 3, 6)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_integer(0, 2)
	deallocate
	execute_predicate('$parse_after_term', 7)

$2:
	get_x_variable(7, 3)
	get_x_variable(8, 4)
	get_x_variable(6, 5)
	put_x_value(2, 3)
	put_x_value(7, 4)
	put_x_value(8, 5)
	put_integer(0, 2)
	execute_predicate('$parse_after_term', 7)
end('$parse_substitution_or_list'/6):



'$parse_substitution'/5:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(5, $1)
	trust($2)

$1:
	get_list(0)
	unify_constant('[')
	unify_x_variable(0)
	allocate(6)
	get_y_variable(4, 1)
	get_list(2)
	unify_x_variable(1)
	unify_y_variable(3)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_level(5)
	put_y_value(4, 2)
	put_y_variable(0, 3)
	call_predicate('$parse_sublist', 4, 6)
	cut(5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$parse_substitution', 5)

$2:
	get_constant('[]', 2)
	get_x_variable(2, 1)
	put_integer(0, 1)
	execute_predicate('$parse_term', 5)
end('$parse_substitution'/5):



'$parse_sublist'/4:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(4, $1)
	trust($2)

$1:
	get_list(0)
	unify_constant(']')
	unify_void(1)
	neck_cut
	fail

$2:
	allocate(8)
	get_y_variable(3, 1)
	get_y_variable(7, 2)
	get_y_variable(1, 3)
	get_y_level(2)
	put_y_variable(4, 19)
	put_y_variable(0, 19)
	put_y_variable(5, 3)
	put_y_variable(6, 4)
	put_integer(999, 1)
	call_predicate('$parse_term', 5, 8)
	put_y_value(6, 0)
	put_y_value(4, 1)
	put_y_value(7, 2)
	put_y_value(0, 3)
	call_predicate('$parse_list_args', 4, 6)
	put_y_value(3, 0)
	get_list(0)
	unify_y_value(5)
	unify_y_value(4)
	put_y_value(3, 0)
	call_predicate('$check_sub', 1, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$parse_sublist'/4):



'$check_sub'/1:

	switch_on_term(0, $7, $1, $4, $1, $1, $5)

$4:
	try(1, $1)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$1, '[]':$6])

$6:
	try(1, $1)
	trust($2)

$7:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	get_constant('[]', 0)
	proceed

$3:
	get_list(0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr1(0, 1)
	put_x_variable(2, 2)
	put_integer(2, 3)
	pseudo_instr3(0, 1, 2, 3)
	put_constant('/', 4)
	pseudo_instr3(6, 2, 4, 3)
	put_constant('true', 2)
	get_x_value(3, 2)
	put_integer(2, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_x_variable(1, 2)
	pseudo_instr1(4, 1)
	execute_predicate('$check_sub', 1)
end('$check_sub'/1):



'$parse_bvars/4$0'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 0)
	put_x_variable(1, 2)
	get_structure('check_binder', 2, 2)
	unify_x_value(0)
	unify_constant('[]')
	pseudo_instr2(48, 0, 1)
	proceed

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('$check_bvar', 1, 3)
	cut(2)
	put_y_value(0, 0)
	get_list(0)
	unify_y_value(1)
	unify_constant('[]')
	deallocate
	proceed

$3:
	fail
end('$parse_bvars/4$0'/2):



'$parse_bvars'/4:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(4, $1)
	trust($2)

$1:
	get_list(0)
	unify_constant('[')
	allocate(6)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	put_integer(6, 1)
	pseudo_instr3(1, 1, 23, 0)
	get_y_level(0)
	put_y_variable(1, 1)
	put_x_variable(2, 2)
	put_constant(':', 3)
	call_predicate('current_op', 4, 6)
	put_y_value(5, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	call_predicate('$parse_bvars_list', 5, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(1, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	put_integer(6, 1)
	pseudo_instr3(1, 1, 24, 0)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	put_x_variable(2, 2)
	put_constant(':', 3)
	call_predicate('current_op', 4, 6)
	put_y_value(5, 0)
	put_y_value(2, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	put_y_value(3, 4)
	call_predicate('$parse_term', 5, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$parse_bvars/4$0', 2)
end('$parse_bvars'/4):



'$parse_bvars_list/5$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('[]', 1)
	pseudo_instr2(61, 0, 1)
	proceed

$2:
	put_integer(16, 0)
	execute_predicate('$log_message_and_fail', 2)
end('$parse_bvars_list/5$0'/2):



'$parse_bvars_list'/5:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(5, $1)
	trust($2)

$1:
	get_constant('[]', 2)
	get_list(0)
	unify_constant(']')
	unify_x_variable(0)
	get_x_value(0, 4)
	neck_cut
	proceed

$2:
	allocate(7)
	get_y_variable(1, 0)
	get_y_variable(0, 2)
	get_y_variable(6, 3)
	get_y_variable(5, 4)
	put_y_variable(2, 19)
	put_y_value(6, 2)
	put_y_variable(3, 3)
	put_y_variable(4, 4)
	call_predicate('$parse_term', 5, 7)
	put_y_value(4, 0)
	put_y_value(2, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	call_predicate('$parse_list_args', 4, 4)
	put_y_value(0, 0)
	get_list(0)
	unify_y_value(3)
	unify_y_value(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$parse_bvars_list/5$0', 2)
end('$parse_bvars_list'/5):



'$check_quantop'/3:


$1:
	get_x_variable(3, 1)
	get_x_variable(1, 2)
	put_integer(6, 4)
	pseudo_instr3(1, 4, 0, 2)
	get_x_variable(0, 2)
	put_constant('quant', 2)
	execute_predicate('current_op', 4)
end('$check_quantop'/3):



'$parse_quant'/6:


$1:
	allocate(8)
	get_y_variable(2, 0)
	get_y_variable(7, 1)
	get_x_variable(0, 2)
	get_y_variable(6, 3)
	get_y_variable(3, 4)
	get_y_variable(5, 5)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	put_y_value(6, 2)
	put_y_variable(4, 3)
	call_predicate('$parse_bvars', 4, 8)
	put_y_value(4, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(0, 3)
	put_y_value(5, 4)
	call_predicate('$parse_term', 5, 4)
	pseudo_instr4(7, 23, 22, 21, 20)
	deallocate
	proceed
end('$parse_quant'/6):



'$log_message_and_fail'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(0, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 2)
	put_constant('$read_error_code', 0)
	pseudo_instr2(74, 0, 21)
	put_constant('$read_error_left', 0)
	pseudo_instr2(74, 0, 20)
	fail
end('$log_message_and_fail'/2):



'$report_syntax_error/3$0'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	call_predicate('$strip_token', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$report_syntax_error/3$0', 2)
end('$report_syntax_error/3$0'/2):



'$report_syntax_error'/3:


$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	put_constant('$read_error_code', 1)
	pseudo_instr2(73, 1, 0)
	put_y_variable(6, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	call_predicate('$error_message', 2, 7)
	put_y_value(5, 0)
	put_y_value(6, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 7)
	put_constant('$read_error_left', 1)
	pseudo_instr2(73, 1, 0)
	pseudo_instr3(3, 26, 0, 1)
	get_y_value(1, 1)
	put_y_value(5, 0)
	put_y_value(0, 1)
	call_predicate('$report_syntax_error/3$0', 2, 5)
	put_structure(10, 0)
	set_constant('syntax_error')
	set_constant('unrecoverable')
	set_constant('read_term')
	set_y_value(2)
	set_void(3)
	set_y_value(4)
	set_y_value(3)
	set_y_value(0)
	set_y_value(1)
	deallocate
	execute_predicate('exception', 1)
end('$report_syntax_error'/3):



'$strip_token'/2:

	switch_on_term(0, $16, $7, $7, $8, $7, $7)

$8:
	switch_on_structure(0, 16, ['$default':$7, '$'/0:$9, 'atom'/1:$10, 'var'/2:$11, 'obvar'/2:$12, 'number'/1:$13, 'double'/1:$14, 'string'/1:$15])

$9:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$10:
	try(2, $1)
	trust($7)

$11:
	try(2, $2)
	trust($7)

$12:
	try(2, $3)
	trust($7)

$13:
	try(2, $4)
	trust($7)

$14:
	try(2, $5)
	trust($7)

$15:
	try(2, $6)
	trust($7)

$16:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_structure('atom', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_structure('var', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$3:
	get_structure('obvar', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$4:
	get_structure('number', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$5:
	get_structure('double', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$6:
	get_structure('string', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$7:
	get_x_value(0, 1)
	proceed
end('$strip_token'/2):



'$error_message'/2:

	switch_on_term(0, $18, 'fail', 'fail', 'fail', 'fail', $17)

$17:
	switch_on_constant(0, 32, ['$default':'fail', 1:$1, 2:$2, 3:$3, 4:$4, 5:$5, 6:$6, 7:$7, 8:$8, 9:$9, 10:$10, 11:$11, 12:$12, 13:$13, 14:$14, 15:$15, 16:$16])

$18:
	try(2, $1)
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
	retry($15)
	trust($16)

$1:
	get_integer(1, 0)
	get_constant('end_of_file appears inside quoted term', 1)
	proceed

$2:
	get_integer(2, 0)
	get_constant('unexpected character', 1)
	proceed

$3:
	get_integer(3, 0)
	get_constant('integer overflow', 1)
	proceed

$4:
	get_integer(4, 0)
	get_constant('numerical base is larger than 36', 1)
	proceed

$5:
	get_integer(5, 0)
	get_constant('token is too long (511 characters max.)', 1)
	proceed

$6:
	get_integer(6, 0)
	get_constant('end_of_file appears inside comment', 1)
	proceed

$7:
	get_integer(7, 0)
	get_constant('operator is expected after expression', 1)
	proceed

$8:
	get_integer(8, 0)
	get_constant('expression is expected', 1)
	proceed

$9:
	get_integer(9, 0)
	get_constant('this token cannot start an expression', 1)
	proceed

$10:
	get_integer(10, 0)
	get_constant('"," or ")" is expected in arguments', 1)
	proceed

$11:
	get_integer(11, 0)
	get_constant('",", "|" or ")" is expected in list', 1)
	proceed

$12:
	get_integer(12, 0)
	get_constant('operator is expected', 1)
	proceed

$13:
	get_integer(13, 0)
	get_constant('incompatible operator precedences', 1)
	proceed

$14:
	get_integer(14, 0)
	get_constant('too many arguments (255 max.)', 1)
	proceed

$15:
	get_integer(15, 0)
	get_constant('illegal use of ! or !! escape', 1)
	proceed

$16:
	get_integer(16, 0)
	get_constant('illegal bound variable list', 1)
	proceed
end('$error_message'/2):



