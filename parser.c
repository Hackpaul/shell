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


tree_node *parser(input *buffer, int count){

    int i = 0 , tokens_count = 0 , is_cmd = 1;
    char *temp = NULL;
    
    if(count == 0){
	return NULL;
    }

    tree_node *current = malloc(sizeof(struct tree_node));
    memset(current,0,sizeof(struct tree_node));

    tree_node *struct_ptr = current , *head = current ;
    for(i = 0;i < count ;i ++){

	if(is_cmd == 0){
	    current = create_node(NODE_CMD);
	    *stored_ptr = current;
	    is_cmd = 1;
	}
	temp = buffer->tokens[i];

	if(strcmp(temp,"<") == 0){

	    current->tokens[tokens_count] = NULL;
	    current->file_in = buffer->tokens[i+1]; 
	    i ++;
	    current->is_file_in ++;
	} 
	/*else if(strcmp(temp,"<<") == 0){
	    current->multi_line_in
	    temp = NULL;
	    curent->is_multi_line_in ++;

	}*/
	 else if(strcmp(temp,">") == 0){

	    current->tokens[tokens_count] = NULL;
	    current->file_out = buffer->tokens[i+1];
	    i ++;
	    current->is_file_out ++;

	} else if(strcmp(temp,">>") == 0){ 

	    current->tokens[tokens_count] = NULL;
	    current->append_file = buffer->tokens[i+1];
	    i ++;
	    current->is_append_file ++;
          
	}else if(strcmp(temp,"|") == 0){

	    current->tokens[tokens_count] = NULL;
	    is_cmd = 0;
            tokens_count = 0;
	    struct_ptr = create_node(NODE_PIPE);
	    struct_ptr->left = head;
	    stored_ptr = &struct_ptr->right;
	    head = struct_ptr;

	}else if(strcmp(temp,"||") == 0){

	    current->tokens[tokens_count] = NULL;
	    is_cmd = 0;
	    tokens_count = 0;
	    struct_ptr = create_node(NODE_OR);
	    struct_ptr->left = head;
	    stored_ptr = &struct_ptr->right;
	    head = struct_ptr;

	}else if(strcmp(temp,"&&") == 0){

	    current->tokens[tokens_count] = NULL;
	    is_cmd = 0;
	    tokens_count = 0;
	    struct_ptr = create_node(NODE_AND);
	    struct_ptr->left = head;
	    stored_ptr = &struct_ptr->right;
	    head  = struct_ptr;

	} else {
        current->tokens[tokens_count] = temp;
        tokens_count ++;	
        }
    }
    if(current->tokens[token])
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

