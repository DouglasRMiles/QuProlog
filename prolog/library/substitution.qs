'substitution'/2:


$1:
	allocate(2)
	get_y_variable(0, 1)
	put_y_variable(1, 1)
	call_predicate('$simplify_if_local', 2, 2)
	pseudo_instr2(24, 21, 0)
	put_y_value(0, 2)
	put_constant('[]', 1)
	deallocate
	execute_predicate('$convert_substitutions', 3)
end('substitution'/2):



'$convert_substitutions'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(18, 3)
	get_x_value(0, 3)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(0, 3)
	put_integer(1, 1)
	put_constant('[]', 2)
	call_predicate('$convert_sub', 4, 4)
	pseudo_instr2(26, 23, 0)
	put_list(1)
	set_y_value(0)
	set_y_value(2)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$convert_substitutions', 3)
end('$convert_substitutions'/3):



'$convert_sub'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 2)
	pseudo_instr3(17, 1, 0, 2)
	neck_cut
	pseudo_instr3(18, 1, 0, 5)
	pseudo_instr2(69, 1, 6)
	get_x_variable(1, 6)
	put_structure(2, 6)
	set_constant('/')
	set_x_value(5)
	set_x_value(2)
	put_list(2)
	set_x_value(6)
	set_x_value(4)
	execute_predicate('$convert_sub', 4)

$2:
	get_x_value(2, 3)
	proceed
end('$convert_sub'/4):



'substitute'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(1, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_level(4)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	call_predicate('closed_list', 1, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	call_predicate('$build_substitute', 3, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(2)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$break_substitute', 3, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('substitute'/3):



'$build_substitute'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(18, 1)
	get_y_level(3)
	put_y_variable(2, 2)
	call_predicate('$build_substitutions', 3, 4)
	cut(3)
	pseudo_instr3(19, 22, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('substitute')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('term')
	put_structure(1, 2)
	set_constant('list')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('list')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('-')
	set_x_value(3)
	put_structure(1, 3)
	set_constant('?')
	set_constant('term')
	put_structure(3, 4)
	set_constant('substitute')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('compound')
	put_structure(1, 4)
	set_constant('list')
	set_x_value(3)
	put_structure(1, 3)
	set_constant('@')
	set_x_value(4)
	put_structure(1, 4)
	set_constant('?')
	set_constant('term')
	put_structure(3, 5)
	set_constant('substitute')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('type_exception', 3)
end('$build_substitute'/3):



'$break_substitute'/3:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 2)
	call_predicate('substitution', 2, 2)
	pseudo_instr2(25, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$break_substitute'/3):



'$build_substitutions'/3:

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
	allocate(5)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(3, 1)
	get_y_variable(0, 2)
	put_y_variable(4, 19)
	put_y_value(2, 0)
	call_predicate('closed_list', 1, 5)
	put_y_value(2, 0)
	put_y_value(4, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 5)
	put_integer(256, 0)
	pseudo_instr2(1, 24, 0)
	pseudo_instr4(14, 24, 23, 22, 0)
	get_x_variable(1, 0)
	put_y_value(1, 0)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$build_substitutions', 3)
end('$build_substitutions'/3):



'$build_sub/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	fail

$2:
	proceed
end('$build_sub/3$0'/1):



'$build_sub'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(1)
	get_structure('/', 2, 0)
	unify_y_variable(3)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	pseudo_instr1(4, 24)
	put_y_value(4, 0)
	call_predicate('$build_sub/3$0', 1, 5)
	pseudo_instr3(15, 22, 20, 24)
	pseudo_instr3(16, 22, 20, 23)
	pseudo_instr2(70, 22, 0)
	get_x_variable(1, 0)
	put_y_value(1, 0)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$build_sub', 3)
end('$build_sub'/3):



'parallel_sub'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('[]', 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(1)
	unify_x_variable(4)
	unify_x_variable(1)
	get_list(2)
	unify_x_ref(5)
	unify_x_variable(2)
	get_structure('/', 2, 5)
	unify_x_value(3)
	unify_x_value(4)
	execute_predicate('parallel_sub', 3)
end('parallel_sub'/3):



