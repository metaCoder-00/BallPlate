#include "Motor.h"
#include "tim.h"

void MotorInit(void)
{

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);

    HAL_GPIO_WritePin(MOTOR_X_Direction_GPIO_Port, MOTOR_X_Direction_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MOTOR_Y_Direction_GPIO_Port, MOTOR_Y_Direction_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MOTOR_X_Enable_GPIO_Port, MOTOR_X_Enable_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MOTOR_Y_Enable_GPIO_Port, MOTOR_Y_Enable_Pin, GPIO_PIN_RESET);
}


void X_Motor_Fre_Change(int16_t X_Motor_Fre)
{
    TIM12->CCR1 = 5000;
    TIM12->PSC = X_Motor_Fre - 1;
}

void X_MotorStop(void)
{
    TIM12->CCR1 = 0;
    HAL_GPIO_WritePin(MOTOR_X_Enable_GPIO_Port, MOTOR_X_Enable_Pin, GPIO_PIN_RESET);
}

void X_Motor_Control(int8_t X_PWM)
{
    float Fre = 0;

    if(X_PWM < 0)
    {
        Direction_X_back_1();
        X_PWM = -X_PWM;
    }
    else
    {
        Direction_X_to_1();
    }

    if(X_PWM == 0)
    {
        X_MotorStop();
        return;
    }
    else
    {   
        //Fre = 10000;
        Fre = (1.0/X_PWM) * 1000;
    }
    HAL_GPIO_WritePin(MOTOR_X_Enable_GPIO_Port, MOTOR_X_Enable_Pin, GPIO_PIN_RESET);    
    X_Motor_Fre_Change(Fre);
}




void Y_Motor_Fre_Change(int16_t Y_Motor_Fre)
{
    TIM3->CCR1 = 5000;
    TIM3->PSC = Y_Motor_Fre - 1;
}

void Y_MotorStop(void)
{
    TIM3->CCR1 = 0;
    HAL_GPIO_WritePin(MOTOR_Y_Enable_GPIO_Port, MOTOR_Y_Enable_Pin, GPIO_PIN_RESET);
}

void Y_Motor_Control(int8_t Y_PWM)
{
    float Fre = 0;
    if(Y_PWM < 0)
    {
        Direction_Y_back_2();
        Y_PWM = -Y_PWM;
    }
    else
    {
        Direction_Y_to_2();
    }

    if(Y_PWM == 0)
    {
        Y_MotorStop();
        return;
    }
    else
    {   
        Fre = (1.0/Y_PWM) * 1000;
    }
    HAL_GPIO_WritePin(MOTOR_Y_Enable_GPIO_Port, MOTOR_Y_Enable_Pin, GPIO_PIN_RESET);    
    Y_Motor_Fre_Change(Fre);
}



