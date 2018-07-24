'$opcode'/3:

	switch_on_term(0, $100, 'fail', 'fail', 'fail', 'fail', $99)

$99:
	switch_on_constant(0, 256, ['$default':'fail', 'put_x_variable':$1, 'put_y_variable':$2, 'put_x_value':$3, 'put_y_value':$4, 'put_constant':$5, 'put_integer':$6, 'put_list':$7, 'put_structure':$8, 'put_x_object_variable':$9, 'put_y_object_variable':$10, 'put_x_object_value':$11, 'put_y_object_value':$12, 'put_quantifier':$13, 'check_binder':$14, 'put_substitution':$15, 'put_x_term_substitution':$16, 'put_y_term_substitution':$17, 'put_initial_empty_substitution':$18, 'get_x_variable':$19, 'get_y_variable':$20, 'get_x_value':$21, 'get_y_value':$22, 'get_constant':$23, 'get_integer':$24, 'get_list':$25, 'get_structure':$26, 'get_structure_frame':$27, 'get_x_object_variable':$28, 'get_y_object_variable':$29, 'get_x_object_value':$30, 'get_y_object_value':$31, 'unify_x_variable':$32, 'unify_y_variable':$33, 'unify_x_value':$34, 'unify_y_value':$35, 'unify_void':$36, 'set_x_variable':$37, 'set_y_variable':$38, 'set_x_value':$39, 'set_y_value':$40, 'set_x_object_variable':$41, 'set_y_object_variable':$42, 'set_x_object_value':$43, 'set_y_object_value':$44, 'set_constant':$45, 'set_integer':$46, 'set_void':$47, 'set_object_void':$48, 'allocate':$49, 'deallocate':$50, 'call_predicate':$51, 'call_address':$52, 'call_escape':$53, 'execute_predicate':$54, 'execute_address':$55, 'execute_escape':$56, 'noop':$57, 'jump':$58, 'proceed':$59, 'fail':$60, 'halt':$61, 'exit':$62, 'try_me_else':$63, 'retry_me_else':$64, 'trust_me_else_fail':$65, 'try':$66, 'retry':$67, 'trust':$68, 'neck_cut':$69, 'get_x_level':$70, 'get_y_level':$71, 'cut':$72, 'switch_on_term':$73, 'switch_on_constant':$74, 'switch_on_structure':$75, 'switch_on_quantifier':$76, 'pseudo_instr0':$77, 'pseudo_instr1':$78, 'pseudo_instr2':$79, 'pseudo_instr3':$80, 'pseudo_instr4':$81, 'pseudo_instr5':$82, 'unify_constant':$83, 'unify_integer':$84, 'unify_x_ref':$85, 'unify_y_ref':$86, 'db_jump':$87, 'db_execute_predicate':$88, 'db_execute_address':$89, 'db_proceed':$90, 'put_double':$91, 'get_double':$92, 'set_double':$93, 'unify_double':$94, 'put_string':$95, 'get_string':$96, 'set_string':$97, 'unify_string':$98])

$100:
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
	retry($44)
	retry($45)
	retry($46)
	retry($47)
	retry($48)
	retry($49)
	retry($50)
	retry($51)
	retry($52)
	retry($53)
	retry($54)
	retry($55)
	retry($56)
	retry($57)
	retry($58)
	retry($59)
	retry($60)
	retry($61)
	retry($62)
	retry($63)
	retry($64)
	retry($65)
	retry($66)
	retry($67)
	retry($68)
	retry($69)
	retry($70)
	retry($71)
	retry($72)
	retry($73)
	retry($74)
	retry($75)
	retry($76)
	retry($77)
	retry($78)
	retry($79)
	retry($80)
	retry($81)
	retry($82)
	retry($83)
	retry($84)
	retry($85)
	retry($86)
	retry($87)
	retry($88)
	retry($89)
	retry($90)
	retry($91)
	retry($92)
	retry($93)
	retry($94)
	retry($95)
	retry($96)
	retry($97)
	trust($98)

$1:
	get_constant('put_x_variable', 0)
	get_integer(1, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$2:
	get_constant('put_y_variable', 0)
	get_integer(2, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$3:
	get_constant('put_x_value', 0)
	get_integer(3, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$4:
	get_constant('put_y_value', 0)
	get_integer(4, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$5:
	get_constant('put_constant', 0)
	get_integer(5, 1)
	get_list(2)
	unify_constant('constant')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$6:
	get_constant('put_integer', 0)
	get_integer(6, 1)
	get_list(2)
	unify_constant('integer')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$7:
	get_constant('put_list', 0)
	get_integer(7, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$8:
	get_constant('put_structure', 0)
	get_integer(8, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$9:
	get_constant('put_x_object_variable', 0)
	get_integer(9, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$10:
	get_constant('put_y_object_variable', 0)
	get_integer(10, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$11:
	get_constant('put_x_object_value', 0)
	get_integer(11, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$12:
	get_constant('put_y_object_value', 0)
	get_integer(12, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$13:
	get_constant('put_quantifier', 0)
	get_integer(13, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$14:
	get_constant('check_binder', 0)
	get_integer(14, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$15:
	get_constant('put_substitution', 0)
	get_integer(15, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$16:
	get_constant('put_x_term_substitution', 0)
	get_integer(16, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$17:
	get_constant('put_y_term_substitution', 0)
	get_integer(17, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$18:
	get_constant('put_initial_empty_substitution', 0)
	get_integer(18, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$19:
	get_constant('get_x_variable', 0)
	get_integer(19, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$20:
	get_constant('get_y_variable', 0)
	get_integer(20, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$21:
	get_constant('get_x_value', 0)
	get_integer(21, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$22:
	get_constant('get_y_value', 0)
	get_integer(22, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$23:
	get_constant('get_constant', 0)
	get_integer(23, 1)
	get_list(2)
	unify_constant('constant')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$24:
	get_constant('get_integer', 0)
	get_integer(24, 1)
	get_list(2)
	unify_constant('integer')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$25:
	get_constant('get_list', 0)
	get_integer(25, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$26:
	get_constant('get_structure', 0)
	get_integer(26, 1)
	get_list(2)
	unify_constant('constant')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$27:
	get_constant('get_structure_frame', 0)
	get_integer(27, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$28:
	get_constant('get_x_object_variable', 0)
	get_integer(28, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$29:
	get_constant('get_y_object_variable', 0)
	get_integer(29, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$30:
	get_constant('get_x_object_value', 0)
	get_integer(30, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$31:
	get_constant('get_y_object_value', 0)
	get_integer(31, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$32:
	get_constant('unify_x_variable', 0)
	get_integer(32, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$33:
	get_constant('unify_y_variable', 0)
	get_integer(33, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$34:
	get_constant('unify_x_value', 0)
	get_integer(34, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$35:
	get_constant('unify_y_value', 0)
	get_integer(35, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$36:
	get_constant('unify_void', 0)
	get_integer(36, 1)
	get_list(2)
	unify_constant('number')
	unify_constant('[]')
	proceed

$37:
	get_constant('set_x_variable', 0)
	get_integer(37, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$38:
	get_constant('set_y_variable', 0)
	get_integer(38, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$39:
	get_constant('set_x_value', 0)
	get_integer(39, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$40:
	get_constant('set_y_value', 0)
	get_integer(40, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$41:
	get_constant('set_x_object_variable', 0)
	get_integer(41, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$42:
	get_constant('set_y_object_variable', 0)
	get_integer(42, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$43:
	get_constant('set_x_object_value', 0)
	get_integer(43, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$44:
	get_constant('set_y_object_value', 0)
	get_integer(44, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$45:
	get_constant('set_constant', 0)
	get_integer(45, 1)
	get_list(2)
	unify_constant('constant')
	unify_constant('[]')
	proceed

$46:
	get_constant('set_integer', 0)
	get_integer(46, 1)
	get_list(2)
	unify_constant('integer')
	unify_constant('[]')
	proceed

$47:
	get_constant('set_void', 0)
	get_integer(47, 1)
	get_list(2)
	unify_constant('number')
	unify_constant('[]')
	proceed

$48:
	get_constant('set_object_void', 0)
	get_integer(48, 1)
	get_list(2)
	unify_constant('number')
	unify_constant('[]')
	proceed

$49:
	get_constant('allocate', 0)
	get_integer(49, 1)
	get_list(2)
	unify_constant('number')
	unify_constant('[]')
	proceed

$50:
	get_constant('deallocate', 0)
	get_integer(50, 1)
	get_constant('[]', 2)
	proceed

$51:
	get_constant('call_predicate', 0)
	get_integer(51, 1)
	get_list(2)
	unify_constant('predatom')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_constant('[]')
	proceed

$52:
	get_constant('call_address', 0)
	get_integer(52, 1)
	get_list(2)
	unify_constant('address')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_constant('[]')
	proceed

$53:
	get_constant('call_escape', 0)
	get_integer(53, 1)
	get_list(2)
	unify_constant('address')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_constant('[]')
	proceed

$54:
	get_constant('execute_predicate', 0)
	get_integer(54, 1)
	get_list(2)
	unify_constant('predatom')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_constant('[]')
	proceed

$55:
	get_constant('execute_address', 0)
	get_integer(55, 1)
	get_list(2)
	unify_constant('address')
	unify_constant('[]')
	proceed

$56:
	get_constant('execute_escape', 0)
	get_integer(56, 1)
	get_list(2)
	unify_constant('address')
	unify_constant('[]')
	proceed

$57:
	get_constant('noop', 0)
	get_integer(57, 1)
	get_constant('[]', 2)
	proceed

$58:
	get_constant('jump', 0)
	get_integer(58, 1)
	get_list(2)
	unify_constant('address')
	unify_constant('[]')
	proceed

$59:
	get_constant('proceed', 0)
	get_integer(59, 1)
	get_constant('[]', 2)
	proceed

$60:
	get_constant('fail', 0)
	get_integer(60, 1)
	get_constant('[]', 2)
	proceed

$61:
	get_constant('halt', 0)
	get_integer(61, 1)
	get_constant('[]', 2)
	proceed

$62:
	get_constant('exit', 0)
	get_integer(62, 1)
	get_constant('[]', 2)
	proceed

$63:
	get_constant('try_me_else', 0)
	get_integer(63, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('offset')
	unify_constant('[]')
	proceed

$64:
	get_constant('retry_me_else', 0)
	get_integer(64, 1)
	get_list(2)
	unify_constant('offset')
	unify_constant('[]')
	proceed

$65:
	get_constant('trust_me_else_fail', 0)
	get_integer(65, 1)
	get_constant('[]', 2)
	proceed

$66:
	get_constant('try', 0)
	get_integer(66, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('offset')
	unify_constant('[]')
	proceed

$67:
	get_constant('retry', 0)
	get_integer(67, 1)
	get_list(2)
	unify_constant('offset')
	unify_constant('[]')
	proceed

$68:
	get_constant('trust', 0)
	get_integer(68, 1)
	get_list(2)
	unify_constant('offset')
	unify_constant('[]')
	proceed

$69:
	get_constant('neck_cut', 0)
	get_integer(69, 1)
	get_constant('[]', 2)
	proceed

$70:
	get_constant('get_x_level', 0)
	get_integer(70, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$71:
	get_constant('get_y_level', 0)
	get_integer(71, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$72:
	get_constant('cut', 0)
	get_integer(72, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$73:
	get_constant('switch_on_term', 0)
	get_integer(73, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$74:
	get_constant('switch_on_constant', 0)
	get_integer(74, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('tablesize')
	unify_constant('[]')
	proceed

$75:
	get_constant('switch_on_structure', 0)
	get_integer(75, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('tablesize')
	unify_constant('[]')
	proceed

$76:
	get_constant('switch_on_quantifier', 0)
	get_integer(76, 1)
	get_list(2)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('tablesize')
	unify_constant('[]')
	proceed

$77:
	get_constant('pseudo_instr0', 0)
	get_integer(77, 1)
	get_list(2)
	unify_constant('number')
	unify_constant('[]')
	proceed

$78:
	get_constant('pseudo_instr1', 0)
	get_integer(78, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$79:
	get_constant('pseudo_instr2', 0)
	get_integer(79, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$80:
	get_constant('pseudo_instr3', 0)
	get_integer(80, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$81:
	get_constant('pseudo_instr4', 0)
	get_integer(81, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$82:
	get_constant('pseudo_instr5', 0)
	get_integer(82, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$83:
	get_constant('unify_constant', 0)
	get_integer(83, 1)
	get_list(2)
	unify_constant('constant')
	unify_constant('[]')
	proceed

$84:
	get_constant('unify_integer', 0)
	get_integer(84, 1)
	get_list(2)
	unify_constant('integer')
	unify_constant('[]')
	proceed

$85:
	get_constant('unify_x_ref', 0)
	get_integer(85, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$86:
	get_constant('unify_y_ref', 0)
	get_integer(86, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$87:
	get_constant('db_jump', 0)
	get_integer(87, 1)
	get_list(2)
	unify_constant('number')
	unify_x_ref(0)
	get_list(0)
	unify_constant('address')
	unify_x_ref(0)
	get_list(0)
	unify_constant('address')
	unify_x_ref(0)
	get_list(0)
	unify_constant('address')
	unify_constant('[]')
	proceed

$88:
	get_constant('db_execute_predicate', 0)
	get_integer(88, 1)
	get_list(2)
	unify_constant('predatom')
	unify_x_ref(0)
	get_list(0)
	unify_constant('number')
	unify_constant('[]')
	proceed

$89:
	get_constant('db_execute_address', 0)
	get_integer(89, 1)
	get_list(2)
	unify_constant('address')
	unify_constant('[]')
	proceed

$90:
	get_constant('db_proceed', 0)
	get_integer(90, 1)
	get_constant('[]', 2)
	proceed

$91:
	get_constant('put_double', 0)
	get_integer(91, 1)
	get_list(2)
	unify_constant('double')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$92:
	get_constant('get_double', 0)
	get_integer(92, 1)
	get_list(2)
	unify_constant('double')
	unify_x_ref(0)
	get_list(0)
	unify_constant('register')
	unify_constant('[]')
	proceed

$93:
	get_constant('set_double', 0)
	get_integer(93, 1)
	get_list(2)
	unify_constant('double')
	unify_constant('[]')
	proceed

$94:
	get_constant('unify_double', 0)
	get_integer(94, 1)
	get_list(2)
	unify_constant('double')
	unify_constant('[]')
	proceed

$95:
	get_constant('put_string', 0)
	get_integer(95, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$96:
	get_constant('get_string', 0)
	get_integer(96, 1)
	get_list(2)
	unify_constant('register')
	unify_constant('[]')
	proceed

$97:
	get_constant('set_string', 0)
	get_integer(97, 1)
	get_constant('[]', 2)
	proceed

$98:
	get_constant('unify_string', 0)
	get_integer(98, 1)
	get_constant('[]', 2)
	proceed
end('$opcode'/3):



