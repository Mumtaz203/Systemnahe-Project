#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

extern pthread_mutex_t list_mutex;

void create_threads(int num_dirs, char *directories[]);
void* traverse_directory_thread(void *arg);

#endif

