#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

unsigned long hash_string(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    // Loop through every character until the null terminator \0
    while ((c = *str++)) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c; 
    }

    return hash;
}


int hash(struct hash_table *ptr){
    int no_of_hashed = 0;

    while(ptr->buildins[no_of_hashed] != NULL){
    ptr->hash_array[no_of_hashed] = hash_string(ptr->buildins[no_of_hashed]);
    no_of_hashed ++;
    }
    ptr->hash_array[no_of_hashed]=0;
    return no_of_hashed;
}
