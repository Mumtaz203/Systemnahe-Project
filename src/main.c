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
    if (argc < 2) {
        printf("Usage: ./program [options] <directory1> <directory2> ...\n");
        return 1;
    }

    char *directories[10];
    int num_dirs = 0;

    parse_arguments(argc, argv, &num_dirs, directories);

    if (!isatty(STDIN_FILENO)) {  // Kullanıcı stdin’den veri gönderiyor mu?
        char stdin_input[1024];
        if (fgets(stdin_input, sizeof(stdin_input), stdin)) {
            stdin_input[strcspn(stdin_input, "\n")] = 0;  // Yeni satır karakterini temizle
            directories[num_dirs] = strdup(stdin_input);
            num_dirs++;
        }
    }

    if (num_dirs > 0) {
        create_threads(num_dirs, directories);
    } else {
        printf("No directories specified.\n");
    }

    return 0;
}
