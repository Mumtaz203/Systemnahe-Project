#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

int show_last_modified = 0;
int show_list_mode = 0;
int recursive_mode = 0;

void parse_arguments(int argc, char *argv[], int *num_dirs, char *directories[]) {
    show_last_modified = 0;
    show_list_mode = 0;
    recursive_mode = 0;
    
    *num_dirs = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-R") == 0) {
            printf("Recursive mode enabled.\n");
            recursive_mode = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            printf("List mode enabled.\n");
            show_list_mode = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            printf("Show last modification time enabled.\n");
            show_last_modified = 1;
        } else if (argv[i][0] == '-') {
            printf("Unknown option: %s\n", argv[i]);
        } else {
            directories[*num_dirs] = argv[i];
            (*num_dirs)++;
        }
    }
}

