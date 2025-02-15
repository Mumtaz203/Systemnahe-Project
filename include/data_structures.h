#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *data);
void free_list(Node *head);
void append_node(Node **head, const char *data);  

#endif

