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
    int pid, pid1, new_fd, new_fd1, i = 1, j = 0, count = 0, count1 = 1, status;

    if (argc == 1) //Condition for valid arguments
    {
	printf("Error: No arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
    }
    else if(argc < 4) //Condition if sufficient arguments are not present
    {
	printf("Error: Insufficient arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
    }
    else //Condition if valid arguments are passed
    {
	while(strcmp(argv[i++],"|") != 0)
	{

	    count++;
	}
	char *array[count + 1];
	for(i = 1; i < count + 1; i++) //Loop to store arguments in an array
	{
	    array[i - 1] = argv[i];
	}
	array[i] = NULL;

	i = count + 2;

	while(argv[i++] != NULL)
	{
	    count1++;
	}
	char *array1[count1 + 1];

	for(i = count + 2;i < argc;i++)
	{
	    array1[j] = argv[i];
	    j++;
	}
	array1[j] = NULL;

	int fd[2];

	pipe(fd);

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
	    for(i = 0;i < argc;i++)
	    {
		printf("%s",array[i]);
	    }
	    execvp(array[0], array);

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
		execvp(*array1, array1);

		return 1;
	    }
	    else
	    {
		wait(&status);
		return 1;
	    }
	}
    }
}
