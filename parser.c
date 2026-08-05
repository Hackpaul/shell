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

