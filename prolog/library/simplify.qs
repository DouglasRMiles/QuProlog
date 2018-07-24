'$simplify_if_local/2$0/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	pseudo_instr1(4, 0)
	proceed
end('$simplify_if_local/2$0/3$0'/1):



'$simplify_if_local/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('$simplify_if_local/2$0/3$0', 1, 3)
	cut(2)
	pseudo_instr2(111, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	pseudo_instr2(25, 0, 3)
	get_x_variable(0, 3)
	put_x_variable(4, 4)
	pseudo_instr3(19, 2, 4, 3)
	get_x_variable(2, 3)
	pseudo_instr2(111, 2, 3)
	get_x_value(1, 3)
	get_x_value(4, 0)
	proceed
end('$simplify_if_local/2$0'/3):



'$simplify_if_local'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	pseudo_instr2(24, 22, 0)
	get_y_variable(0, 0)
	get_y_level(3)
	call_predicate('$locals_in_sub', 1, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$simplify_if_local/2$0', 3)

$2:
	get_x_value(0, 1)
	proceed
end('$simplify_if_local'/2):



