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

export QPBIN	= /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/bin


export QC		= qc
export QCFLAGS		= 
export COMPILE.qc	= $(QPBIN)/$(QC) $(QCFLAGS)

export PROLOG		= prolog



.PHONY: all
all:	objects

#export	PARALLEL	= -j 2

.PHONY: objects
objects:
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/bin	$(PARALLEL) all 
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src	$(PARALLEL) all
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src	$(PARALLEL) install
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/prolog	$(PARALLEL) all



.PHONY: tkICM
tkICM:
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src tkICM

.PHONY: xqp
xqp:
	cd /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src/xqp;qmake;cd -
	cd /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src/xqpdebug;qmake;cd -
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src/xqp
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src/xqpdebug
	/usr/bin/install /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src/xqp/xqp /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/bin
	/usr/bin/install /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src/xqpdebug/xqpdebug /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/bin

.PHONY: clean
clean:
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/bin	$(PARALLEL) clean
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/src	$(PARALLEL) clean
	@$(MAKE) -C /opt/logicmoo_workspace/taupl/qulog0.4/QuProlog/prolog	$(PARALLEL) clean
