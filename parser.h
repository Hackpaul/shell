#ifndef PARSER_H
#define PARSER_H

#include "shared.h"
#include "struct.h"

int tokenizer(input *buffer);
tree_node *parser(char **buffer, int count);

#endif 
