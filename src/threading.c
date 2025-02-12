//THREADING.C
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/threading.h"
#include "../include/file_operations.h"

pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int active_threads = 0;

void* thread_function(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;

    pthread_mutex_lock(&thread_count_mutex);
    active_threads++;
    pthread_mutex_unlock(&thread_count_mutex);

    traverse_directory(args->path);

    free(args);

    pthread_mutex_lock(&thread_count_mutex);
    active_threads--;
    pthread_mutex_unlock(&thread_count_mutex);

    return NULL;
}

void create_threads(int num_dirs, char *directories[]) {  // ✅ ⁠ main.c ⁠ bunu çağırıyor
    pthread_t threads[MAX_THREADS];
    int thread_index = 0;

    for (int i = 0; i < num_dirs; i++) {
        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        if (!args) {
            perror("Failed to allocate memory for thread args");
            continue;
        }
        strncpy(args->path, directories[i], sizeof(args->path) - 1);
        args->path[sizeof(args->path) - 1] = '\0';
        
        if (pthread_create(&threads[thread_index], NULL, thread_function, args) != 0) {
            perror("Failed to create thread");
            free(args);
        } else {
            thread_index++;
        }
    }

    for (int i = 0; i < thread_index; i++) {
        pthread_join(threads[i], NULL);
    }
}
