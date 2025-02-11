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

#define MAX_FILES 1024  
#define MAX_SUBDIRS 100  

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

// 📌 Dosyaları tarihe göre sıralayan fonksiyon (Azalan sıralama)
int compare_mtime(const void *a, const void *b) {
    FileEntry *fileA = (FileEntry *)a;
    FileEntry *fileB = (FileEntry *)b;
    return (fileB->mtime - fileA->mtime);
}

// 📌 Dizinleri alfabetik sıraya göre sıralayan fonksiyon
int compare_name(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// 📌 Yetkileri yazdıran fonksiyon
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

// 📌 Ana traverse fonksiyonu
int traverse_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return -1;
    }

    struct dirent *entry;
    struct stat file_stat;
    char *subdirs[MAX_SUBDIRS];  // Alt dizinleri saklamak için
    int subdir_count = 0;

    // 📌 Dosyaları dinamik olarak tutuyoruz
    FileEntry *files = malloc(MAX_FILES * sizeof(FileEntry));
    if (!files) {
        perror("Memory allocation failed");
        closedir(dir);
        return -1;
    }
    int file_count = 0;

    printf("\n📂 %s:\n", path);
    pthread_mutex_lock(&list_mutex);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;  // Gizli dosyaları atla

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
                if (subdir_count < MAX_SUBDIRS) {
                    subdirs[subdir_count] = strdup(full_path);
                    subdir_count++;
                }
            }
        } else {
            perror("Failed to get file stats");
        }
    }

    pthread_mutex_unlock(&list_mutex);
    closedir(dir);

    // 📌 Eğer -T seçiliyse, dosyaları tarihe göre sıralıyoruz
    if (show_last_modified) {
        qsort(files, file_count, sizeof(FileEntry), compare_mtime);
    }

    // 📌 Dosyaları ekrana yazdır (alt dizinler hariç)
    for (int i = 0; i < file_count; i++) {
        if (show_list_mode) {
            print_permissions(files[i].mode);
            printf("%3ld ", (long)files[i].nlink);
            struct passwd *pw = getpwuid(files[i].uid);
            struct group *gr = getgrgid(files[i].gid);
            printf("%-8s %-8s ", pw->pw_name, gr->gr_name);
            printf("%8lld ", (long long)files[i].size);
            if (show_last_modified) {
                char time_str[20];
                strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S %Y", localtime(&files[i].mtime));
                printf("%s ", time_str);
            }
            printf("%s\n", files[i].name);
        } else if (show_last_modified) {
            char time_str[20];
            strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S %Y", localtime(&files[i].mtime));
            printf("%-30s %s\n", files[i].name, time_str);
        } else {
            printf("%s\n", files[i].name);
        }
    }

    fflush(stdout);  // 📌 Çıktıyı hemen yazdır!

    free(files);  // 📌 Bellek sızıntısını önlemek için free()

    // 📌 **ALT DİZİNLERİ GEZİYORUZ (SIRALI OLARAK)**
    if (subdir_count > 0) {
        qsort(subdirs, subdir_count, sizeof(char *), compare_name);
    }

    for (int i = 0; i < subdir_count; i++) {
        printf("\n🔍 Entering directory: %s\n", subdirs[i]);
        fflush(stdout);  // 📌 Çıktının sırasını bozmamak için!

        traverse_directory(subdirs[i]);

        free(subdirs[i]);  // 📌 Bellek sızıntısını engelle!
    }

    return 0;
}

