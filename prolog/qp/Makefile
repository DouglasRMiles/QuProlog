#
# Makefile for "qp"
#
PROGRAM		= /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin/qp

SOURCES		= qp.ql

BASES		= $(basename $(SOURCES))
OBJECTS		= $(addsuffix .qo,$(BASES))
ASMS =        $(addsuffix .qs,$(BASES))

.PHONY:	all
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(COMPILE.qc) -r -o $(PROGRAM) $(OBJECTS)

.PHONY:	clean
clean:
	$(RM) Makefile $(OBJECTS) 


%.qo: %.qs
	$(COMPILE.qc) -c -o $@ $<

