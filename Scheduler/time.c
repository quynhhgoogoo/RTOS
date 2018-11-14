#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

void timer_init(void);
void timer_handler (int);

int main(){
  timer_init();
  while(1);
}

void timer_handler (int signum){
        static int count = 0;
        static int count1=610, count2=360,count3=260;
        printf ("\n%d (%d %d %d) : ", count+=10, count1-=10,count2-=10,count3-=10);

         if(count1==0){
          count1=610;
          printf ("Task 1");
        }
         if(count2==0){
          count2=360;
          printf("Task 2");
        }
         if(count3==0){
          count3=260;
          printf ("Task 3");
        }
}

void timer_init(void){
        struct sigaction sa;
        struct itimerval timer;

        /* Install timer_handler as the signal handler for SIGVTALRM. */
        memset (&sa, 0, sizeof (sa));
        sa.sa_handler = &timer_handler;
        sigaction (SIGVTALRM, &sa, NULL);

        /* Configure the timer to expire after 250 msec... */
        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 25000;

        /* ... and every 250 msec after that. */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 25000;

        /* Start a virtual timer. It counts down whenever this process is
        executing. */
        setitimer (ITIMER_VIRTUAL, &timer, NULL);

        /* Do busy work. */
        /*while (1);*/
}

