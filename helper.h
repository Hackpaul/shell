#ifndef HELPER_H
#define HELPER_H

#include "shared.h"
#include "struct.h"

struct tree_node *create_node(Node_type type);

int execute_ast(tree_node *head,pointer_struct *ptr);
int free_node(tree_node *head);

#endif

