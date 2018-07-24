'get_char/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$get_char1', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(1, 3)
	set_constant('get_char')
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('get_char/1$0'/2):



'get_char'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('get_char/1$0', 2)
end('get_char'/1):



'get_char/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$get_char1', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 3)
	set_constant('get_char')
	set_x_value(2)
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('get_char/2$0'/2):



'get_char/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$get_char1', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 3)
	set_constant('get_char')
	set_x_value(2)
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('get_char/2$1'/2):



'get_char'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('get_char')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 3)
	set_constant('get_char')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 4)
	set_constant('get_char')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	pseudo_instr2(101, 0, 2)
	get_structure('$prop', 7, 2)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	neck_cut
	execute_predicate('get_char/2$0', 2)

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('get_char/2$1', 2)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('get_char')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 3)
	set_constant('get_char')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 4)
	set_constant('get_char')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('get_char'/2):



'peek/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(135, 0, 2)
	get_x_variable(0, 2)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(1, 3)
	set_constant('peek')
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('peek/1$0'/2):



'peek'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('peek/1$0', 2)
end('peek'/1):



'peek/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(135, 0, 2)
	get_x_variable(0, 2)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 3)
	set_constant('peek')
	set_x_value(2)
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('peek/2$0'/2):



'peek/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(135, 0, 2)
	get_x_variable(0, 2)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 3)
	set_constant('peek')
	set_x_value(2)
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('peek/2$1'/2):



'peek'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('peek')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 3)
	set_constant('peek')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 4)
	set_constant('peek')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	pseudo_instr2(101, 0, 2)
	get_structure('$prop', 7, 2)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	neck_cut
	execute_predicate('peek/2$0', 2)

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('peek/2$1', 2)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('peek')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 3)
	set_constant('peek')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('atomic')
	put_structure(2, 4)
	set_constant('peek')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('peek'/2):



'$get_char1/2$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$get_char1/2$0'/1):



'$get_char1'/2:


$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_level(3)
	put_y_variable(0, 19)
	call_predicate('repeat', 0, 4)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$get_char2', 2, 4)
	put_y_value(0, 0)
	call_predicate('$get_char1/2$0', 1, 4)
	cut(3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$get_char3', 3)
end('$get_char1'/2):



'$get_char2'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_constant('past', 1)
	pseudo_instr1(33, 0)
	neck_cut
	proceed

$2:
	get_constant('end_of_file', 1)
	pseudo_instr1(32, 0)
	neck_cut
	proceed

$3:
	pseudo_instr2(5, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_char2'/2):



'$get_char3'/3:

	switch_on_term(0, $7, $3, $3, $3, $3, $4)

$4:
	switch_on_constant(0, 4, ['$default':$3, 'end_of_file':$5, 'past':$6])

$5:
	try(3, $1)
	trust($3)

$6:
	try(3, $2)
	trust($3)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('end_of_file', 0)
	get_constant('end_of_file', 2)
	pseudo_instr2(101, 1, 0)
	get_structure('$prop', 7, 0)
	unify_void(4)
	unify_x_variable(0)
	unify_void(2)
	neck_cut
	execute_predicate('$eof_action', 2)

$2:
	get_constant('past', 0)
	pseudo_instr2(101, 1, 0)
	get_structure('$prop', 7, 0)
	unify_void(4)
	unify_x_variable(0)
	unify_void(2)
	neck_cut
	execute_predicate('$eof_action', 2)

$3:
	get_x_value(0, 2)
	proceed
end('$get_char3'/3):



'put_char'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('put_char', 2)
end('put_char'/1):



'put_char'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr2(6, 21, 20)
	deallocate
	proceed

$2:
	pseudo_instr2(6, 0, 1)
	proceed
end('put_char'/2):



'tab'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	pseudo_instr2(0, 2, 1)
	get_x_variable(1, 2)
	execute_predicate('$tab', 2)
end('tab'/1):



'tab'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('tab')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('ground')
	put_structure(2, 3)
	set_constant('tab')
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
	set_constant('ground')
	put_structure(2, 4)
	set_constant('tab')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(2)
	pseudo_instr2(0, 0, 21)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$tab', 2)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('tab')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('ground')
	put_structure(2, 3)
	set_constant('tab')
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
	set_constant('ground')
	put_structure(2, 4)
	set_constant('tab')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('tab'/2):



'$tab'/2:

	try(2, $1)
	trust($2)

$1:
	put_integer(0, 0)
	pseudo_instr2(2, 1, 0)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	put_constant(' ', 1)
	call_predicate('put_char', 2, 2)
	pseudo_instr2(70, 21, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$tab', 2)
end('$tab'/2):



'get_line'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('$get_line1', 2)
end('get_line'/1):



'get_line'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	execute_predicate('$get_line1', 2)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('get_line')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('-')
	set_constant('string')
	put_structure(2, 3)
	set_constant('get_line')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$get_line1', 2)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('get_line')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('?')
	set_constant('string')
	put_structure(2, 3)
	set_constant('get_line')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('get_line'/2):



'$get_line1'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr2(93, 3, 0)
	put_x_value(3, 1)
	execute_predicate('$get_line2', 3)
end('$get_line1'/2):



'$get_line2'/3:

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
	get_integer(-1, 0)
	get_integer(-1, 2)
	pseudo_instr2(101, 1, 0)
	get_structure('$prop', 7, 0)
	unify_void(4)
	unify_x_variable(0)
	unify_void(2)
	neck_cut
	execute_predicate('$eof_action', 2)

$2:
	get_x_value(0, 2)
	proceed
end('$get_line2'/3):



'put_line'/1:


$1:
	pseudo_instr1(28, 1)
	pseudo_instr2(113, 1, 0)
	proceed
end('put_line'/1):



'put_line'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	pseudo_instr2(113, 0, 1)
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('put_line')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('string')
	put_structure(2, 3)
	set_constant('put_line')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('put_line')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 21, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(2)
	pseudo_instr2(113, 21, 20)
	deallocate
	proceed

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('put_line')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('string')
	put_structure(2, 3)
	set_constant('put_line')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('put_line')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('put_line'/2):



'get_code/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$get_code1', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(1, 3)
	set_constant('get_code')
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('get_code/1$0'/2):



'get_code'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(27, 0)
	execute_predicate('get_code/1$0', 2)
end('get_code'/1):



'get_code/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$get_code1', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 3)
	set_constant('get_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('get_code/2$0'/2):



'get_code/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$get_code1', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 3)
	set_constant('get_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(2)
	execute_predicate('exception', 1)
end('get_code/2$1'/2):



'get_code'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('get_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('get_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('get_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	pseudo_instr2(101, 0, 2)
	get_structure('$prop', 7, 2)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	neck_cut
	execute_predicate('get_code/2$0', 2)

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('get_code/2$1', 2)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('get_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('get_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('get_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('get_code'/2):



'$get_code1'/2:


$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_level(3)
	put_y_variable(0, 19)
	call_predicate('repeat', 0, 4)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$get_code2', 2, 4)
	cut(3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$get_code3', 3)
end('$get_code1'/2):



'$get_code2'/2:

	try(2, $1)
	trust($2)

$1:
	get_constant('past', 1)
	pseudo_instr1(33, 0)
	neck_cut
	proceed

$2:
	pseudo_instr2(7, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_code2'/2):



'$get_code3'/3:

	switch_on_term(0, $7, $3, $3, $3, $3, $4)

$4:
	switch_on_constant(0, 4, ['$default':$3, -1:$5, 'past':$6])

$5:
	try(3, $1)
	trust($3)

$6:
	try(3, $2)
	trust($3)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_integer(-1, 0)
	get_integer(-1, 2)
	pseudo_instr2(101, 1, 0)
	get_structure('$prop', 7, 0)
	unify_void(4)
	unify_x_variable(0)
	unify_void(2)
	neck_cut
	execute_predicate('$eof_action', 2)

$2:
	get_constant('past', 0)
	pseudo_instr2(101, 1, 0)
	get_structure('$prop', 7, 0)
	unify_void(4)
	unify_x_variable(0)
	unify_void(2)
	neck_cut
	execute_predicate('$eof_action', 2)

$3:
	get_x_value(0, 2)
	proceed
end('$get_code3'/3):



'put_code'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('put_code', 2)
end('put_code'/1):



'put_code'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr2(8, 21, 20)
	deallocate
	proceed

$2:
	pseudo_instr2(8, 0, 1)
	proceed
end('put_code'/2):



'nl'/0:


$1:
	pseudo_instr1(28, 0)
	put_integer(10, 1)
	execute_predicate('put_code', 2)
end('nl'/0):



'nl'/1:


$1:
	put_integer(10, 1)
	execute_predicate('put_code', 2)
end('nl'/1):



'skip'/1:


$1:
	allocate(3)
	get_y_variable(2, 0)
	pseudo_instr1(27, 0)
	get_y_variable(1, 0)
	put_y_variable(0, 1)
	call_predicate('$get_code1', 2, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$skip', 3)
end('skip'/1):



'skip/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('skip/2$0'/1):



'skip'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('skip')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('skip')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	pseudo_instr1(3, 21)
	pseudo_instr2(101, 22, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('input')
	unify_void(5)
	neck_cut
	put_y_value(2, 0)
	put_y_variable(0, 1)
	call_predicate('$get_code1', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$skip', 3)

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('skip')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('skip')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_value(0, 0)
	call_predicate('skip/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('skip')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('skip')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('integer', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('skip')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('skip')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('skip'/2):



'$skip'/3:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, -1:$5])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$6:
	try(3, $2)
	trust($3)

$7:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_integer(-1, 0)
	neck_cut
	put_structure(2, 3)
	set_constant('skip')
	set_x_value(1)
	set_x_value(2)
	put_structure(4, 0)
	set_constant('stream_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	set_x_value(1)
	execute_predicate('exception', 1)

$2:
	get_x_value(0, 2)
	neck_cut
	proceed

$3:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_value(2, 0)
	put_y_variable(0, 1)
	call_predicate('$get_code1', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$skip', 3)
end('$skip'/3):



