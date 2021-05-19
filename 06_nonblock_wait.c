#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include <sys/wait.h>

int main()
{

    int pid1, ppid, status;

    pid1 = fork(); //Creating child process
    if (pid1 < 0)
    {
	printf("Error\n");
	return 1;
    }
    else if (pid1 == 0) //Condition for child process
    {
	sleep(5);
	exit(0); //Exit child process
    }
    else   //Condition for parent process
    {
	printf("A child created with pid %d\n",pid1);
	int pidwait;
	do
	{
	    pidwait = waitpid(pid1, &status, WNOHANG); //To check if child exited
	    if (pidwait == 0)
	    {
		printf("Parent is running...\n");
	    }
	    sleep(1);
	}while(pidwait == 0);

	if(WIFEXITED(status)) //Condition to check exit status of child
	{
	    printf("Child %d terminated normally with exit status %d\n", pid1, WEXITSTATUS(status));
	}
	printf("Parent Terminating\n");
    }
}

