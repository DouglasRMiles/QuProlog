'retract/1$0'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ':-'/2:$5])

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
	get_structure(':-', 2, 0)
	unify_void(2)
	neck_cut
	fail

$2:
	proceed
end('retract/1$0'/1):



'retract'/1:

	switch_on_term(0, $9, $8, $8, $5, $8, $8)

$5:
	switch_on_structure(0, 4, ['$default':$8, '$'/0:$6, ':-'/2:$7])

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

$8:
	try(1, $1)
	retry($3)
	trust($4)

$9:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('retract')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('retract')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure(':-', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	pseudo_instr1(46, 0)
	neck_cut
	execute_predicate('$retract', 2)

$3:
	allocate(2)
	get_y_variable(0, 0)
	pseudo_instr1(46, 20)
	get_y_level(1)
	call_predicate('retract/1$0', 1, 2)
	cut(1)
	put_y_value(0, 0)
	put_constant('true', 1)
	deallocate
	execute_predicate('$retract', 2)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('retract')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('retract')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('retract'/1):



'$retract/2$0'/0:

	try(0, $1)
	trust($2)

$1:
	proceed

$2:
	fail
end('$retract/2$0'/0):



'$retract/2$1'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'true':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('true', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	deallocate
	proceed
end('$retract/2$1'/2):



'$retract'/2:


$1:
	allocate(8)
	get_y_variable(3, 1)
	get_y_level(1)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('$correct_name', 2, 8)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 24, 0, 1)
	pseudo_instr3(66, 0, 1, 2)
	get_y_value(7, 2)
	pseudo_instr4(15, 24, 27, 0, 1)
	get_y_value(6, 0)
	get_y_value(5, 1)
	call_predicate('$retract/2$0', 0, 8)
	put_y_value(6, 0)
	put_y_value(7, 1)
	put_y_value(2, 2)
	put_y_value(5, 3)
	put_y_value(0, 4)
	call_predicate('$get_clause_ref', 5, 5)
	pseudo_instr3(57, 22, 24, 0)
	pseudo_instr2(67, 24, 1)
	put_y_value(3, 3)
	put_constant('[]', 2)
	call_predicate('$post_trans_decompile', 4, 3)
	pseudo_instr1(12, 22)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$retract/2$1', 2)
end('$retract'/2):



'$retract2'/4:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 2)
	get_x_variable(4, 3)
	pseudo_instr4(15, 22, 1, 0, 2)
	get_x_variable(3, 2)
	put_y_variable(0, 2)
	call_predicate('$get_clause_ref', 5, 3)
	pseudo_instr3(57, 20, 22, 0)
	pseudo_instr2(67, 22, 1)
	put_y_value(1, 3)
	put_constant('[]', 2)
	call_predicate('$post_trans_decompile', 4, 1)
	pseudo_instr1(12, 20)
	deallocate
	proceed
end('$retract2'/4):



'retractall'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(46, 0)
	put_x_variable(1, 1)
	allocate(0)
	call_predicate('$retract', 2, 0)
	fail

$2:
	proceed
end('retractall'/1):



'abolish'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '/'/2:$5])

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
	get_structure('/', 2, 0)
	allocate(5)
	unify_y_variable(3)
	unify_y_variable(2)
	pseudo_instr1(2, 23)
	pseudo_instr1(3, 22)
	get_y_level(4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 5)
	pseudo_instr3(33, 21, 20, 0)
	put_integer(1, 1)
	get_x_value(0, 1)
	cut(4)
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 23, 22)
	call_predicate('retractall', 1, 2)
	pseudo_instr2(29, 21, 20)
	deallocate
	proceed

$2:
	proceed
end('abolish'/1):



