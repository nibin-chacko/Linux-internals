#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    int fd, fd1, ppid, pid1, pid2;
    pid1 = fork(); //Create a child process
    char buffer[2], buffr[2];
    if (pid1 > 0) //Parent process
    {
	printf("A child created with pid %d\n",pid1);

	sleep(3);

	char buff[100];
	sprintf(buff, "/proc/%d/status", pid1);
	printf("\n");
	fd1 = open(buff, O_RDONLY); //Open file in read only mode
	int line = 0;
	while(line < 3) //Loop to print process status
	{
	    int ret = read(fd1, buffer,1); //Read from file
	    write(1,buffer,ret); //To write into stdout
	    if(buffer[0] == '\n') 
		line++;
	}
	pid2 = fork(); //To create second child process
	if (pid2 == 0) //Second child process
	{
	    sleep(3);
	//sprintf(buff, "/proc/%d/status", pid1);
	fd1 = open(buff, O_RDONLY); //Open file in read only mode
	    line=0;
	while(line < 3) //Loop to print process status
	{
	    int ret = read(fd1, buffer,1); //Read from file
	    write(1,buffer,ret); //To write into stdout
	    if(buffer[0] == '\n') 
		line++;
	}
	    if(fd1 != -1) //Condition to check if process is cleared or not
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
	sprintf(buff1, "/proc/%d/status",ppid);
	fd = open(buff1, O_RDONLY); //Open file in read mode

	int line1 = 0;
	while(line1 < 3) //Loop to print process status
	{
	    int ret1 = read(fd1, buffr,1); //Read from file
	    write(1,buffr,ret1); //To write into stdout
	    if(buffr[0] == '\n') 
		line1++;
	    //sleep(3);
	}
	exit(0);

    }
    else
    {

	printf("Error.\n");
    }
}
