CC = gcc
CFLAGS = -Wall -g -I../include -pthread

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests

SRCS = $(SRC_DIR)/data_structures.c $(SRC_DIR)/file_operations.c $(SRC_DIR)/main.c $(SRC_DIR)/threading.c $(SRC_DIR)/utils.c $(SRC_DIR)/traverse_directory.c
OBJS = $(SRCS:.c=.o)

OBJS_TEST = $(SRC_DIR)/data_structures.o $(SRC_DIR)/threading.o $(SRC_DIR)/utils.o $(SRC_DIR)/traverse_directory.o $(SRC_DIR)/file_operations.o

TARGET = program
TEST_TARGET = test_program  

TEST_LIBS = -lcunit

all: $(TARGET) $(TEST_TARGET)  

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(TEST_TARGET): $(TEST_DIR)/test_cases.c $(OBJS_TEST)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_DIR)/test_cases.c $(OBJS_TEST) $(TEST_LIBS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)
	make clean_test  

clean_test:
	rm -f $(TEST_TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) $(TEST_TARGET)

