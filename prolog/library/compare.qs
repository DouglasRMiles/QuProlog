'@=</2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(132, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('@=</2$0'/2):



'@=<'/2:


$1:
	execute_predicate('@=</2$0', 2)
end('@=<'/2):



'@>=/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(130, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('@>=/2$0'/2):



'@>='/2:


$1:
	execute_predicate('@>=/2$0', 2)
end('@>='/2):



'compare'/3:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', '=':$1, '<':$2, '>':$3])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('=', 0)
	pseudo_instr2(131, 1, 2)
	neck_cut
	proceed

$2:
	get_constant('<', 0)
	pseudo_instr2(130, 1, 2)
	neck_cut
	proceed

$3:
	get_constant('>', 0)
	pseudo_instr2(132, 1, 2)
	proceed
end('compare'/3):



