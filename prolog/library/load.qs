'load/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_integer(1, 3)
	put_constant('/', 4)
	pseudo_instr4(1, 0, 3, 4, 2)
	neck_cut
	execute_predicate('$absolute_load', 2)

$2:
	execute_predicate('$search_load', 2)
end('load/1$0'/2):



'load/1$1'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('fail', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('call_predicate', 1)
end('load/1$1'/1):



'load/1$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('load/1$2'/1):



'load'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(2, 0)
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('load/1$0', 2, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('load/1$1', 1)

$2:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('load')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('load')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('load/1$2', 1, 2)
	cut(1)
	put_structure(1, 0)
	set_constant('load')
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('load')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$4:
	put_structure(1, 1)
	set_constant('load')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('load'/1):



'$absolute_load'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(30, 0, 2)
	put_integer(2, 4)
	pseudo_instr3(3, 2, 4, 3)
	get_x_variable(2, 3)
	put_integer(3, 3)
	put_x_variable(4, 4)
	pseudo_instr4(2, 0, 2, 3, 4)
	put_constant('.qo', 2)
	get_x_value(4, 2)
	neck_cut
	pseudo_instr2(83, 0, 2)
	get_x_value(1, 2)
	proceed

$2:
	put_x_variable(3, 4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('.qo')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_variable(0, 2)
	pseudo_instr2(83, 0, 2)
	get_x_value(1, 2)
	proceed
end('$absolute_load'/2):



'$search_load'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(0, 1)
	put_y_variable(1, 0)
	call_predicate('$search_dir', 1, 3)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(1)
	unify_x_ref(2)
	get_list(2)
	unify_constant('/')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(2)
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$absolute_load', 2)
end('$search_load'/2):



'$search_dir'/1:


$1:
	get_x_variable(2, 0)
	pseudo_instr1(10, 0)
	put_integer(1, 1)
	execute_predicate('$search_dir1', 3)
end('$search_dir'/1):



'$search_dir1/3$0'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr3(3, 0, 1, 4)
	get_x_variable(0, 4)
	pseudo_instr4(2, 2, 1, 0, 3)
	proceed

$2:
	get_x_variable(4, 0)
	get_x_variable(0, 2)
	get_x_variable(2, 3)
	pseudo_instr2(69, 4, 1)
	execute_predicate('$search_dir1', 3)
end('$search_dir1/3$0'/4):



'$search_dir1'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(3, 2)
	put_constant(':', 2)
	pseudo_instr4(1, 4, 1, 2, 0)
	neck_cut
	put_x_value(4, 2)
	execute_predicate('$search_dir1/3$0', 4)

$2:
	pseudo_instr2(30, 0, 3)
	pseudo_instr3(3, 3, 1, 4)
	get_x_variable(3, 4)
	pseudo_instr2(69, 3, 4)
	get_x_variable(3, 4)
	pseudo_instr4(2, 0, 1, 3, 2)
	proceed
end('$search_dir1'/3):



'$basename'/2:


$1:
	get_x_variable(2, 1)
	put_integer(1, 1)
	execute_predicate('$basename1', 3)
end('$basename'/2):



'$basename1/3$0'/4:

	try(4, $1)
	trust($2)

$1:
	put_integer(2, 5)
	pseudo_instr3(3, 0, 5, 4)
	get_x_variable(0, 4)
	put_integer(3, 4)
	put_x_variable(5, 5)
	pseudo_instr4(2, 1, 0, 4, 5)
	put_constant('.qo', 0)
	get_x_value(5, 0)
	neck_cut
	put_integer(3, 1)
	pseudo_instr3(3, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$2:
	get_x_value(3, 2)
	proceed
end('$basename1/3$0'/4):



'$basename1'/3:

	try(3, $1)
	trust($2)

$1:
	put_constant('/', 4)
	pseudo_instr4(1, 0, 1, 4, 3)
	get_x_variable(1, 3)
	neck_cut
	pseudo_instr2(69, 1, 3)
	get_x_variable(1, 3)
	execute_predicate('$basename1', 3)

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	pseudo_instr2(30, 23, 0)
	pseudo_instr3(3, 0, 22, 1)
	pseudo_instr2(69, 1, 2)
	put_y_value(3, 1)
	put_y_variable(1, 3)
	call_predicate('$basename1/3$0', 4, 4)
	pseudo_instr4(2, 23, 22, 21, 20)
	deallocate
	proceed
end('$basename1'/3):



'$dynamic_load'/2:


$1:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	pseudo_instr1(2, 24)
	pseudo_instr1(3, 23)
	put_constant('$dynamic_lib', 1)
	put_integer(2, 2)
	pseudo_instr3(33, 1, 2, 0)
	put_integer(1, 1)
	get_x_value(0, 1)
	get_y_level(1)
	put_y_variable(0, 0)
	put_y_variable(2, 1)
	call_predicate('$dynamic_lib', 2, 5)
	put_structure(2, 0)
	set_constant('/')
	set_y_value(4)
	set_y_value(3)
	put_y_value(2, 1)
	call_predicate('member', 2, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('load', 1)
end('$dynamic_load'/2):



'define_dynamic_lib/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('define_dynamic_lib/2$0'/1):



'define_dynamic_lib'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(2, 21)
	get_y_level(2)
	put_constant('$dynamic_pred', 0)
	call_predicate('application', 2, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('$dynamic_lib')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('define_dynamic_lib')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 4)
	set_constant('define_dynamic_lib')
	set_x_value(1)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('define_dynamic_lib')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 4)
	set_constant('define_dynamic_lib')
	set_x_value(1)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('define_dynamic_lib/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('define_dynamic_lib')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 4)
	set_constant('define_dynamic_lib')
	set_x_value(1)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('define_dynamic_lib')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 4)
	set_constant('define_dynamic_lib')
	set_x_value(1)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_structure(2, 1)
	set_constant('/')
	set_constant('atom')
	set_constant('arity')
	put_structure(1, 3)
	set_constant('list')
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('type_exception', 4)
end('define_dynamic_lib'/2):



'$dynamic_pred'/1:


$1:
	pseudo_instr1(0, 0)
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	proceed
end('$dynamic_pred'/1):



