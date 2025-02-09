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
        printf("Usage: ./program [options] <directory>\n");
        return 1;
    }
show_last_modified=0;
    char *directory = argv[argc - 1];
    parse_arguments(argc, argv);
if (show_last_modified) {
        printf("Listing files with last modification time:\n");
    }
    
    traverse_directory(directory);

    return 0;
}

