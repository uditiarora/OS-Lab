#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#define nCommands 1000 
#define nLists 100
#define clear() printf("\033[H\033[J") 
void begin(){ 
	clear(); 
	char* username = getenv("USER"); 
	printf("\nUser is: @%s", username); 
	printf("\n"); 
	sleep(1); 
	clear(); 
}
int takeInput(char* str){ 
	char* buf; 

	buf = readline("\nmyshell>>> "); 
	if (strlen(buf) != 0) { 
		add_history(buf); 
		strcpy(str, buf); 
		return 0; 
	} else { 
		return 1; 
	} 
} 


void printDir(){ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\nCurrent Working Directory %s", cwd); 
} 

void execute(char** parsed){ 
	pid_t pid = fork(); 

	if (pid == -1) { 
		printf("\nFork Error"); 
		return; 
	}
	else if (pid == 0) { 
		if (execvp(parsed[0], parsed) < 0) { 
			printf("\nCould not execute command."); 
		} 
		exit(0); 
	} 
	else {
		wait(NULL); 
		return; 
	} 
} 

void openHelp(){ 
	puts("\nTry to execute any valid linux shell command"); 

	return; 
} 


int defaultArgs(char** parsed){ 
	int NoOfOwnCmds = 4, i, switchOwnArg = 0; 
	char* temp[NoOfOwnCmds]; 
	char* username; 

	temp[0] = "exit"; 
	temp[1] = "cd"; 
	temp[2] = "help"; 
	temp[3] = "intro"; 

	for (i = 0; i < NoOfOwnCmds; i++) { 
		if (strcmp(parsed[0], temp[i]) == 0) { 
			switchOwnArg = i + 1; 
			break; 
		} 
	} 

	switch (switchOwnArg) { 
	case 1: 
		exit(0); 
	case 2: 
		chdir(parsed[1]); 
		return 1; 
	case 3: 
		openHelp(); 
		return 1; 
	case 4: 
		username = getenv("USER"); 
		printf("\nHello %s.\nWelcome to myshell. You can use it to execute any linux commands\n", 
			username); 
		return 1; 
	default: 
		break; 
	} 

	return 0; 
} 



int main(){ 
	char input[nCommands], *history[nLists]; 
	char* historyPiped[nLists]; 
	int flag = 0; 
	begin(); 

	while (1) { 
		printDir(); 
		if (takeInput(input)) 
			continue; 
		flag = process(input, history, historyPiped); 
		if (flag == 1) 
			execute(history); 

		if (flag == 2) 
			executePiped(history, historyPiped); 
	} 
	return 0; 
} 




int parsePipe(char* str, char** strpiped){ 
	int i; 
	for (i = 0; i < 2; i++) { 
		strpiped[i] = strsep(&str, "|"); 
		if (strpiped[i] == NULL) 
			break; 
	} 

	if (strpiped[1] == NULL) 
		return 0;
	else { 
		return 1; 
	} 
} 


void executePiped(char** parsed, char** parsedpipe){ 
	int fd[2]; 
	pid_t p1, p2; 

	if (pipe(fd) < 0) { 
		printf("\nPipe not initialized"); 
		return; 
	} 
	p1 = fork(); 
	if (p1 < 0) { 
		printf("\nFork Error"); 
		return; 
	} 

	if (p1 == 0) { 
		close(fd[0]); 
		dup2(fd[1], STDOUT_FILENO); 
		close(fd[1]); 

		if (execvp(parsed[0], parsed) < 0) { 
			printf("\nCould not execute command"); 
			exit(0); 
		} 
	} else { 

		p2 = fork(); 

		if (p2 < 0) { 
			printf("\nFork Error"); 
			return; 
		} 

		
		if (p2 == 0) { 
			close(fd[1]); 
			dup2(fd[0], STDIN_FILENO); 
			close(fd[0]); 
			if (execvp(parsedpipe[0], parsedpipe) < 0) { 
				printf("\nCould not execute command"); 
				exit(0); 
			} 
		} else { 
			
			wait(NULL); 
			wait(NULL); 
		} 
	} 
} 


