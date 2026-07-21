#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

unsigned long hash_string(char *string) {
    unsigned long hash = 0;
    while(string[hash]!= '\0'){
        hash ++;
    }	
    return hash;
}


int hash_buildins(struct hash_table *ptr){
    int count = 0;
    unsigned long hash;
    struct string_hash *temp;
    while(ptr->buildins[count] != NULL){
        hash = hash_string(ptr->buildins[count]);
	ptr->hashed_values[count] = hash;
	temp = ptr->hash_array[hash];

	if(temp == NULL){                                    // Creation of node
            temp = malloc(sizeof(struct string_hash));
	    if(temp == NULL){
                printf("Malloc failed\n");
	    }
	    temp->string = ptr->buildins[count];
	    ptr->hash_array[hash] = temp;
	} else {
            while(temp->next != NULL){	                      // appendation of node 
	        temp = temp->next;

            }
	    temp->next = malloc(sizeof(struct string_hash));
	    temp->next->string = ptr->buildins[count];
	    temp->next->next = NULL;
	}
        count ++;
    }
    return count;
}

