#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binTreeStrings.h"

int main() {
    printf("This program reads in text files and creates binary trees from them! \n");

    FILE *myFile = fopen("names.txt", "r");

    if (myFile == NULL) {
        printf("Can't open file...\n");
    } else {
        printf("File opened successfully!\n");
        char input[100];

        while (fscanf(myFile, "%s", input) != EOF) {
            insert(input, &root, strlen(input));
            printf("%s...", input);
        }
    }

    printf("\nPrinting Tree Pre Order!!!...");
    printPreOrder(root, 0);

    printf("\nDestroying Tree...");
    destroy_tree(root);

    fclose(myFile);
    return 0;
}
