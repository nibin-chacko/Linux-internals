#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc,char **argv)
{
    if (argc < 2) //Condition for valid arguments
    {
	printf("Insufficient arguments\nUsage:- ./fcntl_lock <filename>\n");
    }
    else
    {
	struct flock lock;
	int fd = open(argv[1], O_WRONLY|O_TRUNC); //Open file in write mode
	int num = 10,pid,fd1,fd2;
	pid  = fork(); //Create a new process
	if(pid > 0)
	{
	    lock.l_type = F_WRLCK;
	    fcntl(fd, F_SETLKW, &lock); //Set lock in file
	    fd1 = dup2(fd, 1);	
	    while(num--)
		printf("This is parent\n");
	    lock.l_type = F_UNLCK;
	    fcntl(fd, F_UNLCK, &lock); //To remove the lock from the file	
	}
	else if (pid == 0)
	{
	    lock.l_type = F_WRLCK;
	    fcntl(fd, F_SETLKW, &lock); //Set lock in file	
	    fd2 = dup2(fd, 1);	
	    while(num--)
		printf("This is child\n");
	    lock.l_type = F_UNLCK;
	    fcntl(fd, F_UNLCK, &lock);   //To remove the lock from the file
	}
	else
	{
	    printf("Error\n");
	}
    }
}
