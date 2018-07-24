'true'/0:


$1:
	proceed
end('true'/0):



'='/2:


$1:
	get_x_value(0, 1)
	proceed
end('='/2):



'?=/2$0/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('?=/2$0/2$0'/2):



'?=/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('?=/2$0/2$0', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('?=/2$0'/2):



'?='/2:


$1:
	execute_predicate('?=/2$0', 2)
end('?='/2):



'unify_with_occurs_check'/2:


$1:
	get_x_value(0, 1)
	proceed
end('unify_with_occurs_check'/2):



'\\+/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('\\+/1$0'/1):



'\\+'/1:


$1:
	execute_predicate('\\+/1$0', 1)
end('\\+'/1):



'\\==/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('\\==/2$0'/2):



'\\=='/2:


$1:
	execute_predicate('\\==/2$0', 2)
end('\\=='/2):



'=\\=/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('=:=', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('=\\=/2$0'/2):



'=\\='/2:


$1:
	execute_predicate('=\\=/2$0', 2)
end('=\\='/2):



'->'/2:


$1:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('call', 1, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call', 1)
end('->'/2):



'once'/1:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call', 1, 1)
	cut(0)
	deallocate
	proceed
end('once'/1):



