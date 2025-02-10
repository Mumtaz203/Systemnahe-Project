#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_operations.h"
#include "../include/data_structures.h"
#include "../include/threading.h"
#include "../include/utils.h"

extern int show_last_modified;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./program [options] <directory1> <directory2> ...\n");
        return 1;
    }

    char *directories[10]; 
    int num_dirs = 0;

    parse_arguments(argc, argv, &num_dirs, directories);

    if (num_dirs > 0) {
        create_threads(num_dirs, directories);
    } else {
        printf("No directories specified.\n");
    }

    return 0;
}

