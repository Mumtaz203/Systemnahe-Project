//THREADING.H

#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

#define MAX_THREADS 10

typedef struct {
    char path[1024];
} ThreadArgs; 

extern pthread_mutex_t list_mutex;
extern pthread_mutex_t thread_count_mutex;
extern int active_threads;

extern void* thread_function(void *arg);  

void create_threads(int num_dirs, char *directories[]);

#endif
