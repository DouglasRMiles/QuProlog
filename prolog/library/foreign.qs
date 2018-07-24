'$write_type'/1:

	switch_on_term(0, $6, 'fail', 'fail', 'fail', 'fail', $5)

$5:
	switch_on_constant(0, 8, ['$default':'fail', 'integer':$1, 'float':$2, 'atom':$3, 'string':$4])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('integer', 0)
	put_constant('long', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_constant('float', 0)
	put_constant('double', 0)
	execute_predicate('$foreign_write', 1)

$3:
	get_constant('atom', 0)
	put_constant('char *', 0)
	execute_predicate('$foreign_write', 1)

$4:
	get_constant('string', 0)
	put_constant('char *', 0)
	execute_predicate('$foreign_write', 1)
end('$write_type'/1):



'$type_check'/1:

	switch_on_term(0, $6, 'fail', 'fail', 'fail', 'fail', $5)

$5:
	switch_on_constant(0, 8, ['$default':'fail', 'integer':$1, 'float':$2, 'atom':$3, 'string':$4])

$6:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('integer', 0)
	put_constant('isInteger()', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_constant('float', 0)
	put_constant('isDouble()', 0)
	execute_predicate('$foreign_write', 1)

$3:
	get_constant('atom', 0)
	put_constant('isAtom()', 0)
	execute_predicate('$foreign_write', 1)

$4:
	get_constant('string', 0)
	put_constant('isString()', 0)
	execute_predicate('$foreign_write', 1)
end('$type_check'/1):



'$extract_value'/2:

	switch_on_term(0, $7, 'fail', 'fail', 'fail', 'fail', $6)

$6:
	switch_on_constant(0, 16, ['$default':'fail', 'integer':$1, 'float':$2, 'double':$3, 'atom':$4, 'string':$5])

$7:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('integer', 0)
	get_x_variable(0, 1)
	allocate(0)
	call_predicate('$write_pval', 1, 0)
	put_constant('->getInteger()', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$2:
	get_constant('float', 0)
	get_x_variable(0, 1)
	allocate(0)
	call_predicate('$write_pval', 1, 0)
	put_constant('->getDouble()', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$3:
	get_constant('double', 0)
	get_x_variable(0, 1)
	allocate(0)
	call_predicate('$write_pval', 1, 0)
	put_constant('->getDouble()', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$4:
	get_constant('atom', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_constant('fi->getAtomString(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 0)
	put_constant(')', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$5:
	get_constant('string', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_constant('fi->getString(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 0)
	put_constant(')', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$extract_value'/2):



'$make_term'/2:

	switch_on_term(0, $7, 'fail', 'fail', 'fail', 'fail', $6)

$6:
	switch_on_constant(0, 16, ['$default':'fail', 'integer':$1, 'float':$2, 'double':$3, 'string':$4, 'atom':$5])

$7:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('integer', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 1)
	put_constant(' = fi->makeInteger(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 1)
	put_constant('integer', 0)
	deallocate
	execute_predicate('$write_foreign_val', 2)

$2:
	get_constant('float', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 1)
	put_constant(' = fi->makeDouble(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 1)
	put_constant('float', 0)
	deallocate
	execute_predicate('$write_foreign_val', 2)

$3:
	get_constant('double', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 1)
	put_constant(' = fi->makeDouble(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 1)
	put_constant('float', 0)
	deallocate
	execute_predicate('$write_foreign_val', 2)

$4:
	get_constant('string', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 1)
	put_constant(' = fi->makeString(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 1)
	put_constant('string', 0)
	deallocate
	execute_predicate('$write_foreign_val', 2)

$5:
	get_constant('atom', 0)
	allocate(1)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 1)
	put_constant(' = fi->makeAtom(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 1)
	put_constant('atom', 0)
	deallocate
	execute_predicate('$write_foreign_val', 2)
end('$make_term'/2):



'$write_foreign_language'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'c':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_constant('c', 0)
	neck_cut
	put_constant('"C"', 0)
	execute_predicate('$foreign_write', 1)

$2:
	proceed
end('$write_foreign_language'/1):



'load_foreign_files'/1:


$1:
	put_constant('[]', 1)
	execute_predicate('load_foreign_files', 2)
end('load_foreign_files'/1):



'load_foreign_files/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_constant('atom', 0)
	call_predicate('application', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('load_foreign_files/2$0'/1):



'load_foreign_files'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('load_foreign_files')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('load_foreign_files')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('load_foreign_files')
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('load_foreign_files')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('load_foreign_files')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('load_foreign_files')
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(2, 21)
	get_y_level(2)
	put_constant('atom', 0)
	call_predicate('application', 2, 3)
	cut(2)
	put_list(0)
	set_y_value(1)
	set_constant('[]')
	put_y_value(0, 1)
	deallocate
	execute_predicate('$load_foreign_files', 2)

$4:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(1, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 3)
	put_y_value(0, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$load_foreign_files', 2)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(0, 0)
	call_predicate('load_foreign_files/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('load_foreign_files')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('load_foreign_files')
	set_x_value(2)
	set_x_value(3)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('load_foreign_files')
	set_x_value(1)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_integer(2, 1)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('load_foreign_files')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('load_foreign_files')
	set_x_value(2)
	set_x_value(3)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('load_foreign_files')
	set_x_value(1)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('load_foreign_files'/2):



'$load_foreign_files'/2:


$1:
	allocate(10)
	get_y_variable(5, 1)
	put_y_variable(6, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(7, 1)
	put_y_variable(9, 2)
	put_y_variable(8, 3)
	call_predicate('$foreign_functions', 4, 10)
	put_constant('foreignXXXXXX', 1)
	pseudo_instr2(47, 1, 0)
	get_y_value(2, 0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	call_predicate('$interface_file', 3, 10)
	put_y_value(1, 0)
	put_y_value(9, 1)
	put_y_value(8, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	call_predicate('$gen_foreign_file', 5, 8)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('qcc -o ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(0)
	unify_x_ref(2)
	get_list(2)
	unify_constant(' ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(1)
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_y_value(7, 0)
	put_list(1)
	set_y_value(0)
	set_constant('[]')
	put_y_value(6, 2)
	call_predicate('append', 3, 7)
	pseudo_instr4(3, 26, 25, 24, 23)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('rm -f ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(2)
	unify_x_ref(2)
	get_list(2)
	unify_constant(' ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(1)
	unify_x_ref(2)
	get_list(2)
	unify_constant(' ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(0)
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	deallocate
	proceed
end('$load_foreign_files'/2):



'generate_foreign_interface'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(2, 3)
	neck_cut
	put_list(0)
	set_x_value(3)
	set_constant('[]')
	put_constant('[]', 1)
	execute_predicate('generate_foreign_interface', 3)
end('generate_foreign_interface'/2):



'generate_foreign_interface/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_constant('atom', 0)
	call_predicate('application', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('generate_foreign_interface/3$0'/1):



'generate_foreign_interface/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_constant('atom', 0)
	call_predicate('application', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('generate_foreign_interface/3$1'/1):



'generate_foreign_interface'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('generate_foreign_interface')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('generate_foreign_interface')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('generate_foreign_interface')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('generate_foreign_interface')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('generate_foreign_interface')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('generate_foreign_interface')
	set_x_value(2)
	set_x_value(3)
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_y_value(2, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 3)
	put_y_value(1, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 3)
	pseudo_instr1(2, 20)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$convert_foreign', 3)

$5:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('generate_foreign_interface/3$0', 1, 2)
	cut(1)
	put_structure(2, 0)
	set_constant('generate_foreign_interface')
	set_y_value(0)
	set_void(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('generate_foreign_interface')
	set_x_value(2)
	set_x_value(3)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('generate_foreign_interface')
	set_x_value(1)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_integer(1, 1)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	get_y_level(1)
	call_predicate('generate_foreign_interface/3$1', 1, 2)
	cut(1)
	put_structure(2, 0)
	set_constant('generate_foreign_interface')
	set_y_value(0)
	set_void(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('generate_foreign_interface')
	set_x_value(2)
	set_x_value(3)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('generate_foreign_interface')
	set_x_value(1)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_integer(2, 1)
	deallocate
	execute_predicate('type_exception', 4)

$7:
	get_x_variable(3, 0)
	put_structure(2, 0)
	set_constant('generate_foreign_interface')
	set_x_value(3)
	set_void(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(2, 1)
	set_constant('generate_foreign_interface')
	set_x_value(2)
	set_x_value(3)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 5)
	set_constant('generate_foreign_interface')
	set_x_value(1)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_integer(3, 1)
	execute_predicate('type_exception', 4)
end('generate_foreign_interface'/3):



'$foreign_functions'/4:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(4, $2)
	trust($3)

$5:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('[]', 2)
	get_constant('[]', 3)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(10)
	unify_y_variable(3)
	get_y_variable(8, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_level(9)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(7, 1)
	call_predicate('$foreign_object_file', 2, 10)
	put_y_value(7, 0)
	put_y_value(4, 1)
	call_predicate('foreign_file', 2, 10)
	cut(9)
	put_y_value(8, 0)
	get_list(0)
	unify_y_value(7)
	unify_y_value(2)
	put_y_value(4, 0)
	put_y_value(6, 1)
	put_y_value(1, 2)
	put_y_value(5, 3)
	put_y_value(0, 4)
	call_predicate('$collect_function_spec', 5, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$foreign_functions', 4)

$3:
	put_x_value(0, 1)
	get_list(1)
	unify_x_variable(1)
	unify_void(1)
	put_structure(1, 2)
	set_constant('load_foreign_files')
	set_x_value(0)
	put_structure(1, 3)
	set_constant('foreign_file')
	set_x_value(1)
	put_structure(3, 0)
	set_constant('declaration_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_x_value(3)
	execute_predicate('exception', 1)
end('$foreign_functions'/4):



'$foreign_object_file'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	put_integer(2, 2)
	put_constant('.o', 3)
	pseudo_instr4(1, 0, 2, 3, 1)
	neck_cut
	proceed

$2:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.o')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_value(1, 2)
	proceed
end('$foreign_object_file'/2):



'$collect_function_spec/5$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 2)
	put_constant('foreign', 3)
	put_integer(2, 4)
	pseudo_instr3(33, 3, 4, 2)
	put_integer(1, 3)
	get_x_value(2, 3)
	call_predicate('foreign', 2, 1)
	put_y_value(0, 0)
	get_constant('c', 0)
	deallocate
	proceed

$2:
	get_x_variable(3, 1)
	get_x_variable(1, 2)
	put_constant('foreign', 4)
	put_integer(3, 5)
	pseudo_instr3(33, 4, 5, 2)
	put_integer(1, 4)
	get_x_value(2, 4)
	put_x_value(3, 2)
	execute_predicate('foreign', 3)
end('$collect_function_spec/5$0'/3):



'$collect_function_spec'/5:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(5, $2)
	trust($3)

$5:
	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	get_x_value(3, 4)
	proceed

$2:
	get_list(0)
	allocate(9)
	unify_y_variable(4)
	unify_y_variable(2)
	get_y_variable(7, 1)
	get_y_variable(1, 2)
	get_y_variable(3, 3)
	get_y_variable(0, 4)
	get_y_level(8)
	put_y_value(4, 0)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	call_predicate('$collect_function_spec/5$0', 3, 9)
	cut(8)
	put_y_value(7, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_variable(1)
	get_structure(':', 2, 0)
	unify_y_value(6)
	unify_y_value(5)
	put_y_value(3, 0)
	get_list(0)
	unify_y_value(4)
	unify_x_variable(3)
	put_y_value(2, 0)
	put_y_value(1, 2)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$collect_function_spec', 5)

$3:
	get_list(0)
	unify_x_variable(0)
	unify_void(1)
	put_structure(2, 1)
	set_constant('foreign')
	set_x_value(0)
	set_void(1)
	put_structure(3, 0)
	set_constant('declaration_error')
	set_constant('unrecoverable')
	set_constant('true')
	set_x_value(1)
	execute_predicate('exception', 1)
end('$collect_function_spec'/5):



'$interface_file'/3:


$1:
	put_x_variable(4, 5)
	get_list(5)
	unify_x_value(0)
	unify_x_ref(5)
	get_list(5)
	unify_constant('.cc')
	unify_constant('[]')
	pseudo_instr2(31, 4, 3)
	get_x_value(1, 3)
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.o')
	unify_constant('[]')
	pseudo_instr2(31, 3, 1)
	get_x_value(2, 1)
	proceed
end('$interface_file'/3):



'$gen_foreign_file/5$0/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_integer(-1, 2)
	get_x_value(0, 2)
	neck_cut
	put_x_variable(2, 0)
	get_structure('open', 3, 0)
	unify_x_value(1)
	unify_constant('write')
	unify_void(1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened stream ')
	set_x_value(3)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('$gen_foreign_file/5$0/3$0'/2):



'$gen_foreign_file/5$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	get_x_variable(0, 2)
	pseudo_instr3(31, 3, 1, 2)
	get_x_value(0, 2)
	neck_cut
	put_x_value(3, 1)
	execute_predicate('$gen_foreign_file/5$0/3$0', 2)

$2:
	put_structure(3, 1)
	set_constant('open')
	set_x_value(0)
	set_constant('write')
	set_void(1)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('$gen_foreign_file/5$0'/3):



'$gen_foreign_file'/5:


$1:
	allocate(10)
	get_y_variable(9, 0)
	get_y_variable(7, 1)
	get_y_variable(5, 2)
	get_y_variable(6, 3)
	get_y_variable(4, 4)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(8, 1)
	put_x_variable(2, 2)
	put_constant('write', 0)
	call_predicate('$iomode', 3, 10)
	put_y_value(9, 0)
	put_y_value(8, 1)
	put_y_value(1, 2)
	call_predicate('$gen_foreign_file/5$0', 3, 8)
	put_constant('$foreign_stream', 0)
	pseudo_instr2(74, 0, 21)
	put_constant('#include "QuProlog.h"
', 0)
	call_predicate('$foreign_write', 1, 8)
	put_y_value(7, 0)
	put_y_value(5, 1)
	put_y_value(6, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	call_predicate('$gen_extern_declaration', 5, 6)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	call_predicate('$gen_foreign_functions', 4, 2)
	put_y_value(0, 1)
	put_constant('true', 0)
	call_predicate('$boolnum', 2, 2)
	pseudo_instr2(40, 21, 20)
	deallocate
	proceed
end('$gen_foreign_file'/5):



'$foreign_write'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(2, 1)
	neck_cut
	put_constant('$foreign_stream', 2)
	pseudo_instr2(73, 2, 0)
	execute_predicate('write_atom', 2)

$2:
	pseudo_instr1(3, 0)
	neck_cut
	put_constant('$foreign_stream', 2)
	pseudo_instr2(73, 2, 1)
	pseudo_instr2(18, 1, 0)
	proceed

$3:
	pseudo_instr1(85, 0)
	neck_cut
	put_constant('$foreign_stream', 2)
	pseudo_instr2(73, 2, 1)
	pseudo_instr2(115, 1, 0)
	proceed

$4:
	put_structure(2, 1)
	set_constant(':')
	set_constant('fail to write out')
	set_x_value(0)
	put_constant('stderr', 0)
	allocate(0)
	call_predicate('write', 2, 0)
	fail
end('$foreign_write'/1):



'$gen_extern_declaration'/5:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(5, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('[]', 2)
	get_constant('[]', 3)
	get_constant('[]', 4)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(5)
	unify_y_variable(4)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(3)
	get_list(2)
	unify_x_variable(2)
	unify_y_variable(2)
	get_list(3)
	unify_x_variable(3)
	unify_y_variable(1)
	get_list(4)
	unify_x_variable(4)
	unify_y_variable(0)
	call_predicate('$gen_extern_declar', 5, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$gen_extern_declaration', 5)
end('$gen_extern_declaration'/5):



'$gen_extern_declar'/5:


$1:
	get_structure(':', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_structure('/', 2, 2)
	unify_x_variable(2)
	unify_x_variable(1)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	pseudo_instr3(0, 0, 2, 1)
	put_x_value(0, 2)
	put_integer(0, 0)
	call_predicate('$partition_foreign_args', 5, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$write_extrn_c_fn', 4)
end('$gen_extern_declar'/5):



'$partition_foreign_args/5$0'/1:

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
	proceed

$2:
	proceed
end('$partition_foreign_args/5$0'/1):



'$partition_foreign_args'/5:

	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 3)
	get_x_value(0, 1)
	get_x_variable(0, 4)
	allocate(1)
	get_y_level(0)
	call_predicate('$partition_foreign_args/5$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(5, 0)
	allocate(6)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_x_variable(2, 3)
	get_y_variable(2, 4)
	pseudo_instr2(69, 5, 0)
	get_y_variable(1, 0)
	pseudo_instr3(1, 21, 23, 0)
	get_y_level(5)
	put_x_value(5, 1)
	put_y_variable(0, 3)
	call_predicate('$partition_foreign_arg', 5, 6)
	cut(5)
	put_y_value(1, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	deallocate
	execute_predicate('$partition_foreign_args', 5)

$3:
	get_x_variable(5, 0)
	get_x_variable(0, 2)
	pseudo_instr2(69, 5, 1)
	put_constant('[]', 2)
	execute_predicate('type_exception', 3)
end('$partition_foreign_args'/5):



'$partition_foreign_arg'/5:

	switch_on_term(0, $6, 'fail', $3, $4, 'fail', 'fail')

$4:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$5, '+'/1:$1, '-'/1:$2])

$5:
	try(5, $1)
	trust($2)

$6:
	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_structure('+', 1, 0)
	unify_x_variable(0)
	get_list(2)
	unify_x_ref(2)
	unify_x_variable(5)
	get_structure('arg', 3, 2)
	unify_constant('in')
	unify_x_value(0)
	unify_x_value(1)
	get_x_value(5, 3)
	proceed

$2:
	get_structure('-', 1, 0)
	unify_x_variable(0)
	get_list(2)
	unify_x_ref(2)
	unify_x_variable(5)
	get_structure('arg', 3, 2)
	unify_constant('out')
	unify_x_value(0)
	unify_x_value(1)
	get_x_value(5, 3)
	proceed

$3:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('-', 1, 0)
	unify_x_variable(0)
	get_x_value(2, 3)
	get_list(4)
	unify_x_ref(2)
	unify_constant('[]')
	get_structure('arg', 3, 2)
	unify_constant('out')
	unify_x_value(0)
	unify_x_value(1)
	proceed
end('$partition_foreign_arg'/5):



'$write_extrn_c_fn'/4:


$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_constant('extern ', 0)
	call_predicate('$foreign_write', 1, 4)
	put_y_value(3, 0)
	call_predicate('$write_foreign_language', 1, 3)
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 3)
	put_y_value(2, 0)
	call_predicate('$write_return_type', 1, 2)
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	call_predicate('$foreign_write', 1, 1)
	put_constant('(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_foreign_arg_proto', 1, 0)
	put_constant(');
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_extrn_c_fn'/4):



'$write_return_type'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	put_constant('void', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('arg', 3, 0)
	unify_void(1)
	unify_x_variable(0)
	unify_void(1)
	execute_predicate('$write_type', 1)
end('$write_return_type'/1):



'$write_foreign_arg_proto'/1:

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
	put_constant('void', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('arg', 3, 0)
	unify_x_variable(1)
	unify_x_variable(0)
	unify_void(1)
	neck_cut
	execute_predicate('$write_foreign_prototype', 2)

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(1)
	unify_y_variable(0)
	get_structure('arg', 3, 0)
	unify_x_variable(1)
	unify_x_variable(0)
	unify_void(1)
	call_predicate('$write_foreign_prototype', 2, 1)
	put_constant(', ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_foreign_arg_proto', 1)
end('$write_foreign_arg_proto'/1):



'$write_foreign_prototype'/2:


$1:
	allocate(1)
	get_y_variable(0, 1)
	call_predicate('$write_type', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_inout', 1)
end('$write_foreign_prototype'/2):



'$write_inout'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'out':$1, 'in':$2])

$4:
	try(1, $1)
	trust($2)

$1:
	get_constant('out', 0)
	put_constant('*', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_constant('in', 0)
	proceed
end('$write_inout'/1):



'$gen_foreign_functions'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_constant('[]', 2)
	get_constant('[]', 3)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_list(2)
	unify_x_variable(2)
	unify_y_variable(1)
	get_list(3)
	unify_x_variable(3)
	unify_y_variable(0)
	call_predicate('$gen_foreign_function', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$gen_foreign_functions', 4)
end('$gen_foreign_functions'/4):



'$gen_foreign_function'/4:


$1:
	allocate(4)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_variable(2, 2)
	get_y_variable(3, 3)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(2)
	unify_x_ref(2)
	get_list(2)
	unify_constant('_interface')
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	get_y_value(3, 0)
	put_constant('
extern "C" bool
', 0)
	call_predicate('$foreign_write', 1, 4)
	put_y_value(3, 0)
	call_predicate('$foreign_write', 1, 3)
	put_constant('(ForeignInterface* fi)
{
 bool result = true;
', 0)
	call_predicate('$foreign_write', 1, 3)
	put_y_value(1, 0)
	call_predicate('$write_foreign_args', 1, 3)
	put_y_value(0, 0)
	call_predicate('$write_foreign_args', 1, 3)
	put_y_value(1, 0)
	call_predicate('$write_pval_args', 1, 3)
	put_y_value(0, 0)
	call_predicate('$write_pval_args', 1, 3)
	put_y_value(1, 0)
	call_predicate('$write_output_args', 1, 3)
	put_y_value(0, 0)
	call_predicate('$write_output_args', 1, 3)
	put_constant('
', 0)
	call_predicate('$foreign_write', 1, 3)
	put_y_value(1, 0)
	call_predicate('$get_foreign_values', 1, 3)
	put_y_value(0, 0)
	call_predicate('$get_foreign_values', 1, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	call_predicate('$write_foreign_call', 3, 2)
	put_y_value(1, 0)
	call_predicate('$make_output_values', 1, 1)
	put_y_value(0, 0)
	call_predicate('$make_output_values', 1, 0)
	put_constant('
 return(result);
}
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$gen_foreign_function'/4):



'$write_foreign_args'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(0)
	get_structure('arg', 3, 0)
	unify_void(1)
	unify_y_variable(2)
	unify_y_variable(1)
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 3)
	put_y_value(2, 0)
	call_predicate('$write_type', 1, 3)
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$write_foreign_val', 2, 1)
	put_constant(';
', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_foreign_args', 1)
end('$write_foreign_args'/1):



'$write_foreign_val'/2:


$1:
	allocate(1)
	get_y_variable(0, 1)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_foreign_val'/2):



'$write_output_args'/1:

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
	call_predicate('$write_output_arg', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_output_args', 1)
end('$write_output_args'/1):



'$write_output_arg'/1:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$4, 'arg'/3:$5])

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
	get_structure('arg', 3, 0)
	unify_constant('out')
	unify_void(1)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	put_constant(' Object* ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 0)
	put_constant(';
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$2:
	get_structure('arg', 3, 0)
	unify_void(3)
	proceed
end('$write_output_arg'/1):



'$write_output_val'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('outarg', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_output_val'/1):



'$write_pval_args'/1:

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
	call_predicate('$write_pval_arg', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_pval_args', 1)
end('$write_pval_args'/1):



'$write_pval_arg'/1:


$1:
	get_structure('arg', 3, 0)
	unify_void(2)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	put_constant(' Object* ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 0)
	put_constant(';
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_pval_arg'/1):



'$write_pval'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('object', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_pval'/1):



'$get_foreign_values'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	put_constant('
', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	call_predicate('$get_foreign_value', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$get_foreign_values', 1)
end('$get_foreign_values'/1):



'$get_foreign_value'/1:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$4, 'arg'/3:$5])

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
	get_structure('arg', 3, 0)
	unify_constant('in')
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	neck_cut
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 2)
	put_constant(' = ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(0, 0)
	call_predicate('$write_foreign_reg', 1, 2)
	put_constant(';
 if (!', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 2)
	put_constant('->', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	call_predicate('$type_check', 1, 2)
	put_constant(')
 {
  return(false);
 }
 ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$get_foreign_val', 2)

$2:
	get_structure('arg', 3, 0)
	unify_constant('out')
	unify_void(1)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 1)
	put_constant(' = ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_foreign_reg', 1, 0)
	put_constant(';
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$get_foreign_value'/1):



'$get_foreign_val'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'float':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_constant('float', 0)
	neck_cut
	put_constant('if (', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 2)
	put_constant('->', 0)
	call_predicate('$foreign_write', 1, 2)
	put_constant('integer', 0)
	call_predicate('$type_check', 1, 2)
	put_constant(')
 {
  ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$write_foreign_val', 2, 2)
	put_constant(' = ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(0, 1)
	put_constant('integer', 0)
	call_predicate('$extract_value', 2, 2)
	put_constant(';
 }
 else
 {
  ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$write_foreign_val', 2, 2)
	put_constant(' = ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$extract_value', 2, 0)
	put_constant(';
 }
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	call_predicate('$write_foreign_val', 2, 2)
	put_constant(' = ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$extract_value', 2, 0)
	put_constant(';
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$get_foreign_val'/2):



'$write_foreign_reg'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('fi->getXReg(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$foreign_write', 1, 0)
	put_constant(')', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_foreign_reg'/1):



'$write_foreign_call'/3:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(0, 1)
	get_y_variable(1, 2)
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 3)
	put_y_value(2, 0)
	call_predicate('$write_return_val', 1, 2)
	put_y_value(1, 0)
	call_predicate('$foreign_write', 1, 1)
	put_constant('(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_foreign_call_args', 1, 0)
	put_constant(');
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_foreign_call'/3):



'$write_return_val'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('arg', 3, 0)
	unify_void(1)
	unify_x_variable(0)
	unify_x_variable(1)
	allocate(0)
	call_predicate('$write_foreign_val', 2, 0)
	put_constant(' = ', 0)
	deallocate
	execute_predicate('$foreign_write', 1)
end('$write_return_val'/1):



'$write_foreign_call_args'/1:

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
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	neck_cut
	execute_predicate('$write_foreign_call_arg', 1)

$3:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	call_predicate('$write_foreign_call_arg', 1, 1)
	put_constant(', ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_foreign_call_args', 1)
end('$write_foreign_call_args'/1):



'$write_foreign_call_arg'/1:


$1:
	get_structure('arg', 3, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	call_predicate('$write_foreign_address', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$write_foreign_val', 2)
end('$write_foreign_call_arg'/1):



'$write_foreign_address'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'out':$1, 'in':$2])

$4:
	try(1, $1)
	trust($2)

$1:
	get_constant('out', 0)
	put_constant('&', 0)
	execute_predicate('$foreign_write', 1)

$2:
	get_constant('in', 0)
	proceed
end('$write_foreign_address'/1):



'$make_output_values'/1:

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
	call_predicate('$make_output_value', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$make_output_values', 1)
end('$make_output_values'/1):



'$make_output_value'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'arg'/3:$5])

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
	get_structure('arg', 3, 0)
	unify_constant('out')
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	neck_cut
	put_constant(' ', 0)
	call_predicate('$foreign_write', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$make_term', 2, 1)
	put_constant(');
 result = result && fi->unify(', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_pval', 1, 1)
	put_constant(', ', 0)
	call_predicate('$foreign_write', 1, 1)
	put_y_value(0, 0)
	call_predicate('$write_output_val', 1, 0)
	put_constant(');
', 0)
	deallocate
	execute_predicate('$foreign_write', 1)

$2:
	proceed
end('$make_output_value'/1):



'load_foreign'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('load_foreign', 3)
end('load_foreign'/2):



'load_foreign'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(2, 3)
	neck_cut
	put_list(0)
	set_x_value(3)
	set_constant('[]')
	execute_predicate('$load_foreign', 3)

$2:
	execute_predicate('$load_foreign', 3)
end('load_foreign'/3):



'$load_foreign/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_constant('atom', 0)
	call_predicate('application', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$load_foreign/3$0'/1):



'$load_foreign/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(50, 0)
	neck_cut
	fail

$2:
	proceed
end('$load_foreign/3$1'/1):



'$load_foreign'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('load_foreign')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(2)
	put_structure(3, 6)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(3)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('load_foreign')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(2)
	put_structure(3, 6)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(3)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('load_foreign')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(2)
	put_structure(3, 6)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(3)
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_level(5)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(3, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 6)
	pseudo_instr1(50, 24)
	put_y_value(2, 1)
	put_constant('atom', 0)
	call_predicate('application', 2, 6)
	cut(5)
	put_y_value(4, 0)
	put_structure(3, 2)
	set_constant('load_foreign')
	set_y_value(3)
	set_y_value(4)
	set_y_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(3)
	set_x_value(4)
	set_x_value(5)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(1, 4)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 6)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(5)
	set_x_value(6)
	put_list(5)
	set_x_value(4)
	set_x_value(3)
	put_structure(3, 1)
	set_constant('type_exception')
	set_x_value(2)
	set_integer(2)
	set_x_value(5)
	put_y_value(1, 2)
	put_y_value(0, 3)
	call_predicate('$foreign_funcs', 4, 4)
	pseudo_instr4(3, 23, 22, 21, 20)
	deallocate
	proceed

$5:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('$load_foreign/3$0', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('load_foreign')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(2)
	put_structure(3, 6)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(3)
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
	call_predicate('$load_foreign/3$1', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('load_foreign')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(2)
	put_structure(3, 6)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(3)
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_integer(2, 1)
	deallocate
	execute_predicate('type_exception', 4)

$7:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('load_foreign')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(1)
	put_structure(3, 1)
	set_constant('load_foreign')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(2)
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(2)
	put_structure(3, 6)
	set_constant('load_foreign')
	set_x_value(1)
	set_x_value(4)
	set_x_value(5)
	put_list(2)
	set_x_value(6)
	set_x_value(3)
	put_integer(3, 1)
	execute_predicate('type_exception', 3)
end('$load_foreign'/3):



'$foreign_funcs'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 2)
	get_constant('[]', 3)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_list(2)
	unify_x_variable(2)
	unify_y_variable(1)
	get_list(3)
	unify_x_variable(3)
	unify_y_variable(0)
	call_predicate('$c_name', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$foreign_funcs', 4)
end('$foreign_funcs'/4):



'$c_name'/4:

	switch_on_term(0, $10, $9, $9, $5, $9, $9)

$5:
	switch_on_structure(0, 8, ['$default':$9, '$'/0:$6, '='/2:$7, '/'/2:$8])

$6:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(4, $1)
	retry($2)
	trust($4)

$8:
	try(4, $1)
	retry($3)
	trust($4)

$9:
	try(4, $1)
	trust($4)

$10:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	pseudo_instr1(1, 4)
	neck_cut
	execute_predicate('call', 1)

$2:
	get_structure('=', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_x_value(0, 2)
	get_x_value(4, 3)
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	pseudo_instr1(2, 4)
	neck_cut
	proceed

$3:
	get_x_value(0, 2)
	get_structure('/', 2, 0)
	unify_x_value(3)
	unify_x_variable(0)
	pseudo_instr1(2, 3)
	pseudo_instr1(3, 0)
	neck_cut
	proceed

$4:
	get_x_variable(0, 1)
	execute_predicate('call', 1)
end('$c_name'/4):



'$convert_foreign'/3:


$1:
	allocate(7)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	put_y_variable(6, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	put_y_variable(1, 3)
	call_predicate('$foreign_functions', 4, 7)
	put_y_value(4, 0)
	put_y_value(6, 1)
	put_y_value(0, 2)
	call_predicate('$interface_file', 3, 7)
	put_y_value(6, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$gen_foreign_file', 5, 7)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('qcc -o ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(0)
	unify_x_ref(2)
	get_list(2)
	unify_constant(' ')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(6)
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	pseudo_instr2(46, 0, 1)
	put_integer(0, 0)
	get_x_value(1, 0)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(0)
	set_y_value(3)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(5, 4)
	deallocate
	execute_predicate('$convert_foreign_call', 5)
end('$convert_foreign'/3):



'$convert_foreign_call/5$0/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_integer(-1, 2)
	get_x_value(0, 2)
	neck_cut
	put_x_variable(2, 0)
	get_structure('open', 3, 0)
	unify_x_value(1)
	unify_constant('write')
	unify_void(1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened stream ')
	set_x_value(3)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('$convert_foreign_call/5$0/3$0'/2):



'$convert_foreign_call/5$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	get_x_variable(0, 2)
	pseudo_instr3(31, 3, 1, 2)
	get_x_value(0, 2)
	neck_cut
	put_x_value(3, 1)
	execute_predicate('$convert_foreign_call/5$0/3$0', 2)

$2:
	put_structure(3, 1)
	set_constant('open')
	set_x_value(0)
	set_constant('write')
	set_void(1)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('$convert_foreign_call/5$0'/3):



'$convert_foreign_call'/5:


$1:
	allocate(8)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	put_x_variable(2, 3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.ql')
	unify_constant('[]')
	pseudo_instr2(31, 2, 1)
	get_y_variable(7, 1)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	put_x_variable(2, 2)
	put_constant('write', 0)
	call_predicate('$iomode', 3, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(1, 2)
	call_predicate('$convert_foreign_call/5$0', 3, 6)
	put_y_value(1, 0)
	put_constant('?- load_foreign(
 [
', 1)
	call_predicate('write_atom', 2, 6)
	put_y_value(1, 0)
	put_y_value(5, 1)
	call_predicate('$write_foreign_list', 2, 5)
	put_y_value(1, 0)
	put_constant('
 ],
 [
', 1)
	call_predicate('write_atom', 2, 5)
	put_y_value(1, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('$write_foreign_decl', 3, 3)
	put_y_value(1, 0)
	put_constant('
 ],
 [
', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$write_foreign_list', 2, 2)
	put_y_value(1, 0)
	put_constant(']).', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(0, 1)
	put_constant('true', 0)
	call_predicate('$boolnum', 2, 2)
	pseudo_instr2(40, 21, 20)
	deallocate
	proceed
end('$convert_foreign_call'/5):



'$write_foreign_list'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_list(1)
	unify_y_variable(0)
	unify_constant('[]')
	neck_cut
	put_constant(' ', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('writeq_atom', 2)

$3:
	allocate(3)
	get_y_variable(1, 0)
	get_list(1)
	unify_y_variable(2)
	unify_y_variable(0)
	put_constant(' ', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('writeq_atom', 2, 2)
	put_y_value(1, 0)
	put_constant(',
', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$write_foreign_list', 2)
end('$write_foreign_list'/2):



'$write_foreign_decl'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(0, 0)
	get_list(1)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	get_list(2)
	unify_y_variable(1)
	unify_constant('[]')
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	pseudo_instr3(0, 0, 23, 22)
	put_y_value(0, 0)
	put_constant(' ', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(0, 0)
	put_constant('/', 1)
	call_predicate('write_atom', 2, 3)
	pseudo_instr2(18, 20, 22)
	put_y_value(0, 0)
	put_constant(' = ', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_y_value(0, 0)
	put_constant('_interface', 1)
	deallocate
	execute_predicate('write_atom', 2)

$2:
	allocate(6)
	get_y_variable(2, 0)
	get_list(1)
	unify_x_ref(0)
	unify_y_variable(1)
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	get_list(2)
	unify_y_variable(3)
	unify_y_variable(0)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	pseudo_instr3(0, 0, 25, 24)
	put_y_value(2, 0)
	put_constant(' ', 1)
	call_predicate('write_atom', 2, 6)
	put_y_value(2, 0)
	put_y_value(5, 1)
	call_predicate('write_atom', 2, 5)
	put_y_value(2, 0)
	put_constant('/', 1)
	call_predicate('write_atom', 2, 5)
	pseudo_instr2(18, 22, 24)
	put_y_value(2, 0)
	put_constant(' = ', 1)
	call_predicate('write_atom', 2, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	put_constant('_interface,
', 1)
	call_predicate('write_atom', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$write_foreign_decl', 3)
end('$write_foreign_decl'/3):



