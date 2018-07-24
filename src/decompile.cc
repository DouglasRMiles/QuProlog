// decompile.cc -  A decompiler
//
// ##Copyright##
// 
// Copyright 2000-2016 Peter Robinson  (pjr@itee.uq.edu.au)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.00 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ##Copyright##
//
// email: svrc@cs.uq.oz.au
//
// $Id: decompile.cc,v 1.11 2006/02/06 00:51:38 qp Exp $

#include <sys/types.h>
#include <signal.h>

#include "config.h"


#ifdef WIN32
        #include <io.h>
        #define _WINSOCKAPI_
        #include <windows.h>
#else
        #include <unistd.h>
        extern "C" int kill(pid_t, int);
#endif

#include "atom_table.h"
#include "code.h"
#include "dynamic_code.h"  
#include "pred_table.h"
#include "thread_qp.h"

#include "pseudo_instr_arrays.h"

extern AtomTable *atoms;
extern Code *code;
extern PredTab *predicates;

// Helps to label the opcodes for proceesing via MkOpcodes

#define	OPCODE(x, y)		x

#define BACKTRACK  return(RV_FAIL)

#define ADD_UNIFICATION(t1, t2, listElem)		                \
do {							                \
   Structure* u = heap.newStructure(2);   	                        \
   u->setFunctor(AtomTable::equal);                                     \
   u->setArgument(1, t1);                                               \
   u->setArgument(2, t2);                                               \
   Cons* l = heap.newCons();                                            \
   l->setHead(u);                                                       \
   *listElem = l;                                                       \
   listElem = l->getTailAddress();                                      \
 } while (0)

#define  BUILD_CALL_TERM(predicate, arity, listElem)    \
do {							\
   Object* u;						\
   if (arity == 0)					\
   {							\
     u = predicate;					\
   }							\
   else							\
   {							\
     Structure* call = heap.newStructure(arity);        \
     call->setFunctor(predicate);                       \
     for (int i = 0; i < (int)arity; i++)		\
     {							\
       call->setArgument(i+1, X[i]);                    \
     }							\
     u = call;                                          \
   }							\
   Cons* l = heap.newCons();                            \
   l->setHead(u);                                       \
   *listElem = l;                                       \
   listElem = l->getTailAddress();                      \
 } while (0)

Object*& 
DecPSIGetReg(const word32 i, Object** X, Object** Y)
{
  if (i < NUMBER_X_REGISTERS)
    {
      return X[i];
    }
  else
    {
      return Y[i - NUMBER_X_REGISTERS];
    }
}       

Thread::ReturnValue  
Thread::decompile(CodeLoc programCounter, Object* head, Object*& instrlist)
{
  heapobject*	StructurePointer = NULL;
  Object          *X[20], *Y[50];
  bool          inHead = true;
  Object**         listElem;
  Object*          instrHead;

  //
  // Inialize the instruction list
  //
  listElem = &instrHead;

  head = heap.dereference(head);

  //
  // Initialize the "X" registers with the args of the head
  //
  if (head->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, head);
      size_t n = str->getArity();
      while (n > 0)
        {
          X[n-1] = str->getArgument(n);
          n--;
        }
    }

  while (true)
    {
      switch (getInstruction(programCounter))
	{
	case OPCODE(PUT_X_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[i] = heap.newVariable();
	    X[j]= X[i];
	  }
	break;

	case OPCODE(PUT_Y_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[j] = heap.newVariable();
	    Y[i] = X[j];
	  }
	break;

	case OPCODE(PUT_X_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[j]= X[i];
	  }
	break;

	case OPCODE(PUT_Y_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[j]= Y[i];
	  }
	break;

	case OPCODE(PUT_CONSTANT, ARGS(constant, register)):
	  {
	    Object* c = getConstant(programCounter);
	    const word32 i = getRegister(programCounter);
	    X[i]= c;
	  }
	break;

	case OPCODE(PUT_INTEGER, ARGS(integer, register)):
	  {
	    Object* c = heap.newInteger(getInteger(programCounter));
	    const word32 i = getRegister(programCounter);
	    X[i]= c;
	  }
	break;

	case OPCODE(PUT_DOUBLE, ARGS(double, register)):
	  {
	    Object* c = heap.newDouble(getDouble(programCounter));
	    const word32 i = getRegister(programCounter);
	    X[i]= c;
	  }
	break;
	case OPCODE(PUT_STRING, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    char* c = (char*)programCounter;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    programCounter += size+1;

	    X[i]= str;
	  }
	break;

	case OPCODE(PUT_LIST, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    X[i] = heap.newCons();
	    StructurePointer = X[i]->storage();
	  }
	break;

	case OPCODE(PUT_STRUCTURE, ARGS(number, register)):
	  {
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    X[i] = heap.newStructure(n);
	    StructurePointer = X[i]->storage();
	  }
	break;

	case OPCODE(PUT_X_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[i] = heap.newObjectVariable();
	    X[j]= X[i];
	  }
	break;

	case OPCODE(PUT_Y_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[j] = heap.newObjectVariable();
	    Y[i] = X[j];
	  }
	break;

	case OPCODE(PUT_X_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[j] = X[i];
	  }
	break;

	case OPCODE(PUT_Y_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[j] = Y[i];
	  }
	break;

	case OPCODE(PUT_QUANTIFIER, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    X[i] = heap.newQuantifiedTerm();
            StructurePointer = X[i]->storage();  
	  }
	break;
	  
	case OPCODE(CHECK_BINDER, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    Object* c = AtomTable::nil;

            if (! checkBinder(X[i], c))
              {
                BACKTRACK;
              }  
	  }
	break;
	  
	case OPCODE(PUT_SUBSTITUTION, ARGS(number, register)):
	  {
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    SubstitutionBlock* sub = heap.newSubstitutionBlock(n);
            X[i] = heap.newSubstitutionBlockList(sub, X[i]);
            StructurePointer = sub->storage();      
	  }
	break;
	  
	case OPCODE(PUT_X_TERM_SUBSTITUTION, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
            assert(!X[i]->isNil());
            X[j] = heap.newSubstitution(X[i], X[j]);       
	  }
	break;
	  
	case OPCODE(PUT_Y_TERM_SUBSTITUTION, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
            assert(!Y[i]->isNil());
            X[j] = heap.newSubstitution(Y[i], X[j]);   
	  }
	break;
	  
	case OPCODE(PUT_INITIAL_EMPTY_SUBSTITUTION, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    X[i] = AtomTable::nil;    
	  }
	break;

	case OPCODE(GET_X_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    X[i] = X[j];
	  }
	break;
	  
	case OPCODE(GET_Y_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    Y[i] = X[j];
	  }
	break;

	case OPCODE(GET_X_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
            if (inHead)
              {
	        if (! unify(X[i], X[j]))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], X[j], listElem);
              }
	  }
	break;
	  
	case OPCODE(GET_Y_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);

            if (inHead)
              {
	        if (! unify(Y[i], X[j]))
	          {
		    BACKTRACK;
	          }
              } else
              {
                ADD_UNIFICATION(Y[i], X[j], listElem);
              }
         
	  }
	break;
	  
	case OPCODE(GET_CONSTANT, ARGS(constant, register)):
	  {
	    Object* c = getConstant(programCounter);
	    const word32 i =getRegister(programCounter);
            if (inHead)
              {
		if (! unify(X[i], c))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], c, listElem);
              }
	  }
	break; 

	case OPCODE(GET_INTEGER, ARGS(integer, register)):
	  {
	    Object* c = heap.newInteger(getInteger(programCounter));
	    const word32 i =getRegister(programCounter);
            if (inHead)
              {
		if (! unify(X[i], c))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], c, listElem);
              }
	  }
	break; 
	  
	case OPCODE(GET_DOUBLE, ARGS(double, register)):
	  {
	    Object* c = heap.newDouble(getDouble(programCounter));
	    const word32 i =getRegister(programCounter);
            if (inHead)
              {
		if (! unify(X[i], c))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], c, listElem);
              }
	  }
	break; 
	case OPCODE(GET_STRING, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    char* c = (char*)programCounter;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    programCounter += size+1;
            if (inHead)
              {
		if (! unify(X[i], str))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], str, listElem);
              }
	  }
	break;
  
	case OPCODE(GET_LIST, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);

	    Variable* newhead = heap.newVariable();
	    Variable* newtail = heap.newVariable();
	    newhead->setOccursCheck();        // PJR
	    newtail->setOccursCheck();        // PJR
	    Cons* newlist = heap.newCons(newhead, newtail);
	    StructurePointer = newlist->storage();       

            if (inHead)
              {
	        if (! unify(X[i], newlist))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], newlist, listElem);
              }
	  }
	break; 
	  
	case OPCODE(GET_STRUCTURE, ARGS(constant, number, register)):
	  {
	    Object* c = getConstant(programCounter);
	    const word32 n = getNumber(programCounter);
	    const word32 i =getRegister(programCounter);

	    Structure* newstruct = heap.newStructure(n);
	    newstruct->setFunctor(c);
	    for (u_int j = 1; j <= n; j++)
	      {
		Variable* arg = heap.newVariable();
		arg->setOccursCheck();        
		newstruct->setArgument(j, arg);
	      }
	    StructurePointer = newstruct->storage() + 1;     

            if (inHead)
              {
	        if (! unify(X[i], newstruct))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], newstruct, listElem);
              }
	  }
	break;
	  
	case OPCODE(GET_STRUCTURE_FRAME, ARGS(number, register)):
	  {
	    const word32 n = getNumber(programCounter);
	    const word32 i =getRegister(programCounter);

	    Structure* newstruct = heap.newStructure(n);
	    Variable* funct = heap.newVariable();
	    funct->setOccursCheck();        // PJR
	    newstruct->setFunctor(funct);          
	    for (u_int j = 1; j <= n; j++)
	      {
		Variable* arg = heap.newVariable();
		arg->setOccursCheck();        // PJR
		newstruct->setArgument(j, arg);
	      }
	    StructurePointer = newstruct->storage();     

            if (inHead)
              {
	        if (! unify(X[i], newstruct))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], newstruct, listElem);
              }
	  }
	break;
	  
	case OPCODE(GET_X_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i =getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    Object* xval = X[j];
	    X[i] = heap.newObjectVariable(); 

            if (inHead)
              {
	        if (! unify(X[i], xval))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], xval, listElem);
              }
	  }
	break; 
	  
	case OPCODE(GET_Y_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    
	    Object* xval = X[j];
	    Y[i] = heap.newObjectVariable();
	    if (inHead)
              {
		if (! unify(Y[i], xval))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(Y[i], xval, listElem);
              }
	  }
	break;
	  
	case OPCODE(GET_X_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i =getRegister(programCounter);
	    const word32 j = getRegister(programCounter);

            if (inHead)
              {
	        if (! unify(X[i], X[j]))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(X[i], X[j], listElem);
              }
	  }
	break; 
	  
	case OPCODE(GET_Y_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i =getRegister(programCounter);
	    const word32 j = getRegister(programCounter);

            if (inHead)
              {
	        if (! unify(Y[i], X[j]))
	          {
		    BACKTRACK;
	          }
              }
            else
              {
                ADD_UNIFICATION(Y[i], X[j], listElem);
              }
	  }
	break; 
	  
	case OPCODE(UNIFY_X_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    X[i] = reinterpret_cast<Object*>(*StructurePointer); 
            StructurePointer++;
	  }
	break;
	  
	case OPCODE(UNIFY_Y_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    Y[i] = reinterpret_cast<Object*>(*StructurePointer);
	    StructurePointer++;
          }
	break;
	  
	case OPCODE(UNIFY_X_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);

            Object* arg =  reinterpret_cast<Object*>(*StructurePointer);
            StructurePointer++;
	    if (! unify(X[i], arg))
	      {
		BACKTRACK;
	      }
	  }
	break;
	  
	case OPCODE(UNIFY_Y_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
            Object* arg =  reinterpret_cast<Object*>(*StructurePointer);
            StructurePointer++;
	    if (! unify(Y[i], arg))
	      {
		BACKTRACK;
	      }
	  }
	break; 
	  
	case OPCODE(UNIFY_VOID, ARGS(number)):
	  {
	    const word32 n = getNumber(programCounter);
	    StructurePointer += n;

	  }
	break; 
	  
	case OPCODE(SET_X_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
            Variable* var = heap.newVariable();
            var->setOccursCheck();
            X[i] = var;
            *StructurePointer = reinterpret_cast<heapobject>(var);
            StructurePointer++;         
	  }
	break; 

	case OPCODE(SET_Y_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
            Variable* var = heap.newVariable();
            var->setOccursCheck();
            Y[i] = var;
            *StructurePointer = reinterpret_cast<heapobject>(var);
	    StructurePointer++;
	  }
	break; 
	  
	case OPCODE(SET_X_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    *StructurePointer = reinterpret_cast<heapobject>(X[i]);
	    StructurePointer++;
	  }
	break; 
	  
	case OPCODE(SET_Y_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    *StructurePointer = reinterpret_cast<heapobject>(Y[i]);
	    StructurePointer++;
	  }
	break; 
	  
	case OPCODE(SET_X_OBJECT_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
            X[i] = heap.newObjectVariable();
            *StructurePointer = reinterpret_cast<heapobject>(X[i]);       
	    StructurePointer++;
	  }
	break; 
	  
	case OPCODE(SET_Y_OBJECT_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
            Y[i] = heap.newObjectVariable();
            *StructurePointer = reinterpret_cast<heapobject>(Y[i]);
	    StructurePointer++;
	  }
	break; 
	  
	case OPCODE(SET_X_OBJECT_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
           *StructurePointer = reinterpret_cast<heapobject>(X[i]);
            StructurePointer++;           
	  }
	break; 
	  
	case OPCODE(SET_Y_OBJECT_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    *StructurePointer = reinterpret_cast<heapobject>(Y[i]);
            StructurePointer++;  
	  }
	break; 
	  
	case OPCODE(SET_CONSTANT, ARGS(constant)):
	  {
	    const Object* c = getConstant(programCounter);
	    *StructurePointer = reinterpret_cast<heapobject>(c); 
	    StructurePointer++;
	  }
	break;
 
	case OPCODE(SET_INTEGER, ARGS(integer)):
	  {
	    const Object* c = heap.newInteger(getInteger(programCounter));
	    *StructurePointer = reinterpret_cast<heapobject>(c); 
	    StructurePointer++;
	  }
	break; 
	  
	case OPCODE(SET_DOUBLE, ARGS(double)):
	  {
	    const Object* c = heap.newDouble(getDouble(programCounter));
	    *StructurePointer = reinterpret_cast<heapobject>(c); 
	    StructurePointer++;
	  }
	break; 
	case OPCODE(SET_STRING, ARGS(register)):
	  {
	    char* c = (char*)programCounter;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    programCounter += size+1;
	    *StructurePointer = reinterpret_cast<heapobject>(str); 
	    StructurePointer++;
	  }
	break;
  

	case OPCODE(SET_VOID, ARGS(number)):
	  {
	    const word32 n = getNumber(programCounter);
            for (u_int count = 1; count <= n; count++)
              {
                Variable* var = heap.newVariable();
                var->setOccursCheck();
                *StructurePointer = reinterpret_cast<heapobject>(var);
                StructurePointer++;
              }               
	  }
	break; 
	  
	case OPCODE(SET_OBJECT_VOID, ARGS(number)):
	  {
	    const word32 n = getNumber(programCounter);
            for (u_int count = 1; count <= n; count++)
              {
                ObjectVariable* var = heap.newObjectVariable();
                *StructurePointer = reinterpret_cast<heapobject>(var);
                StructurePointer++;
              }                      
	  }
	break;

	case OPCODE(ALLOCATE, ARGS(number)):
	  {
	    getNumber(programCounter);
	  }
	break; 
	  
	case OPCODE(DEALLOCATE, ARGS()):
	  {
	  }
	break; 
	  
	case OPCODE(CALL_PREDICATE, ARGS(predatom, number, number)):
	  {
            inHead = false;

	    Atom* predicate = getPredAtom(programCounter);
	    const word32 arity = getNumber(programCounter);
	    getNumber(programCounter);
	    BUILD_CALL_TERM(predicate, arity, listElem);
	  }
	break; 
	  
	case OPCODE(CALL_ADDRESS, ARGS(address, number)):
	  {

            inHead = false;

	    const CodeLoc address = getCodeLoc(programCounter);
	    getNumber(programCounter);
            CodeLoc loc = address - Code::SIZE_OF_HEADER;
	    Atom* predicate = reinterpret_cast<Atom*>(getAddress(loc));
            const word32 arity = getNumber(loc);
	    BUILD_CALL_TERM(predicate, arity, listElem);
	  }
	break; 
	  
	case OPCODE(CALL_ESCAPE, ARGS(address, number)):
	  {
            const PredLoc address = getAddress(programCounter);
            getNumber(programCounter);
            Atom* predicate = predicates->getPredName(address, atoms);
            const word32 arity = predicates->getArity(address);
	    BUILD_CALL_TERM(predicate, arity, listElem);
	  }
	break;
	  
	case OPCODE(EXECUTE_PREDICATE, ARGS(predatom, number)):
	  {
	    Atom* predicate = getPredAtom(programCounter);
	    const word32 arity = getNumber(programCounter);
	    BUILD_CALL_TERM(predicate, arity, listElem);
	    *listElem = AtomTable::nil;
            instrlist = instrHead;
            return (RV_SUCCESS);
	  }
	break; 
	    
	case OPCODE(EXECUTE_ADDRESS, ARGS(address)):
	  {
	    const CodeLoc address = getCodeLoc(programCounter);
            CodeLoc loc = address - Code::SIZE_OF_HEADER;
	    Atom* predicate = reinterpret_cast<Atom*>(getAddress(loc));
            const word32 arity = getNumber(loc);
            BUILD_CALL_TERM(predicate, arity, listElem);
	    *listElem = AtomTable::nil;
            instrlist = instrHead;
            return (RV_SUCCESS);

          }
	break;
	  
	case OPCODE(EXECUTE_ESCAPE, ARGS(address)):
	  {
            const PredLoc address = getAddress(programCounter);
            Atom* predicate = predicates->getPredName(address, atoms);
            const word32 arity = predicates->getArity(address);   
	    BUILD_CALL_TERM(predicate, arity, listElem);
	    *listElem = AtomTable::nil;
            instrlist = instrHead;
            return (RV_SUCCESS);
	  }
	break;
	  
	case OPCODE(NOOP, ARGS()):
	  //
	  // Do nothing.
	  //
	  break;
	  
	case OPCODE(JUMP, ARGS(address)):
	  {
              BACKTRACK;
	  }
	break;

	case OPCODE(PROCEED, ARGS()):
	  *listElem = AtomTable::nil;
	  instrlist = instrHead;
          return (RV_SUCCESS);
	  break; 
  
	case OPCODE(FAIL, ARGS()):
	  {
	    Object* predicate = AtomTable::failure;
	    BUILD_CALL_TERM(predicate, 0, listElem);
	    *listElem = AtomTable::nil;
	    instrlist = instrHead;
	    return (RV_SUCCESS);
	  }
	  break;
  
	case OPCODE(HALT, ARGS()):
	  BACKTRACK;
	  break;
	  
	case OPCODE(EXIT, ARGS()):
	  BACKTRACK;
	  break;
	  
	case OPCODE(TRY_ME_ELSE, ARGS(number, offset)):
	  {
	    BACKTRACK;
	  }
	break; 
	  
	case OPCODE(RETRY_ME_ELSE, ARGS(offset)):
	  {
	    BACKTRACK;
	  }
	break;
	  
	case OPCODE(TRUST_ME_ELSE_FAIL, ARGS()):
	  {
	    BACKTRACK;
	  }
	  break; 
	  
	case OPCODE(TRY, ARGS(number, offset)):
	  {
	    BACKTRACK;
	  }
	break; 
	  
	case OPCODE(RETRY, ARGS(offset)):
	  {
	    BACKTRACK;
	  }
	break; 
	  
	case OPCODE(TRUST, ARGS(offset)):
	  {
	    BACKTRACK;
	  }
	break; 
	  
	case OPCODE(NECK_CUT, ARGS()):
	  {
            inHead = false;
	    Object* predicate = AtomTable::neckcut; // "$$neckcut"  PJR
            BUILD_CALL_TERM(predicate, 0, listElem);
	  }
	break; 
	  
	case OPCODE(GET_X_LEVEL, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    X[i] = heap.newVariable();
	    Object* predicate = atoms->add("$get_level");
	    Structure* u = heap.newStructure(1);
	    u->setFunctor(predicate);
	    u->setArgument(1, X[i]);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break; 
	  
	case OPCODE(GET_Y_LEVEL, ARGS(register)):
	  {
	    const word32 i = getRegister(programCounter);
	    Y[i] = heap.newVariable();
	    Object* predicate = atoms->add("$get_level");
	    Structure* u = heap.newStructure(1);
	    u->setFunctor(predicate);
	    u->setArgument(1, Y[i]);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break; 
	  
	case OPCODE(CUT, ARGS(register)):
	  {
            inHead = false;
	    const word32 i = getRegister(programCounter);
	    Object* predicate = AtomTable::cut_atom;
	    Structure* u = heap.newStructure(1);
	    u->setFunctor(predicate);
	    u->setArgument(1, Y[i]);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break; 
	  
	case OPCODE(SWITCH_ON_TERM, ARGS(register)):
	  {
	    BACKTRACK;
	  }
	break; 
	  
	case OPCODE(SWITCH_ON_CONSTANT, ARGS(register, tablesize)):
	  {
	    BACKTRACK;
	  }
	break;
	  
	case OPCODE(SWITCH_ON_STRUCTURE, ARGS(register, tablesize)):
	  {
	    BACKTRACK;
	  }
	break;
	  
	case OPCODE(SWITCH_ON_QUANTIFIER, ARGS(register, tablesize)):
	  {
	    BACKTRACK;
	  }
	break;

	case OPCODE(PSEUDO_INSTR0, ARGS(number)):
	  {
            inHead = false;
	    const word32 n = getNumber(programCounter);
	    Object* predicate = AtomTable::psi0_call; 
	    Object* psi = heap.newInteger(n);
	    Structure* u = heap.newStructure(1);
	    u->setFunctor(predicate);
	    u->setArgument(1, psi);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break;

	case OPCODE(PSEUDO_INSTR1, ARGS(number, register)):
	  {
	    //
	    // An instruction with 1 argument.
	    //

            inHead = false;
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    
	   Object* predicate = AtomTable::psi1_call;
           Object* psi = heap.newInteger(n);
           Object*& arg = DecPSIGetReg(i,X,Y);
           psi1NewVars(pseudo_instr1_array[n].mode, arg);
	   Structure* u = heap.newStructure(2);
	   u->setFunctor(predicate);
	   u->setArgument(1, psi);
	   u->setArgument(2, arg);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
          }
	break;

	case OPCODE(PSEUDO_INSTR2, ARGS(number, register, register)):
	  {
            inHead = false;
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);

	    Object*& arg1 = DecPSIGetReg(i,X,Y);
	    Object*& arg2 = DecPSIGetReg(j,X,Y);
	    psi2NewVars(pseudo_instr2_array[n].mode, arg1, arg2);

	    Object* predicate = AtomTable::psi2_call;;
	    Object* psi = heap.newInteger(n);
	    Structure* u = heap.newStructure(3);
	    u->setFunctor(predicate);
	    u->setArgument(1, psi);
	    u->setArgument(2, arg1);
	    u->setArgument(3, arg2);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break;

	case OPCODE(PSEUDO_INSTR3, ARGS(number, register, register, register)):
	  {
            inHead = false;
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    const word32 k = getRegister(programCounter);
	    
	    Object*& arg1 = DecPSIGetReg(i,X,Y);
	    Object*& arg2 = DecPSIGetReg(j,X,Y);
	    Object*& arg3 = DecPSIGetReg(k,X,Y);

	    psi3NewVars(pseudo_instr3_array[n].mode, arg1, arg2, arg3);
	    
	    Object* predicate = AtomTable::psi3_call;;
	    Object* psi = heap.newInteger(n);
	    Structure* u = heap.newStructure(4);
	    u->setFunctor(predicate);
	    u->setArgument(1, psi);
	    u->setArgument(2, arg1);
	    u->setArgument(3, arg2);
	    u->setArgument(4, arg3);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break;

	case OPCODE(PSEUDO_INSTR4, ARGS(number, register, register, register, register)):
	  {
            inHead = false;
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    const word32 k = getRegister(programCounter);
	    const word32 m = getRegister(programCounter);

	    Object*& arg1 = DecPSIGetReg(i,X,Y);
	    Object*& arg2 = DecPSIGetReg(j,X,Y);
	    Object*& arg3 = DecPSIGetReg(k,X,Y);
	    Object*& arg4 = DecPSIGetReg(m,X,Y);

	    psi4NewVars(pseudo_instr4_array[n].mode, arg1, arg2, arg3, arg4);

	    Object* predicate = AtomTable::psi4_call;;
	    Object* psi = heap.newInteger(n);
	    Structure* u = heap.newStructure(5);
	    u->setFunctor(predicate);
	    u->setArgument(1, psi);
	    u->setArgument(2, arg1);
	    u->setArgument(3, arg2);
	    u->setArgument(4, arg3);
	    u->setArgument(5, arg4);
	    Cons* l = heap.newCons();
	    l->setHead(u);
	    *listElem = l;
	    listElem = l->getTailAddress();
	  }
	break;

	case OPCODE(PSEUDO_INSTR5, ARGS(number, register, register, register, register, register)):
	  {
            inHead = false;
	    const word32 n = getNumber(programCounter);
	    const word32 i = getRegister(programCounter);
	    const word32 j = getRegister(programCounter);
	    const word32 k = getRegister(programCounter);
	    const word32 m = getRegister(programCounter);
	    const word32 o = getRegister(programCounter);

	    Object*& arg1 = DecPSIGetReg(i,X,Y);
	    Object*& arg2 = DecPSIGetReg(j,X,Y);
	    Object*& arg3 = DecPSIGetReg(k,X,Y);
	    Object*& arg4 = DecPSIGetReg(m,X,Y);
	    Object*& arg5 = DecPSIGetReg(o,X,Y);

           psi5NewVars(pseudo_instr5_array[n].mode, 
		       arg1, arg2, arg3, arg4, arg5);
	   Object* predicate = AtomTable::psi5_call;;
	   Object* psi = heap.newInteger(n);
	   Structure* u = heap.newStructure(6);
	   u->setFunctor(predicate);
	   u->setArgument(1, psi);
	   u->setArgument(2, arg1);
	   u->setArgument(3, arg2);
	   u->setArgument(4, arg3);
	   u->setArgument(5, arg4);
	   u->setArgument(6, arg5);
	   Cons* l = heap.newCons();
	   l->setHead(u);
	   *listElem = l;
	   listElem = l->getTailAddress();
	  }
	break;

	case OPCODE(UNIFY_CONSTANT, ARGS(constant)):
	  {
	    Object* c = getConstant(programCounter);
            Object* arg =  reinterpret_cast<Object*>(*StructurePointer);
            StructurePointer++;
	    if (! unify(c, arg))
	      {
		BACKTRACK;
	      }
	  }
	break;

	case OPCODE(UNIFY_INTEGER, ARGS(integer)):
	  {
	    Object* c = heap.newInteger(getInteger(programCounter));
            Object* arg =  reinterpret_cast<Object*>(*StructurePointer);
            StructurePointer++;
	    if (! unify(c, arg))
	      {
		BACKTRACK;
	      }
	  }
	break;
	
	case OPCODE(UNIFY_DOUBLE, ARGS(double)):
	  {
	    Object* c = heap.newDouble(getDouble(programCounter));
            Object* arg =  reinterpret_cast<Object*>(*StructurePointer);
            StructurePointer++;
	    if (! unify(c, arg))
	      {
		BACKTRACK;
	      }
	  }
	break;
	case OPCODE(UNIFY_STRING, ARGS()):
	  {
	    char* c = (char*)programCounter;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    programCounter += size+1;
            Object* arg =  reinterpret_cast<Object*>(*StructurePointer);
	    StructurePointer++;
	    if (! unify(str, arg))
	      {
		BACKTRACK;
	      }

	  }
	break;

	case OPCODE(UNIFY_X_REF, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    X[i] = reinterpret_cast<Object*>(*StructurePointer); 
            StructurePointer++;
	  }
	break;
	  
	case OPCODE(UNIFY_Y_REF, ARGS(register)):
	  {
	    const word32 i =getRegister(programCounter);
	    Y[i] = reinterpret_cast<Object*>(*StructurePointer);
	    StructurePointer++;
          }
	break;
	case OPCODE(DB_JUMP, ARGS(number, address, address, address)):
	  {
	    BACKTRACK;
	  }
	break;

	case OPCODE(DB_EXECUTE_PREDICATE, ARGS(predatom, number)):
	  {
	    Atom* predicate = getPredAtom(programCounter);
	    const word32 arity = getNumber(programCounter);
	    BUILD_CALL_TERM(predicate, arity, listElem);
	    *listElem = AtomTable::nil;
            instrlist = instrHead;
            return (RV_SUCCESS);
	  }
	break; 

  	case OPCODE(DB_EXECUTE_ADDRESS, ARGS(address)):
	  {
	    const CodeLoc address = getCodeLoc(programCounter);
            CodeLoc loc = address - Code::SIZE_OF_HEADER;
	    Atom* predicate = reinterpret_cast<Atom*>(getAddress(loc));
            const word32 arity = getNumber(loc);
            BUILD_CALL_TERM(predicate, arity, listElem);
	    *listElem = AtomTable::nil;
            instrlist = instrHead;
            return (RV_SUCCESS);

          }
	break;
	  
	case OPCODE(DB_PROCEED, ARGS()):
	  *listElem = AtomTable::nil;
	  instrlist = instrHead;
          return (RV_SUCCESS);
	  break; 

	default:
#ifdef WIN32
         (void)(TerminateProcess(GetCurrentProcess(), SIGILL));
#else
          (void)(kill(getpid(), SIGILL));
#endif
          break;
	}
    }
  return RV_EXIT;
}

Thread::ReturnValue  
Thread::next_instr(CodeLoc programCounter, Object* head, Object* &first, 
		   Object* &next)
{
  Object*          X[20];

  head = heap.dereference(head);

  //
  // Initialize the "X" registers with the args of the head
  //
  if (head->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, head);
      int n = static_cast<int>(str->getArity());
      while (n > 0)
        {
          X[n-1] = str->getArgument(n);
          n--;
        }
    }

  next = AtomTable::failure;

  while (true)
    {
      switch (getInstruction(programCounter))
	{
	case OPCODE(PUT_X_VARIABLE, ARGS(register, register)):
	case OPCODE(PUT_Y_VARIABLE, ARGS(register, register)):
	case OPCODE(PUT_X_VALUE, ARGS(register, register)):
	case OPCODE(PUT_Y_VALUE, ARGS(register, register)):
	case OPCODE(PUT_CONSTANT, ARGS(constant, register)):
	case OPCODE(PUT_INTEGER, ARGS(integer, register)):
	case OPCODE(PUT_DOUBLE, ARGS(double, register)):
	case OPCODE(PUT_STRING, ARGS(register)):
	case OPCODE(PUT_LIST, ARGS(register)):
	case OPCODE(PUT_STRUCTURE, ARGS(number, register)):
	case OPCODE(PUT_X_OBJECT_VARIABLE, ARGS(register, register)):
	case OPCODE(PUT_Y_OBJECT_VARIABLE, ARGS(register, register)):
	case OPCODE(PUT_X_OBJECT_VALUE, ARGS(register, register)):
	case OPCODE(PUT_Y_OBJECT_VALUE, ARGS(register, register)):
	case OPCODE(PUT_QUANTIFIER, ARGS(register)):
	case OPCODE(CHECK_BINDER, ARGS(register)):
	case OPCODE(PUT_SUBSTITUTION, ARGS(number, register)):
	case OPCODE(PUT_X_TERM_SUBSTITUTION, ARGS(register, register)):
	case OPCODE(PUT_Y_TERM_SUBSTITUTION, ARGS(register, register)):
	case OPCODE(PUT_INITIAL_EMPTY_SUBSTITUTION, ARGS(register)):
	case OPCODE(GET_X_VARIABLE, ARGS(register, register)):
	case OPCODE(GET_Y_VARIABLE, ARGS(register, register)):
	case OPCODE(GET_X_VALUE, ARGS(register, register)):
	case OPCODE(GET_Y_VALUE, ARGS(register, register)):
	case OPCODE(GET_CONSTANT, ARGS(constant, register)):
	case OPCODE(GET_INTEGER, ARGS(integer, register)):
	case OPCODE(GET_DOUBLE, ARGS(double, register)):
	case OPCODE(GET_STRING, ARGS(register)):
	case OPCODE(GET_LIST, ARGS(register)):
	case OPCODE(GET_STRUCTURE, ARGS(constant, number, register)):
	case OPCODE(GET_STRUCTURE_FRAME, ARGS(number, register)):
	case OPCODE(GET_X_OBJECT_VARIABLE, ARGS(register, register)):
	case OPCODE(GET_Y_OBJECT_VARIABLE, ARGS(register, register)):
	case OPCODE(GET_X_OBJECT_VALUE, ARGS(register, register)):
	case OPCODE(GET_Y_OBJECT_VALUE, ARGS(register, register)):
	case OPCODE(UNIFY_X_VARIABLE, ARGS(register)):
	case OPCODE(UNIFY_Y_VARIABLE, ARGS(register)):
	case OPCODE(UNIFY_X_REF, ARGS(register)):
	case OPCODE(UNIFY_Y_REF, ARGS(register)):
	case OPCODE(UNIFY_X_VALUE, ARGS(register)):
	case OPCODE(UNIFY_Y_VALUE, ARGS(register)):
	case OPCODE(UNIFY_VOID, ARGS(number)):
	case OPCODE(SET_X_VARIABLE, ARGS(register)):
	case OPCODE(SET_Y_VARIABLE, ARGS(register)):
	case OPCODE(SET_X_VALUE, ARGS(register)):
	case OPCODE(SET_Y_VALUE, ARGS(register)):
	case OPCODE(SET_X_OBJECT_VARIABLE, ARGS(register)):
	case OPCODE(SET_Y_OBJECT_VARIABLE, ARGS(register)):
	case OPCODE(SET_X_OBJECT_VALUE, ARGS(register)):
	case OPCODE(SET_Y_OBJECT_VALUE, ARGS(register)):
	case OPCODE(SET_CONSTANT, ARGS(constant)):
	case OPCODE(SET_INTEGER, ARGS(integer)):
	case OPCODE(SET_DOUBLE, ARGS(double)):
	case OPCODE(SET_STRING, ARGS()):
	case OPCODE(SET_VOID, ARGS(number)):
	case OPCODE(SET_OBJECT_VOID, ARGS(number)):
	case OPCODE(ALLOCATE, ARGS(number)):
	case OPCODE(DEALLOCATE, ARGS()):
	case OPCODE(CALL_PREDICATE, ARGS(predatom, number, number)):
	case OPCODE(CALL_ADDRESS, ARGS(address, number)):
	case OPCODE(CALL_ESCAPE, ARGS(address, number)):
	case OPCODE(EXECUTE_PREDICATE, ARGS(predatom, number)):
	case OPCODE(EXECUTE_ADDRESS, ARGS(address)):
	case OPCODE(EXECUTE_ESCAPE, ARGS(address)):
	case OPCODE(NOOP, ARGS()):
	case OPCODE(PROCEED, ARGS()):
	case OPCODE(HALT, ARGS()):
	case OPCODE(EXIT, ARGS()):
	case OPCODE(NECK_CUT, ARGS()):
	case OPCODE(GET_X_LEVEL, ARGS(register)):
	case OPCODE(GET_Y_LEVEL, ARGS(register)):
	case OPCODE(CUT, ARGS(register)):
	case OPCODE(PSEUDO_INSTR0, ARGS(number)):
	case OPCODE(PSEUDO_INSTR1, ARGS(number, register)):
	case OPCODE(PSEUDO_INSTR2, ARGS(number, register, register)):
	case OPCODE(PSEUDO_INSTR3, ARGS(number, register, register, register)):
	case OPCODE(PSEUDO_INSTR4, ARGS(number, register, register, register, register)):
	case OPCODE(PSEUDO_INSTR5, ARGS(number, register, register, register, register, register)):
	case OPCODE(UNIFY_CONSTANT, ARGS(constant)):
	case OPCODE(UNIFY_INTEGER, ARGS(integer)):
	case OPCODE(UNIFY_DOUBLE, ARGS(double)):
	case OPCODE(UNIFY_STRING, ARGS()):
          {
	    first = heap.newInteger(
                         reinterpret_cast<long>(programCounter - Code::SIZE_OF_INSTRUCTION));
             return(RV_SUCCESS);
          }
        break;

	case OPCODE(FAIL, ARGS()):
          {
	    if (next->isNumber())
              {
                programCounter = reinterpret_cast<CodeLoc>(next->getInteger());
              }
            else
              {
                BACKTRACK;
              }
          }
        break;

	case OPCODE(JUMP, ARGS(address)):
	  {
            const CodeLoc address = getCodeLoc(programCounter);
            programCounter = address;
	  }
	break;
	case OPCODE(TRY_ME_ELSE, ARGS(number, offset)):
	  {
             getNumber(programCounter);
             const word32 label = getOffset(programCounter);
	     next = heap.newInteger(reinterpret_cast<long>(programCounter + label));
	  }
	break; 
	  
	case OPCODE(RETRY_ME_ELSE, ARGS(offset)):
	  {
             const word32 label = getOffset(programCounter);
	     next = heap.newInteger(reinterpret_cast<long>(programCounter + label));
	  }
	break;

	case OPCODE(TRUST_ME_ELSE_FAIL, ARGS()):
          {
          }
        break;
	  
	case OPCODE(TRY, ARGS(number, offset)):
	  {
             getNumber(programCounter);
             const word32 label = getOffset(programCounter);
	     next = heap.newInteger(reinterpret_cast<long>(programCounter));
             programCounter += label;
	  }
	break; 
	  
	case OPCODE(RETRY, ARGS(offset)):
	  {
            const word32 label = getOffset(programCounter);
	    next = heap.newInteger(reinterpret_cast<long>(programCounter));
            programCounter += label;
	  }
	break; 
	  
	case OPCODE(TRUST, ARGS(offset)):
	  {
            const word32 label = getOffset(programCounter);
            programCounter += label;
	  }
	break; 
	  
	case OPCODE(SWITCH_ON_TERM, ARGS(register)):
	  {
            const word32 i = getRegister(programCounter);
	    PrologValue pval(X[i]);
            heap.prologValueDereference(pval);          
            CodeLoc loc =
              programCounter + Code::SIZE_OF_OFFSET * pval.getTerm()->switchOffset();
            const word32 offset = getOffset(loc);
            if (offset == Code::FAIL)
              {
                BACKTRACK;
              }
            else
              {
                programCounter += 6 * Code::SIZE_OF_OFFSET + offset;
              }              
	  }
	break; 
	  
	case OPCODE(SWITCH_ON_CONSTANT, ARGS(register, tablesize)):
	  {
            const word32 i = getRegister(programCounter);
            const word32 n = getTableSize(programCounter);

            const ConstantTable CodeConstTable(*code, programCounter, n);

	    Object* val = heap.dereference(X[i]);

            ConstEntry constant; 
	    if (val->isAtom())
	      {
		constant.assign(reinterpret_cast<wordptr>(val), 
				ConstEntry::ATOM_TYPE);
	      }
	    else
	      {
		assert(val->isNumber());
		constant.assign(val->getInteger(), 
				ConstEntry::INTEGER_TYPE);
	      }

            const word32 label = CodeConstTable.lookUp(constant);
            if (label == Code::FAIL)
              {
                BACKTRACK;
              }
            else
              {
                programCounter += label;
              }            
	  }
	break;
	  
	case OPCODE(SWITCH_ON_STRUCTURE, ARGS(register, tablesize)):
	  {
            const word32 i = getRegister(programCounter);
            const word32 n = getTableSize(programCounter);

            const StructureTable CodeStructTable(*code, programCounter, n);

	    Object* val = heap.dereference(X[i]);
            word32 arity;
            Object* func;

            if (val->isStructure())
              {
                Structure* str = OBJECT_CAST(Structure*, val);
                arity = static_cast<word32>(str->getArity());
                func = heap.dereference(str->getFunctor());
                if (!func->isAtom())
                  {
                    func = AtomTable::dollar;
                    arity = 0;
                  }
              }
            else          
              {
                assert(val->isSubstitution());
                PrologValue pval(val);

                heap.prologValueDereference(pval);
                assert(pval.getTerm()->isStructure());
                Structure* str = OBJECT_CAST(Structure*,pval.getTerm());
                arity = static_cast<word32>(str->getArity());
                PrologValue pfunc(pval.getSubstitutionBlockList(),
                                  str->getFunctor());
                heap.prologValueDereference(pfunc);
                func = pfunc.getTerm();
                if (!func->isAtom())
                  {
                    func = AtomTable::dollar;
                    arity = 0;
                  }
              }                                

            StructEntry structure(reinterpret_cast<wordptr>(func), arity);

            const word32 label = CodeStructTable.lookUp(structure);

            if (label == Code::FAIL)
              {
                BACKTRACK;
              }
            else
              {
                programCounter += label;
              }             
	  }
	break;
	  
	case OPCODE(SWITCH_ON_QUANTIFIER, ARGS(register, tablesize)):
	  {
            const word32 i = getRegister(programCounter);
            const word32 n = getTableSize(programCounter);

            const StructureTable CodeQuantTable(*code, programCounter, n);

	    PrologValue pval(X[i]);

            heap.prologValueDereference(pval);

            assert(pval.getTerm()->isQuantifiedTerm());

            QuantifiedTerm* quantterm
              = OBJECT_CAST(QuantifiedTerm*, pval.getTerm());
            word32 arity
              = static_cast<word32>(quantterm->getBoundVars()->boundListLength());


            PrologValue quant(pval.getSubstitutionBlockList(),
                              quantterm->getQuantifier());

	    heap.prologValueDereference(quant);
            Object* q = quant.getTerm();

            if (!q->isAtom() || arity == WORD32_MAX)
              {
                q = AtomTable::dollar;
                arity = 0;
              }
                                                                                                            
            StructEntry structure(reinterpret_cast<wordptr>(q),  arity);

            const word32 label = CodeQuantTable.lookUp(structure);
            if (label == Code::FAIL)
              {
                BACKTRACK;
              }
            else
              {
                programCounter += label;
              }             
	  }
	break;

	default:
#ifdef WIN32
          (void)(TerminateProcess(GetCurrentProcess(), SIGILL));
#else
          (void)(kill(getpid(), SIGILL));
#endif
          break;
	}
    }
  return RV_EXIT;
}

//
// psi_decompile(codeptr, headterm, bodylist)
// Returns the list of body "calls" for the body of the clause that starts at 
// codeptr and whose head matches headterm.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_decompile(Object*& o1, Object*& o2, Object*& o3)
{
  Object* co = heap.dereference(o1);
  assert(co->isNumber());
  assert(co->getInteger() != 0);
  
  LinkedClause* clause = (LinkedClause*)(co->getInteger());
  CodeLoc pc = clause->getCodeBlock()->getCode();
  return(decompile(pc, o2, o3));
}

//
// psi_next_instr(codeptr, headterm, codeptr, codeptr)
// return the loc of current instr and next instr (or fail if no 
// next instr.
// mode(in,in,out,out)
//
Thread::ReturnValue
Thread::psi_next_instr(Object*& o1, Object*& o2, Object*& o3, Object*& o4)
{
  Object* co = heap.dereference(o1);
  assert(co->isNumber());
  CodeLoc pc = reinterpret_cast<CodeLoc>(co->getInteger());

  return(next_instr(pc, o2, o3, o4));
}



