'findall'/3:


$1:
	get_x_variable(3, 0)
	pseudo_instr1(91, 0)
	get_x_variable(4, 0)
	allocate(1)
	get_y_level(0)
	put_structure(4, 0)
	set_constant('$findall')
	set_x_value(4)
	set_x_value(1)
	set_x_value(3)
	set_x_value(2)
	put_x_variable(2, 1)
	put_structure(1, 3)
	set_constant('$dealloc_buffer')
	set_x_value(4)
	put_structure(1, 4)
	set_constant('throw')
	set_x_value(2)
	put_structure(2, 2)
	set_constant(',')
	set_x_value(3)
	set_x_value(4)
	call_predicate('catch', 3, 1)
	cut(0)
	deallocate
	proceed
end('findall'/3):



'$findall'/4:


$1:
	allocate(2)
	get_y_variable(1, 3)
	put_y_variable(0, 3)
	call_predicate('$findall1', 4, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$findall'/4):



'$findall1'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	get_y_variable(0, 2)
	call_predicate('call', 1, 2)
	put_constant('fail', 0)
	pseudo_instr3(27, 21, 20, 0)
	fail

$2:
	pseudo_instr2(12, 0, 1)
	get_x_value(3, 1)
	pseudo_instr1(92, 0)
	proceed
end('$findall1'/4):



'bagof'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_level(6)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_value(4, 0)
	put_y_value(5, 1)
	put_y_variable(1, 2)
	call_predicate('$free_vars', 3, 7)
	put_constant('[]', 0)
	pseudo_instr2(133, 21, 0)
	cut(6)
	put_structure(2, 0)
	set_constant(',')
	set_y_value(1)
	set_y_value(5)
	put_y_value(4, 1)
	put_y_value(3, 2)
	call_predicate('findall', 3, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	call_predicate('$bag_sort', 2, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$extract_bag', 3)

$2:
	allocate(1)
	get_y_variable(0, 2)
	call_predicate('findall', 3, 1)
	put_constant('[]', 0)
	pseudo_instr2(133, 20, 0)
	deallocate
	proceed
end('bagof'/3):



'setof'/3:


$1:
	allocate(2)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('bagof', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('sort', 2)
end('setof'/3):



'$free_vars'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	put_y_variable(1, 1)
	call_predicate('$separate_goal_from_bound_vars', 2, 4)
	pseudo_instr2(67, 23, 0)
	put_x_variable(2, 3)
	get_list(3)
	unify_y_value(2)
	unify_y_value(1)
	pseudo_instr2(67, 2, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('diff_list', 3)
end('$free_vars'/3):



'$separate_goal_from_bound_vars'/2:

	switch_on_term(0, $24, $23, $23, $12, $23, $23)

$12:
	switch_on_structure(0, 32, ['$default':$23, '$'/0:$13, '\\+'/1:$14, 'call'/1:$15, 'once'/1:$16, ','/2:$17, ';'/2:$18, '->'/2:$19, '^'/2:$20, 'bagof'/3:$21, 'setof'/3:$22])

$13:
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
	trust($11)

$14:
	try(2, $1)
	retry($2)
	trust($11)

$15:
	try(2, $1)
	retry($3)
	trust($11)

$16:
	try(2, $1)
	retry($4)
	trust($11)

$17:
	try(2, $1)
	retry($5)
	trust($11)

$18:
	try(2, $1)
	retry($6)
	trust($11)

$19:
	try(2, $1)
	retry($7)
	trust($11)

$20:
	try(2, $1)
	retry($8)
	trust($11)

$21:
	try(2, $1)
	retry($9)
	trust($11)

$22:
	try(2, $1)
	retry($10)
	trust($11)

$23:
	try(2, $1)
	trust($11)

$24:
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
	trust($11)

$1:
	get_constant('[]', 1)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_structure('\\+', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$separate_goal_from_bound_vars', 2)

$3:
	get_structure('call', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$separate_goal_from_bound_vars', 2)

$4:
	get_structure('once', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$separate_goal_from_bound_vars', 2)

$5:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$separate_goal_from_bound_vars', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$separate_goal_from_bound_vars', 2)

$6:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$separate_goal_from_bound_vars', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$separate_goal_from_bound_vars', 2)

$7:
	get_structure('->', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$separate_goal_from_bound_vars', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$separate_goal_from_bound_vars', 2)

$8:
	get_structure('^', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	neck_cut
	execute_predicate('$separate_goal_from_bound_vars', 2)

$9:
	get_structure('bagof', 3, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	unify_void(1)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	neck_cut
	execute_predicate('$separate_goal_from_bound_vars', 2)

$10:
	get_structure('setof', 3, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	unify_void(1)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	neck_cut
	execute_predicate('$separate_goal_from_bound_vars', 2)

$11:
	get_constant('[]', 1)
	proceed
end('$separate_goal_from_bound_vars'/2):



'$extract_bag/3$0'/6:

	try(6, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	put_x_value(2, 0)
	get_list(0)
	unify_x_value(3)
	unify_x_value(4)
	proceed

$2:
	get_x_variable(6, 0)
	get_x_variable(0, 5)
	put_x_value(6, 1)
	execute_predicate('$extract_bag', 3)
end('$extract_bag/3$0'/6):



'$extract_bag'/3:


$1:
	get_list(0)
	unify_x_ref(3)
	unify_x_variable(0)
	get_structure(',', 2, 3)
	allocate(6)
	unify_y_variable(5)
	unify_y_variable(4)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	put_y_value(5, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$split_bag', 4, 6)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$extract_bag/3$0', 6)
end('$extract_bag'/3):



'$split_bag'/4:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(4, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_ref(4)
	unify_x_variable(0)
	get_structure(',', 2, 4)
	unify_x_variable(4)
	unify_x_variable(5)
	get_list(2)
	unify_x_value(5)
	unify_x_variable(2)
	get_x_value(4, 1)
	neck_cut
	execute_predicate('$split_bag', 4)

$2:
	get_constant('[]', 2)
	get_x_value(0, 3)
	proceed
end('$split_bag'/4):



'$alpha_equiv/4$0'/4:

	try(4, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr3(6, 0, 1, 4)
	put_constant('true', 0)
	get_x_value(4, 0)
	neck_cut
	get_x_value(2, 3)
	proceed

$2:
	get_x_variable(1, 3)
	allocate(1)
	get_y_level(0)
	call_predicate('member_eq', 2, 1)
	cut(0)
	fail

$3:
	get_list(2)
	unify_x_value(0)
	unify_x_value(3)
	get_x_value(0, 1)
	proceed
end('$alpha_equiv/4$0'/4):



'$alpha_equiv'/4:

	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(4, 2)
	get_x_variable(2, 3)
	pseudo_instr1(1, 0)
	neck_cut
	pseudo_instr1(1, 1)
	put_x_value(4, 3)
	execute_predicate('$alpha_equiv/4$0', 4)

$2:
	get_x_value(2, 3)
	pseudo_instr1(43, 0)
	neck_cut
	pseudo_instr3(6, 0, 1, 2)
	put_constant('true', 0)
	get_x_value(2, 0)
	proceed

$3:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	put_x_variable(0, 0)
	put_y_variable(1, 19)
	pseudo_instr3(0, 24, 0, 21)
	put_x_variable(1, 1)
	put_x_variable(3, 3)
	pseudo_instr3(0, 23, 1, 3)
	get_y_value(1, 3)
	put_y_variable(0, 3)
	call_predicate('$alpha_equiv', 4, 5)
	put_y_value(1, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(0, 4)
	put_y_value(2, 5)
	put_integer(0, 0)
	deallocate
	execute_predicate('$alpha_equiv_args', 6)
end('$alpha_equiv'/4):



'$alpha_equiv_args'/6:

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
	pseudo_instr3(1, 21, 23, 1)
	put_y_variable(0, 3)
	call_predicate('$alpha_equiv', 4, 6)
	put_y_value(1, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(0, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$alpha_equiv_args', 6)
end('$alpha_equiv_args'/6):



'$bag_sort'/2:


$1:
	put_constant('$bag_compare', 2)
	execute_predicate('$merge_sort', 3)
end('$bag_sort'/2):



'$bag_compare'/2:


$1:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	get_structure(',', 2, 1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr2(130, 0, 1)
	proceed
end('$bag_compare'/2):



'sort'/2:


$1:
	put_constant('@<', 2)
	execute_predicate('$merge_sort', 3)
end('sort'/2):



'sort'/3:


$1:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$merge_sort', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$remove_sorted_duplicates', 2)
end('sort'/3):



'msort'/2:


$1:
	put_constant('@<', 2)
	execute_predicate('$merge_sort', 3)
end('msort'/2):



'msort'/3:


$1:
	execute_predicate('$merge_sort', 3)
end('msort'/3):



'$key_order'/2:


$1:
	get_structure('-', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	get_structure('-', 2, 1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr2(130, 0, 1)
	proceed
end('$key_order'/2):



'keysort'/2:


$1:
	put_constant('$key_order', 2)
	execute_predicate('msort', 3)
end('keysort'/2):



'$merge_sort'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(0, 1)
	call_predicate('length', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 4)
	put_constant('[]', 3)
	deallocate
	execute_predicate('$merge_sort', 5)
end('$merge_sort'/3):



'$merge_sort'/5:

	switch_on_term(0, $9, $4, $4, $4, $4, $5)

$5:
	switch_on_constant(0, 8, ['$default':$4, 0:$6, 1:$7, 2:$8])

$6:
	try(5, $1)
	trust($4)

$7:
	try(5, $2)
	trust($4)

$8:
	try(5, $3)
	trust($4)

$9:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_integer(0, 0)
	get_constant('[]', 2)
	neck_cut
	proceed

$2:
	get_integer(1, 0)
	get_list(1)
	unify_x_variable(0)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(0)
	unify_constant('[]')
	get_x_value(1, 3)
	neck_cut
	proceed

$3:
	get_integer(2, 0)
	get_list(1)
	unify_x_variable(0)
	unify_x_ref(1)
	get_list(1)
	unify_x_variable(1)
	unify_x_variable(5)
	get_x_value(5, 3)
	get_x_variable(3, 4)
	neck_cut
	execute_predicate('$merge_sort2', 4)

$4:
	allocate(8)
	get_y_variable(7, 0)
	get_y_variable(3, 2)
	get_y_variable(5, 3)
	get_y_variable(2, 4)
	put_x_variable(2, 3)
	get_structure('//', 2, 3)
	unify_y_value(7)
	unify_integer(2)
	pseudo_instr2(0, 0, 2)
	get_y_variable(6, 0)
	put_y_variable(0, 19)
	put_y_variable(1, 2)
	put_y_variable(4, 3)
	call_predicate('$merge_sort', 5, 8)
	pseudo_instr3(3, 27, 26, 0)
	put_y_value(4, 1)
	put_y_value(0, 2)
	put_y_value(5, 3)
	put_y_value(2, 4)
	call_predicate('$merge_sort', 5, 4)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$merge', 4)
end('$merge_sort'/5):



'$merge_sort2'/4:

	try(4, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(4, 0)
	get_x_variable(5, 1)
	get_list(2)
	unify_x_value(4)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(5)
	unify_constant('[]')
	get_x_variable(0, 3)
	allocate(1)
	get_y_level(0)
	put_x_value(4, 1)
	put_x_value(5, 2)
	call_predicate('call_predicate', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(4, 0)
	get_list(2)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(4)
	unify_constant('[]')
	get_x_variable(0, 3)
	allocate(1)
	get_y_level(0)
	put_x_value(4, 2)
	call_predicate('call_predicate', 3, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_list(2)
	unify_x_value(0)
	unify_constant('[]')
	proceed
end('$merge_sort2'/4):



'$merge'/4:

	switch_on_term(0, $9, $5, $6, $5, $5, $7)

$6:
	try(4, $1)
	retry($2)
	retry($3)
	trust($5)

$7:
	switch_on_constant(0, 4, ['$default':$5, '[]':$8])

$8:
	try(4, $4)
	trust($5)

$9:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_list(0)
	allocate(6)
	unify_y_variable(4)
	unify_y_variable(3)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_list(2)
	unify_x_value(1)
	unify_y_variable(1)
	get_y_variable(0, 3)
	get_y_level(5)
	put_y_value(0, 0)
	put_y_value(4, 2)
	call_predicate('call_predicate', 3, 6)
	cut(5)
	put_list(0)
	set_y_value(4)
	set_y_value(3)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$merge', 4)

$2:
	get_list(0)
	unify_x_variable(4)
	allocate(6)
	unify_y_variable(4)
	get_list(1)
	unify_y_variable(3)
	unify_y_variable(2)
	get_list(2)
	unify_x_value(4)
	unify_y_variable(1)
	get_y_variable(0, 3)
	get_y_level(5)
	put_y_value(0, 0)
	put_x_value(4, 1)
	put_y_value(3, 2)
	call_predicate('call_predicate', 3, 6)
	cut(5)
	put_y_value(4, 0)
	put_list(1)
	set_y_value(3)
	set_y_value(2)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$merge', 4)

$3:
	get_list(0)
	unify_x_variable(4)
	unify_x_variable(0)
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	get_list(2)
	unify_x_value(4)
	unify_x_variable(2)
	neck_cut
	execute_predicate('$merge', 4)

$4:
	get_constant('[]', 0)
	get_x_value(1, 2)
	neck_cut
	proceed

$5:
	get_constant('[]', 1)
	get_x_value(0, 2)
	proceed
end('$merge'/4):



'$remove_sorted_duplicates'/2:

	switch_on_term(0, $6, 'fail', $5, 'fail', 'fail', $1)

$5:
	try(2, $2)
	retry($3)
	trust($4)

$6:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	get_list(1)
	unify_x_value(0)
	unify_constant('[]')
	neck_cut
	proceed

$3:
	get_list(0)
	unify_x_variable(2)
	unify_x_ref(0)
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(3)
	pseudo_instr2(110, 2, 0)
	neck_cut
	put_list(0)
	set_x_value(2)
	set_x_value(3)
	execute_predicate('$remove_sorted_duplicates', 2)

$4:
	get_list(0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$remove_sorted_duplicates', 2)
end('$remove_sorted_duplicates'/2):



'^'/2:


$1:
	get_x_variable(0, 1)
	execute_predicate('call_predicate', 1)
end('^'/2):



'forall/2$0/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('forall/2$0/2$0'/1):



'forall/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 1)
	get_y_level(0)
	call_predicate('call', 1, 2)
	put_y_value(1, 0)
	call_predicate('forall/2$0/2$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('forall/2$0'/2):



'forall'/2:


$1:
	execute_predicate('forall/2$0', 2)
end('forall'/2):



