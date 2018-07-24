'open_list'/1:

	switch_on_term(0, $3, $1, $3, $1, $1, $1)

$3:
	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('open_list', 1)
end('open_list'/1):



'open_tail'/2:

	switch_on_term(0, $3, $1, $3, $1, $1, $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('open_tail', 2)
end('open_tail'/2):



'open_length'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(3, 0)
	neck_cut
	put_integer(0, 1)
	pseudo_instr2(2, 1, 0)
	put_x_value(2, 1)
	execute_predicate('$build_open_list', 2)

$2:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$open_length', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('open_length'/2):



'$open_length'/2:

	switch_on_term(0, $3, $1, $3, $1, $1, $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_integer(0, 1)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	allocate(2)
	get_y_variable(0, 1)
	put_y_variable(1, 1)
	call_predicate('$open_length', 2, 2)
	pseudo_instr2(69, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$open_length'/2):



'$build_open_list'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	pseudo_instr2(70, 0, 2)
	get_x_variable(0, 2)
	execute_predicate('$build_open_list', 2)
end('$build_open_list'/2):



'open_member'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	fail

$2:
	get_list(1)
	unify_x_value(0)
	unify_void(1)
	proceed

$3:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('open_member', 2)
end('open_member'/2):



'open_member_eq'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	fail

$2:
	get_list(1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr2(110, 0, 1)
	proceed

$3:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('open_member_eq', 2)
end('open_member_eq'/2):



'open_append'/2:


$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('open_tail', 2, 3)
	cut(2)
	put_y_value(1, 0)
	put_x_variable(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('append', 3)
end('open_append'/2):



'search_insert'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	get_list(1)
	unify_x_value(0)
	unify_void(1)
	proceed

$2:
	get_list(1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	proceed

$3:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('search_insert', 2)
end('search_insert'/2):



'open_to_closed'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('open_to_closed', 1)
end('open_to_closed'/1):



'closed_to_open'/2:


$1:
	get_x_variable(2, 1)
	put_x_variable(1, 1)
	execute_predicate('append', 3)
end('closed_to_open'/2):



