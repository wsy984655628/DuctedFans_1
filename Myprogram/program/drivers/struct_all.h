#ifndef __STRUCT_ALL_H__
#define __STRUCT_ALL_H__

#include "stm32f4xx.h"

struct _MainInt_Time
{
	uint32_t EntranceT;
	uint32_t ExitT;
	uint32_t gap;
};
extern struct _MainInt_Time MainInt_Time;

struct _out_angle
{
	unsigned char flag;
	unsigned int count;
	
	double yaw;
	double roll;
	double pitch;
	
	double rad_yaw;
	double rad_roll;
	double rad_pitch;
};
extern struct _out_angle out_angle;

#endif
