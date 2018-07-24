
#include "objects.h"
#include "atom_table.h"
#include "pedro_env.h"
#include "thread_qp.h"
#include "heap_qp.h"


void set_buffstate(char* buff, int size);

void delete_buffstate();

int scanner(Thread* th, AtomTable* atoms, VarMap* vmap, Object** val, bool r);

#define ERROR_TOKEN              0
#define NEWLINE_TOKEN            1
#define OBRA_TOKEN               2
#define CBRA_TOKEN               3
#define COMMA_TOKEN              4
#define OSBRA_TOKEN              5
#define CSBRA_TOKEN              6
#define VBAR_TOKEN               7
#define TERM_TOKEN               8
