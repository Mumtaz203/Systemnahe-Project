#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

int show_last_modified = 0; 
int  show_list_mode = 0;
int recursive_mode = 0;
void parse_arguments(int argc, char *argv[]) {
    show_last_modified = 0; 
     show_list_mode = 0;

    for (int i = 1; i < argc; i++) { 
        if (strcmp(argv[i], "-r") == 0) {
            printf("Recursive mode enabled.\n");
        } else if (strcmp(argv[i], "-l") == 0) {
		show_list_mode = 1;
            printf("List mode enabled.\n");
        }else if (strcmp(argv[i], "-R") == 0) {
            printf("Recursive listing enabled.\n");
            recursive_mode = 1; 
       } 
	else if (strcmp(argv[i], "-T") == 0) { 
            printf("Show last modification time enabled.\n");
            show_last_modified = 1; 
        } else if (argv[i][0] == '-') {
            printf("Unknown option: %s\n", argv[i]);
        }
    }
}


