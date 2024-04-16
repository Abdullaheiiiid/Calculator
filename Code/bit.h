#ifndef BIT_H
#define BIT_H

#define	SETBIT(NUM,BIT) (NUM |= (1<<BIT))
#define	CLEARBIT(NUM,BIT) (NUM &= ~(1<<BIT))
#define	TOGGLEBIT(NUM,BIT) (NUM ^= (1<<BIT))
#define	GETBIT(NUM,BIT) (NUM = ((NUM >> BIT) & 1))

#endif
