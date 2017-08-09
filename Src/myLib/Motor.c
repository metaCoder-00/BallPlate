#include "Motor.h"
#include "tim.h"

void MotorInit(void)
{

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

    HAL_GPIO_WritePin(MOTOR_X_Direction_GPIO_Port, MOTOR_X_Direction_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(MOTOR_Y_Direction_GPIO_Port, MOTOR_Y_Direction_Pin, GPIO_PIN_RESET);
}


void X_Motor_PWM_Change(int16_t X_Motor_PWM)
{
    TIM3->CCR2 = X_Motor_PWM;
}

void Y_Motor_PWM_Change(int16_t Y_Motor_PWM)
{
    TIM3->CCR1 = Y_Motor_PWM;
}

