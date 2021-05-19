
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main()
{
    char buff[100];
    int fd1,fd2;
    fd1 = fork(); //Creating child process
    if (fd1 < 0)
    {
	printf("Error\n");
    }
    else if(fd1 == 0) //Child process
    {
	sleep(1);
    }
    else //Parent process
    {
	int pid = fd1;

	printf("A child created with pid %d\n",pid);
	sprintf(buff, "/proc/%d/status", fd1);
	int fd1 = open(buff, O_RDONLY); //Open file in read only mode
	int line = 0;
	char ch[10];
	while(line < 3) //Loop to print process status
	{
	    int ret = read(fd1, ch,1); //Read from file
	    write(1,ch,ret); //To write into stdout
	    if(ch[0] == '\n') //Condition for new line
		line++;
	}
	close(fd1);
	sleep(3);
	fd1 = open(buff, O_RDONLY); //Open file in read only mode
	line = 0;
	while(line < 3) //Loop to print process status
	{
	    int ret = read(fd1, buff,1); //Read from file
	    write(1,buff,ret); //To write into stdout
	    if(buff[0] == '\n') //Condition for new line
		line++;
	}
	close(fd1);
	int fd2 =fork(); //Create child process
	if(fd2 < 0)
	{
	    perror("Error\n");
	    return 1;
	}
	else if(fd2 == 0)
	{
	    sprintf(buff, "/proc/%d/status", fd1);
	    int fd3 = open(buff, O_RDONLY); //Open file in read only mode

	    if(fd3 != -1)
	    {
		sleep(3);
		printf("Process %d cleared by init\n",pid);
		return 1;

	    }
	}
    }
}




