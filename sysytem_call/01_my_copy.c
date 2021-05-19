#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <string.h>


int mycopy(int source,int dest) //Function to copy file
{
    int ret;
    char buff[50];
    do //Loop to copy content
    {
	ret = read(source, buff, 50); //To read from source file
	write(dest, buff, ret);  //To write into destination file
    }while(ret == 50);
    return 0;
}


int main(int argc,char **argv)
{
    struct stat buff;
    int fd, fd1;
    char chr;

    if (argc == 1 || (argc == 2 && strcmp(argv[1],"-p") != 0)) //Condition if sufficient arguments are not present
    {
	printf("Insufficient arguments\nUsage:- ./my_copy [option] <source file> <destination file>\n");
    }
    if( argc == 3 && strcmp(argv[1],"-p") == 0)
    {
	printf("Insufficient arguments\nUsage:- ./my_copy [option] <source file> <destination file>\n");
    }

    if( argc == 2 && strcmp(argv[1],"-p") == 0)
	printf("Destination file misiing\n");

    else if (argc == 3 && strcmp(argv[1],"-p") != 0)
    {
	fd = open(argv[1],O_RDONLY); //Open source file in read mode
	fd1 = open(argv[2],O_CREAT | O_EXCL | O_WRONLY,0666); //Open destination file in write mode
	if (fd1 == -1) //Condition if file failed to open
	{
	    if (errno = EEXIST) //Condition if error is due to existence of file
	    {
		printf("File dest.txt is already exists.\nDo you want to overwrite (y/n)\n");
		scanf("\n%c",&chr);
		if (chr == 'y')
		{
		    fd1 = open(argv[2],O_WRONLY|O_TRUNC);
		    mycopy(fd,fd1);
		}
		else
		{
		    exit(1);
		}
	    }
	}
	else
	{
	    mycopy(fd,fd1);
	}
	close(fd); //close file descriptors
	close(fd1);
    }
    if (argc == 4 && strcmp(argv[1],"-p") == 0) //Condition if -p option is present
    {
	fd = open(argv[2],O_RDONLY);

	fstat(fd, &buff);
	fd1 = open(argv[3], O_CREAT|O_EXCL|O_WRONLY,buff.st_mode&0777);

	umask(0);

	if (fd1 == -1) //Condition if file failed to open
	{
	    if (errno == EEXIST) //Condition if error is due to existence of file
	    {
		printf("File %s already exsist\ndo you want to overwrite(y/n):",argv[3]);
		scanf("%c", &chr);
		if (chr == 'y')
		{
		    fd1 = open(argv[3], O_WRONLY|O_TRUNC);
		    fchmod(fd1, buff.st_mode & 0777); //Copy permissions from source file to destination file
		    mycopy(fd,fd1);
		}
		else
		    exit(1);
	    }
	}

	else
	{
	    fd = open(argv[2],O_RDONLY);
	    mycopy(fd,fd1);
	}
	close(fd);
	close(fd1);
    }
    if (argc > 4) //Condition if more arguments are present
	printf("Usage: ./my_copy [option] <source file> <destination file>\n");


    return 0;
}

