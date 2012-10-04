// Project 3 - du
// Cliff Kelley

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#define SUCCESS 0
#define FAILURE -1
#define DIR_STRING_SIZE 256
#define CURRENT_DIR "."
#define PARENT_DIR ".."

// List Directories
// Params: String directory name
// Returns: Int size of directory
// Purpose: Reads through directory for entries and calculates size
int list_directories(const char*);

//=========================================================================================================

// Main
int main (int argc, char* argv[])
{
	// If there are less than or exactly 2 arguments
	if (argc <= 2)
	{
		// Set the directory to the argument, or to the current dir if there isn't one
		const char * directory = argc > 1 ? argv[1] : CURRENT_DIR;
		struct stat dirStats;
		
		// Get stats on directory
		if(stat(directory, &dirStats) != SUCCESS)
		{
			printf("Not a valid file or directory: %s\n", directory);
			return(FAILURE);
		}
		else
		{
			// If argument is a directory
			if(S_ISDIR(dirStats.st_mode))
			{
				// List the directory and it's sub-directories
				if(list_directories(directory) == -1)
				{
					return FAILURE;
				}
			}
			// Else (it's a file name)
			else
			{
				// Print info on the file
				printf("%8lld B     %s\n", (long long)dirStats.st_size, directory);
			}
		}
	}
	
	// Else (too many arguments) 
	else
	{
		printf("Too many arguments. Usage: ./du1 [directory]\n");
		return FAILURE;
	}
	return SUCCESS;
}// End main

//=========================================================================================================

int list_directories(const char* dirname)
{
	DIR* directoryPointer;
	struct dirent* currentEntry;
	struct stat entryStats;
	
	// Get stats on the directory
	if (stat(dirname, &entryStats) != SUCCESS)
	{
		perror("Failed to get directory stats\n");
		return(FAILURE);
	}

	// Start out with the directory size
	int dirSize = entryStats.st_size;

	// Open the directory
	if((directoryPointer = opendir(dirname)) == NULL)
	{
		perror(("du1: cannot open %s\n", dirname));
		return(FAILURE);
	}
	else
	{
		// While there are still more items in the directory
		while ((currentEntry = readdir(directoryPointer)) != NULL)
		{
			// String for storing entry path (including parent directory)
			char entryPath[DIR_STRING_SIZE];
			
			// Create a string with the directory name and the current entry name
			snprintf(entryPath, sizeof(entryPath) - 1, "%s/%s", dirname, currentEntry->d_name);
			
			// Get stats on the entry director
			if (stat(entryPath, &entryStats) != SUCCESS) 
			{
				perror("Failed to get file stats\n");
			}
			// Check to make sure we're not looking at the parent or current directory
			else if(strcmp(currentEntry->d_name, PARENT_DIR) && strcmp(currentEntry->d_name, CURRENT_DIR))
			{
				// If this entry is a directory
				if(S_ISDIR(entryStats.st_mode))
				{
					// Call list_directories on this directory and add the size to dirSize
					dirSize += list_directories(entryPath);
				}
				// Else (It's a file)
				else
				{
					// Add the file size to the dirSize
					dirSize += entryStats.st_size;
					// Print file information
					printf("%8lld B     %s/%s\n", (long long)entryStats.st_size, dirname, currentEntry->d_name, "");
				}
			}// End else if
		}// End while more items
		
		// Close the file
		if(closedir(directoryPointer)!= SUCCESS)
		{
			perror("Failed to close the directory.");
			return(FAILURE);
		}

		// Print directory information
		printf("%8lld B     %s\n", (long long)dirSize, dirname);
		
		// Return the directory size
		return dirSize;

	}// End else
}// End list_directories
