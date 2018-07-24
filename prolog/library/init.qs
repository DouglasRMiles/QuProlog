'$initialise_system_backtrackable'/0:


$1:
	allocate(0)
	call_predicate('$initial_loading', 0, 0)
	deallocate
	execute_predicate('$initialise_subsystems', 0)
end('$initialise_system_backtrackable'/0):



'$initialise_system_non_backtrackable'/0:


$1:
	execute_predicate('$init_retry', 0)
end('$initialise_system_non_backtrackable'/0):



'$initial_loading'/0:


$1:
	proceed
end('$initial_loading'/0):



'$initialise_subsystems'/0:


$1:
	allocate(0)
	call_predicate('$init_debug', 0, 0)
	call_predicate('$init_exception', 0, 0)
	call_predicate('$init_fcompile', 0, 0)
	call_predicate('$init_index', 0, 0)
	call_predicate('$init_interpreter', 0, 0)
	call_predicate('$init_op', 0, 0)
	call_predicate('$init_stream', 0, 0)
	call_predicate('$init_term_exp', 0, 0)
	call_predicate('$init_record', 0, 0)
	deallocate
	execute_predicate('$init_objvar', 0)
end('$initialise_subsystems'/0):



