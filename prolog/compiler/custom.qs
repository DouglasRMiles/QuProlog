'$customize'/2:

	switch_on_term(0, $52, 'fail', 'fail', $45, 'fail', $51)

$45:
	switch_on_structure(0, 64, ['$default':'fail', '$'/0:$46, 'put'/3:$1, 'get'/3:$2, 'unify_ref'/1:$47, 'unify'/2:$5, 'set'/2:$6, 'check_binder'/1:$7, 'allocate'/1:$8, 'call_predicate'/3:$10, 'call_address'/2:$11, 'call_escape'/2:$12, 'execute_predicate'/2:$13, 'execute_address'/1:$14, 'execute_escape'/1:$15, '$pseudo_instr0'/1:$16, '$pseudo_instr1'/2:$17, '$pseudo_instr2'/3:$18, '$pseudo_instr3'/4:$19, '$pseudo_instr4'/5:$20, '$pseudo_instr5'/6:$21, 'try_me_else'/2:$28, 'retry_me_else'/1:$29, 'try'/2:$31, 'retry'/1:$32, 'trust'/1:$33, '$$get_level$$'/1:$48, '$$get_level_ancestor$$'/1:$49, '$$cut$$'/1:$39, '$$cut_ancestor$$'/1:$40, 'switch_on_term'/7:$41, 'switch'/4:$50])

$46:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
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
	retry($28)
	retry($29)
	retry($31)
	retry($32)
	retry($33)
	retry($35)
	retry($36)
	retry($37)
	retry($38)
	retry($39)
	retry($40)
	retry($41)
	retry($42)
	retry($43)
	trust($44)

$47:
	try(2, $3)
	trust($4)

$48:
	try(2, $35)
	trust($36)

$49:
	try(2, $37)
	trust($38)

$50:
	try(2, $42)
	retry($43)
	trust($44)

$51:
	switch_on_constant(0, 32, ['$default':'fail', 'deallocate':$9, 'noop':$22, 'jump':$23, 'proceed':$24, 'fail':$25, 'halt':$26, 'exit':$27, 'trust_me_else_fail':$30, 'neck_cut':$34])

$52:
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
	retry($28)
	retry($29)
	retry($30)
	retry($31)
	retry($32)
	retry($33)
	retry($34)
	retry($35)
	retry($36)
	retry($37)
	retry($38)
	retry($39)
	retry($40)
	retry($41)
	retry($42)
	retry($43)
	trust($44)

$1:
	get_structure('put', 3, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	unify_x_variable(2)
	get_x_variable(3, 1)
	put_x_value(4, 1)
	execute_predicate('$customize_put', 4)

$2:
	get_structure('get', 3, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	unify_x_variable(2)
	get_x_variable(3, 1)
	put_x_value(4, 1)
	execute_predicate('$customize_get', 4)

$3:
	get_structure('unify_ref', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('unify_x_ref', 1, 1)
	unify_x_value(0)
	proceed

$4:
	get_structure('unify_ref', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('unify_y_ref', 1, 1)
	unify_x_value(0)
	proceed

$5:
	get_structure('unify', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	execute_predicate('$customize_unify', 3)

$6:
	get_structure('set', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	execute_predicate('$customize_set', 3)

$7:
	get_structure('check_binder', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('check_binder', 1, 1)
	unify_x_value(0)
	proceed

$8:
	get_structure('allocate', 1, 0)
	unify_x_variable(0)
	get_structure('allocate', 1, 1)
	unify_x_value(0)
	proceed

$9:
	get_constant('deallocate', 0)
	get_constant('deallocate', 1)
	proceed

$10:
	get_structure('call_predicate', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('call_predicate', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$11:
	get_structure('call_address', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('call_address', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$12:
	get_structure('call_escape', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('call_escape', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$13:
	get_structure('execute_predicate', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('execute_predicate', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$14:
	get_structure('execute_address', 1, 0)
	unify_x_variable(0)
	get_structure('execute_address', 1, 1)
	unify_x_value(0)
	proceed

$15:
	get_structure('execute_escape', 1, 0)
	unify_x_variable(0)
	get_structure('execute_escape', 1, 1)
	unify_x_value(0)
	proceed

$16:
	get_structure('$pseudo_instr0', 1, 0)
	unify_x_variable(0)
	get_structure('pseudo_instr0', 1, 1)
	unify_x_value(0)
	proceed

$17:
	get_structure('$pseudo_instr1', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_structure('pseudo_instr1', 2, 1)
	unify_x_value(2)
	unify_x_variable(1)
	execute_predicate('$ps_custom_arg', 2)

$18:
	get_structure('$pseudo_instr2', 3, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_structure('pseudo_instr2', 3, 1)
	unify_x_value(2)
	unify_x_variable(1)
	unify_y_variable(0)
	call_predicate('$ps_custom_arg', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$ps_custom_arg', 2)

$19:
	get_structure('$pseudo_instr3', 4, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	unify_y_variable(1)
	get_structure('pseudo_instr3', 4, 1)
	unify_x_value(2)
	unify_x_variable(1)
	unify_y_variable(2)
	unify_y_variable(0)
	call_predicate('$ps_custom_arg', 2, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$ps_custom_arg', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$ps_custom_arg', 2)

$20:
	get_structure('$pseudo_instr4', 5, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	unify_y_variable(3)
	unify_y_variable(1)
	get_structure('pseudo_instr4', 5, 1)
	unify_x_value(2)
	unify_x_variable(1)
	unify_y_variable(4)
	unify_y_variable(2)
	unify_y_variable(0)
	call_predicate('$ps_custom_arg', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	call_predicate('$ps_custom_arg', 2, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$ps_custom_arg', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$ps_custom_arg', 2)

$21:
	get_structure('$pseudo_instr5', 6, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	allocate(8)
	unify_y_variable(7)
	unify_y_variable(5)
	unify_y_variable(3)
	unify_y_variable(1)
	get_structure('pseudo_instr5', 6, 1)
	unify_x_value(2)
	unify_x_variable(1)
	unify_y_variable(6)
	unify_y_variable(4)
	unify_y_variable(2)
	unify_y_variable(0)
	call_predicate('$ps_custom_arg', 2, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	call_predicate('$ps_custom_arg', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	call_predicate('$ps_custom_arg', 2, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$ps_custom_arg', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$ps_custom_arg', 2)

$22:
	get_constant('noop', 0)
	get_constant('noop', 1)
	proceed

$23:
	get_constant('jump', 0)
	get_constant('jump', 1)
	proceed

$24:
	get_constant('proceed', 0)
	get_constant('proceed', 1)
	proceed

$25:
	get_constant('fail', 0)
	get_constant('fail', 1)
	proceed

$26:
	get_constant('halt', 0)
	get_constant('halt', 1)
	proceed

$27:
	get_constant('exit', 0)
	get_constant('exit', 1)
	proceed

$28:
	get_structure('try_me_else', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('try_me_else', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$29:
	get_structure('retry_me_else', 1, 0)
	unify_x_variable(0)
	get_structure('retry_me_else', 1, 1)
	unify_x_value(0)
	proceed

$30:
	get_constant('trust_me_else_fail', 0)
	get_constant('trust_me_else_fail', 1)
	proceed

$31:
	get_structure('try', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('try', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$32:
	get_structure('retry', 1, 0)
	unify_x_variable(0)
	get_structure('retry', 1, 1)
	unify_x_value(0)
	proceed

$33:
	get_structure('trust', 1, 0)
	unify_x_variable(0)
	get_structure('trust', 1, 1)
	unify_x_value(0)
	proceed

$34:
	get_constant('neck_cut', 0)
	get_constant('neck_cut', 1)
	proceed

$35:
	get_structure('$$get_level$$', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('get_x_level', 1, 1)
	unify_x_value(0)
	proceed

$36:
	get_structure('$$get_level$$', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('get_y_level', 1, 1)
	unify_x_value(0)
	proceed

$37:
	get_structure('$$get_level_ancestor$$', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('get_x_level', 1, 1)
	unify_x_value(0)
	proceed

$38:
	get_structure('$$get_level_ancestor$$', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('get_y_level', 1, 1)
	unify_x_value(0)
	proceed

$39:
	get_structure('$$cut$$', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('cut', 1, 1)
	unify_x_value(0)
	proceed

$40:
	get_structure('$$cut_ancestor$$', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('cut', 1, 1)
	unify_x_value(0)
	proceed

$41:
	get_structure('switch_on_term', 7, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_x_variable(5)
	unify_x_variable(6)
	unify_x_variable(7)
	get_structure('switch_on_term', 7, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(6)
	unify_x_value(7)
	proceed

$42:
	get_structure('switch', 4, 0)
	unify_constant('const')
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('switch_on_constant', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$43:
	get_structure('switch', 4, 0)
	unify_constant('struct')
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('switch_on_structure', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed

$44:
	get_structure('switch', 4, 0)
	unify_constant('quant')
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('switch_on_quantifier', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	proceed
end('$customize'/2):



'$customize_put/4$0'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	get_structure('put_integer', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$2:
	get_structure('put_constant', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed
end('$customize_put/4$0'/3):



'$customize_put'/4:

	switch_on_term(0, $25, 'fail', 'fail', $19, 'fail', $22)

$19:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$20, ':'/2:$21])

$20:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($9)
	retry($10)
	retry($11)
	trust($12)

$21:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($9)
	retry($10)
	retry($11)
	trust($12)

$22:
	switch_on_constant(0, 16, ['$default':'fail', 'constant':$5, 'structure':$23, 'apply_structure':$13, 'quantifier':$14, 'substitution':$24])

$23:
	try(4, $6)
	retry($7)
	trust($8)

$24:
	try(4, $15)
	retry($16)
	retry($17)
	trust($18)

$25:
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
	retry($13)
	retry($14)
	retry($15)
	retry($16)
	retry($17)
	trust($18)

$1:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_x_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$2:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_y_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$3:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_x_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_y_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$5:
	get_constant('constant', 0)
	get_x_variable(0, 1)
	get_structure('$xreg', 1, 2)
	unify_x_variable(2)
	get_x_variable(1, 3)
	execute_predicate('$customize_put/4$0', 3)

$6:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_constant('[|]')
	unify_integer(2)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_list', 1, 3)
	unify_x_value(0)
	proceed

$7:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_constant('.')
	unify_integer(2)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_list', 1, 3)
	unify_x_value(0)
	proceed

$8:
	get_constant('structure', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_structure', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$9:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_x_object_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$10:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_y_object_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$11:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_x_object_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$12:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_y_object_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$13:
	get_constant('apply_structure', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_apply_structure', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$14:
	get_constant('quantifier', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_quantifier', 1, 3)
	unify_x_value(0)
	proceed

$15:
	get_constant('substitution', 0)
	get_constant('zero', 1)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_initial_empty_substitution', 1, 3)
	unify_x_value(0)
	proceed

$16:
	get_constant('substitution', 0)
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_x_term_substitution', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$17:
	get_constant('substitution', 0)
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('put_y_term_substitution', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$18:
	get_constant('substitution', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('put_substitution', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	proceed
end('$customize_put'/4):



'$customize_get/4$0'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	get_structure('get_integer', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed

$2:
	get_structure('get_constant', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	proceed
end('$customize_get/4$0'/3):



'$customize_get'/4:

	switch_on_term(0, $20, 'fail', 'fail', $15, 'fail', $18)

$15:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$16, ':'/2:$17])

$16:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($10)
	retry($11)
	retry($12)
	trust($13)

$17:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($10)
	retry($11)
	retry($12)
	trust($13)

$18:
	switch_on_constant(0, 8, ['$default':'fail', 'constant':$5, 'structure':$19, 'structure_frame':$9, 'apply_structure':$14])

$19:
	try(4, $6)
	retry($7)
	trust($8)

$20:
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
	retry($13)
	trust($14)

$1:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_x_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$2:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_y_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$3:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_x_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_y_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$5:
	get_constant('constant', 0)
	get_x_variable(0, 1)
	get_structure('$xreg', 1, 2)
	unify_x_variable(2)
	get_x_variable(1, 3)
	execute_predicate('$customize_get/4$0', 3)

$6:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_constant('[|]')
	unify_integer(2)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('get_list', 1, 3)
	unify_x_value(0)
	proceed

$7:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_constant('.')
	unify_integer(2)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('get_list', 1, 3)
	unify_x_value(0)
	proceed

$8:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_x_variable(0)
	unify_x_variable(1)
	get_structure('$xreg', 1, 2)
	unify_x_variable(2)
	get_structure('get_structure', 3, 3)
	unify_x_value(0)
	unify_x_value(1)
	unify_x_value(2)
	proceed

$9:
	get_constant('structure_frame', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('get_structure_frame', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	proceed

$10:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_x_object_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$11:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_y_object_variable', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$12:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_x_object_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$13:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('get_y_object_value', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed

$14:
	get_constant('apply_structure', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('get_apply_structure', 2, 3)
	unify_x_value(1)
	unify_x_value(0)
	proceed
end('$customize_get'/4):



'$customize_unify/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	get_structure('unify_integer', 1, 1)
	unify_x_value(0)
	proceed

$2:
	get_structure('unify_constant', 1, 1)
	unify_x_value(0)
	proceed
end('$customize_unify/3$0'/2):



'$customize_unify'/3:

	switch_on_term(0, $10, 'fail', 'fail', $7, 'fail', $6)

$7:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$8, ':'/2:$9])

$8:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$9:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$10:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('unify_x_variable', 1, 2)
	unify_x_value(0)
	proceed

$2:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('unify_y_variable', 1, 2)
	unify_x_value(0)
	proceed

$3:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('unify_x_value', 1, 2)
	unify_x_value(0)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('unify_y_value', 1, 2)
	unify_x_value(0)
	proceed

$5:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('void')
	get_structure('unify_void', 1, 2)
	unify_x_value(1)
	proceed

$6:
	get_constant('constant', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	execute_predicate('$customize_unify/3$0', 2)
end('$customize_unify'/3):



'$customize_set/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	get_structure('set_integer', 1, 1)
	unify_x_value(0)
	proceed

$2:
	get_structure('set_constant', 1, 1)
	unify_x_value(0)
	proceed
end('$customize_set/3$0'/2):



'$customize_set'/3:

	switch_on_term(0, $15, 'fail', 'fail', $12, 'fail', $9)

$12:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$13, ':'/2:$14])

$13:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($10)
	trust($11)

$14:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($10)
	trust($11)

$15:
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
	trust($11)

$1:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_x_variable', 1, 2)
	unify_x_value(0)
	proceed

$2:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_y_variable', 1, 2)
	unify_x_value(0)
	proceed

$3:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_x_value', 1, 2)
	unify_x_value(0)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_y_value', 1, 2)
	unify_x_value(0)
	proceed

$5:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_x_object_variable', 1, 2)
	unify_x_value(0)
	proceed

$6:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_y_object_variable', 1, 2)
	unify_x_value(0)
	proceed

$7:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_x_object_value', 1, 2)
	unify_x_value(0)
	proceed

$8:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('set_y_object_value', 1, 2)
	unify_x_value(0)
	proceed

$9:
	get_constant('constant', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	execute_predicate('$customize_set/3$0', 2)

$10:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('void')
	get_structure('set_void', 1, 2)
	unify_x_value(1)
	proceed

$11:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('void')
	get_structure('set_object_void', 1, 2)
	unify_x_value(1)
	proceed
end('$customize_set'/3):



'$ps_custom_arg'/2:

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
	allocate(3)
	unify_y_variable(2)
	get_y_variable(0, 1)
	put_y_variable(1, 0)
	call_predicate('$last_x_reg', 1, 3)
	put_x_variable(1, 2)
	get_structure('+', 2, 2)
	unify_integer(1)
	unify_y_value(2)
	pseudo_instr3(2, 1, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$ps_custom_arg'/2):



