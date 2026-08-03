#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "struct.h"
#include "shared.h"
#include "function.h"

void do_exit(input *buffer){
    if(buffer->no_of_arguments == 1) {
        fflush(stdout);
        free(buffer->buffer);
        free_nodes(buffer->table);
        exit(SUCCESS);
    } else {
        printf("Invalid no of arguments!\n");
    }	
}

void do_cd(input *buffer){
    char path[PATH_SIZE] = {0};

    if(buffer->no_of_arguments == 2){
        if(buffer->tokens[1][0] == '~'){
           char *home = getenv("HOME");
            snprintf(path,sizeof(path),"%s%s",home,buffer->tokens[1] + 1);
            if(chdir(path) == -1){
                perror("cd");
            }

        } else {
            if(chdir(buffer->tokens[1]) == -1){
                perror("cd");
            }
        }

    } else if(buffer->no_of_arguments == 1){
        char *home = getenv("HOME");
        if(chdir(home) == -1){
            perror("cd");
        }
    } else{
        fprintf(stderr,"cd : invalid number of arguments\n");
    }
}
