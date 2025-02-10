#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../include/data_structures.h" 

Node* create_node(const char *data) {
    
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }
    
    new_node->data = strdup(data);
    if (!new_node->data) {
        perror("Failed to allocate memory for node data");
        free(new_node); 
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        
        free(temp->data);
        free(temp);
    }
}


void append_node(Node **head, const char *data) {
    Node *new_node = create_node(data);
    if (!new_node) return;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

