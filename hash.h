#ifndef HASH_H
#define HASH_H

#include "shared.h"
#include "struct.h"

int hash_buildins(hash_table *ptr);
unsigned long hash_string(char *string); 
void free_nodes(hash_table *ptr);

#endif
