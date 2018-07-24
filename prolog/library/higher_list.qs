'application'/2:


$1:
	get_x_variable(2, 1)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	execute_predicate('map', 2)
end('application'/2):



'map'/3:


$1:
	get_x_variable(3, 1)
	put_list(4)
	set_x_value(2)
	set_constant('[]')
	put_list(1)
	set_x_value(3)
	set_x_value(4)
	execute_predicate('map', 2)
end('map'/3):



'map'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(0, 1)
	execute_predicate('$all_empty', 1)

$2:
	allocate(4)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(2, 19)
	put_y_variable(3, 1)
	put_y_variable(0, 2)
	call_predicate('$heads_and_tails', 3, 4)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(1)
	set_y_value(3)
	call_predicate('=..', 2, 3)
	put_y_value(2, 0)
	call_predicate('call_with_inlining', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('map', 2)
end('map'/2):



'$all_empty'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_constant('[]')
	unify_x_variable(0)
	execute_predicate('$all_empty', 1)
end('$all_empty'/1):



'$heads_and_tails'/3:

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
	unify_x_ref(3)
	unify_x_variable(0)
	get_list(3)
	unify_x_variable(3)
	unify_x_variable(4)
	get_list(1)
	unify_x_value(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(4)
	unify_x_variable(2)
	execute_predicate('$heads_and_tails', 3)
end('$heads_and_tails'/3):



'filter'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	neck_cut
	proceed

$2:
	allocate(5)
	get_y_variable(1, 0)
	get_list(1)
	unify_y_variable(3)
	unify_y_variable(0)
	get_y_variable(2, 2)
	put_integer(1, 1)
	pseudo_instr3(38, 21, 1, 0)
	put_integer(1, 1)
	pseudo_instr3(39, 0, 1, 23)
	get_y_level(4)
	call_predicate('call_with_inlining', 1, 5)
	cut(4)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(3)
	unify_x_variable(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('filter', 3)

$3:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('filter', 3)
end('filter'/3):



'fold'/4:


$1:
	execute_predicate('fold_right', 4)
end('fold'/4):



'fold_right'/4:

	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 2)
	get_x_value(1, 3)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_list(2)
	unify_y_variable(2)
	unify_x_variable(2)
	get_y_variable(0, 3)
	put_y_variable(1, 3)
	call_predicate('fold_right', 4, 4)
	put_integer(3, 1)
	pseudo_instr3(38, 23, 1, 0)
	put_integer(1, 1)
	pseudo_instr3(39, 0, 1, 22)
	put_integer(2, 1)
	pseudo_instr3(39, 0, 1, 21)
	put_integer(3, 1)
	pseudo_instr3(39, 0, 1, 20)
	deallocate
	execute_predicate('call_with_inlining', 1)
end('fold_right'/4):



'fold_left'/4:

	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 2)
	get_x_value(1, 3)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_list(2)
	unify_x_variable(2)
	unify_y_variable(2)
	get_y_variable(1, 3)
	put_integer(3, 3)
	pseudo_instr3(38, 23, 3, 0)
	put_integer(1, 3)
	pseudo_instr3(39, 0, 3, 1)
	put_integer(2, 1)
	pseudo_instr3(39, 0, 1, 2)
	put_integer(3, 1)
	put_y_variable(0, 19)
	pseudo_instr3(39, 0, 1, 20)
	call_predicate('call_with_inlining', 1, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('fold_left', 4)
end('fold_left'/4):



'front_with'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	neck_cut
	proceed

$2:
	allocate(5)
	get_y_variable(1, 0)
	get_list(1)
	unify_y_variable(3)
	unify_y_variable(0)
	get_y_variable(2, 2)
	put_integer(1, 1)
	pseudo_instr3(38, 21, 1, 0)
	put_integer(1, 1)
	pseudo_instr3(39, 0, 1, 23)
	get_y_level(4)
	call_predicate('call_with_inlining', 1, 5)
	cut(4)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(3)
	unify_x_variable(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('front_with', 3)

$3:
	get_constant('[]', 2)
	proceed
end('front_with'/3):



'after_with'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 1)
	get_constant('[]', 2)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(2, 0)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	put_integer(1, 2)
	pseudo_instr3(38, 22, 2, 0)
	put_integer(1, 2)
	pseudo_instr3(39, 0, 2, 1)
	get_y_level(3)
	call_predicate('call_with_inlining', 1, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('after_with', 3)

$3:
	get_x_value(1, 2)
	proceed
end('after_with'/3):



