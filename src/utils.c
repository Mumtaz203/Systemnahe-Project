#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

// Global değişken
int show_last_modified = 0;

void parse_arguments(int argc, char *argv[]) {
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            printf("Recursive mode enabled.\n");
        } else if (strcmp(argv[i], "-l") == 0) {
            printf("List mode enabled.\n");
        } else if (strcmp(argv[i], "-T") == 0) { // T opsiyonu için kontrol
            printf("Show last modification time enabled.\n");
            show_last_modified = 1; // T opsiyonu etkinleştiriliyor
        } else {
            printf("Unknown option: %s\n", argv[i]);
        }
    }
}


