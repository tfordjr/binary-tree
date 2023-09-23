#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define MAX_STRING_LENGTH 20


int main(int argc, char* argv[]) {
    FILE* myFile = NULL;

    if (argc > 2) {
        perror("Too many arguments\n");
	return 0;
    } else if (argc == 1){
	printf("Needs to read from file keyboard...\n");
    	char c[MAX_STRING_LENGTH];
	int index = 0;

	while ((c[index] = getchar()) !=EOF && index < MAX_STRING_LENGTH - 1){
	    if (c[index] == '\n' || c[index] == '\t' || c[index] == ' '){
		c[index] = '\0';
		insert(c, &root, 0);
		index = 0;
	    } else {
		index++;
	    }
	}
    } else {   // input from file


	char filename[20];	
	snprintf(filename, sizeof(filename), "%s.f23", argv[1]);	    

    	myFile = fopen(filename, "r");

    	if (myFile == NULL) {
            printf("Can't open file...\n");
    	} else {
            printf("File opened successfully!\n");
            char input[100];

            while (fscanf(myFile, "%s", input) != EOF) {
                insert(input, &root, 0);
                printf("%s...", input);
            }
    	}
    }   // Everything above this line is the creation of the binary tree

    char* inFile = (argc > 1) ? argv[1] : NULL;

    char filePrefix[20];
    if (inFile) {
	snprintf(filePrefix, sizeof(filePrefix), "%s", inFile);
    } else {
	snprintf(filePrefix, sizeof(filePrefix), "out");
    }    
    
    char preorderFilename[20];
    char inorderFilename[20];
    char postorderFilename[20];

    snprintf(preorderFilename, sizeof(preorderFilename), "%s.preorder", filePrefix);
    snprintf(inorderFilename, sizeof(inorderFilename), "%s.inorder", filePrefix);
    snprintf(postorderFilename, sizeof(postorderFilename), "%s.postorder", filePrefix);

    FILE* preorderFile = fopen(preorderFilename, "a");
    FILE* inorderFile = fopen(inorderFilename, "a");
    FILE* postorderFile = fopen(postorderFilename, "a");

    if (preorderFile == NULL || inorderFile == NULL || postorderFile == NULL) {
	perror("tree.c: Error: Error opening one of the output files");
	return 1;
    }

    fprintf(preorderFile, "Pre Order:\n");
    printPreOrderToFile(root, preorderFile);

    fprintf(inorderFile, "In Order:\n");
    printInOrderToFile(root, inorderFile);

    fprintf(postorderFile, "Post Order:\n");
    printPostOrderToFile(root, postorderFile);

    printf("\n\tDestroying Tree...\n");
    destroy_tree(root);

    if(myFile)
	fclose(myFile);

    fclose(preorderFile);
    fclose(inorderFile);
    fclose(postorderFile);   
 
    return 0;
}
