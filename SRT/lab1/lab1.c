#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


#define US_PER_SEC      1000000
#define BILLION			1000000000
#define SIGRT 			SIGRTMIN


void doControl() 
{
   int t;
   int dt = 0;
   int x = (rand() % 10 + 1) % 9;
   dt = rand() % 30000;      
   t = 500000 + dt;
   printf("########## usleep %f sec\n", t / (double)(US_PER_SEC));
   if (x == 0) while(true);   
   usleep(t);       
}

void deadlineHandler(int sign) 
{
	printf("#### Deadline exceeded ####\n");
}

void alarmHandler(int sign)
{
	printf("##### Restart requered #####\n");
	raise(SIGUSR1);
}


int main()
{
	srand(time(NULL));

	int delay = 3;
	double dt = 0.5;
	int hard_dt = 1;
	double soft_dt = 0.04 * dt;

	printf("soft limit %f sec\n", dt + soft_dt);
	printf("hard limit %i sec\n\n", hard_dt);

	signal(SIGALRM, alarmHandler);
	signal(SIGRT, deadlineHandler);

	while(true) 
	{
		alarm(hard_dt);

		struct timespec start_time, stop_time;
		if (clock_gettime(CLOCK_REALTIME, &start_time) == -1)
		{
			perror("clock gettime");
			return EXIT_FAILURE;
		}
		doControl(); 
		if (clock_gettime(CLOCK_REALTIME, &stop_time) == -1) 
		{
			perror("clock gettime");
			return EXIT_FAILURE;
		}
		alarm(0);

		double duration = (double)(stop_time.tv_sec - start_time.tv_sec) + (double)(stop_time.tv_nsec - start_time.tv_nsec)/(double)BILLION;
		printf("########## duration %f sec\n", duration);
		if (duration > dt + soft_dt)
		{
			raise(SIGRT);
		}
		
		printf("\n");
		sleep(delay);       
	}
	return EXIT_SUCCESS;
}