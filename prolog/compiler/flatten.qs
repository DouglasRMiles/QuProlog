'$flatten_clauses'/5:


$1:
	allocate(9)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_variable(8, 2)
	get_y_variable(3, 3)
	get_y_variable(1, 4)
	put_y_variable(7, 19)
	put_y_variable(5, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	call_predicate('name', 2, 9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	call_predicate('name', 2, 8)
	put_list(0)
	set_integer(47)
	set_constant('[]')
	put_y_value(7, 1)
	put_y_value(5, 2)
	call_predicate('append', 3, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(2, 2)
	call_predicate('append', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 3)
	put_y_value(0, 5)
	put_integer(1, 2)
	put_integer(0, 4)
	put_constant('[]', 6)
	call_predicate('$flatten_clauses', 7, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$compile_extracted_clauses', 2)
end('$flatten_clauses'/5):



'$compile_extracted_clauses'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	allocate(4)
	get_y_variable(1, 1)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	put_y_variable(0, 3)
	call_predicate('$read_flatten_pred', 4, 4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	call_predicate('$compile_pred', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$compile_extracted_clauses', 2)
end('$compile_extracted_clauses'/2):



'$flatten_clauses'/7:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(7, $2)
	trust($3)

$5:
	try(7, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_x_value(5, 6)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(12)
	unify_y_variable(5)
	get_structure(':-', 2, 0)
	unify_x_variable(0)
	unify_y_variable(11)
	get_list(1)
	unify_x_ref(1)
	unify_y_variable(4)
	get_structure('clause', 2, 1)
	unify_x_ref(1)
	unify_x_ref(7)
	get_structure(':-', 2, 1)
	unify_x_value(0)
	unify_y_variable(10)
	get_structure('label', 1, 7)
	unify_y_variable(6)
	get_y_value(6, 2)
	get_y_variable(3, 3)
	get_y_variable(9, 4)
	get_y_variable(8, 5)
	get_y_variable(2, 6)
	neck_cut
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(7, 1)
	call_predicate('$colvars', 2, 12)
	put_y_value(11, 0)
	put_y_value(10, 1)
	put_y_value(3, 2)
	put_y_value(7, 3)
	put_y_value(9, 4)
	put_y_value(1, 5)
	put_y_value(8, 6)
	put_y_value(0, 7)
	call_predicate('$flatten_body', 8, 7)
	pseudo_instr2(69, 26, 0)
	get_x_variable(2, 0)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	put_y_value(2, 6)
	deallocate
	execute_predicate('$flatten_clauses', 7)

$3:
	get_list(0)
	unify_x_variable(7)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(8)
	unify_x_variable(1)
	get_structure('clause', 2, 8)
	unify_x_value(7)
	unify_x_ref(7)
	get_structure('label', 1, 7)
	unify_x_variable(7)
	get_x_value(7, 2)
	pseudo_instr2(69, 7, 2)
	execute_predicate('$flatten_clauses', 7)
end('$flatten_clauses'/7):



'$flatten_body/8$0'/10:

	try(10, $1)
	trust($2)

$1:
	allocate(11)
	get_y_variable(9, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(4, 6)
	get_y_variable(3, 7)
	get_y_variable(2, 8)
	get_y_level(10)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 11)
	cut(10)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(9, 2)
	put_y_value(8, 3)
	put_y_value(7, 4)
	put_y_value(6, 5)
	put_y_value(5, 6)
	put_y_value(4, 7)
	put_y_value(3, 8)
	put_y_value(2, 9)
	deallocate
	execute_predicate('$unfold_map', 10)

$2:
	put_x_value(2, 1)
	get_structure('map', 2, 1)
	unify_x_value(0)
	unify_x_value(9)
	get_x_value(6, 5)
	get_x_value(7, 8)
	proceed
end('$flatten_body/8$0'/10):



'$flatten_body'/8:

	switch_on_term(0, $38, $18, $18, $19, $18, $18)

$19:
	switch_on_structure(0, 64, ['$default':$18, '$'/0:$20, ','/2:$21, 'build_structure'/4:$22, 'map'/2:$23, 'filter'/3:$24, 'fold'/4:$25, 'fold_right'/4:$26, 'fold_left'/4:$27, 'front_with'/3:$28, 'after_with'/3:$29, '$pretrans_block'/1:$30, 'write_term_list'/1:$31, 'write_term_list'/2:$32, 'once'/1:$33, '\\+'/1:$34, '$if_then_else'/3:$35, '$if_then'/2:$36, ';'/2:$37])

$20:
	try(8, $1)
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
	retry($16)
	retry($17)
	trust($18)

$21:
	try(8, $1)
	trust($18)

$22:
	try(8, $2)
	trust($18)

$23:
	try(8, $3)
	trust($18)

$24:
	try(8, $4)
	trust($18)

$25:
	try(8, $5)
	trust($18)

$26:
	try(8, $6)
	trust($18)

$27:
	try(8, $7)
	trust($18)

$28:
	try(8, $8)
	trust($18)

$29:
	try(8, $9)
	trust($18)

$30:
	try(8, $10)
	trust($18)

$31:
	try(8, $11)
	trust($18)

$32:
	try(8, $12)
	trust($18)

$33:
	try(8, $13)
	trust($18)

$34:
	try(8, $14)
	trust($18)

$35:
	try(8, $15)
	trust($18)

$36:
	try(8, $16)
	trust($18)

$37:
	try(8, $17)
	trust($18)

$38:
	try(8, $1)
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
	retry($16)
	retry($17)
	trust($18)

$1:
	get_structure(',', 2, 0)
	allocate(16)
	unify_y_variable(12)
	unify_y_variable(7)
	get_structure(',', 2, 1)
	unify_y_variable(11)
	unify_y_variable(6)
	get_y_variable(5, 2)
	get_y_variable(14, 3)
	get_y_variable(10, 4)
	get_y_variable(4, 5)
	get_y_variable(9, 6)
	get_y_variable(3, 7)
	neck_cut
	put_y_variable(13, 19)
	put_y_variable(8, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(12, 0)
	put_y_variable(15, 1)
	call_predicate('$colvars', 2, 16)
	put_y_value(7, 0)
	put_y_value(13, 1)
	call_predicate('$colvars', 2, 16)
	put_y_value(15, 0)
	put_y_value(14, 1)
	put_y_value(2, 2)
	call_predicate('$compiler_union_list', 3, 15)
	put_y_value(13, 0)
	put_y_value(14, 1)
	put_y_value(8, 2)
	call_predicate('$compiler_union_list', 3, 13)
	put_y_value(12, 0)
	put_y_value(11, 1)
	put_y_value(5, 2)
	put_y_value(8, 3)
	put_y_value(10, 4)
	put_y_value(1, 5)
	put_y_value(9, 6)
	put_y_value(0, 7)
	call_predicate('$flatten_body', 8, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(4, 5)
	put_y_value(0, 6)
	put_y_value(3, 7)
	deallocate
	execute_predicate('$flatten_body', 8)

$2:
	get_structure('build_structure', 4, 0)
	allocate(24)
	unify_y_variable(18)
	unify_y_variable(17)
	unify_x_variable(0)
	unify_y_variable(8)
	get_y_variable(16, 1)
	get_y_variable(22, 2)
	get_y_variable(21, 4)
	get_y_variable(20, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(23)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(11, 1)
	put_y_variable(19, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 24)
	cut(23)
	put_y_value(19, 0)
	put_y_value(12, 1)
	call_predicate('same_length', 2, 23)
	put_y_value(22, 0)
	put_y_value(13, 1)
	put_y_value(21, 2)
	put_y_value(20, 3)
	call_predicate('$new_predicate_name', 4, 20)
	put_y_value(15, 0)
	put_list(1)
	set_y_value(14)
	set_y_value(19)
	put_list(2)
	set_y_value(17)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 19)
	put_y_value(16, 0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$put_structure', 3, 0)
	unify_y_value(18)
	unify_y_value(17)
	unify_y_value(14)
	get_structure(',', 2, 1)
	unify_y_value(15)
	unify_x_ref(0)
	get_structure('=', 2, 0)
	unify_y_value(8)
	unify_y_value(14)
	put_y_value(9, 0)
	put_list(1)
	set_void(1)
	set_y_value(12)
	put_list(2)
	set_integer(0)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 14)
	put_y_value(7, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(12)
	put_list(2)
	set_y_value(6)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 14)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(12)
	put_list(2)
	set_y_value(4)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 13)
	put_y_value(12, 0)
	put_list(2)
	set_y_value(3)
	set_constant('[]')
	put_list(1)
	set_y_value(6)
	set_x_value(2)
	put_y_value(10, 2)
	call_predicate('append', 3, 12)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(10)
	call_predicate('=..', 2, 10)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(9)
	unify_constant('!')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(7)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(2)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('$set_argument', 3, 2)
	unify_y_value(8)
	unify_y_value(6)
	unify_y_value(3)
	get_structure(',', 2, 3)
	unify_x_ref(2)
	unify_y_value(5)
	get_structure('is', 2, 2)
	unify_y_value(4)
	unify_x_ref(2)
	get_structure('-', 2, 2)
	unify_y_value(6)
	unify_integer(1)
	put_y_value(1, 2)
	get_list(2)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_y_value(0)
	deallocate
	proceed

$3:
	get_structure('map', 2, 0)
	allocate(12)
	unify_y_variable(9)
	unify_y_variable(8)
	get_structure(',', 2, 1)
	unify_y_variable(10)
	unify_y_variable(7)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	get_y_variable(1, 7)
	get_y_level(11)
	put_y_variable(0, 19)
	put_y_value(8, 0)
	call_predicate('closed_list', 1, 12)
	cut(11)
	put_y_value(8, 0)
	put_y_value(0, 1)
	put_y_value(10, 2)
	call_predicate('$copy_map_var_tails', 3, 10)
	put_y_value(9, 0)
	put_y_value(0, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	put_y_value(1, 8)
	put_y_value(8, 9)
	deallocate
	execute_predicate('$flatten_body/8$0', 10)

$4:
	get_structure('filter', 3, 0)
	unify_x_variable(0)
	allocate(23)
	unify_y_variable(18)
	unify_y_variable(17)
	get_y_variable(16, 1)
	get_y_variable(21, 2)
	get_y_variable(20, 4)
	get_y_variable(19, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(22)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(11, 1)
	put_y_variable(15, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 23)
	cut(22)
	put_y_value(15, 0)
	put_y_value(12, 1)
	call_predicate('same_length', 2, 22)
	put_y_value(21, 0)
	put_y_value(14, 1)
	put_y_value(20, 2)
	put_y_value(19, 3)
	call_predicate('$new_predicate_name', 4, 19)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(17)
	set_y_value(15)
	put_list(2)
	set_y_value(18)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(2)
	call_predicate('=..', 2, 15)
	put_y_value(9, 0)
	put_list(1)
	set_constant('[]')
	set_y_value(12)
	put_list(2)
	set_constant('[]')
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(2)
	call_predicate('=..', 2, 15)
	put_y_value(8, 0)
	put_list(1)
	set_y_value(6)
	set_y_value(12)
	put_list(2)
	set_y_value(7)
	set_y_value(13)
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(12)
	put_list(2)
	set_y_value(7)
	set_y_value(13)
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(12)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(2)
	call_predicate('=..', 2, 13)
	put_y_value(12, 0)
	put_list(1)
	set_y_value(7)
	set_constant('[]')
	put_y_value(10, 2)
	call_predicate('append', 3, 12)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(10)
	call_predicate('=..', 2, 10)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(9)
	unify_constant('true')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(8)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(4)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_constant('!')
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_x_ref(2)
	unify_y_value(2)
	get_structure('=', 2, 2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(7)
	unify_y_value(5)
	put_x_variable(2, 3)
	get_structure(':-', 2, 3)
	unify_y_value(3)
	unify_y_value(2)
	put_y_value(1, 3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(2)
	unify_y_value(0)
	deallocate
	proceed

$5:
	get_structure('fold', 4, 0)
	unify_x_variable(0)
	allocate(24)
	unify_y_variable(19)
	unify_y_variable(18)
	unify_y_variable(17)
	get_y_variable(16, 1)
	get_y_variable(22, 2)
	get_y_variable(21, 4)
	get_y_variable(20, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(23)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(7, 1)
	put_y_variable(15, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 24)
	cut(23)
	put_y_value(15, 0)
	put_y_value(11, 1)
	call_predicate('same_length', 2, 23)
	put_y_value(22, 0)
	put_y_value(14, 1)
	put_y_value(21, 2)
	put_y_value(20, 3)
	call_predicate('$new_predicate_name', 4, 20)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(17)
	set_y_value(15)
	put_list(2)
	set_y_value(19)
	set_x_value(1)
	put_list(3)
	set_y_value(18)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(13)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(3)
	set_constant('[]')
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(9)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(1)
	set_y_value(10)
	set_y_value(12)
	put_list(3)
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(3)
	set_y_value(12)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 12)
	put_y_value(11, 0)
	put_list(1)
	set_y_value(9)
	set_constant('[]')
	put_list(2)
	set_y_value(8)
	set_x_value(1)
	put_list(1)
	set_y_value(10)
	set_x_value(2)
	put_y_value(6, 2)
	call_predicate('append', 3, 8)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(7)
	set_y_value(6)
	call_predicate('=..', 2, 6)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(5)
	unify_constant('true')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(4)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(3)
	unify_y_value(2)
	put_y_value(1, 2)
	get_list(2)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_y_value(0)
	deallocate
	proceed

$6:
	get_structure('fold_right', 4, 0)
	unify_x_variable(0)
	allocate(24)
	unify_y_variable(19)
	unify_y_variable(18)
	unify_y_variable(17)
	get_y_variable(16, 1)
	get_y_variable(22, 2)
	get_y_variable(21, 4)
	get_y_variable(20, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(23)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(7, 1)
	put_y_variable(15, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 24)
	cut(23)
	put_y_value(15, 0)
	put_y_value(11, 1)
	call_predicate('same_length', 2, 23)
	put_y_value(22, 0)
	put_y_value(14, 1)
	put_y_value(21, 2)
	put_y_value(20, 3)
	call_predicate('$new_predicate_name', 4, 20)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(17)
	set_y_value(15)
	put_list(2)
	set_y_value(19)
	set_x_value(1)
	put_list(3)
	set_y_value(18)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(13)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(3)
	set_constant('[]')
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(9)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(1)
	set_y_value(10)
	set_y_value(12)
	put_list(3)
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(3)
	set_y_value(12)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 12)
	put_y_value(11, 0)
	put_list(1)
	set_y_value(9)
	set_constant('[]')
	put_list(2)
	set_y_value(8)
	set_x_value(1)
	put_list(1)
	set_y_value(10)
	set_x_value(2)
	put_y_value(6, 2)
	call_predicate('append', 3, 8)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(7)
	set_y_value(6)
	call_predicate('=..', 2, 6)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(5)
	unify_constant('true')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(4)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(3)
	unify_y_value(2)
	put_y_value(1, 2)
	get_list(2)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_y_value(0)
	deallocate
	proceed

$7:
	get_structure('fold_left', 4, 0)
	unify_x_variable(0)
	allocate(24)
	unify_y_variable(19)
	unify_y_variable(18)
	unify_y_variable(17)
	get_y_variable(16, 1)
	get_y_variable(22, 2)
	get_y_variable(21, 4)
	get_y_variable(20, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(23)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(7, 1)
	put_y_variable(15, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 24)
	cut(23)
	put_y_value(15, 0)
	put_y_value(11, 1)
	call_predicate('same_length', 2, 23)
	put_y_value(22, 0)
	put_y_value(14, 1)
	put_y_value(21, 2)
	put_y_value(20, 3)
	call_predicate('$new_predicate_name', 4, 20)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(17)
	set_y_value(15)
	put_list(2)
	set_y_value(19)
	set_x_value(1)
	put_list(3)
	set_y_value(18)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(13)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(3)
	set_constant('[]')
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(9)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(1)
	set_y_value(10)
	set_y_value(12)
	put_list(3)
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(11)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(3)
	set_y_value(12)
	set_x_value(2)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 12)
	put_y_value(11, 0)
	put_list(1)
	set_y_value(9)
	set_constant('[]')
	put_list(2)
	set_y_value(10)
	set_x_value(1)
	put_list(1)
	set_y_value(8)
	set_x_value(2)
	put_y_value(6, 2)
	call_predicate('append', 3, 8)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(7)
	set_y_value(6)
	call_predicate('=..', 2, 6)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(5)
	unify_constant('true')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(4)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(3)
	unify_y_value(2)
	put_y_value(1, 2)
	get_list(2)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_y_value(0)
	deallocate
	proceed

$8:
	get_structure('front_with', 3, 0)
	unify_x_variable(0)
	allocate(23)
	unify_y_variable(18)
	unify_y_variable(17)
	get_y_variable(16, 1)
	get_y_variable(21, 2)
	get_y_variable(20, 4)
	get_y_variable(19, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(22)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(11, 1)
	put_y_variable(15, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 23)
	cut(22)
	put_y_value(15, 0)
	put_y_value(12, 1)
	call_predicate('same_length', 2, 22)
	put_y_value(21, 0)
	put_y_value(14, 1)
	put_y_value(20, 2)
	put_y_value(19, 3)
	call_predicate('$new_predicate_name', 4, 19)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(17)
	set_y_value(15)
	put_list(2)
	set_y_value(18)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(2)
	call_predicate('=..', 2, 15)
	put_y_value(9, 0)
	put_list(1)
	set_constant('[]')
	set_y_value(12)
	put_list(2)
	set_constant('[]')
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(2)
	call_predicate('=..', 2, 15)
	put_y_value(8, 0)
	put_list(1)
	set_y_value(6)
	set_y_value(12)
	put_list(2)
	set_y_value(7)
	set_y_value(13)
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(2, 0)
	put_list(1)
	set_constant('[]')
	set_y_value(12)
	put_list(2)
	set_y_value(7)
	set_y_value(13)
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(4)
	set_y_value(12)
	put_list(2)
	set_y_value(13)
	set_x_value(1)
	put_list(1)
	set_y_value(14)
	set_x_value(2)
	call_predicate('=..', 2, 13)
	put_y_value(12, 0)
	put_list(1)
	set_y_value(7)
	set_constant('[]')
	put_y_value(10, 2)
	call_predicate('append', 3, 12)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(10)
	call_predicate('=..', 2, 10)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(9)
	unify_constant('true')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(8)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(3)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_constant('!')
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_x_ref(2)
	unify_y_value(5)
	get_structure('=', 2, 2)
	unify_y_value(6)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(7)
	unify_y_value(4)
	put_x_variable(2, 3)
	get_structure(':-', 2, 3)
	unify_y_value(2)
	unify_constant('true')
	put_y_value(1, 3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(2)
	unify_y_value(0)
	deallocate
	proceed

$9:
	get_structure('after_with', 3, 0)
	unify_x_variable(0)
	allocate(22)
	unify_y_variable(14)
	unify_y_variable(17)
	get_y_variable(16, 1)
	get_y_variable(20, 2)
	get_y_variable(19, 4)
	get_y_variable(18, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	get_y_level(21)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(8, 1)
	put_y_variable(15, 2)
	put_x_variable(3, 3)
	call_predicate('$flatten_call', 4, 22)
	cut(21)
	put_y_value(15, 0)
	put_y_value(10, 1)
	call_predicate('same_length', 2, 21)
	put_y_value(20, 0)
	put_y_value(13, 1)
	put_y_value(19, 2)
	put_y_value(18, 3)
	call_predicate('$new_predicate_name', 4, 18)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(17)
	set_y_value(15)
	put_list(2)
	set_y_value(14)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 15)
	put_y_value(6, 0)
	put_list(1)
	set_constant('[]')
	set_y_value(10)
	put_list(2)
	set_constant('[]')
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 15)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(10)
	put_list(2)
	set_y_value(9)
	set_y_value(12)
	put_list(3)
	set_x_value(2)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(3)
	call_predicate('=..', 2, 15)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(14)
	set_y_value(10)
	put_list(2)
	set_y_value(14)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 14)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(10)
	put_list(2)
	set_y_value(12)
	set_x_value(1)
	put_list(1)
	set_y_value(13)
	set_x_value(2)
	call_predicate('=..', 2, 11)
	put_y_value(10, 0)
	put_list(1)
	set_y_value(9)
	set_constant('[]')
	put_y_value(7, 2)
	call_predicate('append', 3, 9)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(7)
	call_predicate('=..', 2, 7)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(6)
	unify_constant('!')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(5)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(3)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_constant('!')
	unify_y_value(4)
	put_x_variable(2, 3)
	get_structure(':-', 2, 3)
	unify_y_value(2)
	unify_constant('true')
	put_y_value(1, 3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(2)
	unify_y_value(0)
	deallocate
	proceed

$10:
	get_structure('$pretrans_block', 1, 0)
	allocate(5)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_y_variable(3, 3)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	get_list(6)
	unify_x_ref(1)
	unify_x_variable(4)
	get_structure(':-', 2, 1)
	unify_y_value(2)
	unify_y_value(4)
	get_x_value(4, 7)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$new_predicate_name', 4, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('$predicate_args', 3, 3)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('=..', 2)

$11:
	get_structure('write_term_list', 1, 0)
	unify_x_variable(8)
	get_x_value(4, 5)
	get_x_value(6, 7)
	put_structure(1, 0)
	set_constant('write_term_list')
	set_x_value(8)
	execute_predicate('$write_tl_expand', 2)

$12:
	get_structure('write_term_list', 2, 0)
	unify_x_variable(8)
	unify_x_variable(9)
	get_x_value(4, 5)
	get_x_value(6, 7)
	put_structure(2, 0)
	set_constant('write_term_list')
	set_x_value(8)
	set_x_value(9)
	execute_predicate('$write_tl_expand', 2)

$13:
	get_structure('once', 1, 0)
	allocate(5)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_y_variable(3, 3)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	get_list(6)
	unify_x_ref(1)
	unify_x_variable(4)
	get_structure(':-', 2, 1)
	unify_y_value(2)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_y_value(4)
	unify_constant('!')
	get_x_value(4, 7)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$new_predicate_name', 4, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('$predicate_args', 3, 3)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('=..', 2)

$14:
	get_structure('\\+', 1, 0)
	allocate(7)
	unify_y_variable(3)
	get_y_variable(1, 1)
	get_x_variable(0, 2)
	get_y_variable(6, 3)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	get_list(6)
	unify_y_variable(2)
	unify_x_ref(1)
	get_list(1)
	unify_y_variable(0)
	unify_x_variable(1)
	get_x_value(1, 7)
	neck_cut
	put_y_variable(4, 19)
	put_y_variable(5, 1)
	call_predicate('$new_predicate_name', 4, 7)
	put_y_value(3, 0)
	put_y_value(6, 1)
	put_y_value(4, 2)
	call_predicate('$predicate_args', 3, 6)
	put_y_value(1, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(4)
	call_predicate('=..', 2, 4)
	put_y_value(2, 0)
	get_structure(':-', 2, 0)
	unify_y_value(1)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(3)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_constant('!')
	unify_constant('fail')
	put_y_value(0, 0)
	get_structure(':-', 2, 0)
	unify_y_value(1)
	unify_constant('true')
	deallocate
	proceed

$15:
	allocate(11)
	get_y_variable(10, 0)
	get_y_variable(3, 1)
	get_x_variable(0, 2)
	get_y_variable(9, 3)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	get_list(6)
	unify_y_variable(6)
	unify_y_variable(2)
	get_y_variable(1, 7)
	put_y_value(10, 1)
	get_structure('$if_then_else', 3, 1)
	unify_y_variable(5)
	unify_y_variable(4)
	unify_y_variable(0)
	neck_cut
	put_y_variable(7, 19)
	put_y_variable(8, 1)
	call_predicate('$new_predicate_name', 4, 11)
	put_y_value(10, 0)
	put_y_value(9, 1)
	put_y_value(7, 2)
	call_predicate('$predicate_args', 3, 9)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(8)
	set_y_value(7)
	call_predicate('=..', 2, 7)
	put_y_value(6, 0)
	get_structure(':-', 2, 0)
	unify_y_value(3)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(5)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_constant('!')
	unify_y_value(4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$flatten_else', 4)

$16:
	allocate(8)
	get_y_variable(7, 0)
	get_y_variable(3, 1)
	get_x_variable(0, 2)
	get_y_variable(6, 3)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	get_list(6)
	unify_y_variable(2)
	unify_x_variable(1)
	get_x_value(1, 7)
	put_y_value(7, 1)
	get_structure('$if_then', 2, 1)
	unify_y_variable(1)
	unify_y_variable(0)
	neck_cut
	put_y_variable(4, 19)
	put_y_variable(5, 1)
	call_predicate('$new_predicate_name', 4, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(4, 2)
	call_predicate('$predicate_args', 3, 6)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(4)
	call_predicate('=..', 2, 4)
	put_y_value(2, 0)
	get_structure(':-', 2, 0)
	unify_y_value(3)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(1)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_constant('!')
	unify_y_value(0)
	deallocate
	proceed

$17:
	allocate(7)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_y_variable(6, 3)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	put_y_value(3, 1)
	get_structure(';', 2, 1)
	unify_void(2)
	neck_cut
	put_y_variable(4, 19)
	put_y_variable(5, 1)
	call_predicate('$new_predicate_name', 4, 7)
	put_y_value(3, 0)
	put_y_value(6, 1)
	put_y_value(4, 2)
	call_predicate('$predicate_args', 3, 6)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(5)
	set_y_value(4)
	call_predicate('=..', 2, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$flatten_disj', 4)

$18:
	get_x_value(0, 1)
	get_x_value(4, 5)
	get_x_value(6, 7)
	proceed
end('$flatten_body'/8):



'$flatten_else'/4:

	switch_on_term(0, $8, $3, $3, $4, $3, $3)

$4:
	switch_on_structure(0, 8, ['$default':$3, '$'/0:$5, '$if_then_else'/3:$6, '$if_then'/2:$7])

$5:
	try(4, $1)
	retry($2)
	trust($3)

$6:
	try(4, $1)
	trust($3)

$7:
	try(4, $2)
	trust($3)

$8:
	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_structure('$if_then_else', 3, 0)
	unify_x_variable(4)
	unify_x_variable(5)
	unify_x_variable(0)
	get_list(3)
	unify_x_variable(6)
	unify_x_variable(3)
	neck_cut
	get_structure(':-', 2, 6)
	unify_x_value(1)
	unify_x_ref(6)
	get_structure(',', 2, 6)
	unify_x_value(4)
	unify_x_ref(4)
	get_structure(',', 2, 4)
	unify_constant('!')
	unify_x_value(5)
	execute_predicate('$flatten_else', 4)

$2:
	get_structure('$if_then', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_list(3)
	unify_x_variable(3)
	unify_x_value(2)
	neck_cut
	put_x_value(3, 2)
	get_structure(':-', 2, 2)
	unify_x_value(1)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_x_value(0)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_constant('!')
	unify_x_value(4)
	proceed

$3:
	get_list(3)
	unify_x_variable(3)
	unify_x_value(2)
	put_x_value(3, 2)
	get_structure(':-', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	proceed
end('$flatten_else'/4):



'$unfold_map/10$0'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	put_x_value(1, 0)
	get_structure('$pretrans_block', 1, 0)
	unify_x_value(2)
	proceed
end('$unfold_map/10$0'/3):



'$unfold_map'/10:

	try(10, $1)
	retry($2)
	trust($3)

$1:
	allocate(23)
	get_y_variable(7, 0)
	get_y_variable(18, 1)
	get_y_variable(17, 2)
	get_y_variable(16, 3)
	get_y_variable(21, 4)
	get_y_variable(20, 6)
	get_y_variable(19, 7)
	get_y_variable(1, 8)
	get_y_variable(0, 9)
	get_y_level(22)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_value(17, 0)
	call_predicate('$list_of_vars', 1, 23)
	cut(22)
	put_y_value(18, 0)
	put_y_value(9, 1)
	call_predicate('same_length', 2, 22)
	put_y_value(17, 0)
	put_y_value(13, 1)
	call_predicate('length', 2, 22)
	put_y_value(21, 0)
	put_y_value(11, 1)
	put_y_value(20, 2)
	put_y_value(19, 3)
	call_predicate('$new_predicate_name', 4, 19)
	put_y_value(17, 0)
	put_y_value(18, 1)
	put_y_value(15, 2)
	call_predicate('append', 3, 17)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(15)
	call_predicate('=..', 2, 15)
	put_y_value(13, 0)
	put_y_value(9, 1)
	put_y_value(14, 2)
	call_predicate('$list_of_empties', 3, 15)
	put_y_value(5, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(14)
	call_predicate('=..', 2, 14)
	put_y_value(13, 0)
	put_y_value(9, 1)
	put_y_value(8, 2)
	put_y_value(10, 3)
	put_y_value(12, 4)
	call_predicate('$ht_lists', 5, 13)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(12)
	call_predicate('=..', 2, 12)
	put_y_value(3, 0)
	put_list(1)
	set_y_value(11)
	set_y_value(10)
	call_predicate('=..', 2, 10)
	put_y_value(9, 0)
	put_y_value(8, 1)
	put_y_value(6, 2)
	call_predicate('append', 3, 8)
	put_y_value(2, 0)
	put_list(1)
	set_y_value(7)
	set_y_value(6)
	call_predicate('=..', 2, 6)
	put_x_variable(0, 1)
	get_structure(':-', 2, 1)
	unify_y_value(5)
	unify_constant('true')
	put_x_variable(1, 2)
	get_structure(':-', 2, 2)
	unify_y_value(4)
	unify_x_ref(2)
	get_structure(',', 2, 2)
	unify_y_value(2)
	unify_y_value(3)
	put_y_value(1, 2)
	get_list(2)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_y_value(0)
	deallocate
	proceed

$2:
	get_constant('true', 3)
	get_x_variable(0, 2)
	get_x_value(6, 7)
	get_x_value(8, 9)
	allocate(1)
	get_y_level(0)
	call_predicate('$list_of_empties', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	allocate(19)
	get_y_variable(9, 0)
	get_y_variable(8, 1)
	get_x_variable(0, 2)
	get_structure(',', 2, 3)
	unify_y_variable(13)
	unify_y_variable(7)
	get_y_variable(6, 4)
	get_y_variable(5, 5)
	get_y_variable(12, 6)
	get_y_variable(4, 7)
	get_y_variable(11, 8)
	get_y_variable(3, 9)
	put_y_variable(17, 19)
	put_y_variable(16, 19)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(10, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(18, 1)
	put_y_variable(2, 2)
	call_predicate('$ht_lists', 3, 19)
	put_y_value(8, 0)
	put_y_value(18, 1)
	put_y_value(17, 2)
	call_predicate('append', 3, 18)
	put_y_value(16, 0)
	put_list(1)
	set_y_value(9)
	set_y_value(17)
	call_predicate('=..', 2, 17)
	put_y_value(16, 0)
	put_y_value(15, 1)
	put_y_value(14, 4)
	put_constant('no', 2)
	put_constant('yes', 3)
	call_predicate('$pretrans_formula1', 5, 16)
	put_y_value(14, 0)
	put_y_value(10, 1)
	put_y_value(15, 2)
	call_predicate('$unfold_map/10$0', 3, 14)
	put_y_value(10, 0)
	put_y_value(13, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(12, 4)
	put_y_value(1, 5)
	put_y_value(11, 6)
	put_y_value(0, 7)
	call_predicate('$flatten_body', 8, 10)
	put_y_value(9, 0)
	put_y_value(8, 1)
	put_y_value(2, 2)
	put_y_value(7, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	put_y_value(1, 6)
	put_y_value(4, 7)
	put_y_value(0, 8)
	put_y_value(3, 9)
	deallocate
	execute_predicate('$unfold_map', 10)
end('$unfold_map'/10):



'$list_of_empties'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_integer(0, 0)
	get_x_value(1, 2)
	neck_cut
	proceed

$2:
	get_list(2)
	unify_constant('[]')
	unify_x_variable(2)
	pseudo_instr2(70, 0, 3)
	get_x_variable(0, 3)
	execute_predicate('$list_of_empties', 3)
end('$list_of_empties'/3):



'$list_of_empties'/1:

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
	execute_predicate('$list_of_empties', 1)
end('$list_of_empties'/1):



'$list_of_vars'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr1(1, 1)
	execute_predicate('$list_of_vars', 1)
end('$list_of_vars'/1):



'$ht_lists'/5:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$1:
	get_integer(0, 0)
	get_constant('[]', 2)
	get_x_value(1, 3)
	get_x_value(1, 4)
	neck_cut
	proceed

$2:
	get_list(2)
	unify_x_variable(5)
	unify_x_variable(2)
	get_list(3)
	unify_x_variable(6)
	unify_x_variable(3)
	get_list(4)
	unify_x_ref(7)
	unify_x_variable(4)
	get_list(7)
	unify_x_value(5)
	unify_x_value(6)
	pseudo_instr2(70, 0, 5)
	get_x_variable(0, 5)
	execute_predicate('$ht_lists', 5)
end('$ht_lists'/5):



'$ht_lists'/3:

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
	execute_predicate('$ht_lists', 3)
end('$ht_lists'/3):



'$flatten_disj'/4:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ';'/2:$5])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$6:
	try(4, $1)
	trust($2)

$1:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 3)
	call_predicate('$flatten_disj', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$flatten_disj', 4)

$2:
	get_list(2)
	unify_x_variable(2)
	unify_x_variable(4)
	get_x_value(4, 3)
	put_x_variable(4, 5)
	get_structure(':-', 2, 5)
	unify_x_value(1)
	unify_x_value(0)
	pseudo_instr2(95, 4, 3)
	get_x_value(2, 3)
	proceed
end('$flatten_disj'/4):



'$new_predicate_name'/4:


$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_value(1, 0)
	put_y_variable(6, 1)
	call_predicate('name', 2, 7)
	put_list(0)
	set_integer(36)
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
	pseudo_instr2(69, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$new_predicate_name'/4):



'$predicate_args'/3:


$1:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(0, 1)
	call_predicate('$colvars', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$compiler_intersect_list', 3)
end('$predicate_args'/3):



'$flatten_call'/4:

	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	get_constant('atom', 3)
	pseudo_instr1(2, 0)
	neck_cut
	get_x_value(1, 0)
	put_constant('[]', 0)
	get_x_value(2, 0)
	proceed

$3:
	get_constant('inline', 3)
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_structure(4, 0)
	set_constant('$inline')
	set_y_value(2)
	set_void(3)
	put_x_variable(1, 1)
	call_predicate('clause', 2, 4)
	cut(3)
	put_y_value(1, 0)
	get_y_value(2, 0)
	put_y_value(0, 0)
	get_constant('[]', 0)
	deallocate
	proceed

$4:
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(2, 2)
	get_y_variable(4, 3)
	pseudo_instr1(0, 0)
	put_y_variable(0, 19)
	put_list(1)
	set_y_variable(3)
	set_y_variable(1)
	call_predicate('=..', 2, 6)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(0, 2)
	put_y_value(4, 3)
	call_predicate('$flatten_call', 4, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)
end('$flatten_call'/4):



'$copy_map_var_tails'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_x_variable(0, 2)
	execute_predicate('$ho_close_tail', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	call_predicate('$copy_map_var_tail', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$copy_map_var_tails', 3)
end('$copy_map_var_tails'/3):



'$copy_map_var_tail'/3:

	switch_on_term(0, $7, $1, $4, $1, $1, $5)

$4:
	try(3, $1)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$1, '[]':$6])

$6:
	try(3, $1)
	trust($2)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(3, 1)
	get_x_variable(1, 2)
	pseudo_instr1(1, 0)
	neck_cut
	put_x_value(3, 2)
	execute_predicate('$conj_var_lookup', 3)

$2:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$3:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(3)
	unify_x_variable(1)
	execute_predicate('$copy_map_var_tail', 3)
end('$copy_map_var_tail'/3):



'$conj_var_lookup'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_void(1)
	get_structure('=', 2, 1)
	unify_x_value(2)
	unify_x_value(0)
	proceed

$2:
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_void(1)
	get_structure('=', 2, 1)
	unify_x_variable(1)
	unify_x_variable(3)
	pseudo_instr2(110, 0, 3)
	neck_cut
	get_x_value(2, 1)
	proceed

$3:
	get_structure(',', 2, 1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('$conj_var_lookup', 3)
end('$conj_var_lookup'/3):



'$ho_close_tail'/1:

	switch_on_term(0, $4, 'fail', 'fail', $3, 'fail', $1)

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$2, ','/2:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	get_constant('true', 0)
	neck_cut
	proceed

$2:
	get_structure(',', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$ho_close_tail', 1)
end('$ho_close_tail'/1):



'$write_tl_expand'/2:

	switch_on_term(0, $5, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$4, 'write_term_list'/1:$1, 'write_term_list'/2:$2])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_structure('write_term_list', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_variable(2)
	get_structure('current_output', 1, 1)
	unify_x_variable(1)
	execute_predicate('$write_tl_expand1', 3)

$2:
	get_structure('write_term_list', 2, 0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_variable(2)
	get_structure('$streamnum', 2, 1)
	unify_x_value(3)
	unify_x_variable(1)
	neck_cut
	execute_predicate('$write_tl_expand1', 3)
end('$write_tl_expand'/2):



'$write_tl_expand1'/3:

	switch_on_term(0, $7, $1, $4, $1, $1, $5)

$4:
	try(3, $1)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$1, '[]':$6])

$6:
	try(3, $1)
	trust($2)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_structure('$write_term_list', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_constant('[]', 0)
	get_constant('true', 2)
	proceed

$3:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_structure(',', 2, 2)
	unify_x_variable(2)
	unify_y_variable(0)
	call_predicate('$write_tl_expand2', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$write_tl_expand1', 3)
end('$write_tl_expand1'/3):



'$write_tl_expand2'/3:

	switch_on_term(0, $29, $1, $1, $14, $1, $26)

$14:
	switch_on_structure(0, 32, ['$default':$1, '$'/0:$15, 'tab'/1:$16, 'pc'/1:$17, 'wa'/1:$18, 'wqa'/1:$19, 'wi'/1:$20, 'w'/1:$21, 'q'/1:$22, 'wR'/1:$23, 'wRq'/1:$24, 'wl'/2:$25])

$15:
	try(3, $1)
	retry($3)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	trust($13)

$16:
	try(3, $1)
	trust($3)

$17:
	try(3, $1)
	trust($5)

$18:
	try(3, $1)
	trust($6)

$19:
	try(3, $1)
	trust($7)

$20:
	try(3, $1)
	trust($8)

$21:
	try(3, $1)
	trust($9)

$22:
	try(3, $1)
	trust($10)

$23:
	try(3, $1)
	trust($11)

$24:
	try(3, $1)
	trust($12)

$25:
	try(3, $1)
	trust($13)

$26:
	switch_on_constant(0, 4, ['$default':$1, 'nl':$27, 'sp':$28])

$27:
	try(3, $1)
	trust($2)

$28:
	try(3, $1)
	trust($4)

$29:
	try(3, $1)
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
	trust($13)

$1:
	get_structure('$write_term_term', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_constant('nl', 0)
	get_structure('put_code', 2, 2)
	unify_x_value(1)
	unify_integer(10)
	proceed

$3:
	get_structure('tab', 1, 0)
	unify_x_variable(0)
	get_structure('$tab', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$4:
	get_constant('sp', 0)
	get_structure('put_code', 2, 2)
	unify_x_value(1)
	unify_integer(32)
	proceed

$5:
	get_structure('pc', 1, 0)
	unify_x_variable(0)
	get_structure('put_code', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$6:
	get_structure('wa', 1, 0)
	unify_x_variable(0)
	get_structure('write_atom', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$7:
	get_structure('wqa', 1, 0)
	unify_x_variable(0)
	get_structure('writeq_atom', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$8:
	get_structure('wi', 1, 0)
	unify_x_variable(0)
	get_structure('write_integer', 2, 2)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$9:
	get_structure('w', 1, 0)
	unify_x_variable(0)
	get_structure('$write_t', 3, 2)
	unify_x_value(1)
	unify_x_value(0)
	unify_constant('write')
	proceed

$10:
	get_structure('q', 1, 0)
	unify_x_variable(0)
	get_structure('$write_t', 3, 2)
	unify_x_value(1)
	unify_x_value(0)
	unify_constant('writeq')
	proceed

$11:
	get_structure('wR', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('name_vars', 1, 2)
	unify_x_value(0)
	get_structure('$write_t', 3, 3)
	unify_x_value(1)
	unify_x_value(0)
	unify_constant('write')
	proceed

$12:
	get_structure('wRq', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('name_vars', 1, 2)
	unify_x_value(0)
	get_structure('$write_t_q', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$13:
	get_structure('wl', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_x_variable(5, 1)
	get_x_variable(3, 2)
	put_x_value(4, 1)
	put_x_value(5, 2)
	execute_predicate('$write_tl_expand3', 4)
end('$write_tl_expand2'/3):



'$write_tl_expand3'/4:

	switch_on_term(0, $9, $1, $6, $1, $1, $7)

$6:
	try(4, $1)
	retry($2)
	retry($4)
	trust($5)

$7:
	switch_on_constant(0, 4, ['$default':$1, '[]':$8])

$8:
	try(4, $1)
	trust($3)

$9:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_structure('$write_list_sep', 3, 3)
	unify_x_value(0)
	unify_x_value(1)
	unify_x_value(2)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_structure('$write_list_sep', 3, 3)
	unify_x_ref(3)
	unify_x_value(1)
	unify_x_value(2)
	get_list(3)
	unify_x_value(0)
	unify_x_value(4)
	pseudo_instr1(1, 4)
	neck_cut
	proceed

$3:
	get_constant('[]', 0)
	get_constant('true', 3)
	proceed

$4:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	neck_cut
	put_x_value(3, 1)
	get_structure('$write_t', 3, 1)
	unify_x_value(2)
	unify_x_value(0)
	unify_constant('write')
	proceed

$5:
	get_list(0)
	unify_x_variable(4)
	unify_x_variable(0)
	get_structure(',', 2, 3)
	unify_x_variable(5)
	unify_x_ref(3)
	get_structure(',', 2, 3)
	unify_x_variable(6)
	unify_x_variable(3)
	get_structure('$write_t', 3, 5)
	unify_x_value(2)
	unify_x_value(4)
	unify_constant('write')
	put_x_value(6, 4)
	get_structure('$write_t', 3, 4)
	unify_x_value(2)
	unify_x_value(1)
	unify_constant('write')
	execute_predicate('$write_tl_expand3', 4)
end('$write_tl_expand3'/4):



