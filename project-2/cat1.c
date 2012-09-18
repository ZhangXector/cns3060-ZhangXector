#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN 512

void display_lines(FILE* fp, int type);

int main(int argc, char* argv[])
{
	FILE* fp;
	int cmpResult;
	int type = 0;

	if(argc > 2)
	{
		cmpResult = (argv[1][0] - '-');
		if(cmpResult == 0)
		{
			cmpResult = strcmp(argv[1], "-n");
			if(cmpResult != 0)
			{
				printf("%s is not a recognized command. Usage: ./cat1 [-n] filename.\n", argv[1]);
				return 1;
			}
		}
	}

	if(argc == 1)
	{
		display_lines(stdin, type);
		return 0;
	}
	else if(cmpResult == 0)
	{
		type = 2;
		int i;

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
	else
	{
		type = 1;
		int i;

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

void display_lines(FILE* fp, int type)
{
	char line[LINELEN];
	int num_of_lines = 0;
	int lineNum = 1;

	if(!fgets(line, LINELEN, fp))
	{
		printf("Error reading line from file.");
		exit(1);
	}
	else do 
	{
		if(type == 1 || type == 0)
		{
			if(fputs(line, stdout) == EOF)
				exit(0);
			num_of_lines++;
		}
		else
		{
			printf("    %i ", lineNum);
			if(fputs(line, stdout) == EOF)
				exit(0);
			num_of_lines++;
			lineNum++;
		}
	} while(fgets(line, LINELEN, fp));
}
