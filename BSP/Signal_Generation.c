//*********************************************************************
//
//           版权所有 (C), 2008-2028, 江西理工大学秒创八楼
//             -----------------------------------------------
//
//  文件作者:   liupengcheng
//  生成日期:   2018-3-21
//  功能描述:   信号的生成，产生--这里仅局限于PAC9685 芯片（16通道PWM信号输出）
//  修改历史:
//  (1) 修改日期:
//      修改作者:
//      修改内容:
//
//*********************************************************************
#include "Signal_Generation.h"
#include <math.h>

// Set to true to print some debug messages, or false to disable them.
#define ENABLE_DEBUG_OUTPUT 1

//void Adafruit_PWMServoDriver(unsigned char addr) {
//	addr= 0x40;
//  _i2caddr = addr;
//}

//unsigned char _i2caddr=0x80;
unsigned char _i2caddr=0xAA;





DEVICE_DEFINE(SIGNAL_GENERATION,DEVICE_TWO)

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期      :2017 2017/11/27 21:38
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
DEVICE_FUNC_DEFINE_OPEN(SIGNAL_GENERATION) 			
{
	I2C_HandleTypeDef SignalI2c;
	HAL_I2C_MspInit(&SignalI2c);
	MX_I2C1_Init();
//	printf("reset\n");
	write8(PCA9685_MODE1, 0x0);
//	printf("PWM servo Init Over!\n");
	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期      :2017 2017/11/27 21:38
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
DEVICE_FUNC_DEFINE_CLOSE(SIGNAL_GENERATION) 		
{
	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期      :2017 2017/11/27 21:38
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
DEVICE_FUNC_DEFINE_WRITE(SIGNAL_GENERATION) 		
{
	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期      :2017 2017/11/27 21:38
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
DEVICE_FUNC_DEFINE_READ(SIGNAL_GENERATION) 			
{
	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期      :2017 2017/11/27 21:38
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
DEVICE_FUNC_DEFINE_LSEEK(SIGNAL_GENERATION) 		
{
	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期      :2017 2017/11/27 21:38
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
DEVICE_FUNC_DEFINE_IOCTL(SIGNAL_GENERATION)
{
	return DEV_OK;
}



void reset(void) {
 write8(PCA9685_MODE1, 0x0);
}

void SetPWMFreq(float freq) {
	
	
	unsigned char oldmode = read8(PCA9685_MODE1);
	unsigned char newmode = (oldmode&0x7F) | 0x10; // sleep
	unsigned char prescale;
	float prescaleval;
	//Serial.print("Attempting to set freq ");
	//Serial.println(freq);
	freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
	prescaleval = 25000000;
	printf("EVA :%f\t",prescaleval);
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	if (ENABLE_DEBUG_OUTPUT) {
	printf("Estimated pre-scale: "); printf("%f\t",prescaleval);
	}
	prescale = floor(prescaleval + 0.5);
	if (ENABLE_DEBUG_OUTPUT) {
	printf("Final pre-scale: "); printf("%d\n",prescale);
	}


	write8(PCA9685_MODE1, newmode); // go to sleep
	write8(PCA9685_PRESCALE, prescale); // set the prescaler
	write8(PCA9685_MODE1, oldmode);
	write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
							// This is why the beginTransmission below was not working.
	//  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}

void SetPWM(unsigned char num, unsigned short on, unsigned short off) {
	//Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
//	printf("setPWM");
	unsigned char on_off[5];
	on_off[0] = on;
	on_off[1] = on>>8;
	on_off[2] = off;
	on_off[3] = off>>8;
	HAL_I2C_Mem_Write(&hi2c1,_i2caddr,LED0_ON_L+4*num,I2C_MEMADD_SIZE_8BIT,on_off,4,35);
}

// Sets pin without having to deal with on/off tick placement and properly handles
// a zero value as completely off.  Optional invert parameter supports inverting
// the pulse for sinking to ground.  Val should be a value from 0 to 4095 inclusive.
void SetPin(unsigned char num, unsigned short val, unsigned char invert)
{
	// Clamp value between 0 and 4095 inclusive.
	val = fmin(val, 4095);
	if (invert) {
		if (val == 0) {
		// Special value for signal fully on.
			SetPWM(num, 4096, 0);
		}
		else if (val == 4095) {
		// Special value for signal fully off.
			SetPWM(num, 0, 4096);
		}
		else {
			SetPWM(num, 0, 4095-val);
		}
	}
	else {
		if (val == 4095) {
		// Special value for signal fully on.
			SetPWM(num, 4096, 0);
		}
		else if (val == 0) {
		// Special value for signal fully off.
			SetPWM(num, 0, 4096);
		}
		else {
			SetPWM(num, 0, val);
		}
	}
}

unsigned char read8(unsigned char addr) {
	unsigned char data;
	HAL_I2C_Mem_Read(&hi2c1,_i2caddr,addr,I2C_MEMADD_SIZE_8BIT,&data,1,35);
	
/*调试代码*/
//	HAL_StatusTypeDef state;
//	state = HAL_I2C_Mem_Read(&hi2c1,_i2caddr,addr,I2C_MEMADD_SIZE_8BIT,&data,1,35);
//	if(state!= HAL_OK)
//	{
//		printf("Transmit Eorr:%d",state);
//	}
//	else 
//	{
//		printf("Transmit staet :%c\n",data);
//		return data;
//	}
/*调试代码*/	
	
}

void write8(unsigned char addr, unsigned char d) {
	
		HAL_I2C_Mem_Write(&hi2c1,_i2caddr,addr,I2C_MEMADD_SIZE_8BIT,&d,1,35);
	
/*调试代码*/
//	HAL_StatusTypeDef state;
//	
//	state = HAL_I2C_Mem_Write(&hi2c1,_i2caddr,addr,I2C_MEMADD_SIZE_8BIT,&d,1,35);
//	if(state!= HAL_OK)
//	{
//		printf("Transmit Eorr:%d",state);
//	}
//	else 
//	{
//		printf("Transmit staet :%d\n",state);
//	}
/*调试代码*/
	
}



