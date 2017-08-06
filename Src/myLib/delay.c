#include "delay.h"

void delay_ms2(int32_t nms)
{
	int32_t temp;
	SysTick->LOAD = 8000*nms;
	SysTick->CTRL = 0x00;		//清空计数器
	SysTick->CTRL = 0x01;		//使能，减到0是无动作，采用外部时钟源
	do
	{
		temp = SysTick->CTRL;	//读取当前倒计数值
	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	SysTick->CTRL = 0x00;		//关闭计数器
	SysTick->VAL = 0x00;		//清空计数器
}

void delay_us2(int32_t nus)
{
	int32_t temp;
	SysTick->LOAD = 5*nus;
	SysTick->CTRL = 0x00;		//清空计数器
	SysTick->CTRL = 0x01;		//使能，减到0是无动作，采用外部时钟源
	do
	{
		temp = SysTick->CTRL;	//读取当前倒计数值
	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	SysTick->CTRL = 0x00;		//关闭计数器
	SysTick->VAL = 0x00;		//清空计数器
}

void delay_10us2(void)
{
	int32_t temp;
	SysTick->LOAD = 2500;
	SysTick->CTRL = 0x00;		//清空计数器
	SysTick->CTRL = 0x01;		//使能，减到0是无动作，采用外部时钟源
	do
	{
		temp = SysTick->CTRL;	//读取当前倒计数值
	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	SysTick->CTRL = 0x00;		//关闭计数器
	SysTick->VAL = 0x00;		//清空计数器
}
