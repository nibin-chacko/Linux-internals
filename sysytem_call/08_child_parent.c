#include<stdio.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    //declaring variables
    int i;
    pid_t pid[3],pid1;
    int status;
    //child process
    if((pid[0] = fork()) == 0)
    {
	sleep(2);
    }
    else
    {
	//parent process
	printf("1) the child pid = %d\t the parent pid = %d\n",pid[0],getpid());
	if((pid[1] =fork()) == 0)
	{
	    sleep(4);
	}
	else
	{
	    printf("2) the child pid = %d\t the parent pid = %d\n",pid[1],getpid());
	    if((pid[2] = fork()) == 0)
		sleep(6);
	    else
	    {
		printf("3) the child pid = %d\t the parent pid = %d\n",pid[2],getpid());
		for(i = 0; i < 3;i++)
		{
		    	pid1 = waitpid(pid[i],&status,0);
		    if(WIFEXITED(status))
		    {
			printf("child %d termiated normaly %d\n",pid1,status);
		    }
		    else
		    {
			printf("child %d termiated abnormaly %d\n",pid1,status);
		    }
		}
	    }
	}
	//to check the status of child
    }
}
