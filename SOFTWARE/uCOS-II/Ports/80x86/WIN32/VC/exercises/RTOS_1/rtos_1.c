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

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void TaskStart(void *data);        /* Function prototype of Startup task           */
void Print_fixedPos(void *data);    /* Function prototypes of Print_fixedPos Task     */


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
    symbol = 'X';

    OSTaskCreate(Print_fixedPos, (void *)&symbol, (void *)&TaskStk[0][TASK_STK_SIZE - 1], 1);

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

void Print_fixedPos(void *data)
{
    INT8U  x;
    INT8U  y;

#ifdef __WIN32__
    srand(GetCurrentThreadId());
#endif
#ifdef __LINUX__
    srand(getppid());
#endif

    for (;;) {

        x = 15;                        /* Find X position where task number will appear      */
        y = 15;                        /* Find Y position where task number will appear      */

        /* Display the task number on the screen              */
        PC_DispChar(x, y, *((char *)data), DISP_FGND_BLACK + DISP_BGND_GRAY);

        OSTimeDly(1);                            /* Delay 1 clock tick                                 */
    }
} /*function code*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                      NON-TASK FUNCTIONS
*********************************************************************************************************
*/
