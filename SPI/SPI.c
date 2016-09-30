/*
 * SPI.c
 *
 * Created: 2016-09-18 10:38:13
 * Author : Piotr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_io.h"
#include "SPI.h"

void SPI_InitMaster(void){
	// Set MOSI, SCK as Output
	DDRB |=(1<<SPI_MOSI_PIN)|(1<<SPI_CLK_PIN);
	PORTB |= (0<<SPI_MOSI_PIN);
	// Enable SPI, Set as Master
	// Prescaler: Fosc/16, Enable Interrupts
	//The MOSI, SCK pins are as per ATMega8
	SPCR=(1<<SPIE)|(1<<SPE)|(SPI_BYTE_ORDER<<DORD)|(1<<MSTR)|(1<<SPR1)|(0<<SPR0)|(1<<CPOL)|(1<<CPHA);
}

void SPI_InitSlave(void){
	SET_PINPORT_AS_OUT(DDRB, SPI_MISO_PIN); //MISO as OUTPUT
	SPCR = (1<<SPIE)|(0<<MSTR)|(SPI_BYTE_ORDER<<DORD)|(1<<CPOL)|(1<<CPHA);   
	//Enable SPI
}

uint8_t SendByte(uint8_t data){
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}

uint8_t ReadByte(){
	return 0;
}

