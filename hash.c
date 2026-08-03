#include <stdio.h>
#include <stdlib.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

unit hash_string(char *string) {
    unit hash = 0;
    while(string[hash]!= '\0'){
        hash ++;
    }	
    return hash;
}


int hash_buildins(hash_table *ptr){
    int count = 0;
    unit hash;
    hash_node *temp;
    while(ptr->buildins[count] != NULL){
        hash = hash_string(ptr->buildins[count]);
        temp = ptr->hash_array[hash];

        if(temp == NULL){                                    // Creation of node
            temp = malloc(sizeof(hash_node));
            if(temp == NULL){
                printf("Malloc failed\n");
            }
            temp->string = ptr->buildins[count];
            temp->slot = count;
            ptr->hash_array[hash] = temp;
        } else {
            while(temp->next != NULL){	                      // appendation of node 
               temp = temp->next;

            }
            temp->next = malloc(sizeof(hash_node));
            temp->next->string = ptr->buildins[count];
            temp->next->slot = count;
            temp->next->next = NULL;
        }
        count ++;
    }
    return count;
}
