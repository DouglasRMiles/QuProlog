'statistics'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	put_y_variable(0, 0)
	call_predicate('thread_symbol', 1, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('statistics', 3)
end('statistics'/2):



'statistics'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(43, 22)
	pseudo_instr1(1, 21)
	neck_cut
	put_y_value(1, 0)
	call_predicate('$stat_key', 1, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$statistics', 3)

$2:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	pseudo_instr1(43, 3)
	allocate(1)
	get_y_level(0)
	put_x_value(3, 1)
	call_predicate('$statistics', 3, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('statistics')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('thread')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('statistics')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('statistics'/3):



'$stat_key'/1:

	switch_on_term(0, $20, 'fail', 'fail', 'fail', 'fail', $19)

$19:
	switch_on_constant(0, 64, ['$default':'fail', 'choice':$1, 'core':$2, 'garbage_collection':$3, 'global_stack':$4, 'heap':$5, 'local_stack':$6, 'program':$7, 'runtime':$8, 'stack_shifts':$9, 'binding_trail':$10, 'other_trail':$11, 'code':$12, 'string':$13, 'name':$14, 'ip_table':$15, 'scratchpad':$16, 'atom':$17, 'predicate':$18])

$20:
	try(1, $1)
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
	trust($18)

$1:
	get_constant('choice', 0)
	proceed

$2:
	get_constant('core', 0)
	proceed

$3:
	get_constant('garbage_collection', 0)
	proceed

$4:
	get_constant('global_stack', 0)
	proceed

$5:
	get_constant('heap', 0)
	proceed

$6:
	get_constant('local_stack', 0)
	proceed

$7:
	get_constant('program', 0)
	proceed

$8:
	get_constant('runtime', 0)
	proceed

$9:
	get_constant('stack_shifts', 0)
	proceed

$10:
	get_constant('binding_trail', 0)
	proceed

$11:
	get_constant('other_trail', 0)
	proceed

$12:
	get_constant('code', 0)
	proceed

$13:
	get_constant('string', 0)
	proceed

$14:
	get_constant('name', 0)
	proceed

$15:
	get_constant('ip_table', 0)
	proceed

$16:
	get_constant('scratchpad', 0)
	proceed

$17:
	get_constant('atom', 0)
	proceed

$18:
	get_constant('predicate', 0)
	proceed
end('$stat_key'/1):



'$statistics/3$0'/1:

	switch_on_term(0, $5, $1, $1, $1, $1, $3)

$3:
	switch_on_constant(0, 4, ['$default':$1, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('$stat_runtime', 2)
	pseudo_instr2(73, 2, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(0, 1)
	get_x_value(0, 1)
	proceed
end('$statistics/3$0'/1):



'$statistics'/3:

	switch_on_term(0, $21, 'fail', 'fail', 'fail', 'fail', $20)

$20:
	switch_on_constant(0, 64, ['$default':'fail', 'choice':$1, 'core':$2, 'garbage_collection':$3, 'global_stack':$4, 'heap':$5, 'local_stack':$6, 'memory':$7, 'program':$8, 'runtime':$9, 'stack_shifts':$10, 'binding_trail':$11, 'other_trail':$12, 'code':$13, 'string':$14, 'name':$15, 'ip_table':$16, 'scratchpad':$17, 'atom':$18, 'predicate':$19])

$21:
	try(3, $1)
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
	trust($19)

$1:
	get_constant('choice', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_x_ref(3)
	get_list(3)
	unify_x_variable(3)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(7, 1, 4, 5)
	put_x_value(4, 1)
	get_structure('stat', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$2:
	get_constant('core', 0)
	get_x_variable(1, 2)
	neck_cut
	put_constant('memory', 0)
	execute_predicate('$statistics', 2)

$3:
	get_constant('garbage_collection', 0)
	get_list(2)
	unify_integer(0)
	unify_x_ref(0)
	get_list(0)
	unify_integer(0)
	unify_x_ref(0)
	get_list(0)
	unify_integer(0)
	unify_constant('[]')
	neck_cut
	proceed

$4:
	get_constant('global_stack', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_x_ref(3)
	get_list(3)
	unify_x_variable(3)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(8, 1, 4, 5)
	put_x_value(4, 1)
	get_structure('stat', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$5:
	get_constant('heap', 0)
	get_x_variable(1, 2)
	neck_cut
	put_constant('program', 0)
	execute_predicate('$statistics', 2)

$6:
	get_constant('local_stack', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_x_ref(3)
	get_list(3)
	unify_x_variable(3)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(9, 1, 4, 5)
	put_x_value(4, 1)
	get_structure('stat', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$7:
	get_constant('memory', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_integer(0)
	unify_constant('[]')
	neck_cut
	pseudo_instr1(16, 1)
	get_x_value(0, 1)
	proceed

$8:
	get_constant('program', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_integer(0)
	unify_constant('[]')
	neck_cut
	pseudo_instr1(17, 1)
	get_x_value(0, 1)
	proceed

$9:
	get_constant('runtime', 0)
	get_list(2)
	allocate(4)
	unify_y_variable(0)
	unify_x_ref(0)
	get_list(0)
	unify_y_variable(1)
	unify_constant('[]')
	neck_cut
	get_y_level(3)
	pseudo_instr1(15, 0)
	get_y_value(0, 0)
	put_y_variable(2, 0)
	call_predicate('$statistics/3$0', 1, 4)
	cut(3)
	pseudo_instr3(3, 20, 22, 0)
	get_y_value(1, 0)
	put_constant('$stat_runtime', 0)
	pseudo_instr2(74, 0, 20)
	deallocate
	proceed

$10:
	get_constant('stack_shifts', 0)
	get_list(2)
	unify_integer(0)
	unify_x_ref(0)
	get_list(0)
	unify_integer(0)
	unify_x_ref(0)
	get_list(0)
	unify_integer(0)
	unify_constant('[]')
	neck_cut
	proceed

$11:
	get_constant('binding_trail', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_x_ref(3)
	get_list(3)
	unify_x_variable(3)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(10, 1, 4, 5)
	put_x_value(4, 1)
	get_structure('stat', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$12:
	get_constant('other_trail', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_x_ref(3)
	get_list(3)
	unify_x_variable(3)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(59, 1, 4, 5)
	put_x_value(4, 1)
	get_structure('stat', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$13:
	get_constant('code', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(1)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(11, 2, 3, 4)
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed

$14:
	get_constant('string', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(1)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(12, 3, 4, 5)
	put_x_value(4, 3)
	get_structure('stat', 3, 3)
	unify_x_value(0)
	unify_x_value(1)
	unify_x_value(2)
	proceed

$15:
	get_constant('name', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_constant('[]')
	neck_cut
	pseudo_instr2(15, 1, 3)
	put_x_value(3, 1)
	get_structure('stat', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$16:
	get_constant('ip_table', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_constant('[]')
	neck_cut
	pseudo_instr2(99, 1, 3)
	put_x_value(3, 1)
	get_structure('stat', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$17:
	get_constant('scratchpad', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(2)
	get_list(2)
	unify_x_variable(2)
	unify_x_ref(3)
	get_list(3)
	unify_x_variable(3)
	unify_constant('[]')
	neck_cut
	pseudo_instr3(62, 1, 4, 5)
	put_x_value(4, 1)
	get_structure('stat', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$18:
	get_constant('atom', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(1)
	unify_constant('[]')
	neck_cut
	pseudo_instr2(13, 2, 3)
	get_structure('stat', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$19:
	get_constant('predicate', 0)
	get_list(2)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(1)
	unify_constant('[]')
	neck_cut
	pseudo_instr2(14, 2, 3)
	get_structure('stat', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed
end('$statistics'/3):



'statistics'/0:


$1:
	pseudo_instr1(68, 0)
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(28, 0)
	put_constant('Data Area	Total	Used	Free	Max Usage', 1)
	call_predicate('write_atom', 2, 1)
	call_predicate('nl', 0, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_global_stack', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_scratchpad', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_local_stack', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_choice_stack', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_binding_trail', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_other_trail', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_code_area', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_string_area', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_name_table', 1, 1)
	put_y_value(0, 0)
	call_predicate('$statistics_IP_table', 1, 0)
	call_predicate('$statistics_atom_table', 0, 0)
	call_predicate('$statistics_predicate_table', 0, 0)
	deallocate
	execute_predicate('$statistics_runtime', 0)
end('statistics'/0):



'$statistics_global_stack'/1:


$1:
	pseudo_instr3(8, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('global stack	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_global_stack'/1):



'$statistics_scratchpad'/1:


$1:
	pseudo_instr3(62, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('scratchpad	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_scratchpad'/1):



'$statistics_local_stack'/1:


$1:
	pseudo_instr3(9, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('local stack	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_local_stack'/1):



'$statistics_choice_stack'/1:


$1:
	pseudo_instr3(7, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('choice stack	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_choice_stack'/1):



'$statistics_binding_trail'/1:


$1:
	pseudo_instr3(10, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('binding trail	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_binding_trail'/1):



'$statistics_other_trail'/1:


$1:
	pseudo_instr3(59, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('other trail	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_other_trail'/1):



'$statistics_code_area'/1:


$1:
	pseudo_instr3(11, 0, 1, 2)
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('code area	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_code_area'/1):



'$statistics_string_area'/1:


$1:
	pseudo_instr3(12, 0, 1, 2)
	put_x_value(1, 0)
	get_structure('stat', 3, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 22, 21, 0)
	get_y_variable(3, 0)
	pseudo_instr1(28, 0)
	put_constant('string area	', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(3, 0)
	call_predicate('write', 1, 3)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_string_area'/1):



'$statistics_name_table'/1:


$1:
	pseudo_instr2(15, 0, 1)
	put_x_value(1, 0)
	get_structure('stat', 2, 0)
	allocate(3)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 21, 20, 0)
	get_y_variable(2, 0)
	pseudo_instr1(28, 0)
	put_constant('name table	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_name_table'/1):



'$statistics_IP_table'/1:


$1:
	pseudo_instr2(99, 0, 1)
	put_x_value(1, 0)
	get_structure('stat', 2, 0)
	allocate(3)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 21, 20, 0)
	get_y_variable(2, 0)
	pseudo_instr1(28, 0)
	put_constant('IP table	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_IP_table'/1):



'$statistics_atom_table'/0:


$1:
	pseudo_instr2(13, 0, 1)
	get_structure('stat', 2, 0)
	allocate(3)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 21, 20, 0)
	get_y_variable(2, 0)
	pseudo_instr1(28, 0)
	put_constant('atom table	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_atom_table'/0):



'$statistics_predicate_table'/0:


$1:
	pseudo_instr2(14, 0, 1)
	get_structure('stat', 2, 0)
	allocate(3)
	unify_y_variable(1)
	unify_y_variable(0)
	pseudo_instr3(2, 21, 20, 0)
	get_y_variable(2, 0)
	pseudo_instr1(28, 0)
	put_constant('predicate table	', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	call_predicate('write', 1, 2)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	call_predicate('write', 1, 1)
	pseudo_instr1(28, 0)
	put_constant('	', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_predicate_table'/0):



'$statistics_runtime'/0:


$1:
	pseudo_instr1(15, 0)
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('nl', 0, 1)
	pseudo_instr1(28, 0)
	put_constant('runtime		', 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	call_predicate('write', 1, 0)
	pseudo_instr1(28, 0)
	put_constant(' ms', 1)
	call_predicate('write_atom', 2, 0)
	call_predicate('nl', 0, 0)
	deallocate
	execute_predicate('nl', 0)
end('$statistics_runtime'/0):



