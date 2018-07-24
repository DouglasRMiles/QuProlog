'$escape_builtin'/1:


$1:
	get_x_variable(2, 0)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 2, 0, 1)
	execute_predicate('$escape_builtin', 2)
end('$escape_builtin'/1):



'$escape_builtin'/2:

	switch_on_term(0, $18, 'fail', 'fail', 'fail', 'fail', $17)

$17:
	switch_on_constant(0, 32, ['$default':'fail', 'true':$1, 'fail':$2, '$$get_level$$':$3, '$$get_level_ancestor$$':$4, '$$cut$$':$5, '$$cut_ancestor$$':$6, 'check_binder':$7, '$pseudo_instr0':$8, '$pseudo_instr1':$9, '$pseudo_instr2':$10, '$pseudo_instr3':$11, '$pseudo_instr4':$12, '$pseudo_instr5':$13, '$piarg':$14, '$pieq':$15, '$psi_life':$16])

$18:
	try(2, $1)
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
	trust($16)

$1:
	get_constant('true', 0)
	get_integer(0, 1)
	proceed

$2:
	get_constant('fail', 0)
	get_integer(0, 1)
	proceed

$3:
	get_constant('$$get_level$$', 0)
	get_integer(1, 1)
	proceed

$4:
	get_constant('$$get_level_ancestor$$', 0)
	get_integer(1, 1)
	proceed

$5:
	get_constant('$$cut$$', 0)
	get_integer(1, 1)
	proceed

$6:
	get_constant('$$cut_ancestor$$', 0)
	get_integer(1, 1)
	proceed

$7:
	get_constant('check_binder', 0)
	get_integer(1, 1)
	proceed

$8:
	get_constant('$pseudo_instr0', 0)
	get_integer(1, 1)
	proceed

$9:
	get_constant('$pseudo_instr1', 0)
	get_integer(2, 1)
	proceed

$10:
	get_constant('$pseudo_instr2', 0)
	get_integer(3, 1)
	proceed

$11:
	get_constant('$pseudo_instr3', 0)
	get_integer(4, 1)
	proceed

$12:
	get_constant('$pseudo_instr4', 0)
	get_integer(5, 1)
	proceed

$13:
	get_constant('$pseudo_instr5', 0)
	get_integer(6, 1)
	proceed

$14:
	get_constant('$piarg', 0)
	get_integer(2, 1)
	proceed

$15:
	get_constant('$pieq', 0)
	get_integer(1, 1)
	proceed

$16:
	get_constant('$psi_life', 0)
	get_integer(1, 1)
	proceed
end('$escape_builtin'/2):



'$colvars'/2:


$1:
	get_x_variable(2, 1)
	put_x_value(2, 1)
	put_constant('[]', 3)
	execute_predicate('$split_arg', 4)
end('$colvars'/2):



'$split_arg/4$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(4, 0)
	proceed

$2:
	pseudo_instr1(1, 0)
	proceed
end('$split_arg/4$0'/1):



'$split_arg/4$1/4$0/3$0'/3:

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
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	put_constant('[]', 2)
	get_x_value(3, 2)
	allocate(1)
	get_y_level(0)
	call_predicate('$compiler_member_eq', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$split_arg/4$1/4$0/3$0'/3):



'$split_arg/4$1/4$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$split_arg/4$1/4$0/3$0', 3, 1)
	cut(0)
	fail

$2:
	proceed
end('$split_arg/4$1/4$0'/3):



'$split_arg/4$1'/4:

	switch_on_term(0, $3, $1, $3, $1, $1, $1)

$3:
	try(4, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 3)
	get_y_level(2)
	call_predicate('$split_arg/4$1/4$0', 3, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_list(0)
	unify_x_value(1)
	unify_x_value(3)
	proceed
end('$split_arg/4$1'/4):



'$split_arg'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_value(2, 3)
	pseudo_instr1(43, 0)
	neck_cut
	proceed

$2:
	get_x_value(2, 3)
	pseudo_instr1(108, 0)
	neck_cut
	proceed

$3:
	allocate(6)
	get_y_variable(3, 1)
	get_y_variable(5, 2)
	get_y_variable(2, 3)
	pseudo_instr1(6, 0)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	put_y_variable(1, 2)
	call_predicate('$break_substitute', 3, 6)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(5, 2)
	put_y_value(0, 3)
	call_predicate('$split_arg', 4, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$split_arg', 4)

$4:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_level(4)
	call_predicate('$split_arg/4$0', 1, 5)
	cut(4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$split_arg/4$1', 4)

$5:
	get_x_variable(4, 0)
	allocate(6)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	pseudo_instr1(5, 4)
	neck_cut
	put_x_variable(0, 0)
	put_y_variable(5, 19)
	put_y_variable(1, 19)
	pseudo_instr4(7, 4, 0, 25, 21)
	put_y_variable(0, 19)
	put_y_variable(4, 3)
	call_predicate('$split_arg', 4, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('$split_arg', 4, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$split_arg', 4)

$6:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	put_x_variable(0, 0)
	put_y_variable(1, 19)
	pseudo_instr3(0, 24, 0, 21)
	put_y_variable(0, 3)
	call_predicate('$split_arg', 4, 5)
	put_y_value(1, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(0, 4)
	put_y_value(2, 5)
	put_integer(0, 0)
	deallocate
	execute_predicate('$split_avs', 6)
end('$split_arg'/4):



'$split_avs'/6:

	try(6, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	get_x_value(4, 5)
	neck_cut
	proceed

$2:
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_x_variable(2, 4)
	get_y_variable(2, 5)
	pseudo_instr2(69, 0, 1)
	get_y_variable(1, 1)
	pseudo_instr3(1, 21, 24, 0)
	put_y_value(3, 1)
	put_y_variable(0, 3)
	call_predicate('$split_arg', 4, 6)
	put_y_value(1, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(0, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$split_avs', 6)
end('$split_avs'/6):



'$obvarsmap_lookup'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	get_list(1)
	unify_x_ref(1)
	unify_void(1)
	get_structure('=', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$2:
	get_list(1)
	unify_x_ref(1)
	unify_void(1)
	get_structure('=', 2, 1)
	unify_x_variable(1)
	unify_x_variable(3)
	pseudo_instr3(6, 0, 1, 4)
	put_constant('true', 0)
	get_x_value(4, 0)
	neck_cut
	get_x_value(2, 3)
	proceed

$3:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('$obvarsmap_lookup', 3)
end('$obvarsmap_lookup'/3):



'$gc'/1:


$1:
	execute_predicate('$c_gc', 1)
end('$gc'/1):



'$c_gc'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$one_call', 1, 1)
	put_y_value(0, 1)
	put_constant('$gc', 0)
	call_predicate('$set', 2, 0)
	fail

$2:
	get_x_variable(1, 0)
	put_constant('$gc', 0)
	execute_predicate('$get', 2)
end('$c_gc'/1):



'$one_call'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '$compileclause'/3:$5])

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
	get_structure('$compileclause', 3, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	unify_x_variable(2)
	neck_cut
	execute_predicate('$compileclause', 3)

$2:
	allocate(1)
	get_y_level(0)
	call_predicate('call', 1, 1)
	cut(0)
	deallocate
	proceed
end('$one_call'/1):



'$set/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	put_structure(2, 0)
	set_constant('$set_access')
	set_x_value(1)
	set_void(1)
	execute_predicate('retract', 1)

$2:
	proceed
end('$set/2$0'/1):



'$set'/2:


$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('$set/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('$set_access')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)
end('$set'/2):



'$get'/2:


$1:
	execute_predicate('$set_access', 2)
end('$get'/2):



'$compiler_member_eq'/2:

	try(2, $1)
	trust($2)

$1:
	get_list(1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr3(6, 0, 1, 2)
	put_constant('true', 0)
	get_x_value(2, 0)
	proceed

$2:
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('$compiler_member_eq', 2)
end('$compiler_member_eq'/2):



'$compiler_union_list'/3:

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
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('$compiler_member_eq', 2, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$compiler_union_list', 3)

$3:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	execute_predicate('$compiler_union_list', 3)
end('$compiler_union_list'/3):



'$compiler_intersect_list'/3:

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
	get_constant('[]', 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_list(2)
	unify_x_value(0)
	unify_y_variable(0)
	get_y_level(3)
	call_predicate('$compiler_member_eq', 2, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$compiler_intersect_list', 3)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$compiler_intersect_list', 3)
end('$compiler_intersect_list'/3):



'$x_reg'/2:


$1:
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed
end('$x_reg'/2):



'$y_reg'/2:


$1:
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed
end('$y_reg'/2):



'$reg'/2:

	switch_on_term(0, $5, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$4, '$xreg'/1:$1, '$yreg'/1:$2])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$2:
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed
end('$reg'/2):



