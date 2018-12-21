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
typedef struct TaskCounter {
    INT8U count1;
    INT8U count2;
} TaskCounter;

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];
char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */
OS_EVENT	*RandomSem;
OS_EVENT	*RanSem;
INT8U		err;
TaskCounter	count;

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void TaskStart(void *data);        /* Function prototype of Startup task           */
void Task1(void *data);
void Task2(void *data);
INT8U read_value(INT8U task);
void write_value(INT8U task, INT8U value);

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

    count.count1 = 0;
    count.count2 = 0;
    
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

    pdata = pdata;                                         /* Prevent compiler warning                 */
 
    OSTaskCreate(Task1, NULL, (void *)&TaskStk[0][TASK_STK_SIZE - 1], 1);
    OSTaskCreate(Task2, NULL, (void *)&TaskStk[0][TASK_STK_SIZE - 1], 2);
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

INT8U read_value(INT8U task){
    INT8U temp=0;
    OSSemPend(RandomSem, 0, &err);
    if(task==1){
        temp=count.count1;
    }
    if(task==2){
        temp=count.count2;
    }
    OSSemPost(RandomSem);
    return temp;
}

void write_value(INT8U task, INT8U value){
    OSSemPend(RandomSem, 0, &err);
    if(task==1){
        count.count1=value;
    }
    if(task==2){
        count.count2=value;
    }
    OSSemPost(RandomSem);
}

void Task1(void *data){
	INT8U counter1 =0;
	INT8U counter2;

	for(;;){
		counter2 = read_value(2);
		counter1 ++;
		printf("Task B running time : %d\n", counter2);
		write_value(1, counter1);
        	OSTimeDlyHMSM(0,0,1,0);
	}
}

void Task2(void *data){
	INT8U counter1 =0;
	INT8U counter2;

	for(;;){
		counter1 = read_value(1);
		counter2 ++;
		printf("Task B running time : %d\n", counter1);
		write_value(2, counter2);
        	OSTimeDlyHMSM(0,0,1,0);
	}
}




/*$PAGE*/
/*
*********************************************************************************************************
*                                      NON-TASK FUNCTIONS
*********************************************************************************************************
*/
