'$init_exception'/0:


$1:
	put_structure(2, 0)
	set_constant('/')
	set_constant('$global_exception_handler')
	set_integer(2)
	allocate(0)
	call_predicate('dynamic', 1, 0)
	put_structure(2, 0)
	set_constant('/')
	set_constant('user_exception_message')
	set_integer(2)
	deallocate
	execute_predicate('dynamic', 1)
end('$init_exception'/0):



'exception/1$0/5$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('call_predicate', 1, 2)
	cut(1)
	put_y_value(0, 0)
	get_constant('true', 0)
	deallocate
	proceed

$2:
	put_constant('fail', 0)
	get_x_value(1, 0)
	proceed
end('exception/1$0/5$0'/2):



'exception/1$0'/5:

	try(5, $1)
	retry($2)
	trust($3)

$1:
	allocate(2)
	get_y_variable(0, 0)
	put_constant('$locally_handled_exceptions', 1)
	pseudo_instr2(4, 1, 0)
	get_x_variable(1, 0)
	pseudo_instr1(46, 1)
	get_y_level(1)
	put_y_value(0, 0)
	call_predicate('member', 2, 2)
	cut(1)
	put_structure(1, 0)
	set_constant('$exception')
	set_y_value(0)
	deallocate
	execute_predicate('throw', 1)

$2:
	allocate(5)
	get_y_variable(2, 1)
	get_y_level(4)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(3, 1)
	call_predicate('$global_exception_handler', 2, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	call_predicate('exception/1$0/5$0', 2, 3)
	put_y_value(2, 0)
	put_x_variable(1, 1)
	put_y_value(1, 2)
	put_x_variable(3, 3)
	call_predicate('$exception_severity', 4, 2)
	put_y_value(1, 0)
	call_predicate('call_predicate', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$3:
	get_x_variable(5, 0)
	get_x_variable(6, 1)
	get_x_variable(0, 2)
	put_x_value(5, 1)
	put_x_value(6, 2)
	execute_predicate('$default_exception_handler', 5)
end('exception/1$0'/5):



'exception'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	allocate(6)
	get_y_variable(4, 0)
	get_y_level(5)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	put_y_variable(1, 3)
	put_y_variable(0, 4)
	call_predicate('$valid_exception_term', 5, 6)
	cut(5)
	put_y_value(4, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('exception/1$0', 5)

$2:
	pseudo_instr1(1, 0)
	neck_cut
	put_structure(1, 1)
	set_constant('exception')
	set_x_value(0)
	put_structure(1, 2)
	set_constant('default')
	set_constant('exception_term')
	put_structure(1, 0)
	set_constant('+')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('exception')
	set_x_value(0)
	put_list(4)
	set_x_value(3)
	set_constant('[]')
	put_structure(5, 0)
	set_constant('instantiation_error')
	set_constant('fatal')
	set_x_value(1)
	set_x_value(2)
	set_integer(1)
	set_x_value(4)
	execute_predicate('exception', 1)

$3:
	put_structure(1, 1)
	set_constant('exception')
	set_x_value(0)
	put_structure(1, 2)
	set_constant('default')
	set_constant('exception_term')
	put_structure(1, 0)
	set_constant('+')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('exception')
	set_x_value(0)
	put_list(4)
	set_x_value(3)
	set_constant('[]')
	put_structure(5, 0)
	set_constant('type_error')
	set_constant('fatal')
	set_x_value(1)
	set_x_value(2)
	set_integer(1)
	set_x_value(4)
	execute_predicate('exception', 1)
end('exception'/1):



'default_exception_handler'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	allocate(6)
	get_y_variable(4, 0)
	get_y_level(5)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	put_y_variable(1, 3)
	put_y_variable(0, 4)
	call_predicate('$valid_exception_term', 5, 6)
	cut(5)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$default_exception_handler', 5)

$2:
	pseudo_instr1(1, 0)
	neck_cut
	put_structure(1, 1)
	set_constant('default_exception_handler')
	set_x_value(0)
	put_structure(1, 2)
	set_constant('default')
	set_constant('exception_term')
	put_structure(1, 0)
	set_constant('+')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('default_exception_handler')
	set_x_value(0)
	put_list(4)
	set_x_value(3)
	set_constant('[]')
	put_structure(5, 0)
	set_constant('instantiation_error')
	set_constant('fatal')
	set_x_value(1)
	set_x_value(2)
	set_integer(1)
	set_x_value(4)
	execute_predicate('exception', 1)

$3:
	put_structure(1, 1)
	set_constant('default_exception_handler')
	set_x_value(0)
	put_structure(1, 2)
	set_constant('default')
	set_constant('exception_term')
	put_structure(1, 0)
	set_constant('+')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('default_exception_handler')
	set_x_value(0)
	put_list(4)
	set_x_value(3)
	set_constant('[]')
	put_structure(5, 0)
	set_constant('type_error')
	set_constant('fatal')
	set_x_value(1)
	set_x_value(2)
	set_integer(1)
	set_x_value(4)
	execute_predicate('exception', 1)
end('default_exception_handler'/1):



'$default_exception_handler/5$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'SIGSEGV':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('SIGSEGV', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$default_exception_handler/5$0'/1):



'$default_exception_handler/5$1/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$dynamic_load', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$default_exception_handler/5$1/2$0'/2):



'$default_exception_handler/5$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$default_exception_handler/5$1/2$0', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$default_exception_handler/5$1'/2):



'$default_exception_handler'/5:

	switch_on_term(0, $8, $4, $4, $4, $4, $5)

$5:
	switch_on_constant(0, 4, ['$default':$4, 'signal':$6, 'undefined_predicate':$7])

$6:
	try(5, $1)
	trust($4)

$7:
	try(5, $2)
	retry($3)
	trust($4)

$8:
	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('signal', 0)
	get_structure('signal', 4, 1)
	unify_void(3)
	allocate(2)
	unify_y_variable(0)
	get_y_level(1)
	put_y_value(0, 0)
	call_predicate('$default_exception_handler/5$0', 1, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$signal_handler', 1)

$2:
	get_constant('undefined_predicate', 0)
	pseudo_instr2(92, 3, 0)
	get_x_variable(2, 0)
	allocate(2)
	get_y_level(1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	put_y_variable(0, 3)
	call_predicate('$inline', 4, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call', 1)

$3:
	get_constant('undefined_predicate', 0)
	allocate(4)
	get_y_variable(0, 3)
	get_y_level(1)
	put_y_value(0, 0)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$higher_functor', 3, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	call_predicate('$default_exception_handler/5$1', 2, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$4:
	put_structure(1, 0)
	set_constant('exception')
	set_x_value(1)
	execute_predicate('throw', 1)
end('$default_exception_handler'/5):



'exception_severity'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(4)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_x_variable(1, 1)
	put_y_variable(0, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$valid_exception_term', 5, 4)
	cut(3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_x_variable(3, 3)
	deallocate
	execute_predicate('$exception_severity', 4)

$2:
	pseudo_instr1(1, 0)
	neck_cut
	put_structure(3, 3)
	set_constant('exception_severity')
	set_x_value(0)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('default')
	set_constant('exception_term')
	put_structure(1, 0)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('exception_severity')
	set_x_value(0)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_constant('[]')
	put_structure(5, 0)
	set_constant('instantiation_error')
	set_constant('fatal')
	set_x_value(3)
	set_x_value(1)
	set_integer(1)
	set_x_value(2)
	execute_predicate('exception', 1)

$3:
	put_structure(3, 3)
	set_constant('exception_severity')
	set_x_value(0)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('default')
	set_constant('exception_term')
	put_structure(1, 0)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_constant('atom')
	put_structure(3, 5)
	set_constant('exception_severity')
	set_x_value(0)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(5)
	set_constant('[]')
	put_structure(5, 0)
	set_constant('type_error')
	set_constant('fatal')
	set_x_value(3)
	set_x_value(1)
	set_integer(1)
	set_x_value(2)
	execute_predicate('exception', 1)
end('exception_severity'/3):



'$exception_severity'/4:

	switch_on_term(0, $7, 'fail', 'fail', 'fail', 'fail', $6)

$6:
	switch_on_constant(0, 16, ['$default':'fail', 'information':$1, 'warning':$2, 'recoverable':$3, 'unrecoverable':$4, 'fatal':$5])

$7:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('information', 0)
	get_constant('true', 1)
	get_constant('true', 2)
	get_constant('Information: ', 3)
	proceed

$2:
	get_constant('warning', 0)
	get_constant('true', 1)
	get_constant('true', 2)
	get_constant('Warning: ', 3)
	proceed

$3:
	get_constant('recoverable', 0)
	get_constant('fail', 1)
	get_constant('true', 2)
	get_constant('Recoverable error: ', 3)
	proceed

$4:
	get_constant('unrecoverable', 0)
	get_constant('fail', 1)
	get_constant('fail', 2)
	get_constant('Unrecoverable error: ', 3)
	proceed

$5:
	get_constant('fatal', 0)
	get_constant('halt', 1)
	get_constant('halt', 2)
	get_constant('Fatal error: ', 3)
	proceed
end('$exception_severity'/4):



'get_exception_message'/2:


$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_level(6)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	put_y_variable(1, 3)
	put_y_variable(0, 4)
	call_predicate('$valid_exception_term', 5, 7)
	cut(6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	put_y_value(4, 5)
	deallocate
	execute_predicate('$get_exception_message', 6)
end('get_exception_message'/2):



'$get_exception_message/6$0'/6:

	try(6, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('user_exception_message', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	put_y_value(0, 0)
	call_predicate('closed_list', 1, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(6, 0)
	allocate(5)
	get_y_variable(2, 1)
	get_x_variable(7, 2)
	get_x_variable(0, 3)
	get_y_variable(4, 4)
	get_x_variable(2, 5)
	get_y_level(3)
	put_y_variable(0, 19)
	put_y_value(4, 1)
	put_x_value(7, 3)
	put_x_value(6, 4)
	put_y_variable(1, 5)
	call_predicate('$builtin_exception_message', 6, 5)
	put_y_value(4, 0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_y_value(0, 3)
	call_predicate('$exception_severity', 4, 4)
	cut(3)
	put_y_value(2, 0)
	get_list(0)
	unify_y_value(0)
	unify_y_value(1)
	deallocate
	proceed

$4:
	put_x_value(1, 0)
	get_list(0)
	unify_constant('No Message')
	unify_constant('[]')
	proceed
end('$get_exception_message/6$0'/6):



'$get_exception_message'/6:


$1:
	get_x_variable(6, 1)
	get_x_variable(7, 2)
	get_x_variable(8, 3)
	get_x_variable(2, 4)
	get_x_variable(1, 5)
	put_x_value(6, 3)
	put_x_value(7, 4)
	put_x_value(8, 5)
	execute_predicate('$get_exception_message/6$0', 6)
end('$get_exception_message'/6):



'$builtin_exception_message'/6:

	switch_on_term(0, $26, 'fail', 'fail', 'fail', 'fail', $22)

$22:
	switch_on_constant(0, 64, ['$default':'fail', 'type_error':$23, 'instantiation_error':$24, 'stream_error':$5, 'permission_error':$6, 'dynamic_code_error':$7, 'undefined_predicate':$8, 'range_error':$9, 'value_error':$10, 'zero_divide':$11, 'syntax_error':$12, 'signal':$25, 'exception_error':$15, 'context_error':$16, 'declaration_error':$17, 'allocation_failure_error':$18, 'system_call_error':$19, 'unimplemented_error':$20, 'unsupported_error':$21])

$23:
	try(6, $1)
	trust($2)

$24:
	try(6, $3)
	trust($4)

$25:
	try(6, $13)
	trust($14)

$26:
	try(6, $1)
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
	trust($21)

$1:
	get_constant('type_error', 0)
	get_constant('default', 3)
	get_structure('type_error', 5, 4)
	unify_void(3)
	unify_x_variable(0)
	unify_x_variable(1)
	get_list(5)
	unify_constant('type error in ')
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('w', 1, 3)
	unify_x_value(2)
	get_list(4)
	unify_constant(' at argument ')
	unify_x_ref(2)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('w', 1, 2)
	unify_x_value(0)
	get_list(3)
	unify_constant('nl')
	unify_x_ref(0)
	get_list(0)
	unify_constant('  allowable modes are ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(2)
	get_structure('w', 1, 0)
	unify_x_value(1)
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$2:
	get_constant('type_error', 0)
	get_structure('default', 1, 3)
	unify_x_variable(0)
	get_structure('type_error', 5, 4)
	unify_void(3)
	unify_x_variable(1)
	unify_void(1)
	get_list(5)
	unify_constant('type error in ')
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('w', 1, 3)
	unify_x_value(2)
	get_list(4)
	unify_constant(' at argument ')
	unify_x_ref(2)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('w', 1, 2)
	unify_x_value(1)
	get_list(3)
	unify_constant('nl')
	unify_x_ref(1)
	get_list(1)
	unify_constant('  expected type ')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('w', 1, 1)
	unify_x_value(0)
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$3:
	get_constant('instantiation_error', 0)
	get_constant('default', 3)
	get_structure('instantiation_error', 5, 4)
	unify_void(3)
	unify_x_variable(0)
	unify_x_variable(1)
	get_list(5)
	unify_constant('instantiation error in ')
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('w', 1, 3)
	unify_x_value(2)
	get_list(4)
	unify_constant(' at argument ')
	unify_x_ref(2)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('w', 1, 2)
	unify_x_value(0)
	get_list(3)
	unify_constant('nl')
	unify_x_ref(0)
	get_list(0)
	unify_constant('  allowable modes are ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(2)
	get_structure('w', 1, 0)
	unify_x_value(1)
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$4:
	get_constant('instantiation_error', 0)
	get_structure('default', 1, 3)
	unify_x_variable(0)
	get_structure('instantiation_error', 5, 4)
	unify_void(3)
	unify_x_variable(1)
	unify_void(1)
	get_list(5)
	unify_constant('instantiation error in ')
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('w', 1, 3)
	unify_x_value(2)
	get_list(4)
	unify_constant(' at argument ')
	unify_x_ref(2)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('w', 1, 2)
	unify_x_value(1)
	get_list(3)
	unify_constant('nl')
	unify_x_ref(1)
	get_list(1)
	unify_constant('  expected type ')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('w', 1, 1)
	unify_x_value(0)
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$5:
	get_constant('stream_error', 0)
	get_list(5)
	unify_constant('stream error in ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$6:
	get_constant('permission_error', 0)
	get_list(5)
	unify_constant('permission error in ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$7:
	get_constant('dynamic_code_error', 0)
	get_list(5)
	unify_constant('dynamic code error in ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$8:
	get_constant('undefined_predicate', 0)
	get_list(5)
	unify_constant('undefined predicate: ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_ref(0)
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	pseudo_instr3(0, 2, 0, 3)
	proceed

$9:
	get_constant('range_error', 0)
	get_structure('range_error', 5, 4)
	unify_void(3)
	unify_x_variable(0)
	unify_x_variable(1)
	get_list(5)
	unify_constant('argument ')
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('w', 1, 3)
	unify_x_value(0)
	get_list(4)
	unify_constant(' of ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(3)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(3)
	unify_constant(' must be in range ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(2)
	get_structure('w', 1, 0)
	unify_x_value(1)
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$10:
	get_constant('value_error', 0)
	get_structure('value_error', 4, 4)
	unify_void(3)
	unify_x_variable(0)
	get_list(5)
	unify_constant('bad value for argument')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('w', 1, 1)
	unify_x_value(0)
	get_list(3)
	unify_constant(' of ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$11:
	get_constant('zero_divide', 0)
	get_structure('zero_divide', 3, 4)
	unify_void(3)
	get_list(5)
	unify_constant('division by zero')
	unify_x_ref(0)
	get_list(0)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$12:
	get_constant('syntax_error', 0)
	get_structure('syntax_error', 10, 4)
	unify_void(6)
	unify_x_variable(0)
	unify_x_variable(4)
	allocate(4)
	unify_y_variable(3)
	unify_x_variable(1)
	get_list(5)
	unify_constant('syntax error in ')
	unify_x_ref(5)
	get_list(5)
	unify_x_ref(5)
	unify_x_ref(6)
	get_structure('w', 1, 5)
	unify_x_value(2)
	get_list(6)
	unify_constant(' in lines ')
	unify_x_ref(2)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(5)
	get_structure('w', 1, 2)
	unify_x_ref(2)
	get_structure('-', 2, 2)
	unify_x_value(0)
	unify_x_value(4)
	get_list(5)
	unify_constant('nl')
	unify_x_ref(0)
	get_list(0)
	unify_x_value(3)
	unify_x_ref(0)
	get_list(0)
	unify_constant('nl')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(2)
	get_structure('wl', 2, 0)
	unify_y_variable(2)
	unify_constant(' ')
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	put_y_variable(0, 19)
	put_y_variable(1, 0)
	call_predicate('length', 2, 4)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	call_predicate('append', 3, 3)
	put_y_value(1, 0)
	put_list(1)
	set_constant(' <<here>> ')
	set_y_value(0)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)

$13:
	get_constant('signal', 0)
	get_structure('signal', 4, 4)
	unify_void(3)
	unify_constant('SIGSEGV')
	get_list(5)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(3)
	get_list(1)
	unify_constant(' is over 90 full')
	unify_x_ref(0)
	get_list(0)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$14:
	get_constant('signal', 0)
	get_structure('signal', 4, 4)
	unify_void(3)
	unify_x_variable(0)
	get_list(5)
	unify_constant('signal ')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('w', 1, 1)
	unify_x_value(0)
	get_list(2)
	unify_constant(' received')
	unify_x_ref(0)
	get_list(0)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$15:
	get_constant('exception_error', 0)
	get_list(5)
	unify_constant('exception error while handling ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$16:
	get_constant('context_error', 0)
	get_list(5)
	unify_constant('context error in ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$17:
	get_constant('declaration_error', 0)
	get_list(5)
	unify_constant('missing declaration for ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(3)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$18:
	get_constant('allocation_failure_error', 0)
	get_structure('allocation_failure_error', 5, 4)
	unify_void(3)
	unify_x_variable(0)
	unify_x_variable(1)
	get_list(5)
	unify_constant('Allocation failure, arg ')
	unify_x_ref(3)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('w', 1, 3)
	unify_x_value(0)
	get_list(4)
	unify_constant(' type ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(3)
	get_structure('w', 1, 0)
	unify_x_value(1)
	get_list(3)
	unify_constant(' in ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_value(2)
	get_list(1)
	unify_constant('nl')
	unify_constant('[]')
	proceed

$19:
	get_constant('system_call_error', 0)
	get_structure('system_call_error', 4, 4)
	unify_void(3)
	unify_x_variable(0)
	get_list(5)
	unify_constant('System call failure: ')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('w', 1, 1)
	unify_x_variable(1)
	get_list(2)
	unify_constant('nl')
	unify_constant('[]')
	pseudo_instr2(89, 0, 2)
	get_x_value(1, 2)
	proceed

$20:
	get_constant('unimplemented_error', 0)
	get_list(5)
	unify_constant('Unimplemented predicate: ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_variable(0)
	get_list(1)
	unify_constant('/')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('w', 1, 1)
	unify_x_variable(1)
	get_list(3)
	unify_constant('nl')
	unify_constant('[]')
	pseudo_instr3(0, 2, 0, 1)
	proceed

$21:
	get_constant('unsupported_error', 0)
	get_list(5)
	unify_constant('Unsupported predicate: ')
	unify_x_ref(0)
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('w', 1, 0)
	unify_x_variable(0)
	get_list(1)
	unify_constant('/')
	unify_x_ref(1)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('w', 1, 1)
	unify_x_variable(1)
	get_list(3)
	unify_constant('nl')
	unify_constant('[]')
	pseudo_instr3(0, 2, 0, 1)
	proceed
end('$builtin_exception_message'/6):



'default_exception_error'/1:


$1:
	allocate(2)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('get_exception_message', 2, 2)
	put_y_value(0, 1)
	put_constant('stderr', 0)
	call_predicate('$streamnum', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$write_term_list', 2)
end('default_exception_error'/1):



'add_global_exception_handler'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$valid_exception_term', 5, 3)
	pseudo_instr1(46, 20)
	cut(2)
	put_structure(2, 0)
	set_constant('$global_exception_handler')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('asserta', 1)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	pseudo_instr1(46, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('$global_exception_handler')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('asserta', 1)

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('add_global_exception_handler')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('add_global_exception_handler')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('goal', 3)
	execute_predicate('instantiation_exception', 4)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('add_global_exception_handler')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('@')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('add_global_exception_handler')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('exception_term', 3)
	execute_predicate('type_exception', 4)
end('add_global_exception_handler'/2):



'remove_global_exception_handler'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$valid_exception_term', 5, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('$global_exception_handler')
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('retract', 1)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('$global_exception_handler')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('retract', 1)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('remove_global_exception_handler')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('?')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('?')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('remove_global_exception_handler')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('exception_term', 3)
	execute_predicate('type_exception', 4)
end('remove_global_exception_handler'/2):



'with_local_exception_handler/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('[]', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('with_local_exception_handler/3$0'/1):



'with_local_exception_handler/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('[]', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('with_local_exception_handler/3$1'/1):



'with_local_exception_handler'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	pseudo_instr1(46, 23)
	get_y_level(4)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$valid_exception_term', 5, 5)
	pseudo_instr1(46, 21)
	cut(4)
	put_constant('$locally_handled_exceptions', 1)
	pseudo_instr2(4, 1, 0)
	get_y_value(0, 0)
	put_y_value(0, 0)
	call_predicate('with_local_exception_handler/3$0', 1, 4)
	put_constant('$locally_handled_exceptions', 0)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(2)
	unify_y_value(0)
	pseudo_instr2(3, 0, 1)
	put_y_value(3, 0)
	put_structure(1, 1)
	set_constant('$exception')
	set_y_value(2)
	put_y_value(1, 2)
	call_predicate('catch', 3, 1)
	put_constant('$locally_handled_exceptions', 0)
	pseudo_instr2(3, 0, 20)
	deallocate
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	pseudo_instr1(46, 23)
	pseudo_instr1(1, 22)
	pseudo_instr1(46, 21)
	neck_cut
	put_constant('$locally_handled_exceptions', 1)
	pseudo_instr2(4, 1, 0)
	get_y_variable(0, 0)
	call_predicate('with_local_exception_handler/3$1', 1, 4)
	put_constant('$locally_handled_exceptions', 0)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(2)
	unify_y_value(0)
	pseudo_instr2(3, 0, 1)
	put_y_value(3, 0)
	put_structure(1, 1)
	set_constant('$exception')
	set_y_value(2)
	put_y_value(1, 2)
	call_predicate('catch', 3, 1)
	put_constant('$locally_handled_exceptions', 0)
	pseudo_instr2(3, 0, 20)
	deallocate
	proceed

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('with_local_exception_handler')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('+')
	set_constant('nonvar')
	put_structure(3, 4)
	set_constant('with_local_exception_handler')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 3)
	set_constant('default')
	set_constant('goal')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 4)

$4:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('with_local_exception_handler')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('+')
	set_constant('nonvar')
	put_structure(3, 4)
	set_constant('with_local_exception_handler')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 3)
	set_constant('default')
	set_constant('goal')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 4)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('with_local_exception_handler')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('+')
	set_constant('nonvar')
	put_structure(3, 4)
	set_constant('with_local_exception_handler')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_structure(1, 3)
	set_constant('default')
	set_constant('exception_term')
	put_integer(2, 1)
	execute_predicate('type_exception', 4)
end('with_local_exception_handler'/3):



'$valid_exception_term'/5:


$1:
	pseudo_instr1(0, 0)
	put_x_variable(5, 5)
	pseudo_instr3(0, 0, 1, 5)
	put_integer(3, 1)
	pseudo_instr2(2, 1, 5)
	put_integer(1, 5)
	pseudo_instr3(1, 5, 0, 1)
	get_x_value(2, 1)
	put_integer(2, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_value(3, 1)
	put_integer(3, 2)
	pseudo_instr3(1, 2, 0, 1)
	get_x_value(4, 1)
	proceed
end('$valid_exception_term'/5):



'$call_exception'/1:


$1:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('call')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('call')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('$call_exception'/1):



'$signal_exception'/3:

	try(3, $1)
	trust($2)

$1:
	execute_predicate('$signal_exception1', 3)

$2:
	proceed
end('$signal_exception'/3):



'$signal_exception1'/3:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	put_y_variable(1, 1)
	call_predicate('$signal_severity', 2, 4)
	put_x_variable(0, 1)
	get_structure('signal', 4, 1)
	unify_y_value(1)
	unify_constant('true')
	unify_y_value(2)
	unify_y_value(3)
	call_predicate('$signal_exception_test', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('$signal_exception1'/3):



'$signal_exception_test'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('exception', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_structure(1, 0)
	set_constant('exception')
	set_x_value(1)
	call_predicate('exception_exception', 1, 1)
	cut(0)
	deallocate
	proceed
end('$signal_exception_test'/1):



'$signal_severity'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'SIGSEGV':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_constant('SIGSEGV', 0)
	get_constant('warning', 1)
	neck_cut
	proceed

$2:
	get_constant('recoverable', 1)
	proceed
end('$signal_severity'/2):



'instantiation_exception'/3:


$1:
	get_x_variable(3, 0)
	put_structure(5, 0)
	set_constant('instantiation_error')
	set_constant('recoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(1)
	set_x_value(2)
	execute_predicate('exception', 1)
end('instantiation_exception'/3):



'instantiation_exception'/4:


$1:
	get_x_variable(4, 0)
	put_structure(1, 5)
	set_constant('default')
	set_x_value(3)
	put_structure(5, 0)
	set_constant('instantiation_error')
	set_constant('recoverable')
	set_x_value(4)
	set_x_value(5)
	set_x_value(1)
	set_x_value(2)
	execute_predicate('exception', 1)
end('instantiation_exception'/4):



'type_exception'/3:


$1:
	get_x_variable(3, 0)
	put_structure(5, 0)
	set_constant('type_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(1)
	set_x_value(2)
	execute_predicate('exception', 1)
end('type_exception'/3):



'type_exception'/4:


$1:
	get_x_variable(4, 0)
	put_structure(1, 5)
	set_constant('default')
	set_x_value(3)
	put_structure(5, 0)
	set_constant('type_error')
	set_constant('unrecoverable')
	set_x_value(4)
	set_x_value(5)
	set_x_value(1)
	set_x_value(2)
	execute_predicate('exception', 1)
end('type_exception'/4):



'exception_exception'/1:


$1:
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('exception_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('exception_exception'/1):



