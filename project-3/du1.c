#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SUCCESS 0
#define FAILURE 1

#define CURRENT_DIR "."
#define PARENT_DIR ".."

void list_directories(char*);

int main (int argc, char* argv[])
{
	if (argc <= 2)
	{
		const char * directory = argc > 1 ? argv[1] : CURRENT_DIR;
		printf("%s:\n", directory);
		printf("==============================================================\n");
		list_directories(directory);
	}
	else
	{
		printf("Too many arguments. Usage: ./du1 [directory]\n");
		return FAILURE;
	}
	return SUCCESS;
}

void list_directories(char* dirname)
{
	DIR* directoryPointer;
	struct dirent* currentEntry;
	struct stat entryStats;

	if((directoryPointer = opendir(dirname)) == NULL)
	{
		perror(("du1: cannot open %s\n", dirname));
		exit(1);
	}
	else
	{
		while ((currentEntry = readdir(directoryPointer)) != NULL)
		{
			printf("Trying to get stats on %s\n", currentEntry->d_name);
			if (stat(currentEntry->d_name, &entryStats) != SUCCESS) 
			{
				perror("Failed to get file stats\n");
				//continue;
			}
			else if(strcmp(currentEntry->d_name, PARENT_DIR) && strcmp(currentEntry->d_name, CURRENT_DIR))
			{
				printf("Got file stats\n");
				if(S_ISDIR(entryStats.st_mode))
				{
					printf("%s: THIS IS A DIR!\n", dirname);
					list_directories(currentEntry->d_name);
				}
				printf("Size: %lld b\n", (long long)entryStats.st_size);
				//continue;
			}
			printf("==============================================================\n");
		}
		if(closedir(directoryPointer)!= SUCCESS)
		{
			perror("Failed to close the directory.");
			exit(1);
		}
	}
}
