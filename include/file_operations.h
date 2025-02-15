#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stddef.h>  
#include <dirent.h>  
#include <sys/stat.h> 

int traverse_directory(const char *path); 

int write_to_file(const char *filename, const char *data);
int read_from_file(const char *filename, char *buffer, size_t size);

#endif

