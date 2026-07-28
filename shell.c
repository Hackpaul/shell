#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

void sigint_handler(int sig){

        write(STDOUT_FILENO, "\n", 1);
}

int main(void){
        int count , stop = 1;
        pid_t process_id;


	struct sigaction signal;
	signal.sa_handler = sigint_handler;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = 0;
	sigaction(SIGINT,&signal,NULL);
        
        input shared_buffer; // Declare a shared structure for buffer
        hash_table hash = {0}; 
	shared_buffer.table = &hash;
	char path[PATH_SIZE] = {0};

        initialize_buildins(&hash);
        shared_buffer.buffer = NULL;

	while(stop){
	    getcwd(path,sizeof(path));
	    setenv("PWD",path,1);
	    printf("%s@pc$%s ",getenv("USER"),getenv("PWD"));
	    fflush(stdout);
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
                 printf("\n");
	         stop = 0;
             } else if(shared_buffer.code==-1){
	         stop = 1;
	     }
	     free(shared_buffer.buffer);
        }

	return 0;
}
