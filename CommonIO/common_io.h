/*
 * common_io.h
 *
 * Created: 2016-09-18 00:37:16
 *  Author: Piotr
 */ 


#ifndef COMMON_IO_H_
#define COMMON_IO_H_

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

#define SET_PINPORT_AS_OUT(ADDRES,PIN) (ADDRES |= (1<<PIN))
#define SET_PINPORT_AS_IN(ADDRES,PIN) (ADDRES &= ~(1<<PIN))

#endif /* COMMON_IO_H_ */