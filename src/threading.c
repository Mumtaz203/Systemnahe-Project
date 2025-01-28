#include <stdio.h>
#include <pthread.h>
#include "../include/threading.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_function(void *arg) {
    char *message = (char *)arg;

    pthread_mutex_lock(&mutex);
    printf("Thread says: %s\n", message);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void create_threads() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function, "Hello from Thread 1");
    pthread_create(&thread2, NULL, thread_function, "Hello from Thread 2");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

