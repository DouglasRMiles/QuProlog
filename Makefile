#
# Main makefile
#
# Please note that the order in which the targets are evaluated
# is important. Don't be tempted to reorder or parallelise
# the makefiles!
#
# Richard Hagen
#

#
# Nothing else should need attention, but there are some things that
# are interesting later on, particularly the rules for making Qu-Prolog
# objects.
#

export QPBIN	= /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin


export QC		= qc
export QC_RELEASE	= qc
export QCFLAGS		= 
export BOOTSTRAP.qc	= $(QPBIN)/$(QC) $(QCFLAGS)
export COMPILE.qc	= $(QPBIN)/qc $(QCFLAGS)

export PROLOG		= prolog



.PHONY: all
all:	objects

#export	PARALLEL	= -j 2

.PHONY: objects
objects:
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin	$(PARALLEL) all 
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src	$(PARALLEL) all
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src	$(PARALLEL) install
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/prolog	$(PARALLEL) all



.PHONY: tkICM
tkICM:
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src tkICM

.PHONY: xqp
xqp:
	cd /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src/xqp;qmake;cd -
	cd /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src/xqpdebug;qmake;cd -
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src/xqp
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src/xqpdebug
	/usr/bin/install /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src/xqp/xqp /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin
	/usr/bin/install /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src/xqpdebug/xqpdebug /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin

.PHONY: clean
clean:
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin	$(PARALLEL) clean
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/src	$(PARALLEL) clean
	@$(MAKE) -C /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/prolog	$(PARALLEL) clean
