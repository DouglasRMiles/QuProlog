'dcg'/2:


$1:
	get_structure('-->', 2, 0)
	unify_x_variable(0)
	allocate(7)
	unify_y_variable(6)
	get_y_variable(3, 1)
	put_y_variable(0, 19)
	put_y_variable(5, 1)
	put_y_variable(4, 2)
	put_y_variable(2, 3)
	put_y_variable(1, 4)
	call_predicate('$dcg_expand_head', 5, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('$dcg_expand_body', 4, 4)
	put_y_value(3, 0)
	get_structure(':-', 2, 0)
	unify_y_value(2)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_y_value(1)
	deallocate
	proceed
end('dcg'/2):



'C'/3:


$1:
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_value(0, 1)
	get_x_value(3, 2)
	proceed
end('C'/3):



'phrase'/2:


$1:
	allocate(1)
	put_y_variable(0, 3)
	put_constant('[]', 2)
	call_predicate('$dcg_expand_body', 4, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('phrase'/2):



'phrase'/3:


$1:
	allocate(1)
	put_y_variable(0, 3)
	call_predicate('$dcg_expand_body', 4, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('phrase'/3):



'$dcg_expand_head'/5:

	switch_on_term(0, $9, $8, $8, $5, $8, $8)

$5:
	switch_on_structure(0, 4, ['$default':$8, '$'/0:$6, ','/2:$7])

$6:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$8:
	try(5, $1)
	retry($3)
	trust($4)

$9:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 2)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(0, 2)
	put_x_variable(4, 4)
	call_predicate('$dcg_expand_head', 5, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$dcg_expand_body', 4)

$3:
	get_constant('true', 4)
	pseudo_instr1(2, 0)
	neck_cut
	put_integer(2, 4)
	pseudo_instr3(0, 3, 0, 4)
	put_integer(1, 4)
	pseudo_instr3(1, 4, 3, 0)
	get_x_value(1, 0)
	put_integer(2, 1)
	pseudo_instr3(1, 1, 3, 0)
	get_x_value(2, 0)
	proceed

$4:
	get_constant('true', 4)
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(0, 2)
	get_y_variable(1, 3)
	pseudo_instr1(0, 0)
	neck_cut
	put_x_variable(1, 1)
	put_x_variable(3, 3)
	pseudo_instr3(0, 0, 1, 3)
	pseudo_instr2(69, 3, 2)
	get_y_variable(4, 2)
	put_integer(2, 4)
	pseudo_instr3(2, 3, 4, 2)
	get_y_variable(2, 2)
	pseudo_instr3(0, 21, 1, 22)
	put_y_value(1, 1)
	put_integer(1, 2)
	call_predicate('$same_args', 4, 5)
	pseudo_instr3(1, 24, 21, 0)
	get_y_value(3, 0)
	pseudo_instr3(1, 22, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$dcg_expand_head'/5):



'$dcg_expand_body'/4:

	switch_on_term(0, $26, $25, $14, $15, $25, $22)

$14:
	try(4, $1)
	retry($10)
	retry($11)
	retry($12)
	trust($13)

$15:
	switch_on_structure(0, 16, ['$default':$25, '$'/0:$16, ','/2:$17, ';'/2:$18, '->'/2:$19, '\\+'/1:$20, '{}'/1:$21])

$16:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($8)
	retry($12)
	trust($13)

$17:
	try(4, $1)
	retry($2)
	retry($12)
	trust($13)

$18:
	try(4, $1)
	retry($3)
	retry($4)
	retry($12)
	trust($13)

$19:
	try(4, $1)
	retry($5)
	retry($12)
	trust($13)

$20:
	try(4, $1)
	retry($6)
	retry($12)
	trust($13)

$21:
	try(4, $1)
	retry($8)
	retry($12)
	trust($13)

$22:
	switch_on_constant(0, 4, ['$default':$25, '!':$23, '[]':$24])

$23:
	try(4, $1)
	retry($7)
	retry($12)
	trust($13)

$24:
	try(4, $1)
	retry($9)
	retry($12)
	trust($13)

$25:
	try(4, $1)
	retry($12)
	trust($13)

$26:
	try(4, $1)
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
	pseudo_instr1(1, 0)
	neck_cut
	get_structure('=', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	get_x_value(1, 2)
	proceed

$2:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_y_variable(4, 2)
	get_y_variable(2, 3)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(3, 2)
	put_y_variable(1, 3)
	call_predicate('$dcg_expand_body', 4, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('$dcg_expand_body', 4, 3)
	put_y_value(2, 0)
	get_structure(',', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$3:
	get_structure(';', 2, 0)
	unify_x_ref(0)
	allocate(11)
	unify_y_variable(8)
	get_structure('->', 2, 0)
	unify_x_variable(0)
	unify_y_variable(10)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(9, 2)
	put_y_variable(4, 3)
	call_predicate('$dcg_expand_body', 4, 11)
	put_y_value(10, 0)
	put_y_value(9, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	call_predicate('$dcg_expand_body', 4, 9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	call_predicate('$dcg_expand_body', 4, 7)
	put_y_value(5, 0)
	get_structure(';', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('->', 2, 0)
	unify_y_value(4)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_y_value(2)
	unify_x_ref(0)
	get_structure('=', 2, 0)
	unify_y_value(6)
	unify_y_value(3)
	get_structure(',', 2, 1)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure('=', 2, 0)
	unify_y_value(6)
	unify_y_value(1)
	deallocate
	proceed

$4:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(8)
	unify_y_variable(7)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	neck_cut
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 2)
	put_y_variable(2, 3)
	call_predicate('$dcg_expand_body', 4, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	call_predicate('$dcg_expand_body', 4, 6)
	put_y_value(4, 0)
	get_structure(';', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure(',', 2, 0)
	unify_y_value(2)
	unify_x_ref(0)
	get_structure('=', 2, 0)
	unify_y_value(5)
	unify_y_value(3)
	get_structure(',', 2, 1)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure('=', 2, 0)
	unify_y_value(5)
	unify_y_value(1)
	deallocate
	proceed

$5:
	get_structure('->', 2, 0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_y_variable(4, 2)
	get_y_variable(2, 3)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(3, 2)
	put_y_variable(1, 3)
	call_predicate('$dcg_expand_body', 4, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	call_predicate('$dcg_expand_body', 4, 3)
	put_y_value(2, 0)
	get_structure('->', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$6:
	get_structure('\\+', 1, 0)
	unify_x_variable(0)
	allocate(4)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	neck_cut
	put_x_variable(2, 2)
	put_y_variable(0, 3)
	call_predicate('$dcg_expand_body', 4, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_structure('\\+', 1, 0)
	unify_y_value(0)
	deallocate
	proceed

$7:
	get_constant('!', 0)
	get_x_value(1, 2)
	neck_cut
	put_constant('!', 0)
	get_x_value(3, 0)
	proceed

$8:
	get_structure('{}', 1, 0)
	unify_x_variable(0)
	get_x_value(1, 2)
	neck_cut
	get_x_value(3, 0)
	proceed

$9:
	get_constant('[]', 0)
	get_x_value(1, 2)
	neck_cut
	put_constant('true', 0)
	get_x_value(3, 0)
	proceed

$10:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	neck_cut
	get_structure('C', 3, 3)
	unify_x_value(1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$11:
	get_list(0)
	unify_x_variable(0)
	unify_x_ref(4)
	get_list(4)
	unify_x_variable(4)
	unify_x_variable(5)
	allocate(3)
	get_y_variable(2, 3)
	neck_cut
	put_y_variable(1, 3)
	get_structure('C', 3, 3)
	unify_x_value(1)
	unify_x_value(0)
	unify_x_variable(1)
	put_list(0)
	set_x_value(4)
	set_x_value(5)
	put_y_variable(0, 3)
	call_predicate('$dcg_expand_body', 4, 3)
	put_y_value(2, 0)
	get_structure(',', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$12:
	allocate(4)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	pseudo_instr1(108, 0)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('string_to_list', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$dcg_expand_body', 4)

$13:
	put_x_variable(4, 4)
	execute_predicate('$dcg_expand_head', 5)
end('$dcg_expand_body'/4):



