'chr_init'/0:


$1:
	put_integer(1180, 0)
	put_constant('xfx', 1)
	put_constant('==>', 2)
	allocate(0)
	call_predicate('op', 3, 0)
	put_integer(1180, 0)
	put_constant('xfx', 1)
	put_constant('<=>', 2)
	call_predicate('op', 3, 0)
	put_integer(1150, 0)
	put_constant('fx', 1)
	put_constant('constraints', 2)
	call_predicate('op', 3, 0)
	put_integer(1150, 0)
	put_constant('fx', 1)
	put_constant('chr_constraint', 2)
	call_predicate('op', 3, 0)
	put_integer(1150, 0)
	put_constant('fx', 1)
	put_constant('handler', 2)
	call_predicate('op', 3, 0)
	put_integer(1150, 0)
	put_constant('fx', 1)
	put_constant('rules', 2)
	call_predicate('op', 3, 0)
	put_integer(1100, 0)
	put_constant('xfx', 1)
	put_constant('\\', 2)
	call_predicate('op', 3, 0)
	put_integer(1200, 0)
	put_constant('xfx', 1)
	put_constant('@', 2)
	call_predicate('op', 3, 0)
	put_integer(1190, 0)
	put_constant('xfx', 1)
	put_constant('pragma', 2)
	call_predicate('op', 3, 0)
	put_integer(500, 0)
	put_constant('yfx', 1)
	put_constant('#', 2)
	call_predicate('op', 3, 0)
	put_integer(1150, 0)
	put_constant('fx', 1)
	put_constant('chr_type', 2)
	call_predicate('op', 3, 0)
	put_integer(1150, 0)
	put_constant('fx', 1)
	put_constant('chr_declaration', 2)
	call_predicate('op', 3, 0)
	put_integer(1130, 0)
	put_constant('xfx', 1)
	put_constant('--->', 2)
	call_predicate('op', 3, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$chr term  ')
	set_integer(1)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$chr_constraint_info')
	set_integer(2)
	call_predicate('dynamic', 1, 0)
	put_constant('$chr_compile', 0)
	deallocate
	execute_predicate('add_expansion', 1)
end('chr_init'/0):



'$chr_expandable'/1:

	switch_on_term(0, $7, 'fail', 'fail', $5, 'fail', 'fail')

$5:
	switch_on_structure(0, 16, ['$default':'fail', '$'/0:$6, '<=>'/2:$1, '==>'/2:$2, '@'/2:$3, 'pragma'/2:$4])

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

$1:
	get_structure('<=>', 2, 0)
	unify_void(2)
	proceed

$2:
	get_structure('==>', 2, 0)
	unify_void(2)
	proceed

$3:
	get_structure('@', 2, 0)
	unify_void(2)
	proceed

$4:
	get_structure('pragma', 2, 0)
	unify_void(2)
	proceed
end('$chr_expandable'/1):



'$chr_constraints'/1:

	switch_on_term(0, $9, 'fail', 'fail', $5, 'fail', 'fail')

$5:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$6, ':-'/1:$7, '?-'/1:$8])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(1, $1)
	trust($2)

$8:
	try(1, $3)
	trust($4)

$9:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('constraints', 1, 0)
	unify_void(1)
	proceed

$2:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_constraint', 1, 0)
	unify_void(1)
	proceed

$3:
	get_structure('?-', 1, 0)
	unify_x_ref(0)
	get_structure('constraints', 1, 0)
	unify_void(1)
	proceed

$4:
	get_structure('?-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_constraint', 1, 0)
	unify_void(1)
	proceed
end('$chr_constraints'/1):



'$chr_ignore'/1:

	switch_on_term(0, $12, 'fail', 'fail', $9, 'fail', 'fail')

$9:
	switch_on_structure(0, 16, ['$default':'fail', '$'/0:$10, 'constraints'/1:$1, ':-'/1:$11, 'chr_type'/1:$3, 'option'/2:$5, 'handler'/1:$7, 'rules'/1:$8])

$10:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$11:
	try(1, $2)
	retry($4)
	trust($6)

$12:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_structure('constraints', 1, 0)
	unify_void(1)
	proceed

$2:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_type', 1, 0)
	unify_void(1)
	proceed

$3:
	get_structure('chr_type', 1, 0)
	unify_void(1)
	proceed

$4:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_declaration', 1, 0)
	unify_void(1)
	proceed

$5:
	get_structure('option', 2, 0)
	unify_void(2)
	proceed

$6:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_option', 2, 0)
	unify_void(2)
	proceed

$7:
	get_structure('handler', 1, 0)
	unify_void(1)
	proceed

$8:
	get_structure('rules', 1, 0)
	unify_void(1)
	proceed
end('$chr_ignore'/1):



'$chr_compile'/2:

	switch_on_term(0, $8, $7, $7, $7, $7, $5)

$5:
	switch_on_constant(0, 4, ['$default':$7, 'end_of_file':$6])

$6:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$8:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('[]', 1)
	allocate(1)
	get_y_level(0)
	call_predicate('$chr_ignore', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_constant('[]', 1)
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('$chr_constraints', 1, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$extract_constraints', 1)

$3:
	get_constant('[]', 1)
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('$chr_expandable', 1, 2)
	cut(1)
	put_structure(1, 0)
	set_constant('$chr term  ')
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$4:
	get_constant('end_of_file', 0)
	allocate(10)
	get_y_variable(2, 1)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_structure(2, 0)
	set_constant('/')
	set_x_variable(2)
	set_x_variable(3)
	put_structure(2, 1)
	set_constant('$chr_constraint_info')
	set_x_value(2)
	set_x_value(3)
	put_y_variable(9, 2)
	call_predicate('findall', 3, 10)
	put_y_value(9, 0)
	put_y_value(1, 1)
	call_predicate('$gen_names_code', 2, 10)
	put_y_value(9, 0)
	put_y_value(4, 1)
	call_predicate('$gen_constraints_code', 2, 9)
	put_x_variable(1, 0)
	put_structure(1, 2)
	set_constant('$chr term  ')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('retract')
	set_x_value(2)
	put_y_value(8, 2)
	call_predicate('findall', 3, 9)
	put_constant('[]', 0)
	pseudo_instr2(133, 28, 0)
	put_y_value(8, 0)
	put_integer(1, 1)
	call_predicate('$compile_rules', 2, 8)
	put_y_value(7, 0)
	call_predicate('$collect_code', 1, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	call_predicate('$unfold_code', 3, 7)
	put_structure(2, 0)
	set_constant('$chr_constraint_info')
	set_void(2)
	call_predicate('retractall', 1, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('append', 3, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)
end('$chr_compile'/2):



'$gen_names_code'/2:

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
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(1)
	get_structure('/', 2, 0)
	unify_y_variable(4)
	unify_void(1)
	get_list(1)
	unify_y_variable(3)
	unify_y_variable(0)
	put_y_value(4, 1)
	put_y_variable(2, 2)
	put_constant('chr_constraints__', 0)
	call_predicate('atom_concat', 3, 5)
	put_y_value(3, 0)
	get_structure('$chr_names', 2, 0)
	unify_y_value(4)
	unify_y_value(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$gen_names_code', 2)
end('$gen_names_code'/2):



'$compile_rules'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(0)
	get_y_variable(1, 1)
	put_y_variable(2, 2)
	call_predicate('$compile_a_rule', 3, 3)
	put_y_value(2, 0)
	call_predicate('$unfold_rule', 1, 2)
	pseudo_instr2(69, 21, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$compile_rules', 2)
end('$compile_rules'/2):



'$unfold_rule'/1:


$1:
	get_structure('chr_rule', 5, 0)
	allocate(6)
	unify_y_variable(5)
	unify_y_variable(4)
	unify_y_variable(3)
	unify_y_variable(2)
	unify_y_variable(1)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_variable(0, 2)
	call_predicate('diff_list', 3, 6)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	call_predicate('$unfold_remove', 6, 6)
	put_y_value(0, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$unfold_left', 6)
end('$unfold_rule'/1):



'$unfold_remove/6$0'/8:

	try(8, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_x_variable(8, 8)
	put_x_variable(9, 9)
	pseudo_instr3(0, 1, 8, 9)
	put_structure(9, 0)
	set_constant('chr_rule_data')
	set_x_value(8)
	set_x_value(9)
	set_constant('remove')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	set_x_value(6)
	set_x_value(7)
	execute_predicate('assert', 1)

$2:
	proceed
end('$unfold_remove/6$0'/8):



'$unfold_remove'/6:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(6, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	allocate(8)
	unify_y_variable(7)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(7)
	set_constant('[]')
	put_y_variable(6, 2)
	call_predicate('diff_list', 3, 8)
	put_y_value(7, 0)
	get_structure('c', 3, 0)
	unify_x_variable(1)
	unify_void(1)
	unify_x_variable(0)
	put_y_value(7, 2)
	put_y_value(4, 3)
	put_y_value(6, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	call_predicate('$unfold_remove/6$0', 8, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$unfold_remove', 6)
end('$unfold_remove'/6):



'$unfold_left/6$0'/8:

	try(8, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_x_variable(8, 8)
	put_x_variable(9, 9)
	pseudo_instr3(0, 1, 8, 9)
	put_structure(9, 0)
	set_constant('chr_rule_data')
	set_x_value(8)
	set_x_value(9)
	set_constant('leave')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	set_x_value(6)
	set_x_value(7)
	execute_predicate('assert', 1)

$2:
	proceed
end('$unfold_left/6$0'/8):



'$unfold_left'/6:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(6, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	allocate(8)
	unify_y_variable(7)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(7)
	set_constant('[]')
	put_y_variable(6, 2)
	call_predicate('diff_list', 3, 8)
	put_y_value(7, 0)
	get_structure('c', 3, 0)
	unify_x_variable(1)
	unify_void(1)
	unify_x_variable(0)
	put_y_value(7, 2)
	put_y_value(4, 3)
	put_y_value(6, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	call_predicate('$unfold_left/6$0', 8, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$unfold_left', 6)
end('$unfold_left'/6):



'$collect_code'/1:


$1:
	allocate(2)
	get_y_variable(1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_x_variable(2)
	set_x_variable(3)
	put_structure(2, 1)
	set_constant('$chr_constraint_info')
	set_x_value(2)
	set_x_value(3)
	put_y_variable(0, 2)
	call_predicate('findall', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$collect_code', 2)
end('$collect_code'/1):



'$collect_code'/2:

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
	unify_x_ref(0)
	allocate(4)
	unify_y_variable(1)
	get_structure('/', 2, 0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_list(1)
	unify_x_ref(0)
	unify_y_variable(0)
	get_structure('-', 2, 0)
	unify_x_ref(0)
	unify_y_variable(3)
	get_structure('/', 2, 0)
	unify_x_value(2)
	unify_x_value(3)
	put_structure(9, 0)
	set_constant('chr_rule_data')
	set_x_value(2)
	set_x_value(3)
	set_x_variable(1)
	set_x_variable(4)
	set_x_variable(5)
	set_x_variable(6)
	set_x_variable(7)
	set_x_variable(8)
	set_x_variable(9)
	put_structure(9, 10)
	set_constant('chr_rule_data')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	set_x_value(6)
	set_x_value(7)
	set_x_value(8)
	set_x_value(9)
	put_structure(1, 1)
	set_constant('retract')
	set_x_value(10)
	put_y_variable(2, 2)
	call_predicate('findall', 3, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$remove_chr_repeat_rules', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$collect_code', 2)
end('$collect_code'/2):



'$unfold_code/3$0'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_value(1)
	unify_void(1)
	neck_cut
	proceed

$2:
	put_constant('all', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_code/3$0'/2):



'$unfold_code/3$1'/6:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$1:
	get_x_variable(6, 0)
	get_x_variable(0, 1)
	allocate(8)
	get_y_variable(7, 2)
	get_y_variable(6, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	put_constant('[]', 1)
	get_x_value(6, 1)
	neck_cut
	put_y_variable(0, 19)
	put_list(2)
	set_y_variable(1)
	set_constant('[]')
	put_list(1)
	set_y_variable(2)
	set_x_value(2)
	put_y_variable(5, 2)
	call_predicate('append', 3, 8)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(7)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_integer(1)
	unify_constant('[]')
	put_constant('__', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_x_variable(2, 0)
	put_y_value(0, 0)
	put_list(1)
	set_x_value(2)
	set_y_value(5)
	call_predicate('=..', 2, 5)
	put_y_value(4, 0)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':-', 2, 0)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure('chr_add_constraint', 3, 0)
	unify_y_value(2)
	unify_y_value(3)
	unify_y_value(1)
	deallocate
	proceed

$2:
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	put_integer(1, 3)
	put_constant('not_added', 5)
	put_constant('no_nonvar', 6)
	execute_predicate('$unfold_rules', 7)
end('$unfold_code/3$1'/6):



'$unfold_code'/3:

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
	unify_x_ref(0)
	allocate(10)
	unify_y_variable(4)
	get_structure('-', 2, 0)
	unify_x_ref(0)
	unify_y_variable(7)
	get_structure('/', 2, 0)
	unify_y_variable(9)
	unify_y_variable(8)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 29, 28)
	put_y_variable(5, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_list(1)
	set_y_value(9)
	set_y_variable(6)
	call_predicate('=..', 2, 10)
	put_y_value(6, 0)
	put_y_value(5, 1)
	call_predicate('$unfold_code/3$0', 2, 10)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(9, 2)
	put_y_value(8, 3)
	put_y_value(1, 4)
	put_y_value(5, 5)
	call_predicate('$unfold_code/3$1', 6, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('$unfold_code', 3, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)
end('$unfold_code'/3):



'$unfold_rules/7$0'/4:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'chr_rule_data'/9:$5])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$6:
	try(4, $1)
	trust($2)

$1:
	get_structure('chr_rule_data', 9, 0)
	unify_void(2)
	unify_constant('remove')
	unify_void(6)
	neck_cut
	get_x_value(1, 2)
	put_constant('nonvar', 0)
	get_x_value(3, 0)
	proceed

$2:
	pseudo_instr2(69, 2, 0)
	get_x_value(1, 0)
	put_constant('no_nonvar', 0)
	get_x_value(3, 0)
	proceed
end('$unfold_rules/7$0'/4):



'$unfold_rules'/7:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(7, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 4)
	proceed

$2:
	get_list(0)
	allocate(11)
	unify_y_variable(10)
	unify_y_variable(8)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(9, 3)
	get_y_variable(2, 4)
	get_x_variable(7, 5)
	get_x_variable(8, 6)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_value(10, 0)
	put_y_value(8, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(9, 4)
	put_y_variable(1, 5)
	put_x_value(7, 6)
	put_y_variable(5, 7)
	call_predicate('$unfold_rule_body', 9, 11)
	put_y_value(10, 0)
	put_y_value(4, 1)
	put_y_value(9, 2)
	put_y_value(3, 3)
	call_predicate('$unfold_rules/7$0', 4, 9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(4, 3)
	put_y_value(0, 4)
	put_y_value(5, 5)
	put_y_value(3, 6)
	call_predicate('$unfold_rules', 7, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)
end('$unfold_rules'/7):



'$gen_done'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 1)
	proceed

$2:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('c', 3, 2)
	unify_void(1)
	unify_x_variable(2)
	unify_void(1)
	get_structure(',', 2, 1)
	unify_x_ref(3)
	unify_x_variable(1)
	get_structure('=', 2, 3)
	unify_x_value(2)
	unify_constant('done')
	execute_predicate('$gen_done', 2)
end('$gen_done'/2):



'$gen_choices/5$0'/4:

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
	put_integer(0, 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('all', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(4, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	put_x_value(4, 2)
	execute_predicate('$gen_index', 3)
end('$gen_choices/5$0'/4):



'$gen_choices/5$1'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	get_y_level(5)
	call_predicate('member', 2, 6)
	cut(5)
	put_y_value(3, 0)
	get_y_value(4, 0)
	put_y_value(2, 0)
	get_structure('member', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$2:
	get_list(2)
	unify_x_value(0)
	unify_x_value(1)
	put_x_value(3, 1)
	get_structure(',', 2, 1)
	unify_x_value(0)
	unify_x_ref(0)
	get_structure('member', 2, 0)
	unify_x_value(4)
	unify_x_value(5)
	proceed
end('$gen_choices/5$1'/6):



'$gen_choices'/5:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(5, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 4)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(17)
	unify_y_variable(11)
	get_structure('c', 3, 0)
	unify_y_variable(16)
	unify_y_variable(7)
	unify_void(1)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(12, 3)
	get_y_variable(6, 4)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(8, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(9, 0)
	put_y_value(7, 1)
	put_y_variable(5, 2)
	call_predicate('$gen_not_eqs', 3, 17)
	pseudo_instr3(0, 36, 34, 35)
	pseudo_instr3(0, 24, 34, 35)
	pseudo_instr1(51, 24)
	put_y_value(4, 0)
	put_y_value(16, 1)
	put_y_value(3, 2)
	call_predicate('$gen_unif', 3, 16)
	put_y_value(15, 0)
	put_y_value(13, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	call_predicate('$gen_choices/5$0', 4, 15)
	put_x_variable(0, 1)
	get_structure('chr_lookup_hash', 3, 1)
	unify_y_value(14)
	unify_y_value(13)
	unify_y_value(10)
	put_y_value(12, 1)
	put_y_value(8, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(10, 5)
	call_predicate('$gen_choices/5$1', 6, 12)
	put_y_value(11, 0)
	put_y_value(10, 1)
	put_list(2)
	set_y_value(7)
	set_y_value(9)
	put_y_value(8, 3)
	put_y_value(0, 4)
	call_predicate('$gen_choices', 5, 8)
	put_y_value(6, 0)
	get_structure(',', 2, 0)
	unify_y_value(2)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('arg', 3, 0)
	unify_integer(3)
	unify_y_value(1)
	unify_y_value(7)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('var', 1, 0)
	unify_y_value(7)
	get_structure(',', 2, 1)
	unify_y_value(5)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('arg', 3, 0)
	unify_integer(1)
	unify_y_value(1)
	unify_y_value(4)
	get_structure(',', 2, 1)
	unify_y_value(3)
	unify_y_value(0)
	deallocate
	proceed
end('$gen_choices'/5):



'$gen_unif'/3:


$1:
	allocate(4)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_variable(0, 19)
	put_list(1)
	set_void(1)
	set_y_variable(1)
	call_predicate('=..', 2, 4)
	put_y_value(3, 0)
	put_list(1)
	set_void(1)
	set_y_value(0)
	call_predicate('=..', 2, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$gen_unif_aux', 3)
end('$gen_unif'/3):



'$gen_unif_aux'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('true', 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_structure(',', 2, 2)
	unify_x_variable(2)
	unify_y_variable(0)
	call_predicate('$gen_single_unif', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$gen_unif_aux', 3)
end('$gen_unif_aux'/3):



'$gen_single_unif'/3:

	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_value(0, 1)
	neck_cut
	put_constant('true', 0)
	get_x_value(2, 0)
	proceed

$2:
	pseudo_instr1(1, 1)
	neck_cut
	get_structure('==', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$3:
	pseudo_instr1(43, 1)
	neck_cut
	get_structure('==', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$4:
	get_structure(',', 2, 2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('freeze_term', 2, 2)
	unify_x_value(0)
	unify_x_variable(2)
	get_structure(',', 2, 3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('=', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	get_structure('thaw_term', 1, 4)
	unify_x_value(2)
	proceed
end('$gen_single_unif'/3):



'$gen_index/3$0/3$0'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr1(43, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$3:
	put_constant('all', 0)
	get_x_value(1, 0)
	proceed
end('$gen_index/3$0/3$0'/2):



'$gen_index/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	allocate(3)
	get_y_variable(1, 2)
	get_y_level(2)
	put_structure(2, 0)
	set_constant('==')
	set_x_value(3)
	set_y_variable(0)
	call_predicate('$conj_in', 2, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$gen_index/3$0/3$0', 2)

$2:
	put_constant('all', 0)
	get_x_value(2, 0)
	proceed
end('$gen_index/3$0'/3):



'$gen_index'/3:


$1:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_list(2)
	set_y_variable(0)
	set_void(1)
	put_list(1)
	set_void(1)
	set_x_value(2)
	call_predicate('=..', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$gen_index/3$0', 3)
end('$gen_index'/3):



'$conj_in'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_structure(',', 2, 1)
	unify_x_value(0)
	unify_void(1)
	neck_cut
	proceed

$3:
	get_structure(',', 2, 1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('$conj_in', 2)
end('$conj_in'/2):



'$gen_not_eqs'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_structure(',', 2, 2)
	unify_x_ref(4)
	unify_x_variable(2)
	get_structure('chr_not_eq', 2, 4)
	unify_x_value(3)
	unify_x_value(1)
	execute_predicate('$gen_not_eqs', 3)
end('$gen_not_eqs'/3):



'$unfold_rule_body/9$0'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_value(1)
	unify_void(1)
	neck_cut
	proceed

$2:
	put_constant('all', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_rule_body/9$0'/2):



'$unfold_rule_body/9$1'/5:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'not_added':$4])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$1:
	put_constant('not_added', 5)
	get_x_value(0, 5)
	neck_cut
	put_x_value(1, 0)
	get_structure('chr_add_constraint', 3, 0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	proceed

$2:
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_rule_body/9$1'/5):



'$unfold_rule_body/9$2'/7:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(7, $1)
	trust($2)

$5:
	try(7, $1)
	trust($2)

$1:
	put_constant('[]', 6)
	get_x_value(0, 6)
	neck_cut
	put_x_value(1, 0)
	get_list(0)
	unify_x_value(2)
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':-', 2, 0)
	unify_x_value(3)
	unify_x_value(4)
	put_constant('added', 0)
	get_x_value(5, 0)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_x_value(2)
	unify_constant('[]')
	get_x_value(5, 6)
	proceed
end('$unfold_rule_body/9$2'/7):



'$unfold_rule_body/9$3'/5:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'no_nonvar':$4])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$1:
	put_constant('no_nonvar', 5)
	get_x_value(0, 5)
	neck_cut
	put_x_variable(0, 5)
	get_structure(':-', 2, 5)
	unify_x_value(1)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_constant('!')
	get_structure('nonvar', 1, 1)
	unify_x_value(2)
	put_x_value(3, 1)
	get_list(1)
	unify_x_value(0)
	unify_x_value(4)
	proceed

$2:
	get_x_value(3, 4)
	proceed
end('$unfold_rule_body/9$3'/5):



'$unfold_rule_body/9$4'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_value(1)
	unify_void(1)
	neck_cut
	proceed

$2:
	put_constant('all', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_rule_body/9$4'/2):



'$unfold_rule_body/9$5'/8:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'not_added':$4])

$4:
	try(8, $1)
	trust($2)

$5:
	try(8, $1)
	trust($2)

$1:
	put_constant('not_added', 8)
	get_x_value(0, 8)
	neck_cut
	put_x_value(1, 0)
	get_structure('chr_add_constraint', 3, 0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	put_x_value(5, 0)
	get_structure(':-', 2, 0)
	unify_x_value(6)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_value(1)
	unify_x_value(7)
	proceed

$2:
	put_constant('true', 0)
	get_x_value(1, 0)
	put_x_value(5, 0)
	get_structure(':-', 2, 0)
	unify_x_value(6)
	unify_x_value(7)
	proceed
end('$unfold_rule_body/9$5'/8):



'$unfold_rule_body/9$6'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	put_constant('[]', 4)
	get_x_value(0, 4)
	neck_cut
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('arg', 3, 0)
	unify_integer(5)
	unify_x_value(2)
	unify_x_variable(0)
	get_structure('check_and_update_applied', 2, 1)
	unify_x_ref(1)
	unify_x_value(0)
	get_structure('a', 2, 1)
	unify_x_value(3)
	unify_constant('[]')
	proceed

$2:
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_rule_body/9$6'/4):



'$unfold_rule_body/9$7'/6:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$1:
	put_constant('[]', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr2(69, 2, 0)
	put_x_variable(2, 6)
	get_list(6)
	unify_x_value(3)
	unify_x_ref(3)
	get_list(3)
	unify_x_value(4)
	unify_x_ref(3)
	get_list(3)
	unify_x_value(0)
	unify_constant('[]')
	put_constant('__', 0)
	pseudo_instr3(28, 2, 0, 1)
	get_x_variable(2, 1)
	put_y_variable(0, 0)
	put_list(1)
	set_x_value(2)
	set_x_value(5)
	call_predicate('=..', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$unfold_rule_body/9$7'/6):



'$unfold_rule_body/9$8'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_value(1)
	unify_void(1)
	neck_cut
	proceed

$2:
	put_constant('all', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_rule_body/9$8'/2):



'$unfold_rule_body/9$9'/5:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'no_nonvar':$4])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$1:
	put_constant('no_nonvar', 5)
	get_x_value(0, 5)
	neck_cut
	put_x_variable(0, 5)
	get_structure(':-', 2, 5)
	unify_x_value(1)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_constant('!')
	get_structure('nonvar', 1, 1)
	unify_x_value(2)
	put_x_value(3, 1)
	get_list(1)
	unify_x_value(0)
	unify_x_value(4)
	proceed

$2:
	get_x_value(3, 4)
	proceed
end('$unfold_rule_body/9$9'/5):



'$unfold_rule_body/9$10'/5:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'not_added':$4])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$1:
	put_constant('not_added', 5)
	get_x_value(0, 5)
	neck_cut
	put_x_value(1, 0)
	get_structure('chr_add_constraint', 3, 0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	proceed

$2:
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_rule_body/9$10'/5):



'$unfold_rule_body/9$11'/9:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(9, $1)
	trust($2)

$5:
	try(9, $1)
	trust($2)

$1:
	put_constant('[]', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	allocate(3)
	get_y_variable(2, 1)
	get_x_variable(0, 5)
	get_y_variable(1, 8)
	pseudo_instr2(69, 2, 1)
	put_x_variable(5, 8)
	get_list(8)
	unify_x_value(3)
	unify_x_ref(3)
	get_list(3)
	unify_x_value(4)
	unify_x_ref(3)
	get_list(3)
	unify_x_value(1)
	unify_constant('[]')
	put_constant('__', 1)
	pseudo_instr3(28, 5, 1, 2)
	get_y_variable(0, 2)
	put_list(2)
	set_x_value(7)
	set_constant('[]')
	put_list(1)
	set_x_value(6)
	set_x_value(2)
	put_y_value(1, 2)
	call_predicate('append', 3, 3)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(0)
	set_y_value(1)
	deallocate
	execute_predicate('=..', 2)
end('$unfold_rule_body/9$11'/9):



'$unfold_rule_body/9$12'/13:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'true':$4])

$4:
	try(13, $1)
	trust($2)

$5:
	try(13, $1)
	trust($2)

$1:
	put_constant('true', 12)
	get_x_value(0, 12)
	neck_cut
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_value(2)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_value(3)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('chr_lookup_hash', 3, 0)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(6)
	get_structure(',', 2, 1)
	unify_x_value(7)
	unify_x_value(8)
	put_x_value(9, 0)
	get_list(0)
	unify_x_value(10)
	unify_x_value(11)
	proceed

$2:
	allocate(5)
	get_y_variable(4, 9)
	get_y_variable(3, 10)
	get_y_variable(2, 11)
	get_y_variable(1, 12)
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_value(3)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_constant('!')
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_value(2)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('chr_lookup_hash', 3, 0)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(6)
	get_structure(',', 2, 1)
	unify_x_value(7)
	unify_x_value(8)
	put_structure(2, 0)
	set_constant(',')
	set_x_value(2)
	set_x_value(8)
	put_y_variable(0, 1)
	call_predicate('$flatten_ands_true', 2, 5)
	put_y_value(4, 0)
	get_list(0)
	unify_y_value(3)
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_y_value(2)
	get_structure(':-', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed
end('$unfold_rule_body/9$12'/13):



'$unfold_rule_body'/9:

	switch_on_term(0, $7, 'fail', 'fail', $4, 'fail', 'fail')

$4:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$5, 'chr_rule_data'/9:$6])

$5:
	try(9, $1)
	retry($2)
	trust($3)

$6:
	try(9, $1)
	retry($2)
	trust($3)

$7:
	try(9, $1)
	retry($2)
	trust($3)

$1:
	get_structure('chr_rule_data', 9, 0)
	unify_void(2)
	unify_constant('remove')
	allocate(27)
	unify_y_variable(14)
	unify_void(1)
	unify_y_variable(12)
	unify_y_variable(10)
	unify_y_variable(9)
	unify_y_variable(8)
	get_y_variable(21, 1)
	get_y_variable(17, 5)
	get_y_variable(20, 6)
	get_y_variable(19, 7)
	get_y_variable(16, 8)
	neck_cut
	put_x_variable(1, 5)
	get_list(5)
	unify_x_value(2)
	unify_x_ref(5)
	get_list(5)
	unify_x_value(3)
	unify_x_ref(5)
	get_list(5)
	unify_x_value(4)
	unify_constant('[]')
	put_constant('__', 4)
	pseudo_instr3(28, 1, 4, 0)
	get_y_variable(26, 0)
	put_y_variable(13, 19)
	pseudo_instr3(0, 33, 2, 3)
	put_y_variable(25, 19)
	put_y_variable(23, 19)
	put_y_variable(22, 19)
	put_y_variable(18, 19)
	put_y_variable(15, 19)
	put_y_variable(11, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(13, 0)
	put_list(1)
	set_x_value(2)
	set_y_variable(24)
	call_predicate('=..', 2, 27)
	put_y_value(24, 0)
	put_list(2)
	set_y_value(23)
	set_constant('[]')
	put_list(1)
	set_y_value(11)
	set_x_value(2)
	put_y_value(25, 2)
	call_predicate('append', 3, 27)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(26)
	set_y_value(25)
	call_predicate('=..', 2, 25)
	put_y_value(24, 0)
	put_y_value(22, 1)
	call_predicate('$unfold_rule_body/9$0', 2, 24)
	put_y_value(20, 0)
	put_y_value(18, 1)
	put_y_value(11, 2)
	put_y_value(22, 3)
	put_y_value(23, 4)
	call_predicate('$unfold_rule_body/9$1', 5, 22)
	put_y_value(21, 0)
	put_y_value(15, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	put_y_value(18, 4)
	put_y_value(19, 5)
	put_y_value(20, 6)
	call_predicate('$unfold_rule_body/9$2', 7, 18)
	put_y_value(16, 0)
	put_y_value(2, 1)
	put_y_value(11, 2)
	put_y_value(17, 3)
	put_y_value(15, 4)
	call_predicate('$unfold_rule_body/9$3', 5, 15)
	put_y_value(14, 0)
	get_structure('c', 3, 0)
	unify_x_variable(1)
	unify_y_value(11)
	unify_void(1)
	pseudo_instr1(51, 33)
	put_y_value(13, 0)
	put_y_value(7, 2)
	call_predicate('$gen_unif', 3, 13)
	put_y_value(12, 0)
	put_x_variable(1, 1)
	put_list(2)
	set_y_value(11)
	set_constant('[]')
	put_y_value(6, 4)
	put_constant('[]', 3)
	call_predicate('$gen_choices', 5, 11)
	put_y_value(10, 0)
	put_y_value(5, 1)
	call_predicate('$gen_done', 2, 10)
	put_y_value(9, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('$gen_freeze_thaw', 3, 10)
	put_x_variable(0, 1)
	get_structure(',', 2, 1)
	unify_y_value(7)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(6)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(4)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(9)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(3)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_constant('!')
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(5)
	unify_y_value(8)
	put_y_value(0, 1)
	call_predicate('$flatten_ands_true', 2, 3)
	put_y_value(1, 0)
	get_structure(':-', 2, 0)
	unify_y_value(2)
	unify_y_value(0)
	deallocate
	proceed

$2:
	get_constant('added', 7)
	get_structure('chr_rule_data', 9, 0)
	unify_void(3)
	unify_x_variable(0)
	unify_void(1)
	unify_constant('[]')
	allocate(27)
	unify_y_variable(21)
	unify_y_variable(12)
	unify_y_variable(11)
	get_y_variable(19, 1)
	get_y_variable(18, 2)
	get_y_variable(17, 3)
	get_y_variable(16, 4)
	get_list(5)
	unify_y_variable(2)
	unify_x_ref(1)
	get_list(1)
	unify_y_variable(24)
	unify_constant('[]')
	get_y_variable(23, 6)
	get_structure('c', 3, 0)
	unify_y_variable(14)
	unify_y_variable(10)
	unify_void(1)
	put_y_variable(26, 19)
	put_y_variable(25, 19)
	put_y_variable(22, 19)
	put_y_variable(20, 19)
	put_y_variable(15, 19)
	put_y_variable(13, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(21, 0)
	put_y_variable(9, 1)
	call_predicate('$gen_done', 2, 27)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(18)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(17)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(16)
	unify_constant('[]')
	put_constant('__', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_value(26, 0)
	pseudo_instr3(0, 33, 38, 37)
	put_y_value(13, 0)
	put_list(1)
	set_y_value(18)
	set_y_value(25)
	call_predicate('=..', 2, 27)
	put_y_value(25, 0)
	put_list(2)
	set_y_value(20)
	set_constant('[]')
	put_list(1)
	set_y_value(10)
	set_x_value(2)
	put_y_value(15, 2)
	call_predicate('append', 3, 27)
	put_y_value(1, 0)
	put_list(1)
	set_y_value(26)
	set_y_value(15)
	call_predicate('=..', 2, 26)
	put_y_value(25, 0)
	put_y_value(22, 1)
	call_predicate('$unfold_rule_body/9$4', 2, 25)
	put_y_value(23, 0)
	put_y_value(8, 1)
	put_y_value(10, 2)
	put_y_value(22, 3)
	put_y_value(20, 4)
	put_y_value(24, 5)
	put_y_value(1, 6)
	put_y_value(7, 7)
	call_predicate('$unfold_rule_body/9$5', 8, 22)
	put_y_value(21, 0)
	put_y_value(6, 1)
	put_y_value(20, 2)
	put_y_value(16, 3)
	call_predicate('$unfold_rule_body/9$6', 4, 20)
	put_y_value(19, 0)
	put_y_value(7, 1)
	put_y_value(16, 2)
	put_y_value(18, 3)
	put_y_value(17, 4)
	put_y_value(15, 5)
	call_predicate('$unfold_rule_body/9$7', 6, 15)
	pseudo_instr1(51, 33)
	put_y_value(13, 0)
	put_y_value(14, 1)
	put_y_value(5, 2)
	call_predicate('$gen_unif', 3, 13)
	put_y_value(12, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('$gen_freeze_thaw', 3, 13)
	put_x_variable(0, 1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('var', 1, 1)
	unify_y_value(10)
	get_structure(',', 2, 2)
	unify_y_value(5)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(4)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(12)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(3)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(6)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_constant('!')
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(8)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(9)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(11)
	unify_y_value(7)
	put_y_value(0, 1)
	call_predicate('$flatten_ands_true', 2, 3)
	put_y_value(2, 0)
	get_structure(':-', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$3:
	get_constant('added', 7)
	get_structure('chr_rule_data', 9, 0)
	unify_void(3)
	unify_x_variable(0)
	unify_void(1)
	allocate(37)
	unify_y_variable(8)
	unify_y_variable(7)
	unify_y_variable(6)
	unify_y_variable(5)
	get_y_variable(27, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(31, 5)
	get_y_variable(29, 6)
	get_y_variable(30, 8)
	get_structure('c', 3, 0)
	unify_y_variable(35)
	unify_y_variable(26)
	unify_void(1)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(2)
	unify_constant('[]')
	put_constant('__', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_variable(36, 0)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(2)
	unify_x_ref(2)
	get_list(2)
	unify_integer(0)
	unify_constant('[]')
	put_constant('__', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_variable(23, 0)
	put_y_variable(34, 19)
	pseudo_instr3(0, 54, 24, 23)
	put_y_variable(33, 19)
	put_y_variable(32, 19)
	put_y_variable(28, 19)
	put_y_variable(22, 19)
	put_y_variable(21, 19)
	put_y_variable(20, 19)
	put_y_variable(19, 19)
	put_y_variable(18, 19)
	put_y_variable(17, 19)
	put_y_variable(16, 19)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(0, 19)
	put_y_variable(1, 0)
	put_list(2)
	set_y_variable(25)
	set_constant('[]')
	put_list(1)
	set_y_value(26)
	set_x_value(2)
	put_y_variable(24, 2)
	call_predicate('append', 3, 37)
	put_y_value(1, 0)
	put_list(1)
	set_y_value(25)
	set_constant('[]')
	put_list(2)
	set_y_value(26)
	set_constant('[]')
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_constant('[]')
	set_x_value(3)
	put_y_value(22, 2)
	call_predicate('append', 3, 37)
	put_y_value(11, 0)
	put_list(1)
	set_y_value(36)
	set_y_value(24)
	call_predicate('=..', 2, 36)
	put_y_value(34, 0)
	put_list(1)
	set_y_value(4)
	set_y_value(1)
	call_predicate('=..', 2, 36)
	put_y_value(1, 0)
	put_y_value(28, 1)
	call_predicate('$unfold_rule_body/9$8', 2, 36)
	pseudo_instr1(51, 54)
	put_y_value(34, 0)
	put_y_value(35, 1)
	put_y_value(21, 2)
	call_predicate('$gen_unif', 3, 34)
	put_y_value(8, 0)
	get_list(0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('c', 3, 0)
	unify_x_variable(1)
	unify_void(2)
	put_x_variable(0, 0)
	pseudo_instr3(0, 1, 40, 0)
	pseudo_instr3(0, 53, 40, 0)
	pseudo_instr1(51, 53)
	put_y_value(33, 0)
	put_y_value(32, 2)
	call_predicate('$gen_unif', 3, 34)
	put_y_value(33, 0)
	put_y_value(32, 1)
	put_y_value(19, 2)
	call_predicate('$gen_index', 3, 32)
	put_y_value(21, 0)
	put_y_value(18, 1)
	call_predicate('$flatten_ands_true', 2, 32)
	put_y_value(30, 0)
	put_y_value(11, 1)
	put_y_value(26, 2)
	put_y_value(31, 3)
	put_y_value(17, 4)
	call_predicate('$unfold_rule_body/9$9', 5, 30)
	put_y_value(29, 0)
	put_y_value(16, 1)
	put_y_value(26, 2)
	put_y_value(28, 3)
	put_y_value(25, 4)
	call_predicate('$unfold_rule_body/9$10', 5, 28)
	put_y_value(27, 0)
	put_y_value(15, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(1, 5)
	put_y_value(26, 6)
	put_y_value(25, 7)
	put_y_value(24, 8)
	call_predicate('$unfold_rule_body/9$11', 9, 24)
	put_y_value(14, 0)
	put_list(2)
	set_y_value(13)
	set_y_value(22)
	put_list(1)
	set_y_value(23)
	set_x_value(2)
	call_predicate('=..', 2, 22)
	put_y_value(18, 0)
	put_y_value(12, 1)
	put_y_value(16, 2)
	put_y_value(21, 3)
	put_y_value(20, 4)
	put_y_value(19, 5)
	put_y_value(13, 6)
	put_y_value(14, 7)
	put_y_value(15, 8)
	put_y_value(17, 9)
	put_y_value(10, 10)
	put_y_value(0, 11)
	put_y_value(11, 12)
	call_predicate('$unfold_rule_body/9$12', 13, 13)
	put_y_value(12, 0)
	put_y_value(9, 1)
	call_predicate('$flatten_ands_true', 2, 12)
	put_y_value(10, 0)
	get_structure(':-', 2, 0)
	unify_y_value(11)
	unify_y_value(9)
	put_y_value(8, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(7, 5)
	put_y_value(6, 6)
	put_y_value(5, 7)
	put_y_value(1, 8)
	put_y_value(0, 9)
	put_integer(0, 4)
	deallocate
	execute_predicate('$unfold_down', 10)
end('$unfold_rule_body'/9):



'$gen_freeze_thaw/3$0'/2:

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
	unify_x_variable(2)
	unify_x_variable(0)
	pseudo_instr1(41, 2)
	neck_cut
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$gen_freeze_thaw/3$0', 2)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$gen_freeze_thaw/3$0', 2)
end('$gen_freeze_thaw/3$0'/2):



'$gen_freeze_thaw'/3:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	pseudo_instr2(67, 25, 0)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('$gen_freeze_thaw/3$0', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 3)
	put_constant('[]', 2)
	call_predicate('$get_goal_vars', 4, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	call_predicate('remove_duplicates', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$gen_freeze_thaw_goals', 3)
end('$gen_freeze_thaw'/3):



'$get_goal_vars'/4:

	switch_on_term(0, $11, $10, $10, $5, $10, $8)

$5:
	switch_on_structure(0, 4, ['$default':$10, '$'/0:$6, ','/2:$7])

$6:
	try(4, $2)
	retry($3)
	trust($4)

$7:
	try(4, $2)
	retry($3)
	trust($4)

$8:
	switch_on_constant(0, 4, ['$default':$10, 'true':$9])

$9:
	try(4, $1)
	retry($3)
	trust($4)

$10:
	try(4, $3)
	trust($4)

$11:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('true', 0)
	get_x_value(2, 3)
	neck_cut
	proceed

$2:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 3)
	call_predicate('$get_goal_vars', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$get_goal_vars', 4)

$3:
	allocate(6)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_level(5)
	put_y_variable(0, 19)
	put_y_variable(3, 1)
	call_predicate('$guard_info', 2, 6)
	cut(5)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	call_predicate('intersect_list', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('append', 3)

$4:
	allocate(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	pseudo_instr2(67, 0, 2)
	get_x_variable(0, 2)
	put_y_variable(0, 2)
	call_predicate('intersect_list', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('append', 3)
end('$get_goal_vars'/4):



'$gen_freeze_thaw_goals'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 1)
	get_constant('true', 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure('freeze_term', 1, 4)
	unify_x_value(3)
	get_structure(',', 2, 2)
	unify_x_ref(4)
	unify_x_variable(2)
	get_structure('thaw_term', 1, 4)
	unify_x_value(3)
	execute_predicate('$gen_freeze_thaw_goals', 3)
end('$gen_freeze_thaw_goals'/3):



'$guard_info'/2:

	switch_on_term(0, $11, 'fail', 'fail', $8, 'fail', 'fail')

$8:
	switch_on_structure(0, 16, ['$default':'fail', '$'/0:$9, 'nonvar'/1:$10, 'var'/1:$2, 'atom'/1:$3, 'atomic'/1:$4, 'number'/1:$5, 'integer'/1:$6])

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
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_constant('[]', 1)
	get_structure('nonvar', 1, 0)
	unify_void(1)
	proceed

$2:
	get_constant('[]', 1)
	get_structure('var', 1, 0)
	unify_void(1)
	proceed

$3:
	get_constant('[]', 1)
	get_structure('atom', 1, 0)
	unify_void(1)
	proceed

$4:
	get_constant('[]', 1)
	get_structure('atomic', 1, 0)
	unify_void(1)
	proceed

$5:
	get_constant('[]', 1)
	get_structure('number', 1, 0)
	unify_void(1)
	proceed

$6:
	get_constant('[]', 1)
	get_structure('integer', 1, 0)
	unify_void(1)
	proceed

$7:
	get_constant('[]', 1)
	get_structure('nonvar', 1, 0)
	unify_void(1)
	proceed
end('$guard_info'/2):



'$unfold_down/10$0'/6:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$1:
	put_constant('[]', 6)
	get_x_value(0, 6)
	neck_cut
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('arg', 3, 0)
	unify_integer(5)
	unify_x_value(2)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('arg', 3, 1)
	unify_integer(4)
	unify_x_value(3)
	unify_x_variable(1)
	get_structure('check_and_update_applied', 2, 2)
	unify_x_ref(2)
	unify_x_value(0)
	get_structure('a', 2, 2)
	unify_x_value(4)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_value(5)
	proceed

$2:
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed
end('$unfold_down/10$0'/6):



'$unfold_down'/10:

	switch_on_term(0, $3, 'fail', $3, 'fail', 'fail', 'fail')

$3:
	try(10, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	allocate(27)
	get_y_variable(19, 3)
	get_y_variable(18, 5)
	get_y_variable(15, 6)
	get_y_variable(14, 7)
	get_y_variable(21, 8)
	get_list(9)
	unify_y_variable(26)
	unify_x_ref(3)
	get_list(3)
	unify_y_variable(4)
	unify_x_ref(3)
	get_list(3)
	unify_y_variable(2)
	unify_constant('[]')
	neck_cut
	put_x_variable(5, 6)
	get_list(6)
	unify_x_value(1)
	unify_x_ref(1)
	get_list(1)
	unify_x_value(2)
	unify_x_ref(1)
	get_list(1)
	unify_y_value(19)
	unify_x_ref(1)
	get_list(1)
	unify_x_value(4)
	unify_constant('[]')
	put_constant('__', 1)
	pseudo_instr3(28, 5, 1, 3)
	get_y_variable(24, 3)
	get_structure('c', 3, 0)
	unify_y_variable(20)
	unify_y_variable(13)
	unify_void(1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 40, 0, 1)
	put_y_variable(12, 19)
	pseudo_instr3(0, 32, 0, 1)
	put_y_variable(23, 19)
	put_y_variable(22, 19)
	put_y_variable(16, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(21, 0)
	put_list(1)
	set_y_variable(17)
	set_constant('[]')
	put_list(2)
	set_void(1)
	set_x_value(1)
	put_list(1)
	set_void(1)
	set_x_value(2)
	put_y_variable(25, 2)
	call_predicate('append', 3, 27)
	put_y_value(26, 0)
	put_list(2)
	set_constant('[]')
	set_y_value(25)
	put_list(1)
	set_y_value(24)
	set_x_value(2)
	call_predicate('=..', 2, 25)
	put_y_value(21, 0)
	put_list(1)
	set_y_value(17)
	set_constant('[]')
	put_list(2)
	set_y_value(11)
	set_x_value(1)
	put_list(1)
	set_y_value(16)
	set_x_value(2)
	put_y_value(23, 2)
	call_predicate('append', 3, 25)
	put_y_value(1, 0)
	put_list(1)
	set_y_value(10)
	set_y_value(22)
	put_list(2)
	set_x_value(1)
	set_y_value(23)
	put_list(1)
	set_y_value(24)
	set_x_value(2)
	call_predicate('=..', 2, 25)
	put_y_value(0, 0)
	put_list(2)
	set_y_value(22)
	set_y_value(23)
	put_list(1)
	set_y_value(24)
	set_x_value(2)
	call_predicate('=..', 2, 22)
	pseudo_instr1(52, 40)
	pseudo_instr1(51, 32)
	pseudo_instr1(51, 41)
	put_y_value(12, 0)
	put_y_value(20, 1)
	put_y_value(9, 2)
	call_predicate('$gen_unif', 3, 20)
	put_y_value(18, 0)
	put_y_value(8, 1)
	call_predicate('$gen_done', 2, 20)
	put_y_value(18, 0)
	put_y_value(7, 1)
	put_y_value(17, 2)
	put_y_value(10, 3)
	put_y_value(19, 4)
	put_y_value(16, 5)
	call_predicate('$unfold_down/10$0', 6, 16)
	put_y_value(15, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	call_predicate('$gen_freeze_thaw', 3, 16)
	put_x_variable(0, 1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('arg', 3, 1)
	unify_integer(3)
	unify_y_value(10)
	unify_y_value(13)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('var', 1, 1)
	unify_y_value(13)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('chr_not_in', 2, 1)
	unify_y_value(13)
	unify_y_value(11)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('arg', 3, 1)
	unify_integer(1)
	unify_y_value(10)
	unify_y_value(12)
	get_structure(',', 2, 2)
	unify_y_value(9)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(6)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(15)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(5)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(7)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_constant('!')
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(8)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(14)
	unify_y_value(0)
	put_y_value(3, 1)
	call_predicate('$flatten_ands_true', 2, 5)
	put_y_value(4, 0)
	get_structure(':-', 2, 0)
	unify_y_value(1)
	unify_y_value(3)
	put_y_value(2, 0)
	get_structure(':-', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(38)
	unify_y_variable(8)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(34, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	get_y_variable(26, 8)
	get_y_variable(10, 9)
	get_structure('c', 3, 0)
	unify_y_variable(25)
	unify_void(2)
	put_y_variable(24, 19)
	put_x_variable(0, 0)
	pseudo_instr3(0, 45, 44, 0)
	put_y_variable(23, 19)
	pseudo_instr3(0, 43, 44, 0)
	put_y_variable(36, 19)
	put_y_variable(35, 19)
	put_y_variable(33, 19)
	put_y_variable(32, 19)
	put_y_variable(31, 19)
	put_y_variable(30, 19)
	put_y_variable(29, 19)
	put_y_variable(28, 19)
	put_y_variable(27, 19)
	put_y_variable(22, 19)
	put_y_variable(21, 19)
	put_y_variable(20, 19)
	put_y_variable(19, 19)
	put_y_variable(18, 19)
	put_y_variable(17, 19)
	put_y_variable(16, 19)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(9, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(23, 0)
	put_list(1)
	set_void(1)
	set_y_variable(37)
	call_predicate('=..', 2, 38)
	put_y_value(26, 0)
	put_y_value(37, 1)
	put_y_value(1, 2)
	call_predicate('append', 3, 37)
	put_y_value(8, 0)
	get_list(0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('c', 3, 0)
	unify_x_variable(1)
	unify_void(2)
	put_x_variable(0, 0)
	put_x_variable(2, 2)
	pseudo_instr3(0, 1, 0, 2)
	pseudo_instr3(0, 56, 0, 2)
	pseudo_instr1(52, 1)
	pseudo_instr1(51, 56)
	pseudo_instr1(51, 46)
	put_y_value(36, 0)
	put_y_value(35, 2)
	call_predicate('$gen_unif', 3, 37)
	put_y_value(36, 0)
	put_y_value(35, 1)
	put_y_value(22, 2)
	call_predicate('$gen_index', 3, 35)
	pseudo_instr2(69, 54, 0)
	get_y_value(0, 0)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(7)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(5)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(34)
	unify_constant('[]')
	put_constant('__', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_value(33, 0)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(7)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(5)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(0)
	unify_constant('[]')
	put_constant('__', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_value(28, 0)
	put_y_value(26, 0)
	put_list(1)
	set_y_value(29)
	set_constant('[]')
	put_list(2)
	set_y_value(21)
	set_x_value(1)
	put_list(1)
	set_y_value(30)
	set_x_value(2)
	put_y_value(32, 2)
	call_predicate('append', 3, 34)
	put_y_value(9, 0)
	put_list(2)
	set_constant('[]')
	set_y_value(32)
	put_list(1)
	set_y_value(33)
	set_x_value(2)
	call_predicate('=..', 2, 34)
	put_y_value(12, 0)
	put_list(1)
	set_y_value(20)
	set_y_value(31)
	put_list(2)
	set_x_value(1)
	set_y_value(32)
	put_list(1)
	set_y_value(33)
	set_x_value(2)
	call_predicate('=..', 2, 34)
	put_y_value(19, 0)
	put_list(2)
	set_y_value(31)
	set_y_value(32)
	put_list(1)
	set_y_value(33)
	set_x_value(2)
	call_predicate('=..', 2, 34)
	put_y_value(11, 0)
	put_list(2)
	set_y_value(31)
	set_y_value(32)
	put_list(1)
	set_y_value(33)
	set_x_value(2)
	call_predicate('=..', 2, 31)
	put_y_value(1, 0)
	put_list(1)
	set_y_value(29)
	set_constant('[]')
	put_list(2)
	set_y_value(17)
	set_y_value(21)
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(2)
	set_y_value(18)
	set_y_value(30)
	put_list(1)
	set_x_value(2)
	set_x_value(3)
	put_y_value(27, 2)
	call_predicate('append', 3, 29)
	put_y_value(16, 0)
	put_list(2)
	set_y_value(15)
	set_y_value(27)
	put_list(1)
	set_y_value(28)
	set_x_value(2)
	call_predicate('=..', 2, 27)
	pseudo_instr1(52, 45)
	pseudo_instr1(51, 43)
	pseudo_instr1(51, 46)
	put_y_value(23, 0)
	put_y_value(25, 1)
	put_y_value(14, 2)
	call_predicate('$gen_unif', 3, 25)
	put_x_variable(0, 1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('arg', 3, 1)
	unify_integer(3)
	unify_y_value(20)
	unify_y_value(17)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('var', 1, 1)
	unify_y_value(17)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('chr_not_in', 2, 1)
	unify_y_value(17)
	unify_y_value(21)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('arg', 3, 1)
	unify_integer(1)
	unify_y_value(20)
	unify_y_value(23)
	get_structure(',', 2, 2)
	unify_y_value(14)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_constant('!')
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('chr_lookup_hash', 3, 1)
	unify_y_value(24)
	unify_y_value(22)
	unify_y_value(15)
	get_structure(',', 2, 2)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('arg', 3, 1)
	unify_integer(4)
	unify_y_value(20)
	unify_y_value(18)
	get_structure(',', 2, 2)
	unify_y_value(16)
	unify_y_value(19)
	put_y_value(13, 1)
	call_predicate('$flatten_ands_true', 2, 14)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(12)
	unify_y_value(13)
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(12)
	unify_y_value(11)
	put_y_value(10, 2)
	get_list(2)
	unify_y_value(9)
	unify_x_ref(2)
	get_list(2)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_variable(9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(0, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	put_y_value(1, 8)
	deallocate
	execute_predicate('$unfold_down', 10)
end('$unfold_down'/10):



'$flatten_ands_true'/2:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ','/2:$5])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$6:
	try(2, $1)
	trust($2)

$1:
	get_structure(',', 2, 0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 1)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$flatten_ands_true', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$flatten_ands_true', 3)

$2:
	get_x_value(0, 1)
	proceed
end('$flatten_ands_true'/2):



'$flatten_ands_true'/3:

	switch_on_term(0, $11, $10, $10, $5, $10, $8)

$5:
	switch_on_structure(0, 4, ['$default':$10, '$'/0:$6, ','/2:$7])

$6:
	try(3, $1)
	retry($3)
	trust($4)

$7:
	try(3, $1)
	retry($3)
	trust($4)

$8:
	switch_on_constant(0, 4, ['$default':$10, 'true':$9])

$9:
	try(3, $2)
	retry($3)
	trust($4)

$10:
	try(3, $3)
	trust($4)

$11:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure(',', 2, 0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 2)
	call_predicate('$flatten_ands_true', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$flatten_ands_true', 3)

$2:
	get_constant('true', 0)
	get_x_value(1, 2)
	neck_cut
	proceed

$3:
	get_constant('true', 1)
	get_x_value(0, 2)
	neck_cut
	proceed

$4:
	get_structure(',', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed
end('$flatten_ands_true'/3):



'$remove_chr_repeat_rules'/2:


$1:
	execute_predicate('$remove_chr_repeat_rules_1', 2)
end('$remove_chr_repeat_rules'/2):



'$remove_chr_repeat_rules_1'/2:

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
	unify_x_variable(2)
	get_list(1)
	unify_x_value(0)
	allocate(2)
	unify_y_variable(1)
	put_x_value(2, 1)
	put_y_variable(0, 2)
	call_predicate('$remove_chr_repeat', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$remove_chr_repeat_rules_1', 2)
end('$remove_chr_repeat_rules_1'/2):



'$remove_chr_repeat'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	proceed

$2:
	allocate(4)
	get_y_variable(2, 0)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('$is_chr_repeat', 2, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$remove_chr_repeat', 3)

$3:
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('$remove_chr_repeat', 3)
end('$remove_chr_repeat'/3):



'$is_chr_repeat'/2:


$1:
	get_structure('chr_rule_data', 9, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_void(1)
	allocate(8)
	unify_y_variable(7)
	unify_void(1)
	unify_y_variable(6)
	unify_void(1)
	unify_y_variable(5)
	unify_y_variable(4)
	get_structure('chr_rule_data', 9, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_void(1)
	unify_y_variable(3)
	unify_void(1)
	unify_y_variable(2)
	unify_void(1)
	unify_y_variable(1)
	unify_y_variable(0)
	put_y_value(7, 0)
	put_list(1)
	set_y_value(7)
	set_y_value(6)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_list(5)
	set_y_value(3)
	set_y_value(2)
	put_y_value(1, 6)
	put_y_value(0, 7)
	call_predicate('$is_char_repeat_1', 8, 8)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(3)
	set_y_value(2)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_y_value(7, 4)
	put_list(5)
	set_y_value(7)
	set_y_value(6)
	put_y_value(5, 6)
	put_y_value(4, 7)
	deallocate
	execute_predicate('$is_char_repeat_1', 8)
end('$is_chr_repeat'/2):



'$is_char_repeat_1/8$0/8$0'/8:

	try(8, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_x_variable(1, 6)
	get_y_variable(3, 7)
	put_x_variable(2, 3)
	get_structure(',', 2, 3)
	unify_x_value(0)
	unify_x_ref(3)
	get_structure(',', 2, 3)
	unify_y_value(4)
	unify_x_ref(3)
	get_structure(',', 2, 3)
	unify_y_value(2)
	unify_y_value(1)
	pseudo_instr1(51, 2)
	get_x_value(4, 5)
	get_y_level(0)
	call_predicate('$chr_perm', 2, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	call_predicate('$chr_equal_goals', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$chr_equal_goals', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$is_char_repeat_1/8$0/8$0'/8):



'$is_char_repeat_1/8$0'/8:

	try(8, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$is_char_repeat_1/8$0/8$0', 8, 1)
	cut(0)
	fail

$2:
	proceed
end('$is_char_repeat_1/8$0'/8):



'$is_char_repeat_1'/8:


$1:
	get_x_variable(8, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(9, 4)
	get_x_variable(10, 5)
	get_x_variable(11, 6)
	get_x_variable(3, 7)
	put_x_value(8, 4)
	put_x_value(9, 5)
	put_x_value(10, 6)
	put_x_value(11, 7)
	execute_predicate('$is_char_repeat_1/8$0', 8)
end('$is_char_repeat_1'/8):



'$chr_perm'/2:

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
	put_y_variable(0, 2)
	call_predicate('delete', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$chr_perm', 2)
end('$chr_perm'/2):



'$chr_equal_goals'/2:

	switch_on_term(0, $8, $2, $2, $4, $2, $2)

$4:
	switch_on_structure(0, 8, ['$default':$2, '$'/0:$5, ','/2:$6, '='/2:$7])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	trust($2)

$7:
	try(2, $2)
	trust($3)

$8:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_structure(',', 2, 1)
	unify_x_variable(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$chr_equal_goals', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$chr_equal_goals', 2)

$2:
	get_x_value(0, 1)
	neck_cut
	proceed

$3:
	get_structure('=', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('=', 2, 1)
	unify_x_value(2)
	unify_x_value(0)
	proceed
end('$chr_equal_goals'/2):



'$compile_a_rule'/3:

	switch_on_term(0, $9, 'fail', 'fail', $6, 'fail', 'fail')

$6:
	switch_on_structure(0, 16, ['$default':'fail', '$'/0:$7, '@'/2:$1, 'pragma'/2:$8, '<=>'/2:$4, '==>'/2:$5])

$7:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(3, $2)
	trust($3)

$9:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_structure('@', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$compile_a_rule', 3)

$2:
	get_structure('pragma', 2, 0)
	unify_x_variable(0)
	unify_x_ref(3)
	get_structure('passive', 1, 3)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$compile_a_rule', 3, 1)
	put_y_value(0, 0)
	get_constant('passive', 0)
	deallocate
	proceed

$3:
	get_structure('pragma', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	execute_predicate('$compile_a_rule', 3)

$4:
	get_structure('<=>', 2, 0)
	unify_x_variable(0)
	allocate(7)
	unify_y_variable(6)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$compile_head', 3, 7)
	put_y_value(6, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	call_predicate('$compile_body', 3, 6)
	put_y_value(4, 0)
	get_structure('chr_rule', 5, 0)
	unify_y_value(5)
	unify_y_value(3)
	unify_y_value(2)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$5:
	get_structure('==>', 2, 0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	put_x_variable(2, 2)
	call_predicate('$compile_head', 3, 6)
	put_y_value(5, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	call_predicate('$compile_body', 3, 5)
	put_y_value(3, 0)
	get_structure('chr_rule', 5, 0)
	unify_y_value(4)
	unify_y_value(2)
	unify_constant('[]')
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed
end('$compile_a_rule'/3):



'$compile_head'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '\\'/2:$5])

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
	get_structure('\\', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$compile_head1', 2, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('$compile_head1', 2, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)

$2:
	get_x_value(1, 2)
	execute_predicate('$compile_head1', 2)
end('$compile_head'/3):



'$compile_head1'/3:


$1:
	get_structure('#', 2, 0)
	unify_x_variable(3)
	unify_x_variable(4)
	get_x_variable(0, 1)
	get_list(2)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure('c', 3, 2)
	unify_x_value(3)
	unify_void(1)
	unify_x_value(4)
	neck_cut
	execute_predicate('$compile_head1', 2)
end('$compile_head1'/3):



'$compile_head1'/2:

	switch_on_term(0, $8, $3, $3, $4, $3, $3)

$4:
	switch_on_structure(0, 8, ['$default':$3, '$'/0:$5, ','/2:$6, '#'/2:$7])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	trust($3)

$7:
	try(2, $2)
	trust($3)

$8:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_structure(',', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(3)
	unify_x_variable(1)
	get_structure('c', 3, 3)
	unify_x_value(2)
	unify_void(2)
	neck_cut
	execute_predicate('$compile_head1', 2)

$2:
	get_structure('#', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_list(1)
	unify_x_ref(1)
	unify_constant('[]')
	get_structure('c', 3, 1)
	unify_x_value(0)
	unify_void(1)
	unify_x_value(2)
	neck_cut
	proceed

$3:
	get_list(1)
	unify_x_ref(1)
	unify_constant('[]')
	get_structure('c', 3, 1)
	unify_x_value(0)
	unify_void(2)
	proceed
end('$compile_head1'/2):



'$compile_body'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '|'/2:$5])

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
	get_structure('|', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_value(0, 1)
	get_x_value(3, 2)
	neck_cut
	proceed

$2:
	get_constant('true', 1)
	get_x_value(0, 2)
	proceed
end('$compile_body'/3):



'$extract_constraints'/1:

	switch_on_term(0, $9, 'fail', 'fail', $5, 'fail', 'fail')

$5:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$6, ':-'/1:$7, '?-'/1:$8])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(1, $1)
	trust($2)

$8:
	try(1, $3)
	trust($4)

$9:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('constraints', 1, 0)
	unify_x_variable(0)
	execute_predicate('$process_constraints', 1)

$2:
	get_structure(':-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_constraint', 1, 0)
	unify_x_variable(0)
	execute_predicate('$process_constraints', 1)

$3:
	get_structure('?-', 1, 0)
	unify_x_ref(0)
	get_structure('constraints', 1, 0)
	unify_x_variable(0)
	execute_predicate('$process_constraints', 1)

$4:
	get_structure('?-', 1, 0)
	unify_x_ref(0)
	get_structure('chr_constraint', 1, 0)
	unify_x_variable(0)
	execute_predicate('$process_constraints', 1)
end('$extract_constraints'/1):



'$process_constraints'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ','/2:$5])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$6:
	try(1, $1)
	trust($2)

$1:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(0)
	neck_cut
	put_y_variable(2, 1)
	put_y_variable(1, 2)
	call_predicate('$get_constraint_name_arity', 3, 3)
	put_structure(2, 0)
	set_constant('$chr_constraint_info')
	set_y_value(2)
	set_y_value(1)
	call_predicate('assert', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$process_constraints', 1)

$2:
	allocate(2)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$get_constraint_name_arity', 3, 2)
	put_structure(2, 0)
	set_constant('$chr_constraint_info')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)
end('$process_constraints'/1):



'$get_constraint_name_arity'/3:

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
	unify_x_variable(3)
	get_x_value(0, 1)
	get_x_value(3, 2)
	neck_cut
	proceed

$2:
	pseudo_instr3(0, 0, 1, 2)
	proceed
end('$get_constraint_name_arity'/3):



'$gen_constraints_code'/2:

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
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_y_variable(0)
	call_predicate('$gen_constraint_code', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$gen_constraints_code', 2)
end('$gen_constraints_code'/2):



'$gen_constraint_code'/3:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(3)
	unify_x_variable(0)
	allocate(11)
	get_y_variable(7, 1)
	get_y_variable(2, 2)
	put_y_variable(6, 19)
	pseudo_instr3(0, 26, 3, 0)
	put_x_variable(2, 4)
	get_list(4)
	unify_x_value(3)
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(4)
	get_list(4)
	unify_integer(1)
	unify_constant('[]')
	put_constant('__', 4)
	pseudo_instr3(28, 2, 4, 1)
	get_y_variable(9, 1)
	put_x_variable(2, 4)
	get_list(4)
	unify_x_value(3)
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('retry')
	unify_constant('[]')
	put_constant('__', 0)
	pseudo_instr3(28, 2, 0, 1)
	get_y_variable(5, 1)
	put_y_variable(8, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(6, 0)
	put_list(1)
	set_x_value(3)
	set_y_variable(10)
	call_predicate('=..', 2, 11)
	put_y_value(10, 0)
	put_list(2)
	set_y_value(3)
	set_constant('[]')
	put_list(1)
	set_y_value(4)
	set_x_value(2)
	put_y_value(8, 2)
	call_predicate('append', 3, 10)
	put_y_value(1, 0)
	put_list(1)
	set_y_value(9)
	set_y_value(8)
	call_predicate('=..', 2, 8)
	put_y_value(0, 0)
	put_list(1)
	set_y_value(3)
	set_constant('[]')
	put_list(2)
	set_y_value(4)
	set_x_value(1)
	put_list(3)
	set_y_value(6)
	set_x_value(2)
	put_list(1)
	set_y_value(5)
	set_x_value(3)
	call_predicate('=..', 2, 8)
	put_y_value(7, 0)
	get_structure(':-', 2, 0)
	unify_y_value(6)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('=', 2, 0)
	unify_y_value(3)
	unify_x_ref(0)
	get_structure('c', 5, 0)
	unify_y_value(6)
	unify_y_value(5)
	unify_y_value(4)
	unify_void(2)
	get_structure(',', 2, 1)
	unify_y_value(1)
	unify_x_ref(0)
	get_structure('chr_add_delays', 1, 0)
	unify_y_value(3)
	put_y_value(2, 0)
	get_structure(':-', 2, 0)
	unify_y_value(0)
	unify_y_value(1)
	deallocate
	proceed
end('$gen_constraint_code'/3):



'$chr_process_var_delays'/2:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	put_constant('delays on vars', 1)
	pseudo_instr3(41, 1, 24, 0)
	get_y_variable(1, 0)
	put_constant('indexed constraints', 1)
	pseudo_instr3(41, 1, 24, 0)
	get_y_variable(3, 0)
	get_y_level(0)
	put_y_value(5, 0)
	put_y_variable(2, 1)
	call_predicate('chr_hash_arg', 2, 6)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(2, 3)
	call_predicate('$chr_rehash_delays', 4, 2)
	put_y_value(1, 0)
	call_predicate('$chr_retry_var_delays', 1, 1)
	cut(0)
	deallocate
	proceed
end('$chr_process_var_delays'/2):



'$chr_rehash_delays'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_y_variable(4, 19)
	put_y_variable(5, 1)
	call_predicate('$chr_names', 2, 6)
	pseudo_instr3(41, 25, 21, 0)
	get_x_variable(1, 0)
	put_constant('[]', 2)
	pseudo_instr4(19, 25, 20, 0, 2)
	put_y_value(4, 2)
	call_predicate('$chr_append', 3, 6)
	pseudo_instr3(40, 25, 20, 24)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$chr_rehash_delays', 4)
end('$chr_rehash_delays'/4):



'$chr_retry_var_delays'/1:

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
	call_predicate('call_predicate', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$chr_retry_var_delays', 1)
end('$chr_retry_var_delays'/1):



'$chr_append'/3:

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
	unify_x_variable(3)
	unify_x_variable(0)
	put_integer(3, 5)
	pseudo_instr3(1, 5, 3, 4)
	get_x_variable(3, 4)
	pseudo_instr1(46, 3)
	neck_cut
	execute_predicate('$chr_append', 3)

$3:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('$chr_append', 3)
end('$chr_append'/3):



'chr_add_constraint'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(46, 0)
	neck_cut
	proceed

$2:
	put_integer(4, 4)
	pseudo_instr3(1, 4, 2, 3)
	execute_predicate('chr_add_constraint', 4)
end('chr_add_constraint'/3):



'chr_add_constraint/4$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_value(1)
	put_constant('indexed constraints', 0)
	pseudo_instr3(40, 0, 2, 3)
	proceed
end('chr_add_constraint/4$0'/3):



'chr_add_constraint/4$1'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'all':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_constant('all', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('chr_add_constraint__2', 3)
end('chr_add_constraint/4$1'/3):



'chr_add_constraint'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr1(46, 3)
	neck_cut
	proceed

$2:
	get_x_variable(0, 1)
	allocate(3)
	get_y_variable(2, 2)
	put_integer(1, 2)
	pseudo_instr3(1, 2, 22, 1)
	pseudo_instr2(67, 1, 2)
	put_constant('$constraint_id', 4)
	put_integer(0, 5)
	pseudo_instr3(56, 4, 2, 5)
	pseudo_instr2(69, 2, 4)
	get_x_value(3, 4)
	put_constant('$constraint_id', 2)
	pseudo_instr2(3, 2, 3)
	put_y_variable(1, 19)
	put_x_variable(2, 2)
	pseudo_instr3(0, 1, 21, 2)
	put_y_variable(0, 1)
	call_predicate('chr_hash_arg', 2, 3)
	put_constant('indexed constraints', 1)
	put_constant('[]', 2)
	pseudo_instr4(19, 1, 20, 0, 2)
	get_x_variable(1, 0)
	put_y_value(1, 0)
	put_y_value(0, 2)
	call_predicate('chr_add_constraint/4$0', 3, 3)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_constant('all', 0)
	call_predicate('chr_add_constraint__2', 3, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('chr_add_constraint/4$1', 3)
end('chr_add_constraint'/4):



'chr_add_delays'/1:

	switch_on_term(0, $6, $1, $1, $3, $1, $1)

$3:
	switch_on_structure(0, 4, ['$default':$1, '$'/0:$4, 'c'/5:$5])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$6:
	try(1, $1)
	trust($2)

$1:
	put_integer(3, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_variable(0, 1)
	pseudo_instr1(46, 0)
	neck_cut
	proceed

$2:
	get_x_variable(1, 0)
	put_x_value(1, 0)
	get_structure('c', 5, 0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_void(2)
	pseudo_instr2(67, 2, 0)
	allocate(2)
	get_y_variable(1, 0)
	put_y_variable(0, 0)
	put_list(5)
	set_x_value(1)
	set_constant('[]')
	put_list(1)
	set_x_value(4)
	set_x_value(5)
	put_list(4)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_x_value(3)
	set_x_value(4)
	call_predicate('=..', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$add_vars_delays', 2)
end('chr_add_delays'/1):



'$add_vars_delays/2$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 1)
	put_constant('[]', 1)
	get_x_value(0, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('bound')
	set_x_value(3)
	put_structure(2, 1)
	set_constant('$chr_process_var_delays')
	set_x_value(3)
	set_x_value(2)
	execute_predicate('delay_until', 2)

$2:
	proceed
end('$add_vars_delays/2$0'/3):



'$add_vars_delays/2$1'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member_eq', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_constant('delays on vars', 3)
	put_x_variable(4, 5)
	get_list(5)
	unify_x_value(0)
	unify_x_value(1)
	pseudo_instr3(40, 3, 2, 4)
	proceed
end('$add_vars_delays/2$1'/3):



'$add_vars_delays'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	allocate(5)
	unify_y_variable(4)
	unify_y_variable(1)
	get_y_variable(0, 1)
	put_y_variable(2, 19)
	put_y_value(4, 0)
	put_y_variable(3, 1)
	call_predicate('chr_hash_arg', 2, 5)
	put_constant('delays on vars', 1)
	put_constant('[]', 2)
	pseudo_instr4(19, 1, 23, 0, 2)
	get_y_value(2, 0)
	put_y_value(2, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('$add_vars_delays/2$0', 3, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	call_predicate('$add_vars_delays/2$1', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$add_vars_delays', 2)
end('$add_vars_delays'/2):



'chr_hash_arg'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(43, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr1(1, 0)
	neck_cut
	pseudo_instr2(126, 0, 2)
	get_x_value(1, 2)
	proceed

$3:
	get_constant('all', 1)
	proceed
end('chr_hash_arg'/2):



'chr_not_eq'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('done', 2)
	get_x_value(1, 2)
	put_constant('done', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('chr_not_eq'/2):



'chr_not_in'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'done':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('done', 2)
	get_x_value(0, 2)
	allocate(1)
	get_y_level(0)
	call_predicate('member_eq', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('chr_not_in'/2):



'chr_lookup_hash'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_x_variable(0, 1)
	get_y_variable(0, 2)
	put_y_variable(2, 19)
	put_y_variable(1, 1)
	call_predicate('chr_hash_arg', 2, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$chr_names', 2, 3)
	put_constant('[]', 1)
	pseudo_instr4(19, 22, 21, 0, 1)
	get_y_value(0, 0)
	deallocate
	proceed
end('chr_lookup_hash'/3):



'chr_add_constraint__2'/3:


$1:
	allocate(4)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	get_y_variable(3, 2)
	put_y_variable(2, 19)
	put_y_variable(1, 1)
	call_predicate('$chr_names', 2, 4)
	put_constant('[]', 1)
	pseudo_instr4(19, 21, 20, 0, 1)
	put_y_value(2, 1)
	call_predicate('clean_constraints', 2, 4)
	put_x_variable(0, 1)
	get_list(1)
	unify_y_value(3)
	unify_y_value(2)
	pseudo_instr3(40, 21, 20, 0)
	deallocate
	proceed
end('chr_add_constraint__2'/3):



'$chr_constraint'/1:


$1:
	allocate(3)
	get_y_variable(1, 0)
	put_y_variable(0, 19)
	put_x_variable(0, 0)
	put_y_variable(2, 1)
	call_predicate('$chr_names', 2, 3)
	put_constant('all', 1)
	put_constant('[]', 2)
	pseudo_instr4(19, 22, 1, 0, 2)
	get_x_variable(1, 0)
	put_structure(5, 0)
	set_constant('c')
	set_y_value(1)
	set_void(1)
	set_y_value(0)
	set_void(2)
	call_predicate('member', 2, 1)
	pseudo_instr1(1, 20)
	deallocate
	proceed
end('$chr_constraint'/1):



'chr_collect_constraints'/1:


$1:
	allocate(2)
	get_y_variable(1, 0)
	put_x_variable(2, 0)
	put_structure(2, 1)
	set_constant('$chr_names')
	set_void(1)
	set_x_value(2)
	put_y_variable(0, 2)
	call_predicate('findall', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('chr_collect_constraints_2', 2)
end('chr_collect_constraints'/1):



'chr_collect_constraints_2'/2:

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
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	put_constant('all', 2)
	put_constant('[]', 3)
	pseudo_instr4(19, 0, 2, 1, 3)
	get_x_variable(0, 1)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('chr_extract_active_constraints', 2, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	call_predicate('chr_collect_constraints_2', 2, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)
end('chr_collect_constraints_2'/2):



'chr_extract_active_constraints'/2:

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
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('c', 5, 2)
	unify_x_variable(2)
	unify_void(1)
	unify_x_variable(3)
	unify_void(2)
	pseudo_instr1(1, 3)
	neck_cut
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('chr_extract_active_constraints', 2)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('chr_extract_active_constraints', 2)
end('chr_extract_active_constraints'/2):



'$chr_print_constraints/0$0'/1:

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
	proceed

$2:
	allocate(2)
	get_y_variable(0, 0)
	pseudo_instr1(28, 0)
	get_y_variable(1, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 2)
	put_y_value(1, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 2)
	put_y_value(1, 0)
	put_constant('constraints:', 1)
	put_constant('write', 2)
	call_predicate('$write_t', 3, 2)
	put_y_value(1, 0)
	put_integer(10, 1)
	call_predicate('put_code', 2, 1)
	put_structure(2, 0)
	set_constant('member')
	set_x_variable(1)
	set_y_value(0)
	put_structure(1, 2)
	set_constant('wRq')
	set_x_value(1)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_list(2)
	set_constant('nl')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('write_term_list')
	set_x_value(2)
	call_predicate('forall', 2, 0)
	deallocate
	execute_predicate('nl', 0)
end('$chr_print_constraints/0$0'/1):



'$chr_print_constraints'/0:


$1:
	allocate(1)
	put_y_variable(0, 0)
	call_predicate('chr_collect_constraints', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$chr_print_constraints/0$0', 1)
end('$chr_print_constraints'/0):



'check_and_update_applied'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	get_list(1)
	unify_x_value(0)
	unify_void(1)
	proceed

$2:
	get_list(1)
	unify_x_variable(2)
	unify_x_variable(1)
	pseudo_instr2(133, 0, 2)
	execute_predicate('check_and_update_applied', 2)
end('check_and_update_applied'/2):



'clean_constraints'/2:

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
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	put_integer(3, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_x_variable(2, 3)
	pseudo_instr1(46, 2)
	neck_cut
	execute_predicate('clean_constraints', 2)

$3:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('clean_constraints', 2)
end('clean_constraints'/2):



'chr_remove_aux'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(1)
	unify_x_variable(0)
	get_structure('c', 4, 1)
	unify_void(1)
	unify_constant('done')
	unify_void(2)
	execute_predicate('chr_remove_aux', 1)
end('chr_remove_aux'/1):



'$query_chr_support1526442631_929/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$chr_names')
	set_integer(2)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_chr_support1526442631_929/0$0'/0):



'$query_chr_support1526442631_929'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(0)
	call_predicate('$query_chr_support1526442631_929/0$0', 0, 0)
	fail

$2:
	proceed
end('$query_chr_support1526442631_929'/0):



'$query'/0:


$1:
	execute_predicate('$query_chr_support1526442631_929', 0)
end('$query'/0):



