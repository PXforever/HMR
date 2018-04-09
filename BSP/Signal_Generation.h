/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#ifndef __SIGNAL_GENERATION_H
#define __SIGNAL_GENERATION_H

//1、头文件
/********************************************************************************************************************************************************************/
#include "stm32f1xx_hal.h"
#include "Device.h"

//2、宏定义
/********************************************************************************************************************************************************************/
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

//SetPWM(0,0,(Get_AD(ADC_CH2)*0.114+100));
#define SERVO_MAX 556                 //最大的旋转度
#define SERVO_MIN 100                 //最小的旋转度

//3、类型定义
/********************************************************************************************************************************************************************/




//4、变量声明
/********************************************************************************************************************************************************************/


//5、函数声明
/********************************************************************************************************************************************************************/
uint8_t read8(uint8_t addr);
void write8(uint8_t addr, uint8_t d);


void begin(void);
void reset(void);
void SetPWMFreq(float freq);
void SetPWM(uint8_t num, uint16_t on, uint16_t off);
void SetPin(uint8_t num, uint16_t val, uint8_t invert);
//void Adafruit_PWMServoDriver(u8 addr);


#endif










