#include <stdio.h>
#include <assert.h>
#include "../include/data_structures.h"
#include "../include/file_operations.h"

void test_linked_list() {
    Node *head = create_node("Test Node");
    assert(head != NULL);
    assert(strcmp(head->data, "Test Node") == 0);

    free_list(head);
    printf("Linked list tests passed!\n");
}

void test_directory_traversal() {
    traverse_directory(".");
    printf("Directory traversal tests passed!\n");
}

int main() {
    test_linked_list();
    test_directory_traversal();
    return 0;
}

