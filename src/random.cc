// random.cc -  support for random numbers
//
// http://www.qbrundage.com/michaelb/pubs/essays/random_number_generation
//
// $Id: random.cc,v 1.3 2006/01/31 23:17:51 qp Exp $

#include <limits.h>
#include <stdlib.h>
#include <math.h>

#include "thread_qp.h"

#define R250_LEN     250
#define R521_LEN     521
#define ALL_BITS     0x7FFFFFFFL

int r250_index;
int r521_index;
unsigned long r250_buffer[R250_LEN];
unsigned long r521_buffer[R521_LEN];

void r250_521_init() {
    int i = R521_LEN;
    unsigned long mask1 = 1;
    unsigned long mask2 = 0xFFFFFFFF;
	
    while (i-- > R250_LEN) {
        r521_buffer[i] = rand();
    }
    while (i-- > 31) {
        r250_buffer[i] = rand();
        r521_buffer[i] = rand();
    }
    
    /*
    Establish linear independence of the bit columns
    by setting the diagonal bits and clearing all bits above
    */
    while (i-- > 0) {
        r250_buffer[i] = (rand() | mask1) & mask2;
        r521_buffer[i] = (rand() | mask1) & mask2;
        mask2 ^= mask1;
        mask1 >>= 1;
    }
    r250_buffer[0] = mask1;
    r521_buffer[0] = mask2;
    r250_index = 0;
    r521_index = 0;
}

#define R250_IA  (sizeof(unsigned long)*103)
#define R250_IB  (sizeof(unsigned long)*R250_LEN - R250_IA)
#define R521_IA  (sizeof(unsigned long)*168)
#define R521_IB  (sizeof(unsigned long)*R521_LEN - R521_IA)

unsigned long r250_521_random() {
    /*
    I prescale the indices by sizeof(unsigned long) to eliminate
    four shlwi instructions in the compiled code.  This minor optimization
    increased perf by about 12%.
    
    I also carefully arrange index increments and comparisons to minimize
    instructions.  gcc 3.3 seems a bit weak on instruction reordering. The
    j1/j2 branches are mispredicted, but nevertheless these optimizations
    increased perf by another 10%.
    */
    
    int i1 = r250_index;
    int i2 = r521_index;
    unsigned char * b1 = (unsigned char*)r250_buffer;
    unsigned char * b2 = (unsigned char*)r521_buffer;
    unsigned long * tmp1, * tmp2;
    unsigned long r, s;
    int j1, j2;
    
    j1 = i1 - R250_IB;
    if (j1 < 0)
        j1 = i1 + R250_IA;
    j2 = i2 - R521_IB;
    if (j2 < 0)
        j2 = i2 + R521_IA;
    
    tmp1 = (unsigned long *)(b1 + i1);
    r = (*(unsigned long *)(b1 + j1)) ^ (*tmp1);
    *tmp1 = r;
    tmp2 = (unsigned long *)(b2 + i2);
    s = (*(unsigned long *)(b2 + j2)) ^ (*tmp2);
    *tmp2 = s;
    
    i1 = (i1 != sizeof(unsigned long)*(R250_LEN-1)) ? (i1 + sizeof(unsigned long)) : 0;
    r250_index = i1;
    i2 = (i2 != sizeof(unsigned long)*(R521_LEN-1)) ? (i2 + sizeof(unsigned long)) : 0;
    r521_index = i2;
        
    return (r ^ s) & ALL_BITS;
}


double dr250()          /* returns a random double in range 0..1 */
{
  int r = r250_521_random();
  while (r == ALL_BITS)  r = r250_521_random();

  return (double)r / ALL_BITS;
}
//
// psi_srandom(Seed)
// Random number seed. If the seed is given then that is used
// otherwise the seed is the current time and the seed is
// instantiated to that value
// mode(in)
Thread::ReturnValue
Thread::psi_srandom(Object *& object1)
{
  Object* val1 = heap.dereference(object1);
  
  if (val1->isVariable())
    {
      long seed = static_cast<long>(time((time_t *) NULL));
      srand(seed);
      r250_521_init();
      for (int i = 0; i < 10; i++) (void)r250_521_random();
      return BOOL_TO_RV(unify(object1, heap.newInteger(seed)));
    }
  else if (val1->isInteger())
    {
      srand(val1->getInteger());
      r250_521_init();
      for (int i = 0; i < 10; i++) (void)r250_521_random();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  return(RV_SUCCESS);
}

//
// psi_random_float(Float)
// returns a random float
// mode(out)
Thread::ReturnValue
Thread:: psi_random_float(Object *& object1)
{
  object1 = heap.newDouble(dr250());
  return(RV_SUCCESS);
}


//
// psi_random_int(Int)
// returns a random int
// mode(out)
Thread::ReturnValue
Thread:: psi_random_int(Object *& object1)
{
  object1 = heap.newInteger(r250_521_random());
  return(RV_SUCCESS);
}

//
// psi_random_range(Low, Upper, Val)
// returns a random int in the range [Low, Upper]
// mode(iin, in, out)
Thread::ReturnValue
Thread:: psi_random_range(Object *& object1, Object *& object2, 
			  Object *& object3)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (!val1->isInteger())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else if (!val2->isInteger())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  double r = dr250();
  int x = val1->getInteger();
  int y = val2->getInteger();
  int size = y - x + 1;
  
  int res = x + (long)floor(r*size);

  object3 = heap.newInteger(res);
  return(RV_SUCCESS);
}
