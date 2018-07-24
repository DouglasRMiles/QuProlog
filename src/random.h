// random.h -  support for random numbers
//
// r250 taken from http://www.taygeta.com/random.html
//
// $Id: random.h,v 1.1 2005/05/26 03:51:02 qp Exp $

#ifndef RANDOM_H
#define RANDOM_H

/*
#ifdef NO_PROTO
void         r250_init();
unsigned int r250();
double      dr250();

#else
void         r250_init(int seed);
unsigned int r250( void );
double       dr250( void );
#endif
*/

public:
ReturnValue psi_srandom(Object *&);
ReturnValue psi_random_float(Object *&);
ReturnValue psi_random_int(Object *&);
ReturnValue psi_random_range(Object *&, Object *&, Object *&);


#endif // RANDOM_H

