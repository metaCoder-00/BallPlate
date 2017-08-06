#ifndef __COMPLEMENTARY_FUSION_FILTER_H
#define __COMPLEMENTARY_FUSION_FILTER_H

#include "stm32f7xx_hal.h"
#include "mpu6050_filter.h"

float Complementary_Fusion_Filter(void);
void Angle_send_data(short Gyro_Integer, short Acc, short Real_Angle);







#endif

