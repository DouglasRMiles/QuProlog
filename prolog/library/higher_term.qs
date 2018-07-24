'build_structure'/4:


$1:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(2)
	get_y_variable(1, 3)
	pseudo_instr3(38, 4, 0, 2)
	get_y_variable(0, 2)
	call_predicate('$build_structure', 3, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('build_structure'/4):



'$build_structure'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_integer(2, 1)
	pseudo_instr3(38, 21, 1, 0)
	put_integer(1, 1)
	pseudo_instr3(39, 0, 1, 22)
	put_integer(2, 1)
	put_y_variable(3, 19)
	pseudo_instr3(39, 0, 1, 23)
	call_predicate('call_with_inlining', 1, 4)
	pseudo_instr3(39, 20, 22, 23)
	pseudo_instr2(70, 22, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$build_structure', 3)
end('$build_structure'/3):



'collect_simple_terms'/4:


$1:
	allocate(6)
	get_y_variable(3, 0)
	get_x_variable(0, 1)
	get_y_variable(5, 2)
	get_y_variable(1, 3)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('$simplify_if_local', 2, 6)
	pseudo_instr2(24, 24, 0)
	put_y_value(5, 1)
	put_y_value(2, 2)
	put_y_value(3, 3)
	call_predicate('$collect_substitutions', 4, 5)
	pseudo_instr2(25, 24, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	call_predicate('$collect_bare_term', 4, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('collect_simple_terms'/4):



'$collect_substitutions'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr1(18, 3)
	get_x_value(0, 3)
	neck_cut
	get_x_value(2, 1)
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	pseudo_instr2(26, 23, 0)
	put_y_variable(0, 2)
	call_predicate('$collect_substitutions', 4, 4)
	put_y_value(3, 0)
	put_y_value(0, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_integer(1, 1)
	deallocate
	execute_predicate('$collect_sub', 5)
end('$collect_substitutions'/4):



'$collect_sub'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(6, 1)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	pseudo_instr3(17, 26, 25, 0)
	get_y_variable(1, 0)
	neck_cut
	pseudo_instr2(69, 26, 0)
	get_x_variable(1, 0)
	put_y_variable(0, 19)
	put_y_value(5, 0)
	put_y_variable(4, 3)
	call_predicate('$collect_sub', 5, 7)
	pseudo_instr3(18, 26, 25, 0)
	get_x_variable(1, 0)
	put_y_value(2, 0)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('collect_simple_terms', 4, 4)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$collect_bare_term', 4)

$2:
	get_x_value(2, 3)
	neck_cut
	proceed
end('$collect_sub'/5):



'$collect_bare_term/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call_predicate', 4, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_value(3, 2)
	proceed
end('$collect_bare_term/4$0'/4):



'$collect_bare_term'/4:

	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(4, 0)
	get_x_variable(5, 1)
	get_x_variable(6, 2)
	get_x_variable(0, 3)
	pseudo_instr1(45, 4)
	neck_cut
	put_x_value(4, 1)
	put_x_value(5, 2)
	put_x_value(6, 3)
	execute_predicate('$collect_bare_term/4$0', 4)

$2:
	get_x_variable(4, 1)
	allocate(6)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	pseudo_instr1(5, 0)
	neck_cut
	put_x_variable(1, 1)
	put_y_variable(5, 19)
	put_y_variable(1, 19)
	pseudo_instr4(7, 0, 1, 25, 21)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	put_x_value(4, 2)
	put_y_variable(4, 3)
	call_predicate('collect_simple_terms', 4, 6)
	put_y_value(2, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('collect_simple_terms', 4, 4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('collect_simple_terms', 4)

$3:
	allocate(5)
	get_y_variable(4, 0)
	get_x_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	put_x_variable(1, 1)
	put_y_variable(1, 19)
	pseudo_instr3(0, 24, 1, 21)
	put_y_value(2, 0)
	put_x_value(4, 2)
	put_y_variable(0, 3)
	call_predicate('collect_simple_terms', 4, 5)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	put_y_value(0, 4)
	put_y_value(3, 5)
	put_integer(0, 0)
	deallocate
	execute_predicate('$collect_args', 6)
end('$collect_bare_term'/4):



'$collect_args'/6:

	try(6, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	get_x_value(4, 5)
	neck_cut
	proceed

$2:
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_x_variable(2, 4)
	get_y_variable(2, 5)
	pseudo_instr2(69, 0, 1)
	get_y_variable(1, 1)
	pseudo_instr3(1, 21, 23, 0)
	get_x_variable(1, 0)
	put_y_value(4, 0)
	put_y_variable(0, 3)
	call_predicate('collect_simple_terms', 4, 6)
	put_y_value(1, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(0, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$collect_args', 6)
end('$collect_args'/6):



'transform_simple_terms'/3:


$1:
	allocate(6)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_variable(2, 2)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(5, 1)
	put_y_variable(3, 2)
	call_predicate('$break_substitute', 3, 6)
	put_y_value(5, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	call_predicate('$transform_substitutions', 3, 5)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(4, 2)
	call_predicate('$transform_bare_term', 3, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$build_substitute', 3)
end('transform_simple_terms'/3):



'$transform_substitutions'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	call_predicate('$transform_sub', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$transform_substitutions', 3)
end('$transform_substitutions'/3):



'$transform_sub'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	call_predicate('$transform_bare_term', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$transform_sub', 3)
end('$transform_sub'/3):



'$transform_bare_term'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	get_x_variable(4, 1)
	get_x_variable(0, 2)
	pseudo_instr1(45, 3)
	neck_cut
	put_x_value(3, 1)
	put_x_value(4, 2)
	execute_predicate('call_predicate', 3)

$2:
	allocate(7)
	get_y_variable(3, 1)
	get_y_variable(5, 2)
	pseudo_instr1(5, 0)
	neck_cut
	put_x_variable(1, 1)
	put_y_variable(6, 19)
	put_y_variable(4, 19)
	pseudo_instr4(7, 0, 1, 26, 24)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(5, 0)
	put_y_variable(2, 2)
	call_predicate('transform_simple_terms', 3, 7)
	put_y_value(5, 0)
	put_y_value(6, 1)
	put_y_value(1, 2)
	call_predicate('transform_simple_terms', 3, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	call_predicate('transform_simple_terms', 3, 4)
	put_constant('[]', 0)
	pseudo_instr2(61, 21, 0)
	pseudo_instr4(7, 23, 22, 21, 20)
	deallocate
	proceed

$3:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_x_variable(1, 1)
	put_y_variable(0, 19)
	pseudo_instr3(0, 23, 1, 20)
	put_y_value(1, 0)
	put_y_variable(4, 2)
	call_predicate('transform_simple_terms', 3, 5)
	pseudo_instr3(0, 22, 24, 20)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_integer(0, 0)
	deallocate
	execute_predicate('$transform_args', 5)
end('$transform_bare_term'/3):



'$transform_args'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	pseudo_instr2(69, 0, 1)
	get_y_variable(0, 1)
	pseudo_instr3(1, 20, 23, 0)
	get_x_variable(1, 0)
	pseudo_instr3(1, 20, 22, 0)
	get_x_variable(2, 0)
	put_y_value(1, 0)
	call_predicate('transform_simple_terms', 3, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$transform_args', 5)
end('$transform_args'/5):



'transform_subterms'/3:


$1:
	pseudo_instr2(65, 1, 3)
	allocate(1)
	get_y_variable(0, 3)
	call_predicate('$transform_subterms', 3, 1)
	pseudo_instr1(52, 20)
	deallocate
	proceed
end('transform_subterms'/3):



'$transform_subterms'/3:

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
	get_x_variable(0, 1)
	get_y_variable(2, 2)
	pseudo_instr1(6, 0)
	neck_cut
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(5, 1)
	put_y_variable(3, 2)
	call_predicate('$break_substitute', 3, 6)
	put_y_value(5, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	call_predicate('$transform_subterms_subslists', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('$transform_subterms', 3, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$build_substitute', 3)

$2:
	pseudo_instr1(1, 1)
	neck_cut
	get_x_value(2, 1)
	proceed

$3:
	pseudo_instr1(4, 1)
	neck_cut
	get_x_value(2, 1)
	proceed

$4:
	pseudo_instr1(43, 1)
	neck_cut
	execute_predicate('call_predicate', 3)

$5:
	pseudo_instr1(108, 1)
	neck_cut
	execute_predicate('call_predicate', 3)

$6:
	allocate(6)
	get_y_variable(2, 0)
	get_y_variable(4, 1)
	get_y_variable(1, 2)
	pseudo_instr1(0, 24)
	neck_cut
	put_x_variable(1, 1)
	put_y_variable(3, 19)
	pseudo_instr3(0, 24, 1, 23)
	put_y_variable(0, 19)
	put_y_variable(5, 2)
	call_predicate('$transform_subterms', 3, 6)
	pseudo_instr3(0, 20, 25, 23)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('$transform_subterms_args', 4, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('call_predicate', 3)

$7:
	allocate(7)
	get_y_variable(1, 0)
	get_y_variable(0, 2)
	put_y_variable(5, 19)
	put_x_variable(0, 0)
	put_y_variable(6, 19)
	pseudo_instr4(7, 1, 25, 0, 26)
	neck_cut
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(3, 1)
	put_y_value(1, 2)
	call_predicate('$transform_subterms_bvars', 3, 7)
	put_y_value(1, 0)
	put_y_value(6, 1)
	put_y_value(2, 2)
	call_predicate('$transform_subterms', 3, 6)
	put_y_value(1, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	call_predicate('$transform_subterms', 3, 5)
	put_constant('[]', 0)
	pseudo_instr2(61, 23, 0)
	put_x_variable(1, 1)
	pseudo_instr4(7, 1, 24, 23, 22)
	put_y_value(1, 0)
	put_y_value(0, 2)
	deallocate
	execute_predicate('call_predicate', 3)
end('$transform_subterms'/3):



'$transform_subterms_args'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	pseudo_instr3(1, 23, 21, 0)
	get_x_variable(1, 0)
	pseudo_instr3(1, 23, 20, 0)
	get_x_variable(2, 0)
	put_y_value(2, 0)
	call_predicate('$transform_subterms', 3, 4)
	pseudo_instr2(70, 23, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$transform_subterms_args', 4)
end('$transform_subterms_args'/4):



'$transform_subterms_subslists'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	call_predicate('$transform_subterms_subs', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$transform_subterms_subslists', 3)
end('$transform_subterms_subslists'/3):



'$transform_subterms_subs'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(2)
	get_structure('/', 2, 0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(1)
	unify_y_variable(1)
	get_structure('/', 2, 1)
	unify_x_variable(4)
	unify_x_value(0)
	get_y_variable(0, 2)
	put_y_value(0, 0)
	put_x_value(3, 1)
	put_x_value(4, 2)
	call_predicate('$transform_subterms', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$transform_subterms_subs', 3)
end('$transform_subterms_subs'/3):



'$transform_subterms_bvars'/3:

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
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(2)
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_list(1)
	unify_x_ref(1)
	unify_y_variable(1)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_variable(4)
	get_y_variable(0, 2)
	neck_cut
	put_y_value(0, 0)
	put_x_value(3, 1)
	put_x_value(4, 2)
	call_predicate('$transform_subterms', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$transform_subterms_bvars', 3)

$3:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(3)
	unify_x_variable(1)
	execute_predicate('$transform_subterms_bvars', 3)
end('$transform_subterms_bvars'/3):



