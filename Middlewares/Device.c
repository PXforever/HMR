#include "Device.h"


struct device *device_list[DEVICE_SUM]= 
{
	 ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+0*sizeof(struct device))),
	 ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+1*sizeof(struct device))), 
	 ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+2*sizeof(struct device))), 
   ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+3*sizeof(struct device))),
   ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+4*sizeof(struct device))),
   ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+5*sizeof(struct device)))
};



/**********************************************************************
** ��������         :DEV_Open
** ������           :liupengcheng
** ��������         :2018-3-22
** �����޸���       :liupengcheng
** ����޸�����      :2018-3-22
** ��������         :ע���豸
** ��ڲ���         :
                        file����ע���豸�ı��
** ���ز���         :
                        none
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Open(int device_num)
{
    if (device_list[device_num]->opt.open==NULL||device_list[device_num]->id!=device_num)
    {
        return -1;
    }
    device_list[device_num]->opt.open();
    return 1;
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Close(int device_num)
{
    if (device_list[device_num]->opt.close==NULL||device_list[device_num]->id!=device_num)
    {
        return -1;
    }
    device_list[device_num]->opt.close();
    return 1;
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Read(int device_num, char *ptr, int len,uint32_t* address)
{
    if (device_list[device_num]->opt.read==NULL||device_list[device_num]->id!=device_num)
    {
        return -1;   
    }
    device_list[device_num]->opt.read(ptr, len, address);
    return 1;
}  


/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Write(int device_num, char *ptr, int len,uint32_t* address)
{
    if (device_list[device_num]->opt.read==NULL||device_list[device_num]->id!=device_num)
    {
        return -1;    
    }
    device_list[device_num]->opt.write(ptr, len,address);
    return 1;
}


#if 0

caddr_t _sbrk(int incr)
{
    extern char *end;
    extern char *_Main_Stack_Limit;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == NULL)
        heap_end = end;

    prev_heap_end = heap_end;

    if (heap_end + incr > _Main_Stack_Limit)
    {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

#endif




Dev_Run_Resul_Enum DEV_Lseek(int device_num, int ptr, int dir)
{
    if (device_list[device_num]->opt.lseek==NULL||device_list[device_num]->id!=device_num)
    {
        return -1;
    }
    device_list[device_num]->opt.lseek(ptr, dir);
    return 1;
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum ioctl(int device_num, int request, ...)
{
    va_list ap;
    int res = -1;

    if (device_num != device_list[device_num]->id||device_list[device_num]->opt.ioctl==NULL)
    {
        return -1;
    }
    va_start(ap, request);
    res = device_list[device_num]->opt.ioctl(request, va_arg(ap, void *));
    va_end(ap);
    return res;
}










