#ifndef UTILS_H
#define UTILS_H

extern int show_last_modified;
extern int show_list_mode;
extern int recursive_mode;

void parse_arguments(int argc, char *argv[], int *num_dirs, char *directories[]);

#endif  

