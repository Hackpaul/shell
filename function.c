#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

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

void do_exit(char **tokens,int count,pointer_struct *ptr){
    if(count == 1) {
        fflush(stdout);
        free(((input *)ptr->input_ptr)->buffer);
        free_nodes((hash_table *)ptr->hash_table_ptr);
        exit(SUCCESS);
    } else {
        printf("Invalid no of arguments!\n");
    }	
}

void do_cd(char**tokens,int count, pointer_struct *ptr){
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
}
