#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    int ppid, fd1, fd2;
    fd1 = fork(); //Create a child process
	char buff[100];

    if (fd1 > 0) //Parent process
    {
	printf("A child created with pid %d\n",fd1);

	//sleep(3);

	char buff[100];
	//printf("\n");
	//system(buff);
	       // char buff[100];
        sprintf(buff, "/proc/%d/status", fd1);
        //printf("\n");
        fd1 = open(buff, O_RDONLY); //Open file in read only mode
        int line = 0;
        while(line < 3) //Loop to print process status
        {
            int ret = read(fd1, buff,1); //Read from file
            write(1,buff,ret); //To write into stdout
            if(buff[0] == '\n')
                line++;
        }

	fd2 = fork(); //To create second child process
	if (fd2 == 0) //Second child process
	{
	    sleep(3);
	    /*if(system(buff) != -1) //Condition to check if process is cleared or not
	    {
		printf("process %d cleared by init",pid1);
	    }
	    else
	    {
		printf("Error\n");
	    }*/
	            char buff[100];
        sprintf(buff, "/proc/%d/status", fd1);
        //printf("\n");
        fd1 = open(buff, O_RDONLY); //Open file in read only mode
        int line = 0;
        while(line < 3) //Loop to print process status
        {
            int ret = read(fd1, buff,1); //Read from file
            write(1,buff,ret); //To write into stdout
            if(buff[0] == '\n')
                line++;
        }

	    exit(0);
	}
	else
	{
	    exit(1);
	}
    }
    else if (fd1 == 0 ) //Child process
    {
    	sleep(3);
/*	char buff[100];
	int ppid = getpid();
	//system(buff1);
	      //  char buff[100];
        sprintf(buff, "/proc/%d/status", fd1);
        //printf("\n");
        fd1 = open(buff, O_RDONLY); //Open file in read only mode
        int line = 0;
        while(line < 3) //Loop to print process status
        {
            int ret = read(fd1, buff,1); //Read from file
            write(1,buff,ret); //To write into stdout
            if(buff[0] == '\n')
                line++;
        }*/


	exit(0);
    }
}
