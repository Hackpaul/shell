#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

void free_nodes(hash_table *ptr){
    hash_node *back, *front;
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

void initialize_buildins(hash_table *ptr){
                                 // to add a new function , add it before NULL. 
    ptr->buildins[0] = "exit";
    ptr->do_command[0] = do_exit;
    ptr->buildins[1] = "cd";
    ptr->do_command[1] = do_cd;
    ptr->buildins[2] = NULL;
    hash_buildins(ptr);
}

int buildin_handler(input* buffer , hash_table *ptr){
    int is_found = FAIL;

    unit hash = hash_string(buffer->tokens[0]);
    hash_node *temp = ptr->hash_array[hash];

    while(temp != NULL){
        if(strcmp(temp->string,buffer->tokens[0]) == 0){
            is_found = SUCCESS;
            ptr->do_command[temp->slot](buffer);
	    break;
	}
	temp = temp->next;
    }
    return is_found;
}


