#include "Complementary_fusion_filter.h"
#include "usart.h"
#include "mpu6050_filter.h"

float gyro_integration = 0;
float Real_Angle = 0;


float Complementary_Fusion_Filter(void)
{
	gyro_integration = (sensor.gyro.origin.y) + gyro_integration;//锟斤拷锟斤拷锟斤拷锟斤拷 5ms
	//锟斤拷锟斤拷锟角伙拷锟斤拷转锟斤拷锟缴角讹拷 锟斤拷锟节诧拷锟斤拷
	
	//锟斤拷通锟斤拷锟斤拷锟节猴拷
	Real_Angle = (Real_Angle + sensor.gyro.averag.y * 0.008f) * 0.88f + sensor.acc.averag.y * 0.12f;
	
	//Angle_send_data(sensor.acc.origin.y, sensor.acc.averag.y, Real_Angle);
	return Real_Angle;
	
}

void Angle_send_data(short Gyro_Integer, short Acc, short Real_Angle)
{
	uint8_t tbuf[6]; 
	tbuf[0]=(Gyro_Integer>>8)&0XFF;
	tbuf[1]=Gyro_Integer&0XFF; 
	tbuf[2]=(Acc>>8)&0XFF;
	tbuf[3]=Acc&0XFF;
	tbuf[4]=(Real_Angle>>8)&0XFF;
	tbuf[5]=Real_Angle&0XFF;
	usart3_niming_report(0XA1,tbuf,6);//锟皆讹拷锟斤拷帧,0XA1
}	

