#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

#include "struct.h"
#include "shared.h"
#include "function.h"
#include "hash.h" 

void sigint_handler(int sig){                        // SIGINT handler	
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
}

void initialize_signals(void){
    struct sigaction sigint , sigtstp , sigquit;      // Signal : SIGINT     

    sigint.sa_handler = sigint_handler;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = 0;
    sigaction(SIGINT,&sigint,NULL);
    
    sigemptyset(&sigtstp.sa_mask);                    // Signal : SIGTSTP
    sigtstp.sa_handler = SIG_IGN;
    sigaction(SIGTSTP,&sigtstp,NULL);

    sigemptyset(&sigquit.sa_mask);                    // Signal : SIGQUIT
    sigquit.sa_handler = SIG_IGN;
    sigaction(SIGQUIT,&sigquit,NULL);
    
}

int check_is_redirection(tree_node *ptr){
        int fd;
	char *file;

	if(ptr->cmd_node.is_file_out > 0){

	     file = ptr->cmd_node.file_out;

	    if(file != NULL){

		fd = open(file,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if(fd > 0){
		    dup2(fd,STDOUT_FILENO);
		    close(fd);
		} else {
		    perror("FILE OUT ");
		    return 0;
		}

	    } else {
		fprintf(stderr,"Error : No file specified");
		exit(EXIT_FAILURE);
	    }

	}

        if(ptr->cmd_node.is_file_in > 0){

	    file = ptr->cmd_node.file_in;
	    if(file != NULL){

		fd = open(file,O_RDONLY);
		if(fd > 0){
		    dup2(fd,STDIN_FILENO);
		    close(fd);
		} else {
		    perror("FILE IN ");
		    return 0;
		}

	    } else {
		fprintf(stderr,"Error : No file specified");
		exit(EXIT_FAILURE);
	    }
	}

        if(ptr->cmd_node.is_append_file > 0){

	     file = ptr->cmd_node.append_file;
	     if(file != NULL){

		fd = open(file,O_WRONLY | O_CREAT | O_APPEND , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if(fd > 0){
		    dup2(fd,STDOUT_FILENO);
		    close(fd);
		} else {
		    perror("FILE APPEND ");
		    return 0;
		}

	    } else {
		fprintf(stderr,"Error : No file specified");
		exit(EXIT_FAILURE);
	    }
	}
	return 1;

}

int do_exit(char **tokens,int count){
    
    (void) tokens;
    if(count == 1) {
        fflush(stdout);
        return 0;
    } else {
        printf("Invalid no of arguments!\n");
    }	
    return -1;
}

int do_cd(char**tokens,int count){
    char path[PATH_SIZE] = {0};

    if(count == 2){
        if(tokens[1][0] == '~'){
           char *home = getenv("HOME");
            snprintf(path,sizeof(path),"%s%s",home,tokens[1] + 1);
            if(chdir(path) == -1){
                perror("cd");
            }

        } else {
            if(chdir(tokens[1]) == -1){
                perror("cd");
            }
        }

    } else if(count == 1){
        char *home = getenv("HOME");
        if(chdir(home) == -1){
            perror("cd");
        }
    } else{
        fprintf(stderr,"cd : invalid number of arguments\n");
    }
    return SUCCESS;
}
