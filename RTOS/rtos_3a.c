/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*					WIN32 PORT & LINUX PORT
*                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
*                 (Similar to Example 1 of the 80x86 Real Mode port by Jean J. Labrosse)
*                                           All Rights Reserved
** *****************************************************************************************************
*		Further modified by 	mikael.jakas@puv.fi & 
* 					Jukka.matila@vamk.fi
* *****************************************************************************************************
*                                               EXAMPLE #1
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                        2       /* Number of identical tasks                          */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];
char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */
OS_EVENT	*RandomSem;
OS_EVENT	*RanSem;
INT8U		err;

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void TaskStart(void *data);        /* Function prototype of Startup task           */
void Random_Print(void *data);    /* Function prototypes of Print_fixedPos Task     */
void Print_to_Screen(INT8U *text_ptr);
void Task1(void *data);
void Task2(void *data);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

int  main(void)
{
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSInit();                                              /* Initialize uC/OS-II                      */
    RandomSem=OSSemCreate(1);
    RanSem =OSSemCreate(1);
    
    OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
    OSStart();                                             /* Start multitasking                       */
    
return 0;
}


/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
void  TaskStart(void *pdata)
{
    INT16S key;
    INT8U symbol;


    pdata = pdata;                                         /* Prevent compiler warning                 */
    symbol = 'Q';

    OSTaskCreate(Task1, (void *)&symbol, (void *)&TaskStk[0][TASK_STK_SIZE - 1], 1);
    OSTaskCreate(Task2, (void *)&symbol, (void *)&TaskStk[0][TASK_STK_SIZE - 1], 2);
    //OSSemPend(RandomSem, 0, &err);

    for (;;) {

        if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
            if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
                exit(0);  	                           /* End program                              */
            }
        }

        OSTimeDlyHMSM(0, 0, 1, 0);                         /* Wait one second                          */
    }
}

/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/


void Random_Print(void *data)
{
    INT8U  x;
    INT8U  y;
    INT8U  i;

#ifdef __WIN32__
    srand(GetCurrentThreadId());
#endif
#ifdef __LINUX__
    srand(getppid());
#endif

    for (i=0;i<10;i++) {

        x = rand()%79+1;                        /* Find X position where task number will appear      */
        y = rand()%24+1;                        /* Find Y position where task number will appear      */

        /* Display the task number on the screen              */
	PC_DispClrScr(DISP_FGND_BLACK + DISP_BGND_GRAY);
        PC_DispChar(x, y, *((char *)data), DISP_FGND_BLACK + DISP_BGND_GRAY);
	OSTimeDlyHMSM(0, 0, 1, 0);                         /* Wait one second                          */
        OSTimeDly(1);                            /* Delay 1 clock tick                                 */
    	
}
  //OSTaskDel(1);
  OSSemPost(RandomSem);
} /*function code*/

void Print_to_Screen(INT8U *text_ptr)
{
 INT8U delay;
 INT8U symbols[80]= {' '};
 delay = -1;

 OSSemPend(RandomSem, 0, &err);  /*Acquire semaphore for random number generator numbers*/      
 while(delay < 1 || delay >3)
	delay = rand();
 OSSemPost(RandomSem);

 PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK); 
 OSTimeDlyHMSM(0, 0, delay, 0);
 PC_DispStr(33, 15, text_ptr, DISP_FGND_WHITE);
 OSTimeDlyHMSM(0, 0, delay, 0);
 PC_DispStr(33, 0, symbols, DISP_FGND_GREEN);
}
/*function*/

void Task1(void *data){
#ifdef __WIN32__
    srand(GetCurrentThreadId());
#endif
#ifdef __LINUX__
    srand(getppid());
#endif
 for (;;){
        OSSemPend(RanSem, 0, &err);
        Print_to_Screen("Task A");
	OSTimeDlyHMSM(0, 0, 1, 0);
        OSSemPost(RanSem);
   }   
}

void Task2(void *data){
#ifdef __WIN32__
    srand(GetCurrentThreadId());
#endif
#ifdef __LINUX__
    srand(getppid());
#endif
 for (;;){
        OSSemPend(RanSem, 0, &err);
        Print_to_Screen("Task B");
	OSTimeDlyHMSM(0, 0, 1, 0);
        OSSemPost(RanSem);
   }   
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      NON-TASK FUNCTIONS
*********************************************************************************************************
*/
