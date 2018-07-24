'$internal_form'/2:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ':-'/2:$5])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$6:
	try(2, $1)
	trust($2)

$1:
	get_structure(':-', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$correct_name', 2, 4)
	put_y_value(3, 0)
	put_x_variable(2, 2)
	put_y_value(0, 3)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	put_constant('no_cut', 1)
	put_constant('[]', 4)
	call_predicate('$internal_form', 7, 3)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$2:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$correct_name', 2, 2)
	put_y_value(1, 0)
	get_list(0)
	unify_y_value(0)
	unify_constant('[]')
	deallocate
	proceed
end('$internal_form'/2):



'$correct_name/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$correct_name/2$0'/2):



'$correct_name'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(8)
	get_y_variable(6, 0)
	get_y_variable(2, 1)
	put_y_variable(5, 19)
	put_x_variable(1, 1)
	pseudo_instr3(0, 26, 25, 1)
	get_y_level(7)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_value(5, 0)
	put_y_variable(1, 2)
	put_y_variable(4, 3)
	call_predicate('$correct_pred_arity', 4, 8)
	put_y_value(5, 0)
	put_y_value(1, 1)
	call_predicate('$correct_name/2$0', 2, 8)
	cut(7)
	put_y_value(6, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(3)
	call_predicate('=..', 2, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('$shorten_args', 3, 3)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('=..', 2)

$2:
	get_x_value(0, 1)
	proceed
end('$correct_name'/2):



'$correct_pred_arity'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(8, 0)
	get_y_variable(7, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	get_y_level(9)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 0)
	call_predicate('$last_x_reg', 1, 10)
	pseudo_instr2(1, 20, 27)
	cut(9)
	put_y_value(8, 0)
	put_y_value(5, 1)
	call_predicate('name', 2, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	call_predicate('name', 2, 7)
	put_list(0)
	set_integer(47)
	set_constant('[]')
	put_y_value(6, 1)
	put_y_value(4, 2)
	call_predicate('append', 3, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	call_predicate('append', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('name', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed
end('$correct_pred_arity'/4):



'$shorten_args'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 1:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_integer(1, 0)
	get_x_variable(3, 1)
	get_list(2)
	unify_x_variable(0)
	unify_constant('[]')
	neck_cut
	put_list(1)
	set_constant('$qup_shorten')
	set_x_value(3)
	execute_predicate('=..', 2)

$2:
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(3)
	unify_x_variable(2)
	pseudo_instr2(70, 0, 3)
	get_x_variable(0, 3)
	execute_predicate('$shorten_args', 3)
end('$shorten_args'/3):



'$internal_form'/7:

	switch_on_term(0, $19, $18, $18, $11, $18, $16)

$11:
	switch_on_structure(0, 8, ['$default':$18, '$'/0:$12, ','/2:$13, '$$get_level_ancestor$$'/1:$14, '='/2:$15])

$12:
	try(7, $1)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$13:
	try(7, $1)
	retry($5)
	retry($7)
	retry($9)
	trust($10)

$14:
	try(7, $5)
	retry($6)
	retry($7)
	retry($9)
	trust($10)

$15:
	try(7, $5)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$16:
	switch_on_constant(0, 4, ['$default':$18, '!':$17])

$17:
	try(7, $2)
	retry($3)
	retry($4)
	retry($5)
	retry($7)
	retry($9)
	trust($10)

$18:
	try(7, $5)
	retry($7)
	retry($9)
	trust($10)

$19:
	try(7, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$1:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(7)
	unify_y_variable(6)
	get_y_variable(5, 2)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	neck_cut
	put_y_variable(1, 2)
	put_y_variable(0, 4)
	call_predicate('$internal_form', 7, 7)
	put_y_value(6, 0)
	put_y_value(1, 1)
	put_y_value(5, 2)
	put_y_value(0, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	deallocate
	execute_predicate('$internal_form', 7)

$2:
	get_constant('!', 0)
	get_constant('no_cut', 1)
	get_constant('cut', 2)
	pseudo_instr1(1, 6)
	neck_cut
	put_constant('done', 0)
	get_x_value(6, 0)
	put_x_value(3, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_x_value(5)
	get_list(1)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('$$cut$$', 1, 0)
	unify_x_value(5)
	proceed

$3:
	get_constant('!', 0)
	get_constant('no_cut', 1)
	get_constant('cut', 2)
	neck_cut
	put_x_value(3, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('$$cut$$', 1, 0)
	unify_x_value(5)
	proceed

$4:
	get_constant('!', 0)
	get_constant('cut', 1)
	get_constant('cut', 2)
	get_x_value(3, 4)
	neck_cut
	proceed

$5:
	get_constant('no_cut', 2)
	allocate(11)
	get_y_variable(9, 0)
	get_y_variable(2, 3)
	get_y_variable(7, 4)
	get_y_level(10)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(8, 1)
	put_y_variable(5, 2)
	put_y_variable(6, 3)
	call_predicate('$pseudo_instruction', 4, 11)
	cut(10)
	put_y_value(8, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	put_y_value(9, 3)
	call_predicate('$psinstr_process', 4, 8)
	put_y_value(6, 0)
	put_y_value(7, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 6)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(3)
	put_y_value(0, 2)
	call_predicate('append', 3, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)

$6:
	get_constant('no_cut', 2)
	put_x_value(0, 1)
	get_structure('$$get_level_ancestor$$', 1, 1)
	unify_x_value(5)
	neck_cut
	put_x_value(3, 1)
	get_list(1)
	unify_x_value(0)
	unify_x_value(4)
	proceed

$7:
	get_constant('no_cut', 2)
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	get_y_level(3)
	call_predicate('$escape_builtin', 1, 4)
	cut(3)
	put_y_value(1, 0)
	get_list(0)
	unify_y_value(2)
	unify_y_value(0)
	deallocate
	proceed

$8:
	get_constant('no_cut', 2)
	put_x_value(0, 1)
	get_structure('=', 2, 1)
	unify_void(2)
	neck_cut
	put_x_value(3, 1)
	get_list(1)
	unify_x_value(0)
	unify_x_value(4)
	proceed

$9:
	get_constant('no_cut', 2)
	allocate(5)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(4, 6)
	pseudo_instr1(1, 24)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$correct_name', 2, 5)
	put_y_value(4, 0)
	get_constant('done', 0)
	put_y_value(3, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_y_value(1)
	get_list(1)
	unify_y_value(0)
	unify_y_value(2)
	deallocate
	proceed

$10:
	get_constant('no_cut', 2)
	allocate(3)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	put_y_variable(0, 1)
	call_predicate('$correct_name', 2, 3)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(0)
	unify_y_value(1)
	deallocate
	proceed
end('$internal_form'/7):



'$psinstr_process/4$0/7$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	fail

$2:
	proceed
end('$psinstr_process/4$0/7$0'/1):



'$psinstr_process/4$0/7$1'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(3, 0)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	get_y_level(6)
	call_predicate('$psi_uniq_var', 2, 7)
	cut(6)
	put_y_value(5, 0)
	get_list(0)
	unify_x_ref(0)
	unify_y_value(4)
	get_structure('$pieq', 1, 0)
	unify_y_value(3)
	put_y_value(2, 0)
	get_list(0)
	unify_x_ref(0)
	unify_y_value(0)
	get_structure('$piarg', 2, 0)
	unify_y_value(3)
	unify_y_value(1)
	deallocate
	proceed

$2:
	put_x_value(2, 1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('=', 2, 1)
	unify_x_variable(1)
	unify_x_value(0)
	get_list(2)
	unify_x_ref(0)
	unify_x_value(3)
	get_structure('$pieq', 1, 0)
	unify_x_value(1)
	put_x_value(4, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(6)
	get_structure('$piarg', 2, 0)
	unify_x_value(1)
	unify_x_value(5)
	proceed
end('$psinstr_process/4$0/7$1'/7):



'$psinstr_process/4$0'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(8)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	pseudo_instr1(1, 26)
	get_y_level(7)
	call_predicate('$psinstr_process/4$0/7$0', 1, 8)
	cut(7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	put_y_value(0, 6)
	deallocate
	execute_predicate('$psinstr_process/4$0/7$1', 7)

$2:
	put_x_value(2, 1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('=', 2, 1)
	unify_x_value(0)
	unify_x_variable(0)
	get_list(2)
	unify_x_ref(1)
	unify_x_value(3)
	get_structure('$pieq', 1, 1)
	unify_x_value(0)
	put_x_value(4, 1)
	get_list(1)
	unify_x_ref(1)
	unify_x_value(6)
	get_structure('$piarg', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	proceed
end('$psinstr_process/4$0'/7):



'$psinstr_process'/4:

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
	proceed

$2:
	get_list(0)
	unify_x_ref(4)
	unify_x_variable(0)
	get_structure('$psi_life', 1, 4)
	unify_x_variable(4)
	get_list(1)
	unify_x_ref(5)
	unify_x_variable(1)
	get_structure('$psi_life', 1, 5)
	unify_x_value(4)
	execute_predicate('$psinstr_process', 4)

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(4)
	unify_y_variable(3)
	get_structure('=', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_x_variable(6, 1)
	get_x_variable(4, 2)
	get_y_variable(2, 3)
	put_y_value(2, 1)
	put_x_value(6, 2)
	put_y_variable(1, 3)
	put_y_variable(0, 6)
	call_predicate('$psinstr_process/4$0', 7, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$psinstr_process', 4)
end('$psinstr_process'/4):



'$psi_uniq_var'/2:


$1:
	get_x_variable(2, 0)
	put_x_variable(3, 3)
	put_x_variable(0, 0)
	pseudo_instr3(0, 1, 3, 0)
	put_integer(0, 3)
	execute_predicate('$psi_uniq_var', 4)
end('$psi_uniq_var'/2):



'$psi_uniq_var/4$0'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 1)
	get_x_variable(1, 4)
	pseudo_instr2(110, 0, 5)
	neck_cut
	put_integer(0, 0)
	get_x_value(2, 0)
	pseudo_instr2(70, 3, 0)
	put_x_value(5, 2)
	put_integer(1, 3)
	execute_predicate('$psi_uniq_var', 4)

$2:
	get_x_variable(5, 1)
	get_x_variable(1, 4)
	pseudo_instr2(70, 3, 0)
	put_x_value(5, 2)
	put_integer(0, 3)
	execute_predicate('$psi_uniq_var', 4)
end('$psi_uniq_var/4$0'/5):



'$psi_uniq_var'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	get_x_variable(5, 0)
	get_x_variable(4, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	pseudo_instr3(1, 5, 4, 0)
	put_x_value(5, 3)
	execute_predicate('$psi_uniq_var/4$0', 5)
end('$psi_uniq_var'/4):



