// Cliff Kelley
// Project 5 - more

#include <stdio.h>
#include <termios.h>
#include <signal.h>

#define PAGELEN 23
#define LINELEN 512
#define SUCCESS 0
#define ERROR -1
#define STDIN_FD 0

// ======================== Function Definitions ==============================

// Prompt User Function
// Params: None
// Returns: User response
// Purpose: Prompts the user and gets input from terminal
int prompt_user();

// Display Function
// Params: File to display
// Returns: Success/Error
// Purpose: Displays the text from the file according to user input
int display(FILE*);

// Count Lines Function
// Params: File to count
// Returns: Number of lines
// Purpose: Counts the number of lines in the file
int countlines(FILE*);

// Interrupt Signal Function
// Params: Signal code
// Returns: None
// Purpose: Resets the terminal state after catching the interrupt
void interrupt_sig(int);

// Terminal States
struct termios curr_state;
struct termios prev_state;

// File name from argument
char* filename = NULL;

// Used to print the filename only once
int print_filename = 1;

// Percentage of file that has been displayed
double file_percentage = 0;

// ========================= Main Function ====================================

int main(int argc, char* argv[])
{
	FILE* fp;

	// Checks for the interrupt signal
	signal(SIGINT, interrupt_sig);
	
	// Gets the terminal state attributes
	if(tcgetattr(STDIN_FD, &prev_state) == ERROR)
	{
		perror("Unable to get the terminal state.\n");
		return ERROR;
	}

	// If there is no argument passed
	if(argc == 1)
		return display(stdin);
	else if(argc == 2)
	{
		// Opens the file
		if((fp = fopen(argv[1], "r")) != NULL)
		{
			// Stores filename
			filename = argv[1];
			// Displays the file
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

// ========================= Display Function =================================

int display(FILE* fp)
{
	// Line to display
	char line[LINELEN];
	// Number of lines to output
	int output_lines = 0;
	// Total lines in file
	int total_lines = 0;
	// Number of lines displayed so far
	int displayed_lines = 0;
	// User response
	int reply;
	// For input from term when canonical off
	FILE* tty;

	// Count lines in the file
	total_lines = countlines(fp);

	// Open tty for input
	if((tty = fopen("/dev/tty", "r")) == NULL)
	{
		perror("Unable to open termial file.\n");
		return ERROR;
	}
	
	// Set current state
	curr_state = prev_state;

	// Turn off canonical and echo
	curr_state.c_lflag &= ~ICANON;
	curr_state.c_lflag &= ~ECHO;

	// Set the attributes
	if(tcsetattr(STDIN_FD, TCSANOW, &curr_state) == ERROR)
	{
		perror("Unable to set terminal attributes\n");
		return ERROR;
	}

	// Get line from the file
	while (fgets(line, LINELEN, fp))
	{
		// If we've printed 24 lines
		if(output_lines == PAGELEN)
		{
			// Get the percentage displayed
			file_percentage = 100 * ((double)displayed_lines / (double)total_lines); 

			// Get user input
			reply = prompt_user(tty);
			// If 'q' reset attributes and return
			if(reply == SUCCESS)
			{
				tcsetattr(STDIN_FD, TCSANOW, &prev_state);
				return SUCCESS;
			}
			// decrement output lines by response
			output_lines -= reply;
		}
		// If end of line reset attributes and return
		if (fputs(line, stdout) == EOF)
		{
			tcsetattr(STDIN_FD, TCSANOW, &prev_state);
			return SUCCESS;
		}
		else
			// count displayed lines
			++displayed_lines;
		++output_lines;
	}

	tcsetattr(STDIN_FD, TCSANOW, &prev_state);
	return SUCCESS;
}

// ============================= Prompt User ==================================

int prompt_user(FILE* tty)
{
	// User character input
	int c;
	
	// Print the file name if it's the first print
	if (print_filename)
	{
		print_filename = 0;
		printf("\033[7m %s %.2f%% \033[m", filename, file_percentage);
	}
	// Else print percentage
	else
		printf("\033[7m %.2f%% \033[m", file_percentage);

	// Get character
	while((c = getc(tty)) != EOF)
	{
		// If q, quit
		if(c == 'q')
		{
			fputs("\033[80D\033[K", stdout);
			return SUCCESS;
		}
		// If space, display next page
		if(c == ' ')
		{
			fputs("\033[2J\033[H", stdout);
			return PAGELEN;
		}
		// If newline, display one line
		if(c == '\n')
		{
			fputs("\033[80D\033[K", stdout);
			return 1;
		}
	}

	// Reset attributes and error (shouldn't have gotten this far)
	tcsetattr(STDIN_FD, TCSANOW, &prev_state);
	return ERROR;
}

// ============================== Count Lines =================================

int countlines(FILE* fp)
{
	// Number of lines
	int num_lines = 0;
	char line[LINELEN];

	// Get lines from file
	while( fgets(line,sizeof(line),fp) != NULL)
	{
		// Count them
		++num_lines;
	}

	// Rewind file
	rewind(fp);
	return num_lines;	
}

// ========================== Interrupt Catch =================================

void interrupt_sig(int sig)
{
	// Catch signal
	signal(sig, SIG_IGN);
	// Reset attributes
	tcsetattr(STDIN_FD, TCSANOW, &prev_state);
	// Clear line
	fputs("\033[80D\033[K", stdout);
	// Inform user
	printf("\nCTRL-C detected. Restoring terminal state and exiting.\n");
	exit(0);
}

// ============================================================================
