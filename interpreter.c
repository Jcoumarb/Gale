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

void runFile(char* path) {

	printf("execute '%s' (it currently just reads and stores the script from path)\n", path);

	// creates pointer to read file or exits if there is an issue
	FILE *file = fopen(path, "r");
	if ( file == NULL) {
		perror("Error opening file");
		exit(1);
	}


	// Initialize variables for line reading and storage
    	char **galeFile = malloc(INITIAL_ARRAY_SIZE * sizeof(char *));
    	if (galeFile == NULL) {
        	perror("Failed to allocate memory");
        	exit(1);
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

	//What we are left with at this point is a pointer called 'galeFile' that holds all the characters (script)from the file
}

void runPrompt() {
	printf("*** Gale Interactive Execution Mode ***\n");

	char *buffer = NULL;
    	size_t bufsize = 0;

    	while (1) {
        
		// Prompt the user for input
        	printf(">> ");

        	// Use getline to read the line
        	ssize_t len = getline(&buffer, &bufsize, stdin);
        	if (len != -1) {
            		// Remove the newline character, if present
            		if (buffer[len - 1] == '\n') {
                	buffer[len - 1] = '\0';
            		}

			//checks for empty line to break
			if(len == 1) {
				break;
			}

            		// Check for the exit condition
            		if (strcmp(buffer, "exit") == 0) {
                		break;
            		}

            		// Print the stored line
            		printf("execute '%s' (it currently just reads and displays the entered line)\n", buffer);

		} else {
            		printf("Error reading input.\n");
            		break;
        	}
	}

    	// Free the allocated memory
	free(buffer);
}	
int main(int argc, char* argv[]) {

	//                                  *** Argument Handling ***

	// if more than one argument besides the executable file name is passed the program exits
	if(argc > 2) {
		printf("Usage: gale [script]\n");
		exit(1);
	}
	
	// if one line argument besides the executable is passed the file path is read and that script is executed
	else if(argc == 2) {
		runFile(argv[1]);
	}

	// if there are no arguments, it allows the user to run their code interactively and execute line by line through the terminal
	else{
		runPrompt();
	}

	//*********************************************************************************************************
}
