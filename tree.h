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
    int depth;
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

void insert(char* key, struct node **leaf, int depth) {
    if( *leaf == NULL ) {          // Create new node if none exists with same string length as given string
        *leaf = (struct node*) malloc( sizeof( struct node ) );    // Dynamic memory for each node
        (*leaf)->stringArr[0] = strdup(key);       // interestingly without strdup() throughout this function, 
        (*leaf)->stringLength = strlen(key);       // the last provided string will be in every position of the BST
        (*leaf)->numStrings = 1;
        (*leaf)->depth = depth;
	(*leaf)->left = NULL;
        (*leaf)->right = NULL;
    } else if (strlen(key) < (*leaf)->stringLength) {
        insert( key, &(*leaf)->left, depth + 1);
    } else if (strlen(key) > (*leaf)->stringLength) {
        insert( key, &(*leaf)->right, depth + 1 );
    } else {   // Case where correct node is reached and key to be added to stringArr        
	int i;       // Had to create int i for for loop here to avoid having to compile with c99 rules
	bool duplicate = false;
	for (i = 0; i < (*leaf)->numStrings;i++) {    
	    if (strcmp(key, (*leaf)->stringArr[i]) == 0) {
	 	duplicate = true;   
		break; 
	    }
	}
        if (!duplicate) {         // Have to be careful to create a set without duplicates using an array
	    (*leaf)->stringArr[(*leaf)->numStrings] = strdup(key);
            (*leaf)->numStrings++;
	}	
    }
}


void printPreOrder(struct node *leaf) {       // Print PreOrder Traversal to Std out
    if( leaf != NULL ) { 
	int i;
	for(i = 0; i < leaf->numStrings; i++) {
            printf("%s...", leaf->stringArr[i]);
        }
            
        printPreOrder(leaf->left);
        printPreOrder(leaf->right);
    }
}

void printInOrder(struct node *leaf) {     // Print InOrder Traversal to Std out
    if( leaf != NULL ) {
        printInOrder(leaf->left);
        int i;
	for(i = 0; i < leaf->numStrings; i++) {
            printf("%s...", leaf->stringArr[i]);
        }
        printInOrder(leaf->right);
    }
}

void printPostOrder(struct node *leaf) {        // Print PostOrder Traversal to Std out
    if( leaf != NULL ) {
        printPostOrder(leaf->left);
        printPostOrder(leaf->right);
 	int i;
	for(i = 0; i < leaf->numStrings; i++) {
            printf("%s...", leaf->stringArr[i]);
        }
    }
}

void printPreOrderToFile(struct node *leaf, FILE* file) {    // Print PreOrder Traversal to output file
    if( leaf != NULL ) {
	int i;
	for(i = 0; i < leaf->depth; i++) {
	   fprintf(file, "\t\t");
	}
	fprintf(file, "%d: ", leaf->stringLength);
	for(i = 0; i < leaf->numStrings; i++) {
            fprintf(file, "%s ", leaf->stringArr[i]);
        }
	fprintf(file, "\n");
            
        printPreOrderToFile(leaf->left, file);
        printPreOrderToFile(leaf->right, file);
    }
}

void printInOrderToFile(struct node *leaf, FILE* file) {      // Print InOrder Traversal to output file
    if( leaf != NULL ) {
        printInOrderToFile(leaf->left, file);
	
        int i;
	for(i = 0; i < leaf->depth; i++) {
	   fprintf(file, "\t\t");
	}
	fprintf(file, "%d: ", leaf->stringLength);
	for(i = 0; i < leaf->numStrings; i++) {
            fprintf(file, "%s ", leaf->stringArr[i]);
        }
	fprintf(file, "\n");
     

        printInOrderToFile(leaf->right, file);
    }
}

void printPostOrderToFile(struct node *leaf, FILE* file) {       // Print PostOrder Traversal to output file
    if( leaf != NULL ) {
        printPostOrderToFile(leaf->left, file);
        printPostOrderToFile(leaf->right, file);

        int i;
	for(i = 0; i < leaf->depth; i++) {
	   fprintf(file, "\t\t");
	}
	fprintf(file, "%d: ", leaf->stringLength);
	for(i = 0; i < leaf->numStrings; i++) {
            fprintf(file, "%s ", leaf->stringArr[i]);
        }
	fprintf(file, "\n");
 

    }
}


#endif
