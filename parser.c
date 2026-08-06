#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

int parser(input *buffer){

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
	    case ' ' :
	    	temp[current] = '\0';
		break;
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

	if(is_error == SUCCESS){
            break;
        }
    }

    return 0;
}
*/

