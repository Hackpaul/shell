#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "getline.h"

int parser(struct line *buffer){

	char *temp =strtok(buffer->buffer," ");
	int count=0;
        while(temp!=NULL && count < 10){
		buffer->tokens[count]=temp;
		count++;
		temp=strtok(NULL," ");
	}
        return count;
}
