#ifndef GETLINE
#define GETLINE

#define FAIL 0
#define SUCCESS 1 
#define MAX_BUILDINS_COMMANDS 10
#define MAX_TOKENS 10

struct line{             //Shared structure for string buffers

	int code;
	int no_of_arguments;
	char *buffer;
	size_t buffer_size;
        char *tokens[MAX_TOKENS];

};

struct hash_table{
    unsigned char *buildins[MAX_BUILDINS_COMMANDS];
    unsigned long hash_array[MAX_BUILDINS_COMMANDS];
};

void get_line(struct line *ptr);
int parser(struct line *ptr);
void execute_command(struct line *ptr);
void parent(pid_t pid);
void initialize_buildins(struct hash_table *ptr);
int buildin_handler(struct line *buffer , struct hash_table *ptr);
int hash(struct hash_table *ptr);
unsigned long hash_string(unsigned char *str);

#endif 


