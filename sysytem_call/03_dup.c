#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>


int main(int argc,char **argv)
{
    int option, fd, fd1, new_fd;

    if (argc < 2)
    {
	printf("Error : Enter a filename\n");
	printf("Usage : ./a.out < filename > \n ");
    }
    else
    {
	printf("Choose the option you want to continue with : \n 1.dup \n 2.dup2 \n");
	scanf("%d",&option);
	switch (option)  //Switch case for selecting the option
	{
	    case 1:  //Case for dup
		fd = open(argv[1], O_WRONLY);  //Opening file in write only mode
		close (1); //Closing stdout
		new_fd = dup(fd);
		printf("Hello from dup\n");
		break;

	    case 2:  //Case for dup2
		fd1 = open(argv[1], O_WRONLY); //Opening the file in write only mode
		new_fd = dup2(fd1, 1);
		printf("Hello from dup2\n");
		break;

	    default: //Case for valid inputs
		printf("Enter a valid option\n");

	}

    }


}
