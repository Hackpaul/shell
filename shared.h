#ifndef SHARED_H
#define SHARED_H

#define FAIL 0
#define SUCCESS 1 
#define MAX_BUILDINS_COMMANDS 10
#define MAX_TOKENS 10
#define HASH_TABLE 10
#define PATH_SIZE 4096

typedef unsigned long unit;

typedef enum{
   NODE_CMD,
   NODE_PIPE,
   NODE_OR,
   NODE_AND
} Node_type;

#endif 


