/*
 * eeprom.h
 *
 * Created: 2016-09-26 14:36:21
 *  Author: pbrzezinski
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

unsigned char eeprom_frame_00[11] __attribute__((section(".eeprom"))) = {228, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219};
unsigned char eeprom_frame_01[11] __attribute__((section(".eeprom"))) = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char eeprom_frame_02[11] __attribute__((section(".eeprom"))) = {225, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219};
unsigned char eeprom_frame_03[11] __attribute__((section(".eeprom"))) = { 16,   0, 219, 219, 219, 219, 219, 219, 219, 219, 219};
unsigned char eeprom_frame_04[11] __attribute__((section(".eeprom"))) = {248, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219};

#endif /* EEPROM_H_ */