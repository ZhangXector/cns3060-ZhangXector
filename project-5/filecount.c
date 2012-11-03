#include <stdio.h>

int main(int argc, char* argv[])
{
		FILE* fp;

		fp = fopen(argv[1], "r");
		int num = countlines(fp);

		printf("Number of lines: %d\n", num);
		
		fclose(fp);
}

int countlines(FILE* fp)
{
		int num_lines = 0;
		char line[512];

		while( fgets(line,sizeof(line),fp) != NULL)
		{
				++num_lines;
				printf("Line: %s\t--- Number is now: %d\n", line, num_lines);
		}

		return num_lines;
}
