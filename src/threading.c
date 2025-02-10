#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../include/threading.h"
#include "../include/file_operations.h"

#define MAX_THREADS 10  

pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    char path[1024];
} ThreadArgs;

void* thread_function(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    
    
    traverse_directory(args->path);
    
    free(arg);  
    return NULL;
}

void create_threads(int num_dirs, char *directories[]) {
    pthread_t threads[MAX_THREADS];
    int i;

    for (i = 0; i < num_dirs; i++) {
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        if (!args) {
            perror("Failed to allocate memory for thread args");
            continue;
        }
        strncpy(args->path, directories[i], sizeof(args->path) - 1);
        args->path[sizeof(args->path) - 1] = '\0';

        if (pthread_create(&threads[i], NULL, thread_function, args) != 0) {
            perror("Failed to create thread");
            free(args);
        }
    }

    for (i = 0; i < num_dirs; i++) {
        pthread_join(threads[i], NULL);
    }
}

