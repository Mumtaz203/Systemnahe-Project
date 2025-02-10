#include <stdio.h>
#include <dirent.h>
#include "../include/file_operations.h"


void traverse_directorysimple(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') { 
            printf("Found: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int write_to_file(const char *filename, const char *data) { // `void` yerine `int`
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;  // Hata durumunda -1 döndür
    }

    if (fprintf(file, "%s", data) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return -1;  // Yazma hatası durumunda -1 döndür
    }

    fclose(file);
    return 0;  // Başarı durumunda 0 döndür
}


int read_from_file(const char *filename, char *buffer, size_t size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        return -1;
    }
    size_t bytesRead = fread(buffer, 1, size - 1, file);
    buffer[bytesRead] = '\0';  // Null terminator ekle

    fclose(file);
    return 0;  // Başarıyla okunduysa 0 döndür
}
