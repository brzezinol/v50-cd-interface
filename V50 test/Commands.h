/*
 * Commands.h
 *
 * Created: 2016-09-28 09:49:17
 *  Author: pbrzezinski
 */ 
#include <avr/pgmspace.h>

#ifndef COMMANDS_H_
#define COMMANDS_H_

#define CMD_MASTER_ACK			0x5a
#define CMD_SLAVE_ACK			0xdb

#define CMD_DISKINFO			0xF2
#define CMD_UNKNOWN_2			0xF4
#define CMD_UNKNOWN_1			0xF5
#define CMD_ST_ERR				0xF7
#define CMD_STATUS				0xF8
#define CMD_ERROR				0xF9
#define CMD_METADATA			0xFA
#define CMD_DISK_STRUCTURE		0xFB
#define CMD_UNKNOWN_N			0x4E
#define CMD_UNKNOWN_AD			0xAD

#define MSG_EJECT_MSG			0xE1
#define MSG_STOP_MSG			0xE2
#define MSG_PLAY_MSG			0xE4
#define MSG_SCAN_DISABLE_MSG	0xE4
#define MSG_SCAN_ENABLE_MSG		0xE5
#define MSG_FAST_FORWARD_MSG	0xE6
#define MSG_REWIND_MSG			0xE7
#define MSG_RANDOM_ENABLE_MSG	0xEA
#define MSG_PAUSE_MSG			0xEC
#define MSG_GOTO_TRACK_MSG		0xF4
#define MSG_ERROR_INFO_MSG		0xF7
#define MSG_TRACK_INFO_MSG		0xF8
#define MSG_RANDOM_DISABLE_MSG  0xFA
#define MSG_DISKINFO_MSG		0xFC

#define CMD_INIT_1				0x5F
#define CMD_INIT_2				0x01
#define CMD_INIT_3				0x10
#define CMD_INIT_4				0x60
#define CMD_INIT_5				0x41
#define CMD_INIT_6				0x38


#define CMD_STATUS_END			0xCC

typedef struct sCMD_INFO{
  volatile unsigned char PCommand;
  volatile unsigned char SLength;
} sCMD_INFO;

sCMD_INFO ALL_COMMANDS [] = { 
	{   CMD_SLAVE_ACK, 10 },
	{	CMD_INIT_1, 0	},
	{	CMD_INIT_2, 0	},
	{	CMD_INIT_3, 0	},
	{	CMD_INIT_4, 0	},
	{	CMD_INIT_5, 0	},
	{	CMD_INIT_6, 6	},
	{   CMD_STATUS, 10	},
	{	CMD_ST_ERR, 6	},
	{	CMD_UNKNOWN_N, 6	},
	{	CMD_UNKNOWN_AD, 8	},
	{	CMD_STATUS, 10	},
	{	MSG_PLAY_MSG, 10	}
};

#endif /* COMMANDS_H_ */