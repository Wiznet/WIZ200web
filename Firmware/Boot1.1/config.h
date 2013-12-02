#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "types.h"

#define GoBoot()	do{								\
						MCUCR |= _BV(IVCE);			\
						MCUCR |= _BV(IVSEL);		\
						((void (*)())0x1E000)();	\
					}while(0)

#define GoApp()		do{								\
						MCUCR |= _BV(IVCE);		\
						MCUCR &= ~_BV(IVSEL);		\
						((void (*)())0x0000)();		\
					}while(0)

#define PAGE_SIZE		256			/* byte */

//#define DEBUG

#endif
