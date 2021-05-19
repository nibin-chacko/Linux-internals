#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <string.h>

int word_count(int fd, int *lines, int *words, int *chars) //Function to count
{
    *lines = 0, *words = 0, *chars = 0;
    int ret,i;
    char chr,arr[1000];
    while ((ret = read(fd, &chr, 1)) && ret == 1 ) //Loop to count characters
    {
	arr[*chars] = chr;
	(*chars)++;
    }
    for(i = 0; i < (*chars); i++) //Loop to count words and lines 
    {
	if (arr[i] == 10) //Condition for new line
	    (*lines)++;
	if (((arr[i] != 32 && arr[i] != 9 ) && (arr[ i + 1] == 32)) || ((arr[i] !=32 && arr[i] != 9) && arr[i + 1] == 9) || ((arr[i] !=32 && arr[i] != 9 && arr[i] != 10 )  && (arr[i + 1] == 10)) ) //Condition for new words
	    (*words)++; 
    }
}

void print_count(char *path, int lines, int words, int chars,int line_flag, int word_flag, int char_flag) //Function to print the count
{
    if(line_flag == 0 && word_flag == 0 && char_flag == 0) //Condition if no flag is set
	printf("%3d %3d %3d %s\n", lines,words,chars,path);
    else 
    {
	if(line_flag == 1)
	    printf("%3d ", lines);
	if(word_flag == 1)
	    printf("%3d ", words);
	if(char_flag == 1)
	    printf("%3d ", chars);
	printf("%s\n", path);
    }
}

int main(int argc, char *argv[])
{
    int lines = 0, words =0, chars = 0, line_flag = 0, word_flag = 0, char_flag = 0, total_line = 0, total_word = 0, total_char = 0,tfndi = 0, option, total = 0;

    while ((option = getopt(argc, argv, "wlc")) != -1)
    {
	switch (option)  //Switch case for setting flag according to options passed
	{
	    case 'w': //Case for words
		word_flag = 1;
		tfndi = 1;
		break;
	    case 'l': //Case for lines
		line_flag = 1;
		tfndi = 1;
		break;
	    case 'c': //Case for characters
		char_flag = 1;
		tfndi = 1;
		break;
	    default:  //Default case
		tfndi = 1;
		printf("Error\nUsage: <filename> <options>\n");
	}
    }

    if (argv[optind] == NULL) //Condition if no file is passed
    {
	// int fd = dup(0);
	word_count(0, &lines, &words, &chars);
	//close(fd);
	print_count("stdin",lines, words, chars, line_flag, word_flag, char_flag);
    }
    else if (argc > 1) //Condition if file is passed
    {
	while(argv[optind] != NULL)
	{
	    int fd = open(argv[optind], O_RDONLY); //Open file in read mode
	    if (fd == -1) 
	    {
		printf("Error: File %s does not exist\n",argv[optind]);
	    }
	    else
	    {
		word_count(fd, &lines, &words, &chars);
		close(fd);
		print_count("file",lines, words, chars, line_flag, word_flag, char_flag);
	    }
	    total_line = total_line + lines;
	    total_word = total_word + words;
	    total_char = total_char + chars;
	    optind++;
	    ++total;
	}
	if(total > 1) //Condition to print total count
	{
	    print_count("total",total_line, total_word, total_char, line_flag, word_flag, char_flag);
	}
    }
}





