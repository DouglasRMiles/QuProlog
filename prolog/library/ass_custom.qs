'$customize_ass'/2:

	switch_on_term(0, $75, $37, $37, $38, $37, $66)

$38:
	switch_on_structure(0, 64, ['$default':$37, '$'/0:$39, 'put'/3:$40, 'get'/3:$41, 'unify_ref'/1:$42, 'unify'/2:$43, 'set'/2:$44, 'check_binder'/1:$45, 'allocate'/1:$46, 'call_predicate'/3:$47, 'call_address'/2:$48, 'call_escape'/2:$49, 'execute_predicate'/2:$50, 'execute_address'/1:$51, 'execute_escape'/1:$52, 'try_me_else'/2:$53, 'retry_me_else'/1:$54, 'try'/2:$55, 'retry'/1:$56, 'trust'/1:$57, '$$get_level$$'/1:$58, '$$cut$$'/1:$59, '$pseudo_instr0'/1:$60, '$pseudo_instr1'/2:$61, '$pseudo_instr2'/3:$62, '$pseudo_instr3'/4:$63, '$pseudo_instr4'/5:$64, '$pseudo_instr5'/6:$65])

$39:
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
	retry($21)
	retry($22)
	retry($24)
	retry($25)
	retry($26)
	retry($28)
	retry($29)
	retry($30)
	retry($31)
	retry($32)
	retry($33)
	retry($34)
	retry($35)
	retry($36)
	trust($37)

$40:
	try(2, $1)
	trust($37)

$41:
	try(2, $2)
	trust($37)

$42:
	try(2, $3)
	retry($4)
	trust($37)

$43:
	try(2, $5)
	trust($37)

$44:
	try(2, $6)
	trust($37)

$45:
	try(2, $7)
	trust($37)

$46:
	try(2, $8)
	trust($37)

$47:
	try(2, $10)
	trust($37)

$48:
	try(2, $11)
	trust($37)

$49:
	try(2, $12)
	trust($37)

$50:
	try(2, $13)
	trust($37)

$51:
	try(2, $14)
	trust($37)

$52:
	try(2, $15)
	trust($37)

$53:
	try(2, $21)
	trust($37)

$54:
	try(2, $22)
	trust($37)

$55:
	try(2, $24)
	trust($37)

$56:
	try(2, $25)
	trust($37)

$57:
	try(2, $26)
	trust($37)

$58:
	try(2, $28)
	retry($29)
	trust($37)

$59:
	try(2, $30)
	trust($37)

$60:
	try(2, $31)
	trust($37)

$61:
	try(2, $32)
	trust($37)

$62:
	try(2, $33)
	trust($37)

$63:
	try(2, $34)
	trust($37)

$64:
	try(2, $35)
	trust($37)

$65:
	try(2, $36)
	trust($37)

$66:
	switch_on_constant(0, 16, ['$default':$37, 'deallocate':$67, 'noop':$68, 'proceed':$69, 'fail':$70, 'halt':$71, 'exit':$72, 'trust_me_else_fail':$73, 'neck_cut':$74])

$67:
	try(2, $9)
	trust($37)

$68:
	try(2, $16)
	trust($37)

$69:
	try(2, $17)
	trust($37)

$70:
	try(2, $18)
	trust($37)

$71:
	try(2, $19)
	trust($37)

$72:
	try(2, $20)
	trust($37)

$73:
	try(2, $23)
	trust($37)

$74:
	try(2, $27)
	trust($37)

$75:
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
	trust($37)

$1:
	get_structure('put', 3, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	unify_x_variable(2)
	get_x_variable(3, 1)
	put_x_value(4, 1)
	execute_predicate('$customize_put_ass', 4)

$2:
	get_structure('get', 3, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	unify_x_variable(2)
	get_x_variable(3, 1)
	put_x_value(4, 1)
	execute_predicate('$customize_get_ass', 4)

$3:
	get_structure('unify_ref', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(85)
	unify_integer(0)
	unify_x_value(0)
	proceed

$4:
	get_structure('unify_ref', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(86)
	unify_integer(0)
	unify_x_value(0)
	proceed

$5:
	get_structure('unify', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	execute_predicate('$customize_unify_ass', 3)

$6:
	get_structure('set', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	execute_predicate('$customize_set_ass', 3)

$7:
	get_structure('check_binder', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(14)
	unify_integer(0)
	unify_x_value(0)
	proceed

$8:
	get_structure('allocate', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(50)
	unify_integer(2)
	unify_x_value(0)
	proceed

$9:
	get_constant('deallocate', 0)
	get_structure('instr', 1, 1)
	unify_integer(51)
	proceed

$10:
	get_structure('call_predicate', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('instr', 7, 1)
	unify_integer(52)
	unify_integer(3)
	unify_x_value(0)
	unify_integer(2)
	unify_x_value(2)
	unify_integer(2)
	unify_x_value(3)
	proceed

$11:
	get_structure('call_address', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('instr', 5, 1)
	unify_integer(53)
	unify_integer(4)
	unify_x_value(0)
	unify_integer(2)
	unify_x_value(2)
	proceed

$12:
	get_structure('call_escape', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('instr', 5, 1)
	unify_integer(54)
	unify_integer(4)
	unify_x_value(0)
	unify_integer(2)
	unify_x_value(2)
	proceed

$13:
	get_structure('execute_predicate', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('instr', 5, 1)
	unify_integer(55)
	unify_integer(3)
	unify_x_value(0)
	unify_integer(2)
	unify_x_value(2)
	proceed

$14:
	get_structure('execute_address', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(56)
	unify_integer(4)
	unify_x_value(0)
	proceed

$15:
	get_structure('execute_escape', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(57)
	unify_integer(4)
	unify_x_value(0)
	proceed

$16:
	get_constant('noop', 0)
	get_structure('instr', 1, 1)
	unify_integer(58)
	proceed

$17:
	get_constant('proceed', 0)
	get_structure('instr', 1, 1)
	unify_integer(60)
	proceed

$18:
	get_constant('fail', 0)
	get_structure('instr', 1, 1)
	unify_integer(61)
	proceed

$19:
	get_constant('halt', 0)
	get_structure('instr', 1, 1)
	unify_integer(62)
	proceed

$20:
	get_constant('exit', 0)
	get_structure('instr', 1, 1)
	unify_integer(63)
	proceed

$21:
	get_structure('try_me_else', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('instr', 5, 1)
	unify_integer(64)
	unify_integer(2)
	unify_x_value(0)
	unify_integer(5)
	unify_x_value(2)
	proceed

$22:
	get_structure('retry_me_else', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(65)
	unify_integer(5)
	unify_x_value(0)
	proceed

$23:
	get_constant('trust_me_else_fail', 0)
	get_structure('instr', 1, 1)
	unify_integer(66)
	proceed

$24:
	get_structure('try', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('instr', 5, 1)
	unify_integer(67)
	unify_integer(2)
	unify_x_value(0)
	unify_integer(5)
	unify_x_value(2)
	proceed

$25:
	get_structure('retry', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(68)
	unify_integer(5)
	unify_x_value(0)
	proceed

$26:
	get_structure('trust', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(69)
	unify_integer(5)
	unify_x_value(0)
	proceed

$27:
	get_constant('neck_cut', 0)
	get_structure('instr', 1, 1)
	unify_integer(70)
	proceed

$28:
	get_structure('$$get_level$$', 1, 0)
	unify_x_ref(0)
	get_structure('$xreg', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(71)
	unify_integer(0)
	unify_x_value(0)
	proceed

$29:
	get_structure('$$get_level$$', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(72)
	unify_integer(0)
	unify_x_value(0)
	proceed

$30:
	get_structure('$$cut$$', 1, 0)
	unify_x_ref(0)
	get_structure('$yreg', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(73)
	unify_integer(0)
	unify_x_value(0)
	proceed

$31:
	get_structure('$pseudo_instr0', 1, 0)
	unify_x_variable(0)
	get_structure('instr', 3, 1)
	unify_integer(78)
	unify_integer(0)
	unify_x_value(0)
	proceed

$32:
	get_structure('$pseudo_instr1', 2, 0)
	allocate(3)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$ps_custom_arg', 2, 3)
	put_y_value(1, 0)
	get_structure('instr', 5, 0)
	unify_integer(79)
	unify_integer(0)
	unify_y_value(2)
	unify_integer(0)
	unify_y_value(0)
	deallocate
	proceed

$33:
	get_structure('$pseudo_instr2', 3, 0)
	allocate(5)
	unify_y_variable(3)
	unify_x_variable(0)
	unify_y_variable(4)
	get_y_variable(2, 1)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$ps_custom_arg', 2, 5)
	put_y_value(4, 0)
	put_y_value(0, 1)
	call_predicate('$ps_custom_arg', 2, 4)
	put_y_value(2, 0)
	get_structure('instr', 7, 0)
	unify_integer(80)
	unify_integer(0)
	unify_y_value(3)
	unify_integer(0)
	unify_y_value(1)
	unify_integer(0)
	unify_y_value(0)
	deallocate
	proceed

$34:
	get_structure('$pseudo_instr3', 4, 0)
	allocate(7)
	unify_y_variable(4)
	unify_x_variable(0)
	unify_y_variable(6)
	unify_y_variable(5)
	get_y_variable(3, 1)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	call_predicate('$ps_custom_arg', 2, 7)
	put_y_value(6, 0)
	put_y_value(1, 1)
	call_predicate('$ps_custom_arg', 2, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	call_predicate('$ps_custom_arg', 2, 5)
	put_y_value(3, 0)
	get_structure('instr', 9, 0)
	unify_integer(81)
	unify_integer(0)
	unify_y_value(4)
	unify_integer(0)
	unify_y_value(2)
	unify_integer(0)
	unify_y_value(1)
	unify_integer(0)
	unify_y_value(0)
	deallocate
	proceed

$35:
	get_structure('$pseudo_instr4', 5, 0)
	allocate(9)
	unify_y_variable(5)
	unify_x_variable(0)
	unify_y_variable(8)
	unify_y_variable(7)
	unify_y_variable(6)
	get_y_variable(4, 1)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 1)
	call_predicate('$ps_custom_arg', 2, 9)
	put_y_value(8, 0)
	put_y_value(2, 1)
	call_predicate('$ps_custom_arg', 2, 8)
	put_y_value(7, 0)
	put_y_value(1, 1)
	call_predicate('$ps_custom_arg', 2, 7)
	put_y_value(6, 0)
	put_y_value(0, 1)
	call_predicate('$ps_custom_arg', 2, 6)
	put_y_value(4, 0)
	get_structure('instr', 11, 0)
	unify_integer(82)
	unify_integer(0)
	unify_y_value(5)
	unify_integer(0)
	unify_y_value(3)
	unify_integer(0)
	unify_y_value(2)
	unify_integer(0)
	unify_y_value(1)
	unify_integer(0)
	unify_y_value(0)
	deallocate
	proceed

$36:
	get_structure('$pseudo_instr5', 6, 0)
	allocate(11)
	unify_y_variable(6)
	unify_x_variable(0)
	unify_y_variable(10)
	unify_y_variable(9)
	unify_y_variable(8)
	unify_y_variable(7)
	get_y_variable(5, 1)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('$ps_custom_arg', 2, 11)
	put_y_value(10, 0)
	put_y_value(3, 1)
	call_predicate('$ps_custom_arg', 2, 10)
	put_y_value(9, 0)
	put_y_value(2, 1)
	call_predicate('$ps_custom_arg', 2, 9)
	put_y_value(8, 0)
	put_y_value(1, 1)
	call_predicate('$ps_custom_arg', 2, 8)
	put_y_value(7, 0)
	put_y_value(0, 1)
	call_predicate('$ps_custom_arg', 2, 7)
	put_y_value(5, 0)
	get_structure('instr', 13, 0)
	unify_integer(83)
	unify_integer(0)
	unify_y_value(6)
	unify_integer(0)
	unify_y_value(4)
	unify_integer(0)
	unify_y_value(3)
	unify_integer(0)
	unify_y_value(2)
	unify_integer(0)
	unify_y_value(1)
	unify_integer(0)
	unify_y_value(0)
	deallocate
	proceed

$37:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('Cannot customize ', 0)
	call_predicate('error', 1, 1)
	put_y_value(0, 0)
	call_predicate('errornl', 1, 0)
	fail
end('$customize_ass'/2):



'$customize_put_ass'/4:

	switch_on_term(0, $23, 'fail', 'fail', $17, 'fail', $20)

$17:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$18, ':'/2:$19])

$18:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($8)
	retry($9)
	retry($10)
	trust($11)

$19:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($8)
	retry($9)
	retry($10)
	trust($11)

$20:
	switch_on_constant(0, 8, ['$default':'fail', 'constant':$5, 'structure':$21, 'quantifier':$12, 'substitution':$22])

$21:
	try(4, $6)
	trust($7)

$22:
	try(4, $13)
	retry($14)
	retry($15)
	trust($16)

$23:
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
	trust($16)

$1:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(1)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(2)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(3)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(4)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$5:
	get_constant('constant', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 5, 3)
	unify_integer(5)
	unify_integer(1)
	unify_x_value(1)
	unify_integer(0)
	unify_x_value(0)
	proceed

$6:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_constant('.')
	unify_integer(2)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 3, 3)
	unify_integer(6)
	unify_integer(0)
	unify_x_value(0)
	proceed

$7:
	get_constant('structure', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 5, 3)
	unify_integer(7)
	unify_integer(2)
	unify_x_value(1)
	unify_integer(0)
	unify_x_value(0)
	proceed

$8:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(8)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$9:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(9)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$10:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(10)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$11:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(11)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$12:
	get_constant('quantifier', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 3, 3)
	unify_integer(13)
	unify_integer(0)
	unify_x_value(0)
	proceed

$13:
	get_constant('substitution', 0)
	get_constant('zero', 1)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 3, 3)
	unify_integer(18)
	unify_integer(0)
	unify_x_value(0)
	proceed

$14:
	get_constant('substitution', 0)
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(16)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$15:
	get_constant('substitution', 0)
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(17)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$16:
	get_constant('substitution', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 5, 3)
	unify_integer(15)
	unify_integer(2)
	unify_x_value(1)
	unify_integer(0)
	unify_x_value(0)
	proceed
end('$customize_put_ass'/4):



'$customize_get_ass'/4:

	switch_on_term(0, $18, 'fail', 'fail', $13, 'fail', $16)

$13:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$14, ':'/2:$15])

$14:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($9)
	retry($10)
	retry($11)
	trust($12)

$15:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($9)
	retry($10)
	retry($11)
	trust($12)

$16:
	switch_on_constant(0, 8, ['$default':'fail', 'constant':$5, 'structure':$17, 'structure_frame':$8])

$17:
	try(4, $6)
	trust($7)

$18:
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
	trust($12)

$1:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(1)
	get_structure('instr', 5, 3)
	unify_integer(21)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(22)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(23)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(24)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed

$5:
	get_constant('constant', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 5, 3)
	unify_integer(25)
	unify_integer(1)
	unify_x_value(1)
	unify_integer(0)
	unify_x_value(0)
	proceed

$6:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_constant('.')
	unify_integer(2)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 3, 3)
	unify_integer(26)
	unify_integer(0)
	unify_x_value(0)
	proceed

$7:
	get_constant('structure', 0)
	get_structure('/', 2, 1)
	unify_x_variable(0)
	unify_x_variable(1)
	get_structure('$xreg', 1, 2)
	unify_x_variable(2)
	get_structure('instr', 7, 3)
	unify_integer(27)
	unify_integer(1)
	unify_x_value(0)
	unify_integer(2)
	unify_x_value(1)
	unify_integer(0)
	unify_x_value(2)
	proceed

$8:
	get_constant('structure_frame', 0)
	get_structure('$xreg', 1, 2)
	unify_x_variable(0)
	get_structure('instr', 5, 3)
	unify_integer(28)
	unify_integer(2)
	unify_x_value(1)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(29)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(30)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(31)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
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
	get_structure('instr', 5, 3)
	unify_integer(32)
	unify_integer(0)
	unify_x_value(0)
	unify_integer(0)
	unify_x_value(1)
	proceed
end('$customize_get_ass'/4):



'$customize_unify_ass'/3:

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
	get_structure('instr', 3, 2)
	unify_integer(34)
	unify_integer(0)
	unify_x_value(0)
	proceed

$2:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(35)
	unify_integer(0)
	unify_x_value(0)
	proceed

$3:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(36)
	unify_integer(0)
	unify_x_value(0)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(37)
	unify_integer(0)
	unify_x_value(0)
	proceed

$5:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('void')
	get_structure('instr', 3, 2)
	unify_integer(38)
	unify_integer(2)
	unify_x_value(1)
	proceed

$6:
	get_constant('constant', 0)
	get_structure('instr', 3, 2)
	unify_integer(84)
	unify_integer(1)
	unify_x_value(1)
	proceed
end('$customize_unify_ass'/3):



'$customize_set_ass'/3:

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
	get_structure('instr', 3, 2)
	unify_integer(39)
	unify_integer(0)
	unify_x_value(0)
	proceed

$2:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(40)
	unify_integer(0)
	unify_x_value(0)
	proceed

$3:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(41)
	unify_integer(0)
	unify_x_value(0)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(42)
	unify_integer(0)
	unify_x_value(0)
	proceed

$5:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(43)
	unify_integer(0)
	unify_x_value(0)
	proceed

$6:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('variable')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(44)
	unify_integer(0)
	unify_x_value(0)
	proceed

$7:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$xreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(45)
	unify_integer(0)
	unify_x_value(0)
	proceed

$8:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('value')
	get_structure('$yreg', 1, 1)
	unify_x_variable(0)
	get_structure('instr', 3, 2)
	unify_integer(46)
	unify_integer(0)
	unify_x_value(0)
	proceed

$9:
	get_constant('constant', 0)
	get_structure('instr', 3, 2)
	unify_integer(47)
	unify_integer(1)
	unify_x_value(1)
	proceed

$10:
	get_structure(':', 2, 0)
	unify_constant('meta')
	unify_constant('void')
	get_structure('instr', 3, 2)
	unify_integer(48)
	unify_integer(2)
	unify_x_value(1)
	proceed

$11:
	get_structure(':', 2, 0)
	unify_constant('object')
	unify_constant('void')
	get_structure('instr', 3, 2)
	unify_integer(49)
	unify_integer(2)
	unify_x_value(1)
	proceed
end('$customize_set_ass'/3):



