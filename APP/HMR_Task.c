//*********************************************************************
//
//           版权所有 (C), 2008-2028, 江西理工大学秒创八楼
//             -----------------------------------------------
//
//  文件作者:   liupengcheng
//  生成日期:   2018-3-21
//  功能描述:   人形机器人的多任务的实现
//  修改历史:
//  (1) 修改日期:
//      修改作者:
//      修改内容:
//
//*********************************************************************
#include "HMR_Task.h"



/**********************************************************************
** 函数名称         :HMR_Dispatch
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期     :2017 2017/11/27 21:38
** 功能描述         :通信调度任务（第一个线程）
** 入口参数         :
** 返回参数         :
												--none
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/

void HMR_Dispatch(void const *argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	
  for (;;)
  {
		
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}


/**********************************************************************
** 函数名称         :HMR_Protocol_Decode
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期     :2017 2017/11/27 21:38
** 功能描述         :HMR协议解码任务（第二个线程）
** 入口参数         :
** 返回参数         :
												--none
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void HMR_Protocol_Decode(void const *argument)
{
		for(;;)
		{

				osDelay(1);
		}
}



/**********************************************************************
** 函数名称         :HMR_Action_Ctrl
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期     :2017 2017/11/27 21:38
** 功能描述         :HMR运动控制任务（第三个线程）
** 入口参数         :
** 返回参数         :
												--none
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void HMR_Action_Ctrl(void const *argument)
{
		xQueue = xQueueCreate( 10, sizeof( struct AMessage * ) );
		for(;;)
		{

			int a=65;
			int *addr;
			addr = &a;
				// 发送消息 传递的消息内容指针的指针
			
			taskPrintf("a:0x%p, &a:0x%x, addr:0x%p, &addr:%x\n",a,&a,addr,addr);
			
			taskPrintf("addr:%x\n",(int*)addr);
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			while(1)
			
			osDelay(1);
				
		}
}


/**********************************************************************
** 函数名称         :HMR_Action_Ctrl
** 创建人           :liupengcheng
** 创建日期         :2017 2017/11/27 21:38
** 最新修改人       :liupengcheng
** 最近修改日期     :2017 2017/11/27 21:38
** 功能描述         :HMR运动控制任务（第四个线程）
** 入口参数         :
** 返回参数         :
												--none
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void HMR_Print(void const *argument)
{
	
		struct AMessage *pxRxedMessage;
		for(;;)
		{
			
				if( xQueue != 0 )
				{
						if( xQueueReceive( xQueue, &( pxRxedMessage ), ( TickType_t ) 10 ) )
								{
									
										// pcRxedMessage 指向 xMessage
										
										printf("print Task->    ");
//										printf("ID:%d, pxRxedMessage:0x%p, sizeof:%x\n",(*pxRxedMessage).ucMessageID,pxRxedMessage,sizeof(struct AMessage));
										printf("%s\n",(*pxRxedMessage).ucData);
										pxRxedMessage++;
								}
								
				}				
				osDelay(1);

    }
				
				
}





