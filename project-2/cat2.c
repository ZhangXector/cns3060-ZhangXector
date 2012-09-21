#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN 512

void display_lines(FILE*, int);

// =======================================================================================

int main(int argc, char* argv[])
{
	FILE* fp;
	int type = 0;
	int cmpResult;

	// If no arguments are passed
	if(argc == 1)
	{
		display_lines(stdin, type);
	}

	// If there is one argument
	else if(argc == 2)
	{
		// Check if the first character is a - (for a command)
		cmpResult = (argv[1][0] - '-');
		// If first character is a -
		if(cmpResult == 0)
		{
			// Check to see if the command is -n
			cmpResult = strcmp(argv[1], "-n");
			// If not -n
			if(cmpResult != 0)
			{
				// Print error
				printf("%s is not a recognized command. Usage: ./cat1 [-n] filename.\n", argv[1]);
				return 1;
			}
			// Else (command was -n)
			else
			{
				// Set type to numbered and display stdin
				type = 1;
				display_lines(stdin, type);
			}
		}
		// Else (argument is not a command)
		else
		{
		// Open file and display lines
			fp = fopen(argv[1], "r");
			if(fp != NULL)
			{
				display_lines(fp, type);
				fclose(fp);
				return 0;
			}
			else
			{
				printf("Error opening file.\n");
				return 1;
			}
		}
	}
	// Else (More than 1 argument)
	else
	{
		// Check for -n command as above
		cmpResult = (argv[1][0] - '-');
		if(cmpResult == 0)
		{
			cmpResult = strcmp(argv[1], "-n");
			if(cmpResult != 0)
			{
				printf("%s is not a recognized command. Usage: ./cat1 [-n] filename.\n", argv[1]);
				return 1;
			}
			else
			{
				type = 1;
				int i;
				
				// Open file for each argument (numbered output)
				for(i = 2; i < argc; ++i)
				{
					fp = fopen(argv[i], "r");
					if (fp != NULL)
					{
						display_lines(fp, type);
						fclose(fp);
					}
					else
					{
						printf("Error opening file.\n");
						return 1;
					}
				}
				printf("\n");
				return 0;
			}
		}
		else
		{
			int i;
			
			// Open file for each argument (normal output)
			for(i = 1; i < argc; ++i)
			{
				fp = fopen(argv[i], "r");
				if (fp != NULL)
				{
					display_lines(fp, type);
					fclose(fp);
				}
				else
				{
					printf("Error opening file.\n");
					return 1;
				}
			}
			printf("\n");
			return 0;
		}
	}
}// End main

// ==========================================================================================

void display_lines(FILE* fp, int type)
{
	char line[LINELEN];
	int num_of_lines = 0;
	int lineNum = 1;

	if(type == 0)
	{
		if(!fgets(line, LINELEN, fp))
		{
			printf("Error reading line from file.");
			exit(1);
		}
		else do
		{
			if(fputs(line, stdout) == EOF)
				exit(0);
			num_of_lines++;
		}while(fgets(line, LINELEN, fp));
	}
	else
	{
		if(!fgets(line, LINELEN, fp))
		{
			printf("Error reading line from file.");
			exit(1);
		}
		else do
		{
			printf("%4i  ", lineNum);
			if(fputs(line, stdout) == EOF)
				exit(0);
			num_of_lines++;
			lineNum++;
		}while(fgets(line, LINELEN, fp));

	}
}// End display_lines

// ===========================================================================================
