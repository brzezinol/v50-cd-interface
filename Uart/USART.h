/*
 * UART.h
 *
 * Created: 2014-04-19 23:17:16
 *  Author: Piotr
 */ 
#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef USART_BAUDRATE
#define USART_BAUDRATE 250000
#endif

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#ifndef USART_USEINTERRUPT
#define USART_USEINTERRUPT 0
#endif

#define TXT_CR 0x0D
#define TXT_LF 0x0A

volatile unsigned char UART_value;  
volatile unsigned char UART_buffer[16];
volatile uint8_t UART_buffer_position;

void USART_Init(void);
void USART_SendByte(uint8_t u8Data);
void USART_SendStr(const char *str);
uint8_t USART_ReceiveByte();

#endif /* USART_H_ */