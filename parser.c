#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shared.h"
#include "struct.h"
#include "function.h"
#include "helper.h"

int tokenizer(input *buffer){

    char *temp = strtok(buffer->buffer," ");
    int count = 0;
        while(temp != NULL && count < MAX_TOKENS){
            buffer->tokens[count] = temp;
            count ++;
            temp = strtok(NULL," ");
        }
        buffer->no_of_arguments = count;
        buffer->tokens[count] = NULL;
        return count;
}


tree_node *parser(char **buffer, int count){

    int i = 0 , tokens_count = 0 , is_cmd = 1 , is_operator = 0 ,can_append = 1 ,state_unknown = 1;
    char *temp = NULL;
    
    if(count == 0){
	return NULL;
    }

    tree_node *current = create_node(NODE_UNKNOWN);

    tree_node *struct_ptr = current , *head = current , **stored_ptr ;
    for(i = 0;i < count ;i ++){

	can_append = 1;

	if(is_cmd == 0){
	    current = create_node(NODE_UNKNOWN);
	    *stored_ptr = current;
	    state_unknown = 1;
	    is_cmd = 1;
	}
	temp = buffer[i];

	if(strcmp(temp,"<") == 0){
	   
	    if(state_unknown){
	        current->type = NODE_CMD;
	    }

	    if(i+1 < count){
	        current->cmd_node.file_in = buffer[i+1];
	        i ++;
		can_append = 0;
	    } else {
	        current->cmd_node.file_in = NULL;
	    }
	    current->cmd_node.file_in ++;

	} else if(strcmp(temp,">") == 0){

	     if(state_unknown){
		 current->type = NODE_CMD;
	     }

	     if(i+1 < count){
                current->cmd_node.file_out = buffer[i+1];
	        i ++;
		can_append = 0;
	    } else {
		current->cmd_node.file_out = NULL;
	    }
	    current->cmd_node.is_file_out ++;

	} else if(strcmp(temp,">>") == 0){ 

	    if(state_unknown){
		 current->type = NODE_CMD;
	    }

	    if(i+1 < count){
	        current->cmd_node.append_file = buffer[i+1];
	        i ++;
		can_append = 0;
	    } else {
		current->cmd_node.append_file = NULL;
	    }
	    current->cmd_node.is_append_file ++;
          
	} else if(strcmp(temp,"|") == 0){
	
	    if(state_unknown){
	
	    } else {
                current->cmd_node.tokens[tokens_count] = NULL;
	    }
	    is_cmd = 0;
            is_operator = 1;
	    can_append = 0;
	    struct_ptr = create_node(NODE_PIPE);
	    struct_ptr->operator_node.left = head;
	    stored_ptr = &struct_ptr->operator_node.right;
	    head = struct_ptr;

	} else if(strcmp(temp,"||") == 0){

	    if(state_unknown){

	    } else {
	        current->cmd_node.tokens[tokens_count] = NULL;
	    }
	    is_cmd = 0;
	    is_operator = 1;

	    can_append = 0;
	    struct_ptr = create_node(NODE_OR);
	    struct_ptr->operator_node.left = head;
	    stored_ptr = &struct_ptr->operator_node.right;
	    head = struct_ptr;

	} else if(strcmp(temp,"&&") == 0){

	    if(state_unknown){

	     } else {
	        current->cmd_node.tokens[tokens_count] = NULL;
	     }
	    is_cmd = 0;
            is_operator = 1;
	    can_append = 0;
	    struct_ptr = create_node(NODE_AND);
	    struct_ptr->operator_node.left = head;
	    stored_ptr = &struct_ptr->operator_node.right;
	    head  = struct_ptr;

	} else {

	    if(state_unknown){
		current->type = NODE_CMD;
	    }
	    
            current->cmd_node.tokens[tokens_count] = temp;
	    can_append = 1;
	}

	if(state_unknown){
	    state_unknown = 0;
	}
	if(tokens_count +1 < MAX_TOKENS){
	    current->cmd_node.tokens[tokens_count + 1] = NULL;
	}

        if(is_operator){
	    tokens_count = 0;
	    is_operator = 0;
	}

        if(can_append){
	    tokens_count ++;
	    current->cmd_node.count = tokens_count; 
	}

    }
    return head;
}


/*
   A custom parser is under progress !
   Why this choice : 

   	1. To get a full control over whats the user is typing.
	2. This can be easily extended over each new feats. 
*//* 

int parser(input *buffer){
    int token_count = 0, current = 0 ,struct = 0 , is_error = FAIL;
    char *temp = buffer->buffer;
    char *temp_token = NULL , *tokens[10] = {NULL};
    temp_token = temp;

    while(temp[current] != '\0'){
        switch(temp[current]){
            case '|' :
		if(temp[current + 1] == '|'){
                    fprintf(stderr,"shell: syntax error near unexpected token `|' \n");
	            return 1;
                }
		break;
	    default :
	        break;
        }
        current++;
    }

    return 0;
}
*/

