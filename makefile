CC =gcc
TARGET=shell
OBJ=shell.o getline.o parser.o

all: $(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

shell.o : shell.c getline.h
	$(CC) -c shell.c

getline.o : getline.c getline.h
	$(CC) -c getline.c

parser.o : parser.c getline.h
	$(CC) -c parser.c

clean :
	rm -f $(OBJ) $(TARGET)

