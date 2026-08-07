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


Tree_node parser(input *buffer, int count){
    int i = 0 , tokens_count = 0;
    vhar *temp = NULL;

    tree_node *current = calloc(sizeof(struct tree_node));
    memset(current,0,sizeof(struct tree_node));

    Tree_node *struct_ptr = current;
    for(i = 0;i < count ;i ++){
	temp = buffer->tokens[i];

	if(strcmp(temp,"<") == 0){

	    current->file = buffer->tokens[i+1]; 
	    i ++;
	    temp = NULL;
	    current->is_file_in ++;
	} 
	/*else if(strcmp(temp,"<<") == 0){
	    current->multi_line_in
	    temp = NULL;
	    curent->is_multi_line_in ++;

	}*/
	 else if(strcmp(temp,">") == 0){
	    temp = NULL;
	    current->file = buffer->tokens[i+1];
	    i ++;
	    current->is_file_out ++;

	} else if(strcmp(temp,">>") == 0){ 

	    temp = NULL;
	    current->file = buffer->tokens[i+1];
	    i ++;
	    current->is_append_file ++;
          
	}else if(strcmp(temp,"|") == 0){

            tokens_count = 0;
	    ptr = create_node(PIPE);
	    ptr->left = current;
	    ptr->right = current;

	}else if(strcmp(temp,"||") == 0){

	    tokens_count = 0;
	    temp_struct = create_node(NODE_OR);
	    temp_struct->left = current;
	    temp_struct->right = current; 

	}else if(strcmp(temp,"&&") == 0){

	    tokens_count = 0;
	    temp_struct = create_node(NODE_AND);
	    temp_struct->left = current;
	    temp_struct->right = current; 

	}else {

	    current->tokens[tokens_count] = temp;
	    tokens_count ++;

	}
	
    }
    return temp;
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

