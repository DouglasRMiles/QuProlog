#
# Makefile for "qecat"
#

PROGRAM		= $(QPBIN)/qecat

SOURCES		= qecat.ql

BASES		= $(basename $(SOURCES))
OBJECTS		= $(addsuffix .qo,$(BASES))
ASMS =        $(addsuffix .qs,$(BASES))

.PHONY:	all
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(COMPILE.qc)  -o $(PROGRAM) $(OBJECTS)

.PHONY:	clean
clean:
	$(RM) $(OBJECTS) 


%.qo: %.qs
	$(COMPILE.qc) -c -o $@ $<

