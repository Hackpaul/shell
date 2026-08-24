#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"
#include "struct.h"
#include "function.h"

void get_line(input *ptr){

    char *line = NULL;
    size_t buffer_size = 0;
    ssize_t n_size;
    
    n_size=getline(&line,&buffer_size,stdin);
    if(n_size != -1){		
        line[strcspn(line,"\n")] = '\0'; 		
        ptr->buffer = line;
        ptr->code = 1;
        ptr->buffer_size = n_size;
    } else if(feof(stdin)){    //Check for EOF
        ptr->buffer = line;
        ptr->code = 0;
        ptr->buffer_size = 0;
    } else if(ferror(stdin)){  //Check for system error
        ptr->code = -1;
	free(line);
        ptr->buffer = '\0';
        ptr->buffer_size = 1;
        clearerr(stdin);
    }
}

