'$psi_general_exception_handler'/5:

	switch_on_term(0, $13, 'fail', 'fail', 'fail', 'fail', $12)

$12:
	switch_on_constant(0, 32, ['$default':'fail', 0:$1, 1:$2, 2:$3, 3:$4, 4:$5, 5:$6, 6:$7, 7:$8, 8:$9, 9:$10, 10:$11])

$13:
	try(5, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	trust($11)

$1:
	get_integer(0, 0)
	get_x_value(3, 4)
	proceed

$2:
	get_integer(1, 0)
	get_x_variable(5, 1)
	get_x_variable(0, 3)
	get_structure('instantiation_exception', 3, 4)
	unify_x_variable(1)
	unify_x_value(5)
	unify_x_value(2)
	execute_predicate('$psi_call_to_call', 2)

$3:
	get_integer(2, 0)
	allocate(6)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(5, 3)
	get_y_variable(2, 4)
	put_y_value(3, 0)
	get_list(0)
	unify_x_variable(0)
	unify_void(1)
	pseudo_instr3(1, 24, 0, 1)
	get_x_variable(0, 1)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	call_predicate('$template_to_type', 2, 6)
	put_y_value(5, 0)
	put_y_value(0, 1)
	call_predicate('$psi_call_to_call', 2, 5)
	put_y_value(2, 0)
	get_structure('type_exception', 4, 0)
	unify_y_value(0)
	unify_y_value(4)
	unify_y_value(3)
	unify_y_value(1)
	deallocate
	proceed

$4:
	get_integer(3, 0)
	get_x_variable(5, 1)
	get_x_variable(0, 3)
	get_structure('exception', 1, 4)
	unify_x_ref(1)
	get_structure('range_error', 5, 1)
	unify_constant('unrecoverable')
	unify_x_variable(1)
	unify_constant('default')
	unify_x_value(5)
	unify_constant('(see manual)')
	execute_predicate('$psi_call_to_call', 2)

$5:
	get_integer(4, 0)
	get_x_variable(5, 1)
	get_x_variable(0, 3)
	get_structure('exception', 1, 4)
	unify_x_ref(1)
	get_structure('value_error', 4, 1)
	unify_constant('unrecoverable')
	unify_x_variable(1)
	unify_constant('default')
	unify_x_value(5)
	execute_predicate('$psi_call_to_call', 2)

$6:
	get_integer(5, 0)
	get_x_variable(1, 3)
	get_structure('exception', 1, 4)
	unify_x_ref(0)
	get_structure('zero_divide', 3, 0)
	unify_constant('unrecoverable')
	unify_x_value(1)
	unify_constant('default')
	put_x_variable(0, 0)
	execute_predicate('$psi_call_to_call', 2)

$7:
	get_integer(6, 0)
	get_x_variable(0, 3)
	get_structure('exception', 1, 4)
	unify_x_ref(1)
	get_structure('permission_error', 3, 1)
	unify_constant('unrecoverable')
	unify_x_variable(1)
	unify_constant('(see manual)')
	execute_predicate('$psi_call_to_call', 2)

$8:
	get_integer(7, 0)
	get_x_variable(5, 1)
	get_x_variable(0, 3)
	get_structure('exception', 1, 4)
	unify_x_ref(1)
	get_structure('allocation_failure_error', 5, 1)
	unify_constant('unrecoverable')
	unify_x_variable(1)
	unify_constant('default')
	unify_x_value(5)
	allocate(2)
	unify_y_variable(1)
	get_list(2)
	unify_x_variable(2)
	unify_void(1)
	pseudo_instr3(1, 5, 2, 3)
	get_y_variable(0, 3)
	call_predicate('$psi_call_to_call', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$template_to_type', 2)

$9:
	get_integer(8, 0)
	get_x_variable(0, 3)
	get_structure('exception', 1, 4)
	unify_x_ref(1)
	get_structure('system_call_error', 4, 1)
	unify_constant('unrecoverable')
	unify_x_variable(1)
	unify_constant('default')
	allocate(1)
	unify_y_variable(0)
	call_predicate('$psi_call_to_call', 2, 1)
	pseudo_instr1(77, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$10:
	get_integer(9, 0)
	get_structure('exception', 1, 4)
	unify_x_ref(0)
	get_structure('unimplemented_error', 3, 0)
	unify_constant('warning')
	unify_x_value(3)
	unify_constant('default')
	proceed

$11:
	get_integer(10, 0)
	get_structure('exception', 1, 4)
	unify_x_ref(0)
	get_structure('unsupported_error', 3, 0)
	unify_constant('warning')
	unify_x_value(3)
	unify_constant('default')
	proceed
end('$psi_general_exception_handler'/5):



'$psi0_general_exception_handler'/6:


$1:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	execute_predicate('$psi_general_exception_handler', 5)
end('$psi0_general_exception_handler'/6):



'$psi1_general_exception_handler'/7:


$1:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 6)
	execute_predicate('$psi_general_exception_handler', 5)
end('$psi1_general_exception_handler'/7):



'$psi2_general_exception_handler'/8:


$1:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 7)
	execute_predicate('$psi_general_exception_handler', 5)
end('$psi2_general_exception_handler'/8):



'$psi3_general_exception_handler'/9:


$1:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 8)
	execute_predicate('$psi_general_exception_handler', 5)
end('$psi3_general_exception_handler'/9):



'$psi4_general_exception_handler'/10:


$1:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 9)
	execute_predicate('$psi_general_exception_handler', 5)
end('$psi4_general_exception_handler'/10):



'$psi5_general_exception_handler'/11:


$1:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 10)
	execute_predicate('$psi_general_exception_handler', 5)
end('$psi5_general_exception_handler'/11):



'$psi_error_to_atom'/2:

	switch_on_term(0, $13, 'fail', 'fail', 'fail', 'fail', $12)

$12:
	switch_on_constant(0, 32, ['$default':'fail', 0:$1, 1:$2, 2:$3, 3:$4, 4:$5, 5:$6, 6:$7, 7:$8, 8:$9, 9:$10, 10:$11])

$13:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	trust($11)

$1:
	get_integer(0, 0)
	get_constant('ev_no_error', 1)
	proceed

$2:
	get_integer(1, 0)
	get_constant('ev_inst', 1)
	proceed

$3:
	get_integer(2, 0)
	get_constant('ev_type', 1)
	proceed

$4:
	get_integer(3, 0)
	get_constant('ev_range', 1)
	proceed

$5:
	get_integer(4, 0)
	get_constant('ev_value', 1)
	proceed

$6:
	get_integer(5, 0)
	get_constant('ev_zero_divide', 1)
	proceed

$7:
	get_integer(6, 0)
	get_constant('ev_not_permitted', 1)
	proceed

$8:
	get_integer(7, 0)
	get_constant('ev_allocation_failure', 1)
	proceed

$9:
	get_integer(8, 0)
	get_constant('ev_system', 1)
	proceed

$10:
	get_integer(9, 0)
	get_constant('ev_unimplemented', 1)
	proceed

$11:
	get_integer(10, 0)
	get_constant('ev_unsupported', 1)
	proceed
end('$psi_error_to_atom'/2):



'$template_to_type'/2:

	switch_on_term(0, $10, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, '+'/1:$7, '@'/1:$8, '?'/1:$9])

$6:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(2, $1)
	trust($4)

$8:
	try(2, $2)
	trust($4)

$9:
	try(2, $3)
	trust($4)

$10:
	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure('+', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	get_structure('@', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$3:
	get_structure('?', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	neck_cut
	proceed

$4:
	get_x_value(0, 1)
	neck_cut
	proceed
end('$template_to_type'/2):



'$psi_call_to_call'/2:

	switch_on_term(0, $76, $37, $37, $38, $37, $37)

$38:
	switch_on_structure(0, 128, ['$default':$37, '$'/0:$39, '$set_input'/1:$40, '$set_output'/1:$41, '$thread_wait'/1:$42, '$thread_defaults'/1:$43, '$thread_set_defaults'/1:$44, '$reset_std_stream'/1:$45, '$get_char'/2:$46, '$get_code'/2:$47, '$psi_write_atom'/2:$48, '$psi_writeq_atom'/2:$49, '$write_integer'/2:$50, '$codes_atom'/2:$51, '$char_code'/2:$52, '$code_char'/2:$53, '$close'/2:$54, '$stream_to_chars'/2:$55, '$stream_to_atom'/2:$56, '$delay'/2:$57, '$not_free_in'/2:$58, '$increment'/2:$59, '$decrement'/2:$60, '$get_line'/2:$61, '$put_line'/2:$62, '$add'/3:$63, '$subtract'/3:$64, '$open'/3:$65, '$access'/3:$66, '$encoded_write'/3:$67, '$open_socket_stream'/3:$68, '$open_msgstream'/3:$69, '$sub_atom'/4:$70, '$load_foreign'/4:$71, '$open_string'/4:$72, '$encoded_read'/4:$73, '$ipc_send'/4:$74, '$thread_fork'/3:$75])

$39:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	retry($13)
	retry($14)
	retry($15)
	retry($16)
	retry($17)
	retry($18)
	retry($19)
	retry($20)
	retry($21)
	retry($22)
	retry($23)
	retry($24)
	retry($25)
	retry($26)
	retry($27)
	retry($28)
	retry($29)
	retry($30)
	retry($31)
	retry($32)
	retry($33)
	retry($34)
	retry($35)
	retry($36)
	trust($37)

$40:
	try(2, $1)
	trust($37)

$41:
	try(2, $2)
	trust($37)

$42:
	try(2, $3)
	trust($37)

$43:
	try(2, $4)
	trust($37)

$44:
	try(2, $5)
	trust($37)

$45:
	try(2, $6)
	trust($37)

$46:
	try(2, $7)
	trust($37)

$47:
	try(2, $8)
	trust($37)

$48:
	try(2, $9)
	trust($37)

$49:
	try(2, $10)
	trust($37)

$50:
	try(2, $11)
	trust($37)

$51:
	try(2, $12)
	trust($37)

$52:
	try(2, $13)
	trust($37)

$53:
	try(2, $14)
	trust($37)

$54:
	try(2, $15)
	trust($37)

$55:
	try(2, $16)
	trust($37)

$56:
	try(2, $17)
	trust($37)

$57:
	try(2, $18)
	trust($37)

$58:
	try(2, $19)
	trust($37)

$59:
	try(2, $20)
	trust($37)

$60:
	try(2, $21)
	trust($37)

$61:
	try(2, $22)
	trust($37)

$62:
	try(2, $23)
	trust($37)

$63:
	try(2, $24)
	trust($37)

$64:
	try(2, $25)
	trust($37)

$65:
	try(2, $26)
	trust($37)

$66:
	try(2, $27)
	trust($37)

$67:
	try(2, $28)
	trust($37)

$68:
	try(2, $29)
	trust($37)

$69:
	try(2, $30)
	trust($37)

$70:
	try(2, $31)
	trust($37)

$71:
	try(2, $32)
	trust($37)

$72:
	try(2, $33)
	trust($37)

$73:
	try(2, $34)
	trust($37)

$74:
	try(2, $35)
	trust($37)

$75:
	try(2, $36)
	trust($37)

$76:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	retry($13)
	retry($14)
	retry($15)
	retry($16)
	retry($17)
	retry($18)
	retry($19)
	retry($20)
	retry($21)
	retry($22)
	retry($23)
	retry($24)
	retry($25)
	retry($26)
	retry($27)
	retry($28)
	retry($29)
	retry($30)
	retry($31)
	retry($32)
	retry($33)
	retry($34)
	retry($35)
	retry($36)
	trust($37)

$1:
	get_structure('$set_input', 1, 0)
	unify_x_variable(0)
	get_structure('set_input', 1, 1)
	unify_x_value(0)
	neck_cut
	proceed

$2:
	get_structure('$set_output', 1, 0)
	unify_x_variable(0)
	get_structure('set_output', 1, 1)
	unify_x_value(0)
	neck_cut
	proceed

$3:
	get_structure('$thread_wait', 1, 0)
	unify_x_variable(0)
	get_structure('thread_wait', 1, 1)
	unify_x_value(0)
	neck_cut
	proceed

$4:
	get_structure('$thread_defaults', 1, 0)
	unify_x_variable(0)
	get_structure('thread_defaults', 1, 1)
	unify_x_value(0)
	neck_cut
	proceed

$5:
	get_structure('$thread_set_defaults', 1, 0)
	unify_x_variable(0)
	get_structure('thread_set_defaults', 1, 1)
	unify_x_value(0)
	neck_cut
	proceed

$6:
	get_structure('$reset_std_stream', 1, 0)
	unify_x_variable(0)
	get_structure('reset_std_stream', 1, 1)
	unify_x_value(0)
	neck_cut
	proceed

$7:
	get_structure('$get_char', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('get_char', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$8:
	get_structure('$get_code', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('get_code', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$9:
	get_structure('$psi_write_atom', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('write_atom', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$10:
	get_structure('$psi_writeq_atom', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('write_atomq', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$11:
	get_structure('$write_integer', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('write_integer', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$12:
	get_structure('$codes_atom', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('codes_atom', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$13:
	get_structure('$char_code', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('char_code', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$14:
	get_structure('$code_char', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('code_char', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$15:
	get_structure('$close', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('close', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$16:
	get_structure('$stream_to_chars', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('stream_to_chars', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$17:
	get_structure('$stream_to_atom', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('stream_to_atom', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$18:
	get_structure('$delay', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('delay', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$19:
	get_structure('$not_free_in', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('not_free_in', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$20:
	get_structure('$increment', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('is', 2, 1)
	unify_x_value(2)
	unify_x_ref(1)
	get_structure('+', 2, 1)
	unify_x_value(0)
	unify_integer(1)
	neck_cut
	proceed

$21:
	get_structure('$decrement', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('is', 2, 1)
	unify_x_value(2)
	unify_x_ref(1)
	get_structure('-', 2, 1)
	unify_x_value(0)
	unify_integer(1)
	neck_cut
	proceed

$22:
	get_structure('$get_line', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('get_line', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$23:
	get_structure('$put_line', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('put_line', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$24:
	get_structure('$add', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('is', 2, 1)
	unify_x_value(3)
	unify_x_ref(1)
	get_structure('+', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$25:
	get_structure('$subtract', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('is', 2, 1)
	unify_x_value(3)
	unify_x_ref(1)
	get_structure('-', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	neck_cut
	proceed

$26:
	get_structure('$open', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('open', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	neck_cut
	proceed

$27:
	get_structure('$access', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('access', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	neck_cut
	proceed

$28:
	get_structure('$encoded_write', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('encoded_write', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	neck_cut
	proceed

$29:
	get_structure('$open_socket_stream', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('open_socket_stream', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	neck_cut
	proceed

$30:
	get_structure('$open_msgstream', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('open_msgstream', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	neck_cut
	proceed

$31:
	get_structure('$sub_atom', 4, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	get_structure('sub_atom', 4, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	neck_cut
	proceed

$32:
	get_structure('$load_foreign', 4, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	get_structure('load_foreign', 4, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	neck_cut
	proceed

$33:
	get_structure('$open_string', 4, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	get_structure('open_string', 4, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	neck_cut
	proceed

$34:
	get_structure('$encoded_read', 4, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	get_structure('encoded_read', 4, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	neck_cut
	proceed

$35:
	get_structure('$ipc_send', 4, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	get_structure('ipc_send', 4, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	neck_cut
	proceed

$36:
	get_structure('$thread_fork', 3, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('thread_fork', 3, 1)
	unify_x_value(0)
	unify_x_value(2)
	unify_x_value(3)
	neck_cut
	proceed

$37:
	get_x_value(0, 1)
	proceed
end('$psi_call_to_call'/2):



'$query_psi_errors1593041821_478/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(200, 0)
	put_constant('fy', 1)
	put_constant('@', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_psi_errors1593041821_478/0$0'/0):



'$query_psi_errors1593041821_478/0$1'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(500, 0)
	put_constant('fy', 1)
	put_constant('?', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_psi_errors1593041821_478/0$1'/0):



'$query_psi_errors1593041821_478'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	allocate(0)
	call_predicate('$query_psi_errors1593041821_478/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_psi_errors1593041821_478/0$1', 0, 0)
	fail

$3:
	proceed
end('$query_psi_errors1593041821_478'/0):



'$query'/0:


$1:
	execute_predicate('$query_psi_errors1593041821_478', 0)
end('$query'/0):



