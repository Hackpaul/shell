#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"


void initialize_buildins(struct hash_table *ptr){
 //   unsigned char *temp = malloc(sizeof(char[10])); // to add a new function , add it before NULL. 
 //     memset(temp,0,10);
 //   snprintf((char *)temp,10,"exit");
    ptr->buildins[0] = (unsigned char *)"exit";
    ptr->buildins[1] = (unsigned char *)"cd";
    ptr->buildins[2] = NULL;
    hash(ptr);
}

int buildin_handler(struct line* buffer , struct hash_table *ptr){
    int i = 0 ,is_found = FAIL;
    unsigned long string_hash = hash_string((unsigned char *)buffer->tokens[0]);
    
    while(i < MAX_BUILDINS_COMMANDS){
        if(ptr->hash_array[i] != 0){
            if(string_hash == ptr->hash_array[i]){
            is_found = SUCCESS;

	    break;
            }
            i++;
    	}
	else {
            break;
	}
    }

    if(is_found){

        if(i == 0){         // exit - command
            fflush(stdout);
	    free(buffer->buffer);
	    exit(SUCCESS);
        }

        if(i == 1){
            printf("cd cmd!\n");
        }

    }
    return is_found;
}


