'$pretrans_clauses'/2:

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
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	call_predicate('$pretrans', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$pretrans_clauses', 2)
end('$pretrans_clauses'/2):



'$pretrans/2$0'/4:

	switch_on_term(0, $6, $1, $1, $3, $1, $1)

$3:
	switch_on_structure(0, 4, ['$default':$1, '$'/0:$4, '$$cut_ancestor$$'/1:$5])

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
	pseudo_instr1(1, 0)
	neck_cut
	put_x_value(1, 0)
	get_structure(':-', 2, 0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$2:
	get_structure('$$cut_ancestor$$', 1, 0)
	unify_x_variable(0)
	get_structure(':-', 2, 1)
	unify_x_value(2)
	unify_x_ref(1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_value(3)
	get_structure('$$get_level_ancestor$$', 1, 1)
	unify_x_value(0)
	proceed
end('$pretrans/2$0'/4):



'$pretrans'/2:

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
	allocate(5)
	unify_y_variable(3)
	unify_y_variable(4)
	get_y_variable(2, 1)
	neck_cut
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	call_predicate('$legal_goal', 1, 5)
	put_y_value(4, 0)
	put_y_value(1, 1)
	put_y_value(0, 4)
	put_constant('no', 2)
	put_constant('no', 3)
	call_predicate('$pretrans_formula', 5, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$pretrans/2$0', 4)

$2:
	get_x_value(0, 1)
	execute_predicate('$legal_goal', 1)
end('$pretrans'/2):



'$pretrans_formula/5$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_goal', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	fail
end('$pretrans_formula/5$0'/2):



'$pretrans_formula/5$1/7$0'/3:

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
end('$pretrans_formula/5$1/7$0'/3):



'$pretrans_formula/5$1'/7:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'atom':$4])

$4:
	try(7, $1)
	trust($2)

$5:
	try(7, $1)
	trust($2)

$1:
	get_x_variable(7, 1)
	allocate(5)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	put_constant('atom', 1)
	get_x_value(0, 1)
	neck_cut
	put_y_variable(0, 0)
	put_list(1)
	set_x_value(7)
	set_x_value(2)
	call_predicate('=..', 2, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$pretrans_formula1', 5)

$2:
	get_x_variable(7, 1)
	allocate(4)
	get_y_variable(2, 3)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 0)
	put_list(1)
	set_x_value(7)
	set_x_value(2)
	call_predicate('=..', 2, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(0, 4)
	put_constant('no', 2)
	put_constant('yes', 3)
	call_predicate('$pretrans_formula1', 5, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$pretrans_formula/5$1/7$0', 3)
end('$pretrans_formula/5$1'/7):



'$pretrans_formula'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(9)
	get_y_variable(8, 0)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_level(7)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_value(7, 1)
	call_predicate('$pretrans_formula/5$0', 2, 9)
	put_y_value(8, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	call_predicate('$flatten_call', 4, 8)
	cut(7)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	deallocate
	execute_predicate('$pretrans_formula/5$1', 7)

$2:
	get_structure('call', 1, 1)
	unify_x_value(0)
	proceed
end('$pretrans_formula'/5):



'$pretrans_formula1/5$0'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	get_x_value(1, 2)
	proceed

$2:
	put_x_value(1, 0)
	get_structure('$pretrans_block', 1, 0)
	unify_x_value(3)
	proceed
end('$pretrans_formula1/5$0'/4):



'$pretrans_formula1/5$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('$pretrans_formula1/5$1'/1):



'$pretrans_formula1/5$2'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	put_integer(1, 3)
	get_x_value(0, 3)
	get_x_value(1, 2)
	proceed

$2:
	pseudo_instr1(3, 2)
	put_integer(1, 3)
	get_x_value(2, 3)
	get_x_value(1, 0)
	proceed
end('$pretrans_formula1/5$2'/3):



'$pretrans_formula1/5$3'/1:

	try(1, $1)
	trust($2)

$1:
	put_x_variable(1, 1)
	put_integer(2, 2)
	pseudo_instr3(0, 0, 1, 2)
	put_constant('->', 0)
	pseudo_instr2(110, 1, 0)
	neck_cut
	fail

$2:
	proceed
end('$pretrans_formula1/5$3'/1):



'$pretrans_formula1'/5:

	switch_on_term(0, $49, $48, $48, $29, $48, $46)

$29:
	switch_on_structure(0, 32, ['$default':$48, '$'/0:$30, 'message_choice'/1:$31, 'write'/1:$32, 'writeq'/1:$33, 'put_code'/1:$34, 'write'/2:$35, 'writeq'/2:$36, '\\=='/2:$37, '=\\='/2:$38, '>='/2:$39, '>'/2:$40, 'is'/2:$41, '?='/2:$42, '->'/2:$43, ';'/2:$44, ','/2:$45])

$30:
	try(5, $1)
	retry($2)
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
	retry($18)
	retry($19)
	retry($20)
	retry($21)
	retry($22)
	retry($23)
	retry($24)
	retry($25)
	retry($26)
	retry($27)
	trust($28)

$31:
	try(5, $1)
	retry($2)
	retry($5)
	retry($27)
	trust($28)

$32:
	try(5, $1)
	retry($2)
	retry($6)
	retry($7)
	retry($27)
	trust($28)

$33:
	try(5, $1)
	retry($2)
	retry($8)
	retry($27)
	trust($28)

$34:
	try(5, $1)
	retry($2)
	retry($9)
	retry($27)
	trust($28)

$35:
	try(5, $1)
	retry($2)
	retry($10)
	retry($11)
	retry($27)
	trust($28)

$36:
	try(5, $1)
	retry($2)
	retry($12)
	retry($27)
	trust($28)

$37:
	try(5, $1)
	retry($2)
	retry($13)
	retry($27)
	trust($28)

$38:
	try(5, $1)
	retry($2)
	retry($14)
	retry($27)
	trust($28)

$39:
	try(5, $1)
	retry($2)
	retry($15)
	retry($27)
	trust($28)

$40:
	try(5, $1)
	retry($2)
	retry($16)
	retry($27)
	trust($28)

$41:
	try(5, $1)
	retry($2)
	retry($17)
	retry($18)
	retry($19)
	retry($20)
	retry($27)
	trust($28)

$42:
	try(5, $1)
	retry($2)
	retry($21)
	retry($27)
	trust($28)

$43:
	try(5, $1)
	retry($2)
	retry($22)
	retry($27)
	trust($28)

$44:
	try(5, $1)
	retry($2)
	retry($23)
	retry($24)
	retry($25)
	retry($27)
	trust($28)

$45:
	try(5, $1)
	retry($2)
	retry($26)
	retry($27)
	trust($28)

$46:
	switch_on_constant(0, 4, ['$default':$48, '!':$47])

$47:
	try(5, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($27)
	trust($28)

$48:
	try(5, $1)
	retry($2)
	retry($27)
	trust($28)

$49:
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
	retry($14)
	retry($15)
	retry($16)
	retry($17)
	retry($18)
	retry($19)
	retry($20)
	retry($21)
	retry($22)
	retry($23)
	retry($24)
	retry($25)
	retry($26)
	retry($27)
	trust($28)

$1:
	get_x_variable(5, 0)
	allocate(5)
	get_y_variable(3, 1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 5, 0, 1)
	get_y_level(4)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_x_value(5, 2)
	put_y_variable(2, 3)
	call_predicate('$inline', 4, 5)
	cut(4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 4)
	put_constant('no', 2)
	put_constant('yes', 3)
	call_predicate('$pretrans_formula', 5, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	deallocate
	execute_predicate('$pretrans_formula1/5$0', 4)

$2:
	get_x_variable(5, 0)
	get_structure('call', 1, 1)
	unify_x_value(5)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 5, 0, 1)
	allocate(1)
	get_y_level(0)
	call_predicate('$pretrans_formula1/5$1', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_constant('!', 0)
	put_constant('yes', 0)
	pseudo_instr2(110, 3, 0)
	neck_cut
	put_constant('yes', 0)
	get_x_value(4, 0)
	put_constant('!', 0)
	get_x_value(1, 0)
	proceed

$4:
	get_constant('!', 0)
	put_constant('yes', 0)
	pseudo_instr2(110, 2, 0)
	neck_cut
	put_x_value(4, 0)
	get_structure('$$cut_ancestor$$', 1, 0)
	unify_void(1)
	get_x_value(1, 4)
	proceed

$5:
	get_structure('message_choice', 1, 0)
	unify_x_variable(0)
	allocate(6)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_level(5)
	put_y_variable(0, 1)
	call_predicate('$mc_inline', 2, 6)
	cut(5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$pretrans_formula', 5)

$6:
	get_structure('write', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(5)
	get_structure('current_output', 1, 1)
	unify_x_variable(1)
	get_structure('write_integer', 2, 5)
	unify_x_value(1)
	unify_x_value(0)
	pseudo_instr1(3, 0)
	neck_cut
	proceed

$7:
	get_structure('write', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(5)
	get_structure('current_output', 1, 1)
	unify_x_variable(1)
	get_structure('write_atom', 2, 5)
	unify_x_value(1)
	unify_x_value(0)
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$8:
	get_structure('writeq', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(5)
	get_structure('current_output', 1, 1)
	unify_x_variable(1)
	get_structure('writeq_atom', 2, 5)
	unify_x_value(1)
	unify_x_value(0)
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$9:
	get_structure('put_code', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(5)
	get_structure('current_output', 1, 1)
	unify_x_variable(1)
	get_structure('put_code', 2, 5)
	unify_x_value(1)
	unify_x_value(0)
	neck_cut
	proceed

$10:
	get_structure('write', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('write_integer', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	pseudo_instr1(3, 5)
	neck_cut
	proceed

$11:
	get_structure('write', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('write_atom', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	pseudo_instr1(2, 5)
	neck_cut
	proceed

$12:
	get_structure('writeq', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('writeq_atom', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	pseudo_instr1(2, 5)
	neck_cut
	proceed

$13:
	get_structure('\\==', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('\\+', 1, 1)
	unify_x_ref(1)
	get_structure('==', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	neck_cut
	proceed

$14:
	get_structure('=\\=', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('\\+', 1, 1)
	unify_x_ref(1)
	get_structure('=:=', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	neck_cut
	proceed

$15:
	get_structure('>=', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('=<', 2, 1)
	unify_x_value(5)
	unify_x_value(0)
	neck_cut
	proceed

$16:
	get_structure('>', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('<', 2, 1)
	unify_x_value(5)
	unify_x_value(0)
	neck_cut
	proceed

$17:
	get_structure('is', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('$increment', 2, 1)
	unify_x_variable(1)
	unify_x_value(0)
	pseudo_instr1(0, 5)
	put_x_value(5, 0)
	get_structure('+', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	allocate(1)
	get_y_level(0)
	call_predicate('$pretrans_formula1/5$2', 3, 1)
	cut(0)
	deallocate
	proceed

$18:
	get_structure('is', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('$decrement', 2, 1)
	unify_x_variable(1)
	unify_x_value(0)
	pseudo_instr1(0, 5)
	put_x_value(5, 0)
	get_structure('-', 2, 0)
	unify_x_value(1)
	unify_x_variable(0)
	pseudo_instr1(3, 0)
	put_integer(1, 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$19:
	get_structure('is', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('$add', 3, 1)
	unify_x_variable(1)
	unify_x_variable(6)
	unify_x_value(0)
	pseudo_instr1(0, 5)
	put_x_value(5, 0)
	get_structure('+', 2, 0)
	unify_x_value(1)
	unify_x_value(6)
	neck_cut
	proceed

$20:
	get_structure('is', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('$subtract', 3, 1)
	unify_x_variable(1)
	unify_x_variable(6)
	unify_x_value(0)
	pseudo_instr1(0, 5)
	put_x_value(5, 0)
	get_structure('-', 2, 0)
	unify_x_value(1)
	unify_x_value(6)
	neck_cut
	proceed

$21:
	get_structure('?=', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure('\\+', 1, 1)
	unify_x_ref(1)
	get_structure('\\+', 1, 1)
	unify_x_ref(1)
	get_structure('=', 2, 1)
	unify_x_value(0)
	unify_x_value(5)
	neck_cut
	proceed

$22:
	get_structure('->', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_structure('$if_then', 2, 1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	neck_cut
	put_constant('yes', 2)
	call_predicate('$pretrans_formula', 5, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 3)
	put_y_value(0, 4)
	put_constant('yes', 2)
	deallocate
	execute_predicate('$pretrans_formula', 5)

$23:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_y_variable(2, 1)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	pseudo_instr1(1, 0)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	put_constant('yes', 2)
	call_predicate('$pretrans_formula', 5, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_constant('yes', 2)
	call_predicate('$pretrans_formula', 5, 3)
	put_y_value(2, 0)
	get_structure(';', 2, 0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed

$24:
	get_structure(';', 2, 0)
	allocate(7)
	unify_y_variable(5)
	unify_y_variable(3)
	get_structure(';', 2, 1)
	unify_y_variable(4)
	unify_y_variable(2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	get_y_level(6)
	put_y_value(5, 0)
	call_predicate('$pretrans_formula1/5$3', 1, 7)
	cut(6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(1, 3)
	put_y_value(0, 4)
	put_constant('yes', 2)
	call_predicate('$pretrans_formula', 5, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 3)
	put_y_value(0, 4)
	put_constant('yes', 2)
	deallocate
	execute_predicate('$pretrans_formula', 5)

$25:
	get_structure(';', 2, 0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(3)
	get_structure('->', 2, 0)
	unify_x_variable(0)
	unify_y_variable(5)
	get_structure('$if_then_else', 3, 1)
	unify_x_variable(1)
	unify_y_variable(4)
	unify_y_variable(2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	neck_cut
	put_constant('yes', 2)
	call_predicate('$pretrans_formula', 5, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(1, 3)
	put_y_value(0, 4)
	put_constant('yes', 2)
	call_predicate('$pretrans_formula', 5, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 3)
	put_y_value(0, 4)
	put_constant('yes', 2)
	deallocate
	execute_predicate('$pretrans_formula', 5)

$26:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(5)
	unify_y_variable(4)
	get_structure(',', 2, 1)
	unify_x_variable(1)
	unify_y_variable(3)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	neck_cut
	call_predicate('$pretrans_formula', 5, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$pretrans_formula', 5)

$27:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('closed_list', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$expand_consult', 2)

$28:
	get_x_value(0, 1)
	proceed
end('$pretrans_formula1'/5):



'$expand_consult/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(2, 0)
	proceed
end('$expand_consult/2$0'/1):



'$expand_consult/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(2, 0)
	proceed
end('$expand_consult/2$1'/1):



'$expand_consult'/2:

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
	get_constant('true', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(1)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_y_variable(0)
	get_structure('consult', 1, 1)
	unify_x_value(0)
	get_y_level(2)
	call_predicate('$expand_consult/2$0', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$expand_consult', 2)

$3:
	get_list(0)
	unify_x_ref(0)
	allocate(3)
	unify_y_variable(1)
	get_structure('-', 1, 0)
	unify_x_variable(0)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_y_variable(0)
	get_structure('reconsult', 1, 1)
	unify_x_value(0)
	get_y_level(2)
	call_predicate('$expand_consult/2$1', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$expand_consult', 2)

$4:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	execute_predicate('$expand_consult', 2)
end('$expand_consult'/2):



