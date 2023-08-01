#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 100

void printText(const char* lines[], int numLines) {
    for (int i = 0; i < numLines; i++) {
        printf("%s\n", lines[i]);
    }
}

int saveToFile(const char* filename, const char* lines[], int numLines) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening the file.\n");
        return 0;
    }

    for (int i = 0; i < numLines; i++) {
        fputs(lines[i], file);
    }

    fclose(file);
    printf("File saved successfully.\n");
    return 1;
}

int main() {
    const char* prompt = "\t\t\t\t\t--- Notepad ---  \n\t\t\t\tType ':q' to quit or ':w' to save\n";
    const char* goodbyeMsg = "Goodbye!";

    const char* lines[MAX_LINES];
    char buffer[MAX_LINE_LENGTH];
    int numLines = 0;

    printf("%s", prompt);

    while (1) {
        // Read the text line.
        fgets(buffer, MAX_LINE_LENGTH, stdin);

        // Check if the user wants to quit the notepad.
        if (strcmp(buffer, ":q\n") == 0) {
            break;
        }

        // Check if the user wants to save the text line.
        if (strcmp(buffer, ":w\n") == 0) {
            // Get the information to save the text line if user wants. It requires the file name.
            printf("Enter the filename to save: ");
            fgets(buffer, MAX_LINE_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character.
            strcat(buffer, ".txt");
            if (saveToFile(buffer, lines, numLines)) {
                break;
            }
        } else {
            // Allocate memory for the line and copy the text.
            lines[numLines] = strdup(buffer);

            // Increase the number of lines.
            numLines++;

            // Check if the user have reached the maximum number of lines.
            if (numLines >= MAX_LINES) {
                printf("Reached the maximum number of lines.\n");
                break;
            }
        }
    }

    printf("%s", goodbyeMsg);

    for (int i = 0; i < numLines; i++) {
        free((void*)lines[i]);
    }

    return 0;
}
