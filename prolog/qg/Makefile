#
# Makefile for "qg"
#

PROGRAM		= /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin/qg

SOURCES		= qg.ql

BASES		= $(basename $(SOURCES))
OBJECTS		= $(addsuffix .qo,$(BASES))
ASMS =        $(addsuffix .qs,$(BASES))

.PHONY:	all
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(COMPILE.qc) -o $(PROGRAM) $(OBJECTS)

.PHONY:	clean
clean:
	$(RM) Makefile $(OBJECTS) 


%.qo: %.qs
	$(BOOTSTRAP.qc) -c -o $@ $<

