#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "shared.h"

int main(void){
        struct line line_ptr; // Declare a shared structure for buffer
        line_ptr.buffer = NULL;
        int count , stop = 1;
        pid_t process_id;

        while(stop){
	    printf("user@pc$ ");
	    get_line(&line_ptr);    // Pass the struct and get update

      	    if(line_ptr.code == 1){
	        count = parser(&line_ptr);
	        if(count > 0){	     
	            process_id = fork();
		    if(process_id == 0){            // child block
			execute_command(&line_ptr);
		    } else if(process_id > 0){      // parent block
			parent(process_id);
		    } else{
		        fprintf(stderr,"Error : fork cancelled");
			free(line_ptr.buffer);
			exit(EXIT_FAILURE);
		    }

	        }
             } else if(line_ptr.code == 0){
                 printf("User stopped it!\n");
	         stop = 0;
             } else if(line_ptr.code==-1){
                 fprintf(stderr,"Error while reading user input!\n");
	         stop = 1;
	     }
        }
	free(line_ptr.buffer);
	return 0;
}
