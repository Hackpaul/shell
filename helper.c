#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

struct tree_node *create_node(Node_type type){
    struct tree_node *ptr = malloc(sizeof(struct tree_node));
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
    }
    return ptr;
}
 
void execute_cmds(char **tokens,int count,pointer_struct *ptr){
    if(buildin_handler(tokens, count,ptr) == FAIL){
        pid_t process_id = fork();
        if(process_id == 0){             // child block
            execute_command(tokens);
        } else if(process_id > 0){       // parent block
            parent(process_id);
        } else{
            fprintf(stderr,"Error : fork cancelled");
            free(tokens);
            exit(EXIT_FAILURE);
        }
    }
}

int execute_ast(tree_node *head,pointer_struct *ptr){
    if(head == NULL){
        return 0;
    }
    switch(head->type){

        case NODE_CMD:
	     execute_cmds(head->cmd_node.tokens,head->cmd_node.count,ptr);
	     break;
	case NODE_PIPE:
	     execute_ast(head->operator_node.left,ptr);
	     execute_ast(head->operator_node.right,ptr);
	     break;
	case NODE_OR :
	     execute_ast(head->operator_node.left,ptr);
	     execute_ast(head->operator_node.right,ptr); 
	     break;
	case NODE_AND:
             execute_ast(head->operator_node.left,ptr);
	     execute_ast(head->operator_node.right,ptr);
	     break;
    }
    fflush(stdout);
    return 1;

} 

int free_node(tree_node *head){

    switch(head->type){

        case NODE_CMD:

	     free(head);
	     break;

	case NODE_PIPE:
	case NODE_OR : 
	case NODE_AND:
	     if(head->operator_node.left != NULL){
                 free_node(head->operator_node.left);
	     }
	     if(head->operator_node.right != NULL){
	         free_node(head->operator_node.right); 
	     }
	     free(head);

	     break;

    }
    return 1;

}
