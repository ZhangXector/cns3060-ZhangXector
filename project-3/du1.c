#include <stdio.h>
#include <dirent.h>
#include <unistd.h> // For getcwd()

void list_directories(char[]);

int main (int argc, char* argv[])
{
	if (argc == 1)
	{
		return 0;
	}
	else
	{
		while (--argc)
		{
			printf("%s:\n", *++argv);
			list_directories(*argv);
		}
	}
}

void list_directories(char dirname[])
{
	DIR* dir_ptr;
	struct dirent* direntp;

	if((dir_ptr = opendir(dirname)) == NULL)
	{
		fprintf(stderr, "du1: cannot open %s\n", dirname);
		exit(1);
	}
	else
	{
		while ((direntp = readdir(dir_ptr)) != NULL)
		{
			printf("%s\n", direntp->d_name);
		}
		closedir(dir_ptr);
	}
}
