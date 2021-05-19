#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    int ppid, pid1, pid2;
    pid1 = fork(); //Create a child process

    if (pid1 > 0) //Parent process
    {
	printf("A child created with pid %d\n",pid1);

	sleep(3);

	char buff[100];
	sprintf(buff, "cat /proc/%d/status | head  -3", pid1);
	printf("\n");
	system(buff);
	pid2 = fork(); //To create second child process
	if (pid2 == 0) //Second child process
	{
	    sleep(3);
	    if(system(buff) != -1) //Condition to check if process is cleared or not
	    {
		printf("process %d cleared by init",pid1);
	    }
	    else
	    {
		printf("Error\n");
	    }
	    exit(0);
	}
	else
	{
	    exit(1);
	}
    }
    else if (pid1 == 0 ) //Child process
    {
	char buff1[100];
	int ppid = getpid();
	sprintf(buff1, "cat /proc/%d/status | head  -3",ppid);
	system(buff1);

	exit(0);

    }
    else
    {

	printf("Error.\n");
    }
}
