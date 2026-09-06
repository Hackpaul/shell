#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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
	case NODE_UNKNOWN:
	     ptr->type = NODE_UNKNOWN;
	     break;

    }
    
    return ptr;
}
 
int execute_ast(tree_node *head,hash_table *ptr , int write_fd){
    pid_t process_id;
    int is_buildin = FAIL , pipe_fd[2];
    if(head == NULL){
        return 1;
    }
    switch(head->type){

        case NODE_CMD:

	      if(head->cmd_node.tokens[0] != NULL){

                  is_buildin = buildin_handler(head->cmd_node.tokens, head->cmd_node.count,ptr);

	          if(is_buildin == -1){
		     close(write_fd);
	             return 0;
	          }
	          if(is_buildin == FAIL){
		      
                      process_id = fork();
		
                      if(process_id == 0){             // child block

			  if(write_fd > 0){
			      dup2(write_fd,STDOUT_FILENO);
			      close(write_fd);
			  }
                          if(check_is_redirection(head) == 0){
		              exit(EXIT_FAILURE);
		          }
	                  execvp(head->cmd_node.tokens[0],head->cmd_node.tokens);
	                  fprintf(stderr,"shell :%s :is not recognised as a command\n",head->cmd_node.tokens[0]);
                          exit(EXIT_FAILURE); 
                      } else if(process_id > 0){       // parent block
			  if(write_fd > 0){ 
			      close(write_fd);
			  }
                          waitpid(process_id,NULL,0);
                      } else{
                          fprintf(stderr,"Error : fork cancelled");
			  
			  if(write_fd > 0){
			      close(write_fd);
			  }
                          return 0;
                      }

                 }    	
	     } else{
		 
	  	 if(write_fd > 0){
		     close(write_fd);
		 }
		 fprintf(stderr,"syntax error : Error near symbol\n");
	     }
	     
	     break;

	case NODE_PIPE:

	     if(pipe(pipe_fd) < 0){
	         return 0;
	     } 

	     process_id = fork();

	     if(process_id > 0){

		 close(pipe_fd[0]);
	         execute_ast(head->operator_node.left,ptr,pipe_fd[1]);
		 close(pipe_fd[1]);
		 waitpid(process_id,NULL,0);

	     } else if(process_id == 0){


		 dup2(pipe_fd[0],STDIN_FILENO);

		 close(pipe_fd[0]);
		 close(pipe_fd[1]);
	         execute_ast(head->operator_node.right,ptr,write_fd);
		 close(write_fd);
		 exit(SUCCESS);

	     } else {

		 fprintf(stderr,"Error : fork cancelled\n");

	     }

	     break;

	case NODE_OR :

	     if (execute_ast(head->operator_node.left,ptr,0) == 0){
		return 0;
	     }
	     execute_ast(head->operator_node.right,ptr,0); 
	     break;

	case NODE_AND:

             if (execute_ast(head->operator_node.left,ptr,0) == 1) {
	     }
	     execute_ast(head->operator_node.right,ptr,0);
	     break;

	case NODE_UNKNOWN:

	     fprintf(stderr,"syntax error : Error near operator.\n");
	     return 0;
	     break;

    }

    fflush(stdout);
    return 1;

} 

int free_node(tree_node *head){

    if(head == NULL){
	return 0;
    }
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

	case NODE_UNKNOWN:

	     free(head);

    }
    return 1;

}
