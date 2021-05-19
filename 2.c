
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
    fd1=fork();
    if(fd1 == 0)
    {
    	sleep(1);
    }
    else
    {
        sprintf(buff, "/proc/%d/status", fd1);
        //printf("\n");
        int fd1 = open(buff, O_RDONLY); //Open file in read only mode
        int line = 0;
        char ch[10];
        while(line < 3) //Loop to print process status
        {
            int ret = read(fd1, ch,1); //Read from file
            write(1,ch,ret); //To write into stdout
            if(ch[0] == '\n')
                line++;
        }
        close(fd1);
        sleep(3);
        printf(buff);
        //printf("\n");
       fd1 = open(buff, O_RDONLY); //Open file in read only mode
       perror("open");
        line = 0;
        printf("hi%d\n",fd1);
        while(line < 3) //Loop to print process status
        {
            int ret = read(fd1, buff,1); //Read from file
            write(1,buff,ret); //To write into stdout
            if(buff[0] == '\n')
                line++;
        }
        close(fd1);
        
    	
    }
}

        
    	

