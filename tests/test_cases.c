#include <stdio.h>
#include <CUnit/Basic.h>
#include "../include/data_structures.h"
#include "../include/utils.h"
#include "../include/file_operations.h"


void test_linked_list_single_node() {
    Node *node = create_node("Test");
    CU_ASSERT_PTR_NOT_NULL(node);
    CU_ASSERT_STRING_EQUAL(node->data, "Test");

    free_list(node);
}

void test_linked_list_multiple_nodes() {
    Node *head = create_node("First");
    append_node(&head, "Second");
    append_node(&head, "Third");

    CU_ASSERT_STRING_EQUAL(head->data, "First");
    CU_ASSERT_STRING_EQUAL(head->next->data, "Second");
    CU_ASSERT_STRING_EQUAL(head->next->next->data, "Third");

    free_list(head);
}

void test_parse_arguments_basic() {
    char *args1[] = {"program", "-T", "-l", "src"};

    int num_dirs = 0;   
    char *directories[10];

    parse_arguments(4, args1, &num_dirs, directories);

    CU_ASSERT_EQUAL(show_last_modified, 1);
    CU_ASSERT_EQUAL(show_list_mode, 1);
    CU_ASSERT_STRING_EQUAL(directories[0], "src");
}

void test_parse_arguments_recursive() {
    char *args2[] = {"program", "-R", "src", "tests"};

    int num_dirs = 0;   
    char *directories[10];

    parse_arguments(4, args2, &num_dirs, directories);

    CU_ASSERT_EQUAL(recursive_mode, 1);
    CU_ASSERT_STRING_EQUAL(directories[0], "src");
    CU_ASSERT_STRING_EQUAL(directories[1], "tests");
}

void test_parse_arguments_invalid() {
    char *args3[] = {"program", "-X", "invalid"};

    int num_dirs = 0;   
    char *directories[10];

    parse_arguments(3, args3, &num_dirs, directories);

    CU_ASSERT_EQUAL(num_dirs, 0);  // Hatalı argüman olduğu için dizin eklenmemiş olmalı
}

void test_file_read_write() {
    const char *filename = "testfile.txt";
    const char *content = "Hello, world!";
    
    write_to_file(filename, content);
    char buffer[256] = {0};
    
    read_from_file(filename, buffer, sizeof(buffer));
    
    CU_ASSERT_STRING_EQUAL(buffer, content);
    
    remove(filename); // Test sonrası dosyayı temizle
}

void test_read_nonexistent_file() {
    char buffer[256] = {0};
    int result = read_from_file("nonexistent.txt", buffer, sizeof(buffer));
    CU_ASSERT_EQUAL(result, -1);  
}

void test_traverse_directory_basic() {
    int result = traverse_directory(".");
    CU_ASSERT_EQUAL(result, 0);  // Başarılı dizin gezme durumu
}

void test_traverse_directory_invalid() {
    int result = traverse_directory("invalid_dir");
    CU_ASSERT_NOT_EQUAL(result, 0);  // Hatalı dizinde hata almalı
}

void test_traverse_directory_recursive() {
    int result = traverse_directory("src");
    CU_ASSERT_EQUAL(result, 0);  // src dizini geçerli olmalı
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Systemnahe Project Tests", 0, 0);
    
    // Bağlı liste testleri
    CU_add_test(suite, "Single Node Linked List Test", test_linked_list_single_node);
    CU_add_test(suite, "Multiple Nodes Linked List Test", test_linked_list_multiple_nodes);

    // Argüman işleme testleri
    CU_add_test(suite, "Argument Parsing Basic", test_parse_arguments_basic);
    CU_add_test(suite, "Argument Parsing Recursive", test_parse_arguments_recursive);
    CU_add_test(suite, "Argument Parsing Invalid", test_parse_arguments_invalid);

    // Dosya işlemleri testleri
    CU_add_test(suite, "File Read & Write Test", test_file_read_write);
    CU_add_test(suite, "Read Non-Existent File Test", test_read_nonexistent_file);

    // Dizin gezme testleri
    CU_add_test(suite, "Basic Directory Traversal Test", test_traverse_directory_basic);
    CU_add_test(suite, "Invalid Directory Traversal Test", test_traverse_directory_invalid);
    CU_add_test(suite, "Recursive Directory Traversal Test", test_traverse_directory_recursive);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    CU_cleanup_registry();
    return 0;
}

