// delay_escape.cc - General delay mechanism.
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
// $Id: delay_escape.cc,v 1.7 2006/01/31 23:17:49 qp Exp $

//#include "atom_table.h"
#include "global.h"
#include "thread_qp.h"

//
// psi_delay(variable, term)
// Delay the call to term and associate the problem with variable.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_delay(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  assert(val1->isAnyVariable());
  
  //
  // Delay the problem.
  //
  delayProblem(val2, val1);
  
  //
  // Complete operation.
  //
  return(RV_SUCCESS);
}

//
// psi_delayed_problems_for_var(variable, term)
// Return the list of delayed problems associated with the given variable.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_delayed_problems_for_var(Object *& object1, Object *& object2)
{
  Object* o = object1;
  Object* delays = AtomTable::nil;

  assert(o != NULL);
  
  while (o->isAnyVariable()) 
    {
      delays = OBJECT_CAST(Reference*, o)->getDelays();
      Object* n = OBJECT_CAST(Reference*, o)->getReference();
      if ((n == o) || !delays->isNil())
	{
	  object2 = delays;
	  return(RV_SUCCESS);
	}
      o = n;
    }
  object2 = delays;
  return(RV_SUCCESS);
}

//
// psi_get_bound_structure(variable, variable)
// Return the dereferenced variable as the argument of a "bound" structure.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_bound_structure(Object *& object1, Object *& object2)
{

  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isAnyVariable());
  if (val1->isVariable())
    {
      val1 = addExtraInfo(OBJECT_CAST(Variable*, val1));
    }
  Structure* newstruct = heap.newStructure(1);
  newstruct->setFunctor(atoms->add("bound"));
  newstruct->setArgument(1,val1);
  Structure* boundstruct = heap.newStructure(1);
  boundstruct->setFunctor(atoms->add("$bound"));
  boundstruct->setArgument(1,newstruct);

  object2 = boundstruct;
  return(RV_SUCCESS);
}

//
// psi_psidelay_resume
// Restore the thread state after a retry delay from a pseudo instruction
// mode()
//
Thread::ReturnValue
Thread::psi_psidelay_resume(void)
{
  assert(false);
  status.resetNeckCutRetry();
  RestoreXRegisters();
  programCounter = savedPC;
  return(RV_SUCCESS);
}


//
// psi_get_delays(delays,type,avoid)
// Return the list of delayed problems of given type
// type is 'all' or 'unify' other than those in avoid.
// mode(out,in,in)
// 

Thread::ReturnValue
Thread::psi_get_delays(Object *& delaylist, Object*& type, Object*& avoid)
{
  bool unify_only = (type->variableDereference() == atoms->add("unify"));
  Object *delays = AtomTable::nil;
  Object *avoid_list = avoid->variableDereference();


  for (Object *global_delays = 
	 ipTable.getImplicitPara(AtomTable::delays)->variableDereference();
       global_delays->isCons();
       global_delays = OBJECT_CAST(Cons *, global_delays)->getTail()->variableDereference())
    {
      assert(OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference()->isStructure());

      Structure *delay
	= OBJECT_CAST(Structure*, OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference());

      assert(delay->getArity() == 2);
      Object* status = delay->getArgument(1)->variableDereference();
      if (!status->isVariable() || !OBJECT_CAST(Variable*,status)->isFrozen())
	{
	  continue;
	}
      Object* var = delay->getArgument(2);
      Object* vdelays;
      (void)psi_delayed_problems_for_var(var, vdelays);
      for (; vdelays->isCons(); 
	   vdelays = OBJECT_CAST(Cons*, 
				 vdelays)->getTail()->variableDereference())
	{
	  Object* vd = 
	    OBJECT_CAST(Cons*, vdelays)->getHead()->variableDereference();
	  assert(vd->isStructure());
	  Structure* vdstruct = OBJECT_CAST(Structure *, vd);
	  assert(vdstruct->getArity() == 2);
	  Object* vdstatus = vdstruct->getArgument(1)->variableDereference();
	  assert(vdstatus->isVariable());
	  if (!OBJECT_CAST(Variable*,vdstatus)->isFrozen())
	    {
	      continue;
	    }
	  Object* problem = vdstruct->getArgument(2)->variableDereference();
          if (avoid_list->inList(problem))
	    {
	      continue;
	    }
	  if (unify_only)
	    {
	      if (!problem->isStructure())
		{
		  continue;
		}
	      Structure* pstruct = OBJECT_CAST(Structure*, problem);
	      if (pstruct->getArity() == 2 && 
		  pstruct->getFunctor() == AtomTable::equal)
		{
		  delays = heap.newCons(problem, delays);
		}
	    }
	  else
	    {
	      if (!problem->isStructure())
		{
		  delays = heap.newCons(problem, delays);
		}
	      else
		{
		  Structure* pstruct = OBJECT_CAST(Structure*, problem);
		  if (pstruct->getArity() == 2 &&
		      pstruct->getFunctor() == atoms->add("delay_until") &&
		      pstruct->getArgument(1)->variableDereference()->isStructure())
		    {
		      Structure* arg1struct = OBJECT_CAST(Structure*, pstruct->getArgument(1)->variableDereference());
		      if (arg1struct->getArity() == 1 &&
			  arg1struct->getFunctor() == atoms->add("$bound"))
			{
			  Structure* newpstruct = heap.newStructure(2);
			  newpstruct->setFunctor(pstruct->getFunctor());
			  newpstruct->setArgument(1,arg1struct->getArgument(1));
			  newpstruct->setArgument(2,pstruct->getArgument(2));
			  delays = heap.newCons(newpstruct, delays);
			  continue;
			}
		    }		      
		  delays = heap.newCons(problem, delays);
		}
	    }
	}
    }
  delaylist = delays;
  return RV_SUCCESS;
} 



//
// psi_bound(term)
// test if term is bound to something
// mode(in)
//
Thread::ReturnValue
Thread::psi_bound(Object *& object1)
{  
    Object* deref = object1->variableDereference();
    return BOOL_TO_RV(deref != object1);
}

//
// Remove any solved problems associated with any variables.
//
Thread::ReturnValue
Thread::psi_compress_var_delays()
{
  for (Object *global_delays = 
	 ipTable.getImplicitPara(AtomTable::delays)->variableDereference();
       global_delays->isCons();
       global_delays = OBJECT_CAST(Cons *, global_delays)->getTail()->variableDereference())
    {
      assert(OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference()->isStructure());
      
      Structure *delay = OBJECT_CAST(Structure*, OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference());
      
      assert(delay->getArity() == 2);
      Object* status = delay->getArgument(1)->variableDereference();
      if (!status->isVariable() || !OBJECT_CAST(Variable*,status)->isFrozen())
	{
	  continue;
	}
      // Get the variable with delays
      Reference* var = OBJECT_CAST(Reference*, delay->getArgument(2)->variableDereference());

      bool solved_found = false;
      Object* var_delays = var->getDelays();
      if (!var_delays->isNil())
	{
	  // Compress delay list
	  // Find the first delay to keep
	  for ( ; var_delays->isCons();
		var_delays = OBJECT_CAST(Cons *, var_delays)->getTail())
	    {
	      Structure *delay = 
		OBJECT_CAST(Structure *, 
			    OBJECT_CAST(Cons *, var_delays)->getHead());
	      Variable *delay_status = OBJECT_CAST(Variable*, 
					       delay->getArgument(1));
	      if (delay_status->isThawed())
		{
		  // Solved problem
		  solved_found = true;
		}
	      else
		{
		  break;
		}
	    }
	  if (solved_found)
	    {
	       updateAndTrailObject(reinterpret_cast<heapobject*>(var), 
				    var_delays, 
				    Reference::DelaysOffset);
	    }
	  // Scan the rest of the delay list
	  if (var_delays->isNil())
	    {
	      if (solved_found)
		{
		  updateAndTrailObject(reinterpret_cast<heapobject*>(var), 
				       var_delays, 
				       Reference::DelaysOffset);
		}
	      // Nothing to do
	      continue;
	    }
	  solved_found = false;
	  Object* look_ahead = OBJECT_CAST(Cons *, var_delays)->getTail();
	  for ( ; look_ahead->isCons();
		look_ahead = OBJECT_CAST(Cons *, look_ahead)->getTail())
	    {
	      Structure *delay = 
		OBJECT_CAST(Structure *, 
			    OBJECT_CAST(Cons *, look_ahead)->getHead());
	      Variable *delay_status = OBJECT_CAST(Variable*, 
					       delay->getArgument(1));
	      if (delay_status->isThawed())
		{
		  solved_found = true;
		}
	      else
		{
		  if (solved_found)
		    {
		      solved_found = false;
		      // point var_delays at next unsolved problem
		      updateAndTrailObject(reinterpret_cast<heapobject*>(var_delays), look_ahead, Cons::TailOffset);
		    }
		  var_delays = look_ahead;
		}
	    }
	  if (solved_found)
	    {
	      solved_found = false;
	      // point var_delays at next unsolved problem
	      updateAndTrailObject(reinterpret_cast<heapobject*>(var_delays), look_ahead, Cons::TailOffset);
	    }
	}
    }
  return RV_SUCCESS;
}

//
// Retry the delayed nfi problems.
//
Thread::ReturnValue
Thread::psi_retry_ov_delays(void)
{
  return BOOL_TO_RV(retry_delays(NFI));
}
//
// Retry the delayed nfi and = problems.
//
Thread::ReturnValue
Thread::psi_retry_ov_eq_delays(void)
{
  bool result = retry_delays(BOTH);
  if (result)
    {
       (void)psi_compress_var_delays();
       return RV_SUCCESS;
    }
  else
    {
       return RV_FAIL;
    }
}



