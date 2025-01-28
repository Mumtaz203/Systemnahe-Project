#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "../include/file_operations.h"
#include "../include/utils.h"
void traverse_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        
        if (entry->d_name[0] == '.') {
            continue;
        }

       
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        
        if (stat(full_path, &file_stat) == 0) {
            
            printf("%-20s %s", entry->d_name, ctime(&file_stat.st_mtime));
        } else {
            perror("Failed to get file stats");
        }
    }

    closedir(dir);
}


