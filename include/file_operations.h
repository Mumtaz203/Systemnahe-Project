#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stddef.h>  // size_t için gerekli
#include <dirent.h>  // traverse_directory için gerekli olabilir
#include <sys/stat.h> // Dosya bilgilerini almak için

int traverse_directory(const char *path); // Eğer dönüş değeri kullanılmıyorsa void olmalı

int write_to_file(const char *filename, const char *data);
int read_from_file(const char *filename, char *buffer, size_t size);

#endif

