#ifndef __BUTTON_PROCESSING_H
#define __BUTTON_PROCESSING_H

#include "stm32f7xx_hal.h"



typedef enum 
{
    Menu_1st,
    Menu_2nd,
    Menu_3rd
}_BUTTON_STATUE;


typedef enum
{
    System_Initial,
    System_Balance,
    System_Tasking
}_SYSTEM_STATUE;

extern _BUTTON_STATUE button_statue;
extern _SYSTEM_STATUE system_statue;

void Remote_A_Function(void);
void Remote_B_Function(void);
void Remote_C_Function(void);
void Remote_D_Function(void);

void Statue_Init(void);


#endif

