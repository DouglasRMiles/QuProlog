'$init_fcompile'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('$inline')
	set_integer(4)
	execute_predicate('dynamic', 1)
end('$init_fcompile'/0):



'fcompile'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('fcompile')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('fcompile')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('fcompile')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(50, 0)
	neck_cut
	put_constant('[]', 1)
	execute_predicate('$fcompile_files', 2)

$3:
	get_x_variable(1, 0)
	put_list(0)
	set_x_value(1)
	set_constant('[]')
	put_constant('[]', 1)
	execute_predicate('$fcompile_files', 2)
end('fcompile'/1):



'fcompile'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(50, 0)
	neck_cut
	execute_predicate('$fcompile_files', 2)

$2:
	get_x_variable(2, 0)
	put_list(0)
	set_x_value(2)
	set_constant('[]')
	execute_predicate('$fcompile_files', 2)
end('fcompile'/2):



'$fcompile_files'/2:

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
	allocate(8)
	get_y_variable(7, 1)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	put_y_variable(4, 3)
	put_y_variable(3, 4)
	put_y_variable(2, 5)
	call_predicate('$fcompile_access_check', 6, 8)
	put_y_value(7, 0)
	call_predicate('closed_list', 1, 8)
	put_y_value(7, 0)
	put_y_value(1, 1)
	call_predicate('$set_fcompile_options', 2, 7)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$fcompile_options_atom', 2, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	put_y_value(0, 6)
	deallocate
	execute_predicate('$fcompile_files1', 7)
end('$fcompile_files'/2):



'$fcompile_files1/7$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(3, 1)
	put_constant('.ql', 0)
	put_constant('.qi', 1)
	execute_predicate('$change_suffix', 4)

$2:
	get_x_variable(2, 0)
	get_x_variable(3, 1)
	put_constant('.pl', 0)
	put_constant('.qi', 1)
	execute_predicate('$change_suffix', 4)
end('$fcompile_files1/7$0'/2):



'$fcompile_files1/7$1'/8:

	try(8, $1)
	trust($2)

$1:
	put_integer(2, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_variable(0, 1)
	put_constant('true', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_x_variable(8, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	get_x_variable(5, 6)
	put_x_value(8, 6)
	execute_predicate('$fcompile_files2', 8)
end('$fcompile_files1/7$1'/8):



'$fcompile_files1'/7:


$1:
	allocate(11)
	get_y_variable(7, 0)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 22, 0)
	get_y_level(9)
	put_y_variable(8, 19)
	put_y_variable(0, 19)
	put_y_variable(10, 1)
	call_predicate('$defines_atom', 2, 11)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('$QPPATH/qppp')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(10)
	unify_constant('[]')
	put_constant(' ', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_value(8, 0)
	put_y_value(7, 0)
	put_y_value(0, 1)
	call_predicate('$fcompile_files1/7$0', 2, 10)
	cut(9)
	put_y_value(7, 0)
	put_y_value(0, 1)
	put_y_value(8, 2)
	call_predicate('$preprocess', 3, 8)
	put_y_value(2, 0)
	put_y_value(7, 1)
	put_y_value(0, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(1, 7)
	deallocate
	execute_predicate('$fcompile_files1/7$1', 8)
end('$fcompile_files1'/7):



'$preprocess'/3:

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
	allocate(6)
	unify_y_variable(2)
	get_list(1)
	unify_y_variable(5)
	unify_y_variable(1)
	get_y_variable(0, 2)
	put_y_variable(3, 19)
	put_y_variable(4, 1)
	call_predicate('$wrap_quotes', 2, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	call_predicate('$wrap_quotes', 2, 5)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(0)
	unify_x_ref(2)
	get_list(2)
	unify_constant(' < ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_constant(' > ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_constant('[]')
	put_constant(' ', 2)
	pseudo_instr3(28, 1, 2, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$preprocess', 3)
end('$preprocess'/3):



'$fcompile_files2/8$0/8$0'/2:

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
	call_predicate('$wrap_quotes', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$fcompile_files2/8$0/8$0', 2)
end('$fcompile_files2/8$0/8$0'/2):



'$fcompile_files2/8$0'/8:

	try(8, $1)
	trust($2)

$1:
	put_integer(3, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_variable(0, 1)
	put_constant('true', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(8)
	get_y_variable(6, 0)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_x_variable(0, 1)
	put_y_variable(7, 1)
	call_predicate('$fcompile_files2/8$0/8$0', 2, 8)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('/bin/rm -f')
	unify_y_value(7)
	put_constant(' ', 2)
	pseudo_instr3(28, 1, 2, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(6, 5)
	put_y_value(0, 6)
	deallocate
	execute_predicate('$fcompile_files3', 7)
end('$fcompile_files2/8$0'/8):



'$fcompile_files2'/8:


$1:
	allocate(8)
	get_y_variable(7, 0)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	put_y_value(6, 0)
	call_predicate('$expandfiles', 1, 8)
	put_y_value(5, 0)
	call_predicate('$expandfiles', 1, 8)
	put_y_value(1, 0)
	put_y_value(6, 1)
	put_y_value(7, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$fcompile_files2/8$0', 8)
end('$fcompile_files2'/8):



'$wrap_quotes'/2:


$1:
	pseudo_instr1(2, 0)
	put_x_variable(3, 4)
	get_list(4)
	unify_constant('"')
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('"')
	unify_constant('[]')
	put_constant('', 0)
	pseudo_instr3(28, 3, 0, 2)
	get_x_value(1, 2)
	proceed
end('$wrap_quotes'/2):



'$fcompile_files3/7$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(3, 1)
	put_constant('.ql', 0)
	put_constant('.qg', 1)
	execute_predicate('$change_suffix', 4)

$2:
	get_x_variable(2, 0)
	get_x_variable(3, 1)
	put_constant('.pl', 0)
	put_constant('.qg', 1)
	execute_predicate('$change_suffix', 4)
end('$fcompile_files3/7$0'/2):



'$fcompile_files3/7$1'/2:

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
	call_predicate('$wrap_quotes', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$fcompile_files3/7$1', 2)
end('$fcompile_files3/7$1'/2):



'$fcompile_files3/7$2'/2:

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
	call_predicate('$wrap_quotes', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$fcompile_files3/7$2', 2)
end('$fcompile_files3/7$2'/2):



'$fcompile_files3'/7:


$1:
	allocate(13)
	get_y_variable(10, 0)
	get_y_variable(8, 1)
	get_y_variable(12, 2)
	get_x_variable(0, 3)
	get_x_variable(1, 4)
	get_y_variable(3, 6)
	get_y_level(9)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(11, 2)
	call_predicate('append', 3, 13)
	put_y_value(12, 0)
	put_y_value(11, 1)
	put_y_value(5, 2)
	call_predicate('append', 3, 11)
	put_y_value(10, 0)
	put_y_value(7, 1)
	call_predicate('$fcompile_files3/7$0', 2, 10)
	cut(9)
	put_y_value(8, 2)
	put_y_value(6, 3)
	put_constant('.qi', 0)
	put_constant('.qg', 1)
	call_predicate('$change_suffix', 4, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(1, 2)
	call_predicate('append', 3, 6)
	put_y_value(5, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	call_predicate('append', 3, 5)
	put_y_value(4, 0)
	put_y_value(2, 1)
	call_predicate('$fcompile_files3/7$1', 2, 4)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('$QPPATH/qc')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_y_value(2)
	put_constant(' ', 2)
	pseudo_instr3(28, 1, 2, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$fcompile_files3/7$2', 2, 1)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('/bin/rm -f')
	unify_y_value(0)
	put_constant(' ', 2)
	pseudo_instr3(28, 1, 2, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	deallocate
	proceed
end('$fcompile_files3'/7):



'$set_fcompile_options'/2:


$1:
	allocate(20)
	get_y_variable(1, 0)
	get_structure('fcflags', 20, 1)
	unify_x_variable(1)
	unify_y_variable(19)
	unify_y_variable(18)
	unify_y_variable(17)
	unify_y_variable(16)
	unify_y_variable(15)
	unify_y_variable(14)
	unify_y_variable(13)
	unify_y_variable(12)
	unify_y_variable(11)
	unify_y_variable(10)
	unify_y_variable(9)
	unify_y_variable(8)
	unify_y_variable(7)
	unify_y_variable(6)
	unify_y_variable(5)
	unify_y_variable(4)
	unify_y_variable(3)
	unify_y_variable(2)
	unify_y_variable(0)
	put_structure(1, 0)
	set_constant('defines')
	set_x_value(1)
	put_y_value(1, 1)
	put_constant('[]', 2)
	call_predicate('$process_option', 3, 20)
	put_structure(1, 0)
	set_constant('preprocess_only')
	set_y_value(19)
	put_y_value(1, 1)
	put_constant('false', 2)
	call_predicate('$process_option', 3, 19)
	put_structure(1, 0)
	set_constant('expand_only')
	set_y_value(18)
	put_y_value(1, 1)
	put_constant('false', 2)
	call_predicate('$process_option', 3, 18)
	put_structure(1, 0)
	set_constant('term_expand_file')
	set_y_value(17)
	put_y_value(1, 1)
	put_constant('/dev/null', 2)
	call_predicate('$process_option', 3, 17)
	put_structure(1, 0)
	set_constant('compile_only')
	set_y_value(16)
	put_y_value(1, 1)
	put_constant('false', 2)
	call_predicate('$process_option', 3, 16)
	put_structure(1, 0)
	set_constant('assemble_only')
	set_y_value(15)
	put_y_value(1, 1)
	put_constant('false', 2)
	call_predicate('$process_option', 3, 15)
	put_structure(1, 0)
	set_constant('object_file')
	set_y_value(14)
	put_y_value(1, 1)
	put_x_variable(2, 2)
	call_predicate('$process_option', 3, 14)
	put_structure(1, 0)
	set_constant('verbose')
	set_y_value(13)
	put_y_value(1, 1)
	put_constant('false', 2)
	call_predicate('$process_option', 3, 13)
	put_structure(1, 0)
	set_constant('compiler_binding_trail')
	set_y_value(12)
	put_y_value(1, 1)
	put_integer(32, 2)
	call_predicate('$process_option', 3, 12)
	put_structure(1, 0)
	set_constant('compiler_other_trail')
	set_y_value(11)
	put_y_value(1, 1)
	put_integer(32, 2)
	call_predicate('$process_option', 3, 11)
	put_structure(1, 0)
	set_constant('compiler_choice_point_stack')
	set_y_value(10)
	put_y_value(1, 1)
	put_integer(64, 2)
	call_predicate('$process_option', 3, 10)
	put_structure(1, 0)
	set_constant('compiler_environment_stack')
	set_y_value(9)
	put_y_value(1, 1)
	put_integer(64, 2)
	call_predicate('$process_option', 3, 9)
	put_structure(1, 0)
	set_constant('compiler_heap')
	set_y_value(8)
	put_y_value(1, 1)
	put_integer(400, 2)
	call_predicate('$process_option', 3, 8)
	put_structure(1, 0)
	set_constant('compiler_scratchpad')
	set_y_value(7)
	put_y_value(1, 1)
	put_integer(10, 2)
	call_predicate('$process_option', 3, 7)
	put_structure(1, 0)
	set_constant('compiler_name_table')
	set_y_value(6)
	put_y_value(1, 1)
	put_integer(10000, 2)
	call_predicate('$process_option', 3, 6)
	put_structure(1, 0)
	set_constant('compiler_ip_table')
	set_y_value(5)
	put_y_value(1, 1)
	put_integer(10000, 2)
	call_predicate('$process_option', 3, 5)
	put_structure(1, 0)
	set_constant('string_table')
	set_y_value(4)
	put_y_value(1, 1)
	put_integer(64, 2)
	call_predicate('$process_option', 3, 4)
	put_structure(1, 0)
	set_constant('executable_atom_table')
	set_y_value(3)
	put_y_value(1, 1)
	put_integer(10000, 2)
	call_predicate('$process_option', 3, 3)
	put_structure(1, 0)
	set_constant('executable_code_area')
	set_y_value(2)
	put_y_value(1, 1)
	put_integer(400, 2)
	call_predicate('$process_option', 3, 2)
	put_structure(1, 0)
	set_constant('executable_predicate_table')
	set_y_value(0)
	put_y_value(1, 1)
	put_integer(10000, 2)
	deallocate
	execute_predicate('$process_option', 3)
end('$set_fcompile_options'/2):



'$fcompile_options_atom/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(1, 1)
	call_predicate('$wrap_quotes', 2, 2)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('-o ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(1)
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	put_constant('', 0)
	get_x_value(1, 0)
	proceed
end('$fcompile_options_atom/2$0'/2):



'$fcompile_options_atom'/2:


$1:
	allocate(19)
	get_y_variable(18, 0)
	get_y_variable(1, 1)
	get_y_level(0)
	put_y_variable(16, 19)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_value(18, 1)
	put_y_variable(17, 3)
	put_integer(5, 0)
	put_constant('-S', 2)
	call_predicate('$get_boolean_opt_atom', 4, 19)
	put_y_value(18, 1)
	put_y_value(16, 3)
	put_integer(6, 0)
	put_constant('-c', 2)
	call_predicate('$get_boolean_opt_atom', 4, 19)
	put_integer(7, 1)
	pseudo_instr3(1, 1, 38, 0)
	put_y_value(15, 1)
	call_predicate('$fcompile_options_atom/2$0', 2, 19)
	put_y_value(18, 1)
	put_y_value(14, 3)
	put_integer(8, 0)
	put_constant('-v', 2)
	call_predicate('$get_boolean_opt_atom', 4, 19)
	put_y_value(18, 1)
	put_y_value(13, 2)
	put_integer(9, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(12, 2)
	put_integer(10, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(11, 2)
	put_integer(11, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(10, 2)
	put_integer(12, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(9, 2)
	put_integer(13, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(8, 2)
	put_integer(14, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(7, 2)
	put_integer(15, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(6, 2)
	put_integer(16, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(5, 2)
	put_integer(17, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(4, 2)
	put_integer(18, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(3, 2)
	put_integer(19, 0)
	call_predicate('$get_number_opt_atom', 3, 19)
	put_y_value(18, 1)
	put_y_value(2, 2)
	put_integer(20, 0)
	call_predicate('$get_number_opt_atom', 3, 18)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(17)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(16)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(15)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(14)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-B')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(13)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-O')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(12)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-C')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(11)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-e')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(10)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-h')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(9)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-H')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(8)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-n')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(7)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-i')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-s')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(5)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-a')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-d')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_x_ref(2)
	get_list(2)
	unify_constant('-p')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(2)
	unify_constant('[]')
	put_constant(' ', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_value(1, 0)
	cut(0)
	deallocate
	proceed
end('$fcompile_options_atom'/2):



'$defines_atom'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant(' ', 1)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	neck_cut
	put_x_variable(4, 1)
	get_list(1)
	unify_constant('-D')
	unify_x_ref(1)
	get_list(1)
	unify_x_value(2)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(1)
	unify_constant('[]')
	put_constant(' ', 2)
	pseudo_instr3(28, 4, 2, 3)
	execute_predicate('$defines_atom', 2)
end('$defines_atom'/2):



'$get_number_opt_atom'/3:


$1:
	allocate(3)
	get_y_variable(2, 2)
	pseudo_instr3(1, 0, 1, 2)
	get_x_variable(0, 2)
	get_y_level(0)
	put_y_variable(1, 1)
	call_predicate('number_chars', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('atom_chars', 2, 1)
	cut(0)
	deallocate
	proceed
end('$get_number_opt_atom'/3):



'$get_boolean_opt_atom/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr3(1, 0, 1, 4)
	get_x_variable(0, 4)
	put_constant('true', 1)
	get_x_value(0, 1)
	neck_cut
	get_x_value(2, 3)
	proceed

$2:
	put_constant('', 0)
	get_x_value(2, 0)
	proceed
end('$get_boolean_opt_atom/4$0'/4):



'$get_boolean_opt_atom'/4:


$1:
	get_x_variable(4, 2)
	get_x_variable(2, 3)
	put_x_value(4, 3)
	execute_predicate('$get_boolean_opt_atom/4$0', 4)
end('$get_boolean_opt_atom'/4):



'$fcompile_access_check/6$0/11$0/11$0/11$0'/11:

	try(11, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	allocate(12)
	get_y_variable(10, 0)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_x_variable(0, 0)
	put_y_value(10, 2)
	put_constant('.ql', 1)
	call_predicate('atom_concat', 3, 12)
	cut(11)
	put_y_value(9, 0)
	get_list(0)
	unify_y_value(10)
	unify_y_value(8)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(12)
	get_y_variable(10, 0)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_x_variable(0, 0)
	put_y_value(10, 2)
	put_constant('.pl', 1)
	call_predicate('atom_concat', 3, 12)
	cut(11)
	put_y_value(9, 0)
	get_list(0)
	unify_y_value(10)
	unify_y_value(8)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	allocate(12)
	get_y_variable(8, 0)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_x_variable(0, 0)
	put_y_value(8, 2)
	put_constant('.qi', 1)
	call_predicate('atom_concat', 3, 12)
	cut(11)
	put_y_value(10, 0)
	get_y_value(9, 0)
	put_y_value(7, 0)
	get_list(0)
	unify_y_value(8)
	unify_y_value(6)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$4:
	allocate(12)
	get_y_variable(6, 0)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_x_variable(0, 0)
	put_y_value(6, 2)
	put_constant('.qg', 1)
	call_predicate('atom_concat', 3, 12)
	cut(11)
	put_y_value(10, 0)
	get_y_value(9, 0)
	put_y_value(8, 0)
	get_y_value(7, 0)
	put_y_value(5, 0)
	get_list(0)
	unify_y_value(6)
	unify_y_value(4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$5:
	allocate(12)
	get_y_variable(4, 0)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(6, 5)
	get_y_variable(5, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_x_variable(0, 0)
	put_y_value(4, 2)
	put_constant('.qs', 1)
	call_predicate('atom_concat', 3, 12)
	cut(11)
	put_y_value(10, 0)
	get_y_value(9, 0)
	put_y_value(8, 0)
	get_y_value(7, 0)
	put_y_value(6, 0)
	get_y_value(5, 0)
	put_y_value(3, 0)
	get_list(0)
	unify_y_value(4)
	unify_y_value(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$6:
	allocate(12)
	get_y_variable(2, 0)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(6, 5)
	get_y_variable(5, 6)
	get_y_variable(4, 7)
	get_y_variable(3, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_x_variable(0, 0)
	put_y_value(2, 2)
	put_constant('.qo', 1)
	call_predicate('atom_concat', 3, 12)
	cut(11)
	put_y_value(10, 0)
	get_y_value(9, 0)
	put_y_value(8, 0)
	get_y_value(7, 0)
	put_y_value(6, 0)
	get_y_value(5, 0)
	put_y_value(4, 0)
	get_y_value(3, 0)
	put_y_value(1, 0)
	get_list(0)
	unify_y_value(2)
	unify_y_value(0)
	deallocate
	proceed

$7:
	allocate(10)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	put_structure(1, 1)
	set_constant('fcompile')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	call_predicate('exception', 1, 10)
	put_y_value(9, 0)
	get_y_value(8, 0)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$fcompile_access_check/6$0/11$0/11$0/11$0'/11):



'$fcompile_access_check/6$0/11$0/11$0'/11:

	try(11, $1)
	trust($2)

$1:
	put_x_variable(12, 13)
	get_structure('\\/', 2, 13)
	unify_integer(4)
	unify_integer(0)
	pseudo_instr2(0, 11, 12)
	pseudo_instr3(34, 0, 11, 12)
	put_integer(0, 11)
	get_x_value(12, 11)
	neck_cut
	execute_predicate('$fcompile_access_check/6$0/11$0/11$0/11$0', 11)

$2:
	allocate(10)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	put_structure(1, 1)
	set_constant('fcompile')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	call_predicate('exception', 1, 10)
	put_y_value(9, 0)
	get_y_value(8, 0)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$fcompile_access_check/6$0/11$0/11$0'/11):



'$fcompile_access_check/6$0/11$0'/11:

	try(11, $1)
	trust($2)

$1:
	execute_predicate('$fcompile_access_check/6$0/11$0/11$0', 11)

$2:
	allocate(10)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	put_structure(1, 1)
	set_constant('fcompile')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	call_predicate('exception', 1, 10)
	put_y_value(9, 0)
	get_y_value(8, 0)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$fcompile_access_check/6$0/11$0'/11):



'$fcompile_access_check/6$0'/11:

	try(11, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(11, 0)
	allocate(10)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	pseudo_instr1(1, 11)
	neck_cut
	put_structure(1, 0)
	set_constant('fcompile')
	set_x_value(11)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('fcompile')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('fcompile')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_integer(1, 1)
	call_predicate('instantiation_exception', 3, 10)
	put_y_value(9, 0)
	get_y_value(8, 0)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(12)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_y_variable(8, 1)
	call_predicate('$append_ql_suffix', 2, 12)
	put_x_variable(1, 2)
	get_structure('\\/', 2, 2)
	unify_integer(4)
	unify_integer(0)
	pseudo_instr2(0, 0, 1)
	pseudo_instr3(34, 28, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	cut(11)
	put_y_value(10, 0)
	get_list(0)
	unify_y_value(8)
	unify_y_value(9)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	allocate(12)
	get_y_variable(10, 1)
	get_y_variable(9, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_variable(1, 9)
	get_y_variable(0, 10)
	get_y_level(11)
	put_y_variable(8, 1)
	call_predicate('$append_pl_suffix', 2, 12)
	put_x_variable(1, 2)
	get_structure('\\/', 2, 2)
	unify_integer(4)
	unify_integer(0)
	pseudo_instr2(0, 0, 1)
	pseudo_instr3(34, 28, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	cut(11)
	put_y_value(10, 0)
	get_list(0)
	unify_y_value(8)
	unify_y_value(9)
	put_y_value(7, 0)
	get_y_value(6, 0)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$4:
	execute_predicate('$fcompile_access_check/6$0/11$0', 11)
end('$fcompile_access_check/6$0'/11):



'$fcompile_access_check'/6:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(6, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('[]', 2)
	get_constant('[]', 3)
	get_constant('[]', 4)
	get_constant('[]', 5)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(7)
	unify_y_variable(5)
	get_x_variable(6, 2)
	get_x_variable(8, 3)
	get_x_variable(7, 4)
	get_x_variable(9, 5)
	get_y_level(6)
	put_y_variable(4, 2)
	put_x_value(6, 3)
	put_y_variable(3, 4)
	put_x_value(8, 5)
	put_y_variable(2, 6)
	put_y_variable(1, 8)
	put_y_variable(0, 10)
	call_predicate('$fcompile_access_check/6$0', 11, 7)
	cut(6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$fcompile_access_check', 6)
end('$fcompile_access_check'/6):



'$append_ql_suffix'/2:


$1:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.ql')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$append_ql_suffix'/2):



'$append_pl_suffix'/2:


$1:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.pl')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$append_pl_suffix'/2):



'$append_qi_suffix'/2:


$1:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.qi')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$append_qi_suffix'/2):



'$append_qg_suffix'/2:


$1:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.qg')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$append_qg_suffix'/2):



'$append_qs_suffix'/2:


$1:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.qs')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$append_qs_suffix'/2):



'$append_qo_suffix'/2:


$1:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.qo')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$append_qo_suffix'/2):



'$remove_ql_suffix'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('.ql', 1)
	execute_predicate('atom_concat', 3)
end('$remove_ql_suffix'/2):



'$remove_qi_suffix'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('.qi', 1)
	execute_predicate('atom_concat', 3)
end('$remove_qi_suffix'/2):



'$remove_qg_suffix'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('.qg', 1)
	execute_predicate('atom_concat', 3)
end('$remove_qg_suffix'/2):



'$remove_qs_suffix'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('.qs', 1)
	execute_predicate('atom_concat', 3)
end('$remove_qs_suffix'/2):



'$remove_qo_suffix'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('.qo', 1)
	execute_predicate('atom_concat', 3)
end('$remove_qo_suffix'/2):



'$change_suffix'/4:

	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 2)
	get_constant('[]', 3)
	proceed

$2:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_list(2)
	unify_x_variable(2)
	unify_y_variable(1)
	get_list(3)
	unify_y_variable(5)
	unify_y_variable(0)
	put_y_variable(4, 0)
	put_y_value(3, 1)
	call_predicate('atom_concat', 3, 6)
	put_y_value(4, 0)
	put_y_value(2, 1)
	put_y_value(5, 2)
	call_predicate('atom_concat', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$change_suffix', 4)
end('$change_suffix'/4):



