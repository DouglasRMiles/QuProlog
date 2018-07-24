'closed_list'/1:

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
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('closed_list', 1)
end('closed_list'/1):



'length'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 1)
	pseudo_instr1(1, 2)
	neck_cut
	put_integer(0, 1)
	execute_predicate('$length', 3)

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(3, 0)
	put_integer(0, 1)
	pseudo_instr2(2, 1, 0)
	put_x_value(2, 1)
	execute_predicate('$build_list', 2)
end('length'/2):



'$length'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	pseudo_instr2(69, 1, 3)
	get_x_variable(1, 3)
	execute_predicate('$length', 3)
end('$length'/3):



'$build_list'/2:

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
	put_constant('[]', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	pseudo_instr2(70, 0, 2)
	get_x_variable(0, 2)
	execute_predicate('$build_list', 2)
end('$build_list'/2):



'same_length'/2:

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
	unify_void(1)
	unify_x_variable(0)
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('same_length', 2)
end('same_length'/2):



'member'/2:

	try(2, $1)
	trust($2)

$1:
	get_list(1)
	unify_x_value(0)
	unify_void(1)
	proceed

$2:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('member', 2)
end('member'/2):



'member_eq'/2:

	try(2, $1)
	trust($2)

$1:
	get_list(1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr2(110, 0, 1)
	proceed

$2:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	neck_cut
	execute_predicate('member_eq', 2)
end('member_eq'/2):



'append'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('append', 3)
end('append'/3):



'delete'/3:

	try(3, $1)
	trust($2)

$1:
	get_list(1)
	unify_x_value(0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$2:
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('delete', 3)
end('delete'/3):



'delete_all'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	proceed

$2:
	get_list(1)
	unify_x_value(0)
	unify_x_variable(1)
	neck_cut
	execute_predicate('delete_all', 3)

$3:
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('delete_all', 3)
end('delete_all'/3):



'reverse'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('$reverse', 3)
end('reverse'/2):



'$reverse'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_x_variable(4, 2)
	put_list(2)
	set_x_value(3)
	set_x_value(4)
	execute_predicate('$reverse', 3)
end('$reverse'/3):



'distribute'/3:


$1:
	execute_predicate('distribute_left', 3)
end('distribute'/3):



'distribute_right'/3:

	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	neck_cut
	proceed

$2:
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_ref(4)
	unify_x_variable(2)
	get_structure(',', 2, 4)
	unify_x_value(3)
	unify_x_value(0)
	execute_predicate('distribute_right', 3)
end('distribute_right'/3):



'distribute_left'/3:

	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	neck_cut
	proceed

$2:
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_ref(4)
	unify_x_variable(2)
	get_structure(',', 2, 4)
	unify_x_value(0)
	unify_x_value(3)
	execute_predicate('distribute_left', 3)
end('distribute_left'/3):



'remove_duplicates'/2:

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
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(1, 1)
	call_predicate('member_eq', 2, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('remove_duplicates', 2)

$3:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('remove_duplicates', 2)
end('remove_duplicates'/2):



'union_list'/3:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(3, $2)
	trust($3)

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('member_eq', 2, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('union_list', 3)

$3:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('union_list', 3)
end('union_list'/3):



'intersect_list'/3:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(3, $2)
	trust($3)

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('[]', 2)
	proceed

$2:
	get_list(0)
	allocate(5)
	unify_y_variable(3)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_variable(2, 2)
	get_y_level(4)
	put_y_value(3, 0)
	call_predicate('member_eq', 2, 5)
	cut(4)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(3)
	unify_x_variable(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('intersect_list', 3)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('intersect_list', 3)
end('intersect_list'/3):



'diff_list'/3:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(3, $2)
	trust($3)

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('[]', 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('member_eq', 2, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('diff_list', 3)

$3:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('diff_list', 3)
end('diff_list'/3):



