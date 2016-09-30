/*
 * SPI.h
 *
 * Created: 2016-09-18 10:38:37
 *  Author: Piotr
 */ 


#ifndef SPI_H_
#define SPI_H_

#define SPI_PORT DDRB
#define SPI_MOSI_PIN PINB3
#define SPI_MISO_PIN PINB4
#define SPI_SS_PIN PINB0
#define SPI_CLK_PIN PINB5
#define MSB 0
#define LSB 1
#define SPI_BYTE_ORDER LSB

#define SPI_DISABLE (SPCR |= (0<<SPE))
#define SPI_ENABLE (SPCR |= (1<<SPE))
#define SPI_INT_ENABLE (SPCR |= (1<<SPIE))
#define SPI_INT_DISABLE (SPCR &= ~(1<<SPIE))

void SPI_InitMaster(void);
void SPI_InitSlave(void);
uint8_t SendByte(uint8_t data);
uint8_t ReadByte();

#endif /* SPI_H_ */