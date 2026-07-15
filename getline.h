#ifndef GETLINE
#define GETLINE

struct line{             //Shared structure for string buffers

	int code;
	char *buffer;
	size_t buffer_size;
        char *tokens[10];
};

void get_line(struct line *ptr);
int parser(struct line *ptr);

#endif 


