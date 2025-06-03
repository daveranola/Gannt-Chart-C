#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "printGannt.h"
#include "userInput.h"


// main void loop
int main(void)
{ 
    //ASCII ART
    printf(" ________  ________  ________   ________   _________        ________  ___  ___  ________  ________  _________   \n");
    printf("|\\   ____\\|\\   __  \\|\\   ___  \\|\\   ___  \\|\\___   ___\\     |\\   ____\\|\\  \\|\\  \\|\\   __  \\|\\   __  \\|\\___   ___\\ \n");
    printf("\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\|___ \\  \\_|     \\ \\  \\___|\\ \\  \\\\  \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_| \n");
    printf(" \\ \\  \\  __\\ \\   __  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\       \\ \\  \\    \\ \\   __  \\ \\   __  \\ \\   _  _\\   \\ \\  \\  \n");
    printf("  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\       \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\  \\|   \\ \\  \\ \n");
    printf("   \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\   \\ \\__\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\ \\__\\ \\__\\\\ _\\    \\ \\__\\ \n");
    printf("    \\|_______|\\|__|\\|__|\\|__| \\|__|\\|__| \\|__|    \\|__|        \\|_______|\\|__|\\|__|\\|__|\\|__|\\|__|\\|__|    \\|__|\n\n");
    // user inpiut choice variables (max 10 characters)
    char choice[10];
    char option[10];

    printf("Welcome to the Gantt Generator\n");
    // while loop to ask user for Gannt chart option
    while (1) {
        printf("Would you like to use the test example or create your own Gantt from scratch? (yes or no)\n");
        scanf("%9s", choice);
        
        if (strcmp(choice, "yes") == 0) {
            testDataCircular();
            // testDataNoCircular();
            break;
        } else if (strcmp(choice, "no") == 0) {
            getUserInput();
            break;
        } else {
            printf("Invalid input. Please restart the program and enter 'yes' or 'no'.\n");
        }
    }


    // while loop prompts user for the next action
    while (1) {
        printf("\nIf you wish to edit the Gantt please type 'edit' / If you wish to run a test, type 'test' or to exit, type 'quit':\n");
        scanf("%9s", option);

        if (strcmp(option, "edit") == 0) {
            editTask();
        } else if (strcmp(option, "test") == 0) {
            runTest();
        } else if (strcmp(option, "quit") == 0) {
            printf("Exiting program...\n");
            break;
        } else {
            printf("Invalid input. Please enter 'edit', 'test', or 'quit'.\n");
        }
    }

    return 0;

}
