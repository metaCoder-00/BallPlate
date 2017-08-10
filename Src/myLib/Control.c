#include "Control.h"


//基于建模的LQR二次最优线性控制
//输入为 位移 速度  角度  角速度

int16_t X_LQR_Control(int16_t x, int16_t dx, int16_t x_angle, int16_t x_palstance)
{
    return 12.2474 * x + 12.6925 * dx - 45.5128 * x_angle - 9.7993 * x_palstance;
}

int16_t Y_LQR_Control(int16_t y, int16_t dy, int16_t y_angle, int16_t y_palstance)
{
    return 12.2474 * y + 12.6925 * dy - 45.5128 * y_angle - 9.7993 * y_palstance;
}