#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define MAX_STRING_LENGTH 20

void fileOutput(char*); 

int main(int argc, char* argv[]) {
    FILE* myFile = NULL;

    if (argc > 2) {
        perror("Too many arguments\n");
	return 0;
    } else if (argc == 1){  // If argc == 1, then input will come from the keyboard
	printf("Needs to read from keyboard...\n");
    	char c[MAX_STRING_LENGTH];    // Character buffer array
	int index = 0;

	while ((c[index] = getchar()) !=EOF && index < MAX_STRING_LENGTH - 1){ //buffer collects words by letter 
	    if (c[index] == '\n' || c[index] == '\t' || c[index] == ' '){
		c[index] = '\0';
		insert(c, &root, 0);     // once word is found, it is inserted into the binary tree
		index = 0;          
	    } else {
		index++;   // No newlines, tabs, or whitespace found so word is not complete
	    }
	}
    } else {   // argc == 2 so input will come from the filename provided
	char filename[20];	
	snprintf(filename, sizeof(filename), "%s.f23", argv[1]);   // .f23 appended to provided arg  
    	
	myFile = fopen(filename, "r");        

    	if (myFile == NULL) {
            perror("Can't open file...\n");      // perror checking on file
	    return 1;
    	} else {
            printf("File opened successfully!\n");
            char input[100];

            while (fscanf(myFile, "%s", input) != EOF) {    // scan input file for words
                insert(input, &root, 0);                    // insert words into binary tree
            }
    	}
    }   

    char* inFile = (argc > 1) ? argv[1] : NULL;  // InFile is provided filename. If none provided, inFile is null.
    fileOutput(inFile);      // File output generation occurs in fileOutput()

    if(myFile)
	fclose(myFile);
    return 0;
}

void fileOutput(char* inFile) {
    char filePrefix[20];
    if (inFile) {
	snprintf(filePrefix, sizeof(filePrefix), "%s", inFile);   // given name is file prefix
    } else {
	snprintf(filePrefix, sizeof(filePrefix), "out");     // "out" is default file prefix
    }    
    
    char preorderFilename[20];   // generate filename strings
    char inorderFilename[20];
    char postorderFilename[20];

    snprintf(preorderFilename, sizeof(preorderFilename), "%s.preorder", filePrefix); //fix suffixes to filenames
    snprintf(inorderFilename, sizeof(inorderFilename), "%s.inorder", filePrefix);
    snprintf(postorderFilename, sizeof(postorderFilename), "%s.postorder", filePrefix);

    FILE* preorderFile = fopen(preorderFilename, "a");  // generate file objects from filenames
    FILE* inorderFile = fopen(inorderFilename, "a");
    FILE* postorderFile = fopen(postorderFilename, "a");

    if (preorderFile == NULL || inorderFile == NULL || postorderFile == NULL) { //fopen operation error checking
	perror("tree.c: Error: Error opening one of the output files");
	exit(0);
    }
    
    printPreOrderToFile(root, preorderFile);    // Print binary tree traversals to generated output file objects
    printInOrderToFile(root, inorderFile);
    printPostOrderToFile(root, postorderFile);
    
    destroy_tree(root);    // Destroy tree and close file objects to clean up after ourselves
    fclose(preorderFile);
    fclose(inorderFile);
    fclose(postorderFile);    
}
