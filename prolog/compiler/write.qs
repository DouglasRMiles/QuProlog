'$write_pred'/2:


$1:
	allocate(2)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	call_predicate('$warg', 1, 2)
	call_predicate('$colon', 0, 2)
	call_predicate('nl', 0, 2)
	call_predicate('nl', 0, 2)
	put_y_value(1, 0)
	call_predicate('$write_instr_nice', 1, 1)
	put_constant('end(', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 1)
	put_y_value(0, 0)
	call_predicate('$warg', 1, 0)
	put_integer(41, 0)
	call_predicate('put', 1, 0)
	call_predicate('$colon', 0, 0)
	call_predicate('nl', 0, 0)
	call_predicate('nl', 0, 0)
	call_predicate('nl', 0, 0)
	deallocate
	execute_predicate('nl', 0)
end('$write_pred'/2):



'$write_instr_nice'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 0)
	put_x_value(2, 1)
	call_predicate('member', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('$write_instr', 2, 0)
	fail

$2:
	proceed
end('$write_instr_nice'/2):



'$write_instr'/2:

	switch_on_term(0, $8, $3, $3, $4, $3, $3)

$4:
	switch_on_structure(0, 8, ['$default':$3, '$'/0:$5, 'label'/1:$6, 'comment'/1:$7])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	trust($3)

$7:
	try(2, $2)
	trust($3)

$8:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_structure('label', 1, 0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	put_y_value(0, 0)
	call_predicate('nl', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$wlabel', 2, 1)
	put_y_value(0, 0)
	call_predicate('$colon', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('nl', 1)

$2:
	get_structure('comment', 1, 0)
	unify_void(1)
	neck_cut
	proceed

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$customize', 2, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$winstr', 2)
end('$write_instr'/2):



'$make_anonymous'/1:

	switch_on_term(0, $5, 'fail', $4, 'fail', 'fail', $1)

$4:
	try(1, $2)
	trust($3)

$5:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_constant('_')
	unify_x_variable(0)
	neck_cut
	execute_predicate('$make_anonymous', 1)

$3:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$make_anonymous', 1)
end('$make_anonymous'/1):



'$write_clause'/1:

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
	allocate(2)
	unify_y_variable(1)
	unify_y_variable(0)
	neck_cut
	put_integer(9, 0)
	call_predicate('put', 1, 2)
	put_constant(' * ', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 2)
	put_y_value(1, 0)
	call_predicate('writeq', 1, 1)
	put_constant(' :-', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 1)
	call_predicate('nl', 0, 1)
	put_y_value(0, 0)
	call_predicate('$write_body', 1, 0)
	put_integer(46, 0)
	call_predicate('put', 1, 0)
	deallocate
	execute_predicate('nl', 0)

$2:
	allocate(1)
	get_y_variable(0, 0)
	put_integer(9, 0)
	call_predicate('put', 1, 1)
	put_constant(' * ', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 1)
	put_y_value(0, 0)
	call_predicate('writeq', 1, 0)
	put_integer(46, 0)
	call_predicate('put', 1, 0)
	deallocate
	execute_predicate('nl', 0)
end('$write_clause'/1):



'$write_body'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, ','/2:$5])

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
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('$write_body', 1, 1)
	put_integer(44, 0)
	call_predicate('put', 1, 1)
	call_predicate('nl', 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$write_body', 1)

$2:
	allocate(1)
	get_y_variable(0, 0)
	put_integer(9, 0)
	call_predicate('put', 1, 1)
	put_constant(' * ', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 1)
	put_integer(32, 0)
	call_predicate('put', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('writeq', 1)
end('$write_body'/1):



'$colon'/1:


$1:
	put_integer(58, 1)
	execute_predicate('put', 2)
end('$colon'/1):



'$wname'/2:


$1:
	allocate(2)
	get_y_variable(0, 1)
	put_y_variable(1, 1)
	call_predicate('name', 2, 2)
	put_y_value(0, 0)
	put_integer(39, 1)
	call_predicate('put', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$wname_list', 2, 1)
	put_y_value(0, 0)
	put_integer(39, 1)
	deallocate
	execute_predicate('put', 2)
end('$wname'/2):



'$wname_list/2$0/2$0'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 39:$1, 92:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_integer(39, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(92, 1)
	get_x_value(0, 1)
	proceed
end('$wname_list/2$0/2$0'/1):



'$wname_list/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('$wname_list/2$0/2$0', 1, 3)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('put', 2)

$2:
	proceed
end('$wname_list/2$0'/2):



'$wname_list'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	allocate(3)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	put_y_value(2, 0)
	call_predicate('$wname_list/2$0', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('put', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$wname_list', 2)
end('$wname_list'/2):



'$wlabel'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	put_integer(36, 1)
	call_predicate('put', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('[]', 2)
	deallocate
	execute_predicate('write_term', 3)
end('$wlabel'/2):



'$winstr/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(0, 1)
	get_y_variable(1, 2)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 22)
	neck_cut
	put_y_value(0, 0)
	put_integer(40, 1)
	call_predicate('put', 2, 3)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	put_integer(1, 0)
	call_predicate('$warg', 4, 1)
	put_y_value(0, 0)
	put_integer(41, 1)
	deallocate
	execute_predicate('put', 2)

$2:
	proceed
end('$winstr/2$0'/3):



'$winstr'/2:


$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(0, 1)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	pseudo_instr3(0, 22, 23, 21)
	put_y_value(0, 0)
	put_integer(9, 1)
	call_predicate('put', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	call_predicate('$winstr/2$0', 3, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('nl', 1)
end('$winstr'/2):



'$warg'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	get_x_variable(1, 3)
	neck_cut
	pseudo_instr3(1, 0, 2, 3)
	get_x_variable(0, 3)
	execute_predicate('$warg', 2)

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	pseudo_instr3(1, 23, 21, 0)
	put_y_value(0, 1)
	call_predicate('$warg', 2, 4)
	put_y_value(0, 0)
	put_constant(', ', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 4)
	pseudo_instr2(69, 23, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$warg', 4)
end('$warg'/4):



'$warg'/2:

	switch_on_term(0, $18, $17, $9, $10, $17, $17)

$9:
	try(2, $6)
	retry($7)
	trust($8)

$10:
	switch_on_structure(0, 16, ['$default':$17, '$'/0:$11, 'label'/1:$12, '$default'/1:$13, '/'/2:$14, '$xreg'/1:$15, '$yreg'/1:$16])

$11:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$12:
	try(2, $1)
	retry($6)
	trust($7)

$13:
	try(2, $2)
	retry($6)
	trust($7)

$14:
	try(2, $3)
	retry($6)
	trust($7)

$15:
	try(2, $4)
	retry($6)
	trust($7)

$16:
	try(2, $5)
	retry($6)
	trust($7)

$17:
	try(2, $6)
	trust($7)

$18:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_structure('label', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('$wlabel', 2)

$2:
	get_structure('$default', 1, 0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	put_constant('$default', 0)
	call_predicate('$wname', 2, 2)
	put_y_value(0, 0)
	put_integer(40, 1)
	call_predicate('put', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$wlabel', 2, 1)
	put_y_value(0, 0)
	put_integer(41, 1)
	deallocate
	execute_predicate('put', 2)

$3:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	call_predicate('$wname', 2, 2)
	put_y_value(0, 0)
	put_integer(47, 1)
	call_predicate('put', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('[]', 2)
	deallocate
	execute_predicate('write_term', 3)

$4:
	get_structure('$xreg', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	put_constant('[]', 2)
	execute_predicate('write_term', 3)

$5:
	get_structure('$yreg', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	put_constant('[]', 2)
	execute_predicate('write_term', 3)

$6:
	pseudo_instr1(2, 0)
	neck_cut
	execute_predicate('$wname', 2)

$7:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(3, 2)
	neck_cut
	put_x_value(2, 1)
	put_constant('[]', 2)
	execute_predicate('write_term', 3)

$8:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_list(0)
	unify_void(2)
	neck_cut
	put_y_value(0, 0)
	put_integer(91, 1)
	call_predicate('put', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$whash', 2, 1)
	put_y_value(0, 0)
	put_integer(93, 1)
	deallocate
	execute_predicate('put', 2)
end('$warg'/2):



'$whash'/2:

	switch_on_term(0, $3, 'fail', $3, 'fail', 'fail', 'fail')

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_ref(0)
	unify_constant('[]')
	get_structure(':', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	call_predicate('$warg', 2, 2)
	put_y_value(0, 0)
	call_predicate('$colon', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$warg', 2)

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(1)
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_y_variable(2)
	get_y_variable(0, 1)
	call_predicate('$warg', 2, 3)
	put_y_value(0, 0)
	call_predicate('$colon', 1, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$warg', 2, 2)
	put_y_value(0, 0)
	put_constant(', ', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$whash', 2)
end('$whash'/2):



