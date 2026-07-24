#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "shared.h"
#include "struct.h"

void execute_command(input *buffer){
	execvp(buffer->tokens[0],buffer->tokens);
	printf("shell :%s :is not recognised as a command\n",buffer->tokens[0]);
	exit(EXIT_FAILURE);
}

void parent(pid_t child_pid){
	waitpid(child_pid,NULL,0);
}

