
CC = gcc
CFLAGS = -Wall -g -I../include -DDEBUG


SRC_DIR = ../src
INCLUDE_DIR = ../include
TEST_DIR = ../tests


SRCS = src/data_structures.c src/file_operations.c src/main.c src/threading.c src/utils.c src/traverse_directory.c

OBJS = $(SRCS:.c=.o)

TARGET = program
TEST_TARGET = test


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(TEST_TARGET): $(TEST_DIR)/test_cases.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_cases.c $(OBJS)


install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/


clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) $(TEST_TARGET)

