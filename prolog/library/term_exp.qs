'$init_term_exp'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('term_expansion')
	set_integer(2)
	allocate(0)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('term_expansion')
	set_integer(3)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$multi_expansion')
	set_integer(2)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$multi_expansion')
	set_integer(3)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$subterm_expansion')
	set_integer(3)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$subterm_expansion')
	set_integer(4)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$subterm_expansion_context')
	set_integer(1)
	call_predicate('dynamic', 1, 0)
	put_constant('$multi_expand_depth_limit', 0)
	put_integer(100, 1)
	pseudo_instr2(74, 0, 1)
	put_constant('$subterm_expand_depth_limit', 0)
	put_integer(100, 1)
	pseudo_instr2(74, 0, 1)
	deallocate
	proceed
end('$init_term_exp'/0):



'expand_term'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(44, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('term_expansion', 2, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$rest_expansion', 2)

$3:
	execute_predicate('$rest_expansion', 2)
end('expand_term'/2):



'expand_term'/3:

	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(44, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('term_expansion', 3, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$rest_expansion', 2)

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('term_expansion', 2, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$rest_expansion', 2)

$4:
	execute_predicate('$rest_expansion', 2)
end('expand_term'/3):



'$rest_expansion'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('dcg', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_value(0, 1)
	proceed
end('$rest_expansion'/2):



'add_expansion'/1:


$1:
	get_x_variable(1, 0)
	put_constant('term_expansion', 0)
	put_integer(2, 2)
	execute_predicate('add_linking_clause', 3)
end('add_expansion'/1):



'del_expansion'/1:


$1:
	get_x_variable(1, 0)
	put_constant('term_expansion', 0)
	put_integer(2, 2)
	execute_predicate('del_linking_clause', 3)
end('del_expansion'/1):



'add_expansion_vars'/1:


$1:
	get_x_variable(1, 0)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	execute_predicate('add_linking_clause', 3)
end('add_expansion_vars'/1):



'del_expansion_vars'/1:


$1:
	get_x_variable(1, 0)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	execute_predicate('del_linking_clause', 3)
end('del_expansion_vars'/1):



'add_linking_clause/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('clause', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant(':-')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('assert', 1)
end('add_linking_clause/3$0'/2):



'add_linking_clause/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_clause_head', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('add_linking_clause/3$1'/1):



'add_linking_clause/3$2'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_clause_head', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('add_linking_clause/3$2'/1):



'add_linking_clause'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	allocate(6)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_level(5)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	call_predicate('$legal_clause_head', 1, 6)
	put_y_value(3, 0)
	call_predicate('$legal_clause_head', 1, 6)
	pseudo_instr1(3, 22)
	put_integer(0, 0)
	pseudo_instr2(2, 0, 22)
	cut(5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	call_predicate('$make_linking_clause', 5, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('add_linking_clause/3$0', 2)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('add_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('add_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('add_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('add_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('add_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('add_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('add_linking_clause/3$1', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('add_linking_clause')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('add_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)

$6:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(1, 0)
	call_predicate('add_linking_clause/3$2', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('add_linking_clause')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('add_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	deallocate
	execute_predicate('type_exception', 3)

$7:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('add_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('add_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('add_linking_clause'/3):



'del_linking_clause/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_clause_head', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('del_linking_clause/3$0'/1):



'del_linking_clause'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(4, 2)
	get_y_level(6)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	call_predicate('$legal_clause_head', 1, 7)
	pseudo_instr1(3, 24)
	put_integer(0, 0)
	pseudo_instr2(2, 0, 24)
	cut(6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(1, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$make_linking_head', 5, 5)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('clause', 2, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	call_predicate('$extract_body', 3, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_structure(2, 0)
	set_constant(':-')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('retract', 1)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('del_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('del_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('del_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('del_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('del_linking_clause/3$0', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('del_linking_clause')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('del_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('del_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('del_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('del_linking_clause'/3):



'get_linking_clause/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_clause_head', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('get_linking_clause/3$0'/1):



'get_linking_clause'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(1, 1)
	get_y_variable(3, 2)
	get_y_level(6)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	call_predicate('$legal_clause_head', 1, 7)
	pseudo_instr1(3, 23)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 23)
	cut(6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$make_linking_head', 5, 5)
	put_y_value(4, 0)
	put_y_value(2, 1)
	call_predicate('clause', 2, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('$extract_body', 3, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('get_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('get_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('get_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('get_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('get_linking_clause/3$0', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('get_linking_clause')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('get_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('get_linking_clause')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('get_linking_clause')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('get_linking_clause'/3):



'$make_linking_clause'/5:


$1:
	allocate(7)
	get_y_variable(5, 1)
	get_y_variable(6, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	put_y_variable(0, 19)
	put_y_value(6, 1)
	put_y_value(4, 2)
	put_y_variable(2, 3)
	put_y_variable(1, 4)
	call_predicate('$make_linking_head', 5, 7)
	put_x_variable(0, 0)
	put_x_variable(3, 3)
	pseudo_instr3(0, 25, 0, 3)
	put_integer(1, 2)
	pseudo_instr3(2, 2, 3, 1)
	get_y_value(0, 1)
	pseudo_instr3(2, 26, 3, 1)
	pseudo_instr3(0, 23, 0, 1)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_integer(1, 2)
	call_predicate('$same_args', 4, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$same_args', 5)
end('$make_linking_clause'/5):



'$make_linking_head'/5:


$1:
	get_x_variable(5, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	put_x_variable(6, 6)
	put_x_variable(3, 3)
	pseudo_instr3(0, 0, 6, 3)
	pseudo_instr3(2, 3, 5, 7)
	get_x_value(4, 7)
	put_integer(1, 7)
	pseudo_instr3(2, 7, 3, 5)
	get_x_value(2, 5)
	pseudo_instr3(0, 1, 6, 4)
	put_integer(1, 2)
	execute_predicate('$same_args', 4)
end('$make_linking_head'/5):



'$extract_body'/3:


$1:
	get_x_variable(3, 1)
	get_x_variable(1, 2)
	put_x_variable(2, 2)
	put_x_variable(4, 4)
	pseudo_instr3(0, 0, 2, 4)
	pseudo_instr3(3, 4, 3, 5)
	get_x_variable(3, 5)
	pseudo_instr3(0, 1, 2, 3)
	put_integer(1, 2)
	execute_predicate('$same_args', 4)
end('$extract_body'/3):



'multi_expand_term'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('multi_expand_term', 3)
end('multi_expand_term'/2):



'multi_expand_term'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(44, 0)
	neck_cut
	get_x_value(0, 1)
	proceed

$2:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$multi_expand_term', 3, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_list(1)
	unify_x_value(0)
	unify_constant('[]')
	proceed
end('multi_expand_term'/3):



'$multi_expand_term'/3:


$1:
	get_x_variable(4, 0)
	get_x_variable(5, 1)
	get_x_variable(3, 2)
	put_constant('$multi_expand_depth_limit', 1)
	pseudo_instr2(73, 1, 0)
	allocate(2)
	get_y_level(1)
	put_x_value(4, 1)
	put_x_value(5, 2)
	put_y_variable(0, 4)
	call_predicate('$multi_expand_term', 5, 2)
	cut(1)
	pseudo_instr1(46, 20)
	deallocate
	proceed
end('$multi_expand_term'/3):



'$multi_expand_term'/5:

	switch_on_term(0, $8, $7, $7, $7, $7, $5)

$5:
	switch_on_constant(0, 4, ['$default':$7, 0:$6])

$6:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(5, $2)
	retry($3)
	trust($4)

$8:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_integer(0, 0)
	get_list(2)
	unify_x_value(1)
	unify_constant('[]')
	neck_cut
	put_structure(3, 2)
	set_constant('multi_expand_term')
	set_x_value(1)
	set_void(1)
	set_x_value(3)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_list(3)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('Warning: depth bound exceeded while multi_expanding ')
	set_x_value(3)
	put_structure(5, 0)
	set_constant('range_error')
	set_constant('warning')
	set_x_value(2)
	set_x_value(1)
	set_void(2)
	execute_predicate('exception', 1)

$2:
	allocate(6)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	pseudo_instr1(46, 0)
	get_y_level(5)
	put_y_variable(0, 1)
	put_y_value(2, 2)
	call_predicate('$multi_expansion', 3, 6)
	cut(5)
	put_y_value(1, 0)
	get_constant('true', 0)
	pseudo_instr2(70, 24, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$multi_expand_terms', 5)

$3:
	allocate(6)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	pseudo_instr1(46, 0)
	get_y_level(5)
	put_y_variable(0, 1)
	call_predicate('$multi_expansion', 2, 6)
	cut(5)
	put_y_value(1, 0)
	get_constant('true', 0)
	pseudo_instr2(70, 24, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$multi_expand_terms', 5)

$4:
	get_list(2)
	unify_x_value(1)
	unify_constant('[]')
	proceed
end('$multi_expand_term'/5):



'$multi_expand_terms'/5:

	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_value(1, 2)
	pseudo_instr1(1, 1)
	neck_cut
	proceed

$2:
	get_constant('[]', 1)
	get_constant('[]', 2)
	neck_cut
	proceed

$3:
	allocate(7)
	get_y_variable(6, 0)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(5)
	get_y_variable(2, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(1, 2)
	call_predicate('$multi_expand_term', 5, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(0, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	call_predicate('$multi_expand_terms', 5, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)

$4:
	execute_predicate('$multi_expand_term', 5)
end('$multi_expand_terms'/5):



'multi_expand_depth_limit/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('multi_expand_depth_limit/1$0'/1):



'multi_expand_depth_limit'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	put_integer(0, 1)
	pseudo_instr2(1, 1, 0)
	neck_cut
	put_constant('$multi_expand_depth_limit', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$2:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('$multi_expand_depth_limit', 2)
	pseudo_instr2(73, 2, 1)
	get_x_value(0, 1)
	proceed

$3:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('multi_expand_depth_limit/1$0', 1, 1)
	put_structure(1, 0)
	set_constant('multi_expand_depth_limit')
	set_y_value(0)
	put_structure(1, 1)
	set_constant('?')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('multi_expand_depth_limit')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('multi_expand_depth_limit')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('positive_integer', 2)
	execute_predicate('range_exception', 3)
end('multi_expand_depth_limit'/1):



'expand_subterms'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('expand_subterms', 3)
end('expand_subterms'/2):



'expand_subterms'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(44, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$expand_subterms', 3, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_value(0, 1)
	proceed
end('expand_subterms'/3):



'$expand_subterms'/3:


$1:
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	put_constant('$subterm_expand_depth_limit', 1)
	pseudo_instr2(73, 1, 0)
	get_y_variable(3, 0)
	get_y_level(1)
	put_y_variable(0, 19)
	put_y_variable(2, 0)
	call_predicate('$subterm_expansion_context', 1, 7)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(4, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	call_predicate('$expand_subterms', 6, 2)
	cut(1)
	pseudo_instr1(46, 20)
	deallocate
	proceed
end('$expand_subterms'/3):



'$expand_subterms/6$0'/7:

	try(7, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	get_x_variable(7, 1)
	get_x_variable(8, 2)
	get_x_variable(2, 3)
	get_x_variable(1, 5)
	get_x_variable(3, 6)
	put_constant('true', 0)
	get_x_value(2, 0)
	pseudo_instr2(70, 4, 0)
	put_x_value(8, 4)
	put_x_value(7, 5)
	execute_predicate('$expand_subterms', 6)
end('$expand_subterms/6$0'/7):



'$expand_subterms/6$1'/7:

	try(7, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	get_x_variable(7, 1)
	get_x_variable(8, 2)
	get_x_variable(2, 3)
	get_x_variable(1, 5)
	get_x_variable(3, 6)
	put_constant('true', 0)
	get_x_value(2, 0)
	pseudo_instr2(70, 4, 0)
	put_x_value(8, 4)
	put_x_value(7, 5)
	execute_predicate('$expand_subterms', 6)
end('$expand_subterms/6$1'/7):



'$expand_subterms/6$2'/7:

	try(7, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	get_x_variable(7, 1)
	get_x_variable(8, 2)
	get_x_variable(2, 3)
	get_x_variable(1, 5)
	get_x_variable(3, 6)
	put_constant('true', 0)
	get_x_value(2, 0)
	pseudo_instr2(70, 4, 0)
	put_x_value(8, 4)
	put_x_value(7, 5)
	execute_predicate('$expand_subterms', 6)
end('$expand_subterms/6$2'/7):



'$expand_subterms'/6:

	switch_on_term(0, $14, $13, $13, $13, $13, $11)

$11:
	switch_on_constant(0, 4, ['$default':$13, 0:$12])

$12:
	try(6, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$13:
	try(6, $2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$14:
	try(6, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$1:
	get_integer(0, 0)
	get_x_value(4, 5)
	put_constant('$subterm_expand_depth_limit', 1)
	pseudo_instr2(73, 1, 0)
	put_structure(3, 1)
	set_constant('expand_subterms')
	set_x_value(4)
	set_void(1)
	set_x_value(3)
	put_list(2)
	set_constant('nl')
	set_constant('[]')
	put_list(3)
	set_x_value(4)
	set_x_value(2)
	put_list(2)
	set_constant(') exceeded while subterm_expanding ')
	set_x_value(3)
	put_list(3)
	set_x_value(0)
	set_x_value(2)
	put_list(2)
	set_constant('Warning: depth bound (')
	set_x_value(3)
	put_structure(5, 0)
	set_constant('range_error')
	set_constant('warning')
	set_x_value(1)
	set_x_value(2)
	set_void(2)
	execute_predicate('exception', 1)

$2:
	allocate(11)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_x_variable(0, 4)
	get_y_variable(2, 5)
	pseudo_instr1(6, 0)
	neck_cut
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(10, 1)
	put_y_variable(9, 2)
	call_predicate('$break_substitute', 3, 11)
	put_y_value(10, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(1, 3)
	put_y_value(3, 4)
	put_y_value(8, 5)
	call_predicate('$expand_subterms_subslists', 6, 10)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	put_y_value(9, 4)
	put_y_value(7, 5)
	call_predicate('$expand_subterms', 6, 9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(0, 2)
	call_predicate('$build_substitute', 3, 7)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(4, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	put_y_value(3, 6)
	deallocate
	execute_predicate('$expand_subterms/6$0', 7)

$3:
	pseudo_instr1(1, 4)
	neck_cut
	get_x_value(5, 4)
	proceed

$4:
	pseudo_instr1(4, 4)
	neck_cut
	get_x_value(5, 4)
	proceed

$5:
	allocate(9)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(8, 4)
	get_y_variable(1, 5)
	get_y_level(6)
	put_y_variable(0, 19)
	put_y_variable(7, 0)
	call_predicate('member', 2, 9)
	put_y_value(7, 0)
	put_y_value(8, 1)
	put_y_value(0, 2)
	put_y_value(2, 3)
	call_predicate('$subterm_expansion', 4, 7)
	cut(6)
	put_y_value(3, 0)
	get_constant('true', 0)
	pseudo_instr2(70, 25, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(0, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$expand_subterms', 6)

$6:
	allocate(9)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(8, 4)
	get_y_variable(1, 5)
	get_y_level(6)
	put_y_variable(0, 19)
	put_y_variable(7, 0)
	call_predicate('member', 2, 9)
	put_y_value(7, 0)
	put_y_value(8, 1)
	put_y_value(0, 2)
	call_predicate('$subterm_expansion', 3, 7)
	cut(6)
	put_y_value(3, 0)
	get_constant('true', 0)
	pseudo_instr2(70, 25, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(0, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$expand_subterms', 6)

$7:
	pseudo_instr1(43, 4)
	neck_cut
	get_x_value(5, 4)
	proceed

$8:
	pseudo_instr1(108, 4)
	neck_cut
	get_x_value(5, 4)
	proceed

$9:
	allocate(10)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(8, 4)
	get_y_variable(2, 5)
	pseudo_instr1(0, 28)
	neck_cut
	put_x_variable(4, 4)
	put_y_variable(7, 19)
	pseudo_instr3(0, 28, 4, 27)
	put_y_variable(0, 19)
	put_y_variable(1, 2)
	put_y_variable(9, 5)
	call_predicate('$expand_subterms', 6, 10)
	pseudo_instr3(0, 20, 29, 27)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(1, 3)
	put_y_value(3, 4)
	put_y_value(8, 5)
	put_y_value(0, 6)
	call_predicate('$expand_subterms_args', 7, 7)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(4, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	put_y_value(3, 6)
	deallocate
	execute_predicate('$expand_subterms/6$1', 7)

$10:
	allocate(10)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 5)
	put_y_variable(8, 19)
	put_x_variable(0, 0)
	put_y_variable(9, 19)
	pseudo_instr4(7, 4, 28, 0, 29)
	neck_cut
	put_y_variable(6, 19)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_variable(0, 3)
	put_y_value(2, 4)
	put_y_variable(7, 5)
	call_predicate('$expand_subterms_bvars', 6, 10)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	put_y_value(2, 3)
	put_y_value(9, 4)
	put_y_value(6, 5)
	call_predicate('$expand_subterms', 6, 9)
	put_constant('[]', 0)
	pseudo_instr2(61, 27, 0)
	put_x_variable(2, 2)
	pseudo_instr4(7, 2, 28, 27, 26)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(3, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(2, 6)
	deallocate
	execute_predicate('$expand_subterms/6$2', 7)
end('$expand_subterms'/6):



'$expand_subterms_subslists'/6:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(6, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 5)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_list(5)
	unify_x_variable(5)
	unify_y_variable(0)
	call_predicate('$expand_subterms_subs', 6, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$expand_subterms_subslists', 6)
end('$expand_subterms_subslists'/6):



'$expand_subterms_subs'/6:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(6, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 5)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(5)
	get_structure('/', 2, 0)
	unify_x_variable(6)
	unify_x_variable(0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_list(5)
	unify_x_ref(1)
	unify_y_variable(0)
	get_structure('/', 2, 1)
	unify_x_variable(5)
	unify_x_value(0)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_x_value(6, 4)
	call_predicate('$expand_subterms', 6, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$expand_subterms_subs', 6)
end('$expand_subterms_subs'/6):



'$expand_subterms_args'/7:

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
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	pseudo_instr3(1, 26, 21, 0)
	get_x_variable(4, 0)
	pseudo_instr3(1, 26, 20, 0)
	get_x_variable(5, 0)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	call_predicate('$expand_subterms', 6, 7)
	pseudo_instr2(70, 26, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	put_y_value(0, 6)
	deallocate
	execute_predicate('$expand_subterms_args', 7)
end('$expand_subterms_args'/7):



'$expand_subterms_bvars'/6:

	switch_on_term(0, $8, $1, $5, $1, $1, $6)

$5:
	try(6, $1)
	retry($3)
	trust($4)

$6:
	switch_on_constant(0, 4, ['$default':$1, '[]':$7])

$7:
	try(6, $1)
	trust($2)

$8:
	try(6, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_value(0, 5)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_constant('[]', 0)
	get_constant('[]', 5)
	proceed

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(5)
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_x_variable(6)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_list(5)
	unify_x_ref(1)
	unify_y_variable(0)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_variable(5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_x_value(6, 4)
	call_predicate('$expand_subterms', 6, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$expand_subterms_bvars', 6)

$4:
	get_list(0)
	unify_x_variable(6)
	unify_x_variable(0)
	get_list(5)
	unify_x_value(6)
	unify_x_variable(5)
	execute_predicate('$expand_subterms_bvars', 6)
end('$expand_subterms_bvars'/6):



'subterm_expand_depth_limit/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('subterm_expand_depth_limit/1$0'/1):



'subterm_expand_depth_limit'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	put_integer(0, 1)
	pseudo_instr2(1, 1, 0)
	neck_cut
	put_constant('$subterm_expand_depth_limit', 1)
	pseudo_instr2(74, 1, 0)
	proceed

$2:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('$subterm_expand_depth_limit', 2)
	pseudo_instr2(73, 2, 1)
	get_x_value(0, 1)
	proceed

$3:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('subterm_expand_depth_limit/1$0', 1, 1)
	put_structure(1, 0)
	set_constant('subterm_expand_depth_limit')
	set_y_value(0)
	put_structure(1, 1)
	set_constant('?')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('subterm_expand_set_depth_limit')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 3)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('subterm_expand_depth_limit')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('positive_integer', 2)
	execute_predicate('range_exception', 3)
end('subterm_expand_depth_limit'/1):



'$multi_sub_expand_term'/3:


$1:
	get_x_variable(3, 0)
	allocate(7)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	put_constant('$multi_expand_depth_limit', 1)
	pseudo_instr2(73, 1, 0)
	get_y_level(1)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_x_value(3, 1)
	put_y_variable(4, 2)
	put_y_value(5, 3)
	put_y_variable(0, 4)
	call_predicate('$multi_expand_term', 5, 7)
	put_constant('$subterm_expand_depth_limit', 1)
	pseudo_instr2(73, 1, 0)
	get_y_value(3, 0)
	put_y_value(2, 0)
	call_predicate('$subterm_expansion_context', 1, 7)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(6, 5)
	call_predicate('$expand_subterms', 6, 2)
	cut(1)
	pseudo_instr1(46, 20)
	deallocate
	proceed
end('$multi_sub_expand_term'/3):



'add_multi_expansion'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$multi_expansion', 0)
	put_integer(2, 2)
	allocate(0)
	call_predicate('add_linking_clause', 3, 0)
	put_x_variable(1, 1)
	put_constant('yes', 0)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('add_multi_expansion'/1):



'del_multi_expansion'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$multi_expansion', 0)
	put_integer(2, 2)
	allocate(0)
	call_predicate('del_linking_clause', 3, 0)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('del_multi_expansion'/1):



'add_subterm_expansion'/1:


$1:
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 19)
	put_structure(1, 0)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_integer(2, 2)
	call_predicate('add_linking_clause', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_void(1)
	call_predicate('retractall', 1, 1)
	put_x_variable(1, 0)
	put_structure(1, 2)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 3)
	set_constant('get_linking_clause')
	set_x_value(2)
	set_x_variable(2)
	set_integer(2)
	put_structure(1, 4)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('get_linking_clause')
	set_x_value(4)
	set_x_value(2)
	set_integer(3)
	put_structure(2, 4)
	set_constant(';')
	set_x_value(3)
	set_x_value(1)
	put_structure(2, 1)
	set_constant('^')
	set_x_value(2)
	set_x_value(4)
	put_y_value(0, 2)
	call_predicate('bagof', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_y_value(0)
	call_predicate('assert', 1, 0)
	put_x_variable(0, 0)
	put_constant('yes', 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('add_subterm_expansion'/1):



'del_subterm_expansion'/1:


$1:
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 19)
	put_structure(1, 0)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_integer(2, 2)
	call_predicate('del_linking_clause', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_void(1)
	call_predicate('retractall', 1, 1)
	put_x_variable(1, 0)
	put_structure(1, 2)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 3)
	set_constant('get_linking_clause')
	set_x_value(2)
	set_x_variable(2)
	set_integer(2)
	put_structure(1, 4)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('get_linking_clause')
	set_x_value(4)
	set_x_value(2)
	set_integer(3)
	put_structure(2, 4)
	set_constant(';')
	set_x_value(3)
	set_x_value(1)
	put_structure(2, 1)
	set_constant('^')
	set_x_value(2)
	set_x_value(4)
	put_y_value(0, 2)
	call_predicate('bagof', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_y_value(0)
	call_predicate('assert', 1, 0)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('del_subterm_expansion'/1):



'add_multi_expansion_vars'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$multi_expansion', 0)
	put_integer(3, 2)
	allocate(0)
	call_predicate('add_linking_clause', 3, 0)
	put_x_variable(1, 1)
	put_constant('yes', 0)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('add_multi_expansion_vars'/1):



'del_multi_expansion_vars'/1:


$1:
	get_x_variable(1, 0)
	put_constant('$multi_expansion', 0)
	put_integer(3, 2)
	allocate(0)
	call_predicate('del_linking_clause', 3, 0)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('del_multi_expansion_vars'/1):



'add_subterm_expansion_vars'/1:


$1:
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 19)
	put_structure(1, 0)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_integer(3, 2)
	call_predicate('add_linking_clause', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_void(1)
	call_predicate('retractall', 1, 1)
	put_x_variable(1, 0)
	put_structure(1, 2)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 3)
	set_constant('get_linking_clause')
	set_x_value(2)
	set_x_variable(2)
	set_integer(2)
	put_structure(1, 4)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('get_linking_clause')
	set_x_value(4)
	set_x_value(2)
	set_integer(3)
	put_structure(2, 4)
	set_constant(';')
	set_x_value(3)
	set_x_value(1)
	put_structure(2, 1)
	set_constant('^')
	set_x_value(2)
	set_x_value(4)
	put_y_value(0, 2)
	call_predicate('bagof', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_y_value(0)
	call_predicate('assert', 1, 0)
	put_x_variable(0, 0)
	put_constant('yes', 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('add_subterm_expansion_vars'/1):



'del_subterm_expansion_vars'/1:


$1:
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 19)
	put_structure(1, 0)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_void(1)
	call_predicate('retractall', 1, 1)
	put_x_variable(1, 0)
	put_structure(1, 2)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 3)
	set_constant('get_linking_clause')
	set_x_value(2)
	set_x_variable(2)
	set_integer(2)
	put_structure(1, 4)
	set_constant('$subterm_expansion')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('get_linking_clause')
	set_x_value(4)
	set_x_value(2)
	set_integer(3)
	put_structure(2, 4)
	set_constant(';')
	set_x_value(3)
	set_x_value(1)
	put_structure(2, 1)
	set_constant('^')
	set_x_value(2)
	set_x_value(4)
	put_y_value(0, 2)
	call_predicate('bagof', 3, 1)
	put_structure(1, 0)
	set_constant('$subterm_expansion_context')
	set_y_value(0)
	call_predicate('assert', 1, 0)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion', 2)
end('del_subterm_expansion_vars'/1):



'$update_multi_sub_expansion/2$0'/1:

	switch_on_term(0, $8, $7, $7, $7, $7, $5)

$5:
	switch_on_constant(0, 4, ['$default':$7, 'no':$6])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(1, $1)
	retry($2)
	trust($3)

$8:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(46, 0)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_x_variable(1, 1)
	put_constant('$multi_expansion', 0)
	put_integer(2, 2)
	call_predicate('get_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 0)
	get_constant('yes', 0)
	deallocate
	proceed

$3:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_x_variable(1, 1)
	put_constant('$multi_expansion', 0)
	put_integer(3, 2)
	call_predicate('get_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 0)
	get_constant('yes', 0)
	deallocate
	proceed

$4:
	put_constant('no', 1)
	get_x_value(0, 1)
	proceed
end('$update_multi_sub_expansion/2$0'/1):



'$update_multi_sub_expansion/2$1'/1:

	switch_on_term(0, $8, $7, $7, $7, $7, $5)

$5:
	switch_on_constant(0, 4, ['$default':$7, 'no':$6])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(1, $1)
	retry($2)
	trust($3)

$8:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(46, 0)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_structure(1, 0)
	set_constant('$subterm_expansion')
	set_void(1)
	put_x_variable(1, 1)
	put_integer(2, 2)
	call_predicate('get_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 0)
	get_constant('yes', 0)
	deallocate
	proceed

$3:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_structure(1, 0)
	set_constant('$subterm_expansion')
	set_void(1)
	put_x_variable(1, 1)
	put_integer(3, 2)
	call_predicate('get_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 0)
	get_constant('yes', 0)
	deallocate
	proceed

$4:
	put_constant('no', 1)
	get_x_value(0, 1)
	proceed
end('$update_multi_sub_expansion/2$1'/1):



'$update_multi_sub_expansion/2$2'/2:

	switch_on_term(0, $8, 'fail', 'fail', 'fail', 'fail', $5)

$5:
	switch_on_constant(0, 4, ['$default':'fail', 'yes':$6, 'no':$7])

$6:
	try(2, $1)
	trust($2)

$7:
	try(2, $3)
	trust($4)

$8:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	put_constant('yes', 2)
	get_x_value(0, 2)
	put_constant('yes', 0)
	get_x_value(1, 0)
	neck_cut
	put_constant('$multi_sub_expand_term', 0)
	execute_predicate('$update_multi_sub_expansion', 1)

$2:
	put_constant('yes', 2)
	get_x_value(0, 2)
	put_constant('no', 0)
	get_x_value(1, 0)
	neck_cut
	put_constant('$multi_expand_term', 0)
	execute_predicate('$update_multi_sub_expansion', 1)

$3:
	put_constant('no', 2)
	get_x_value(0, 2)
	put_constant('yes', 0)
	get_x_value(1, 0)
	neck_cut
	put_constant('$expand_subterms', 0)
	execute_predicate('$update_multi_sub_expansion', 1)

$4:
	put_constant('no', 2)
	get_x_value(0, 2)
	put_constant('no', 0)
	get_x_value(1, 0)
	neck_cut
	execute_predicate('$update_multi_sub_expansion', 0)
end('$update_multi_sub_expansion/2$2'/2):



'$update_multi_sub_expansion'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	call_predicate('$update_multi_sub_expansion/2$0', 1, 2)
	put_y_value(0, 0)
	call_predicate('$update_multi_sub_expansion/2$1', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$update_multi_sub_expansion/2$2', 2)
end('$update_multi_sub_expansion'/2):



'$update_multi_sub_expansion/1$0'/1:

	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	call_predicate('get_linking_clause', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_constant('term_expansion', 0)
	put_constant('$multi_sub_expand_term', 1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	deallocate
	execute_predicate('add_linking_clause', 3)

$3:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_constant('term_expansion', 0)
	put_constant('$multi_expand_term', 1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	deallocate
	execute_predicate('add_linking_clause', 3)

$4:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	put_constant('term_expansion', 0)
	put_constant('$expand_subterms', 1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 2)
	cut(1)
	put_y_value(0, 1)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	deallocate
	execute_predicate('add_linking_clause', 3)

$5:
	get_x_variable(1, 0)
	put_constant('term_expansion', 0)
	put_integer(3, 2)
	execute_predicate('add_linking_clause', 3)
end('$update_multi_sub_expansion/1$0'/1):



'$update_multi_sub_expansion'/1:


$1:
	execute_predicate('$update_multi_sub_expansion/1$0', 1)
end('$update_multi_sub_expansion'/1):



'$update_multi_sub_expansion/0$0'/0:

	try(0, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(1)
	get_y_level(0)
	put_constant('term_expansion', 0)
	put_constant('$multi_sub_expand_term', 1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_level(0)
	put_constant('term_expansion', 0)
	put_constant('$multi_expand_term', 1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 1)
	cut(0)
	deallocate
	proceed

$3:
	allocate(1)
	get_y_level(0)
	put_constant('term_expansion', 0)
	put_constant('$expand_subterms', 1)
	put_integer(3, 2)
	call_predicate('del_linking_clause', 3, 1)
	cut(0)
	deallocate
	proceed

$4:
	proceed
end('$update_multi_sub_expansion/0$0'/0):



'$update_multi_sub_expansion'/0:


$1:
	execute_predicate('$update_multi_sub_expansion/0$0', 0)
end('$update_multi_sub_expansion'/0):



'list_expansions'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('term_expansion')
	set_integer(2)
	allocate(0)
	call_predicate('listing', 1, 0)
	deallocate
	execute_predicate('$list_expansions', 0)
end('list_expansions'/0):



'$list_expansions/0$0'/4:

	switch_on_term(0, $10, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, '$multi_expand_term'/3:$7, '$expand_subterms'/3:$8, '$multi_sub_expand_term'/3:$9])

$6:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(4, $1)
	trust($4)

$8:
	try(4, $2)
	trust($4)

$9:
	try(4, $3)
	trust($4)

$10:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure('$multi_expand_term', 3, 0)
	unify_void(3)
	neck_cut
	execute_predicate('$list_multi_expansions', 0)

$2:
	get_structure('$expand_subterms', 3, 0)
	unify_void(3)
	neck_cut
	execute_predicate('$list_sub_expansions', 0)

$3:
	get_structure('$multi_sub_expand_term', 3, 0)
	unify_void(3)
	neck_cut
	allocate(0)
	call_predicate('$list_multi_expansions', 0, 0)
	deallocate
	execute_predicate('$list_sub_expansions', 0)

$4:
	get_x_variable(4, 0)
	put_structure(3, 5)
	set_constant('term_expansion')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(2, 0)
	set_constant(':-')
	set_x_value(5)
	set_x_value(4)
	allocate(0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$list_expansions/0$0'/4):



'$list_expansions'/0:

	try(0, $1)
	trust($2)

$1:
	put_structure(3, 0)
	set_constant('term_expansion')
	allocate(4)
	set_y_variable(3)
	set_y_variable(2)
	set_y_variable(1)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	call_predicate('$list_expansions/0$0', 4, 0)
	fail

$2:
	proceed
end('$list_expansions'/0):



'$list_multi_expansions'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	put_structure(2, 0)
	set_constant('$multi_expansion')
	set_constant('Term0')
	set_constant('Term')
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_y_value(0)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('multi-expansion: ')
	set_x_value(2)
	call_predicate('write_term_list', 1, 0)
	fail

$2:
	put_structure(3, 0)
	set_constant('$multi_expansion')
	set_constant('Term0')
	set_constant('Term')
	set_constant('Vars')
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_y_value(0)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('multi-expansion-vars: ')
	set_x_value(2)
	call_predicate('write_term_list', 1, 0)
	fail

$3:
	proceed
end('$list_multi_expansions'/0):



'$list_sub_expansions'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	put_structure(3, 0)
	set_constant('$subterm_expansion')
	set_void(1)
	set_constant('Term0')
	set_constant('Term')
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_y_value(0)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('subterm-expansion: ')
	set_x_value(2)
	call_predicate('write_term_list', 1, 0)
	fail

$2:
	put_structure(4, 0)
	set_constant('$subterm_expansion')
	set_void(1)
	set_constant('Term0')
	set_constant('Term')
	set_constant('Vars')
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_y_value(0)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(0)
	set_constant('subterm-expansion-vars: ')
	set_x_value(2)
	call_predicate('write_term_list', 1, 0)
	fail

$3:
	proceed
end('$list_sub_expansions'/0):



