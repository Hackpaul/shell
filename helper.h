#ifndef HELPER_H
#define HELPER_H

#include "shared.h"
#include "struct.h"

struct tree_node *create_node(Node_type type);

int execute_ast(tree_node *head,hash_table *ptr,int write_fd);
int free_node(tree_node *head);

#endif

