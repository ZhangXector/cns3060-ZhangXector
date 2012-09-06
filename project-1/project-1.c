#import <stdio.h>

int main(int argc, char* argv[])
{
	printf("Cliff Kelley\n");
	printf("CS 3060\n\n");

	int i;
	for(i = 1; i < argc; ++i)
	{
		printf(argv[i]);
		printf("\n");
	}
	return 0;
}
