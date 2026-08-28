#ifndef FUNCTION_H
#define FUNCTION_H

#include "shared.h"
#include "struct.h"

void sigint_handler(int sig);
void initialize_signals(void);


// Buildin command 
void do_exit(char **tokens,int count,pointer_struct *ptr);
void do_cd(char **tokens,int count,pointer_struct *ptr);

// Global functions
void get_line(input *ptr);

void initialize_buildins(hash_table *ptr);
int buildin_handler(char **tokens, int count,pointer_struct *ptr);
void execute_command(char **tokens);

#endif
