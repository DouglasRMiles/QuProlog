export COMMAND.ql = ql

export SOURCES.ql	= \
	ql.cc \
	ql_options.cc

export BASES.ql	= $(basename $(SOURCES.ql))
export OBJECTS.ql = $(addsuffix .o,$(BASES.ql))

.PHONY:	all.ql
all.ql: $(COMMAND.ql)

$(COMMAND.ql): $(OBJECTS.ql) $(BIG_LIBRARY)
	$(CXX) $(LDFLAGS) -o $(COMMAND.ql) $(OBJECTS.ql)  $(BIG_LIBRARY)

.PHONY: install.ql
install.ql: /home/pjr/qp10.1/bin/$(COMMAND.ql)

/home/pjr/qp10.1/bin/$(COMMAND.ql): $(COMMAND.ql)
	/bin/install -c $(COMMAND.ql) /home/pjr/qp10.1/bin

.PHONY:	clean.ql
clean.ql:
	$(RM) $(OBJECTS.ql) $(COMMAND.ql) Makefile.ql

##BLOCK##
.PHONY:	clobber.ql
clobber.ql: clean.ql
	$(RM) $(GENERATED.ql) /home/pjr/qp10.1/bin/$(COMMAND.ql)

.PHONY: distclean.ql
distclean.ql: clobber.ql

.PHONY: depend.ql
depend.ql: $(SOURCES.ql) $(GENERATED.ql)
	$(CXX) $(CPPFLAGS) -MM $(SOURCES.ql) > Dependencies.ql

include Dependencies.ql
##ENDBLOCK##

