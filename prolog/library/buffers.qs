'$buff_code'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$buff_code$', 4, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_constant('$buff_code_error', 0)
	execute_predicate('throw', 1)
end('$buff_code'/4):



