'clause/2$0'/0:

	try(0, $1)
	trust($2)

$1:
	proceed

$2:
	fail
end('clause/2$0'/0):



'clause/2$1'/2:

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
end('clause/2$1'/2):



'clause'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('clause')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('clause')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(9)
	get_y_variable(8, 0)
	get_y_variable(2, 1)
	get_y_level(1)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	call_predicate('$legal_clause_head', 1, 9)
	cut(1)
	put_y_value(8, 0)
	put_y_value(3, 1)
	call_predicate('$correct_name', 2, 8)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 23, 0, 1)
	pseudo_instr3(66, 0, 1, 2)
	get_y_value(7, 2)
	pseudo_instr4(15, 23, 27, 0, 1)
	get_y_value(6, 0)
	get_y_value(5, 1)
	call_predicate('clause/2$0', 0, 8)
	put_y_value(6, 0)
	put_y_value(7, 1)
	put_y_value(4, 2)
	put_y_value(5, 3)
	put_y_value(0, 4)
	call_predicate('$get_clause_ref', 5, 5)
	pseudo_instr3(57, 24, 23, 0)
	pseudo_instr2(67, 23, 1)
	put_y_value(2, 3)
	put_constant('[]', 2)
	call_predicate('$post_trans_decompile', 4, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('clause/2$1', 2)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('clause')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('clause')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('clause'/2):



'$get_clause_ref'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_value(0, 2)
	get_x_value(3, 4)
	proceed

$2:
	pseudo_instr4(16, 0, 1, 3, 5)
	get_x_variable(0, 3)
	get_x_variable(3, 5)
	execute_predicate('$get_clause_ref', 5)
end('$get_clause_ref'/5):



'$post_trans_decompile'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 3)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_x_variable(6, 1)
	get_x_variable(7, 2)
	get_x_variable(4, 3)
	put_x_value(5, 1)
	put_x_value(6, 2)
	put_x_value(7, 3)
	execute_predicate('$post_trans_decompile_aux', 5)
end('$post_trans_decompile'/4):



'$post_trans_decompile_aux/5$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	put_constant('!', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_structure('$cut', 1, 1)
	unify_x_value(0)
	proceed
end('$post_trans_decompile_aux/5$0'/2):



'$post_trans_decompile_aux'/5:

	switch_on_term(0, $31, $14, $14, $15, $14, $29)

$15:
	switch_on_structure(0, 32, ['$default':$14, '$'/0:$16, '$get_level'/1:$17, '$cut'/1:$18, '$psi0_calls$'/1:$19, '$psi1_calls$'/2:$20, '$psi2_calls$'/3:$21, '$psi3_calls$'/4:$22, '$psi4_calls$'/5:$23, '$psi5_calls$'/6:$24, '$message_choice'/2:$25, '$ite_call'/4:$26, '$or_call'/3:$27, '='/2:$28])

$16:
	try(5, $1)
	retry($2)
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
	trust($14)

$17:
	try(5, $1)
	trust($14)

$18:
	try(5, $2)
	trust($14)

$19:
	try(5, $4)
	trust($14)

$20:
	try(5, $5)
	trust($14)

$21:
	try(5, $6)
	trust($14)

$22:
	try(5, $7)
	trust($14)

$23:
	try(5, $8)
	trust($14)

$24:
	try(5, $9)
	trust($14)

$25:
	try(5, $10)
	trust($14)

$26:
	try(5, $11)
	trust($14)

$27:
	try(5, $12)
	trust($14)

$28:
	try(5, $13)
	trust($14)

$29:
	switch_on_constant(0, 4, ['$default':$14, '$$neckcut':$30])

$30:
	try(5, $3)
	trust($14)

$31:
	try(5, $1)
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
	trust($14)

$1:
	get_structure('$get_level', 1, 0)
	unify_x_variable(0)
	neck_cut
	put_constant('level', 5)
	get_x_value(0, 5)
	put_x_value(1, 0)
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(1)
	execute_predicate('$post_trans_decompile_aux', 5)

$2:
	get_structure('$cut', 1, 0)
	unify_x_variable(0)
	allocate(6)
	get_y_variable(3, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(2, 4)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$post_trans_decompile_aux/5$0', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	call_predicate('append', 3, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(0, 3)
	put_y_value(2, 4)
	put_constant('[]', 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$3:
	get_constant('$$neckcut', 0)
	allocate(3)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 2)
	call_predicate('append', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 3)
	put_y_value(1, 4)
	put_constant('!', 1)
	put_constant('[]', 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$4:
	get_structure('$psi0_calls$', 1, 0)
	unify_x_variable(0)
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(4, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$psi0_decl', 5, 5)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(0)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$5:
	get_structure('$psi1_calls$', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	allocate(5)
	get_y_variable(2, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(5, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	call_predicate('$psi1_decl', 6, 5)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(0)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_x_variable(1, 3)
	get_structure(',', 2, 3)
	unify_x_value(2)
	unify_y_value(3)
	pseudo_instr2(67, 1, 0)
	get_x_variable(3, 0)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$post_trans_decompile_aux', 5)

$6:
	get_structure('$psi2_calls$', 3, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	unify_x_variable(6)
	allocate(5)
	get_y_variable(2, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(5, 2)
	put_x_value(6, 3)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	call_predicate('$psi2_decl', 7, 5)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(0)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_x_variable(1, 3)
	get_structure(',', 2, 3)
	unify_x_value(2)
	unify_y_value(3)
	pseudo_instr2(67, 1, 0)
	get_x_variable(3, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$7:
	get_structure('$psi3_calls$', 4, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	unify_x_variable(6)
	unify_x_variable(7)
	allocate(5)
	get_y_variable(2, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(5, 2)
	put_x_value(6, 3)
	put_x_value(7, 4)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	call_predicate('$psi3_decl', 8, 5)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(0)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_x_variable(1, 3)
	get_structure(',', 2, 3)
	unify_x_value(2)
	unify_y_value(3)
	pseudo_instr2(67, 1, 0)
	get_x_variable(3, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$8:
	get_structure('$psi4_calls$', 5, 0)
	unify_x_variable(0)
	unify_x_variable(6)
	unify_x_variable(7)
	unify_x_variable(8)
	unify_x_variable(5)
	allocate(5)
	get_y_variable(2, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(6, 2)
	put_x_value(7, 3)
	put_x_value(8, 4)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	call_predicate('$psi4_decl', 9, 5)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(0)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_x_variable(1, 3)
	get_structure(',', 2, 3)
	unify_x_value(2)
	unify_y_value(3)
	pseudo_instr2(67, 1, 0)
	get_x_variable(3, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$9:
	get_structure('$psi5_calls$', 6, 0)
	unify_x_variable(0)
	unify_x_variable(7)
	unify_x_variable(8)
	unify_x_variable(9)
	unify_x_variable(5)
	unify_x_variable(6)
	allocate(5)
	get_y_variable(2, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(7, 2)
	put_x_value(8, 3)
	put_x_value(9, 4)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	put_x_variable(9, 9)
	call_predicate('$psi5_decl', 10, 5)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(0)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_x_variable(1, 3)
	get_structure(',', 2, 3)
	unify_x_value(2)
	unify_y_value(3)
	pseudo_instr2(67, 1, 0)
	get_x_variable(3, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$10:
	get_structure('$message_choice', 2, 0)
	allocate(5)
	unify_y_variable(4)
	unify_void(1)
	get_y_variable(3, 1)
	get_y_variable(2, 4)
	neck_cut
	put_x_variable(1, 4)
	get_structure(',', 2, 4)
	unify_y_value(4)
	unify_x_value(2)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_y_value(4, 0)
	put_y_variable(1, 4)
	put_y_variable(0, 5)
	put_constant('true', 1)
	call_predicate('$check_for_cuts', 6, 5)
	put_y_value(3, 0)
	put_structure(1, 1)
	set_constant('message_choice')
	set_y_value(4)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$11:
	get_structure('$ite_call', 4, 0)
	allocate(7)
	unify_y_variable(6)
	unify_y_variable(5)
	unify_y_variable(4)
	unify_void(1)
	get_y_variable(3, 1)
	get_y_variable(2, 4)
	neck_cut
	put_x_variable(1, 4)
	get_structure(',', 2, 4)
	unify_y_value(6)
	unify_x_ref(4)
	get_structure(',', 2, 4)
	unify_y_value(5)
	unify_x_ref(4)
	get_structure(',', 2, 4)
	unify_y_value(4)
	unify_x_value(2)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_variable(1, 4)
	put_y_variable(0, 5)
	call_predicate('$check_for_cuts', 6, 7)
	put_y_value(3, 0)
	put_structure(2, 2)
	set_constant('->')
	set_y_value(6)
	set_y_value(5)
	put_structure(2, 1)
	set_constant(';')
	set_x_value(2)
	set_y_value(4)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$12:
	get_structure('$or_call', 3, 0)
	allocate(6)
	unify_y_variable(5)
	unify_y_variable(4)
	unify_void(1)
	get_y_variable(3, 1)
	get_y_variable(2, 4)
	neck_cut
	put_x_variable(1, 4)
	get_structure(',', 2, 4)
	unify_y_value(5)
	unify_x_ref(4)
	get_structure(',', 2, 4)
	unify_y_value(4)
	unify_x_value(2)
	pseudo_instr2(67, 1, 0)
	get_x_variable(2, 0)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_variable(1, 4)
	put_y_variable(0, 5)
	call_predicate('$check_for_cuts', 6, 6)
	put_y_value(3, 0)
	put_structure(2, 1)
	set_constant(';')
	set_y_value(5)
	set_y_value(4)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 5)

$13:
	get_structure('=', 2, 0)
	allocate(7)
	unify_y_variable(5)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	pseudo_instr1(1, 25)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(5)
	unify_y_value(4)
	pseudo_instr2(67, 1, 0)
	get_y_level(6)
	put_y_value(1, 1)
	put_constant('[]', 2)
	call_predicate('intersect_list', 3, 7)
	cut(6)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(4)
	unify_y_value(3)
	pseudo_instr2(67, 1, 0)
	get_x_variable(1, 0)
	put_y_value(2, 0)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$post_trans_decompile', 4)

$14:
	get_x_variable(5, 0)
	get_x_variable(0, 1)
	put_x_variable(6, 7)
	get_structure(',', 2, 7)
	unify_x_value(5)
	unify_x_value(2)
	pseudo_instr2(67, 6, 1)
	get_x_variable(2, 1)
	put_x_value(5, 1)
	execute_predicate('$post_trans_decompile_rest', 5)
end('$post_trans_decompile_aux'/5):



'$post_trans_decompile_rest'/5:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(5, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 4)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure(',', 2, 4)
	unify_x_value(1)
	unify_x_variable(4)
	put_x_value(5, 1)
	execute_predicate('$post_trans_decompile_aux', 5)
end('$post_trans_decompile_rest'/5):



'$check_for_cuts'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	get_y_variable(2, 4)
	get_y_variable(0, 5)
	get_y_level(4)
	call_predicate('$no_cuts', 1, 6)
	put_y_value(5, 0)
	call_predicate('$no_cuts', 1, 5)
	cut(4)
	put_y_value(2, 0)
	get_y_value(3, 0)
	put_y_value(0, 0)
	get_y_value(1, 0)
	deallocate
	proceed

$2:
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	get_x_variable(2, 5)
	put_constant('[]', 3)
	get_x_value(4, 3)
	execute_predicate('append', 3)
end('$check_for_cuts'/6):



'$no_cuts'/1:

	switch_on_term(0, $13, $12, $12, $6, $12, $10)

$6:
	switch_on_structure(0, 8, ['$default':$12, '$'/0:$7, ';'/2:$8, '->'/2:$9])

$7:
	try(1, $2)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(1, $2)
	retry($3)
	trust($5)

$9:
	try(1, $2)
	retry($4)
	trust($5)

$10:
	switch_on_constant(0, 4, ['$default':$12, '!':$11])

$11:
	try(1, $1)
	retry($2)
	trust($5)

$12:
	try(1, $2)
	trust($5)

$13:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('!', 0)
	neck_cut
	fail

$2:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$3:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$no_cuts', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$no_cuts', 1)

$4:
	get_structure('->', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$no_cuts', 1)

$5:
	proceed
end('$no_cuts'/1):



'listing'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(1)
	put_y_variable(0, 0)
	put_constant('dynamic', 1)
	call_predicate('predicate_property', 2, 1)
	put_y_value(0, 0)
	call_predicate('$listing_predicate', 1, 0)
	fail

$2:
	proceed
end('listing'/0):



'listing'/1:

	switch_on_term(0, $11, $4, $5, $6, $4, $9)

$5:
	try(1, $2)
	trust($4)

$6:
	switch_on_structure(0, 4, ['$default':$4, '$'/0:$7, '/'/2:$8])

$7:
	try(1, $3)
	trust($4)

$8:
	try(1, $3)
	trust($4)

$9:
	switch_on_constant(0, 4, ['$default':$4, '[]':$10])

$10:
	try(1, $1)
	trust($4)

$11:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('listing', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('listing', 1)

$3:
	get_structure('/', 2, 0)
	unify_x_variable(1)
	unify_x_variable(2)
	pseudo_instr1(2, 1)
	pseudo_instr1(3, 2)
	neck_cut
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 1, 2)
	execute_predicate('$listing_predicate', 1)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('listing')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('listing')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('listing')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_structure(2, 1)
	set_constant('/')
	set_constant('p')
	set_constant('n')
	put_structure(1, 3)
	set_constant('list')
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('type_exception', 4)
end('listing'/1):



'$listing_predicate'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 2)
	put_structure(2, 0)
	set_constant(':-')
	set_y_value(1)
	set_y_value(0)
	call_predicate('portray_clause', 1, 0)
	fail

$2:
	proceed
end('$listing_predicate'/1):



