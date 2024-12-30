#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "data_structures.h"
#include "threading.h"
#include "/home/mitas/project/include/utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./program [options] <directory>\n");
        return 1;
    }

    char *directory = argv[argc - 1];
    parse_arguments(argc, argv);

    
    traverse_directory(directory);

    return 0;
}

