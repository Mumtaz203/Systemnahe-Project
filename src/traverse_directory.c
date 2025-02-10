#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/file_operations.h"
#include "../include/utils.h"
#include "../include/threading.h"

extern int show_last_modified;
extern int show_list_mode;
extern int recursive_mode;
extern pthread_mutex_t list_mutex;

void* traverse_directory_thread(void *arg);  // int* yerine void* yaptık

void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode))  ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x " : "- ");
}

int traverse_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return -1;  // Hata durumunda -1 döndür
    }

    struct dirent *entry;
    struct stat file_stat;

    pthread_mutex_lock(&list_mutex);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            if (show_list_mode) {
                print_permissions(file_stat.st_mode);
                printf("%3ld ", (long)file_stat.st_nlink);
                struct passwd *pw = getpwuid(file_stat.st_uid);
                struct group *gr = getgrgid(file_stat.st_gid);
                printf("%-8s %-8s ", pw->pw_name, gr->gr_name);
                printf("%8lld ", (long long)file_stat.st_size);
                if (show_last_modified) {
                    printf("%s ", ctime(&file_stat.st_mtime));
                }
                printf("%s\n", entry->d_name);
            } else if (show_last_modified) {
                printf("%-30s %s", entry->d_name, ctime(&file_stat.st_mtime));
            } else {
                printf("%s\n", entry->d_name);
            }

            if (recursive_mode && S_ISDIR(file_stat.st_mode)) {
                pthread_t thread;
                char *subdir = strdup(full_path);
                if (subdir) {
                    if (pthread_create(&thread, NULL, traverse_directory_thread, subdir) == 0) {
                        pthread_detach(thread);
                    } else {
                        perror("Failed to create thread for subdirectory");
                        free(subdir);
                    }
                }
            }
        } else {
            perror("Failed to get file stats");
        }
    }
    pthread_mutex_unlock(&list_mutex);

    closedir(dir);
    return 0;  // Başarılı tamamlandıysa 0 döndür
}

void* traverse_directory_thread(void *arg) {
    char *path = (char *)arg;
    printf("\n🔍 Entering directory (thread created): %s\n", path);
    traverse_directory(path);
    free(path);
    return NULL;
}

