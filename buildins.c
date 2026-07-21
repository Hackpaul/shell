#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"

void free_nodes(struct hash_table *ptr){
    struct string_hash *back, *front;
    int i;
    for(i=0; i<HASH_TABLE; i++){
        front = ptr->hash_array[i];
        while(front != NULL){
            back = front ;
	    front = front->next;
	    free(back);
	}
    }

}

void initialize_buildins(struct hash_table *ptr){
                                 // to add a new function , add it before NULL. 
    ptr->buildins[0] = "exit";
    ptr->buildins[1] = "cd";
    ptr->buildins[2] = NULL;
    hash_buildins(ptr);
}

int buildin_handler(struct line* buffer , struct hash_table *ptr){
    int is_found = FAIL;
    unsigned long hash = hash_string(buffer->tokens[0]);
    struct string_hash *temp;
    temp = ptr->hash_array[hash];
    while(temp != NULL){
        if(strcmp(temp->string,buffer->tokens[0]) == 0){
            is_found = SUCCESS;
	    break;
	}
	temp = temp->next;
    }

    if(is_found == SUCCESS){

        if(hash == ptr->hashed_values[0]){         // exit - command
            fflush(stdout);
	    free(buffer->buffer);
	    free_nodes(ptr);
	    exit(SUCCESS);
        }

        if(hash == ptr->hashed_values[1]){
            printf("cd cmd!\n");
        }

    }
    return is_found;
}


