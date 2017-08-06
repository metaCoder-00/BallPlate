#include "STM32F746I2C1_MPU6050.h"
#include "mpu6050_filter.h"

struct _sensor sensor;
double b_IIR[IIR_ORDER+1] ={0.0008f, 0.0032f, 0.0048f, 0.0032f, 0.0008f};  //系数b
double a_IIR[IIR_ORDER+1] ={1.0000f, -3.0176f, 3.5072f, -1.8476f, 0.3708f};//系数a
double InPut_IIR[3][IIR_ORDER+1] = {0};
double OutPut_IIR[3][IIR_ORDER+1] = {0};

/*====================================================================================================*/
/*====================================================================================================*
** 函数名称: IIR_I_Filter
** 功能描述: IIR直接I型滤波器
** 输    入: InData 为当前数据
**           *x     储存未滤波的数据
**           *y     储存滤波后的数据
**           *b     储存系数b
**           *a     储存系数a
**           nb     数组*b的长度
**           na     数组*a的长度
**           LpfFactor
** 输    出: OutData         
** 说    明: 无
** 函数原型: y(n) = b0*x(n) + b1*x(n-1) + b2*x(n-2) -
                    a1*y(n-1) - a2*y(n-2)
**====================================================================================================*/
/*====================================================================================================*/
double IIR_I_Filter(double InData, double *x, double *y, double *b, short nb, double *a, short na)
{
	double z1,z2;
	short i;
	double OutData;
  
	for(i=nb-1; i>0; i--)
	{
		x[i]=x[i-1];
	}
  
	x[0] = InData;
  
	for(z1=0,i=0; i<nb; i++)
	{
		z1 += x[i]*b[i];
	}
  
	for(i=na-1; i>0; i--)
	{
		y[i]=y[i-1];
	}
  
	for(z2=0,i=1; i<na; i++)
	{
		z2 += y[i]*a[i];
	}
  
	y[0] = z1 - z2; 
	OutData = y[0];
    
	return OutData;
}

/*====================================================================================================*/
/*====================================================================================================*
**函数 : LPF_1st
**功能 : 一阶低通滤波
**输入 :  
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
float LPF_1st(float oldData, float newData, float lpf_factor)
{
	return oldData * (1.0f - lpf_factor) + newData * lpf_factor;
}



void MPU6050_USE_Data_Get(void)
{
	static float x,y,z;
	MPU_Get_Accelerometer(&(sensor.acc.origin.x),&(sensor.acc.origin.y),&(sensor.acc.origin.z));	//得到加速度传感器数据
	MPU_Get_Gyroscope(&(sensor.gyro.origin.x),&(sensor.gyro.origin.y),&(sensor.gyro.origin.z));	//得到陀螺仪数据
	
	//加速度计
	sensor.acc.origin.x = sensor.acc.origin.x - sensor.acc.quiet.x;
	sensor.acc.origin.y = sensor.acc.origin.y - sensor.acc.quiet.y;
	sensor.acc.origin.z = sensor.acc.origin.z - sensor.acc.quiet.z;
	
	//陀螺仪
	sensor.gyro.origin.x = sensor.gyro.origin.x - sensor.gyro.quiet.x;
	sensor.gyro.origin.y = sensor.gyro.origin.y - sensor.gyro.quiet.y;
	sensor.gyro.origin.z = sensor.gyro.origin.z - sensor.gyro.quiet.z;
	
	//弧度值
	sensor.gyro.radian.x = sensor.gyro.origin.x - sensor.gyro.quiet.x;
	sensor.gyro.radian.y = sensor.gyro.origin.y - sensor.gyro.quiet.y;
	sensor.gyro.radian.z = sensor.gyro.origin.z - sensor.gyro.quiet.z;
	
	//加速度计IIR滤波
	sensor.acc.averag.x = IIR_I_Filter(sensor.acc.origin.x, InPut_IIR[0], OutPut_IIR[0], b_IIR, IIR_ORDER+1, a_IIR, IIR_ORDER+1);
	sensor.acc.averag.y = IIR_I_Filter(sensor.acc.origin.y, InPut_IIR[1], OutPut_IIR[1], b_IIR, IIR_ORDER+1, a_IIR, IIR_ORDER+1);
	sensor.acc.averag.z = IIR_I_Filter(sensor.acc.origin.z, InPut_IIR[2], OutPut_IIR[2], b_IIR, IIR_ORDER+1, a_IIR, IIR_ORDER+1);
	
	// 陀螺仪一阶低通滤波
 	sensor.gyro.averag.x = LPF_1st(x,sensor.gyro.radian.x * Gyro_G,0.386f);
	x = sensor.gyro.averag.x;
	
 	sensor.gyro.averag.y = LPF_1st(y,sensor.gyro.radian.y * Gyro_G,0.386f);
	y = sensor.gyro.averag.y;
	
 	sensor.gyro.averag.z = LPF_1st(z,sensor.gyro.radian.z * Gyro_G,0.386f);
	z = sensor.gyro.averag.z;
}



//加速度静态采集
void Acc_OFFSET(void)
{
	static int32_t	tempax=0,tempay=0,tempaz=0;
	static uint8_t cnt_a=0;
		
	if(cnt_a==0)
	{
		sensor.acc.quiet.x = 0;
		sensor.acc.quiet.y = 0;
		sensor.acc.quiet.z = 0;
		tempax = 0;
		tempay = 0;
		tempaz = 0;
			//cnt_a = 1;//将下面的++往上提了，目的是照顾校准完成后别再加++了
	}
		
	tempax += sensor.acc.origin.x;	//数据累加
	tempay += sensor.acc.origin.y;
	tempaz += sensor.acc.origin.z;
	cnt_a++;
		
	if(cnt_a==200)
	{
		sensor.acc.quiet.x = tempax/cnt_a;
		sensor.acc.quiet.y = tempay/cnt_a;
		sensor.acc.quiet.z = tempaz/cnt_a;
		cnt_a = 0;
	}
}	

//计算陀螺仪零偏
void Gyro_Caloffest(int16_t x,int16_t y,int16_t z,uint8_t amount)
{
	sensor.gyro.quiet.x = x/amount;
	sensor.gyro.quiet.y = y/amount;
	sensor.gyro.quiet.z = z/amount;
	//200次累计取均值
}


//陀螺仪静态采集
void Gyro_OFFSET(void)
{
	static uint8_t over_flag = 0;
	short gyrox, gyroy, gyroz;
	uint8_t i, cnt_g = 0;
	int16_t Integral[3] = {0, 0, 0};
	int16_t tempg[3] = {0, 0, 0};
	static int16_t gx_last = 0, gy_last = 0, gz_last = 0;
	
	over_flag = 0;	//因为定义的是static，如果不自己赋值，
					//下次进来时over_flag就不会被赋值0了，
					//保持为上一次校准完时赋值的	
	
	while(!over_flag)	//此处系统静止
	{
		if(cnt_g < 200)
		{
			//采集陀螺仪数据
			MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);
			sensor.gyro.origin.x = (int16_t)gyrox;
			sensor.gyro.origin.y = (int16_t)gyroy;
			sensor.gyro.origin.z = (int16_t)gyroz;
			
			tempg[0] += sensor.gyro.origin.x;
			tempg[1] += sensor.gyro.origin.y;
			tempg[2] += sensor.gyro.origin.z;
			
			//在绝对值积分累加
			if(gx_last - sensor.gyro.origin.x < 0)
				Integral[0] += -(gx_last - sensor.gyro.origin.x);
			else
				Integral[0] += (gx_last - sensor.gyro.origin.x);
			
			if(gy_last - sensor.gyro.origin.y < 0)
				Integral[1] += -(gy_last - sensor.gyro.origin.y);
			else
				Integral[1] += (gy_last - sensor.gyro.origin.y);
			
			if(gz_last - sensor.gyro.origin.z < 0)
				Integral[2] += -(gz_last - sensor.gyro.origin.z);
			else
				Integral[2] += (gz_last - sensor.gyro.origin.z);

			gx_last = sensor.gyro.origin.x;
			gy_last = sensor.gyro.origin.y;
			gz_last = sensor.gyro.origin.z;
		}
		else
		{
			//陀螺仪静差较大,未校准成功
			if(Integral[0] >= 350 || Integral[1] >= 350 || Integral[2] >= 350)	//x轴静态积分较大，未解决
			{
				cnt_g = 0;	//重新开始200计数
				for(i=0;i<3;i++)
				{
					tempg[i] = Integral[i] = 0;
				}
			}
			// 陀螺仪静差较小，校准成功
			else
			{				
				Gyro_Caloffest(tempg[0],tempg[1],tempg[2],200);	//保存陀螺仪静态数据
				over_flag = 1;
				//flag.calibratingG = 0;	//成功后清除校准标记
			}
		}
		cnt_g++;	//计数200次，判断一次
	}
	
}	


