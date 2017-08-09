#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f7xx_hal.h"
#include "main.h"

/********牛逼进口步进电机驱动(2DM404  20V)********/
//电机驱动拨码开关见照片
//供电20V
//分频  20-1 ~ 100-1
//频率  50K  ~  10K
//频率越高  转速越快
//速度与占空比基本无关  但占空比为0电机不转
//细分10000   电流1.9A
//拨码开关 10110010


void MotorInit(void);

void X_Motor_PWM_Change(int16_t X_Motor_PWM);

void Y_Motor_PWM_Change(int16_t Y_Motor_PWM);

void X_Motor_Fre_Change(int16_t X_Motor_Fre);

void Y_Motor_Fre_Change(int16_t Y_Motor_Fre);



#endif
