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

