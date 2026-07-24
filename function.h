#ifndef FUNCTION_H
#define FUNCTION_H

#include "shared.h"
#include "struct.h"


// Buildin command 
void do_exit(input *buffer);
void do_cd(input *buffer);



// Global functions
void get_line(input *ptr);
int parser(input *ptr);

void execute_command(input *ptr);
void parent(pid_t pid);
void initialize_buildins(hash_table *ptr);
int buildin_handler(input *buffer , hash_table *ptr);

int hash_buildins(hash_table *ptr);
unsigned long hash_string(char *string); 

void free_nodes(hash_table *ptr);

#endif
