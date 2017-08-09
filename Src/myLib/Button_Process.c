#include "Button_Process.h"
#include "STM32F746SPI1_OLED.h"
#include "main.h"

_BUTTON_STATUE button_statue;
_SYSTEM_STATUE system_statue;

void Statue_Init(void)
{
    button_statue = Menu_1st;
    system_statue = System_Initial;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    
    switch(GPIO_Pin)
    {
        case REMOTE_A_Pin: Remote_A_Function(); break;
    
        case REMOTE_B_Pin: Remote_B_Function(); break;

        case REMOTE_C_Pin: Remote_C_Function(); break;

        case REMOTE_D_Pin: Remote_D_Function(); break;
    
        default : return;
    }
}


void Remote_A_Function(void)
{
    if(system_statue == System_Initial)
    {
        system_statue = System_Balance;
    }

    OLED_ShowString(0, 0, "A");
}

void Remote_B_Function(void)
{
    OLED_ShowString(0, 0, "B");
}

void Remote_C_Function(void)
{
    OLED_ShowString(0, 0, "C");
}

void Remote_D_Function(void)
{
    OLED_ShowString(0, 0, "D");
}




