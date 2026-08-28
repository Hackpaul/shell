#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
	
#include "shared.h"
#include "struct.h"
#include "function.h"
#include "parser.h"
#include "hash.h"
#include "helper.h"

int main(void){

    int count , stop = 1;
 
    input shared_buffer;                              // Declare a shared structure for buffer
    initialize_signals();
    hash_table hash = {0};                            // Initialize hash tables struct 
    shared_buffer.table = &hash;  
    char path[PATH_SIZE] = {0};

    tree_node *tree_ptr;
	
    initialize_buildins(&hash);
    shared_buffer.buffer = NULL;

    while(stop){
        getcwd(path,sizeof(path));
        setenv("PWD",path,1);
        printf("%s@pc$%s ",getenv("USER"),getenv("PWD"));
        fflush(stdout);
        get_line(&shared_buffer);                    // Pass the struct and get update

        if(shared_buffer.code == 1){
            count = tokenizer(&shared_buffer);
	    if(count > 0){	    
	    tree_ptr = parser(shared_buffer.tokens,count);
            stop = execute_ast(tree_ptr,&hash);
    	    free_node(tree_ptr);
	    }
        } else if(shared_buffer.code == 0){
            printf("\n");
            stop = 0;
        } else if(shared_buffer.code == -1){
            stop = 1;
        }
        free(shared_buffer.buffer);
    }
    	free_nodes(&hash);
        return 0;
}


/* 
 Transtion from single tokens to a AST tree exectuin : 
 	1. Change required functions to work with char *tokens[] array as parameter , 
 	2. Change the cmd handling into a new function (buidlin and path ).
	3. Create func : execute tree .
	4. for tempory just print the executin works , and add the each feat on time .
*/
