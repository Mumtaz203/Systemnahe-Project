#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "../include/file_operations.h"
#include "../include/utils.h"
#include "../include/threading.h"

extern int show_last_modified;
extern int show_list_mode;
extern int recursive_mode;

#define MAX_FILES 1024  
#define MAX_SUBDIRS 100  
#define MAX_THREADS 10  

typedef struct {
    char name[1024];
    time_t mtime;
    mode_t mode;
    off_t size;
    nlink_t nlink;
    uid_t uid;
    gid_t gid;
} FileEntry;

extern pthread_mutex_t list_mutex;
extern pthread_mutex_t thread_count_mutex;
extern int active_threads;
extern void* thread_function(void *arg);

int compare_mtime(const void *a, const void *b) {
    const FileEntry *fileA = (const FileEntry *)a;
    const FileEntry *fileB = (const FileEntry *)b;

    return (fileB->mtime - fileA->mtime);  // AZALAN sıralama için B - A olmalı
}


int compare_name(const void *a, const void *b) {
    return strcmp(((FileEntry *)a)->name, ((FileEntry *)b)->name);
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

//  Dizin içeriğini tarama fonksiyonu (Thread güvenli)
int traverse_directory(const char *path) {
    usleep(5000);

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return -1;
    }
    struct dirent *entry;
    struct stat file_stat;
    char *subdirs[MAX_SUBDIRS];
    int subdir_count = 0;
    pthread_t threads[MAX_THREADS];
    int thread_index = 0;

    FileEntry *files = malloc(MAX_FILES * sizeof(FileEntry));
    if (!files) {
        perror("Memory allocation failed");
        closedir(dir);
        return -1;
    }
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            if (file_count < MAX_FILES) {
                strcpy(files[file_count].name, entry->d_name);
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
                if (subdir_count < MAX_SUBDIRS) {
                    subdirs[subdir_count] = strdup(full_path);
                    subdir_count++;
                }
            }
        }
    }
    closedir(dir);

  if (show_last_modified) {
    
    qsort(files, file_count, sizeof(FileEntry), compare_mtime);
} else {
    
    qsort(files, file_count, sizeof(FileEntry), compare_name);
}


    pthread_mutex_lock(&list_mutex);
printf("\n🔍 Entering directory : %s\n", path);

// "total" hesaplama (dosya boyutu yerine `st_blocks` kullan)
long long total_blocks = 0;
for (int i = 0; i < file_count; i++) {
    struct stat file_stat;
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, files[i].name);

    if (stat(full_path, &file_stat) == 0) {
        total_blocks += file_stat.st_blocks;
    }
}
printf("total %lld\n", total_blocks / 2);  // `ls -l` formatındaki "total" (512-byte blokları 1K'ya çevirerek)

// Dosya listeleme işlemi
for (int i = 0; i < file_count; i++) {
    if (show_list_mode) {
        print_permissions(files[i].mode);  // İzinleri göster (drwxr-xr-x gibi)
        printf(" %3ld ", (long)files[i].nlink);  //  Bağlantı sayısı
        struct passwd *pw = getpwuid(files[i].uid);
        struct group *gr = getgrgid(files[i].gid);
        printf(" %-8s %-8s %8lld ", pw->pw_name, gr->gr_name, (long long)files[i].size);

        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&files[i].mtime));
        printf("%s ", time_str);
    }
    printf("%s\n", files[i].name);  // Dosya adını yazdır
}
pthread_mutex_unlock(&list_mutex);


    for (int i = 0; i < subdir_count; i++) {
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        if (!args) {
         perror("Failed to allocate memory for thread args");
            continue;
        }
        strncpy(args->path, subdirs[i], sizeof(args->path) - 1);
        args->path[sizeof(args->path) - 1] = '\0';

        if (pthread_create(&threads[thread_index], NULL, thread_function, args) == 0) {
            thread_index++;
        } else {
            perror("Failed to create thread");
            free(args);
        }
        free(subdirs[i]);
    }

    for (int i = 0; i < thread_index; i++) {
        pthread_join(threads[i], NULL);
    }
    free(files);
    return 0;
}
