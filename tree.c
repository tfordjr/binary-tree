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
		insert(c, &root);
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
                insert(input, &root);
                printf("%s...", input);
            }
    	}
    }

	// This happens no matter what path you use to create binary tree

    printf("\n\tPre Order:\n");
    printPreOrder(root);

    printf("\n\tIn Order:\n");
    printInOrder(root);

    printf("\n\tPost Order:\n");
    printPostOrder(root);

    printf("\n\tDestroying Tree...\n");
    destroy_tree(root);

    if(myFile)
	fclose(myFile);
    
    return 0;
}
