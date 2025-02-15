#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/file_operations.h"
#include "../include/threading.h"
#include "../include/utils.h"

extern int show_last_modified;
extern int show_list_mode;
extern int recursive_mode;

int main(int argc, char *argv[]) {
    char *directories[10];
    int num_dirs = 0;
    int stdin_mode = 0;

   
    if (!isatty(STDIN_FILENO)) {  
        char stdin_input[1024];
        while (fgets(stdin_input, sizeof(stdin_input), stdin)) {
            stdin_input[strcspn(stdin_input, "\n")] = '\0';  
            directories[num_dirs] = strdup(stdin_input);
            num_dirs++;
            stdin_mode = 1;  
        }
    }

    
    if (argc > 1 && !stdin_mode) {  
        parse_arguments(argc, argv, &num_dirs, directories);
    }

    
    if (num_dirs > 0) {
        create_threads(num_dirs, directories);
    } else {
        fprintf(stderr, "No directories specified.\n");
    }

    return 0;
}

