#include "MavlinkProtocol.h"

mavlink_system_t mavlink_system;
uint32_t custom_mode = 0;
uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;
void mavlink_int(void)
{
	mavlink_system.sysid = 20;
	mavlink_system.compid = MAV_COMP_ID_IMU;
	mavlink_system.type = MAV_TYPE_QUADROTOR;
	mavlink_system.state = MAV_STATE_STANDBY;
	mavlink_system.mode = MAV_MODE_MANUAL_ARMED;
}

void mavlink_message(void)
{
	mavlink_message_t msg;
	uint16_t len;
	uint8_t	count=1;
	uint8_t count2=1;
	mavlink_int();
	
	// find usart device
	
	//main loop
	while(1)
	{
		//send IMU 10Hz
		if((SYS_TIME+50000)/100000 == count2)
		{
			count2++;
			mavlink_system.compid = MAV_COMP_ID_IMU;
			
			mavlink_msg_attitude_pack(mavlink_system.sysid,
						mavlink_system.compid,
						&msg,
						SYS_TIME/1000,
						1.0,
						1.0,
						1.0,
						1.0,
						1.0,
						1.0);
			len = mavlink_msg_to_send_buffer(USART_SendBuffer, &msg);
			USART2_DMA_SendData();
		}
		//send heart beat  1Hz
		if(SYS_TIME/1000000 == count)
		{
			count++;
			mavlink_system.compid = MAV_COMP_ID_ALL;
			
			mavlink_msg_heartbeat_pack(mavlink_system.sysid,
						mavlink_system.compid,
						&msg,
						mavlink_system.type,
						autopilot_type,
						mavlink_system.mode,
						custom_mode,
						mavlink_system.state);
			len = mavlink_msg_to_send_buffer(USART_SendBuffer, &msg);			
			USART2_DMA_SendData();
		}
			
		
	}
}
