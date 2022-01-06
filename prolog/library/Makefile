#
# Makefile for "prolog/library"
#
QPOBJDIR= /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/prolog_object/library

SOURCES	= \
	arithmetic.ql \
	ass_custom.ql \
	assert.ql \
	atoms.ql \
	bios.ql \
	buffers.ql \
	builtins.ql \
	c_to_prolog.ql \
	call.ql \
	catch.ql \
	chr_support.ql \
	clause.ql \
	communications.ql \
	compare.ql \
	compile_away.ql \
	consult.ql \
	copy_term.ql \
	dcg.ql \
	db.ql \
	dbqdeal.ql \
	debug.ql \
	delay.ql \
	dynamic.ql \
	pedro.ql \
	encode.ql \
	env_var.ql \
	equal.ql \
	errors.ql \
	eval_goal.ql \
	examine_term.ql \
	exception.ql \
	expand.ql \
	fcompile.ql \
	findall.ql \
	foreign.ql \
	freeness.ql \
	gui.ql \
	handlers.ql \
	higher_list.ql \
	higher_term.ql \
	index.ql \
	init.ql \
	instructions.ql \
	interpreter.ql \
	io.ql \
	ipc.ql \
	load.ql \
	machine.ql \
	name.ql \
	objvar.ql \
	op.ql \
	open_list_util.ql \
	os.ql \
	pipe.ql \
	process.ql \
	pseudo_instr.ql \
	psi_calls.ql \
	psi_errors.ql \
	quantifier.ql \
	read.ql \
	record.ql \
	retract.ql \
	same_args.ql \
	simplify.ql \
	start.ql \
	state.ql \
	statistics.ql \
	stream.ql \
	string.ql \
	structure.ql \
	substitution.ql \
	symbols.ql \
	tcp.ql \
	temperature.ql \
	term_exp.ql \
	thread.ql \
	version.ql \
	write.ql

QPBASES		= $(basename $(SOURCES))
QPOBJECTS	= $(addsuffix .qo,$(QPBASES))
QPASMS =        $(addsuffix .qs,$(QPBASES))

QSSOURCES 	= low_level.qs
QSBASES 	= $(basename $(QSSOURCES))
QSOBJECTS	= $(addsuffix .qo,$(QSBASES))

OBJECTS		= $(QPOBJECTS) $(QSOBJECTS)
ASMS = $(QPASMS) $(QSSOURCES)


.PHONY:	all
all: $(OBJECTS)

.PHONY:	clean
clean:
	$(RM) $(OBJECTS) Makefile


%.qo: %.qs
	$(COMPILE.qc) -c -o $@ $<
