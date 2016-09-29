/*
 * UART.c
 *
 * Created: 2014-04-19 23:17:03
 *  Author: Piotr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <string.h>
#include <common_io.h>
#include "USART.h"

/* This variable is volatile so both main and RX interrupt can use it.
It could also be a uint8_t type */
extern volatile unsigned char UART_value;  
extern volatile unsigned char UART_buffer[16];
//extern volatile uint8_t UART_buffer_position = 0; 

void USART_Init(void){
  /*Set baud rate */
  UBRR0H = (BAUD_PRESCALE >> 8);
  UBRR0L = BAUD_PRESCALE;

  /*Enable receiver and transmitter and Receive interupt and Data Register Empty*/
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(0<<RXCIE0)|(0<<UDRIE0);

  /* Set frame format: 8data, 1stop bit no parity */
  UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void USART_SendByte(uint8_t u8Data){
	// Wait until last byte has been transmitted
	while((UCSR0A & (1 << UDRE0)) == 0);

	// Transmit data
	UDR0 = u8Data;
}

void USART_SendStr(const char *str){
	while(*str) {
		USART_SendByte(*str);		//Advance though string till end
		str++;
	}
	return;
}

// not being used but here for completeness
// Wait until a byte has been received and return received data
uint8_t USART_ReceiveByte(){
	return 0;
}

void USART_clearFrame(void){
	for(UART_buffer_position=0;UART_buffer_position<16;UART_buffer_position++)
		UART_buffer[UART_buffer_position] = 0;
	UART_buffer_position = 0;
}

