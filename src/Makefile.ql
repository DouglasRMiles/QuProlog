export COMMAND.ql = ql

export SOURCES.ql	= \
	ql.cc \
	ql_options.cc

export BASES.ql	= $(basename $(SOURCES.ql))
export OBJECTS.ql = $(addsuffix .o,$(BASES.ql))

.PHONY:	all.ql
all.ql: $(COMMAND.ql)

$(COMMAND.ql): $(OBJECTS.ql) $(BIG_LIBRARY)
	$(CXX) $(LDFLAGS) -o $(COMMAND.ql) $(OBJECTS.ql) -lnsl -ldl  $(BIG_LIBRARY)

.PHONY: install.ql
install.ql: /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin/$(COMMAND.ql)

/opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin/$(COMMAND.ql): $(COMMAND.ql)
	/usr/bin/install -c $(COMMAND.ql) /opt/logicmoo_workspace/packs_sys/logicmoo_opencog/QuProlog/bin

.PHONY:	clean.ql
clean.ql:
	$(RM) $(OBJECTS.ql) $(COMMAND.ql) Makefile.ql


