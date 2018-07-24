// arithmetic.cc -  definitions for pseudo-instructions for arithmetic
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
// $Id: arithmetic.cc,v 1.10 2006/01/31 23:17:49 qp Exp $

#include <math.h>
#ifdef WIN32
        #define M_PI       3.14159265358979323846
        #define M_E        2.71828182845904523536
        //We'll have to use our own function
        double round(double number)
        {
                return number < 0.0 ? ceil(number-0.5) : floor(number+0.5);
        }
#endif

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

#define ARITH_INTEGER_TYPE    0
#define ARITH_DOUBLE_TYPE 1


typedef struct
{ int   type;                           /* type of number */
  union { 
          long  i;                      /* integer */
          double d;                     /* double */
        } value;
} number;

#define IS_INT(x) (x.type == ARITH_INTEGER_TYPE)
#define BOTH_INTS(x,y) ((x.type == ARITH_INTEGER_TYPE) && (y.type == ARITH_INTEGER_TYPE)) 
#define GET_INT_VAL(x) (x.value.i)
#define GET_DOUBLE_VAL(x) ((x.type == ARITH_INTEGER_TYPE) ? (double)(x.value.i) : x.value.d)
#define MAKE_INT(x, v) {x.type = ARITH_INTEGER_TYPE; x.value.i = v;}
#define MAKE_DOUBLE(x, v) {x.type = ARITH_DOUBLE_TYPE; x.value.d = v;}  
/*
#define MAKE_DOUBLE(x, v)                                  	\
do {                                                       	\
  long n = (long)(v);						\
  if ((v) == (double)n)						\
    { x.type = ARITH_INTEGER_TYPE; x.value.i = n; }		\
  else								\
    {x.type = ARITH_DOUBLE_TYPE; x.value.d = (v);}		\
} while (0)
*/

#define IS_ZERO(x) ((x.type == ARITH_INTEGER_TYPE) && (x.value.i == 0))

number zero = {ARITH_INTEGER_TYPE, {0}};
//
// arithEvaluate is an auxilary function used by arithmetical pseudo
//instructions to carry out the evaluation of expressions.
//
number
arithEvaluate(PrologValue& val, Heap& heap, ErrorValue& error_value)
{
  if (val.getTerm()->isInteger())
    {
      number y;
      MAKE_INT(y, val.getTerm()->getInteger());
      return y;
    }
  else if (val.getTerm()->isDouble())
    {
      number y;
      MAKE_DOUBLE(y, val.getTerm()->getDouble());
      return y;
    }
  else if (val.getTerm()->isAtom())
    { 
      if (val.getTerm() == AtomTable::pi)
        {
          number y;
          MAKE_DOUBLE(y, M_PI); // PI
          return y;
        }
      if (val.getTerm() == AtomTable::e)
        {
          number y;
          MAKE_DOUBLE(y, M_E); // E
          return y;
        }
      else
	{
	  error_value = EV_TYPE;
	  return zero;
	}
    }      
  else if (val.getTerm()->isStructure())
    {
      number res1, res2;
      
      Structure *structure = OBJECT_CAST(Structure *, val.getTerm());
      
      size_t arity = structure->getArity();
      
      //
      // calcualte the values of the arguments
      //
      if (arity == 1)
	{
	  PrologValue val1(val.getSubstitutionBlockList(),
			   structure->getArgument(1));	  
	  heap.prologValueDereference(val1);
	  res1 = arithEvaluate(val1, heap, error_value);
	  
	  if (error_value != EV_NO_ERROR)
	    {
	      return zero;
	    }
	}
      else if (arity == 2)
	{
	  PrologValue val1(val.getSubstitutionBlockList(),
			   structure->getArgument(1));	  
	  heap.prologValueDereference(val1);
	  res1 = arithEvaluate(val1, heap, error_value);
	  PrologValue val2(val.getSubstitutionBlockList(),
			   structure->getArgument(2));	  
	  heap.prologValueDereference(val2);
	  res2 = arithEvaluate(val2, heap, error_value);
	  
	  if (error_value != EV_NO_ERROR)
	    {
	      return zero;
	    }
	}
      else // illegal number of arguments
	{
	  error_value = EV_TYPE;
	  return zero;
	}
      
      //
      // evaluate the expression according to the operator
      //
      PrologValue funpv(val.getSubstitutionBlockList(),
			structure->getFunctor());	  
      heap.prologValueDereference(funpv);
      Object* fun = funpv.getTerm();
      
      assert(fun->isAtom());
      
      Atom *op = OBJECT_CAST(Atom *, fun);
      if (op == AtomTable::plus)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) + GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      MAKE_DOUBLE(res, GET_DOUBLE_VAL(res1) + GET_DOUBLE_VAL(res2));
	      return res;
            }
	}
      else if (op == AtomTable::minus)
	{
	  if (arity == 1)
	    {
              if IS_INT(res1)
                {
	          number res;
                  MAKE_INT(res, - GET_INT_VAL(res1));
	          return res;
                }
              else
                {
	          number res;
	          MAKE_DOUBLE(res, - GET_DOUBLE_VAL(res1));
	          return res;
                }
            }
	  else if (arity == 2)
	    {
	      if BOTH_INTS(res1, res2)
                {
	          number res;
                  MAKE_INT(res, GET_INT_VAL(res1) - GET_INT_VAL(res2));
	          return res;
                }
              else
                {
	          number res;
	          MAKE_DOUBLE(res, GET_DOUBLE_VAL(res1) - GET_DOUBLE_VAL(res2));
	          return res;
                }
	    }
	  else
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	}
      else if (op == AtomTable::multiply)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) * GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      number res;
	      errno = 0;
	      MAKE_DOUBLE(res, GET_DOUBLE_VAL(res1) * GET_DOUBLE_VAL(res2));
	      if (errno != 0)
	        {
	          error_value = EV_RANGE;
	          return zero;
	        }
	      return res;
            }
	}
      else if (op == AtomTable::maxi)
	{
	  if (GET_DOUBLE_VAL(res1) > GET_DOUBLE_VAL(res2))
	    return res1;
	  else
	    return res2;
	}      
      else if (op == AtomTable::min)
	{
	  if (GET_DOUBLE_VAL(res1) < GET_DOUBLE_VAL(res2))
	    return res1;
	  else
	    return res2;
	}      
       else if (op == AtomTable::abs)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
          if IS_INT(res1)
            {
	      number res;
              MAKE_INT(res, abs(GET_INT_VAL(res1)));
	      return res;
            }
          else
            {
	      number res;
	      MAKE_DOUBLE(res, fabs(GET_DOUBLE_VAL(res1)));
	      return res;
            }
        }
      else if (op == AtomTable::round)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
          if IS_INT(res1)
            {
	      return res1;
            }
           else
            {
	      number res;
              MAKE_INT(res, (long)round(GET_DOUBLE_VAL(res1)));
	      return res;
            }
        }
      else if (op == AtomTable::floor)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
          if IS_INT(res1)
            {
	      return res1;
            }
           else
            {
	      number res;
              MAKE_INT(res, (long)floor(GET_DOUBLE_VAL(res1)));
	      return res;
            }
        }
      else if (op == AtomTable::truncate)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
          if IS_INT(res1)
            {
	      return res1;
            }
           else
            {
	      number res;
              double num = GET_DOUBLE_VAL(res1);
              if (num > 0) {
                MAKE_INT(res, (long)floor(num));
              }
              else {
                MAKE_INT(res, (long)ceil(num));
              }
	      return res;
            }
        }
       else if (op == AtomTable::ceiling)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
          if IS_INT(res1)
            {
	      return res1;
            }
           else
            {
	      number res;
              MAKE_INT(res, (long)ceil(GET_DOUBLE_VAL(res1)));
	      return res;
            }
        }
      else if (op == AtomTable::sqrt)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  MAKE_DOUBLE(res, sqrt(GET_DOUBLE_VAL(res1)));
	  return res;
        }
      else if (op == AtomTable::sin)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  MAKE_DOUBLE(res, sin(GET_DOUBLE_VAL(res1)));
	  return res;
        }
      else if (op == AtomTable::cos)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  MAKE_DOUBLE(res, cos(GET_DOUBLE_VAL(res1)));
	  return res;
        }
      else if (op == AtomTable::tan)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  errno = 0;
	  MAKE_DOUBLE(res, tan(GET_DOUBLE_VAL(res1)));
	  if (errno != 0)
	    {
	      error_value = EV_RANGE;
	      return zero;
	    }
	  return res;
        }
      else if (op == AtomTable::asin)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  errno = 0;
	  MAKE_DOUBLE(res, asin(GET_DOUBLE_VAL(res1)));
	  if (errno != 0)
	    {
	      error_value = EV_RANGE;
	      return zero;
	    }
	  return res;
        }
      else if (op == AtomTable::acos)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  errno = 0;
	  MAKE_DOUBLE(res, acos(GET_DOUBLE_VAL(res1)));
	  if (errno != 0)
	    {
	      error_value = EV_RANGE;
	      return zero;
	    }
	  return res;
        }
      else if (op == AtomTable::atan)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  errno = 0;
	  MAKE_DOUBLE(res, atan(GET_DOUBLE_VAL(res1)));
	  if (errno != 0)
	    {
	      error_value = EV_RANGE;
	      return zero;
	    }
	  return res;
        }
      else if (op == AtomTable::log)
        {
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  number res;
	  errno = 0;
	  MAKE_DOUBLE(res, log(GET_DOUBLE_VAL(res1)));
	  if (errno != 0)
	    {
	      error_value = EV_RANGE;
	      return zero;
	    }
	  return res;
	}
      else if (op == AtomTable::divide)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if IS_ZERO(res2)
	    {
	      error_value = EV_ZERO_DIVIDE;
	      return zero;
	    }
	  number res;
          errno = 0;
          MAKE_DOUBLE(res, (double)GET_DOUBLE_VAL(res1) / (double)GET_DOUBLE_VAL(res2));
          if (errno != 0)
            {
	      error_value = EV_RANGE;
	      return zero;
            }
	  return res;
	}
      else if (op == AtomTable::intdivide)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if IS_ZERO(res2)
	    {
	      error_value = EV_ZERO_DIVIDE;
	      return zero;
	    }
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) / GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else if (op == AtomTable::mod)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }	      
	  if IS_ZERO(res2)
	    {
	      error_value = EV_ZERO_DIVIDE;
	      return zero;
	    }

	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) % GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else if (op == AtomTable::power)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if (BOTH_INTS(res1, res2) && (GET_INT_VAL(res2) >= 0))
            {
	      number res;
              MAKE_INT(res, (long)::pow(GET_INT_VAL(res1), GET_INT_VAL(res2)));
	      return res;
            }
          else
            {
	      number res;
	      double x = GET_DOUBLE_VAL(res1);
	      double y = GET_DOUBLE_VAL(res2);
	      errno = 0;
	      double z = pow(x, y);
	      if (errno != 0)
	        {
	          error_value = EV_RANGE;
	          return zero;
	        }
	  
	      MAKE_DOUBLE(res, z);
	      return res;
            }
	}
      else if (op == AtomTable::bitwiseand)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) & GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else if (op == AtomTable::bitwiseor)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) | GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else if (op == AtomTable::shiftl)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) << GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else if (op == AtomTable::shiftr)
	{
	  if (arity != 2)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if BOTH_INTS(res1, res2)
            {
	      number res;
              MAKE_INT(res, GET_INT_VAL(res1) >> GET_INT_VAL(res2));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else if (op == AtomTable::bitneg)
	{
	  if (arity != 1)
	    {
	      error_value = EV_TYPE;
	      return zero;
	    }
	  if IS_INT(res1)
            {
	      number res;
              MAKE_INT(res, ~ GET_INT_VAL(res1));
	      return res;
            }
          else
            {
	      error_value = EV_TYPE;
	      return zero;
            }
	}
      else 
	{
	  error_value = EV_TYPE;
	  return zero;
	}
    }
  else if (val.getTerm()->isVariable())
    {
      error_value = EV_INST;
      return zero;
    }
  else
    {
      error_value = EV_TYPE;
      return zero;
    }

  return zero;
}

//
// psi_is(Out, Exp)
// mode(out,in)
//
Thread::ReturnValue
Thread::psi_is(Object *& object1, Object *& object2)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;
  
  PrologValue val(object2);
  heap.prologValueDereference(val);
  number result = arithEvaluate(val, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }
  else
    {
      if IS_INT(result)
        object1 = heap.newInteger(GET_INT_VAL(result));
      else
        object1 = heap.newDouble(GET_DOUBLE_VAL(result));

      return RV_SUCCESS;
    }
}

//
// psi_less(A, B)
// mode(in,in)
// true iff A < B
//
Thread::ReturnValue
Thread::psi_less(Object *& object1, Object *& object2)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  number res1 = arithEvaluate(pval1, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  number res2 = arithEvaluate(pval2, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }
  
  //
  // The two args evaluate correctly so test them
  //
  return BOOL_TO_RV(GET_DOUBLE_VAL(res1) < GET_DOUBLE_VAL(res2));
}

//
// psi_lesseq(A, B)
// mode(in,in)
// true iff A <= B
//
Thread::ReturnValue
Thread::psi_lesseq(Object *& object1, Object *& object2)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  number res1 = arithEvaluate(pval1, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  number res2 = arithEvaluate(pval2, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }
  
  //
  // The two args evaluate correctly so test them
  //
  return BOOL_TO_RV(GET_DOUBLE_VAL(res1) <= GET_DOUBLE_VAL(res2));

}


//
// psi_add(A,B,Sum)
// mode(in,in,out)
// Sum = A + B
//
Thread::ReturnValue
Thread::psi_add(Object *& object1, Object *& object2, Object *& object3)
{
  // Each thread has an error_value member.
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  number res1 = arithEvaluate(pval1, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  number res2 = arithEvaluate(pval2, heap, error_value);
 
  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }

  //
  // The two args evaluate correctly so add them
  //
  if BOTH_INTS(res1, res2)
    {
      object3 = heap.newInteger(GET_INT_VAL(res1) + GET_INT_VAL(res2));
     }
   else
     {
      object3 = heap.newDouble(GET_DOUBLE_VAL(res1) + GET_DOUBLE_VAL(res2));
     }

  return RV_SUCCESS;
}

//
// psi_subtract(A,B,Diff)
// mode(in,in,out)
// Diff = A - B
//
Thread::ReturnValue
Thread::psi_subtract(Object *& object1, Object *& object2, Object *& object3)
{
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  number res1 = arithEvaluate(pval1, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);
  number res2 = arithEvaluate(pval2, heap, error_value);

  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 2);
    }

  //
  // The two args evaluate correctly so subtract them
  //
  if BOTH_INTS(res1, res2)
    {
      object3 = heap.newInteger(GET_INT_VAL(res1) - GET_INT_VAL(res2));
     }
   else
     {
      object3 = heap.newDouble(GET_DOUBLE_VAL(res1) - GET_DOUBLE_VAL(res2));
     }

  return RV_SUCCESS;
}


//
// psi_increment(A,B)
// mode(in,out)
// B = A + 1
//
Thread::ReturnValue
Thread::psi_increment(Object *& object1, Object *& object2)
{
  error_value = EV_NO_ERROR;
  
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  number res1 = arithEvaluate(pval1, heap, error_value);
     
    if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  //
  // The arg evaluate correctly so increment it
  //
  if IS_INT(res1)
    {
      object2 = heap.newInteger(GET_INT_VAL(res1) + 1);
     }
   else
     {
      object2 = heap.newDouble(GET_DOUBLE_VAL(res1) + 1);
     }

  return RV_SUCCESS;
}

//
// psi_decrement(A,B)
// mode(in,out)
// B = A - 1
//
Thread::ReturnValue
Thread::psi_decrement(Object *& object1, Object *& object2)
{
  error_value = EV_NO_ERROR;

  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  number res1 = arithEvaluate(pval1, heap, error_value);
   
  if (error_value != EV_NO_ERROR)
    {
      PSI_ERROR_RETURN(error_value, 1);
    }

  //
  // The arg evaluate correctly so decrement it
  //
  if IS_INT(res1)
    {
      object2 = heap.newInteger(GET_INT_VAL(res1) - 1);
     }
   else
     {
      object2 = heap.newDouble(GET_DOUBLE_VAL(res1) + 1);
     }

  return RV_SUCCESS;
}

//
// psi_hash_double(A,B)
// mode(in,out)
// 
//
Thread::ReturnValue
Thread::psi_hash_double(Object *& object1, Object *& object2)
{
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  Object* dval = pval1.getTerm();

  if (!dval->isDouble())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  double d = dval->getDouble();
  u_int x[2];
  memcpy(x, &d, sizeof(double));
  word32 v = (x[0] | x[1]) & ~(x[0] & x[1]);
  object2 = heap.newInteger(v);
  return RV_SUCCESS;
}
