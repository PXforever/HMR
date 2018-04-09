#ifndef __DEVICE_H
#define __DEVICE_H

//1��ͷ�ļ�
/********************************************************************************************************************************************************************/
#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"

//2�����Ͷ���
/********************************************************************************************************************************************************************/
//�豸open/close/read/write/lseek/ioctl ��������״̬���ö��
typedef enum 
{
    DEV_FAIL = 0,   //���д���
    DEV_OK,         //���гɹ�
} Dev_Run_Resul_Enum;      


#pragma pack(push)
#pragma pack(1)

struct devopt
{
    Dev_Run_Resul_Enum (*open)(void);
    Dev_Run_Resul_Enum (*close)(void);
    Dev_Run_Resul_Enum (*read)(char *buf, int len, uint32_t *address);
    Dev_Run_Resul_Enum (*write)(char *buf, int len, uint32_t *address);
    Dev_Run_Resul_Enum (*lseek)(int ptr, int dir);
    Dev_Run_Resul_Enum (*ioctl)(int request, void *args);
};

struct device
{
    int id;
    struct devopt opt;
};


#pragma pack(pop)


//3���궨��
/********************************************************************************************************************************************************************/
#define DEVICE_SUM 6 //����ָ����������ע��8����Χ�豸


#define DEVICE_ZERO 0   //DEVICE_DEFINE(EX_FLASH,DEVICE_ONE)     �ⲿFLASHоƬ-W25Q64
#define DEVICE_ONE 1   	//DEVICE_DEFINE(LED_CTRL,DEVICE_TWO)     LEDָʾ��
#define DEVICE_TWO 2 		//DEVICE_DEFINE(SIGNAL_GENERATION,DEVICE_THREE)     PAC9685 PWM�ź�����IC
#define DEVICE_THREE 3  //DEVICE_DEFINE(WIFI,DEVICE_FOUR)                   ESP8266 WIFIģ��
#define DEVICE_FOUR 4 	//DEVICE_DEFINE(DEBUG_USART,DEVICE_FIVE)            ��ӡ����
#define DEVICE_FIVE 5   //DEVICE_DEFINE(IO_CTRL,DEVICE_SIX)                 8��IO�ڵĿ���

#define DEVICE_CTRL_FIRST_ADDRESS 0x8005000

#define DEVICE_DEFINE(DEV, ID)                                                                             \
    static Dev_Run_Resul_Enum DEV##_open(void);                                                                           \
    static Dev_Run_Resul_Enum DEV##_close(void);                                                                          \
    static Dev_Run_Resul_Enum DEV##_write(char *buf, int len, uint32_t *address);                                          \
    static Dev_Run_Resul_Enum DEV##_read(char *buf, int len, uint32_t *address);                                           \
    static Dev_Run_Resul_Enum DEV##_lseek(int ptr, int dir);                                                              \
    static Dev_Run_Resul_Enum DEV##_ioctl(int request, void *args);                                                       \
    static struct device DEV __attribute__((at(DEVICE_CTRL_FIRST_ADDRESS + ID * sizeof(struct device)))) =						                  	\
    {                                                                                                  \
            .id = ID,                                                                                      \
            .opt.open = &DEV##_open,                                                                        \
            .opt.close = DEV##_close,                                                                      \
            .opt.read = DEV##_read,                                                                        \
            .opt.write = DEV##_write,                                                                      \
            .opt.lseek = DEV##_lseek,                                                                      \
            .opt.ioctl = DEV##_ioctl,                                                                      \
    };

		
#define DEVICE_FUNC_DEFINE_OPEN(DEV) \
static Dev_Run_Resul_Enum DEV##_open(void)

#define DEVICE_FUNC_DEFINE_CLOSE(DEV) \
static Dev_Run_Resul_Enum DEV##_close(void)

#define DEVICE_FUNC_DEFINE_WRITE(DEV) \
static Dev_Run_Resul_Enum DEV##_write(char *buf, int len, uint32_t *address)

#define DEVICE_FUNC_DEFINE_READ(DEV) \
static Dev_Run_Resul_Enum DEV##_read(char *buf, int len, uint32_t *address)

#define DEVICE_FUNC_DEFINE_LSEEK(DEV) \
static Dev_Run_Resul_Enum DEV##_lseek(int ptr, int dir)

#define DEVICE_FUNC_DEFINE_IOCTL(DEV) \
static Dev_Run_Resul_Enum DEV##_ioctl(int request, void *args)


 

//4����������
/********************************************************************************************************************************************************************/
extern struct device *device_list[];

//5����������
/********************************************************************************************************************************************************************/
extern Dev_Run_Resul_Enum DEV_Open(int device_num);
extern Dev_Run_Resul_Enum DEV_Close(int device_num);
extern Dev_Run_Resul_Enum DEV_Read(int device_num, char *ptr, int len,uint32_t* address);
extern Dev_Run_Resul_Enum DEV_Write(int device_num, char *ptr, int len,uint32_t* address);
extern Dev_Run_Resul_Enum DEV_Lseek(int device_num, int ptr, int dir);
extern Dev_Run_Resul_Enum ioctl(int device_num, int request, ...);
	

#endif

// static int DEV_Open(struct inode *inode, struct file *file)
// static ssize_t DEV_Read(struct file *file, char __user *buf, size_t count, loff_t *pos)
// static ssize_t DEV_Write(struct file *file, char __user *buf, size_t count, loff_t *pos)
// static loff_t DEV_Lseek(struct file *file, loff_t offset, int dir)
// static long DEV_Ioctl(struct file *file, unsigned int cmd, unsigned long *arg)
// static int DEV_Close(struct inode *inode, struct file *file)
