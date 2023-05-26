#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_value;
    struct node *left;
    struct node *right;
};

struct node *root = 0;

void destroy_tree(struct node *leaf) {
    if( leaf != 0 ) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        free( leaf );
    }
}

void insert(int key, struct node **leaf) {
    if( *leaf == 0 ) {
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->key_value = key;
        (*leaf)->left = 0;
        (*leaf)->right = 0;
    } else if(key < (*leaf)->key_value) {
        insert( key, &(*leaf)->left );
    } else if(key > (*leaf)->key_value) {
        insert( key, &(*leaf)->right );
    }
}

struct node *search(int key, struct node *leaf) {
    if( leaf != 0 ) {
        if(key==leaf->key_value) {
            return leaf;
        } else if(key<leaf->key_value) {
            return search(key, leaf->left);
        } else {
            return search(key, leaf->right);
        }
    } else return 0;
}

void printPreOrder(struct node *leaf) {
    if( leaf != 0 ) {
        printf("%d...", leaf->key_value);
        printPreOrder(leaf->left);
        printPreOrder(leaf->right);
    }
}

void printInOrder(struct node *leaf) {
    if( leaf != 0 ) {
        printInOrder(leaf->left);
        printf("%d...", leaf->key_value);
        printInOrder(leaf->right);
    }
}

void printPostOrder(struct node *leaf) {
    if( leaf != 0 ) {
        printPostOrder(leaf->left);
        printPostOrder(leaf->right);
        printf("%d...", leaf->key_value);
    }
}

int main() {
    printf("This program reads in text files and creates binary trees from them! \n");

    //FILE *myFile = fopen("numbers.txt", "r");
    FILE *myFile = fopen("C:\\Users\\Terry\\CLionProjects\\binarytree\\numbers.txt", "r");

    if (myFile == NULL) {
        printf("Can't open file...\n");
    } else {
        printf("File opened successfully!\n");
        int input;
        while (fscanf(myFile, "%d", &input) != EOF)
        {
            insert(input, &root);
            printf("%d...", input);
        }
    }

    printf("\nPrinting Tree Pre Order!!!...");
    printPreOrder(root);

    printf("\nPrinting Tree In Order!!!...");
    printInOrder(root);

    printf("\nPrinting Tree Post Order!!!...");
    printPostOrder(root);

    printf("\nDestroying Tree...");
    destroy_tree(root);

    fclose(myFile);
    return 0;
}

