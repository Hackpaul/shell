#ifndef HELPER_H
#define HELPER_H

#include "shared.h"
#include "struct.h"

struct tree_node *create_node(Node_type type);

void execute_cmds(char **tokens,int count, pointer_struct *ptr);
int execute_ast(tree_node *head);
int free_node(tree_node *head);

#endif

