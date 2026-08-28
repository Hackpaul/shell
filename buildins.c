#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shared.h"
#include "struct.h"
#include "function.h"
#include "hash.h"

void initialize_buildins(hash_table *ptr){     // to add a new function , add it before NULL. 
    ptr->buildins[0] = "exit";
    ptr->do_command[0] = do_exit;
    ptr->buildins[1] = "cd";
    ptr->do_command[1] = do_cd;
    ptr->buildins[2] = NULL;
    hash_buildins(ptr);
}

int buildin_handler(char **tokens , int count, hash_table *ptr){
    int is_found = FAIL;
    hash_table *hash_table_ptr = ptr;
    unit hash = hash_string(tokens[0]);
    hash_node *temp = hash_table_ptr->hash_array[hash];

    while(temp != NULL){

        if(strcmp(temp->string,tokens[0]) == 0){
            is_found = hash_table_ptr->do_command[temp->slot](tokens ,count );
            break;
        }
        temp = temp->next;

    }
    return is_found;
}
