#ifndef DRANDH
#define DRANDH

#include <stdlib.h>

#define RANDM 0x100000000LL
#define RANDC 0xB16
#define RANDK 0x5DEECE66DLL 

static unsigned long long seed = 1;

double drand48(void)
{
	seed = (RANDK * seed + RANDC) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return 	((double)x / (double)RANDM);

}

void srand48(unsigned int i)
{
	seed = (((long long int)i) << 16) | rand();
}


#endif