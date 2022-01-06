'current_atom'/1:


$1:
	put_constant('fail', 1)
	execute_predicate('$current_atom', 2)
end('current_atom'/1):



'$current_atom/2$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('fail', 1)
	get_x_value(2, 1)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$current_atom/2$0'/2):



'$current_atom'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(1, 21)
	put_y_value(1, 1)
	put_integer(-1, 0)
	call_predicate('$search_atom_table', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$current_atom/2$0', 2)
end('$current_atom'/2):



'$search_atom_table/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	get_x_variable(3, 0)
	get_x_variable(0, 2)
	put_x_value(3, 1)
	execute_predicate('$search_atom_table', 2)
end('$search_atom_table/2$0'/3):



'$search_atom_table'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_variable(1, 1)
	pseudo_instr3(32, 2, 1, 3)
	get_x_variable(2, 3)
	execute_predicate('$search_atom_table/2$0', 3)
end('$search_atom_table'/2):



'current_predicate'/1:


$1:
	put_constant('fail', 1)
	execute_predicate('$current_predicate', 2)
end('current_predicate'/1):



'$current_predicate/2$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$current_predicate/2$0'/1):



'$current_predicate/2$1'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	pseudo_instr1(1, 1)
	proceed

$2:
	pseudo_instr1(1, 0)
	pseudo_instr1(3, 1)
	proceed

$3:
	pseudo_instr1(2, 0)
	pseudo_instr1(1, 1)
	proceed
end('$current_predicate/2$1'/2):



'$current_predicate/2$2'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('fail', 1)
	get_x_value(2, 1)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$current_predicate/2$2'/2):



'$current_predicate'/2:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$4, '/'/2:$5])

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
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 2)
	neck_cut
	put_x_value(2, 1)
	allocate(2)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 2)
	pseudo_instr3(33, 21, 20, 0)
	deallocate
	execute_predicate('$current_predicate/2$0', 1)

$2:
	get_structure('/', 2, 0)
	allocate(8)
	unify_y_variable(3)
	unify_y_variable(1)
	get_y_variable(6, 1)
	get_y_level(7)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('$current_predicate/2$1', 2, 8)
	cut(7)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_integer(-1, 0)
	call_predicate('$search_pred_table', 3, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	call_predicate('$current_predicate/2$2', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(0, 3)
	call_predicate('$decompile_pred_arity', 4, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$current_predicate'/2):



'$search_pred_table/3$0'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	get_x_value(2, 3)
	proceed

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 4)
	put_x_value(5, 1)
	execute_predicate('$search_pred_table', 3)
end('$search_pred_table/3$0'/5):



'$search_pred_table'/3:


$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	pseudo_instr4(5, 3, 1, 4, 5)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	execute_predicate('$search_pred_table/3$0', 5)
end('$search_pred_table'/3):



'$decompile_pred_arity/4$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('$', 3)
	pseudo_instr4(1, 0, 1, 3, 2)
	neck_cut
	fail

$2:
	proceed
end('$decompile_pred_arity/4$0'/2):



'$decompile_pred_arity'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(4, 2)
	get_y_variable(0, 3)
	get_y_level(5)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	call_predicate('$last_x_reg', 1, 6)
	put_integer(1, 1)
	put_constant('/', 2)
	pseudo_instr4(1, 22, 1, 2, 0)
	get_y_value(3, 0)
	put_integer(1, 1)
	pseudo_instr3(2, 23, 1, 0)
	get_y_value(1, 0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$decompile_pred_arity/4$0', 2, 6)
	cut(5)
	put_integer(1, 1)
	pseudo_instr3(3, 23, 1, 0)
	put_integer(1, 1)
	pseudo_instr4(2, 22, 1, 0, 24)
	pseudo_instr2(30, 22, 0)
	pseudo_instr3(3, 0, 23, 1)
	get_x_variable(0, 1)
	put_x_variable(1, 1)
	pseudo_instr4(2, 22, 21, 0, 1)
	pseudo_instr2(32, 1, 0)
	pseudo_instr2(39, 0, 1)
	get_y_value(0, 1)
	deallocate
	proceed

$2:
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed
end('$decompile_pred_arity'/4):



'predicate_property'/2:


$1:
	put_constant('fail', 2)
	execute_predicate('$predicate_property', 3)
end('predicate_property'/2):



'$predicate_property/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('fail', 1)
	get_x_value(2, 1)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$predicate_property/3$0'/2):



'$predicate_property'/3:

	switch_on_term(0, $106, $105, $105, $53, $105, $105)

$53:
	switch_on_structure(0, 128, ['$default':$105, '$'/0:$54, 'call'/1:$55, 'once'/1:$56, '\\+'/1:$57, 'catch'/3:$58, 'bagof'/3:$59, 'setof'/3:$60, 'findall'/3:$61, 'forall'/2:$62, 'phrase'/2:$63, 'phrase'/3:$64, 'call_predicate'/1:$65, 'call_predicate'/2:$66, 'call_predicate'/3:$67, 'call_predicate'/4:$68, 'call_predicate'/5:$69, 'delay'/2:$70, 'delay_until'/2:$71, 'retry_woken_delays'/1:$72, 'thread_fork'/2:$73, 'thread_fork'/3:$74, 'thread_push_goal'/2:$75, 'thread_atomic_goal'/1:$76, 'unwind_protect'/2:$77, 'call_cleanup'/2:$78, 'setup_call_cleanup'/3:$79, 'thread_wait_on_goal'/1:$80, 'thread_wait_on_goal'/2:$81, 'front_with'/3:$82, 'after_with'/3:$83, 'build_structure'/4:$84, 'filter'/3:$85, 'map'/2:$86, 'fold'/4:$87, 'fold_left'/4:$88, 'fold_right'/4:$89, 'collect_simple_terms'/4:$90, 'transform_simple_terms'/3:$91, 'transform_subterms'/3:$92, 'add_expansion'/1:$93, 'add_expansion_vars'/1:$94, 'add_multi_expansion'/1:$95, 'add_multi_expansion_vars'/1:$96, 'add_subterm_expansion'/1:$97, 'add_subterm_expansion_vars'/1:$98, 'del_expansion'/1:$99, 'del_expansion_vars'/1:$100, 'del_multi_expansion'/1:$101, 'del_multi_expansion_vars'/1:$102, 'del_subterm_expansion'/1:$103, 'del_subterm_expansion_vars'/1:$104])

$54:
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
	trust($52)

$55:
	try(3, $1)
	retry($2)
	trust($3)

$56:
	try(3, $1)
	retry($2)
	trust($4)

$57:
	try(3, $1)
	retry($2)
	trust($5)

$58:
	try(3, $1)
	retry($2)
	trust($6)

$59:
	try(3, $1)
	retry($2)
	trust($7)

$60:
	try(3, $1)
	retry($2)
	trust($8)

$61:
	try(3, $1)
	retry($2)
	trust($9)

$62:
	try(3, $1)
	retry($2)
	trust($10)

$63:
	try(3, $1)
	retry($2)
	trust($11)

$64:
	try(3, $1)
	retry($2)
	trust($12)

$65:
	try(3, $1)
	retry($2)
	trust($13)

$66:
	try(3, $1)
	retry($2)
	trust($14)

$67:
	try(3, $1)
	retry($2)
	trust($15)

$68:
	try(3, $1)
	retry($2)
	trust($16)

$69:
	try(3, $1)
	retry($2)
	trust($17)

$70:
	try(3, $1)
	retry($2)
	trust($18)

$71:
	try(3, $1)
	retry($2)
	trust($19)

$72:
	try(3, $1)
	retry($2)
	trust($20)

$73:
	try(3, $1)
	retry($2)
	trust($21)

$74:
	try(3, $1)
	retry($2)
	trust($22)

$75:
	try(3, $1)
	retry($2)
	trust($23)

$76:
	try(3, $1)
	retry($2)
	trust($24)

$77:
	try(3, $1)
	retry($2)
	trust($25)

$78:
	try(3, $1)
	retry($2)
	trust($26)

$79:
	try(3, $1)
	retry($2)
	trust($27)

$80:
	try(3, $1)
	retry($2)
	trust($28)

$81:
	try(3, $1)
	retry($2)
	trust($29)

$82:
	try(3, $1)
	retry($2)
	trust($30)

$83:
	try(3, $1)
	retry($2)
	trust($31)

$84:
	try(3, $1)
	retry($2)
	trust($32)

$85:
	try(3, $1)
	retry($2)
	trust($33)

$86:
	try(3, $1)
	retry($2)
	trust($34)

$87:
	try(3, $1)
	retry($2)
	trust($35)

$88:
	try(3, $1)
	retry($2)
	trust($36)

$89:
	try(3, $1)
	retry($2)
	trust($37)

$90:
	try(3, $1)
	retry($2)
	trust($38)

$91:
	try(3, $1)
	retry($2)
	trust($39)

$92:
	try(3, $1)
	retry($2)
	trust($40)

$93:
	try(3, $1)
	retry($2)
	trust($41)

$94:
	try(3, $1)
	retry($2)
	trust($42)

$95:
	try(3, $1)
	retry($2)
	trust($43)

$96:
	try(3, $1)
	retry($2)
	trust($44)

$97:
	try(3, $1)
	retry($2)
	trust($45)

$98:
	try(3, $1)
	retry($2)
	trust($46)

$99:
	try(3, $1)
	retry($2)
	trust($47)

$100:
	try(3, $1)
	retry($2)
	trust($48)

$101:
	try(3, $1)
	retry($2)
	trust($49)

$102:
	try(3, $1)
	retry($2)
	trust($50)

$103:
	try(3, $1)
	retry($2)
	trust($51)

$104:
	try(3, $1)
	retry($2)
	trust($52)

$105:
	try(3, $1)
	trust($2)

$106:
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
	trust($52)

$1:
	allocate(7)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(1, 22)
	neck_cut
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	put_integer(-1, 0)
	call_predicate('$search_pred_table', 3, 7)
	put_y_value(0, 0)
	put_y_value(6, 1)
	call_predicate('$predicate_property/3$0', 2, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	call_predicate('$decompile_pred_arity', 4, 5)
	pseudo_instr3(0, 22, 24, 23)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$predicate_property', 3)

$2:
	get_x_variable(3, 0)
	allocate(3)
	get_y_variable(2, 1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 3, 0, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$obtain_predicate_property', 3)

$3:
	get_structure('call', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call', 1, 0)
	unify_integer(0)
	proceed

$4:
	get_structure('once', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('once', 1, 0)
	unify_integer(0)
	proceed

$5:
	get_structure('\\+', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('\\+', 1, 0)
	unify_integer(0)
	proceed

$6:
	get_structure('catch', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('catch', 3, 0)
	unify_integer(0)
	unify_constant('?')
	unify_integer(0)
	proceed

$7:
	get_structure('bagof', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('bagof', 3, 0)
	unify_constant('?')
	unify_integer(0)
	unify_constant('-')
	proceed

$8:
	get_structure('setof', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('setof', 3, 0)
	unify_constant('?')
	unify_integer(0)
	unify_constant('-')
	proceed

$9:
	get_structure('findall', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('findall', 3, 0)
	unify_constant('?')
	unify_integer(0)
	unify_constant('-')
	proceed

$10:
	get_structure('forall', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('forall', 2, 0)
	unify_integer(0)
	unify_integer(0)
	proceed

$11:
	get_structure('phrase', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('phrase', 2, 0)
	unify_integer(2)
	unify_constant('?')
	proceed

$12:
	get_structure('phrase', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('phrase', 3, 0)
	unify_integer(2)
	unify_constant('?')
	unify_constant('?')
	proceed

$13:
	get_structure('call_predicate', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call_predicate', 1, 0)
	unify_integer(0)
	proceed

$14:
	get_structure('call_predicate', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call_predicate', 2, 0)
	unify_integer(1)
	unify_constant('?')
	proceed

$15:
	get_structure('call_predicate', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call_predicate', 3, 0)
	unify_integer(2)
	unify_constant('?')
	unify_constant('?')
	proceed

$16:
	get_structure('call_predicate', 4, 0)
	unify_void(4)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call_predicate', 4, 0)
	unify_integer(3)
	unify_constant('?')
	unify_constant('?')
	unify_constant('?')
	proceed

$17:
	get_structure('call_predicate', 5, 0)
	unify_void(5)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call_predicate', 5, 0)
	unify_integer(4)
	unify_constant('?')
	unify_constant('?')
	unify_constant('?')
	unify_constant('?')
	proceed

$18:
	get_structure('delay', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('delay', 2, 0)
	unify_constant('-')
	unify_integer(0)
	proceed

$19:
	get_structure('delay_until', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('delay_until', 2, 0)
	unify_constant('+')
	unify_integer(0)
	proceed

$20:
	get_structure('retry_woken_delays', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('retry_woken_delays', 1, 0)
	unify_integer(0)
	proceed

$21:
	get_structure('thread_fork', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('thread_fork', 2, 0)
	unify_constant('?')
	unify_integer(0)
	proceed

$22:
	get_structure('thread_fork', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('thread_fork', 3, 0)
	unify_constant('?')
	unify_integer(0)
	unify_constant('@')
	proceed

$23:
	get_structure('thread_push_goal', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('thread_push_goal', 2, 0)
	unify_constant('@')
	unify_integer(0)
	proceed

$24:
	get_structure('thread_atomic_goal', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('thread_atomic_goal', 1, 0)
	unify_integer(0)
	proceed

$25:
	get_structure('unwind_protect', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('unwind_protect', 2, 0)
	unify_integer(0)
	unify_integer(0)
	proceed

$26:
	get_structure('call_cleanup', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('call_cleanup', 2, 0)
	unify_integer(0)
	unify_integer(0)
	proceed

$27:
	get_structure('setup_call_cleanup', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('setup_call_cleanup', 3, 0)
	unify_integer(0)
	unify_integer(0)
	unify_integer(0)
	proceed

$28:
	get_structure('thread_wait_on_goal', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('thread_wait_on_goal', 1, 0)
	unify_integer(0)
	proceed

$29:
	get_structure('thread_wait_on_goal', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('thread_wait_on_goal', 2, 0)
	unify_integer(0)
	unify_constant('@')
	proceed

$30:
	get_structure('front_with', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('front_with', 3, 0)
	unify_integer(2)
	unify_constant('?')
	unify_constant('?')
	proceed

$31:
	get_structure('after_with', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('after_with', 3, 0)
	unify_integer(2)
	unify_constant('?')
	unify_constant('?')
	proceed

$32:
	get_structure('build_structure', 4, 0)
	unify_void(4)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('build_structure', 3, 0)
	unify_constant('@')
	unify_constant('@')
	unify_integer(2)
	proceed

$33:
	get_structure('filter', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('filter', 3, 0)
	unify_integer(2)
	unify_constant('+')
	unify_constant('?')
	proceed

$34:
	get_structure('map', 2, 0)
	unify_void(2)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('map', 2, 0)
	unify_integer(2)
	unify_constant('+')
	proceed

$35:
	get_structure('fold', 4, 0)
	unify_void(4)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('fold', 4, 0)
	unify_integer(3)
	unify_constant('+')
	unify_constant('+')
	unify_constant('?')
	proceed

$36:
	get_structure('fold_left', 4, 0)
	unify_void(4)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('fold_left', 4, 0)
	unify_integer(3)
	unify_constant('+')
	unify_constant('+')
	unify_constant('?')
	proceed

$37:
	get_structure('fold_right', 4, 0)
	unify_void(4)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('fold_right', 4, 0)
	unify_integer(3)
	unify_constant('+')
	unify_constant('+')
	unify_constant('?')
	proceed

$38:
	get_structure('collect_simple_terms', 4, 0)
	unify_void(4)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('collect_simple_terms', 4, 0)
	unify_integer(3)
	unify_constant('+')
	unify_constant('+')
	unify_constant('?')
	proceed

$39:
	get_structure('transform_simple_terms', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('transform_simple_terms', 3, 0)
	unify_integer(2)
	unify_constant('+')
	unify_constant('?')
	proceed

$40:
	get_structure('transform_subterms', 3, 0)
	unify_void(3)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('transform_subterms', 3, 0)
	unify_integer(2)
	unify_constant('+')
	unify_constant('?')
	proceed

$41:
	get_structure('add_expansion', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('add_expansion', 1, 0)
	unify_integer(2)
	proceed

$42:
	get_structure('add_expansion_vars', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('add_expansion_vars', 1, 0)
	unify_integer(2)
	proceed

$43:
	get_structure('add_multi_expansion', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('add_multi_expansion', 1, 0)
	unify_integer(2)
	proceed

$44:
	get_structure('add_multi_expansion_vars', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('add_multi_expansion_vars', 1, 0)
	unify_integer(2)
	proceed

$45:
	get_structure('add_subterm_expansion', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('add_subterm_expansion', 1, 0)
	unify_integer(2)
	proceed

$46:
	get_structure('add_subterm_expansion_vars', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('add_subterm_expansion_vars', 1, 0)
	unify_integer(2)
	proceed

$47:
	get_structure('del_expansion', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('del_expansion', 1, 0)
	unify_integer(2)
	proceed

$48:
	get_structure('del_expansion_vars', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('del_expansion_vars', 1, 0)
	unify_integer(2)
	proceed

$49:
	get_structure('del_multi_expansion', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('del_multi_expansion', 1, 0)
	unify_integer(2)
	proceed

$50:
	get_structure('del_multi_expansion_vars', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('del_multi_expansion_vars', 1, 0)
	unify_integer(2)
	proceed

$51:
	get_structure('del_subterm_expansion', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('del_subterm_expansion', 1, 0)
	unify_integer(2)
	proceed

$52:
	get_structure('del_subterm_expansion_vars', 1, 0)
	unify_void(1)
	get_structure('meta_predicate', 1, 1)
	unify_x_ref(0)
	get_structure('del_subterm_expansion_vars', 1, 0)
	unify_integer(2)
	proceed
end('$predicate_property'/3):



'$obtain_predicate_property'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('built_in', 2)
	allocate(1)
	get_y_level(0)
	call_predicate('$builtin', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_constant('multifile', 2)
	allocate(1)
	get_y_level(0)
	call_predicate('$multifile', 2, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_constant('dynamic', 2)
	pseudo_instr3(33, 0, 1, 2)
	put_integer(1, 0)
	get_x_value(2, 0)
	neck_cut
	proceed

$4:
	get_constant('static', 2)
	pseudo_instr3(33, 0, 1, 2)
	put_integer(2, 0)
	get_x_value(2, 0)
	neck_cut
	proceed

$5:
	get_constant('foreign', 2)
	pseudo_instr3(33, 0, 1, 2)
	put_integer(3, 0)
	get_x_value(2, 0)
	neck_cut
	proceed
end('$obtain_predicate_property'/3):



'$external/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$internal', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$external/1$0'/1):



'$external'/1:


$1:
	execute_predicate('$external/1$0', 1)
end('$external'/1):



'$internal'/1:


$1:
	put_integer(1, 2)
	put_constant('$', 3)
	pseudo_instr4(1, 0, 2, 3, 1)
	proceed
end('$internal'/1):



'$query_symbols1593041822_10/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('$multifile')
	set_integer(2)
	call_predicate('dynamic', 1, 1)
	cut(0)
	deallocate
	proceed
end('$query_symbols1593041822_10/0$0'/0):



'$query_symbols1593041822_10'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(0)
	call_predicate('$query_symbols1593041822_10/0$0', 0, 0)
	fail

$2:
	proceed
end('$query_symbols1593041822_10'/0):



'$query'/0:


$1:
	execute_predicate('$query_symbols1593041822_10', 0)
end('$query'/0):



