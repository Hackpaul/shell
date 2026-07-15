#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "shared.h"

int main(void){
        struct line line_ptr; // Declaring shared structure for buffer
        line_ptr.buffer=NULL;
	int count;
	pid_t pid;

	printf("user@pc$ ");
	get_line(&line_ptr);    // Passing the struct and get update

	if(line_ptr.code==1){
	     count=parser(&line_ptr);
	     if(count>0){	     
		     pid=fork();
		     if(pid==0){            // child
			     execute_command(&line_ptr);
		     } else if(pid>0){      // parent
			     parent(pid);
		     } else{
			     fprintf(stderr,"Error : fork cancelled");
			     free(line_ptr.buffer);
			     exit(EXIT_FAILURE);
		     }

	     }
        } else if(line_ptr.code==0){
             printf("User stopped it!\n");
	} else if(line_ptr.code==-1){
             fprintf(stderr,"Error while reading user input!\n");
	}
	free(line_ptr.buffer);
	return 0;
}
