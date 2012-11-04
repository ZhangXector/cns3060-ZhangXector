#include <stdio.h>
#include <termios.h>
#include <signal.h>

#define PAGELEN 23
#define LINELEN 512
#define SUCCESS 0
#define ERROR -1
#define STDIN_FD 0

int prompt_user();
int display(FILE*);
int countlines(FILE*);
void interrupt_sig(int);

struct termios curr_state;
struct termios prev_state;
char* filename = NULL;
int print_filename = 1;
double file_percentage = 0;

int main(int argc, char* argv[])
{
	FILE* fp;

	signal(SIGINT, interrupt_sig);
	
	if(tcgetattr(STDIN_FD, &prev_state) == ERROR)
	{
		perror("Unable to get the terminal state.\n");
		return ERROR;
	}

	if(argc == 1)
		return display(stdin);
	else if(argc == 2)
	{
		if((fp = fopen(argv[1], "r")) != NULL)
		{
			filename = argv[1];
			int reply = display(fp);
			fclose(fp);
			return reply;
		}
		else
		{
			printf("Unable to open file %s\n", argv[1]);
			return ERROR;
		}
	}
	else
	{
		perror("Invalid command. Usage - ./more1 [file]\n");
		return ERROR;
	}

	printf("\n");
	return SUCCESS;	
}

int display(FILE* fp)
{
	char line[LINELEN];
	int output_lines = 0;
	int total_lines = 0;
	int displayed_lines = 0;
	int reply;
	FILE* tty;

	total_lines = countlines(fp);

	if((tty = fopen("/dev/tty", "r")) == NULL)
	{
		perror("Unable to open termial file.\n");
		return ERROR;
	}
	
	curr_state = prev_state;

	curr_state.c_lflag &= ~ICANON;
	curr_state.c_lflag &= ~ECHO;

	if(tcsetattr(STDIN_FD, TCSANOW, &curr_state) == ERROR)
	{
		perror("Unable to set terminal attributes\n");
		return ERROR;
	}

	while (fgets(line, LINELEN, fp))
	{
		if(output_lines == PAGELEN)
		{
			file_percentage = 100 * ((double)displayed_lines / (double)total_lines); 

			reply = prompt_user(tty);
			if(reply == SUCCESS)
			{
				tcsetattr(STDIN_FD, TCSANOW, &prev_state);
				return SUCCESS;
			}
			output_lines -= reply;
		}
		if (fputs(line, stdout) == EOF)
		{
			tcsetattr(STDIN_FD, TCSANOW, &prev_state);
			return SUCCESS;
		}
		else
			++displayed_lines;
		++output_lines;
	}

	tcsetattr(STDIN_FD, TCSANOW, &prev_state);
	return SUCCESS;
}

int prompt_user(FILE* tty)
{
	int c;
	
	if (print_filename)
	{
		print_filename = 0;
		printf("\033[7m %s %.2f%% \033[m", filename, file_percentage);
	}
	else
		printf("\033[7m %.2f%% \033[m", file_percentage);
	while((c = getc(tty)) != EOF)
	{
		if(c == 'q')
		{
			fputs("\033[80D\033[K", stdout);
			return SUCCESS;
		}
		if(c == ' ')
		{
			fputs("\033[2J\033[H", stdout);
			return PAGELEN;
		}
		if(c == '\n')
		{
			fputs("\033[80D\033[K", stdout);
			return 1;
		}
	}

	return ERROR;
}

int countlines(FILE* fp)
{
	int num_lines = 0;
	char line[LINELEN];

	while( fgets(line,sizeof(line),fp) != NULL)
	{
		++num_lines;
	}

	rewind(fp);
	return num_lines;	
}

void interrupt_sig(int sig)
{
	signal(sig, SIG_IGN);
	tcsetattr(STDIN_FD, TCSANOW, &prev_state);
	fputs("\033[80D\033[K", stdout);
	printf("\nCTRL-C detected. Restoring terminal state and exiting.\n");
	exit(0);
}
