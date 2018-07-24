'consult/1$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$consult', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('consult/1$0/1$0'/1):



'consult/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('consult/1$0/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('consult/1$0'/1):



'consult/1$1/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$consult', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('consult/1$1/1$0'/1):



'consult/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('consult/1$1/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('consult/1$1'/1):



'consult'/1:

	switch_on_term(0, $9, $8, $8, $5, $8, $8)

$5:
	switch_on_structure(0, 4, ['$default':$8, '$'/0:$6, '-'/1:$7])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$8:
	try(1, $1)
	retry($2)
	trust($4)

$9:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('consult')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('consult')
	set_x_value(2)
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('consult')
	set_x_value(1)
	put_list(1)
	set_x_value(3)
	set_x_value(2)
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('consult')
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(50, 0)
	neck_cut
	execute_predicate('$consult_files', 1)

$3:
	get_structure('-', 1, 0)
	unify_x_variable(0)
	execute_predicate('consult/1$0', 1)

$4:
	execute_predicate('consult/1$1', 1)
end('consult'/1):



'reconsult'/1:


$1:
	execute_predicate('consult', 1)
end('reconsult'/1):



'$consult_files/1$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$consult', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$consult_files/1$0/1$0'/1):



'$consult_files/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$consult_files/1$0/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$consult_files/1$0'/1):



'$consult_files/1$1/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$consult', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$consult_files/1$1/1$0'/1):



'$consult_files/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$consult_files/1$1/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$consult_files/1$1'/1):



'$consult_files'/1:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(1, $2)
	trust($3)

$5:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(1)
	unify_y_variable(0)
	get_structure('-', 1, 0)
	unify_x_variable(0)
	neck_cut
	call_predicate('$consult_files/1$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$consult_files', 1)

$3:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	call_predicate('$consult_files/1$1', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$consult_files', 1)
end('$consult_files'/1):



'$consult/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('$consult/1$0'/1):



'$consult/1$1'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(0, 1)
	get_y_level(1)
	put_y_variable(2, 1)
	put_constant('.qle', 0)
	call_predicate('name', 2, 4)
	put_x_variable(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('encoded', 0)
	deallocate
	execute_predicate('$consult_a_file', 2)

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(0, 1)
	get_y_level(1)
	put_y_variable(2, 1)
	put_constant('.qge', 0)
	call_predicate('name', 2, 4)
	put_x_variable(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('encoded_expanded', 0)
	deallocate
	execute_predicate('$consult_a_file', 2)

$3:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(0, 1)
	get_y_level(1)
	put_y_variable(2, 1)
	put_constant('.qg', 0)
	call_predicate('name', 2, 4)
	put_x_variable(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('normal_expanded', 0)
	deallocate
	execute_predicate('$consult_a_file', 2)

$4:
	put_constant('normal', 0)
	execute_predicate('$consult_a_file', 2)
end('$consult/1$1'/2):



'$consult'/1:

	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('consult')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('consult')
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
	call_predicate('$consult/1$0', 1, 2)
	cut(1)
	put_structure(1, 0)
	set_constant('consult')
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('consult')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$3:
	put_x_variable(2, 3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.ql')
	unify_constant('[]')
	pseudo_instr2(31, 2, 1)
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	put_y_value(0, 0)
	call_predicate('$accessible', 1, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('normal', 0)
	deallocate
	execute_predicate('$consult_a_file', 2)

$4:
	put_x_variable(2, 3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.pl')
	unify_constant('[]')
	pseudo_instr2(31, 2, 1)
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	put_y_value(0, 0)
	call_predicate('$accessible', 1, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('normal', 0)
	deallocate
	execute_predicate('$consult_a_file', 2)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_level(2)
	put_y_variable(0, 19)
	call_predicate('$accessible', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('name', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$consult/1$1', 2)

$6:
	put_structure(1, 1)
	set_constant('consult')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('$consult'/1):



'$accessible'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'user':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_constant('user', 0)
	neck_cut
	proceed

$2:
	put_x_variable(2, 3)
	get_structure('\\/', 2, 3)
	unify_integer(4)
	unify_integer(0)
	pseudo_instr2(0, 1, 2)
	pseudo_instr3(34, 0, 1, 2)
	put_integer(0, 0)
	get_x_value(2, 0)
	proceed
end('$accessible'/1):



'$consult_a_file'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('$consult_open', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_constant('[]', 2)
	call_predicate('$read_assert_clauses', 3, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$consult_close', 1)
end('$consult_a_file'/2):



'$consult_open'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'user':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_constant('user', 0)
	get_integer(0, 1)
	neck_cut
	proceed

$2:
	get_x_variable(2, 1)
	put_constant('read', 1)
	execute_predicate('open', 3)
end('$consult_open'/2):



'$consult_close'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	execute_predicate('close', 1)
end('$consult_close'/1):



'$read_assert_clauses/3$0'/4:

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
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	call_predicate('encoded_read_term', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_constant('end_of_file', 0)
	get_x_value(1, 0)
	proceed
end('$read_assert_clauses/3$0'/4):



'$read_assert_clauses/3$1'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 2)
	allocate(3)
	get_y_variable(1, 3)
	get_y_level(2)
	put_y_variable(0, 2)
	put_x_value(4, 3)
	call_predicate('$consult_clauses', 4, 3)
	cut(2)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('encoded', 0)
	deallocate
	execute_predicate('$read_assert_clauses', 3)

$2:
	proceed
end('$read_assert_clauses/3$1'/4):



'$read_assert_clauses/3$2'/3:

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
end('$read_assert_clauses/3$2'/3):



'$read_assert_clauses/3$3'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 2)
	allocate(3)
	get_y_variable(1, 3)
	get_y_level(2)
	put_y_variable(0, 2)
	put_x_value(4, 3)
	call_predicate('$consult_clauses', 4, 3)
	cut(2)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('encoded_expanded', 0)
	deallocate
	execute_predicate('$read_assert_clauses', 3)

$2:
	proceed
end('$read_assert_clauses/3$3'/4):



'$read_assert_clauses/3$4'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 2)
	allocate(3)
	get_y_variable(1, 3)
	get_y_level(2)
	put_y_variable(0, 2)
	put_x_value(4, 3)
	call_predicate('$consult_clauses', 4, 3)
	cut(2)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('normal_expanded', 0)
	deallocate
	execute_predicate('$read_assert_clauses', 3)

$2:
	proceed
end('$read_assert_clauses/3$4'/4):



'$read_assert_clauses/3$5'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 2)
	allocate(3)
	get_y_variable(1, 3)
	get_y_level(2)
	put_y_variable(0, 2)
	put_x_value(4, 3)
	call_predicate('$consult_clauses', 4, 3)
	cut(2)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('normal', 0)
	deallocate
	execute_predicate('$read_assert_clauses', 3)

$2:
	proceed
end('$read_assert_clauses/3$5'/4):



'$read_assert_clauses'/3:

	switch_on_term(0, $6, 'fail', 'fail', 'fail', 'fail', $5)

$5:
	switch_on_constant(0, 8, ['$default':'fail', 'encoded':$1, 'encoded_expanded':$2, 'normal_expanded':$3, 'normal':$4])

$6:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('encoded', 0)
	allocate(6)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_variable(5, 1)
	put_y_variable(4, 2)
	put_y_variable(1, 3)
	call_predicate('$read_assert_clauses/3$0', 4, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	put_y_value(4, 2)
	call_predicate('expand_term', 3, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$read_assert_clauses/3$1', 4)

$2:
	get_constant('encoded_expanded', 0)
	allocate(4)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_value(3, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$read_assert_clauses/3$2', 3, 4)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$read_assert_clauses/3$3', 4)

$3:
	get_constant('normal_expanded', 0)
	allocate(4)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_value(3, 0)
	put_y_variable(1, 1)
	put_structure(1, 2)
	set_constant('singletons')
	set_y_variable(0)
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('variable_names')
	set_void(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	call_predicate('read_term', 3, 4)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$read_assert_clauses/3$4', 4)

$4:
	get_constant('normal', 0)
	allocate(6)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_variable(5, 1)
	put_structure(1, 2)
	set_constant('singletons')
	set_y_variable(1)
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('variable_names')
	set_y_variable(4)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	call_predicate('read_term', 3, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	put_y_value(4, 2)
	call_predicate('expand_term', 3, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$read_assert_clauses/3$5', 4)
end('$read_assert_clauses'/3):



'$check_singletons'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(3, 1)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	call_predicate('$extract_singletons', 2, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	call_predicate('$extract_pn', 3, 3)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_list(1)
	set_y_value(2)
	set_x_value(0)
	put_list(0)
	set_constant(' Singleton Variables: ')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('/')
	set_y_value(1)
	set_y_value(0)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('Warning: ')
	set_x_value(2)
	put_constant('stderr', 0)
	deallocate
	execute_predicate('write_term_list', 2)
end('$check_singletons'/2):



'$extract_pn'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ':-'/2:$5])

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
	get_structure(':-', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	neck_cut
	pseudo_instr3(0, 0, 1, 2)
	proceed

$2:
	neck_cut
	pseudo_instr3(0, 0, 1, 2)
	proceed
end('$extract_pn'/3):



'$extract_singletons'/2:

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
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('=', 2, 2)
	unify_void(1)
	unify_x_variable(2)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$extract_singletons', 2)
end('$extract_singletons'/2):



'$consult_clauses'/4:

	switch_on_term(0, $7, $3, $4, $3, $3, $5)

$4:
	try(4, $2)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$3, '[]':$6])

$6:
	try(4, $1)
	trust($3)

$7:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 2)
	call_predicate('$consult_clause', 4, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$consult_clauses', 4)

$3:
	execute_predicate('$consult_clause', 4)
end('$consult_clauses'/4):



'$consult_clause/4$0'/1:

	try(1, $1)
	trust($2)

$1:
	execute_predicate('call', 1)

$2:
	proceed
end('$consult_clause/4$0'/1):



'$consult_clause/4$1'/3:

	switch_on_term(0, $6, $1, $1, $3, $1, $1)

$3:
	switch_on_structure(0, 4, ['$default':$1, '$'/0:$4, '/'/2:$5])

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
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	call_predicate('member', 2, 3)
	cut(2)
	put_y_value(0, 0)
	get_y_value(1, 0)
	deallocate
	proceed

$2:
	get_list(2)
	unify_x_value(0)
	unify_x_value(1)
	get_structure('/', 2, 0)
	unify_x_variable(1)
	unify_x_variable(2)
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 1, 2)
	execute_predicate('retractall', 1)
end('$consult_clause/4$1'/3):



'$consult_clause'/4:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, 'end_of_file':$5])

$5:
	try(4, $1)
	retry($2)
	trust($3)

$6:
	try(4, $2)
	trust($3)

$7:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_constant('end_of_file', 0)
	neck_cut
	fail

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_x_value(1, 2)
	get_y_level(0)
	call_predicate('$is_query', 1, 2)
	cut(0)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 21, 0)
	call_predicate('$consult_clause/4$0', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	allocate(4)
	get_y_variable(0, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_x_variable(0, 3)
	put_y_variable(1, 19)
	put_y_value(0, 1)
	call_predicate('$check_singletons', 2, 4)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('get_name', 2, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	call_predicate('$consult_clause/4$1', 3, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('assertz', 1)
end('$consult_clause'/4):



'get_name/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_goal', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	fail
end('get_name/2$0'/2):



'get_name/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_goal', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	fail
end('get_name/2$1'/2):



'get_name'/2:

	switch_on_term(0, $9, $8, $8, $5, $8, $8)

$5:
	switch_on_structure(0, 4, ['$default':$8, '$'/0:$6, ':-'/2:$7])

$6:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$8:
	try(2, $1)
	retry($3)
	trust($4)

$9:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('get_name')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('-')
	set_constant('gcomp')
	put_structure(2, 3)
	set_constant('get_name')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure(':-', 2, 0)
	allocate(3)
	unify_y_variable(1)
	unify_void(1)
	get_y_variable(0, 1)
	get_y_level(2)
	pseudo_instr1(46, 21)
	get_y_level(2)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('get_name/2$0', 2, 3)
	put_y_value(1, 0)
	call_predicate('$legal_clause_head', 1, 3)
	cut(2)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 21, 0, 1)
	put_y_value(0, 2)
	get_structure('/', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	deallocate
	proceed

$3:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(2, 1)
	call_predicate('get_name/2$1', 2, 3)
	put_y_value(1, 0)
	call_predicate('$legal_clause_head', 1, 3)
	cut(2)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 21, 0, 1)
	put_y_value(0, 2)
	get_structure('/', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	deallocate
	proceed

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('get_name')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('-')
	set_constant('gcomp')
	put_structure(2, 3)
	set_constant('get_name')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('get_name'/2):



'$is_query'/1:

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
	unify_void(1)
	proceed

$2:
	get_structure(':-', 1, 0)
	unify_void(1)
	proceed
end('$is_query'/1):



