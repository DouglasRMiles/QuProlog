'atom_concat/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(1, 1)
	proceed
end('atom_concat/3$0'/2):



'atom_concat/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('atom_concat/3$1'/1):



'atom_concat/3$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('atom_concat/3$2'/1):



'atom_concat'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	pseudo_instr1(2, 0)
	pseudo_instr1(2, 1)
	neck_cut
	put_x_variable(4, 5)
	get_list(5)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_constant('[]')
	pseudo_instr2(31, 4, 3)
	get_x_value(2, 3)
	proceed

$2:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(2, 1)
	get_y_variable(3, 2)
	pseudo_instr1(2, 23)
	neck_cut
	pseudo_instr2(30, 23, 0)
	get_y_variable(1, 0)
	put_y_value(1, 1)
	put_y_variable(0, 2)
	put_integer(0, 0)
	call_predicate('between', 3, 5)
	put_integer(1, 0)
	pseudo_instr4(2, 23, 0, 20, 24)
	pseudo_instr3(3, 21, 20, 0)
	pseudo_instr2(69, 20, 1)
	pseudo_instr4(2, 23, 1, 0, 22)
	pseudo_instr2(30, 22, 0)
	get_x_variable(1, 0)
	put_structure(2, 0)
	set_constant('+')
	set_x_value(1)
	set_y_value(0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('=:=', 2)

$3:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(1, 20)
	get_y_level(3)
	call_predicate('atom_concat/3$0', 2, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('atom_concat')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('atom_concat')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('-')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('atom_concat')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(3, 1)
	deallocate
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(3, 0)
	pseudo_instr1(46, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('atom_concat')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('atom_concat')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('-')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('atom_concat')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(3, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)

$5:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('atom_concat/3$1', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('atom_concat')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('atom_concat')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('-')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('atom_concat')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(1, 0)
	call_predicate('atom_concat/3$2', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('atom_concat')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('atom_concat')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(1)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('-')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('atom_concat')
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_x_value(1)
	put_integer(2, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)
end('atom_concat'/3):



'sub_atom'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	pseudo_instr1(2, 23)
	pseudo_instr1(2, 20)
	neck_cut
	pseudo_instr2(30, 23, 0)
	pseudo_instr2(30, 20, 1)
	get_y_value(1, 1)
	put_x_variable(2, 3)
	get_structure('+', 2, 3)
	unify_x_value(0)
	unify_integer(1)
	pseudo_instr3(3, 2, 21, 1)
	put_y_value(2, 2)
	put_integer(1, 0)
	call_predicate('between', 3, 4)
	pseudo_instr4(2, 23, 22, 21, 20)
	deallocate
	proceed

$2:
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	pseudo_instr1(3, 2)
	neck_cut
	pseudo_instr2(30, 0, 4)
	pseudo_instr3(2, 1, 2, 5)
	pseudo_instr2(70, 5, 6)
	get_x_variable(5, 6)
	pseudo_instr2(2, 5, 4)
	put_x_variable(4, 4)
	pseudo_instr4(2, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed

$3:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	pseudo_instr1(2, 23)
	neck_cut
	pseudo_instr2(30, 23, 0)
	pseudo_instr2(69, 0, 1)
	get_y_variable(4, 1)
	put_y_value(2, 2)
	put_integer(1, 0)
	call_predicate('between', 3, 5)
	pseudo_instr3(3, 24, 22, 0)
	get_x_variable(1, 0)
	put_y_value(1, 2)
	put_integer(0, 0)
	call_predicate('between', 3, 4)
	put_x_variable(0, 0)
	pseudo_instr4(2, 23, 22, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$4:
	get_x_variable(4, 0)
	pseudo_instr1(1, 4)
	neck_cut
	put_structure(4, 0)
	set_constant('sub_atom')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_constant('atom')
	put_structure(4, 5)
	set_constant('sub_atom')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	get_x_variable(4, 0)
	put_structure(4, 0)
	set_constant('sub_atom')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('?')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_constant('atom')
	put_structure(4, 5)
	set_constant('sub_atom')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('sub_atom'/4):



