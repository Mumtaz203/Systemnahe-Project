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

#define MAX_FILES 1024  // Maksimum dosya sayısı

void* traverse_directory_thread(void *arg);

typedef struct {
    char name[1024];
    time_t mtime;
    mode_t mode;
    off_t size;
    nlink_t nlink;
    uid_t uid;
    gid_t gid;
} FileEntry;

// Dosyaları tarihe göre sıralayan karşılaştırma fonksiyonu
int compare_mtime(const void *a, const void *b) {
    FileEntry *fileA = (FileEntry *)a;
    FileEntry *fileB = (FileEntry *)b;
    return (fileB->mtime - fileA->mtime); // Azalan sıraya göre sıralar
}

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x " : "- ");
}

int traverse_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return -1;
    }

    struct dirent *entry;
    struct stat file_stat;
    pthread_t threads[100];
    int thread_count = 0;
    char *subdirs[100];
    int subdir_count = 0;
    FileEntry files[MAX_FILES];
    int file_count = 0;

    printf("\n📂 %s:\n", path);
    pthread_mutex_lock(&list_mutex);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            if (file_count < MAX_FILES) {
                strcpy(files[file_count].name, entry->d_name);
                files[file_count].mtime = file_stat.st_mtime;
                files[file_count].mode = file_stat.st_mode;
                files[file_count].size = file_stat.st_size;
                files[file_count].nlink = file_stat.st_nlink;
                files[file_count].uid = file_stat.st_uid;
                files[file_count].gid = file_stat.st_gid;
                file_count++;
            }

            if (recursive_mode && S_ISDIR(file_stat.st_mode)) {
                subdirs[subdir_count] = strdup(full_path);
                subdir_count++;
            }
        } else {
            perror("Failed to get file stats");
        }
    }

    pthread_mutex_unlock(&list_mutex);
    closedir(dir);

    // Eğer -T seçiliyse, dosyaları tarihe göre sırala
    if (show_last_modified) {
        qsort(files, file_count, sizeof(FileEntry), compare_mtime);
    }

    // Sıralanmış dosya listesini yazdır
    for (int i = 0; i < file_count; i++) {
        if (show_list_mode) {
            print_permissions(files[i].mode);
            printf("%3ld ", (long)files[i].nlink);
            struct passwd *pw = getpwuid(files[i].uid);
            struct group *gr = getgrgid(files[i].gid);
            printf("%-8s %-8s ", pw->pw_name, gr->gr_name);
            printf("%8lld ", (long long)files[i].size);
            if (show_last_modified) {
                printf("%s ", ctime(&files[i].mtime));
            }
            printf("%s\n", files[i].name);
        } else if (show_last_modified) {
            printf("%-30s %s", files[i].name, ctime(&files[i].mtime));
        } else {
            printf("%s\n", files[i].name);
        }
    }

    // Rekürsif olarak alt dizinlere gir
    for (int i = 0; i < subdir_count; i++) {
        printf("\n🔍 Entering directory: %s\n", subdirs[i]);

        if (pthread_create(&threads[thread_count], NULL, traverse_directory_thread, subdirs[i]) == 0) {
            thread_count++;
        } else {
            perror("Failed to create thread for subdirectory");
            free(subdirs[i]);
        }
    }

    // Thread'lerin tamamlanmasını bekle
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* traverse_directory_thread(void *arg) {
    char *path = (char *)arg;
    traverse_directory(path);
    free(path);
    return NULL;
}

