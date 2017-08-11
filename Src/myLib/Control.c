#include "Control.h"


//基于建模的LQR二次最优线性控制
//输入为 位移 速度  角度  角速度

int16_t X_LQR_Control(int16_t x, int16_t dx, int16_t x_angle, int16_t x_palstance)
{
    float X_output_pwm = 0;
    
    //X_output_pwm = 12.2474f * x + 12.6925f * dx - 45.5128f * x_angle * 0.0001f - 9.7993f * x_palstance * 0.0001f;

    X_output_pwm = 12.2474 * x + 12.6925 * dx;

    if(X_output_pwm > 25000)
        X_output_pwm = 25000;
    if(X_output_pwm < -25000)
        X_output_pwm = -25000;

    X_output_pwm = X_output_pwm / 10;    

    return (int16_t)X_output_pwm;
}
	
int16_t Y_LQR_Control(int16_t y, int16_t dy, int16_t y_angle, int16_t y_palstance)
{
    float Y_output_pwm = 0;

    //Y_output_pwm = 12.2474f * y + 12.6925f * dy - 45.5128f * y_angle * 0.0001f  - 9.7993f * y_palstance * 0.0001f;

    Y_output_pwm = 12.2474 * y + 12.6925 * dy;

    if(Y_output_pwm > 25000)
        Y_output_pwm = 25000;
    if(Y_output_pwm < -25000)
        Y_output_pwm = -25000;

    Y_output_pwm = Y_output_pwm / 10;

    return (int16_t)Y_output_pwm;
}

