'collect_variables'/2:


$1:
	get_x_variable(3, 1)
	put_x_value(0, 1)
	put_constant('$collect_var', 0)
	put_constant('[]', 2)
	execute_predicate('collect_simple_terms', 4)
end('collect_variables'/2):



'$collect_var'/3:


$1:
	get_list(2)
	unify_x_value(0)
	unify_x_value(1)
	pseudo_instr1(44, 0)
	proceed
end('$collect_var'/3):



'freeze_vars'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$freeze_vars', 0)
	put_constant('[]', 2)
	put_constant('[]', 3)
	execute_predicate('collect_simple_terms', 4)
end('freeze_vars'/1):



'$freeze_vars'/3:


$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	pseudo_instr1(44, 0)
	pseudo_instr1(39, 0)
	proceed
end('$freeze_vars'/3):



'freeze_list'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr1(39, 1)
	execute_predicate('freeze_list', 1)
end('freeze_list'/1):



'thaw_vars'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$thaw_vars', 0)
	put_constant('[]', 2)
	put_constant('[]', 3)
	execute_predicate('collect_simple_terms', 4)
end('thaw_vars'/1):



'$thaw_vars'/3:


$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	pseudo_instr1(44, 0)
	pseudo_instr1(40, 0)
	proceed
end('$thaw_vars'/3):



'thaw_vars'/2:


$1:
	get_x_variable(2, 1)
	put_x_value(0, 1)
	put_x_variable(3, 3)
	put_constant('$thaw_vars2', 0)
	execute_predicate('collect_simple_terms', 4)
end('thaw_vars'/2):



'$thaw_vars2/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member_eq', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$thaw_vars2/3$0'/2):



'$thaw_vars2'/3:


$1:
	allocate(1)
	get_y_variable(0, 0)
	get_x_value(1, 2)
	pseudo_instr1(44, 20)
	call_predicate('$thaw_vars2/3$0', 2, 1)
	pseudo_instr1(40, 20)
	deallocate
	proceed
end('$thaw_vars2'/3):



'thaw_list'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr1(40, 1)
	execute_predicate('thaw_list', 1)
end('thaw_list'/1):



