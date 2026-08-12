#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

struct tree_node *create_node(Node_type type){
    struct tree_node ptr = malloc(sizeof(struct tree_node));
    memset(ptr,0,sizeof(struct tree_node));
    switch (type) {
        case NODE_CMD:
	     ptr->type = NODE_CMD;
	     break;
	case NODE_PIPE:
	     ptr->type = NODE_PIPE;
	     break;
	case NODE_OR : 
	     ptr->type = NODE_OR;
	     break;
	case NODE_AND:
	     ptr->type = NODE_AND;
	     break;
	case default :
	     return NULL;
    }
    return ptr;
}
