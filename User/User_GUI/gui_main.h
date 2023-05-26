#ifndef __GUI_MAIN_H
#define __GUI_MAIN_H

#include "util.h"

typedef enum{
	CORONA = 0x01,
	FAN = 0x02,
}mainData_e;

typedef struct{
	//发送信息
	float power;
	float speed;
	uint8_t speed_up;
	//接收信息
	uint8_t main_rev_data;
}main_pageStruct;

__IO main_pageStruct *get_maindata(void);
uint8_t get_mainData(uint8_t main_data,mainData_e data_state);
#endif
