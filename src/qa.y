%{
/*
 * Copyright (C) 2000-Wednesday 16 May  13:50:25 AEST 2018 
 * Department of Computer Science and Electrical Engineering, 
 * The University of Queensland
 */


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "asm_objects.h"
#include "asm_string_table.cc"
#include "code.h"
#include "code_block.h"
#include "errors.h"
#include "indexing.h"

const char *Program = "qa";

extern "C" int yylex();

int yyerror(const char *);

ASMStringTable *asm_string_table = NULL;

CodeBlock *query_code_block = NULL;
vector<CodeBlock *> *predicate_code_blocks = NULL;

CodeBlock *code_block = NULL;

LabelTable *labels = NULL;

%}
%union {
  long int_value;
  double double_value;

  string *label_name;
  string *atom_name;
  string *string_value;

  ASMLoc loc;

  ASMInt<Code::InstructionSizedType> *instruction;
  ASMInt<Code::ConstantSizedType> *constant;
  ASMDouble<double> *double_num;
  ASMInt<long> *int_num;
  ASMInt<Code::RegisterSizedType> *reg;
  ASMInt<Code::NumberSizedType> *number;
  ASMInt<Code::AddressSizedType> *address;
  ASMInt<Code::OffsetSizedType> *offset;
  ASMInt<Code::PredSizedType> *pred;
  ASMInt<Code::TableSizeSizedType> *table_size;

  vector<ConstantLabel *> *cl_list;
  ConstantLabel *cl;
  
  vector<AtomArityLabel *> *aal_list;
  AtomArityLabel *aal;
}

%token <instruction> put_x_variable
%token <instruction> put_y_variable
%token <instruction> put_x_value
%token <instruction> put_y_value
%token <instruction> put_constant
%token <instruction> put_integer
%token <instruction> put_double
%token <instruction> put_string
%token <instruction> put_list
%token <instruction> put_structure
%token <instruction> put_x_object_variable
%token <instruction> put_y_object_variable
%token <instruction> put_x_object_value
%token <instruction> put_y_object_value
%token <instruction> put_quantifier check_binder
%token <instruction> put_substitution
%token <instruction> put_x_term_substitution
%token <instruction> put_y_term_substitution
%token <instruction> put_initial_empty_substitution

%token <instruction> get_x_variable
%token <instruction> get_y_variable
%token <instruction> get_x_value
%token <instruction> get_y_value
%token <instruction> get_constant
%token <instruction> get_integer
%token <instruction> get_double
%token <instruction> get_string
%token <instruction> get_list
%token <instruction> get_structure
%token <instruction> get_structure_frame
%token <instruction> get_x_object_variable
%token <instruction> get_y_object_variable
%token <instruction> get_x_object_value
%token <instruction> get_y_object_value

%token <instruction> unify_x_variable
%token <instruction> unify_y_variable
%token <instruction> unify_x_value
%token <instruction> unify_y_value
%token <instruction> unify_void
%token <instruction> unify_constant 
%token <instruction> unify_integer 
%token <instruction> unify_double 
%token <instruction> unify_string 
%token <instruction> unify_x_ref 
%token <instruction> unify_y_ref 

%token <instruction> set_x_variable
%token <instruction> set_y_variable
%token <instruction> set_x_value
%token <instruction> set_y_value
%token <instruction> set_x_object_variable
%token <instruction> set_y_object_variable
%token <instruction> set_x_object_value
%token <instruction> set_y_object_value
%token <instruction> set_constant
%token <instruction> set_integer
%token <instruction> set_double
%token <instruction> set_string
%token <instruction> set_void
%token <instruction> set_object_void

%token <instruction> wam_allocate
%token <instruction> wam_deallocate

%token <instruction> call_predicate
%token <instruction> call_address
%token <instruction> call_escape

%token <instruction> execute_predicate
%token <instruction> execute_address
%token <instruction> execute_escape

%token <instruction> noop
%token <instruction> jump
%token <instruction> proceed
%token <instruction> wam_fail
%token <instruction> halt
%token <instruction> wam_exit

%token <instruction> try_me_else
%token <instruction> retry_me_else
%token <instruction> trust_me_else_fail

%token <instruction> wam_try
%token <instruction> retry
%token <instruction> trust

%token <instruction> neck_cut
%token <instruction> get_x_level
%token <instruction> get_y_level
%token <instruction> cut

%token <instruction> switch_on_term
%token <instruction> switch_on_constant
%token <instruction> switch_on_structure
%token <instruction> switch_on_quantifier

%token <instruction> pseudo_instr0
%token <instruction> pseudo_instr1
%token <instruction> pseudo_instr2
%token <instruction> pseudo_instr3
%token <instruction> pseudo_instr4
%token <instruction> pseudo_instr5

%type <cl_list> constant_labels
%type <cl_list> constant_label_list
%type <cl> constant_label

%type <aal_list> atom_arity_labels
%type <aal_list> atom_arity_label_list
%type <aal> atom_arity_label

%type <aal_list> quantifier_labels
%type <aal_list> quantifier_label_list
%type <aal> quantifier_label

%type <label_name> switch_label

%type <constant> atom
%type <address> address
%type <constant> constant
%type <double_num> double_num
%type <int_num> int_num
%type <number> number
%type <reg> reg
%type <table_size> table_size

%token <int_value> INTEGER_TOKEN
%token <double_value> DOUBLE_TOKEN
%token <string_value> STRING_TOKEN
%token <atom_name> ATOM_TOKEN
%token <label_name> LABEL_TOKEN
%token END_TOKEN

%start assembler_file

%%
assembler_file: predicate_list
	;

predicate_list:				/* empty */
	| predicate_list predicate
	;

predicate: predicate_start source_line_list predicate_end
	;

predicate_start: atom '/' number ':'
		{
		  labels = new LabelTable;

		  // Is it the query code block?
		  if ((*asm_string_table)[$1->Value()] == "$query" &&
		      $3->Value() == 0)
		    {
		      if (query_code_block != NULL)
			{
			  Fatal(__FUNCTION__, 
				"more than one query code block");
			}
		      query_code_block = new CodeBlock(QUERY_BLOCK,
						       $1->Value(),
						       $3->Value());

		      code_block = query_code_block;
		    }
		  else
		    {
		      code_block = new CodeBlock(PREDICATE_BLOCK,
						 $1->Value(),
						 $3->Value());
		    }

		  delete $1;
		  delete $3;
		}
	;

predicate_end: END_TOKEN '(' atom '/' number ')' ':'
		{
		  if ($3->Value() != code_block->Atom() ||
		      (u_int)($5->Value()) != code_block->Arity())
		    {
		      Fatal(__FUNCTION__, 
			    "atom or arity mismatch in predicate");
		    }

		  delete $3;
		  delete $5;

		  // Resolve all the fail label references
		  labels->ResolveFail(*code_block);

		  if (code_block->Type() == PREDICATE_BLOCK)
		    {
		      predicate_code_blocks->push_back(code_block);
		    }
		  
		  // Make it difficult to reuse the label table
		  delete labels;
		  labels = NULL;
		}
	;

source_line_list:			/* empty */
	|  source_line_list source_line
	;

source_line: label_instance
	| instr
	;

label_instance: LABEL_TOKEN ':'
		{
		  labels->Resolve(*$1, *code_block);
		}
	;

instr: put_x_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_y_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_x_value '(' reg ','  reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_y_value '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_constant '(' constant ','  reg ')'
 		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_integer '(' int_num ','  reg ')'
 		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}
	| put_double '(' double_num ','  reg ')'
 		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}
	| put_string '(' STRING_TOKEN ','  reg ')'
 		{
		  $1->Put(*code_block); delete $1;
		  $5->Put(*code_block); delete $5;
		  string* buff = $3;
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete $3;
		}

	| put_list '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| put_structure '(' number ','  reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_x_object_variable '(' reg ','  reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_y_object_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_x_object_value '(' reg ',' reg ')'
		 {
		   $1->Put(*code_block); delete $1;
		   $3->Put(*code_block); delete $3;
		   $5->Put(*code_block); delete $5;
		 }

	| put_y_object_value '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_quantifier '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| check_binder '(' reg ')' 
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| put_substitution '(' number ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_x_term_substitution '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_y_term_substitution '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| put_initial_empty_substitution '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| get_x_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_y_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_x_value '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_y_value '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_constant '(' constant ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_integer '(' int_num ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_double '(' double_num ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_string '(' STRING_TOKEN ','  reg ')'
 		{
		  $1->Put(*code_block); delete $1;
		  $5->Put(*code_block); delete $5;
		  string* buff = $3;
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete $3;
		}

	| get_list '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| get_structure '(' constant ',' number ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		  $7->Put(*code_block); delete $7;
		}

	| get_structure_frame '(' number ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_x_object_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_y_object_variable '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_x_object_value '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| get_y_object_value '(' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| unify_x_variable '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| unify_y_variable '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| unify_x_value '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| unify_y_value '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| unify_constant '(' constant ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| unify_integer '(' int_num ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| unify_double '(' double_num ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| unify_string '(' STRING_TOKEN ')'
 		{
		  $1->Put(*code_block); delete $1;
		  string* buff = $3;
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete $3;
		}

	| unify_void '(' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
	        }

	| unify_x_ref '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| unify_y_ref '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_x_variable '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_y_variable '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
	        }

	| set_x_value '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_y_value '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_x_object_variable '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_y_object_variable '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_x_object_value '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
        	}

	| set_y_object_value '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
	        }

	| set_constant '(' constant ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| set_integer '(' int_num ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| set_double '(' double_num ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| set_string '(' STRING_TOKEN ')'
 		{
		  $1->Put(*code_block); delete $1;
		  string* buff = $3;
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete $3;
		}

	| set_void '(' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| set_object_void '(' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| wam_allocate '(' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| wam_deallocate
		{
		  $1->Put(*code_block); delete $1;
		}

	| call_predicate '(' atom ',' number ',' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		  $7->Put(*code_block); delete $7;
		}

	| call_address '(' address ',' number ')'
		{
		  $1->Put(*code_block); delete $1; 
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| call_escape '(' address ',' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| execute_predicate '(' atom ',' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| execute_address '(' address ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| execute_escape '(' address ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| noop
		{
		  $1->Put(*code_block); delete $1;
		}

	| jump '(' address ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| proceed
		{
		  $1->Put(*code_block); delete $1;
		}

	| wam_fail
		{
		  $1->Put(*code_block); delete $1;
		}

	| halt
		{
		  $1->Put(*code_block); delete $1;
		}

	| wam_exit
		{
		  $1->Put(*code_block); delete $1;
		}

	| try_me_else '(' number ',' LABEL_TOKEN ')'
		{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + $3->SizeOf() + Code::SIZE_OF_OFFSET;

		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;

		  labels->AddReference(*$5, *code_block, jump_offset_base);
		}

	| retry_me_else '(' LABEL_TOKEN ')'
		{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + Code::SIZE_OF_OFFSET;

		  $1->Put(*code_block); delete $1;
		  labels->AddReference(*$3, *code_block, jump_offset_base);
		}

	| trust_me_else_fail
		{
		  $1->Put(*code_block); delete $1;
		}

	| wam_try '(' number ',' LABEL_TOKEN ')'
		{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + $3->SizeOf() + Code::SIZE_OF_OFFSET;

		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;

		  labels->AddReference(*$5, *code_block, jump_offset_base);
		}

	| retry '(' LABEL_TOKEN ')'
		{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + Code::SIZE_OF_OFFSET;

		  $1->Put(*code_block); delete $1;
		  labels->AddReference(*$3, *code_block, jump_offset_base);
		}

	| trust '(' LABEL_TOKEN ')'
		{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + Code::SIZE_OF_OFFSET;

		  $1->Put(*code_block); delete $1;
		  labels->AddReference(*$3, *code_block, jump_offset_base);
		}

	| neck_cut
		{
		  $1->Put(*code_block); delete $1;
		}

	| get_x_level '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| get_y_level '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| cut '(' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| switch_on_term '(' reg ','
		switch_label ','
     		switch_label ','
     		switch_label ','
		switch_label ','
     		switch_label ','
		switch_label ')'
		{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + $3->SizeOf() + 6 * Code::SIZE_OF_OFFSET;

		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;

		  labels->AddReference(*$5, *code_block, jump_offset_base);
		  labels->AddReference(*$7, *code_block, jump_offset_base);
		  labels->AddReference(*$9, *code_block, jump_offset_base);
		  labels->AddReference(*$11, *code_block, jump_offset_base);
		  labels->AddReference(*$13, *code_block, jump_offset_base);
		  labels->AddReference(*$15, *code_block, jump_offset_base);
		}

	| switch_on_constant '(' reg ','  table_size ','
	  '[' ATOM_TOKEN ':' switch_label constant_labels ']' ')'
		{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + $3->SizeOf() + $5->SizeOf();

		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); 

		  if (*$8 != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		 ConstantSwitchTable switch_table(jump_offset_base,
							  $5, $10, $11);

		  switch_table.Put(*code_block, *labels);

		  delete $5;
		  delete $10;
		  delete $11;
		}

	| switch_on_structure '(' reg ',' table_size ','
	  '[' ATOM_TOKEN ':' switch_label atom_arity_labels ']' ')'
		{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + $3->SizeOf() + $5->SizeOf();

		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block);

		  if (*$8 != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   $5, $10, $11);

		  switch_table.Put(*code_block, *labels);

		  delete $5;
		  delete $10;
		  delete $11;
		}

	| switch_on_quantifier '(' reg ',' table_size ','
	  '[' ATOM_TOKEN ':' switch_label quantifier_labels ']' ')'
		{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      $1->SizeOf() + $3->SizeOf() + $5->SizeOf();

		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block);

		  if (*$8 != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_quantifier");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   $5, $10, $11);

		  switch_table.Put(*code_block, *labels);

		  delete $5;
		  delete $10;
		  delete $11;
		}

	| pseudo_instr0 '(' number ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		}

	| pseudo_instr1 '(' number ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		}

	| pseudo_instr2 '(' number ',' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		  $7->Put(*code_block); delete $7;
		}

	| pseudo_instr3 '(' number ',' reg ',' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		  $7->Put(*code_block); delete $7;
		  $9->Put(*code_block); delete $9;
		}

	| pseudo_instr4 '(' number ','
	  reg ',' reg ',' reg ',' reg ')'
		{
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		  $7->Put(*code_block); delete $7;
		  $9->Put(*code_block); delete $9;
		  $11->Put(*code_block); delete $11;
		}
	| pseudo_instr5 '(' number ','
	  reg ',' reg ',' reg ',' reg ',' reg ')'
                {
		  $1->Put(*code_block); delete $1;
		  $3->Put(*code_block); delete $3;
		  $5->Put(*code_block); delete $5;
		  $7->Put(*code_block); delete $7;
		  $9->Put(*code_block); delete $9;
		  $11->Put(*code_block); delete $11;
		  $13->Put(*code_block); delete $13;
		}
	;

constant_labels: 
		{
		  $$ = NULL;
		}
	| ',' constant_label_list
		{
		  $$ = $2;
		}
	;

constant_label_list: constant_label
		{
		  vector<ConstantLabel *> *tmp = new vector<ConstantLabel *>;

		  tmp->push_back($1);

		  $$ = tmp;
		}
	| constant_label_list ',' constant_label
		{
		  $1->push_back($3);

		  $$ = $1;
		}
	;

constant_label: constant ':' switch_label
		{
		  $$ = new ConstantLabel($1, $3);
		  
		}
	;

atom_arity_labels:
		{
		  $$ = NULL;
		}
	| ',' atom_arity_label_list
		{
		  $$ = $2;
		}
	;

atom_arity_label_list: atom_arity_label
		{
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back($1);

		  $$ = tmp;
		}
	| atom_arity_label_list ',' atom_arity_label
		{
		  $1->push_back($3);
		  $$ = $1;
		}
	;

atom_arity_label: ATOM_TOKEN '/' number ':' switch_label
		{
		  ASMStringPointer asm_atom($1);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  long arity = $3->Value();
		  ASMInt<Code::NumberSizedType> *carity = new ASMInt<Code::NumberSizedType>(arity);
		  $$ = new AtomArityLabel(atom, carity, $5);

		}
	;

quantifier_labels:
		{
		  $$ = NULL;
		}
	| ',' quantifier_label_list
		{
		  $$ = $2;
		}
	;

quantifier_label_list: quantifier_label
		{
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back($1);

		  $$ = tmp;
		}
	| quantifier_label_list ',' quantifier_label
		{
		  $1->push_back($3);

		  $$ = $1;
		}
	;

quantifier_label: ATOM_TOKEN '/' number ':' switch_label
		{
		  ASMStringPointer asm_atom($1);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  long arity = $3->Value();
		  ASMInt<Code::NumberSizedType> *carity = new ASMInt<Code::NumberSizedType>(arity);
		  $$ = new AtomArityLabel(atom, carity, $5);
		}
	;

switch_label: LABEL_TOKEN
	| ATOM_TOKEN 
		{
		  if (*$1 != "fail")
		    {
		      FatalS(__FUNCTION__, "invalid switch label ",
			     $1->c_str());
		    }
		}
	;

constant: ATOM_TOKEN
		{
		  ASMStringPointer asm_atom($1);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  $$ = new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		}
	| INTEGER_TOKEN
                {
                  $$ = new ASMInt<Code::ConstantSizedType>((Code::ConstantSizedType)($1), ConstEntry::INTEGER_TYPE);

                }
        | '+' INTEGER_TOKEN
                {
                  $$ = new ASMInt<Code::ConstantSizedType>((Code::ConstantSizedType)($2), ConstEntry::INTEGER_TYPE);

                }
        | '-' INTEGER_TOKEN
                {
                  $$ = new ASMInt<Code::ConstantSizedType>((Code::ConstantSizedType)(-$2), ConstEntry::INTEGER_TYPE);

                }
        ;

number: INTEGER_TOKEN
		{ 
		  $$ = new ASMInt<Code::NumberSizedType>($1);

                }
        ;

int_num: INTEGER_TOKEN
		{
		  $$ = new ASMInt<long>((long)($1), ConstEntry::INTEGER_TYPE);

		}
	| '+' INTEGER_TOKEN
		{
		  $$ = new ASMInt<long>((long)($2), ConstEntry::INTEGER_TYPE);

		}
	| '-' INTEGER_TOKEN
		{
		  $$ = new ASMInt<long>(-(long)($2), ConstEntry::INTEGER_TYPE);

		}
	;

double_num: DOUBLE_TOKEN
		{
		  $$ = new ASMDouble<double>((double)($1), ConstEntry::INTEGER_TYPE);

		}
	| '+' DOUBLE_TOKEN
		{
		  $$ = new ASMDouble<double>((double)($2), ConstEntry::INTEGER_TYPE);

		}
	| '-' DOUBLE_TOKEN
		{
		  $$ = new ASMDouble<double>((double)(-$2), ConstEntry::INTEGER_TYPE);

		}
	;

reg: INTEGER_TOKEN
		{
		  $$ = new ASMInt<Code::RegisterSizedType>($1);
		  
		}
	;

address: INTEGER_TOKEN
		{
		  $$ = new ASMInt<Code::AddressSizedType>($1);

		}
	;

atom: ATOM_TOKEN
		{
		  ASMStringPointer asm_atom($1);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);
		  $$ = new ASMInt<Code::PredSizedType>(loc);
		}
	;

table_size: INTEGER_TOKEN
		{
		  $$ = new ASMInt<Code::TableSizeSizedType>($1);

		}
	;

%%
#include "lexer.cc"

#include <stdlib.h>

#include "qa_options.h"
		
QaOptions *qa_options = NULL;

int
main(int argc, char **argv)
{
  qa_options = new QaOptions(argc, argv);

  if (!qa_options->Valid())
    {
      Usage(Program, qa_options->Usage());
    }

  if (streq(qa_options->InputFile(), qa_options->OutputFile()))
    {
      Fatal(__FUNCTION__, "Input and output file names are identical");
    }

  // Should also check for suspect extensions .qg, .qi, .qs, .ql, .qx
  asm_string_table = new ASMStringTable;
  predicate_code_blocks = new vector<CodeBlock *>;

  // Read in the assembler source
  yyin = fopen(qa_options->InputFile(), "r");
  if (yyin == NULL)
    {
      perror(__FUNCTION__);
      exit(EXIT_FAILURE);
    }
      
  int result = yyparse();
  if (result)
    {
      Fatal(__FUNCTION__, "bad .qs input file");
    }
  fclose(yyin);

  // Write out the assembled object

  // First check if any compiled predicates are too big - i.e. >= 2^16
  for (vector<CodeBlock *>::iterator iter = predicate_code_blocks->begin();
       iter != predicate_code_blocks->end();
       iter++)
    {
      if ((*iter)->Current() >= (1 << (8*sizeof(Code::OffsetSizedType))))
        {
	  Fatal(__FUNCTION__, "Compiled predicate is too big");
	}
    }

  #ifdef WIN32
  ofstream ostrm(qa_options->OutputFile(), ios_base::binary);
  #else
  ofstream ostrm(qa_options->OutputFile());
  #endif


  asm_string_table->save(ostrm);

  if (query_code_block)
    {
      query_code_block->Save(ostrm);
    }
  else
    {
      IntSave<Code::OffsetSizedType>(ostrm, 0);
    }
  
  for (vector<CodeBlock *>::iterator iter = predicate_code_blocks->begin();
       iter != predicate_code_blocks->end();
       iter++)
    {
      (*iter)->Save(ostrm);
    }

  ostrm.close();

  exit(EXIT_SUCCESS);
}

int
yyerror(const char *s)
{
  Fatal(__FUNCTION__, s);
  return(1);
}
