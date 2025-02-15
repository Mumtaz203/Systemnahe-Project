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

    // ✅ **Pipeline girdisini kontrol et**
    if (!isatty(STDIN_FILENO)) {  // Eğer stdin’den veri geliyorsa
        char stdin_input[1024];
        while (fgets(stdin_input, sizeof(stdin_input), stdin)) {
            stdin_input[strcspn(stdin_input, "\n")] = '\0';  // Yeni satır karakterini temizle
            directories[num_dirs] = strdup(stdin_input);
            num_dirs++;
            stdin_mode = 1;  // ✅ stdin’den veri alındı
        }
    }

    // ✅ **Komut satırından gelen argümanları işle**
    if (argc > 1 && !stdin_mode) {  
        parse_arguments(argc, argv, &num_dirs, directories);
    }

    // ✅ **Eğer directory varsa traverse_directory başlat**
    if (num_dirs > 0) {
        create_threads(num_dirs, directories);
    } else {
        fprintf(stderr, "No directories specified.\n");
    }

    return 0;
}

