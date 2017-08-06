#ifndef __MPU6050_FILTER_H
#define __MPU6050_FILTER_H
#include "stm32f7xx_hal.h"

struct _float{
		float x;
		float y;
		float z;};

struct _int16{
		int16_t x;
		int16_t y;
		int16_t z;};

struct _trans{
		struct _int16 origin;	//原始值
		struct _float averag;	//平均值
		struct _float histor;	//历史值
		struct _float quiet;	//静态值
		struct _float radian;	//弧度值
			};

struct _sensor{
	struct _trans acc;			//加速度
	struct _trans gyro;			//陀螺仪
			};

extern struct _sensor sensor;
			
			
#define  IIR_ORDER	4      //使用IIR滤波器的阶数
			

double IIR_I_Filter(double InData, double *x, double *y, double *b, short nb, double *a, short na);

#define RtA 	57.324841				
#define AtR    	0.0174533				
#define Acc_G 	0.0011963				
#define Gyro_G 	0.03051756f				
#define Gyro_Gr	0.0005426


float LPF_1st(float oldData, float newData, float lpf_factor);

			
void MPU6050_USE_Data_Get(void);			
void Gyro_OFFSET(void);				
void Acc_OFFSET(void);
void Gyro_Caloffest(int16_t x,int16_t y,int16_t z,uint8_t amount);
short Z_Filter(short aacz, short gyroz);

#endif

