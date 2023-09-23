#ifndef TREE_H
#define TREE_H
#define MAX_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node {
    char* stringArr[MAX_SIZE];
    int stringLength;
    int numStrings;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;


void destroy_tree(struct node *leaf) {
    if( leaf != 0 ) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        free( leaf );
    }
}

void insert(char* key, struct node **leaf) {
    if( *leaf == NULL ) {
        *leaf = (struct node*) malloc( sizeof( struct node ) );        
        (*leaf)->stringArr[0] = strdup(key);
        (*leaf)->stringLength = strlen(key);
        (*leaf)->numStrings = 1;
        (*leaf)->left = NULL;
        (*leaf)->right = NULL;
    } else if (strlen(key) < (*leaf)->stringLength) {
        insert( key, &(*leaf)->left );
    } else if (strlen(key) > (*leaf)->stringLength) {
        insert( key, &(*leaf)->right );
    } else {   // Case where correct node is reached and key to be added to stringArr
        
	int i;
	bool duplicate = false;
	for (i = 0; i < (*leaf)->numStrings;i++) {    
	    if (strcmp(key, (*leaf)->stringArr[i]) == 0) {
	 	duplicate = true;   
		break; 
	    }
	}
        if (!duplicate) {
	    (*leaf)->stringArr[(*leaf)->numStrings] = strdup(key);
            (*leaf)->numStrings++;
	}	
    }
}


void printPreOrder(struct node *leaf) {
    if( leaf != NULL ) {
        int i;
	for(i = 0; i < leaf->numStrings; i++) {
            printf("%s...", leaf->stringArr[i]);
        }
            
        printPreOrder(leaf->left);
        printPreOrder(leaf->right);
    }
}

void printInOrder(struct node *leaf) {
    if( leaf != NULL ) {
        printInOrder(leaf->left);
        int i;
	for(i = 0; i < leaf->numStrings; i++) {
            printf("%s...", leaf->stringArr[i]);
        }
        printInOrder(leaf->right);
    }
}

void printPostOrder(struct node *leaf) {
    if( leaf != NULL ) {
        printPostOrder(leaf->left);
        printPostOrder(leaf->right);
 	int i;
	for(i = 0; i < leaf->numStrings; i++) {
            printf("%s...", leaf->stringArr[i]);
        }
    }
}


#endif
