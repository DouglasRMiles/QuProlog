'$init_stream'/0:


$1:
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(0)
	set_constant('user')
	allocate(0)
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(0)
	set_constant('stdin')
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(0)
	set_constant('user_input')
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(1)
	set_constant('user')
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(1)
	set_constant('stdout')
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(1)
	set_constant('user_output')
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(2)
	set_constant('stderr')
	call_predicate('assertz', 1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_integer(2)
	set_constant('user_error')
	call_predicate('assertz', 1, 0)
	put_integer(0, 0)
	put_x_variable(1, 2)
	get_structure('$prop', 7, 2)
	unify_constant('read')
	unify_constant('input')
	unify_constant('stdin')
	unify_constant('none')
	unify_constant('reset')
	unify_constant('false')
	unify_constant('text')
	pseudo_instr2(100, 0, 1)
	put_integer(1, 0)
	put_x_variable(1, 2)
	get_structure('$prop', 7, 2)
	unify_constant('write')
	unify_constant('output')
	unify_constant('stdout')
	unify_constant('none')
	unify_constant('reset')
	unify_constant('false')
	unify_constant('text')
	pseudo_instr2(100, 0, 1)
	put_integer(2, 0)
	put_x_variable(1, 2)
	get_structure('$prop', 7, 2)
	unify_constant('write')
	unify_constant('output')
	unify_constant('stderr')
	unify_constant('none')
	unify_constant('reset')
	unify_constant('false')
	unify_constant('text')
	pseudo_instr2(100, 0, 1)
	deallocate
	proceed
end('$init_stream'/0):



'$stdio'/1:

	try(1, $1)
	trust($2)

$1:
	neck_cut
	execute_predicate('$stdionum', 1)

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_level(0)
	put_y_variable(1, 0)
	call_predicate('$stdionum', 1, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$stream_alias', 2, 1)
	cut(0)
	deallocate
	proceed
end('$stdio'/1):



'$streamnum'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_level(0)
	put_x_value(2, 1)
	call_predicate('$stream_alias', 2, 1)
	cut(0)
	deallocate
	proceed
end('$streamnum'/2):



'$stdionum'/1:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', 0:$1, 1:$2, 2:$3])

$5:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_integer(0, 0)
	proceed

$2:
	get_integer(1, 0)
	proceed

$3:
	get_integer(2, 0)
	proceed
end('$stdionum'/1):



'open'/3:


$1:
	put_constant('[]', 3)
	execute_predicate('open', 4)
end('open'/3):



'open/4$0'/6:

	try(6, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	allocate(1)
	get_y_level(0)
	call_predicate('$iomode', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(6, 0)
	put_structure(4, 0)
	set_constant('open')
	set_x_value(3)
	set_x_value(6)
	set_x_value(4)
	set_x_value(5)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('open/4$0'/6):



'open/4$1/5$0'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	put_integer(-1, 4)
	get_x_value(0, 4)
	neck_cut
	put_x_variable(4, 5)
	get_structure('open', 4, 5)
	unify_x_value(1)
	unify_x_value(2)
	unify_x_value(0)
	unify_x_value(3)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(4)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened stream ')
	set_x_value(2)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(4)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('open/4$1/5$0'/4):



'open/4$1'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	get_y_level(4)
	call_predicate('$can_open', 2, 6)
	pseudo_instr3(31, 23, 25, 0)
	get_y_value(2, 0)
	cut(4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('open/4$1/5$0', 4)

$2:
	put_structure(4, 5)
	set_constant('open')
	set_x_value(1)
	set_x_value(3)
	set_x_value(2)
	set_x_value(4)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(5)
	set_constant('default')
	execute_predicate('exception', 1)
end('open/4$1'/5):



'open/4$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('open/4$2'/1):



'open'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_variable(4, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(4, 0)
	set_constant('open')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(8)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(1, 2)
	get_y_variable(2, 3)
	pseudo_instr1(2, 25)
	get_y_level(7)
	put_y_variable(6, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	call_predicate('closed_list', 1, 8)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(1, 4)
	put_y_value(2, 5)
	call_predicate('open/4$0', 6, 8)
	cut(7)
	put_y_value(0, 0)
	get_structure('$prop', 7, 0)
	unify_y_value(4)
	unify_y_value(6)
	unify_constant('file')
	unify_y_value(5)
	unify_void(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$open_options', 2, 6)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(1, 2)
	put_y_value(4, 3)
	put_y_value(2, 4)
	call_predicate('open/4$1', 5, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$set_alias', 2, 2)
	pseudo_instr2(100, 21, 20)
	deallocate
	proceed

$3:
	get_x_variable(4, 0)
	pseudo_instr1(1, 4)
	neck_cut
	put_structure(4, 0)
	set_constant('open')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(4, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(4, 0)
	set_constant('open')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(4, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_level(4)
	call_predicate('open/4$2', 1, 5)
	cut(4)
	put_structure(4, 0)
	set_constant('open')
	set_y_value(3)
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	get_x_variable(4, 0)
	put_structure(4, 0)
	set_constant('open')
	set_x_value(4)
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(4, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(4, 1)
	execute_predicate('type_exception', 3)
end('open'/4):



'$can_open/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	put_integer(-1, 2)
	execute_predicate('access', 3)

$2:
	put_integer(2, 1)
	put_integer(0, 2)
	execute_predicate('access', 3)
end('$can_open/2$0'/1):



'$can_open'/2:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', 0:$1, 1:$2, 2:$3])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_integer(0, 0)
	get_x_variable(0, 1)
	put_integer(4, 1)
	put_integer(0, 2)
	execute_predicate('access', 3)

$2:
	get_integer(1, 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_level(0)
	call_predicate('$can_open/2$0', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_integer(2, 0)
	get_x_variable(0, 1)
	put_integer(2, 1)
	put_integer(0, 2)
	execute_predicate('access', 3)
end('$can_open'/2):



'open_string'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('open_string', 3)
end('open_string'/2):



'open_string/3$0/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_integer(-1, 2)
	get_x_value(0, 2)
	neck_cut
	put_x_variable(2, 3)
	get_structure('open_string', 3, 3)
	unify_constant('write')
	unify_x_value(0)
	unify_x_value(1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened stream ')
	set_x_value(3)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('open_string/3$0/3$0'/2):



'open_string/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	pseudo_instr4(4, 4, 3, 5, 2)
	get_x_value(0, 2)
	neck_cut
	execute_predicate('open_string/3$0/3$0', 2)

$2:
	put_structure(3, 3)
	set_constant('open_string')
	set_constant('write')
	set_x_value(1)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	execute_predicate('exception', 1)
end('open_string/3$0'/3):



'open_string/3$1'/4:

	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	put_integer(0, 0)
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr1(108, 0)
	neck_cut
	put_integer(2, 0)
	get_x_value(1, 0)
	proceed

$3:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	put_x_value(0, 1)
	put_constant('integer', 0)
	call_predicate('application', 2, 2)
	cut(1)
	put_y_value(0, 0)
	get_integer(1, 0)
	deallocate
	proceed

$4:
	put_structure(1, 1)
	set_constant('read')
	set_x_value(0)
	put_structure(3, 0)
	set_constant('open_string')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('open_string')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('open_string/3$1'/4):



'open_string/3$2/5$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_integer(-1, 3)
	get_x_value(0, 3)
	neck_cut
	put_x_variable(3, 4)
	get_structure('open_string', 3, 4)
	unify_x_ref(4)
	unify_x_value(0)
	unify_x_value(2)
	get_structure('read', 1, 4)
	unify_x_value(1)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(3)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened stream ')
	set_x_value(2)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('open_string/3$2/5$0'/3):



'open_string/3$2'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	get_x_variable(6, 2)
	get_x_variable(0, 3)
	get_x_variable(2, 4)
	pseudo_instr4(4, 5, 1, 6, 3)
	get_x_value(0, 3)
	neck_cut
	put_x_value(5, 1)
	execute_predicate('open_string/3$2/5$0', 3)

$2:
	put_structure(1, 1)
	set_constant('read')
	set_x_value(0)
	put_structure(3, 2)
	set_constant('open_string')
	set_x_value(1)
	set_x_value(3)
	set_x_value(4)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_constant('default')
	execute_predicate('exception', 1)
end('open_string/3$2'/5):



'open_string'/3:

	switch_on_term(0, $12, $11, $11, $6, $11, $9)

$6:
	switch_on_structure(0, 4, ['$default':$11, '$'/0:$7, 'read'/1:$8])

$7:
	try(3, $1)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(3, $1)
	retry($3)
	retry($4)
	trust($5)

$9:
	switch_on_constant(0, 4, ['$default':$11, 'write':$10])

$10:
	try(3, $1)
	retry($2)
	retry($4)
	trust($5)

$11:
	try(3, $1)
	retry($4)
	trust($5)

$12:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('open_string')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('open_string')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_constant('write', 0)
	allocate(6)
	get_y_variable(1, 1)
	get_y_variable(2, 2)
	get_y_level(5)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	call_predicate('closed_list', 1, 6)
	cut(5)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_constant('write', 0)
	call_predicate('$iomode', 3, 5)
	put_y_value(0, 0)
	get_structure('$prop', 7, 0)
	unify_constant('write')
	unify_y_value(4)
	unify_constant('string')
	unify_constant('none')
	unify_void(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$open_options', 2, 4)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	call_predicate('open_string/3$0', 3, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$set_alias', 2, 2)
	pseudo_instr2(100, 21, 20)
	deallocate
	proceed

$3:
	get_structure('read', 1, 0)
	allocate(8)
	unify_y_variable(5)
	get_y_variable(1, 1)
	get_y_variable(2, 2)
	get_y_level(7)
	put_y_variable(6, 19)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_value(2, 0)
	call_predicate('closed_list', 1, 8)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	call_predicate('open_string/3$1', 4, 8)
	cut(7)
	put_y_value(3, 1)
	put_y_value(6, 2)
	put_constant('read', 0)
	call_predicate('$iomode', 3, 7)
	put_y_value(0, 0)
	get_structure('$prop', 7, 0)
	unify_constant('read')
	unify_y_value(6)
	unify_constant('string')
	unify_constant('none')
	unify_void(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$open_options', 2, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_y_value(1, 3)
	put_y_value(2, 4)
	call_predicate('open_string/3$2', 5, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$set_alias', 2, 2)
	pseudo_instr2(100, 21, 20)
	deallocate
	proceed

$4:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('open_string')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('open_string')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('open_string')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('-')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('open_string')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('type_exception', 3)
end('open_string'/3):



'open_msgstream/3$0'/5:

	try(5, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	allocate(1)
	get_y_level(0)
	call_predicate('$iomode', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(5, 0)
	put_structure(3, 0)
	set_constant('open')
	set_x_value(3)
	set_x_value(5)
	set_x_value(4)
	put_structure(1, 1)
	set_constant('@')
	set_constant('handle')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(3, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('atom', 3)
	execute_predicate('type_exception', 4)
end('open_msgstream/3$0'/5):



'open_msgstream/3$1/5$0'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, -1:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	put_integer(-1, 3)
	get_x_value(0, 3)
	neck_cut
	put_x_variable(3, 4)
	get_structure('open_msgstream', 3, 4)
	unify_x_value(1)
	unify_x_value(2)
	unify_x_value(0)
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_structure(1, 1)
	set_constant('w')
	set_x_value(3)
	put_list(2)
	set_x_value(1)
	set_x_value(0)
	put_list(1)
	set_constant('too many opened streams ')
	set_x_value(2)
	put_structure(3, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	proceed
end('open_msgstream/3$1/5$0'/3):



'open_msgstream/3$1'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	get_x_variable(0, 2)
	get_x_variable(2, 3)
	pseudo_instr3(49, 5, 1, 3)
	get_x_value(0, 3)
	neck_cut
	put_x_value(5, 1)
	execute_predicate('open_msgstream/3$1/5$0', 3)

$2:
	put_structure(3, 1)
	set_constant('open_msgstream')
	set_x_value(4)
	set_x_value(3)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('open_msgstream/3$1'/5):



'open_msgstream'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('open_msgstream')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('handle')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('-')
	set_constant('gcomp')
	put_structure(3, 4)
	set_constant('open')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	get_y_level(6)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_variable(2, 1)
	put_y_variable(5, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	call_predicate('open_msgstream/3$0', 5, 7)
	cut(6)
	put_y_value(0, 0)
	get_structure('$prop', 7, 0)
	unify_y_value(3)
	unify_y_value(5)
	unify_constant('msg')
	unify_constant('none')
	unify_constant('reset')
	unify_constant('false')
	unify_constant('text')
	put_y_value(4, 0)
	get_structure('@', 2, 0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr2(79, 0, 2)
	get_x_variable(0, 2)
	pseudo_instr2(80, 2, 0)
	put_x_variable(0, 3)
	get_structure('@', 2, 3)
	unify_x_value(1)
	unify_x_value(2)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(3, 3)
	put_y_value(4, 4)
	call_predicate('open_msgstream/3$1', 5, 2)
	pseudo_instr2(100, 21, 20)
	deallocate
	proceed
end('open_msgstream'/3):



'$set_alias'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	put_structure(1, 0)
	set_constant('alias')
	set_y_variable(0)
	call_predicate('member', 2, 2)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_y_value(1)
	set_y_value(0)
	call_predicate('assertz', 1, 0)
	fail

$2:
	proceed
end('$set_alias'/2):



'$open_options'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_structure(1, 0)
	set_constant('eof_action')
	set_void(1)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('eof_code', 3)
	call_predicate('$add_open_options', 4, 2)
	put_structure(1, 0)
	set_constant('reposition')
	set_void(1)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('false', 3)
	call_predicate('$add_open_options', 4, 2)
	put_structure(1, 0)
	set_constant('type')
	set_void(1)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('text', 3)
	deallocate
	execute_predicate('$add_open_options', 4)
end('$open_options'/2):



'$add_open_options'/4:


$1:
	allocate(6)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(4, 2)
	get_y_variable(0, 3)
	put_y_variable(5, 1)
	put_y_variable(3, 2)
	call_predicate('$property_name', 3, 6)
	pseudo_instr3(1, 25, 24, 0)
	get_y_value(3, 0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$process_option', 3)
end('$add_open_options'/4):



'$iomode'/3:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', 'read':$1, 'write':$2, 'append':$3])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('read', 0)
	get_integer(0, 1)
	get_constant('input', 2)
	proceed

$2:
	get_constant('write', 0)
	get_integer(1, 1)
	get_constant('output', 2)
	proceed

$3:
	get_constant('append', 0)
	get_integer(2, 1)
	get_constant('output', 2)
	proceed
end('$iomode'/3):



'close'/1:


$1:
	put_constant('[]', 1)
	execute_predicate('close', 2)
end('close'/1):



'close/2$0/3$0'/2:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '$prop'/7:$5])

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
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	neck_cut
	proceed

$2:
	pseudo_instr1(31, 1)
	proceed
end('close/2$0/3$0'/2):



'close/2$0/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	put_structure(2, 0)
	set_constant('$stream_alias')
	set_x_value(1)
	set_void(1)
	allocate(0)
	call_predicate('retract', 1, 0)
	fail

$2:
	proceed
end('close/2$0/3$1'/1):



'close/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_list(1)
	set_integer(2)
	set_constant('[]')
	put_list(2)
	set_integer(1)
	set_x_value(1)
	put_list(1)
	set_integer(0)
	set_x_value(2)
	call_predicate('member', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	pseudo_instr2(101, 21, 0)
	cut(2)
	put_y_value(1, 1)
	call_predicate('close/2$0/3$0', 2, 2)
	put_y_value(1, 0)
	call_predicate('close/2$0/3$1', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$close1', 2)
end('close/2$0'/3):



'close'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('close')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('close')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('close')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('close')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('close')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('close')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(2, 1)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('close/2$0', 3)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('close')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('close')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('close')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('close'/2):



'$close1'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$stdionum', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	pseudo_instr1(27, 2)
	get_x_value(0, 2)
	neck_cut
	allocate(0)
	call_predicate('$close2', 2, 0)
	put_constant('stdin', 0)
	deallocate
	execute_predicate('set_input', 1)

$3:
	pseudo_instr1(28, 2)
	get_x_value(0, 2)
	neck_cut
	allocate(0)
	call_predicate('$close2', 2, 0)
	put_constant('stdout', 0)
	deallocate
	execute_predicate('set_output', 1)

$4:
	execute_predicate('$close2', 2)
end('$close1'/2):



'$close2'/2:


$1:
	allocate(3)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	call_predicate('$close_options', 2, 3)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 22, 0)
	put_y_value(0, 1)
	call_predicate('$boolnum', 2, 2)
	pseudo_instr2(40, 21, 20)
	deallocate
	proceed
end('$close2'/2):



'$close_options'/2:


$1:
	get_x_variable(2, 0)
	get_structure('$close_flag', 1, 1)
	unify_x_variable(1)
	put_structure(1, 0)
	set_constant('force')
	set_x_value(1)
	put_x_value(2, 1)
	put_constant('false', 2)
	execute_predicate('$process_option', 3)
end('$close_options'/2):



'$boolnum'/2:

	switch_on_term(0, $4, 'fail', 'fail', 'fail', 'fail', $3)

$3:
	switch_on_constant(0, 4, ['$default':'fail', 'false':$1, 'true':$2])

$4:
	try(2, $1)
	trust($2)

$1:
	get_constant('false', 0)
	get_integer(0, 1)
	proceed

$2:
	get_constant('true', 0)
	get_integer(1, 1)
	proceed
end('$boolnum'/2):



'set_input'/1:


$1:
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	cut(1)
	pseudo_instr1(29, 20)
	deallocate
	proceed
end('set_input'/1):



'set_output'/1:


$1:
	allocate(2)
	get_y_level(1)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(1)
	pseudo_instr1(30, 20)
	deallocate
	proceed
end('set_output'/1):



'flush_output'/0:


$1:
	pseudo_instr1(28, 0)
	pseudo_instr1(31, 0)
	proceed
end('flush_output'/0):



'stream_property'/2:

	try(2, $1)
	trust($2)

$1:
	get_structure('alias', 1, 1)
	unify_x_variable(1)
	execute_predicate('$stream_alias', 2)

$2:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr2(101, 20, 0)
	get_x_variable(2, 0)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$stream_property1', 3)
end('stream_property'/2):



'$stream_property1/3$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(32, 0)
	proceed

$2:
	pseudo_instr1(33, 0)
	proceed
end('$stream_property1/3$0/1$0'/1):



'$stream_property1/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$stream_property1/3$0/1$0', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$stream_property1/3$0'/1):



'$stream_property1'/3:

	switch_on_term(0, $14, $13, $13, $8, $13, $13)

$8:
	switch_on_structure(0, 8, ['$default':$13, '$'/0:$9, 'end_of_stream'/1:$10, 'position'/1:$11, 'line_number'/1:$12])

$9:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$10:
	try(3, $1)
	retry($2)
	retry($3)
	retry($6)
	trust($7)

$11:
	try(3, $4)
	retry($6)
	trust($7)

$12:
	try(3, $5)
	retry($6)
	trust($7)

$13:
	try(3, $6)
	trust($7)

$14:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_structure('end_of_stream', 1, 0)
	unify_constant('at')
	pseudo_instr1(32, 1)
	proceed

$2:
	get_structure('end_of_stream', 1, 0)
	unify_constant('past')
	pseudo_instr1(33, 1)
	proceed

$3:
	get_structure('end_of_stream', 1, 0)
	unify_constant('no')
	get_x_variable(0, 1)
	execute_predicate('$stream_property1/3$0', 1)

$4:
	get_structure('position', 1, 0)
	unify_x_variable(0)
	pseudo_instr2(41, 1, 2)
	get_x_value(0, 2)
	proceed

$5:
	get_structure('line_number', 1, 0)
	unify_x_variable(0)
	pseudo_instr2(43, 1, 2)
	get_x_value(0, 2)
	proceed

$6:
	allocate(4)
	get_y_variable(0, 0)
	get_y_variable(2, 2)
	pseudo_instr1(46, 20)
	neck_cut
	put_y_variable(3, 1)
	put_y_variable(1, 2)
	call_predicate('$property_name', 3, 4)
	pseudo_instr3(1, 23, 22, 0)
	put_y_value(1, 1)
	call_predicate('$stream_prop', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$check_property', 1)

$7:
	allocate(5)
	get_y_variable(0, 0)
	get_y_variable(4, 2)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(3, 2)
	put_integer(1, 0)
	put_integer(7, 1)
	call_predicate('between', 3, 5)
	pseudo_instr3(1, 23, 24, 0)
	get_y_value(2, 0)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	call_predicate('$property_name', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$stream_prop', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$check_property', 1)
end('$stream_property1'/3):



'$check_property'/1:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, 'file_name'/1:$5])

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
	get_structure('file_name', 1, 0)
	unify_constant('none')
	neck_cut
	fail

$2:
	proceed
end('$check_property'/1):



'$property_name'/3:

	switch_on_term(0, $12, 'fail', 'fail', $9, 'fail', $11)

$9:
	switch_on_structure(0, 16, ['$default':'fail', '$'/0:$10, 'mode'/1:$1, 'file_name'/1:$5, 'eof_action'/1:$6, 'reposition'/1:$7, 'type'/1:$8])

$10:
	try(3, $1)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$11:
	switch_on_constant(0, 8, ['$default':'fail', 'input':$2, 'output':$3, 'string':$4])

$12:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_integer(1, 1)
	get_structure('mode', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$2:
	get_constant('input', 0)
	get_integer(2, 1)
	get_constant('input', 2)
	proceed

$3:
	get_constant('output', 0)
	get_integer(2, 1)
	get_constant('output', 2)
	proceed

$4:
	get_constant('string', 0)
	get_integer(3, 1)
	get_constant('string', 2)
	proceed

$5:
	get_integer(4, 1)
	get_structure('file_name', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$6:
	get_integer(5, 1)
	get_structure('eof_action', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$7:
	get_integer(6, 1)
	get_structure('reposition', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$8:
	get_integer(7, 1)
	get_structure('type', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed
end('$property_name'/3):



'$stream_prop'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	pseudo_instr1(50, 2)
	neck_cut
	put_x_value(2, 1)
	execute_predicate('member', 2)

$3:
	get_x_value(0, 1)
	proceed
end('$stream_prop'/2):



'at_end_of_stream'/0:


$1:
	pseudo_instr1(27, 0)
	pseudo_instr1(32, 0)
	neck_cut
	proceed
end('at_end_of_stream'/0):



'past_end_of_stream'/0:


$1:
	pseudo_instr1(27, 0)
	pseudo_instr1(33, 0)
	neck_cut
	proceed
end('past_end_of_stream'/0):



'$eof_action'/2:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', 'error':$1, 'eof_code':$2, 'reset':$3])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('error', 0)
	put_structure(1, 2)
	set_constant('eof_action')
	set_constant('error')
	put_list(0)
	set_constant('nl')
	set_constant('[]')
	put_list(3)
	set_x_value(1)
	set_x_value(0)
	put_list(4)
	set_constant('attempt to read the end of file ')
	set_x_value(3)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(2)
	set_x_value(4)
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	get_constant('eof_code', 0)
	proceed

$3:
	get_constant('reset', 0)
	pseudo_instr1(34, 1)
	proceed
end('$eof_action'/2):



'set_stream_position/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('set_stream_position/2$0'/1):



'set_stream_position'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('set_stream_position')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(3, 20)
	get_y_level(2)
	put_structure(1, 1)
	set_constant('reposition')
	set_constant('true')
	call_predicate('stream_property', 2, 3)
	cut(2)
	pseudo_instr2(42, 21, 20)
	deallocate
	proceed

$3:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_structure(1, 1)
	set_constant('reposition')
	set_constant('false')
	call_predicate('stream_property', 2, 2)
	put_structure(2, 1)
	set_constant('set_stream_position')
	set_y_value(1)
	set_y_value(0)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	deallocate
	execute_predicate('exception', 1)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('set_stream_position')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(0, 0)
	call_predicate('set_stream_position/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('set_stream_position')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('set_stream_position')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	put_constant('integer', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('set_stream_position')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('set_stream_position')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('set_stream_position'/2):



