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
#include <common_io.h>
#include <SPI.h>
#include "USART.h"
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
volatile unsigned char command_count = 23;
volatile unsigned char command_response_count = 0;
volatile unsigned char command_value = 0;
volatile unsigned char command_in_read = 0;

//przerwanie defaultowe na wypadek pozostawienia 
//niebos³u¿onych przerwañ, aby siê procek nie resetowa³
ISR(__vector_default){
USART_SendByte(0x00);
}

ISR(WDT_vect){
USART_SendByte(0x01);
}

ISR(EE_READY_vect){
USART_SendByte(0x02);
}

ISR(SPM_READY_vect){
USART_SendByte(0x03);
}

ISR(PCINT0_vect){
USART_SendByte(0x04);
}

ISR(PCINT1_vect){
USART_SendByte(0x05);
}

ISR(PCINT2_vect){
USART_SendByte(0x06);
}

ISR(TIMER2_COMPA_vect){
USART_SendByte(0x07);
}

ISR(TIMER2_COMPB_vect){
USART_SendByte(0x08);
}

ISR(TIMER2_OVF_vect){
USART_SendByte(0x09);
}

ISR(TIMER1_CAPT_vect){
USART_SendByte(0x0a);
}

ISR(TIMER1_COMPA_vect){
USART_SendByte(0x0b);
}
ISR(TIMER1_COMPB_vect){
USART_SendByte(0x0c);
}
ISR(TIMER1_OVF_vect){
USART_SendByte(0x0d);
}
ISR(TIMER0_COMPA_vect){
USART_SendByte(0x0e);
}
ISR(TIMER0_OVF_vect){
USART_SendByte(0x0f);
}
ISR(TIMER0_COMPB_vect){
USART_SendByte(0x10);
}

ISR(ADC_vect){
USART_SendByte(0x11);
}

ISR(ANALOG_COMP_vect){
USART_SendByte(0x12);
}

ISR(TWI_vect){
USART_SendByte(0x13);
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
		//SETBIT(PORTB, SPI_MISO_PIN);
		//_delay_us(10);
		//CLEARBIT(PORTB, SPI_MISO_PIN);
		command_value = CMD_SLAVE_ACK;
	}

	SPDR = command_value;

	_delay_us(28);

	SETBIT(PORTB, SPI_MISO_PIN);
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

	_delay_us(5);

	SPI_DISABLE;
	CLEARBIT(PORTB, SPI_MISO_PIN);
	MTS_HIGH;
	if(command_in_read == 1){
		if(command_response_count > 0)
			command_response_count--;
		if(command_response_count <= 0){
			command_in_read = 0;
			command_counter++;
			if(command_counter < command_count){
				if(ALL_COMMANDS[command_counter - 1].SLength == 0)
					_delay_ms(1);
				else
					_delay_ms(16);
				MTS_LOW;
			}
		}
		//else{
			//MTS_HIGH;
		//}
	}
}

//przerwanie odbioru bajtu na USART
ISR(USART_RX_vect){
USART_SendByte(0x14);
}
//przerwanie gotowoœci USART ?
ISR(USART_UDRE_vect){
USART_SendByte(0x15);
}
//przerwanie wys³ania bajtu przez USART
ISR(USART_TX_vect){
USART_SendByte(0x16);
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