#ifndef __MAVLINKPROTOCOL_H__
#define __MAVLINKPROTOCOL_H__

#include "stm32f4xx.h"
#include "usart.h"
#include "pwm.h"

#include <stdint.h>
#pragma anon_unions
#include "mavlink.h"

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
