
CC = gcc
CFLAGS = -Wall -g -I../include

SRCS = data_structures.c file_operations.c main.c threading.c utils.c
OBJS = $(addprefix ../src/, $(SRCS:.c=.o))


TARGET = program


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


../src/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/


clean:
	rm -f ../src/*.o $(TARGET)

