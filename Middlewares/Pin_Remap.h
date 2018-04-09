#ifndef __PINREMAP_H
#define __PINREMAP_H

//1、头文件
/********************************************************************************************************************************************************************/
#include "stm32f1xx_hal.h"

//2、宏定义
/********************************************************************************************************************************************************************/
//1、引用范围 Ex_Flash.c
////////////*******************************************************/
#define  EXFLASH_MOSI_PORT  GPIOA
#define  EXFLASH_MOSI_PIN   GPIO_PIN_7 

#define EXFLASH_MISO_PORT   GPIOA
#define EXFLASH_MISO_PIN    GPIO_PIN_6

#define EXFLASH_CLK_PORT   GPIOA
#define EXFLASH_CLK_PIN    GPIO_PIN_5

#define EXFLASH_CS1_PORT   GPIOA
#define EXFLASH_CS1_PIN    GPIO_PIN_4

//2、应用范围：Led_Ctrl.c
////////////*******************************************************/
#define LED_CTRL1_PORT   GPIOB
#define LED_CTRL1_PIN    GPIO_PIN_0 

//3、引用范围：Signal_Generation.c
////////////*******************************************************/
#define PAC9685_IIC1_SCL_PORT  GPIOB
#define PAC9685_IIC1_SCL_PIN   GPIO_PIN_6

#define PAC9685_IIC1_SDA_PORT  GPIOB
#define PAC9685_IIC1_SDA_PIN   GPIO_PIN_7

//4、应用范围：Wifi.c
////////////*******************************************************/
#define WIFI_IO1_PORT  GPIOA
#define WIFI_IO1_PIN   GPIO_PIN_0

#define WIFI_TX_PORT   GPIOA
#define WIFI_TX_PIN    GPIO_PIN_3

#define WIFI_RX_PORT   GPIOA
#define WIFI_RX_PIN    GPIO_PIN_2

#define WIFI_CHPD_PORT  GPIOB
#define WIFI_CHPD_PIN   GPIO_PIN_11

//5、Others.c
////////////*******************************************************/
#define DEBUG_TX_PORT  GPIOA
#define DEUBG_TX_PIN   GPIO_PIN_9

#define DEBUG_RX_PORT  GPIOA
#define DEBUG_RX_PIN   GPIO_PIN_10

#define IO1_PORT   GPIOA
#define IO1_PIN    GPIO_PIN_8

#define IO2_PORT   GPIOA
#define IO2_PIN    GPIO_PIN_11

#define IO3_PORT  GPIOA
#define IO3_PIN   GPIO_PIN_12

#define IO4_PORT  GPIOB
#define IO4_PIN   GPIO_PIN_5

#define IO5_PORT  GPIOB
#define IO5_PIN   GPIO_PIN_12

#define IO6_PORT  GPIOB
#define IO6_PIN   GPIO_PIN_13

#define IO7_PORT  GPIOB
#define IO7_PIN   GPIO_PIN_14

#define IO8_PORT  GPIOA
#define IO8_PIN   GPIO_PIN_15



//3、类型定义
/********************************************************************************************************************************************************************/



//4、变量声明
/********************************************************************************************************************************************************************/


//5、函数声明
/********************************************************************************************************************************************************************/



#endif






























