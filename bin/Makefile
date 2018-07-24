#
# Makefile for "bin"
#

.PHONY: all
all: qppp_x

.PHONY: qppp_x
qppp_x:
	chmod a+x qppp

.PHONY: clean
clean:
	$(RM) Makefile kq qc qcc qc1.boot qppp

##BLOCK##

.PHONY: depend
depend:

.PHONY: clobber
clobber:

.PHONY: distclean
distclean: clobber
	$(RM) Makefile kq qc qcc qc1.boot qppp
##ENDBLOCK##


.DEFAULT:
	@echo "*** unknown target $@ (ignored)"
