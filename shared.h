#ifndef SHARED
#define SHARED

#define FAIL 0
#define SUCCESS 1 
#define MAX_BUILDINS_COMMANDS 10
#define MAX_TOKENS 10
#define HASH_TABLE 10
#define PATH_SIZE 4096
struct line{             //Shared structure for string buffers
	int code;
	int no_of_arguments;
	char *buffer;
	size_t buffer_size;
        char *tokens[MAX_TOKENS];
};

struct string_hash {
    char *string;
    int slot;
    struct string_hash *next;
};

struct hash_table{
    char *buildins[MAX_BUILDINS_COMMANDS];
    struct string_hash *hash_array[HASH_TABLE];
    unsigned long hashed_values[MAX_BUILDINS_COMMANDS]; 
};

 void get_line(struct line *ptr);
 int parser(struct line *ptr);

 void execute_command(struct line *ptr);
 void parent(pid_t pid);
 void initialize_buildins(struct hash_table *ptr);
 int buildin_handler(struct line *buffer , struct hash_table *ptr);

 int hash_buildins(struct hash_table *ptr);
 unsigned long hash_string(char *string);
 

#endif 


