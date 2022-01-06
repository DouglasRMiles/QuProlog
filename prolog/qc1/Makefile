#
# Makefile for "qc1.qup"
#
PROGRAM		= /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin/qc1.qup

SOURCES		= qc1.ql

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

