#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
    int pid, pid1, new_fd, new_fd1, i = 1, j = 0,k = 0, count = 0, count1 = 0, status;

    if (argc == 1) //Condition for valid arguments
    {
	printf("Error: No arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
    }
   /* else if(argc < 6) //Condition if sufficient arguments are not present
    {
	printf("Error: Insufficient arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
    }*/
    else //Condition if valid arguments are passed
    {
	while(strcmp(argv[i++],"|") != 0)
	{
	    count++;
	}
	argv[count] = NULL;

	i = count + 1;

	while(strcmp(argv[i++],"|") != 0)
	{
	    j++;
	}
	char *array[j + 1];
	for(i = 1; i < j + 1; i++) //Loop to store arguments in an array
	{
	    array[i - 1] = argv[i];
	}
	array[i] = NULL;
	int z;
	i = j + 1;
	while(argv[i++] != NULL)
	{
	    count1++;
	}
	char *array1[count1 + 1];

	for(i = 1;i < j + 1;i++)
	{
	    array1[k] = argv[i];
	    k++;
	}
	array1[k] = NULL;

	int fd[2], fd1[2];

	pipe(fd);
	pipe(fd1);

	pid = fork(); //Create child process

	if (pid <  0)
	{
	    printf("Error\n");
	    return 1;
	}

	else if (pid == 0) //Child process
	{
	    close(fd[0]);
	    new_fd = dup2(fd[1], 1);
	    execvp(*argv, ++argv);
	    perror("Error\n");
	    return 1;
	}
	else //Parent process
	{
	    pid1 = fork();
	    if (pid1 < 0)
	    {
		printf("Error\n");
	    }
	    else if (pid1 == 0)
	    {
		close(fd[1]);
		new_fd1 = dup2(fd[0], 0);
		execvp(*array, array);

		return 1;
	    }
	   /* else
	    {
	    	int pid2;
	    	pid2 = fork();
	    if (pid2 < 0)
	    {
		printf("Error\n");
	    }
	    else if (pid2 == 0)
	    {
		close(fd1[1]);
		new_fd1 = dup2(fd1[0], 0);
		execvp(*array1, array1);

		return 1;
	    }*/
	    else
	    {    
		wait(&status);
		return 1;
	    }
//	}
    }
}
}

