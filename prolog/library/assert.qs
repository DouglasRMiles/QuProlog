'$legal_goal/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	fail

$2:
	proceed
end('$legal_goal/1$0'/1):



'$legal_goal/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(6, 0)
	neck_cut
	fail

$2:
	proceed
end('$legal_goal/1$1'/1):



'$legal_goal'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_level(0)
	call_predicate('$legal_goal/1$0', 1, 2)
	pseudo_instr1(1, 21)
	cut(0)
	deallocate
	proceed

$2:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$3:
	allocate(2)
	get_y_variable(1, 0)
	get_y_level(0)
	call_predicate('$legal_goal/1$1', 1, 2)
	pseudo_instr1(0, 21)
	cut(0)
	deallocate
	proceed

$4:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('Error: The goal/predicate ', 0)
	call_predicate('error', 1, 1)
	put_y_value(0, 0)
	call_predicate('errornl', 1, 0)
	put_constant('must be either an atom, a variable or a', 0)
	call_predicate('errornl', 1, 0)
	put_constant('compound term without a substitution at the outer level', 0)
	call_predicate('errornl', 1, 0)
	fail
end('$legal_goal'/1):



'$legal_body/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_goal', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$legal_body/1$0'/1):



'$legal_body/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('$legal_body/1$1'/1):



'$legal_body'/1:

	switch_on_term(0, $18, $17, $17, $11, $17, $17)

$11:
	switch_on_structure(0, 16, ['$default':$17, '$'/0:$12, ','/2:$13, ';'/2:$14, 'once'/1:$15, '\\+'/1:$16])

$12:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$13:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($10)

$14:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($6)
	retry($7)
	trust($10)

$15:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($8)
	trust($10)

$16:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($9)
	trust($10)

$17:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($10)

$18:
	try(1, $1)
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
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_body/1$0', 1, 1)
	cut(0)
	fail

$3:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$4:
	get_x_variable(1, 0)
	pseudo_instr1(0, 1)
	put_x_variable(0, 0)
	put_x_variable(2, 2)
	pseudo_instr3(0, 1, 0, 2)
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_body/1$1', 1, 1)
	cut(0)
	deallocate
	proceed

$5:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_level(0)
	call_predicate('$legal_body', 1, 2)
	put_y_value(1, 0)
	call_predicate('$legal_body', 1, 1)
	cut(0)
	deallocate
	proceed

$6:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(0)
	pseudo_instr1(46, 0)
	pseudo_instr1(0, 0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	pseudo_instr3(0, 0, 1, 2)
	pseudo_instr1(2, 1)
	get_structure('->', 2, 0)
	unify_x_variable(0)
	unify_y_variable(1)
	neck_cut
	call_predicate('$legal_body', 1, 2)
	put_y_value(1, 0)
	call_predicate('$legal_body', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$legal_body', 1)

$7:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_level(0)
	call_predicate('$legal_body', 1, 2)
	put_y_value(1, 0)
	call_predicate('$legal_body', 1, 1)
	cut(0)
	deallocate
	proceed

$8:
	get_structure('once', 1, 0)
	unify_x_variable(0)
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_body', 1, 1)
	cut(0)
	deallocate
	proceed

$9:
	get_structure('\\+', 1, 0)
	unify_x_variable(0)
	allocate(1)
	get_y_level(0)
	call_predicate('$legal_body', 1, 1)
	cut(0)
	deallocate
	proceed

$10:
	pseudo_instr1(0, 0)
	proceed
end('$legal_body'/1):



'$legal_clause_head/1$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '.':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('.', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$legal_clause_head/1$0'/1):



'$legal_clause_head'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$2:
	get_x_variable(1, 0)
	put_x_variable(0, 0)
	put_x_variable(2, 2)
	pseudo_instr3(0, 1, 0, 2)
	pseudo_instr1(2, 0)
	execute_predicate('$legal_clause_head/1$0', 1)
end('$legal_clause_head'/1):



'$is_dynamic/1$0'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 0:$1, 1:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(1, 1)
	get_x_value(0, 1)
	proceed
end('$is_dynamic/1$0'/1):



'$is_dynamic/1$1'/1:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 0:$1, 1:$2])

$4:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	proceed

$2:
	put_integer(1, 1)
	get_x_value(0, 1)
	proceed
end('$is_dynamic/1$1'/1):



'$is_dynamic'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	put_integer(0, 2)
	pseudo_instr3(33, 0, 2, 1)
	get_x_variable(0, 1)
	execute_predicate('$is_dynamic/1$0', 1)

$2:
	pseudo_instr1(0, 0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	pseudo_instr3(0, 0, 1, 2)
	pseudo_instr3(33, 1, 2, 0)
	execute_predicate('$is_dynamic/1$1', 1)
end('$is_dynamic'/1):



'assert'/1:


$1:
	put_integer(1, 1)
	execute_predicate('assert', 2)
end('assert'/1):



'asserta'/1:


$1:
	put_integer(0, 1)
	execute_predicate('assert', 2)
end('asserta'/1):



'assertz'/1:


$1:
	put_integer(1, 1)
	execute_predicate('assert', 2)
end('assertz'/1):



'assert/2$0'/2:

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
end('assert/2$0'/2):



'assert/2$1'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$is_dynamic', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(2, 3)
	set_constant(':-')
	set_x_value(0)
	set_x_value(1)
	put_structure(2, 1)
	set_constant('assert')
	set_x_value(3)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	allocate(0)
	call_predicate('exception', 1, 0)
	fail
end('assert/2$1'/3):



'assert/2$2'/2:

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
end('assert/2$2'/2):



'assert/2$3'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$is_dynamic', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(2, 2)
	set_constant('assert')
	set_x_value(0)
	set_x_value(1)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_constant('default')
	allocate(0)
	call_predicate('exception', 1, 0)
	fail
end('assert/2$3'/2):



'assert'/2:

	switch_on_term(0, $9, $8, $8, $5, $8, $8)

$5:
	switch_on_structure(0, 4, ['$default':$8, '$'/0:$6, ':-'/2:$7])

$6:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$8:
	try(2, $1)
	retry($3)
	trust($4)

$9:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(1, 0)
	set_constant('assert')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('assert')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure(':-', 2, 0)
	allocate(4)
	unify_y_variable(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	get_y_level(3)
	pseudo_instr1(46, 22)
	get_y_level(3)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('assert/2$0', 2, 4)
	put_y_value(2, 0)
	call_predicate('$legal_clause_head', 1, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	call_predicate('assert/2$1', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$assert_clause', 3)

$3:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(2, 1)
	call_predicate('assert/2$2', 2, 3)
	put_y_value(1, 0)
	call_predicate('$legal_clause_head', 1, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('assert/2$3', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 2)
	put_constant('true', 1)
	deallocate
	execute_predicate('$assert_clause', 3)

$4:
	get_x_variable(2, 0)
	put_structure(1, 0)
	set_constant('assert')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('assert')
	set_x_value(1)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('assert')
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('assert'/2):



'$assert_clause/3$0/3$0/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 1)
	get_y_level(0)
	call_predicate('$legal_goal', 1, 2)
	put_y_value(1, 0)
	call_predicate('$legal_body', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 2)
	cut(0)
	fail
end('$assert_clause/3$0/3$0/3$0'/3):



'$assert_clause/3$0/3$0/3$1'/4:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$dbcompile', 4, 1)
	cut(0)
	deallocate
	proceed
end('$assert_clause/3$0/3$0/3$1'/4):



'$assert_clause/3$0/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(2, 2)
	get_y_level(0)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_value(0, 2)
	call_predicate('$assert_clause/3$0/3$0/3$0', 3, 7)
	call_predicate('$ignore_delays', 0, 7)
	put_integer(1, 0)
	put_integer(0, 1)
	pseudo_instr2(10, 0, 1)
	put_x_variable(0, 1)
	get_structure(',', 2, 1)
	unify_y_value(6)
	unify_y_value(5)
	pseudo_instr1(52, 0)
	put_y_value(6, 0)
	put_y_value(4, 1)
	call_predicate('$correct_name', 2, 6)
	put_x_variable(1, 2)
	get_structure(',', 2, 2)
	unify_y_value(4)
	unify_y_value(5)
	pseudo_instr2(95, 1, 0)
	get_structure(',', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	call_predicate('$assert_clause/3$0/3$0/3$1', 4, 5)
	pseudo_instr4(11, 24, 23, 22, 0)
	get_y_value(1, 0)
	cut(0)
	fail

$2:
	proceed
end('$assert_clause/3$0/3$0'/3):



'$assert_clause/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$assert_clause/3$0/3$0', 3, 1)
	cut(0)
	fail

$2:
	proceed
end('$assert_clause/3$0'/3):



'$assert_clause'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr0(16)
	allocate(0)
	call_predicate('$assert_clause/3$0', 3, 0)
	fail

$2:
	pseudo_instr0(17)
	proceed
end('$assert_clause'/3):



'$dbcompile/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_x_value(1, 0)
	get_list(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$2:
	allocate(11)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(9, 3)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(10, 1)
	put_y_variable(7, 2)
	put_y_variable(8, 3)
	call_predicate('$pseudo_instruction', 4, 11)
	put_y_value(10, 0)
	put_y_value(4, 1)
	put_y_value(6, 2)
	put_x_variable(3, 3)
	call_predicate('$psinstr_process', 4, 10)
	put_y_value(8, 0)
	put_y_value(9, 1)
	put_y_value(5, 2)
	call_predicate('append', 3, 8)
	put_y_value(6, 0)
	put_list(1)
	set_y_value(7)
	set_y_value(5)
	put_y_value(3, 2)
	call_predicate('append', 3, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(0, 2)
	call_predicate('append', 3, 3)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(1)
	unify_y_value(0)
	deallocate
	proceed
end('$dbcompile/4$0'/4):



'$dbcompile'/4:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_y_variable(2, 19)
	put_x_variable(2, 2)
	put_y_variable(4, 3)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	put_y_variable(3, 7)
	put_constant('no_cut', 1)
	put_constant('[]', 4)
	call_predicate('$db_internal_form', 8, 6)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	call_predicate('$dbcompile/4$0', 4, 3)
	put_constant('assert', 1)
	pseudo_instr4(12, 22, 1, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$dbcompile'/4):



'$db_internal_form/8$0'/5:

	try(5, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('done', 5)
	get_x_value(0, 5)
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('call', 1, 0)
	unify_x_value(3)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('call', 1, 0)
	unify_x_value(3)
	proceed
end('$db_internal_form/8$0'/5):



'$db_internal_form/8$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('$db_internal_form/8$1'/1):



'$db_internal_form/8$2'/5:

	try(5, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('done', 5)
	get_x_value(0, 5)
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('call', 1, 0)
	unify_x_value(3)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('call', 1, 0)
	unify_x_value(3)
	proceed
end('$db_internal_form/8$2'/5):



'$db_internal_form/8$3'/6:

	try(6, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('done', 6)
	get_x_value(0, 6)
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_x_ref(0)
	unify_x_value(5)
	get_structure('$message_choice', 2, 0)
	unify_x_value(3)
	unify_x_value(4)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(5)
	get_structure('$message_choice', 2, 0)
	unify_x_value(3)
	unify_x_value(4)
	proceed
end('$db_internal_form/8$3'/6):



'$db_internal_form/8$4'/8:

	try(8, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('done', 8)
	get_x_value(0, 8)
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_x_ref(0)
	unify_x_value(7)
	get_structure('$ite_call', 4, 0)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(6)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(7)
	get_structure('$ite_call', 4, 0)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(6)
	proceed
end('$db_internal_form/8$4'/8):



'$db_internal_form/8$5'/7:

	try(7, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('done', 7)
	get_x_value(0, 7)
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$$get_level$$', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_x_ref(0)
	unify_x_value(6)
	get_structure('$or_call', 3, 0)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	proceed

$2:
	put_x_value(1, 0)
	get_list(0)
	unify_x_ref(0)
	unify_x_value(6)
	get_structure('$or_call', 3, 0)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	proceed
end('$db_internal_form/8$5'/7):



'$db_internal_form'/8:

	switch_on_term(0, $28, $27, $27, $17, $27, $24)

$17:
	switch_on_structure(0, 16, ['$default':$27, '$'/0:$18, ','/2:$19, 'message_choice'/1:$20, ';'/2:$21, '$$get_level_ancestor$$'/1:$22, '='/2:$23])

$18:
	try(8, $1)
	retry($2)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($11)
	retry($12)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$19:
	try(8, $1)
	retry($2)
	retry($4)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$20:
	try(8, $1)
	retry($2)
	retry($5)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$21:
	try(8, $1)
	retry($2)
	retry($6)
	retry($7)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$22:
	try(8, $1)
	retry($2)
	retry($11)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$23:
	try(8, $1)
	retry($2)
	retry($12)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$24:
	switch_on_constant(0, 4, ['$default':$27, 'true':$25, '!':$26])

$25:
	try(8, $1)
	retry($2)
	retry($3)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$26:
	try(8, $1)
	retry($2)
	retry($8)
	retry($9)
	retry($10)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$27:
	try(8, $1)
	retry($2)
	retry($13)
	retry($14)
	retry($15)
	trust($16)

$28:
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
	trust($16)

$1:
	get_constant('no_cut', 2)
	get_x_variable(8, 0)
	get_x_variable(1, 3)
	get_x_variable(2, 5)
	get_x_variable(0, 6)
	pseudo_instr1(1, 8)
	neck_cut
	put_x_value(8, 3)
	execute_predicate('$db_internal_form/8$0', 5)

$2:
	get_constant('no_cut', 2)
	allocate(6)
	get_y_variable(4, 0)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	pseudo_instr1(0, 24)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 24, 0, 1)
	get_y_level(5)
	call_predicate('$db_internal_form/8$1', 1, 6)
	cut(5)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(4, 3)
	put_y_value(2, 4)
	deallocate
	execute_predicate('$db_internal_form/8$2', 5)

$3:
	get_constant('true', 0)
	get_constant('no_cut', 2)
	get_x_value(3, 4)
	neck_cut
	proceed

$4:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(8)
	unify_y_variable(7)
	get_y_variable(6, 2)
	get_y_variable(5, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	neck_cut
	put_y_variable(1, 2)
	put_y_variable(0, 4)
	call_predicate('$db_internal_form', 8, 8)
	put_y_value(7, 0)
	put_y_value(1, 1)
	put_y_value(6, 2)
	put_y_value(0, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(3, 6)
	put_y_value(2, 7)
	deallocate
	execute_predicate('$db_internal_form', 8)

$5:
	get_constant('no_cut', 2)
	get_structure('message_choice', 1, 0)
	unify_x_variable(8)
	get_x_variable(1, 3)
	get_x_variable(9, 4)
	get_x_variable(2, 5)
	get_x_variable(0, 6)
	neck_cut
	put_x_value(7, 3)
	get_structure('$get_level', 1, 3)
	unify_x_variable(4)
	put_x_value(8, 3)
	put_x_value(9, 5)
	execute_predicate('$db_internal_form/8$3', 6)

$6:
	get_constant('no_cut', 2)
	get_structure(';', 2, 0)
	unify_x_variable(8)
	unify_x_variable(9)
	get_x_variable(1, 3)
	get_x_variable(10, 4)
	get_x_variable(2, 5)
	get_x_variable(0, 6)
	pseudo_instr1(46, 8)
	pseudo_instr1(0, 8)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	pseudo_instr3(0, 8, 3, 4)
	pseudo_instr1(2, 3)
	put_x_value(8, 3)
	get_structure('->', 2, 3)
	unify_x_variable(3)
	unify_x_variable(4)
	neck_cut
	put_x_value(7, 5)
	get_structure('$get_level', 1, 5)
	unify_x_variable(6)
	put_x_value(9, 5)
	put_x_value(10, 7)
	execute_predicate('$db_internal_form/8$4', 8)

$7:
	get_constant('no_cut', 2)
	get_structure(';', 2, 0)
	unify_x_variable(8)
	unify_x_variable(9)
	get_x_variable(1, 3)
	get_x_variable(10, 4)
	get_x_variable(2, 5)
	get_x_variable(0, 6)
	neck_cut
	put_x_value(7, 3)
	get_structure('$get_level', 1, 3)
	unify_x_variable(5)
	put_x_value(8, 3)
	put_x_value(9, 4)
	put_x_value(10, 6)
	execute_predicate('$db_internal_form/8$5', 7)

$8:
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

$9:
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

$10:
	get_constant('!', 0)
	get_constant('cut', 1)
	get_constant('cut', 2)
	get_x_value(3, 4)
	neck_cut
	proceed

$11:
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

$12:
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

$13:
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

$14:
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

$15:
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

$16:
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
end('$db_internal_form'/8):



