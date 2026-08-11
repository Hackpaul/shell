#ifndef STRUCT_H
#define STRUCT_H

#include "shared.h"

typedef struct tree_node{
    Nodetype type;
    union {
        typedef struct{
            char *tokens[MAX_TOKENS];
	    int is_file_out;
	    int is_file_in;
	    int is_append_file;
	    char *file;
	} cmd_node;

	typedef struct{
 	    struct tree_node left;
	    struct tree_node right;
	} pipe_node;

	typedef struct{
 	    struct tree_node left;
	    struct tree_node right;
	} or_node;

	typedef struct{
 	    struct tree_node left;
	    struct tree_node right;
	} and_node;
    }
} tree_node;

typedef struct line{                  //Shared structure for string buffers
    int code;
    int no_of_arguments;
    char *buffer;
    size_t buffer_size;
    char *tokens[MAX_TOKENS];
    struct hash_table *table;
}input;

typedef struct node {
    char *string;
    int slot;
    struct node *next;
}hash_node;

typedef struct hash_table{
    char *buildins[MAX_BUILDINS_COMMANDS];
    hash_node *hash_array[HASH_TABLE];
    func do_command[MAX_BUILDINS_COMMANDS];
}hash_table;

typedef void (*func)(struct line *);   // Function pointer

#endif
