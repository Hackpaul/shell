#include<stdio.h>
#include<stdlib.h>
#include "getline.h"

int main(void){
        struct line line_ptr; // Declaring shared structure for buffer
        line_ptr.buffer=NULL;
	int count,i=0;

	get_line(&line_ptr);    // Passing the struct and get update

	if(line_ptr.code==1){
	     printf("Line : %s\n",line_ptr.buffer);
	     count=parser(&line_ptr);
	     if(count>0){
		     while(i<count){
	             printf("Token :%d string :%s\n",i+1,line_ptr.tokens[i]);
	             i++;
		     }
             } else{
         	     printf("No command is entered !, lol\n");
	     }	
        } else if(line_ptr.code==0){
             printf("User stopped it!\n");
	} else if(line_ptr.code==-1){
             fprintf(stderr,"Error while reading user input!\n");
	}
	free(line_ptr.buffer);
	return 0;
}
