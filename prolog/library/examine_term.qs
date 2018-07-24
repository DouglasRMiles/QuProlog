'number'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	proceed

$2:
	pseudo_instr1(85, 0)
	proceed
end('number'/1):



'ground/1$0'/2:

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
	pseudo_instr1(1, 2)
	neck_cut
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('ground/1$0', 2)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('ground/1$0', 2)
end('ground/1$0'/2):



'ground'/1:


$1:
	pseudo_instr2(111, 0, 1)
	get_x_variable(0, 1)
	pseudo_instr2(67, 0, 1)
	get_x_variable(0, 1)
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('ground/1$0', 2, 1)
	put_y_value(0, 0)
	get_constant('[]', 0)
	deallocate
	proceed
end('ground'/1):



