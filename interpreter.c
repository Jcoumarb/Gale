#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 1024
#define INITIAL_ARRAY_SIZE 10

// Function to dynamically add a line to the array of lines
void add_line(char ***lines, size_t *size, size_t *capacity, char *line) {
	if (*size >= *capacity) {
        	*capacity *= 2;
        	*lines = realloc(*lines, *capacity * sizeof(char *));
        	if (*lines == NULL) {
            		perror("Failed to reallocate memory");
            		exit(EXIT_FAILURE);
        	}
    	}

    	(*lines)[*size] = line;
    	(*size)++;
}

int main(int argc, char* argv[]) {

//*** This first section is designed to grab the data from teh program file and save it in an array called 'galeFile' ***
	
	//if the file path was not added exit with a message
	if(argc != 2) {
		printf("no file path provided\n");
		exit(1);
	}
	
	FILE *file = fopen(argv[1], "r");
	
	//if there is an issue opening the file exit with a message
    	if (file == NULL) {
        	perror("Error opening file");
        	exit(1);
    	}

	// Initialize variables for line reading and storage
    	char **galeFile = malloc(INITIAL_ARRAY_SIZE * sizeof(char *));
    	if (galeFile == NULL) {
        	perror("Failed to allocate memory");
        	return 1;
    	}

    	size_t size = 0, capacity = INITIAL_ARRAY_SIZE;
    	char *line = NULL;
    	size_t len = 0;
    	ssize_t read;

    	// Read each line from the file and store it in the array
    	while ((read = getline(&line, &len, file)) != -1) {
        	// Remove newline character if present
        	if (line[read - 1] == '\n') {
            		line[read - 1] = '\0';
        	}

        	add_line(&galeFile, &size, &capacity, strdup(line));
    	}

    	free(line);
    	fclose(file);
//*********************************************************************************************************************
}
