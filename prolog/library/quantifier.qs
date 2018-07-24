'$check_bvar'/1:

	switch_on_term(0, $6, $1, $1, $3, $1, $1)

$3:
	switch_on_structure(0, 4, ['$default':$1, '$'/0:$4, ':'/2:$5])

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
	pseudo_instr1(4, 0)
	neck_cut
	proceed

$2:
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_void(1)
	pseudo_instr1(4, 0)
	proceed
end('$check_bvar'/1):



