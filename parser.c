#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
 
   why this choice : 

   	1. I want a full control over whats the user is typing .
	2. this can be easily extended over each new symbols and quotes . 
*/

/* 

int parser(input *buffer){
    int count = 0, i = 0;
    char *temp = buffer->buffer;
    while(temp[i] != '\n'){
        case temp[i]
    }
    return count;
}

*/

