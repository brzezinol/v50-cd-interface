/*
 * ProjectConfig.h
 *
 * Created: 2016-09-19 20:30:14
 *  Author: pbrzezinski
 */ 


#ifndef PROJECTCONFIG_H_
#define PROJECTCONFIG_H_

#include <avr/iom328p.h>

#define BOARD_SPI_MISO PIND1
#define BOARD_SPI_MOSI PIND2
#define BOARD_SPI_CLK PIND3
#define BOARD_SPI_SS PIND4

#define BOARD_COM_STM PIND5
#define BOARD_WT32_CONNECTED PIND5


#endif /* PROJECTCONFIG_H_ */