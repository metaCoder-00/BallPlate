#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f7xx_hal.h"
#include "arm_math.h"


int16_t X_LQR_Control(int16_t x, uint16_t dx, int16_t x_angle, int16_t x_palstance);

int16_t Y_LQR_Control(int16_t y, uint16_t dy, int16_t y_angle, int16_t y_palstance);









#endif

