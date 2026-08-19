CC = gcc
FLAG = -g -Wextra -Wall -Wpedantic -fsanitize=address
TARGET = shell
SHARED = shared.h struct.h function.h parser.h helper.h
OBJ = shell.o getline.o parser.o pid_handler.o buildins.o hash.o function.o helper.o

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) -fsanitize=address $(OBJ) -o $(TARGET)

shell.o : shell.c $(SHARED)
	$(CC) $(FLAG) -c shell.c

getline.o : getline.c $(SHARED)
	$(CC) $(FLAG) -c getline.c

parser.o : parser.c $(SHARED)
	$(CC) $(FLAG) -c parser.c

pid_handler.o : pid_handler.c $(SHARED)
	$(CC) $(FLAG) -c pid_handler.c

buildins.o : buildins.c $(SHARED) 
	$(CC) $(FLAG) -c buildins.c

hash.o : hash.c $(SHARED)
	$(CC) $(FLAG) -c hash.c

function.o : function.c $(SHARED)
	$(CC) $(FLAG) -c function.c

helper.o : helper.c $(SHARED)
	$(CC) $(FLAG) -c helper.c

clean :
	rm -f $(OBJ) $(TARGET)

