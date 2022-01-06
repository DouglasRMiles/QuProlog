'$failpt_to_catch'/0:


$1:
	pseudo_instr0(0)
	proceed
end('$failpt_to_catch'/0):



'$catch_to_failpt'/0:


$1:
	pseudo_instr0(1)
	proceed
end('$catch_to_failpt'/0):



'$clear_all_signals'/0:


$1:
	pseudo_instr0(2)
	proceed
end('$clear_all_signals'/0):



'$psidelay_resume'/0:


$1:
	pseudo_instr0(3)
	proceed
end('$psidelay_resume'/0):



'$compress_var_delays'/0:


$1:
	pseudo_instr0(4)
	proceed
end('$compress_var_delays'/0):



'$retry_nfi_obvars'/0:


$1:
	pseudo_instr0(5)
	proceed
end('$retry_nfi_obvars'/0):



'fast_retry_delays'/0:


$1:
	pseudo_instr0(6)
	proceed
end('fast_retry_delays'/0):



'thread_yield'/0:


$1:
	pseudo_instr0(7)
	proceed
end('thread_yield'/0):



'thread_exit'/0:


$1:
	pseudo_instr0(8)
	proceed
end('thread_exit'/0):



'thread_is_initial_thread'/0:


$1:
	pseudo_instr0(9)
	proceed
end('thread_is_initial_thread'/0):



'$signal_thread_exit'/0:


$1:
	pseudo_instr0(10)
	proceed
end('$signal_thread_exit'/0):



'gc'/0:


$1:
	pseudo_instr0(11)
	proceed
end('gc'/0):



'pedro_deregister'/0:


$1:
	pseudo_instr0(12)
	proceed
end('pedro_deregister'/0):



'pedro_is_connected'/0:


$1:
	pseudo_instr0(13)
	proceed
end('pedro_is_connected'/0):



'pedro_is_registered'/0:


$1:
	pseudo_instr0(14)
	proceed
end('pedro_is_registered'/0):



'pedro_disconnect'/0:


$1:
	pseudo_instr0(15)
	proceed
end('pedro_disconnect'/0):



'$suspend_gc'/0:


$1:
	pseudo_instr0(16)
	proceed
end('$suspend_gc'/0):



'$unsuspend_gc'/0:


$1:
	pseudo_instr0(17)
	proceed
end('$unsuspend_gc'/0):



'compound'/1:


$1:
	pseudo_instr1(0, 0)
	proceed
end('compound'/1):



'var'/1:


$1:
	pseudo_instr1(1, 0)
	proceed
end('var'/1):



'atom'/1:


$1:
	pseudo_instr1(2, 0)
	proceed
end('atom'/1):



'integer'/1:


$1:
	pseudo_instr1(3, 0)
	proceed
end('integer'/1):



'obvar'/1:


$1:
	pseudo_instr1(4, 0)
	proceed
end('obvar'/1):



'quant'/1:


$1:
	pseudo_instr1(5, 0)
	proceed
end('quant'/1):



'sub'/1:


$1:
	pseudo_instr1(6, 0)
	proceed
end('sub'/1):



'$get_level'/1:


$1:
	pseudo_instr1(7, 1)
	get_x_value(0, 1)
	proceed
end('$get_level'/1):



'$delayneckcut'/1:


$1:
	pseudo_instr1(8, 0)
	proceed
end('$delayneckcut'/1):



'$cut'/1:


$1:
	pseudo_instr1(9, 0)
	proceed
end('$cut'/1):



'$get_qplibpath'/1:


$1:
	pseudo_instr1(10, 1)
	get_x_value(0, 1)
	proceed
end('$get_qplibpath'/1):



'get_args'/1:


$1:
	pseudo_instr1(11, 1)
	get_x_value(0, 1)
	proceed
end('get_args'/1):



'$psi_retract'/1:


$1:
	pseudo_instr1(12, 0)
	proceed
end('$psi_retract'/1):



'$save'/1:


$1:
	pseudo_instr1(13, 0)
	proceed
end('$save'/1):



'$restore'/1:


$1:
	pseudo_instr1(14, 0)
	proceed
end('$restore'/1):



'$cputime'/1:


$1:
	pseudo_instr1(15, 1)
	get_x_value(0, 1)
	proceed
end('$cputime'/1):



'$stat_memory'/1:


$1:
	pseudo_instr1(16, 1)
	get_x_value(0, 1)
	proceed
end('$stat_memory'/1):



'$stat_program'/1:


$1:
	pseudo_instr1(17, 1)
	get_x_value(0, 1)
	proceed
end('$stat_program'/1):



'$empty_sub'/1:


$1:
	pseudo_instr1(18, 1)
	get_x_value(0, 1)
	proceed
end('$empty_sub'/1):



'$call_predicate0'/1:


$1:
	pseudo_instr1(19, 0)
	proceed
end('$call_predicate0'/1):



'$code_top'/1:


$1:
	pseudo_instr1(20, 1)
	get_x_value(0, 1)
	proceed
end('$code_top'/1):



'$get_catch'/1:


$1:
	pseudo_instr1(21, 1)
	get_x_value(0, 1)
	proceed
end('$get_catch'/1):



'$set_catch'/1:


$1:
	pseudo_instr1(22, 0)
	proceed
end('$set_catch'/1):



'$psi_resume'/1:


$1:
	pseudo_instr1(23, 0)
	proceed
end('$psi_resume'/1):



'irandom'/1:


$1:
	pseudo_instr1(24, 1)
	get_x_value(0, 1)
	proceed
end('irandom'/1):



'$clear_signal'/1:


$1:
	pseudo_instr1(25, 0)
	proceed
end('$clear_signal'/1):



'$default_signal_handler'/1:


$1:
	pseudo_instr1(26, 0)
	proceed
end('$default_signal_handler'/1):



'current_input'/1:


$1:
	pseudo_instr1(27, 1)
	get_x_value(0, 1)
	proceed
end('current_input'/1):



'current_output'/1:


$1:
	pseudo_instr1(28, 1)
	get_x_value(0, 1)
	proceed
end('current_output'/1):



'$set_input'/1:


$1:
	pseudo_instr1(29, 0)
	proceed
end('$set_input'/1):



'$set_output'/1:


$1:
	pseudo_instr1(30, 0)
	proceed
end('$set_output'/1):



'flush_output'/1:


$1:
	pseudo_instr1(31, 0)
	proceed
end('flush_output'/1):



'at_end_of_stream'/1:


$1:
	pseudo_instr1(32, 0)
	proceed
end('at_end_of_stream'/1):



'past_end_of_stream'/1:


$1:
	pseudo_instr1(33, 0)
	proceed
end('past_end_of_stream'/1):



'$reset_stream'/1:


$1:
	pseudo_instr1(34, 0)
	proceed
end('$reset_stream'/1):



'$local_obvar'/1:


$1:
	pseudo_instr1(35, 0)
	proceed
end('$local_obvar'/1):



'$new_obvar'/1:


$1:
	pseudo_instr1(36, 1)
	get_x_value(0, 1)
	proceed
end('$new_obvar'/1):



'$valid_obvar_prefix'/1:


$1:
	pseudo_instr1(37, 0)
	proceed
end('$valid_obvar_prefix'/1):



'$set_trace_level'/1:


$1:
	pseudo_instr1(38, 0)
	proceed
end('$set_trace_level'/1):



'freeze_var'/1:


$1:
	pseudo_instr1(39, 0)
	proceed
end('freeze_var'/1):



'thaw_var'/1:


$1:
	pseudo_instr1(40, 0)
	proceed
end('thaw_var'/1):



'frozen_var'/1:


$1:
	pseudo_instr1(41, 0)
	proceed
end('frozen_var'/1):



'thawed_var'/1:


$1:
	pseudo_instr1(42, 0)
	proceed
end('thawed_var'/1):



'atomic'/1:


$1:
	pseudo_instr1(43, 0)
	proceed
end('atomic'/1):



'any_variable'/1:


$1:
	pseudo_instr1(44, 0)
	proceed
end('any_variable'/1):



'simple'/1:


$1:
	pseudo_instr1(45, 0)
	proceed
end('simple'/1):



'nonvar'/1:


$1:
	pseudo_instr1(46, 0)
	proceed
end('nonvar'/1):



'std_var'/1:


$1:
	pseudo_instr1(47, 0)
	proceed
end('std_var'/1):



'std_nonvar'/1:


$1:
	pseudo_instr1(48, 0)
	proceed
end('std_nonvar'/1):



'std_compound'/1:


$1:
	pseudo_instr1(49, 0)
	proceed
end('std_compound'/1):



'list'/1:


$1:
	pseudo_instr1(50, 0)
	proceed
end('list'/1):



'freeze_term'/1:


$1:
	pseudo_instr1(51, 0)
	proceed
end('freeze_term'/1):



'thaw_term'/1:


$1:
	pseudo_instr1(52, 0)
	proceed
end('thaw_term'/1):



'name_vars'/1:


$1:
	pseudo_instr1(53, 0)
	proceed
end('name_vars'/1):



'ip_array_clear'/1:


$1:
	pseudo_instr1(54, 0)
	proceed
end('ip_array_clear'/1):



'$ipc_commit'/1:


$1:
	pseudo_instr1(55, 0)
	proceed
end('$ipc_commit'/1):



'tcp_listen'/1:


$1:
	pseudo_instr1(56, 0)
	proceed
end('tcp_listen'/1):



'tcp_checkconn'/1:


$1:
	pseudo_instr1(57, 0)
	proceed
end('tcp_checkconn'/1):



'tcp_close'/1:


$1:
	pseudo_instr1(58, 0)
	proceed
end('tcp_close'/1):



'realtime'/1:


$1:
	pseudo_instr1(59, 1)
	get_x_value(0, 1)
	proceed
end('realtime'/1):



'$single_sub'/1:


$1:
	pseudo_instr1(60, 0)
	proceed
end('$single_sub'/1):



'tcp_is_socket'/1:


$1:
	pseudo_instr1(61, 0)
	proceed
end('tcp_is_socket'/1):



'process_pid'/1:


$1:
	pseudo_instr1(62, 1)
	get_x_value(0, 1)
	proceed
end('process_pid'/1):



'thread_set_symbol'/1:


$1:
	pseudo_instr1(63, 0)
	proceed
end('thread_set_symbol'/1):



'thread_goal'/1:


$1:
	pseudo_instr1(64, 1)
	get_x_value(0, 1)
	proceed
end('thread_goal'/1):



'thread_is_thread'/1:


$1:
	pseudo_instr1(65, 0)
	proceed
end('thread_is_thread'/1):



'thread_is_runnable'/1:


$1:
	pseudo_instr1(66, 0)
	proceed
end('thread_is_runnable'/1):



'thread_is_suspended'/1:


$1:
	pseudo_instr1(67, 0)
	proceed
end('thread_is_suspended'/1):



'$thread_tid'/1:


$1:
	pseudo_instr1(68, 1)
	get_x_value(0, 1)
	proceed
end('$thread_tid'/1):



'thread_suspend'/1:


$1:
	pseudo_instr1(69, 0)
	proceed
end('thread_suspend'/1):



'thread_resume'/1:


$1:
	pseudo_instr1(70, 0)
	proceed
end('thread_resume'/1):



'$thread_wait_timeout'/1:


$1:
	pseudo_instr1(71, 0)
	proceed
end('$thread_wait_timeout'/1):



'$thread_defaults'/1:


$1:
	pseudo_instr1(72, 1)
	get_x_value(0, 1)
	proceed
end('$thread_defaults'/1):



'$thread_set_defaults'/1:


$1:
	pseudo_instr1(73, 0)
	proceed
end('$thread_set_defaults'/1):



'chdir'/1:


$1:
	pseudo_instr1(74, 0)
	proceed
end('chdir'/1):



'getcwd'/1:


$1:
	pseudo_instr1(75, 1)
	get_x_value(0, 1)
	proceed
end('getcwd'/1):



'nsig'/1:


$1:
	pseudo_instr1(76, 1)
	get_x_value(0, 1)
	proceed
end('nsig'/1):



'thread_errno'/1:


$1:
	pseudo_instr1(77, 1)
	get_x_value(0, 1)
	proceed
end('thread_errno'/1):



'set_trace_flag'/1:


$1:
	pseudo_instr1(78, 0)
	proceed
end('set_trace_flag'/1):



'clear_trace_flag'/1:


$1:
	pseudo_instr1(79, 0)
	proceed
end('clear_trace_flag'/1):



'test_trace_flag'/1:


$1:
	pseudo_instr1(80, 0)
	proceed
end('test_trace_flag'/1):



'$tcp_connect2'/1:


$1:
	pseudo_instr1(81, 0)
	proceed
end('$tcp_connect2'/1):



'stdin'/1:


$1:
	pseudo_instr1(82, 1)
	get_x_value(0, 1)
	proceed
end('stdin'/1):



'stdout'/1:


$1:
	pseudo_instr1(83, 1)
	get_x_value(0, 1)
	proceed
end('stdout'/1):



'stderr'/1:


$1:
	pseudo_instr1(84, 1)
	get_x_value(0, 1)
	proceed
end('stderr'/1):



'float'/1:


$1:
	pseudo_instr1(85, 0)
	proceed
end('float'/1):



'srandom'/1:


$1:
	pseudo_instr1(86, 0)
	proceed
end('srandom'/1):



'$pedro_notify'/1:


$1:
	pseudo_instr1(87, 0)
	proceed
end('$pedro_notify'/1):



'process_symbol'/1:


$1:
	pseudo_instr1(88, 1)
	get_x_value(0, 1)
	proceed
end('process_symbol'/1):



'$pedro_register'/1:


$1:
	pseudo_instr1(89, 0)
	proceed
end('$pedro_register'/1):



'thread_handle'/1:


$1:
	pseudo_instr1(90, 1)
	get_x_value(0, 1)
	proceed
end('thread_handle'/1):



'$alloc_buffer'/1:


$1:
	pseudo_instr1(91, 1)
	get_x_value(0, 1)
	proceed
end('$alloc_buffer'/1):



'$dealloc_buffer'/1:


$1:
	pseudo_instr1(92, 0)
	proceed
end('$dealloc_buffer'/1):



'$debug_write'/1:


$1:
	pseudo_instr1(93, 0)
	proceed
end('$debug_write'/1):



'$addExtraInfoToVars'/1:


$1:
	pseudo_instr1(94, 0)
	proceed
end('$addExtraInfoToVars'/1):



'$reset_std_stream'/1:


$1:
	pseudo_instr1(95, 0)
	proceed
end('$reset_std_stream'/1):



'current_threads'/1:


$1:
	pseudo_instr1(96, 1)
	get_x_value(0, 1)
	proceed
end('current_threads'/1):



'thread_exit'/1:


$1:
	pseudo_instr1(97, 0)
	proceed
end('thread_exit'/1):



'pedro_address'/1:


$1:
	pseudo_instr1(98, 1)
	get_x_value(0, 1)
	proceed
end('pedro_address'/1):



'pedro_port'/1:


$1:
	pseudo_instr1(99, 1)
	get_x_value(0, 1)
	proceed
end('pedro_port'/1):



'bound'/1:


$1:
	pseudo_instr1(100, 0)
	proceed
end('bound'/1):



'$psi_make_iterator'/1:


$1:
	pseudo_instr1(101, 1)
	get_x_value(0, 1)
	proceed
end('$psi_make_iterator'/1):



'set_autoflush'/1:


$1:
	pseudo_instr1(102, 0)
	proceed
end('set_autoflush'/1):



'get_open_streams'/1:


$1:
	pseudo_instr1(103, 1)
	get_x_value(0, 1)
	proceed
end('get_open_streams'/1):



'$broadcast'/1:


$1:
	pseudo_instr1(104, 0)
	proceed
end('$broadcast'/1):



'random'/1:


$1:
	pseudo_instr1(105, 1)
	get_x_value(0, 1)
	proceed
end('random'/1):



'$initial_goal'/1:


$1:
	pseudo_instr1(106, 1)
	get_x_value(0, 1)
	proceed
end('$initial_goal'/1):



'$make_cleanup_cp'/1:


$1:
	pseudo_instr1(107, 1)
	get_x_value(0, 1)
	proceed
end('$make_cleanup_cp'/1):



'string'/1:


$1:
	pseudo_instr1(108, 0)
	proceed
end('string'/1):



'$thread_wait_free_ptr'/1:


$1:
	pseudo_instr1(109, 0)
	proceed
end('$thread_wait_free_ptr'/1):



'$thread_wait_ptr'/1:


$1:
	pseudo_instr1(110, 0)
	proceed
end('$thread_wait_ptr'/1):



'$thread_wait_update'/1:


$1:
	pseudo_instr1(111, 0)
	proceed
end('$thread_wait_update'/1):



'delete_timer'/1:


$1:
	pseudo_instr1(112, 0)
	proceed
end('delete_timer'/1):



'gettimeofday'/1:


$1:
	pseudo_instr1(113, 1)
	get_x_value(0, 1)
	proceed
end('gettimeofday'/1):



'$schedule_threads_now'/1:


$1:
	pseudo_instr1(114, 0)
	proceed
end('$schedule_threads_now'/1):



'set_default_message_thread'/1:


$1:
	pseudo_instr1(115, 0)
	proceed
end('set_default_message_thread'/1):



'default_message_thread'/1:


$1:
	pseudo_instr1(116, 1)
	get_x_value(0, 1)
	proceed
end('default_message_thread'/1):



'$re_free'/1:


$1:
	pseudo_instr1(117, 0)
	proceed
end('$re_free'/1):



'is'/2:


$1:
	pseudo_instr2(0, 2, 1)
	get_x_value(0, 2)
	proceed
end('is'/2):



'<'/2:


$1:
	pseudo_instr2(1, 0, 1)
	proceed
end('<'/2):



'=<'/2:


$1:
	pseudo_instr2(2, 0, 1)
	proceed
end('=<'/2):



'ip_set'/2:


$1:
	pseudo_instr2(3, 0, 1)
	proceed
end('ip_set'/2):



'ip_lookup'/2:


$1:
	pseudo_instr2(4, 0, 2)
	get_x_value(1, 2)
	proceed
end('ip_lookup'/2):



'$get_char'/2:


$1:
	pseudo_instr2(5, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_char'/2):



'$put_char'/2:


$1:
	pseudo_instr2(6, 0, 1)
	proceed
end('$put_char'/2):



'$get_code'/2:


$1:
	pseudo_instr2(7, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_code'/2):



'$put_code'/2:


$1:
	pseudo_instr2(8, 0, 1)
	proceed
end('$put_code'/2):



'$compare_pointers'/2:


$1:
	pseudo_instr2(9, 0, 1)
	proceed
end('$compare_pointers'/2):



'$set_flag'/2:


$1:
	pseudo_instr2(10, 0, 1)
	proceed
end('$set_flag'/2):



'$get_flag'/2:


$1:
	pseudo_instr2(11, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_flag'/2):



'$copy_term_from_buffer'/2:


$1:
	pseudo_instr2(12, 0, 2)
	get_x_value(1, 2)
	proceed
end('$copy_term_from_buffer'/2):



'$stat_atom'/2:


$1:
	pseudo_instr2(13, 2, 3)
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed
end('$stat_atom'/2):



'$stat_predicate'/2:


$1:
	pseudo_instr2(14, 2, 3)
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed
end('$stat_predicate'/2):



'$stat_name'/2:


$1:
	pseudo_instr2(15, 0, 2)
	get_x_value(1, 2)
	proceed
end('$stat_name'/2):



'$psi_write_atom'/2:


$1:
	pseudo_instr2(16, 0, 1)
	proceed
end('$psi_write_atom'/2):



'$psi_writeq_atom'/2:


$1:
	pseudo_instr2(17, 0, 1)
	proceed
end('$psi_writeq_atom'/2):



'$write_integer'/2:


$1:
	pseudo_instr2(18, 0, 1)
	proceed
end('$write_integer'/2):



'$write_var'/2:


$1:
	pseudo_instr2(19, 0, 1)
	proceed
end('$write_var'/2):



'$writeR_var'/2:


$1:
	pseudo_instr2(20, 0, 1)
	proceed
end('$writeR_var'/2):



'$write_obvar'/2:


$1:
	pseudo_instr2(21, 0, 1)
	proceed
end('$write_obvar'/2):



'$writeR_obvar'/2:


$1:
	pseudo_instr2(22, 0, 1)
	proceed
end('$writeR_obvar'/2):



'$writeq_obvar'/2:


$1:
	pseudo_instr2(23, 0, 1)
	proceed
end('$writeq_obvar'/2):



'$get_substitution'/2:


$1:
	pseudo_instr2(24, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_substitution'/2):



'sub_term'/2:


$1:
	pseudo_instr2(25, 0, 2)
	get_x_value(1, 2)
	proceed
end('sub_term'/2):



'$next_sub'/2:


$1:
	pseudo_instr2(26, 0, 2)
	get_x_value(1, 2)
	proceed
end('$next_sub'/2):



'$sub_table_size'/2:


$1:
	pseudo_instr2(27, 0, 2)
	get_x_value(1, 2)
	proceed
end('$sub_table_size'/2):



'$compress_sub_object_variable'/2:


$1:
	pseudo_instr2(28, 0, 2)
	get_x_value(1, 2)
	proceed
end('$compress_sub_object_variable'/2):



'$reset_entry'/2:


$1:
	pseudo_instr2(29, 0, 1)
	proceed
end('$reset_entry'/2):



'atom_length'/2:


$1:
	pseudo_instr2(30, 0, 2)
	get_x_value(1, 2)
	proceed
end('atom_length'/2):



'concat_atom'/2:


$1:
	pseudo_instr2(31, 0, 2)
	get_x_value(1, 2)
	proceed
end('concat_atom'/2):



'$atom_codes'/2:


$1:
	pseudo_instr2(32, 0, 2)
	get_x_value(1, 2)
	proceed
end('$atom_codes'/2):



'$codes_atom'/2:


$1:
	pseudo_instr2(33, 0, 2)
	get_x_value(1, 2)
	proceed
end('$codes_atom'/2):



'$char_code'/2:


$1:
	pseudo_instr2(34, 0, 2)
	get_x_value(1, 2)
	proceed
end('$char_code'/2):



'$code_char'/2:


$1:
	pseudo_instr2(35, 0, 2)
	get_x_value(1, 2)
	proceed
end('$code_char'/2):



'$hash_double'/2:


$1:
	pseudo_instr2(36, 0, 2)
	get_x_value(1, 2)
	proceed
end('$hash_double'/2):



'hash_table_remove'/2:


$1:
	pseudo_instr2(37, 0, 1)
	proceed
end('hash_table_remove'/2):



'$number_codes'/2:


$1:
	pseudo_instr2(38, 0, 2)
	get_x_value(1, 2)
	proceed
end('$number_codes'/2):



'$codes_number'/2:


$1:
	pseudo_instr2(39, 0, 2)
	get_x_value(1, 2)
	proceed
end('$codes_number'/2):



'$close'/2:


$1:
	pseudo_instr2(40, 0, 1)
	proceed
end('$close'/2):



'$stream_position'/2:


$1:
	pseudo_instr2(41, 0, 2)
	get_x_value(1, 2)
	proceed
end('$stream_position'/2):



'$set_stream_position'/2:


$1:
	pseudo_instr2(42, 0, 1)
	proceed
end('$set_stream_position'/2):



'$line_number'/2:


$1:
	pseudo_instr2(43, 0, 2)
	get_x_value(1, 2)
	proceed
end('$line_number'/2):



'$stream_to_chars'/2:


$1:
	pseudo_instr2(44, 0, 2)
	get_x_value(1, 2)
	proceed
end('$stream_to_chars'/2):



'$stream_to_atom'/2:


$1:
	pseudo_instr2(45, 0, 2)
	get_x_value(1, 2)
	proceed
end('$stream_to_atom'/2):



'$system'/2:


$1:
	pseudo_instr2(46, 0, 2)
	get_x_value(1, 2)
	proceed
end('$system'/2):



'$mktemp'/2:


$1:
	pseudo_instr2(47, 0, 2)
	get_x_value(1, 2)
	proceed
end('$mktemp'/2):



'$delay'/2:


$1:
	pseudo_instr2(48, 0, 1)
	proceed
end('$delay'/2):



'$delayed_problems_for_var'/2:


$1:
	pseudo_instr2(49, 0, 2)
	get_x_value(1, 2)
	proceed
end('$delayed_problems_for_var'/2):



'$get_bound_structure'/2:


$1:
	pseudo_instr2(50, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_bound_structure'/2):



'not_free_in'/2:


$1:
	pseudo_instr2(51, 0, 1)
	proceed
end('not_free_in'/2):



'$not_free_in_var_simplify'/2:


$1:
	pseudo_instr2(52, 0, 1)
	proceed
end('$not_free_in_var_simplify'/2):



'is_distinct'/2:


$1:
	pseudo_instr2(53, 0, 1)
	proceed
end('is_distinct'/2):



'get_distinct'/2:


$1:
	pseudo_instr2(54, 0, 2)
	get_x_value(1, 2)
	proceed
end('get_distinct'/2):



'$object_variable_name_to_prefix'/2:


$1:
	pseudo_instr2(55, 0, 2)
	get_x_value(1, 2)
	proceed
end('$object_variable_name_to_prefix'/2):



'$readR_var'/2:


$1:
	pseudo_instr2(56, 2, 1)
	get_x_value(0, 2)
	proceed
end('$readR_var'/2):



'$readR_obvar'/2:


$1:
	pseudo_instr2(57, 2, 1)
	get_x_value(0, 2)
	proceed
end('$readR_obvar'/2):



'quantifier'/2:


$1:
	pseudo_instr2(58, 0, 2)
	get_x_value(1, 2)
	proceed
end('quantifier'/2):



'bound_var'/2:


$1:
	pseudo_instr2(59, 0, 2)
	get_x_value(1, 2)
	proceed
end('bound_var'/2):



'body'/2:


$1:
	pseudo_instr2(60, 0, 2)
	get_x_value(1, 2)
	proceed
end('body'/2):



'check_binder'/2:


$1:
	pseudo_instr2(61, 0, 1)
	proceed
end('check_binder'/2):



'get_var_name'/2:


$1:
	pseudo_instr2(62, 0, 2)
	get_x_value(1, 2)
	proceed
end('get_var_name'/2):



'set_var_name'/2:


$1:
	pseudo_instr2(63, 0, 1)
	proceed
end('set_var_name'/2):



'set_obvar_name'/2:


$1:
	pseudo_instr2(64, 0, 1)
	proceed
end('set_obvar_name'/2):



'freeze_term'/2:


$1:
	pseudo_instr2(65, 0, 2)
	get_x_value(1, 2)
	proceed
end('freeze_term'/2):



'thaw_term'/2:


$1:
	pseudo_instr2(66, 0, 2)
	get_x_value(1, 2)
	proceed
end('thaw_term'/2):



'collect_vars'/2:


$1:
	pseudo_instr2(67, 0, 2)
	get_x_value(1, 2)
	proceed
end('collect_vars'/2):



'$call_predicate1'/2:


$1:
	pseudo_instr2(68, 0, 1)
	proceed
end('$call_predicate1'/2):



'$increment'/2:


$1:
	pseudo_instr2(69, 0, 2)
	get_x_value(1, 2)
	proceed
end('$increment'/2):



'$decrement'/2:


$1:
	pseudo_instr2(70, 0, 2)
	get_x_value(1, 2)
	proceed
end('$decrement'/2):



'name_vars'/2:


$1:
	pseudo_instr2(71, 0, 2)
	get_x_value(1, 2)
	proceed
end('name_vars'/2):



'get_unnamed_vars'/2:


$1:
	pseudo_instr2(72, 0, 2)
	get_x_value(1, 2)
	proceed
end('get_unnamed_vars'/2):



'global_state_lookup'/2:


$1:
	pseudo_instr2(73, 0, 2)
	get_x_value(1, 2)
	proceed
end('global_state_lookup'/2):



'global_state_set'/2:


$1:
	pseudo_instr2(74, 0, 1)
	proceed
end('global_state_set'/2):



'global_state_increment'/2:


$1:
	pseudo_instr2(75, 0, 2)
	get_x_value(1, 2)
	proceed
end('global_state_increment'/2):



'global_state_decrement'/2:


$1:
	pseudo_instr2(76, 0, 2)
	get_x_value(1, 2)
	proceed
end('global_state_decrement'/2):



'$get_dynamic_chain'/2:


$1:
	pseudo_instr2(77, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_dynamic_chain'/2):



'$thread_goal'/2:


$1:
	pseudo_instr2(78, 0, 2)
	get_x_value(1, 2)
	proceed
end('$thread_goal'/2):



'tcp_host_to_ip_address'/2:


$1:
	pseudo_instr2(79, 0, 2)
	get_x_value(1, 2)
	proceed
end('tcp_host_to_ip_address'/2):



'tcp_host_from_ip_address'/2:


$1:
	pseudo_instr2(80, 2, 1)
	get_x_value(0, 2)
	proceed
end('tcp_host_from_ip_address'/2):



'$local_p2p'/2:


$1:
	pseudo_instr2(81, 0, 1)
	proceed
end('$local_p2p'/2):



'$thread_symbol'/2:


$1:
	pseudo_instr2(82, 0, 1)
	proceed
end('$thread_symbol'/2):



'$load'/2:


$1:
	pseudo_instr2(83, 0, 2)
	get_x_value(1, 2)
	proceed
end('$load'/2):



'is_free_in'/2:


$1:
	pseudo_instr2(84, 0, 1)
	proceed
end('is_free_in'/2):



'pipe'/2:


$1:
	pseudo_instr2(85, 2, 3)
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed
end('pipe'/2):



'getenv'/2:


$1:
	pseudo_instr2(86, 0, 2)
	get_x_value(1, 2)
	proceed
end('getenv'/2):



'putenv'/2:


$1:
	pseudo_instr2(87, 0, 1)
	proceed
end('putenv'/2):



'signal_to_atom'/2:


$1:
	pseudo_instr2(88, 0, 2)
	get_x_value(1, 2)
	proceed
end('signal_to_atom'/2):



'strerror'/2:


$1:
	pseudo_instr2(89, 0, 2)
	get_x_value(1, 2)
	proceed
end('strerror'/2):



'$psi_socket_fd'/2:


$1:
	pseudo_instr2(90, 0, 2)
	get_x_value(1, 2)
	proceed
end('$psi_socket_fd'/2):



'$pedro_unsubscribe'/2:


$1:
	pseudo_instr2(91, 0, 1)
	proceed
end('$pedro_unsubscribe'/2):



'uncurry'/2:


$1:
	pseudo_instr2(92, 0, 2)
	get_x_value(1, 2)
	proceed
end('uncurry'/2):



'$get_line'/2:


$1:
	pseudo_instr2(93, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_line'/2):



'ip_array_init'/2:


$1:
	pseudo_instr2(94, 0, 1)
	proceed
end('ip_array_init'/2):



'copy_term'/2:


$1:
	pseudo_instr2(95, 0, 2)
	get_x_value(1, 2)
	proceed
end('copy_term'/2):



'$buffer_set_domains_apart'/2:


$1:
	pseudo_instr2(96, 0, 1)
	proceed
end('$buffer_set_domains_apart'/2):



'$copy_substitution'/2:


$1:
	pseudo_instr2(97, 0, 2)
	get_x_value(1, 2)
	proceed
end('$copy_substitution'/2):



'$copy_obvar_to_buffer_tail'/2:


$1:
	pseudo_instr2(98, 0, 1)
	proceed
end('$copy_obvar_to_buffer_tail'/2):



'$stat_ip_table'/2:


$1:
	pseudo_instr2(99, 0, 2)
	get_x_value(1, 2)
	proceed
end('$stat_ip_table'/2):



'$set_stream_properties'/2:


$1:
	pseudo_instr2(100, 0, 1)
	proceed
end('$set_stream_properties'/2):



'$get_stream_properties'/2:


$1:
	pseudo_instr2(101, 0, 2)
	get_x_value(1, 2)
	proceed
end('$get_stream_properties'/2):



'set_std_stream'/2:


$1:
	pseudo_instr2(102, 0, 1)
	proceed
end('set_std_stream'/2):



'thread_push_goal'/2:


$1:
	pseudo_instr2(103, 0, 1)
	proceed
end('thread_push_goal'/2):



'structural_unify'/2:


$1:
	pseudo_instr2(104, 0, 1)
	proceed
end('structural_unify'/2):



'$not_free_in_nfi_simp'/2:


$1:
	pseudo_instr2(105, 0, 1)
	proceed
end('$not_free_in_nfi_simp'/2):



'$require_nfi_simp'/2:


$1:
	pseudo_instr2(106, 0, 1)
	proceed
end('$require_nfi_simp'/2):



'$fast_simplify'/2:


$1:
	pseudo_instr2(107, 0, 2)
	get_x_value(1, 2)
	proceed
end('$fast_simplify'/2):



'gmtime'/2:


$1:
	pseudo_instr2(108, 0, 1)
	proceed
end('gmtime'/2):



'localtime'/2:


$1:
	pseudo_instr2(109, 0, 1)
	proceed
end('localtime'/2):



'=='/2:


$1:
	pseudo_instr2(110, 0, 1)
	proceed
end('=='/2):



'simplify_term'/2:


$1:
	pseudo_instr2(111, 0, 2)
	get_x_value(1, 2)
	proceed
end('simplify_term'/2):



'is_not_free_in'/2:


$1:
	pseudo_instr2(112, 0, 1)
	proceed
end('is_not_free_in'/2):



'$put_line'/2:


$1:
	pseudo_instr2(113, 0, 1)
	proceed
end('$put_line'/2):



'ip_array_get_entries'/2:


$1:
	pseudo_instr2(114, 0, 2)
	get_x_value(1, 2)
	proceed
end('ip_array_get_entries'/2):



'$write_float'/2:


$1:
	pseudo_instr2(115, 0, 1)
	proceed
end('$write_float'/2):



'select'/2:


$1:
	pseudo_instr2(116, 0, 2)
	get_x_value(1, 2)
	proceed
end('select'/2):



'$write_string'/2:


$1:
	pseudo_instr2(117, 0, 1)
	proceed
end('$write_string'/2):



'$writeq_string'/2:


$1:
	pseudo_instr2(118, 0, 1)
	proceed
end('$writeq_string'/2):



'string_length'/2:


$1:
	pseudo_instr2(119, 0, 2)
	get_x_value(1, 2)
	proceed
end('string_length'/2):



'$stream_to_string'/2:


$1:
	pseudo_instr2(120, 0, 2)
	get_x_value(1, 2)
	proceed
end('$stream_to_string'/2):



'$list_to_string'/2:


$1:
	pseudo_instr2(121, 0, 2)
	get_x_value(1, 2)
	proceed
end('$list_to_string'/2):



'$string_to_atom'/2:


$1:
	pseudo_instr2(122, 0, 2)
	get_x_value(1, 2)
	proceed
end('$string_to_atom'/2):



'$atom_to_string'/2:


$1:
	pseudo_instr2(123, 0, 2)
	get_x_value(1, 2)
	proceed
end('$atom_to_string'/2):



'$pedro_connect'/2:


$1:
	pseudo_instr2(124, 0, 1)
	proceed
end('$pedro_connect'/2):



'$pedro_subscribe'/2:


$1:
	pseudo_instr2(125, 0, 2)
	get_x_value(1, 2)
	proceed
end('$pedro_subscribe'/2):



'hash_variable'/2:


$1:
	pseudo_instr2(126, 0, 2)
	get_x_value(1, 2)
	proceed
end('hash_variable'/2):



'stat'/2:


$1:
	pseudo_instr2(127, 0, 2)
	get_x_value(1, 2)
	proceed
end('stat'/2):



'$thread_wait_extract_preds'/2:


$1:
	pseudo_instr2(128, 0, 2)
	get_x_value(1, 2)
	proceed
end('$thread_wait_extract_preds'/2):



'absolute_file_name'/2:


$1:
	pseudo_instr2(129, 0, 2)
	get_x_value(1, 2)
	proceed
end('absolute_file_name'/2):



'@<'/2:


$1:
	pseudo_instr2(130, 0, 1)
	proceed
end('@<'/2):



'@='/2:


$1:
	pseudo_instr2(131, 0, 1)
	proceed
end('@='/2):



'@>'/2:


$1:
	pseudo_instr2(132, 0, 1)
	proceed
end('@>'/2):



'\\='/2:


$1:
	pseudo_instr2(133, 0, 1)
	proceed
end('\\='/2):



'$string_to_list'/2:


$1:
	pseudo_instr2(134, 0, 2)
	get_x_value(1, 2)
	proceed
end('$string_to_list'/2):



'$peek'/2:


$1:
	pseudo_instr2(135, 0, 2)
	get_x_value(1, 2)
	proceed
end('$peek'/2):



'$hash_string'/2:


$1:
	pseudo_instr2(136, 0, 2)
	get_x_value(1, 2)
	proceed
end('$hash_string'/2):



'$re_compile'/2:


$1:
	pseudo_instr2(137, 0, 2)
	get_x_value(1, 2)
	proceed
end('$re_compile'/2):



'file_directory_name'/2:


$1:
	pseudo_instr2(138, 0, 2)
	get_x_value(1, 2)
	proceed
end('file_directory_name'/2):



'file_base_name'/2:


$1:
	pseudo_instr2(139, 0, 2)
	get_x_value(1, 2)
	proceed
end('file_base_name'/2):



'functor'/3:


$1:
	pseudo_instr3(0, 0, 1, 2)
	proceed
end('functor'/3):



'arg'/3:


$1:
	pseudo_instr3(1, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('arg'/3):



'$add'/3:


$1:
	pseudo_instr3(2, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$add'/3):



'$subtract'/3:


$1:
	pseudo_instr3(3, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$subtract'/3):



'$compare_var'/3:


$1:
	pseudo_instr3(4, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$compare_var'/3):



'$compare_atom'/3:


$1:
	pseudo_instr3(5, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$compare_atom'/3):



'$fast_equal'/3:


$1:
	pseudo_instr3(6, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$fast_equal'/3):



'$stat_choice'/3:


$1:
	pseudo_instr3(7, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$stat_choice'/3):



'$stat_global'/3:


$1:
	pseudo_instr3(8, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$stat_global'/3):



'$stat_local'/3:


$1:
	pseudo_instr3(9, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$stat_local'/3):



'$stat_binding_trail'/3:


$1:
	pseudo_instr3(10, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$stat_binding_trail'/3):



'$stat_code'/3:


$1:
	pseudo_instr3(11, 3, 4, 5)
	get_x_value(0, 3)
	get_x_value(1, 4)
	get_x_value(2, 5)
	proceed
end('$stat_code'/3):



'$stat_string'/3:


$1:
	pseudo_instr3(12, 3, 4, 5)
	get_x_value(0, 3)
	get_x_value(1, 4)
	get_x_value(2, 5)
	proceed
end('$stat_string'/3):



'random'/3:


$1:
	pseudo_instr3(13, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('random'/3):



'$string_concat'/3:


$1:
	pseudo_instr3(14, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$string_concat'/3):



'$set_domain'/3:


$1:
	pseudo_instr3(15, 0, 1, 2)
	proceed
end('$set_domain'/3):



'$set_range'/3:


$1:
	pseudo_instr3(16, 0, 1, 2)
	proceed
end('$set_range'/3):



'$get_domain'/3:


$1:
	pseudo_instr3(17, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$get_domain'/3):



'$get_range'/3:


$1:
	pseudo_instr3(18, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$get_range'/3):



'$build_sub_term'/3:


$1:
	pseudo_instr3(19, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$build_sub_term'/3):



'$get_opcode'/3:


$1:
	pseudo_instr3(20, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_opcode'/3):



'$get_const'/3:


$1:
	pseudo_instr3(21, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_const'/3):



'$get_number'/3:


$1:
	pseudo_instr3(22, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_number'/3):



'$get_address'/3:


$1:
	pseudo_instr3(23, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_address'/3):



'$get_offset'/3:


$1:
	pseudo_instr3(24, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_offset'/3):



'$get_pred'/3:


$1:
	pseudo_instr3(25, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_pred'/3):



'$get_entry'/3:


$1:
	pseudo_instr3(26, 3, 1, 4)
	get_x_value(0, 3)
	get_x_value(2, 4)
	proceed
end('$get_entry'/3):



'$copy_to_buffer_tail'/3:


$1:
	pseudo_instr3(27, 0, 1, 2)
	proceed
end('$copy_to_buffer_tail'/3):



'concat_atom'/3:


$1:
	pseudo_instr3(28, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('concat_atom'/3):



'hash_table_lookup'/3:


$1:
	pseudo_instr3(29, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('hash_table_lookup'/3):



'$hash_table_search'/3:


$1:
	pseudo_instr3(30, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$hash_table_search'/3):



'$open'/3:


$1:
	pseudo_instr3(31, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$open'/3):



'$get_atom_from_atom_table'/3:


$1:
	pseudo_instr3(32, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$get_atom_from_atom_table'/3):



'$symtype'/3:


$1:
	pseudo_instr3(33, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$symtype'/3):



'$access'/3:


$1:
	pseudo_instr3(34, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$access'/3):



'$read_next_token'/3:


$1:
	pseudo_instr3(35, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$read_next_token'/3):



'$encoded_write'/3:


$1:
	pseudo_instr3(36, 0, 1, 2)
	proceed
end('$encoded_write'/3):



'$call_predicate2'/3:


$1:
	pseudo_instr3(37, 0, 1, 2)
	proceed
end('$call_predicate2'/3):



'$put_structure'/3:


$1:
	pseudo_instr3(38, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$put_structure'/3):



'$set_argument'/3:


$1:
	pseudo_instr3(39, 0, 1, 2)
	proceed
end('$set_argument'/3):



'ip_set'/3:


$1:
	pseudo_instr3(40, 0, 1, 2)
	proceed
end('ip_set'/3):



'ip_lookup'/3:


$1:
	pseudo_instr3(41, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('ip_lookup'/3):



'$ipc_next'/3:


$1:
	pseudo_instr3(42, 0, 3, 2)
	get_x_value(1, 3)
	proceed
end('$ipc_next'/3):



'tcp_socket'/3:


$1:
	pseudo_instr3(43, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('tcp_socket'/3):



'tcp_setsockopt'/3:


$1:
	pseudo_instr3(44, 0, 1, 2)
	proceed
end('tcp_setsockopt'/3):



'tcp_getsockopt'/3:


$1:
	pseudo_instr3(45, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('tcp_getsockopt'/3):



'tcp_bind'/3:


$1:
	pseudo_instr3(46, 0, 1, 2)
	proceed
end('tcp_bind'/3):



'$tcp_connect1'/3:


$1:
	pseudo_instr3(47, 0, 1, 2)
	proceed
end('$tcp_connect1'/3):



'$open_socket_stream'/3:


$1:
	pseudo_instr3(48, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$open_socket_stream'/3):



'$open_msgstream'/3:


$1:
	pseudo_instr3(49, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$open_msgstream'/3):



'tcp_getsockname'/3:


$1:
	pseudo_instr3(50, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('tcp_getsockname'/3):



'tcp_getpeername'/3:


$1:
	pseudo_instr3(51, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('tcp_getpeername'/3):



'$tcp_service_to_proto_port'/3:


$1:
	pseudo_instr3(52, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$tcp_service_to_proto_port'/3):



'$tcp_service_proto_to_port'/3:


$1:
	pseudo_instr3(53, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$tcp_service_proto_to_port'/3):



'$tcp_service_from_proto_port'/3:


$1:
	pseudo_instr3(54, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$tcp_service_from_proto_port'/3):



'$tcp_service_proto_from_port'/3:


$1:
	pseudo_instr3(55, 3, 4, 2)
	get_x_value(0, 3)
	get_x_value(1, 4)
	proceed
end('$tcp_service_proto_from_port'/3):



'ip_lookup_default'/3:


$1:
	pseudo_instr3(56, 0, 3, 2)
	get_x_value(1, 3)
	proceed
end('ip_lookup_default'/3):



'$psi_decompile'/3:


$1:
	pseudo_instr3(57, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$psi_decompile'/3):



'$make_sub_from_buffer'/3:


$1:
	pseudo_instr3(58, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$make_sub_from_buffer'/3):



'$stat_other_trail'/3:


$1:
	pseudo_instr3(59, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$stat_other_trail'/3):



'simplify_term'/3:


$1:
	pseudo_instr3(60, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('simplify_term'/3):



'$get_double'/3:


$1:
	pseudo_instr3(61, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_double'/3):



'$stat_scratchpad'/3:


$1:
	pseudo_instr3(62, 0, 3, 4)
	get_x_value(1, 3)
	get_x_value(2, 4)
	proceed
end('$stat_scratchpad'/3):



'$get_delays$'/3:


$1:
	pseudo_instr3(63, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_delays$'/3):



'atom_concat2'/3:


$1:
	pseudo_instr3(64, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('atom_concat2'/3):



'hash_table_insert'/3:


$1:
	pseudo_instr3(65, 0, 1, 2)
	proceed
end('hash_table_insert'/3):



'$predicate_stamp'/3:


$1:
	pseudo_instr3(66, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$predicate_stamp'/3):



'$get_integer'/3:


$1:
	pseudo_instr3(67, 3, 1, 2)
	get_x_value(0, 3)
	proceed
end('$get_integer'/3):



'$ipc_first'/3:


$1:
	pseudo_instr3(68, 0, 1, 3)
	get_x_value(2, 3)
	proceed
end('$ipc_first'/3):



'setarg'/3:


$1:
	pseudo_instr3(69, 0, 1, 2)
	proceed
end('setarg'/3):



'$psi_dynamic'/4:


$1:
	pseudo_instr4(0, 0, 1, 2, 3)
	proceed
end('$psi_dynamic'/4):



'atom_search'/4:


$1:
	pseudo_instr4(1, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('atom_search'/4):



'$sub_atom'/4:


$1:
	pseudo_instr4(2, 0, 1, 2, 3)
	proceed
end('$sub_atom'/4):



'$load_foreign'/4:


$1:
	pseudo_instr4(3, 0, 1, 2, 3)
	proceed
end('$load_foreign'/4):



'$open_string'/4:


$1:
	pseudo_instr4(4, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('$open_string'/4):



'$get_pred_from_pred_table'/4:


$1:
	pseudo_instr4(5, 0, 4, 5, 6)
	get_x_value(1, 4)
	get_x_value(2, 5)
	get_x_value(3, 6)
	proceed
end('$get_pred_from_pred_table'/4):



'$encoded_read'/4:


$1:
	pseudo_instr4(6, 0, 4, 5, 3)
	get_x_value(1, 4)
	get_x_value(2, 5)
	proceed
end('$encoded_read'/4):



'quantify'/4:


$1:
	pseudo_instr4(7, 0, 1, 2, 3)
	proceed
end('quantify'/4):



'$call_predicate3'/4:


$1:
	pseudo_instr4(8, 0, 1, 2, 3)
	proceed
end('$call_predicate3'/4):



'tcp_accept'/4:


$1:
	pseudo_instr4(9, 0, 4, 5, 6)
	get_x_value(1, 4)
	get_x_value(2, 5)
	get_x_value(3, 6)
	proceed
end('tcp_accept'/4):



'$psi_next_instr'/4:


$1:
	pseudo_instr4(10, 0, 1, 4, 5)
	get_x_value(2, 4)
	get_x_value(3, 5)
	proceed
end('$psi_next_instr'/4):



'$psi_assert'/4:


$1:
	pseudo_instr4(11, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('$psi_assert'/4):



'$ccompile'/4:


$1:
	pseudo_instr4(12, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('$ccompile'/4):



'$set_domains_apart'/4:


$1:
	pseudo_instr4(13, 0, 1, 2, 3)
	proceed
end('$set_domains_apart'/4):



'$new_sub'/4:


$1:
	pseudo_instr4(14, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('$new_sub'/4):



'$get_first_clause'/4:


$1:
	pseudo_instr4(15, 0, 1, 4, 5)
	get_x_value(2, 4)
	get_x_value(3, 5)
	proceed
end('$get_first_clause'/4):



'$get_next_clause'/4:


$1:
	pseudo_instr4(16, 0, 1, 4, 5)
	get_x_value(2, 4)
	get_x_value(3, 5)
	proceed
end('$get_next_clause'/4):



'$split_string'/4:


$1:
	pseudo_instr4(17, 0, 1, 4, 5)
	get_x_value(2, 4)
	get_x_value(3, 5)
	proceed
end('$split_string'/4):



'$ipc_get_message'/4:


$1:
	pseudo_instr4(18, 4, 1, 5, 3)
	get_x_value(0, 4)
	get_x_value(2, 5)
	proceed
end('$ipc_get_message'/4):



'ip_lookup_default'/4:


$1:
	pseudo_instr4(19, 0, 1, 4, 3)
	get_x_value(2, 4)
	proceed
end('ip_lookup_default'/4):



'$thread_fork'/4:


$1:
	pseudo_instr4(20, 0, 1, 2, 3)
	proceed
end('$thread_fork'/4):



'$thread_setup_wait'/4:


$1:
	pseudo_instr4(21, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('$thread_setup_wait'/4):



'create_timer'/4:


$1:
	pseudo_instr4(22, 0, 1, 2, 4)
	get_x_value(3, 4)
	proceed
end('create_timer'/4):



'$call_predicate4'/5:


$1:
	pseudo_instr5(0, 0, 1, 2, 3, 4)
	proceed
end('$call_predicate4'/5):



'$re_match'/5:


$1:
	pseudo_instr5(1, 0, 1, 5, 6, 4)
	get_x_value(2, 5)
	get_x_value(3, 6)
	proceed
end('$re_match'/5):



