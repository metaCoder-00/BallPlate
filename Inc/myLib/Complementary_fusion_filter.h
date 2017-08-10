#ifndef __COMPLEMENTARY_FUSION_FILTER_H
#define __COMPLEMENTARY_FUSION_FILTER_H

#include "stm32f7xx_hal.h"
#include "mpu6050_filter.h"

typedef struct 
{
    float X_Real_Angle;
    float Y_Real_Angle;
} _Real_Angle;


extern _Real_Angle Real_Angle;


void Complementary_Fusion_Filter(void);
void Angle_send_data(short Gyro_Integer, short Acc, short Real_Angle);







#endif

