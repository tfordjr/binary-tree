#ifndef BINTREESTRINGS_H
#define BINTREESTRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char **key_values;
    struct node **children;
    int num_keys;  // To store the number of strings in the array
    int max_keys;  // To store the maximum capacity of the array
};

struct node *root = NULL;

void destroy_tree(struct node *leaf) {
    if (leaf != NULL) {
        for (int i = 0; i < leaf->num_keys; i++) {
            free(leaf->key_values[i]);
        }
        free(leaf->key_values);
        for (int i = 0; i < leaf->max_keys; i++) {
            destroy_tree(leaf->children[i]);
        }
        free(leaf->children);
        free(leaf);
    }
}

void insert(const char *key, struct node **leaf, int length) {
    if (*leaf == NULL) {
        *leaf = (struct node *)malloc(sizeof(struct node));
        (*leaf)->key_values = (char **)malloc(sizeof(char *) * 10); // Initial capacity
        (*leaf)->key_values[0] = strdup(key);
        (*leaf)->num_keys = 1;
        (*leaf)->max_keys = 10;  // Initial capacity
        (*leaf)->children = (struct node **)malloc(sizeof(struct node *) * 10);
        for (int i = 0; i < 10; i++) {
            (*leaf)->children[i] = NULL;
        }
    } else {
        if (strlen(key) == length) {
            if ((*leaf)->num_keys < (*leaf)->max_keys) {
                (*leaf)->key_values[(*leaf)->num_keys++] = strdup(key);
            } else {
                // Resize the array if it's full
                (*leaf)->max_keys *= 2;
                (*leaf)->key_values = (char **)realloc((*leaf)->key_values, sizeof(char *) * (*leaf)->max_keys);
                (*leaf)->key_values[(*leaf)->num_keys++] = strdup(key);
            }
        } else if (strlen(key) < length) {
            int index = strlen(key);
            insert(key, &((*leaf)->children[index]), length);
        }
    }
}

void printPreOrder(struct node *leaf, int length) {
    if (leaf != NULL) {
        for (int i = 0; i < leaf->num_keys; i++) {
            printf("%s...", leaf->key_values[i]);
        }
        for (int i = 0; i < leaf->max_keys; i++) {
            printPreOrder(leaf->children[i], length + 1);
        }
    }
}


#endif