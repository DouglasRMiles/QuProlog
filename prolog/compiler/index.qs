'$compile_index/5$0'/8:

	try(8, $1)
	trust($2)

$1:
	get_x_variable(8, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	get_x_variable(5, 6)
	get_x_variable(6, 7)
	put_constant('true', 7)
	pseudo_instr2(110, 8, 7)
	neck_cut
	execute_predicate('$share_or_new', 7)

$2:
	get_x_variable(0, 1)
	get_x_variable(3, 6)
	put_constant('struct', 1)
	execute_predicate('$build_var_tree', 4)
end('$compile_index/5$0'/8):



'$compile_index/5$1'/8:

	try(8, $1)
	trust($2)

$1:
	get_x_variable(8, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	get_x_variable(5, 6)
	get_x_variable(6, 7)
	put_constant('true', 7)
	pseudo_instr2(110, 8, 7)
	neck_cut
	execute_predicate('$share_or_new', 7)

$2:
	get_x_variable(0, 1)
	get_x_variable(3, 6)
	put_constant('quant', 1)
	execute_predicate('$build_var_tree', 4)
end('$compile_index/5$1'/8):



'$compile_index'/5:

	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_list(2)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('clause', 2, 0)
	unify_void(2)
	get_x_value(3, 4)
	neck_cut
	proceed

$2:
	get_integer(0, 1)
	get_x_variable(0, 2)
	allocate(3)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$collect_labels', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_integer(0, 1)
	deallocate
	execute_predicate('$try_block', 4)

$3:
	allocate(7)
	get_y_variable(3, 1)
	get_y_variable(4, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_level(5)
	put_y_variable(0, 19)
	put_y_variable(6, 2)
	call_predicate('$get_pred_index', 3, 7)
	put_y_value(4, 0)
	put_y_value(6, 1)
	call_predicate('$variable_only', 2, 6)
	cut(5)
	put_y_value(4, 0)
	put_y_value(0, 1)
	call_predicate('$collect_labels', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$try_block', 4)

$4:
	allocate(26)
	get_y_variable(8, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(7, 4)
	get_y_level(0)
	put_y_variable(24, 19)
	put_y_variable(23, 19)
	put_y_variable(22, 19)
	put_y_variable(21, 19)
	put_y_variable(20, 19)
	put_y_variable(19, 19)
	put_y_variable(18, 19)
	put_y_variable(17, 19)
	put_y_variable(16, 19)
	put_y_variable(15, 19)
	put_y_variable(14, 19)
	put_y_variable(13, 19)
	put_y_variable(12, 19)
	put_y_variable(11, 19)
	put_y_variable(10, 19)
	put_y_variable(9, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(1, 19)
	put_y_variable(25, 2)
	call_predicate('$get_pred_index', 3, 26)
	pseudo_instr2(70, 45, 0)
	get_y_value(6, 0)
	put_y_value(3, 0)
	put_y_value(25, 1)
	put_y_value(5, 2)
	put_y_value(24, 3)
	put_y_value(15, 4)
	put_y_value(23, 5)
	put_y_value(22, 6)
	put_y_value(20, 7)
	put_y_value(16, 8)
	put_structure(2, 9)
	set_constant('flags')
	set_y_value(21)
	set_y_value(19)
	call_predicate('$build_index_tree', 10, 25)
	put_y_value(5, 0)
	put_y_value(18, 1)
	call_predicate('length', 2, 25)
	put_y_value(24, 0)
	put_y_value(13, 1)
	put_y_value(18, 2)
	put_y_value(4, 3)
	put_y_value(15, 4)
	put_y_value(14, 5)
	put_y_value(17, 6)
	call_predicate('$share_or_new', 7, 24)
	put_y_value(23, 0)
	put_y_value(12, 1)
	put_y_value(18, 2)
	put_y_value(4, 3)
	put_y_value(15, 4)
	put_y_value(14, 5)
	put_y_value(17, 6)
	call_predicate('$share_or_new', 7, 23)
	put_y_value(21, 0)
	put_y_value(22, 1)
	put_y_value(11, 2)
	put_y_value(18, 3)
	put_y_value(4, 4)
	put_y_value(15, 5)
	put_y_value(14, 6)
	put_y_value(17, 7)
	call_predicate('$compile_index/5$0', 8, 21)
	put_y_value(19, 0)
	put_y_value(20, 1)
	put_y_value(10, 2)
	put_y_value(18, 3)
	put_y_value(4, 4)
	put_y_value(15, 5)
	put_y_value(14, 6)
	put_y_value(17, 7)
	call_predicate('$compile_index/5$1', 8, 17)
	put_y_value(16, 0)
	put_y_value(9, 1)
	put_y_value(14, 2)
	call_predicate('$build_fixed_tree', 3, 16)
	put_x_variable(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_y_value(14)
	unify_y_value(15)
	put_x_variable(0, 2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(13)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(12)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(11)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(10)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(9)
	unify_x_value(1)
	put_y_value(8, 1)
	put_y_value(6, 2)
	put_y_value(2, 3)
	put_y_value(7, 4)
	put_y_value(4, 5)
	put_y_value(5, 6)
	call_predicate('$generate_index_instrs', 7, 4)
	put_y_value(3, 0)
	put_y_value(1, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$instantiate_labels', 2, 1)
	cut(0)
	deallocate
	proceed
end('$compile_index'/5):



'$variable_only'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(1)
	get_structure('clause', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	get_y_variable(0, 1)
	put_y_variable(2, 2)
	call_predicate('$getarg', 3, 3)
	pseudo_instr1(1, 22)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$variable_only', 2)
end('$variable_only'/2):



'$collect_labels'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	put_integer(2, 5)
	pseudo_instr3(1, 5, 2, 4)
	get_x_value(3, 4)
	execute_predicate('$collect_labels', 2)
end('$collect_labels'/2):



'$getarg/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	execute_predicate('$search_body_unification', 3)

$2:
	get_x_value(2, 0)
	proceed
end('$getarg/3$0'/3):



'$getarg'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ':-'/2:$5])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$6:
	try(3, $1)
	trust($2)

$1:
	get_structure(':-', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	neck_cut
	pseudo_instr3(1, 1, 0, 4)
	get_x_variable(0, 4)
	put_x_value(3, 1)
	execute_predicate('$getarg/3$0', 3)

$2:
	pseudo_instr3(1, 1, 0, 3)
	get_x_value(2, 3)
	proceed
end('$getarg'/3):



'$classify/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	put_constant('var', 0)
	get_x_value(1, 0)
	proceed

$2:
	put_constant('obvar', 0)
	get_x_value(1, 0)
	proceed
end('$classify/2$0'/2):



'$classify/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('closed_list', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 2)
	put_integer(0, 1)
	deallocate
	execute_predicate('$length', 3)

$2:
	proceed
end('$classify/2$1'/2):



'$classify/2$2'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	neck_cut
	get_structure('quant', 1, 2)
	unify_x_ref(2)
	get_structure('/', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$2:
	put_x_value(2, 0)
	get_structure('quant', 1, 0)
	unify_constant('$default')
	proceed
end('$classify/2$2'/3):



'$classify/2$3'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	neck_cut
	get_structure('struct', 1, 2)
	unify_x_ref(2)
	get_structure('/', 2, 2)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$2:
	put_x_value(2, 0)
	get_structure('struct', 1, 0)
	unify_constant('$default')
	proceed
end('$classify/2$3'/3):



'$classify'/2:

	switch_on_term(0, $11, $10, $11, $10, $10, $10)

$10:
	try(2, $1)
	retry($2)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$11:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('var', 0)
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr1(4, 0)
	neck_cut
	execute_predicate('$classify/2$0', 2)

$3:
	get_list(0)
	unify_void(2)
	neck_cut
	put_constant('list', 0)
	get_x_value(1, 0)
	proceed

$4:
	get_structure('quant', 1, 1)
	unify_constant('$default')
	pseudo_instr1(6, 0)
	pseudo_instr1(5, 0)
	neck_cut
	proceed

$5:
	allocate(3)
	get_y_variable(2, 1)
	pseudo_instr1(5, 0)
	neck_cut
	pseudo_instr2(58, 0, 1)
	get_y_variable(1, 1)
	pseudo_instr2(59, 0, 1)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('$classify/2$1', 2, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$classify/2$2', 3)

$6:
	pseudo_instr1(85, 0)
	neck_cut
	pseudo_instr2(36, 0, 2)
	get_x_variable(0, 2)
	get_structure('const', 1, 1)
	unify_x_value(0)
	proceed

$7:
	pseudo_instr1(108, 0)
	neck_cut
	pseudo_instr2(136, 0, 2)
	get_x_variable(0, 2)
	get_structure('const', 1, 1)
	unify_x_value(0)
	proceed

$8:
	pseudo_instr1(43, 0)
	neck_cut
	get_structure('const', 1, 1)
	unify_x_value(0)
	proceed

$9:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 3, 0, 1)
	execute_predicate('$classify/2$3', 3)
end('$classify'/2):



'$build_index_tree'/10:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(10, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 2)
	get_constant('[]', 3)
	get_constant('[]', 4)
	get_constant('[]', 5)
	get_constant('[]', 6)
	get_constant('[]', 7)
	get_constant('[]', 8)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(20)
	unify_y_variable(18)
	get_y_variable(17, 1)
	get_y_variable(16, 2)
	get_y_variable(15, 3)
	get_y_variable(14, 4)
	get_y_variable(13, 5)
	get_y_variable(12, 6)
	get_y_variable(11, 7)
	get_y_variable(10, 8)
	get_y_variable(9, 9)
	get_structure('clause', 2, 0)
	unify_x_variable(0)
	unify_y_variable(8)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(19, 2)
	call_predicate('$getarg', 3, 20)
	put_y_value(19, 0)
	put_y_value(7, 1)
	call_predicate('$classify', 2, 19)
	put_y_value(18, 0)
	put_y_value(17, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	put_y_value(0, 8)
	put_y_value(9, 9)
	call_predicate('$build_index_tree', 10, 17)
	put_y_value(7, 0)
	put_y_value(8, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	put_y_value(0, 8)
	put_y_value(16, 9)
	put_y_value(15, 10)
	put_y_value(14, 11)
	put_y_value(13, 12)
	put_y_value(12, 13)
	put_y_value(11, 14)
	put_y_value(10, 15)
	put_y_value(9, 16)
	deallocate
	execute_predicate('$update_tree', 17)
end('$build_index_tree'/10):



'$update_tree/17$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	put_constant('$default', 0)
	get_x_value(2, 0)
	neck_cut
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	proceed
end('$update_tree/17$0'/2):



'$update_tree/17$1'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	put_constant('$default', 0)
	get_x_value(2, 0)
	neck_cut
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed

$2:
	proceed
end('$update_tree/17$1'/2):



'$update_tree'/17:

	switch_on_term(0, $10, 'fail', 'fail', $7, 'fail', $9)

$7:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$8, 'struct'/1:$4, 'quant'/1:$5, 'const'/1:$6])

$8:
	try(17, $4)
	retry($5)
	trust($6)

$9:
	switch_on_constant(0, 8, ['$default':'fail', 'var':$1, 'obvar':$2, 'list':$3])

$10:
	try(17, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_constant('var', 0)
	get_list(9)
	unify_x_variable(0)
	unify_x_value(2)
	get_list(10)
	unify_x_value(0)
	unify_x_value(3)
	get_list(11)
	unify_x_value(0)
	unify_x_value(4)
	get_list(12)
	unify_x_value(0)
	unify_x_value(5)
	get_list(13)
	unify_x_value(0)
	unify_x_value(6)
	get_list(14)
	unify_x_value(0)
	unify_x_value(7)
	get_list(15)
	unify_x_value(0)
	unify_x_value(8)
	get_structure('arg', 2, 0)
	unify_constant('var')
	unify_x_value(1)
	proceed

$2:
	get_constant('obvar', 0)
	get_list(9)
	unify_x_ref(0)
	unify_x_value(2)
	get_structure('arg', 2, 0)
	unify_constant('obvar')
	unify_x_value(1)
	get_list(10)
	unify_x_ref(0)
	unify_x_value(3)
	get_structure('arg', 2, 0)
	unify_constant('obvar')
	unify_x_value(1)
	get_x_value(4, 11)
	get_x_value(5, 12)
	get_x_value(6, 13)
	get_x_value(7, 14)
	get_x_value(8, 15)
	proceed

$3:
	get_constant('list', 0)
	get_list(9)
	unify_x_ref(0)
	unify_x_value(2)
	get_structure('arg', 2, 0)
	unify_constant('list')
	unify_x_value(1)
	get_x_value(3, 10)
	get_x_value(4, 11)
	get_list(12)
	unify_x_ref(0)
	unify_x_value(5)
	get_structure('arg', 2, 0)
	unify_constant('list')
	unify_x_value(1)
	get_x_value(6, 13)
	get_x_value(7, 14)
	get_x_value(8, 15)
	proceed

$4:
	get_structure('struct', 1, 0)
	unify_x_variable(0)
	get_list(9)
	unify_x_ref(9)
	unify_x_value(2)
	get_structure('arg', 2, 9)
	unify_x_ref(2)
	unify_x_value(1)
	get_structure('struct', 1, 2)
	unify_x_value(0)
	get_x_value(3, 10)
	get_x_value(4, 11)
	get_x_value(5, 12)
	get_list(13)
	unify_x_ref(2)
	unify_x_value(6)
	get_structure('arg', 2, 2)
	unify_x_ref(2)
	unify_x_value(1)
	get_structure('struct', 1, 2)
	unify_x_value(0)
	get_x_value(7, 14)
	get_x_value(8, 15)
	get_structure('flags', 2, 16)
	unify_x_variable(1)
	unify_void(1)
	execute_predicate('$update_tree/17$0', 2)

$5:
	get_structure('quant', 1, 0)
	unify_x_variable(0)
	get_list(9)
	unify_x_ref(9)
	unify_x_value(2)
	get_structure('arg', 2, 9)
	unify_x_ref(2)
	unify_x_value(1)
	get_structure('quant', 1, 2)
	unify_x_value(0)
	get_x_value(3, 10)
	get_x_value(4, 11)
	get_x_value(5, 12)
	get_x_value(6, 13)
	get_list(14)
	unify_x_ref(2)
	unify_x_value(7)
	get_structure('arg', 2, 2)
	unify_x_ref(2)
	unify_x_value(1)
	get_structure('quant', 1, 2)
	unify_x_value(0)
	get_x_value(8, 15)
	get_structure('flags', 2, 16)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('$update_tree/17$1', 2)

$6:
	get_structure('const', 1, 0)
	unify_x_variable(0)
	get_list(9)
	unify_x_ref(9)
	unify_x_value(2)
	get_structure('arg', 2, 9)
	unify_x_ref(2)
	unify_x_value(1)
	get_structure('const', 1, 2)
	unify_x_value(0)
	get_x_value(3, 10)
	get_x_value(4, 11)
	get_x_value(5, 12)
	get_x_value(6, 13)
	get_x_value(7, 14)
	get_list(15)
	unify_x_ref(2)
	unify_x_value(8)
	get_structure('arg', 2, 2)
	unify_x_ref(2)
	unify_x_value(1)
	get_structure('const', 1, 2)
	unify_x_value(0)
	proceed
end('$update_tree'/17):



'$build_fixed_tree'/3:


$1:
	allocate(6)
	get_y_variable(4, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_x_variable(2, 2)
	put_y_variable(5, 3)
	put_constant('known_chains', 0)
	put_constant('[]', 1)
	call_predicate('$x_set', 4, 6)
	put_structure(2, 1)
	set_constant('chain')
	set_x_variable(0)
	set_x_value(0)
	put_y_value(5, 2)
	put_y_value(3, 3)
	put_constant('var_chain', 0)
	call_predicate('$x_set', 4, 5)
	put_y_value(4, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	call_predicate('$extract_chains', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_x_variable(3, 3)
	put_constant('const', 4)
	deallocate
	execute_predicate('$hash_uses_varonly', 5)
end('$build_fixed_tree'/3):



'$build_var_tree/4$0'/3:

	switch_on_term(0, $7, $3, $4, $3, $3, $5)

$4:
	try(3, $2)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$3, '[]':$6])

$6:
	try(3, $1)
	trust($3)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	put_constant('[]', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('[]', 0)
	get_x_value(1, 0)
	proceed

$2:
	put_x_value(0, 2)
	get_list(2)
	unify_x_ref(2)
	unify_constant('[]')
	get_structure(':', 2, 2)
	unify_void(1)
	unify_constant('[]')
	neck_cut
	get_x_value(1, 0)
	proceed

$3:
	get_list(1)
	unify_x_ref(1)
	unify_x_value(0)
	get_structure(':', 2, 1)
	unify_x_ref(0)
	unify_x_value(2)
	get_structure('/', 2, 0)
	unify_constant('$')
	unify_integer(0)
	proceed
end('$build_var_tree/4$0'/3):



'$build_var_tree'/4:


$1:
	allocate(8)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	put_y_variable(6, 19)
	put_y_variable(4, 19)
	put_y_variable(0, 19)
	put_x_variable(2, 2)
	put_y_variable(7, 3)
	put_constant('known_chains', 0)
	put_constant('[]', 1)
	call_predicate('$x_set', 4, 8)
	put_structure(2, 1)
	set_constant('chain')
	set_x_variable(0)
	set_x_value(0)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_constant('var_chain', 0)
	call_predicate('$x_set', 4, 7)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(6, 2)
	call_predicate('$extract_chains', 3, 6)
	put_y_value(4, 0)
	put_y_value(0, 1)
	put_y_value(5, 2)
	call_predicate('$build_var_tree/4$0', 3, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_x_variable(3, 3)
	put_y_value(3, 4)
	deallocate
	execute_predicate('$hash_uses_varonly', 5)
end('$build_var_tree'/4):



'$share_or_new'/7:

	try(7, $1)
	retry($2)
	trust($3)

$1:
	allocate(5)
	get_y_variable(1, 1)
	get_y_variable(4, 2)
	get_y_variable(0, 3)
	get_y_level(2)
	put_y_variable(3, 1)
	call_predicate('length', 2, 5)
	put_y_value(3, 0)
	get_y_value(4, 0)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_constant('true', 6)
	get_x_value(0, 4)
	get_x_value(1, 5)
	neck_cut
	proceed

$3:
	get_x_value(0, 1)
	proceed
end('$share_or_new'/7):



'$hash_uses_varonly'/5:

	switch_on_term(0, $7, $3, $4, $3, $3, $5)

$4:
	try(5, $2)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$3, '[]':$6])

$6:
	try(5, $1)
	trust($3)

$7:
	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('true', 3)
	get_x_value(1, 2)
	neck_cut
	proceed

$2:
	get_constant('true', 3)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_void(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('arg', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$3:
	get_constant('true', 3)
	get_structure(':', 2, 1)
	unify_x_variable(1)
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_value(0)
	get_structure(':', 2, 3)
	unify_constant('$default')
	unify_x_variable(0)
	get_x_value(0, 2)
	get_x_value(1, 4)
	proceed
end('$hash_uses_varonly'/5):



'$generate_index_instrs'/7:


$1:
	allocate(8)
	get_y_variable(3, 1)
	get_y_variable(7, 2)
	get_list(3)
	unify_y_variable(6)
	unify_x_variable(3)
	get_y_variable(2, 4)
	get_y_variable(4, 6)
	put_y_variable(0, 19)
	put_list(4)
	set_x_value(5)
	set_y_variable(1)
	put_y_variable(5, 5)
	call_predicate('$tree_to_instrs', 6, 8)
	put_y_value(6, 0)
	put_list(2)
	set_y_value(7)
	set_y_value(5)
	put_list(1)
	set_constant('switch_on_term')
	set_x_value(2)
	call_predicate('=..', 2, 5)
	put_y_value(4, 0)
	put_y_value(0, 1)
	call_predicate('$collect_labels', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$try_block', 4)
end('$generate_index_instrs'/7):



'$tree_to_instrs/6$0'/1:

	switch_on_term(0, $6, $1, $1, $3, $1, $1)

$3:
	switch_on_structure(0, 4, ['$default':$1, '$'/0:$4, 'label'/1:$5])

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
	pseudo_instr1(1, 0)
	proceed

$2:
	get_structure('label', 1, 0)
	unify_void(1)
	proceed
end('$tree_to_instrs/6$0'/1):



'$tree_to_instrs'/6:

	switch_on_term(0, $7, 'fail', $6, 'fail', 'fail', $1)

$6:
	try(6, $2)
	retry($3)
	retry($4)
	trust($5)

$7:
	try(6, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('[]', 0)
	get_constant('[]', 5)
	get_x_value(3, 4)
	proceed

$2:
	get_constant('[]', 5)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_x_variable(5)
	unify_x_variable(0)
	get_x_variable(6, 1)
	pseudo_instr1(1, 5)
	neck_cut
	put_x_value(5, 1)
	put_x_value(6, 2)
	execute_predicate('$try_or_fail', 5)

$3:
	get_list(0)
	unify_x_variable(0)
	allocate(7)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_list(5)
	unify_x_value(0)
	unify_y_variable(0)
	get_y_level(6)
	call_predicate('$tree_to_instrs/6$0', 1, 7)
	cut(6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$tree_to_instrs', 6)

$4:
	get_list(0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(5)
	get_structure(':', 2, 0)
	unify_x_variable(7)
	unify_x_variable(0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_x_variable(8, 3)
	get_y_variable(2, 4)
	get_list(5)
	unify_x_variable(6)
	unify_y_variable(1)
	pseudo_instr1(2, 7)
	neck_cut
	put_x_value(7, 2)
	put_y_value(3, 3)
	put_x_value(8, 4)
	put_y_variable(0, 5)
	call_predicate('$generate_hash', 7, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$tree_to_instrs', 6)

$5:
	get_list(0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 4)
	get_list(5)
	unify_x_variable(1)
	unify_y_variable(1)
	put_y_value(4, 2)
	put_y_variable(0, 4)
	call_predicate('$try_or_fail', 5, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$tree_to_instrs', 6)
end('$tree_to_instrs'/6):



'$generate_hash'/7:

	switch_on_term(0, $4, $3, $4, $3, $3, $3)

$4:
	try(7, $1)
	retry($2)
	trust($3)

$1:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_void(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('arg', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_x_value(4, 5)
	get_x_value(0, 6)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	allocate(4)
	get_y_variable(3, 1)
	get_list(4)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 5)
	get_x_value(1, 6)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$collect_labels', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$try_block', 4)

$3:
	get_x_variable(7, 1)
	get_x_variable(1, 3)
	get_list(4)
	unify_x_variable(8)
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(4)
	unify_x_variable(3)
	get_structure('switch', 4, 4)
	unify_x_value(2)
	unify_x_value(1)
	allocate(2)
	unify_y_variable(1)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(9)
	unify_y_variable(0)
	get_x_variable(4, 5)
	get_x_value(8, 6)
	put_y_value(0, 1)
	put_x_value(7, 2)
	put_x_value(9, 5)
	call_predicate('$hash_table', 6, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$size_table', 2)
end('$generate_hash'/7):



'$hash_table'/6:

	switch_on_term(0, $6, 'fail', $5, 'fail', 'fail', $1)

$5:
	try(6, $2)
	retry($3)
	trust($4)

$6:
	try(6, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	get_x_value(3, 4)
	proceed

$2:
	get_list(0)
	unify_x_ref(6)
	unify_x_variable(0)
	get_structure(':', 2, 6)
	unify_constant('$default')
	unify_x_variable(6)
	get_structure(':', 2, 5)
	unify_constant('$default')
	unify_x_value(6)
	pseudo_instr1(1, 6)
	neck_cut
	put_x_variable(5, 5)
	execute_predicate('$hash_table', 6)

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(4)
	get_structure(':', 2, 0)
	unify_constant('$default')
	unify_x_variable(0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 4)
	get_structure(':', 2, 5)
	unify_constant('$default')
	unify_x_variable(1)
	neck_cut
	put_y_variable(0, 4)
	call_predicate('$try_or_fail', 5, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(0, 3)
	put_y_value(1, 4)
	put_x_variable(5, 5)
	deallocate
	execute_predicate('$hash_table', 6)

$4:
	get_list(0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(5)
	get_structure(':', 2, 0)
	unify_x_variable(6)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(1)
	unify_y_variable(4)
	get_structure(':', 2, 1)
	unify_x_value(6)
	unify_x_variable(1)
	get_y_variable(3, 2)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	put_y_variable(0, 4)
	call_predicate('$try_or_fail', 5, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$hash_table', 6)
end('$hash_table'/6):



'$try_or_fail'/5:

	switch_on_term(0, $7, $3, $4, $3, $3, $5)

$4:
	try(5, $2)
	trust($3)

$5:
	switch_on_constant(0, 4, ['$default':$3, '[]':$6])

$6:
	try(5, $1)
	trust($3)

$7:
	try(5, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	get_constant('fail', 1)
	get_x_value(3, 4)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure('arg', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	get_x_value(0, 1)
	get_x_value(3, 4)
	neck_cut
	proceed

$3:
	allocate(4)
	get_y_variable(3, 2)
	get_list(3)
	unify_x_value(1)
	unify_y_variable(2)
	get_y_variable(1, 4)
	put_y_variable(0, 1)
	call_predicate('$collect_labels', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$try_block', 4)
end('$try_or_fail'/5):



'$try_block'/4:


$1:
	get_list(0)
	unify_x_variable(4)
	unify_x_variable(0)
	get_x_variable(5, 1)
	get_list(2)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure('try', 2, 2)
	unify_x_value(5)
	unify_x_value(4)
	get_x_variable(2, 3)
	execute_predicate('$retry_block', 3)
end('$try_block'/4):



'$retry_block'/3:

	switch_on_term(0, $3, 'fail', $3, 'fail', 'fail', 'fail')

$3:
	try(3, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	get_list(1)
	unify_x_ref(1)
	unify_x_variable(3)
	get_structure('trust', 1, 1)
	unify_x_value(0)
	get_x_value(3, 2)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure('retry', 1, 4)
	unify_x_value(3)
	execute_predicate('$retry_block', 3)
end('$retry_block'/3):



'$instantiate_labels'/2:

	switch_on_term(0, $8, $1, $5, $1, $1, $6)

$5:
	try(2, $1)
	retry($3)
	trust($4)

$6:
	switch_on_constant(0, 4, ['$default':$1, '[]':$7])

$7:
	try(2, $1)
	trust($2)

$8:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_constant('[]', 0)
	proceed

$3:
	get_list(0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('label', 1, 2)
	unify_x_variable(2)
	neck_cut
	pseudo_instr2(69, 1, 3)
	get_x_value(2, 3)
	put_x_value(2, 1)
	execute_predicate('$instantiate_labels', 2)

$4:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$instantiate_labels', 2)
end('$instantiate_labels'/2):



'$size_table'/2:


$1:
	allocate(2)
	get_y_variable(0, 1)
	put_y_variable(1, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 2)
	put_structure(2, 0)
	set_constant('-')
	set_y_value(1)
	set_integer(1)
	put_y_value(0, 2)
	put_integer(2, 1)
	call_predicate('$power_of_2', 3, 1)
	put_integer(65536, 0)
	pseudo_instr2(1, 20, 0)
	deallocate
	proceed
end('$size_table'/2):



'$power_of_2'/3:

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
	put_x_variable(4, 5)
	get_structure('>>', 2, 5)
	unify_x_value(0)
	unify_integer(1)
	pseudo_instr2(0, 3, 4)
	get_x_variable(0, 3)
	put_x_variable(4, 5)
	get_structure('<<', 2, 5)
	unify_x_value(1)
	unify_integer(1)
	pseudo_instr2(0, 3, 4)
	get_x_variable(1, 3)
	execute_predicate('$power_of_2', 3)
end('$power_of_2'/3):



'$extract_chains'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	execute_predicate('$collect_chains', 2)

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(2)
	get_structure('arg', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_y_variable(1, 1)
	put_x_value(3, 1)
	put_y_variable(0, 3)
	call_predicate('$update_chain', 4, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$extract_chains', 3)
end('$extract_chains'/3):



'$update_chain/4$0'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(4, 5)
	get_y_variable(1, 6)
	pseudo_instr1(1, 22)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	put_x_value(0, 2)
	put_y_variable(5, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_lookup', 4, 10)
	put_structure(2, 0)
	set_constant('/')
	set_y_value(8)
	set_y_value(7)
	put_structure(2, 2)
	set_constant(':')
	set_y_value(9)
	set_x_value(0)
	put_list(1)
	set_x_value(2)
	set_y_value(6)
	put_y_value(5, 2)
	put_y_value(3, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_set', 4, 5)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(0)
	set_void(1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_constant('var_chain', 0)
	call_predicate('$x_lookup', 4, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$copy_chain', 3)

$2:
	get_x_value(5, 1)
	proceed
end('$update_chain/4$0'/7):



'$update_chain/4$1'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(9, 2)
	get_y_variable(8, 3)
	get_y_variable(7, 4)
	get_y_variable(4, 5)
	get_y_variable(1, 6)
	pseudo_instr1(1, 22)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	put_x_value(0, 2)
	put_y_variable(5, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_lookup', 4, 10)
	put_structure(2, 0)
	set_constant('/')
	set_y_value(8)
	set_y_value(7)
	put_structure(2, 2)
	set_constant(':')
	set_y_value(9)
	set_x_value(0)
	put_list(1)
	set_x_value(2)
	set_y_value(6)
	put_y_value(5, 2)
	put_y_value(3, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_set', 4, 5)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(0)
	set_void(1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_constant('var_chain', 0)
	call_predicate('$x_lookup', 4, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$copy_chain', 3)

$2:
	get_x_value(5, 1)
	proceed
end('$update_chain/4$1'/7):



'$update_chain/4$2'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(9)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(8, 2)
	get_y_variable(7, 3)
	get_y_variable(4, 4)
	get_y_variable(1, 5)
	pseudo_instr1(1, 22)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	put_x_value(0, 2)
	put_y_variable(5, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_lookup', 4, 9)
	put_structure(2, 0)
	set_constant(':')
	set_y_value(8)
	set_y_value(7)
	put_list(1)
	set_x_value(0)
	set_y_value(6)
	put_y_value(5, 2)
	put_y_value(3, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_set', 4, 5)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(0)
	set_void(1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_constant('var_chain', 0)
	call_predicate('$x_lookup', 4, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$copy_chain', 3)

$2:
	get_x_value(4, 1)
	proceed
end('$update_chain/4$2'/6):



'$update_chain'/4:

	switch_on_term(0, $7, 'fail', 'fail', $5, 'fail', $1)

$5:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$6, 'struct'/1:$2, 'quant'/1:$3, 'const'/1:$4])

$6:
	try(4, $2)
	retry($3)
	trust($4)

$7:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('var', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(6)
	get_y_variable(2, 3)
	put_y_variable(4, 2)
	get_structure('arg', 2, 2)
	unify_constant('var')
	unify_x_value(0)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(4, 0)
	put_y_variable(5, 2)
	call_predicate('$add_to_chains', 3, 6)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_y_value(3)
	put_y_value(5, 2)
	put_y_value(0, 3)
	put_constant('var_chain', 0)
	call_predicate('$x_lookup', 4, 5)
	put_y_value(3, 0)
	get_list(0)
	unify_y_value(4)
	unify_x_variable(0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_x_value(0)
	put_y_value(0, 2)
	put_y_value(2, 3)
	put_constant('var_chain', 0)
	deallocate
	execute_predicate('$x_set', 4)

$2:
	get_structure('struct', 1, 0)
	unify_x_ref(0)
	get_structure('/', 2, 0)
	allocate(10)
	unify_y_variable(7)
	unify_y_variable(6)
	get_y_variable(5, 1)
	get_y_variable(9, 2)
	get_y_variable(3, 3)
	put_y_variable(8, 19)
	put_y_variable(4, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_variable(2, 3)
	put_constant('struct', 0)
	call_predicate('$struct_to_atom', 4, 10)
	put_y_value(2, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_y_value(4)
	put_y_value(9, 2)
	put_y_value(8, 3)
	call_predicate('$x_lookup', 4, 9)
	put_y_value(1, 0)
	put_y_value(8, 1)
	put_y_value(2, 2)
	put_y_value(7, 3)
	put_y_value(6, 4)
	put_y_value(0, 5)
	put_y_value(4, 6)
	call_predicate('$update_chain/4$0', 7, 8)
	put_y_value(4, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_variable(2)
	get_structure('arg', 2, 0)
	unify_x_ref(0)
	unify_y_value(5)
	get_structure('struct', 1, 0)
	unify_x_ref(0)
	get_structure('/', 2, 0)
	unify_y_value(7)
	unify_y_value(6)
	put_y_value(2, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_x_value(2)
	put_y_value(0, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$x_set', 4)

$3:
	get_structure('quant', 1, 0)
	unify_x_ref(0)
	get_structure('/', 2, 0)
	allocate(10)
	unify_y_variable(7)
	unify_y_variable(6)
	get_y_variable(5, 1)
	get_y_variable(9, 2)
	get_y_variable(3, 3)
	put_y_variable(8, 19)
	put_y_variable(4, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_variable(2, 3)
	put_constant('quant', 0)
	call_predicate('$struct_to_atom', 4, 10)
	put_y_value(2, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_y_value(4)
	put_y_value(9, 2)
	put_y_value(8, 3)
	call_predicate('$x_lookup', 4, 9)
	put_y_value(1, 0)
	put_y_value(8, 1)
	put_y_value(2, 2)
	put_y_value(7, 3)
	put_y_value(6, 4)
	put_y_value(0, 5)
	put_y_value(4, 6)
	call_predicate('$update_chain/4$1', 7, 8)
	put_y_value(4, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_variable(2)
	get_structure('arg', 2, 0)
	unify_x_ref(0)
	unify_y_value(5)
	get_structure('quant', 1, 0)
	unify_x_ref(0)
	get_structure('/', 2, 0)
	unify_y_value(7)
	unify_y_value(6)
	put_y_value(2, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_x_value(2)
	put_y_value(0, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$x_set', 4)

$4:
	get_structure('const', 1, 0)
	allocate(9)
	unify_y_variable(6)
	get_y_variable(5, 1)
	get_y_variable(8, 2)
	get_y_variable(3, 3)
	put_y_variable(7, 19)
	put_y_variable(4, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(6, 1)
	put_y_variable(2, 3)
	put_constant('const', 0)
	put_integer(0, 2)
	call_predicate('$struct_to_atom', 4, 9)
	put_y_value(2, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_y_value(4)
	put_y_value(8, 2)
	put_y_value(7, 3)
	call_predicate('$x_lookup', 4, 8)
	put_y_value(1, 0)
	put_y_value(7, 1)
	put_y_value(2, 2)
	put_y_value(6, 3)
	put_y_value(0, 4)
	put_y_value(4, 5)
	call_predicate('$update_chain/4$2', 6, 7)
	put_y_value(4, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_variable(2)
	get_structure('arg', 2, 0)
	unify_x_ref(0)
	unify_y_value(5)
	get_structure('const', 1, 0)
	unify_y_value(6)
	put_y_value(2, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(1)
	set_x_value(2)
	put_y_value(0, 2)
	put_y_value(3, 3)
	deallocate
	execute_predicate('$x_set', 4)
end('$update_chain'/4):



'$copy_chain'/3:

	switch_on_term(0, $3, $1, $3, $1, $1, $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_x_value(1, 2)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(3)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(3)
	unify_x_variable(1)
	execute_predicate('$copy_chain', 3)
end('$copy_chain'/3):



'$add_to_chains'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_x_variable(0, 1)
	get_y_variable(2, 2)
	put_y_variable(1, 1)
	put_x_value(0, 2)
	put_y_variable(0, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_lookup', 4, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$add_to_chains', 4)
end('$add_to_chains'/3):



'$add_to_chains'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(2, 3)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(8)
	unify_y_variable(3)
	get_structure(':', 2, 0)
	unify_y_variable(6)
	unify_void(1)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	put_y_variable(0, 19)
	put_y_value(6, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_variable(5)
	set_y_variable(7)
	put_y_variable(4, 3)
	call_predicate('$x_lookup', 4, 8)
	put_y_value(7, 0)
	get_list(0)
	unify_y_value(2)
	unify_x_variable(2)
	put_y_value(6, 0)
	put_structure(2, 1)
	set_constant('chain')
	set_y_value(5)
	set_x_value(2)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('$x_set', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$add_to_chains', 4)
end('$add_to_chains'/4):



'$collect_chains'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_x_variable(2, 1)
	put_y_variable(1, 1)
	put_y_variable(0, 3)
	put_constant('known_chains', 0)
	call_predicate('$x_lookup', 4, 3)
	put_y_value(1, 0)
	put_y_value(2, 2)
	put_y_value(0, 3)
	put_constant('[]', 1)
	deallocate
	execute_predicate('$collect_chains', 4)
end('$collect_chains'/2):



'$collect_chains'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(4)
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_y_variable(5)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_x_variable(2, 3)
	put_structure(2, 1)
	set_constant('chain')
	set_y_variable(1)
	set_constant('[]')
	put_y_variable(0, 3)
	call_predicate('$x_lookup', 4, 6)
	put_y_value(4, 0)
	put_structure(2, 2)
	set_constant(':')
	set_y_value(5)
	set_y_value(1)
	put_list(1)
	set_x_value(2)
	set_y_value(3)
	put_y_value(2, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$collect_chains', 4)
end('$collect_chains'/4):



'$struct_to_atom'/4:


$1:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_y_variable(0, 3)
	put_y_variable(4, 19)
	put_y_variable(1, 19)
	put_y_variable(5, 1)
	call_predicate('name', 2, 6)
	put_list(0)
	set_integer(47)
	set_constant('[]')
	put_y_value(5, 1)
	put_y_value(4, 2)
	call_predicate('append', 3, 5)
	put_y_value(1, 0)
	put_y_value(4, 1)
	call_predicate('name', 2, 4)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(3)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(2)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(1)
	unify_constant('[]')
	put_constant('/', 2)
	pseudo_instr3(28, 1, 2, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$struct_to_atom'/4):



'$search_body_unification'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 2)
	allocate(1)
	get_y_level(0)
	put_x_variable(2, 2)
	call_predicate('$search_body_unification_aux', 4, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_value(0, 2)
	proceed
end('$search_body_unification'/3):



'$search_body_unification_aux/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	put_constant('true', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	proceed

$2:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	put_x_value(4, 2)
	execute_predicate('$search_body_unification_aux', 4)
end('$search_body_unification_aux/4$0'/4):



'$search_body_unification_aux/4$1'/5:

	try(5, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr2(110, 0, 1)
	neck_cut
	put_constant('true', 0)
	get_x_value(2, 0)
	get_x_value(3, 4)
	proceed

$2:
	pseudo_instr2(110, 0, 4)
	neck_cut
	put_constant('true', 0)
	get_x_value(2, 0)
	get_x_value(3, 1)
	proceed

$3:
	proceed
end('$search_body_unification_aux/4$1'/5):



'$search_body_unification_aux'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	fail

$2:
	put_x_variable(0, 0)
	put_x_variable(2, 2)
	pseudo_instr3(0, 1, 0, 2)
	pseudo_instr1(1, 0)
	neck_cut
	fail

$3:
	allocate(4)
	get_y_variable(3, 0)
	get_structure(',', 2, 1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	call_predicate('$search_body_unification_aux', 4, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$search_body_unification_aux/4$0', 4)

$4:
	get_structure('$$get_level_ancestor$$', 1, 1)
	unify_void(1)
	neck_cut
	proceed

$5:
	get_structure('=', 2, 1)
	unify_x_variable(1)
	unify_x_variable(4)
	execute_predicate('$search_body_unification_aux/4$1', 5)
end('$search_body_unification_aux'/4):



