#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{

    int fd[2], fd1[2], newfd, pid1, pid2, pid3, i = 1, count = 0, count1 = 0, count2 = 0, j = 0;
    
    if (argc == 1) //Condition for valid arguments
    {
	printf("Error: No arguments passed\nUsage: ./pipe <command 1> | <command 2>\n");
    }

    else if(argc < 6)
    {
	printf("Insufficient arguments passed!\n");
	printf("Usage : ./pipe <command 1> '|' <command 2> '|' <command 3>\n");
	return 1;
    }
    else
    {
    /* get command 1 from cli */
    while(strcmp(argv[i++], "|") != 0)
	count++; 
    char *array[count + 1];
    for(i = 1;i < count + 1;i++)
    {
	array[i - 1] = argv[i];
    }
    array[i - 1] = NULL;

    /* get command 2 from cli */
    i = count + 2;
    while(strcmp(argv[i++], "|") != 0)
	count1++;
    char *array1[count1 + 1];
    for(i = count + 2;strcmp(argv[i], "|") != 0;i++)
    {
	array1[j] = argv[i];
	j++;
    }
    array1[j] = NULL;

    /* get command 3 from cli */
    i = count + count1 + 3;
    while(argv[i++] != NULL)
	count2++;
    char *array2[count2 + 1];
    j = 0;
    for(i = count + count1 + 3; i < argc;i++)
    {
	array2[j] = argv[i];
	j++;
    }
    array2[j] = NULL;

    /* create a pipe to communicate between related processes */
    pipe(fd);
    pipe(fd1);

    /* creating child 1 */
    pid1 = fork();
    {
	switch(pid1)
	{
	    /* failure */
	    case -1:
		perror("fork");
		return 1;
		break;

		/* child 1 (command 1) */
	    case 0:
		close(fd1[0]);
		close(fd1[1]);		
		/* close read end of first pipe */
		close(fd[0]);
		/* closing stdout */
		close(1);
		/* duplicating fd to redirect stdout */
		newfd = dup(fd[1]);
		/* execute command 1*/
		execvp(array[0], array);
		perror("exec fail");
		return 1;

	    default:
		/* creating child 2 */
		pid2 = fork();

		switch(pid2)
		{
		    /* failure */
		    case -1:
			perror("fork");
			return 1;

			/* child 2 (command 2) */
		    case 0:
			/* close write end */
			close(fd[1]);
			/* close stdin */
			close(0);
			/* duplicate fd to redirect stdin */
			newfd = dup(fd[0]);
			/* close read end of second pipe */
			close(fd1[0]);
			/* close stdout */
			close(1);
			/* duplicate fd to redirect stdout */
			newfd = dup(fd1[1]);
			/* execute command 2 */
			execvp(array1[0], array1);
			perror("exec fail");
			return 1;
			break;

			/* parent */
		    default :
			/* close read and write end of first pipe */
			close(fd[0]);
			close(fd[1]);
			/* creating child 3 */
			pid3 = fork();

			switch (pid3)
			{   
			    /* failure */
			    case -1:
				perror("fork");
				return 1;

				/* child 3 (command 3) */	
			    case 0:
				/*close write end of second pipe */
				close(fd1[1]);
				close(0);
				newfd = dup(fd1[0]);
				execvp(array2[0],array2);
				perror("exec fail");
				return 1;
				break;
				/* parent */
			    default:
				wait(NULL);
			}
		}	
	}
    }
    }
}
