#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "shared.h"

int main(void){
        int count , stop = 1;
        pid_t process_id;
        
        struct line shared_buffer; // Declare a shared structure for buffer
        struct hash_table hash; 

        initialize_buildins(&hash);
        shared_buffer.buffer = NULL;

	while(stop){
	    printf("user@pc$ ");
	    get_line(&shared_buffer);    // Pass the struct and get update

      	    if(shared_buffer.code == 1){
	        count = parser(&shared_buffer);
	        if(count > 0){	    
		    if(buildin_handler(&shared_buffer,&hash) == FAIL){
	                process_id = fork();
		        if(process_id == 0){            // child block
			    execute_command(&shared_buffer);
		        } else if(process_id > 0){      // parent block
			    parent(process_id);
		        } else{
		            fprintf(stderr,"Error : fork cancelled");
			    free(shared_buffer.buffer);
		 	    exit(EXIT_FAILURE);
		        }
	            }
	        }
             } else if(shared_buffer.code == 0){
                 printf("User stopped it!\n");
	         stop = 0;
             } else if(shared_buffer.code==-1){
                 fprintf(stderr,"Error while reading user input!\n");
	         stop = 1;
	     }
	     free(shared_buffer.buffer);
        }

	return 0;
}
