#include <stdio.h>
#include <string.h>
#include "utils.h"

void parse_arguments(int argc, char *argv[]) {
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            printf("Recursive mode enabled.\n");
        } else if (strcmp(argv[i], "-l") == 0) {
            printf("List mode enabled.\n");
        } else {
            printf("Unknown option: %s\n", argv[i]);
        }
    }
}

