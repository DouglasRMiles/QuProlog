'error'/1:


$1:
	get_x_variable(1, 0)
	put_constant('stderr', 0)
	put_constant('write', 2)
	put_integer(1200, 3)
	put_integer(1, 4)
	execute_predicate('$write_term', 5)
end('error'/1):



'errornl'/0:


$1:
	put_constant('stderr', 0)
	put_integer(10, 1)
	execute_predicate('put_code', 2)
end('errornl'/0):



'errornl'/1:


$1:
	allocate(0)
	call_predicate('error', 1, 0)
	call_predicate('errornl', 0, 0)
	put_constant('stderr', 0)
	pseudo_instr1(31, 0)
	deallocate
	proceed
end('errornl'/1):



