#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

#define CURRENT_DIR "."
#define PARENT_DIR ".."

void list_directories(const char*);

int main (int argc, char* argv[])
{
	if (argc <= 2)
	{
		const char * directory = argc > 1 ? argv[1] : CURRENT_DIR;
		struct stat dirStats;
		
		if(stat(directory, &dirStats) != SUCCESS)
		{
			printf("Not a valid file or directory: %s\n", directory);
			return(FAILURE);
		}
		else
		{
			//printf("%20lld B     '%s'\n", (long long)dirStats.st_size, directory);
			if(S_ISDIR(dirStats.st_mode))
			{
				list_directories(directory);
			}
		}
	}
	else
	{
		printf("Too many arguments. Usage: ./du1 [directory]\n");
		return FAILURE;
	}
	return SUCCESS;
}

void list_directories(const char* dirname)
{
	DIR* directoryPointer;
	struct dirent* currentEntry;
	struct stat entryStats;
	int dirSizes = 0;

	if((directoryPointer = opendir(dirname)) == NULL)
	{
		perror(("du1: cannot open %s\n", dirname));
		exit(1);
	}
	else
	{
		while ((currentEntry = readdir(directoryPointer)) != NULL)
		{
			char statDirectory[512];
			
			snprintf(statDirectory, sizeof(statDirectory) - 1, "%s/%s", dirname, currentEntry->d_name);
			if (stat(statDirectory, &entryStats) != SUCCESS) 
			{
				perror("Failed to get file stats\n");
			}
			else if(strcmp(currentEntry->d_name, PARENT_DIR))
			{
				dirSizes += entryStats.st_size;
				if(S_ISDIR(entryStats.st_mode))
				{
					char fullDir[512];
					snprintf(fullDir, sizeof(fullDir) - 1, "%s/%s", dirname, currentEntry->d_name);
					list_directories(fullDir);
					printf("%20lld B     '%s/%s'\n", (long long)dirSizes, dirname, currentEntry->d_name, "");
				}
				else
				{
					printf("%20lld B     '%s/%s'\n", (long long)entryStats.st_size, dirname, currentEntry->d_name, "");
				}
			}
		}
		if(closedir(directoryPointer)!= SUCCESS)
		{
			perror("Failed to close the directory.");
			exit(1);
		}
	}
}
