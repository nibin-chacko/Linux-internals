#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

    int i, pid1, status;
    char *array[argc];

    if(argc < 2) //Condition for valid arguments
    {
	printf("No arguments passed\nUsage:\n./exe_child args...\n");
    }
    else //Condition if valid arguments are passed
    {
	for(i = 0; i < argc - 1; i++) //Loop to store arguments in an array
	{
	    array[i] = argv[i + 1]; //Store arguments in an array
	}
	array[i] = NULL;

	pid1 = fork(); //Create child process
	if (pid1 < 0)
	{
	    printf("Error\n");
	}
	else if(pid1 == 0) //Child process
	{
	    printf("This is the CHILD process with id %d\n",getpid());
	    execvp(argv[1], array); //Execute commands passed
	    exit(0);
	}
	else //Parent process
	{
	    wait(&status); //Parent process waiting for child process to complete

	    if(WIFEXITED(status)) //Condition if child terminated normally
	    {
		printf("Child exited with status %d\n", WEXITSTATUS(status));
	    }
	    else //Condition if child termimated using signal
	    {
		printf("Child terminated abnormally\nChild exited with code %d\n",WTERMSIG(status));
	    }
	}
	return 0;
    }
}

