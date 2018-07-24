'fail'/0:
	/*
	 * fail.
	 */
	fail
end('fail'/0):



'$halt'/1:
	/*
	 * halt(ExitCode).
	 */
	halt
end('$halt'/1):



'check_binder'/1:
	/*
	 * check_binder(BoundList).
	 */
	check_binder(0)
	proceed
end('check_binder'/1):
