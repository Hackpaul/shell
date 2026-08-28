#ifndef FUNCTION_H
#define FUNCTION_H

#include "shared.h"
#include "struct.h"

void sigint_handler(int sig);
void initialize_signals(void);


// Buildin command 
int do_exit(char **tokens,int count);
int do_cd(char **tokens,int count);

// Global functions
void get_line(input *ptr);

int check_is_redirection(tree_node *ptr);

void initialize_buildins(hash_table *ptr);
int buildin_handler(char **tokens, int count, hash_table *ptr);
void execute_command(char **tokens);

#endif
