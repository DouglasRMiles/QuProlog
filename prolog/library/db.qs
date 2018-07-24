'inline'/2:


$1:
	put_constant('true', 2)
	execute_predicate('inline', 3)
end('inline'/2):



'inline/3$0'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	allocate(2)
	get_y_level(0)
	put_structure(4, 0)
	set_constant('$inline')
	set_x_value(4)
	set_y_variable(1)
	set_void(2)
	put_x_variable(1, 1)
	call_predicate('clause', 2, 2)
	pseudo_instr1(1, 21)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(4, 4)
	set_constant('$inline')
	set_x_value(0)
	set_void(1)
	set_x_variable(5)
	set_x_value(1)
	put_list(1)
	set_x_value(0)
	set_x_value(2)
	put_structure(2, 0)
	set_constant('=..')
	set_x_value(5)
	set_x_value(1)
	put_structure(2, 1)
	set_constant(',')
	set_x_value(0)
	set_x_value(3)
	put_structure(2, 0)
	set_constant(':-')
	set_x_value(4)
	set_x_value(1)
	execute_predicate('assert', 1)
end('inline/3$0'/4):



'inline/3$1'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	allocate(1)
	get_y_level(0)
	put_structure(4, 0)
	set_constant('$inline')
	set_x_value(5)
	set_x_value(1)
	set_void(2)
	put_x_variable(1, 1)
	call_predicate('clause', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(4, 5)
	set_constant('$inline')
	set_x_value(0)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(2, 0)
	set_constant(':-')
	set_x_value(5)
	set_x_value(4)
	execute_predicate('assert', 1)
end('inline/3$1'/5):



'inline'/3:

	switch_on_term(0, $8, $7, $7, $4, $7, $7)

$4:
	switch_on_structure(0, 4, ['$default':$7, '$'/0:$5, '@'/2:$6])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$6:
	try(3, $1)
	retry($2)
	trust($3)

$7:
	try(3, $1)
	trust($3)

$8:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('inline')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('+')
	set_constant('term')
	put_structure(1, 3)
	set_constant('+')
	set_constant('term')
	put_structure(3, 4)
	set_constant('inline')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure('@', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_x_variable(3, 2)
	neck_cut
	put_x_value(4, 2)
	execute_predicate('inline/3$0', 4)

$3:
	get_x_variable(5, 0)
	get_x_variable(3, 1)
	get_x_variable(4, 2)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 5, 0, 1)
	put_x_value(5, 2)
	execute_predicate('inline/3$1', 5)
end('inline'/3):



