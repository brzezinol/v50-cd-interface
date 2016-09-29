/*
 * V50 test.c
 *
 * Created: 2016-09-18 00:09:30
 * Author : Piotr
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <common_io.h>
#include <SPI.h>
#include <avr/eeprom.h>
#include "USART.h"
#include "eeprom.h"
#include "Commands.h"

#define ACC_ON PINC1
#define RESET PINC0
#define STM PIND2
#define MTS PINB1
#define INT0_ENABLE (EIMSK = (1<<INT0))
#define INT0_DISABLE (EIMSK &= ~(1<<INT0))
#define MTS_LOW CLEARBIT(PORTB, MTS);
#define MTS_HIGH SETBIT(PORTB, MTS);

volatile unsigned char command_counter = 0;
volatile unsigned char command_count = 13;
volatile unsigned char command_response_count = 0;
volatile unsigned char command_value = 0;
volatile unsigned char command_in_read = 0;

//przerwanie defaultowe na wypadek pozostawienia 
//niebos³u¿onych przerwañ, aby siê procek nie resetowa³
ISR(__vector_default){

}

//zewnetrzne przerwanie INT0
ISR(INT0_vect){
	//flaga bêdzie zdjête w przerwaniu SPI kiedy 
	//command_response_count zejdzie do 0
	if(command_in_read == 0){
		command_value = ALL_COMMANDS[command_counter].PCommand;
		command_response_count = ALL_COMMANDS[command_counter].SLength + 1;
		command_in_read = 1;
	}
	else{
		SETBIT(PORTB, SPI_MISO_PIN);
		_delay_us(10);
		CLEARBIT(PORTB, SPI_MISO_PIN);
		command_value = CMD_SLAVE_ACK;
	}

	SPDR = command_value;

	_delay_us(28);

	SPI_ENABLE;

	SPI_INT_ENABLE;

	MTS_LOW;
}

//zewnetrzne przerwanie INT1, tu nie uzywane
//ale na wszelki wypadek wektor zadeklarowany
ISR(INT1_vect){

}

//przerwanie zakoñczenia transmiski SPI
ISR(SPI_STC_vect){
	volatile unsigned char tmp = SPDR;

	SPI_INT_DISABLE;

	_delay_us(25);

	
	SPI_DISABLE;

	if(command_in_read == 1){
		if(command_response_count > 0)
			command_response_count--;
		if(command_response_count <= 0){
			command_in_read = 0;
			command_counter++;
			if(command_counter < command_count){
				MTS_HIGH;
				_delay_ms(1);
				MTS_LOW;
			}
		}
		else{
			MTS_HIGH;
		}
	}
	USART_SendByte(command_response_count);
}

//przerwanie odbioru bajtu na USART
ISR(USART_RX_vect){

}
//przerwanie gotowoœci USART ?
ISR(USART_UDRE_vect){

}
//przerwanie wys³ania bajtu przez USART
ISR(USART_TX_vect){

}

int main(void)
{
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;

	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;

	/*
		Opis wyprowadzeñ 

		C0 - CD_ACCON
		C1 - CD_RESET
		B1 - MTS
		D2 - STM
		D7 - LED
	*/

	//C0 i C1 jako wyjœcia
	DDRC = (1<<ACC_ON)|(1<<RESET); 
	//B1 out, linia MTS
	DDRB = (1<<MTS);
	//D7 out, testowy LED
	DDRD = (1<<PIND7);
	//MTS pull up
	MTS_LOW;
	 
	///TODO: SPRAWDZIC POLACZENIE KABLI!!!!!
	//CD_RESET - pull-up, ACCON - pull-down
	PORTC = (0<<ACC_ON)|(1<<RESET);

	//Inicjalizacja SPI jako slave
	SPI_InitSlave();

	//Inicjalizacja UART, konfiguracja w USART.h
	USART_Init();

	//Monit ¿e uk³ad ruszy³
	USART_SendStr("INIT");

	//D2 jako wejœcie, to jest linia STM
	SET_PINPORT_AS_IN(DDRD, STM);
	//Pullup
	SETBIT(PORTD, STM); 
	//przerwanie inicjuje zbocze opadaj¹ce
	EICRA = (1<<ISC01);

	//wy³¹czenie przerwania na SPI
	SPI_INT_DISABLE;
	//w³¹czenie przerwania na INT0
	INT0_ENABLE;

	_delay_ms(600);

	//global interrupts on
	sei();

	//USART_SendStr("Lista polecen:");
	//USART_SendByte(TXT_CR);
	//USART_SendByte(TXT_LF);
	//for(int i=0;i<13;i++)
	//{ 
		//volatile unsigned char c = ALL_COMMANDS[i].PCommand;
		//volatile unsigned char s = ALL_COMMANDS[i].SLength;
		//USART_SendByte(255);
		//USART_SendByte(c);
		//USART_SendByte(255);
		//USART_SendByte(s);
		//USART_SendByte(0);
	//}



    while (1) 
    {
		
		

    }
}