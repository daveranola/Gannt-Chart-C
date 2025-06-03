#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "userInput.h"
#include "printGannt.h"

#define MAX_TASKS 10

// Tracks the number of tasks entered by the user || assume the user wants the test data
int taskCount = 10; 

void getUserInput(void) {
    taskCount = 0;

    // Validate task count input
    do {
        printf("How many tasks would you like to add? (1-10): ");
        if (scanf("%d", &taskCount) != 1 || taskCount < 1 || taskCount > MAX_TASKS) {
            printf("Invalid number of tasks. Please enter a number between 1 and 10.\n"); // invalid task number
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (taskCount < 1 || taskCount > MAX_TASKS); 

    // for loop to ask all necessary questions depending on task amount
    for (int i = 0; i < taskCount; i++) {
        printf("\nPlease enter the task name: "); // ask user
        scanf("%s", data[i].taskName);

        // Validate startMonth input
        do {
            printf("Start month (1-12): ");
            if (scanf("%d", &data[i].startMonth) != 1 || data[i].startMonth < 1 || data[i].startMonth > 12) {
                printf("Invalid input. Please enter a number between 1 and 12 for the start month.\n"); // invalid start month
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (data[i].startMonth < 1 || data[i].startMonth > 12);
        data[i].startMonth -= 1; // Convert to 0-based index

        // Validate endMonth input
        do {
            printf("End month (1-12): ");
            if (scanf("%d", &data[i].endMonth) != 1 || data[i].endMonth < 1 || data[i].endMonth > 12) {
                printf("Invalid input. Please enter a number between 1 and 12 for the end month.\n"); // invalid end month
                while (getchar() != '\n'); // Clear input buffer
            } else if (data[i].endMonth < data[i].startMonth) { // Check if endMonth is before startMonth
                printf("End month cannot be before the start month. Please enter a valid end month.\n"); // end month is before start month
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (data[i].endMonth < 1 || data[i].endMonth > 12 || data[i].endMonth < data[i].startMonth);
        data[i].endMonth -= 1; // Convert to 0-based index

        // Validate number of dependencies input
        do {
            printf("Enter how many dependencies %s has (0-%d): ", data[i].taskName, taskCount);
            if (scanf("%d", &data[i].numOfDep) != 1 || data[i].numOfDep < 0 || data[i].numOfDep > 9) {
                printf("Invalid input. Please enter a number between 0 and %d for the number of dependencies.\n", taskCount); // invalid amount of dependencies
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (data[i].numOfDep < 0 || data[i].numOfDep > 9);

        // Ensure dependencies are within valid range and unique
        for (int j = 0; j < data[i].numOfDep; j++) {
            int dep;
            int isDuplicate;

            do {
                isDuplicate = 0;
                printf("Enter dependent task (1-%d): ", taskCount);
                if (scanf("%d", &dep) != 1 || dep < 1 || dep > taskCount) {
                    printf("Invalid input. Please enter a valid dependent task number between 1 and %d.\n", taskCount); // dependent task is invalid
                    while (getchar() != '\n'); // Clear input buffer
                    isDuplicate = 1;
                    continue;
                }

                // Convert to 0-based index
                dep--;

                // Check if dependency is already entered
                for (int k = 0; k < j; k++) {
                    if (data[i].dependencies[k] == dep) {
                        printf("Dependency %d has already been entered. Please enter a unique dependency.\n", dep + 1);
                        isDuplicate = 1;
                        break;
                    }
                }
            } while (isDuplicate);

            data[i].dependencies[j] = dep; // Store the valid dependency
        }
    }

    printf("\nYour Gantt chart has been created!\n");
    displayGannt(data, taskCount); // Display the user-created Gantt chart
}

// function for editing tasks
void editTask(void) {
    char taskName[30], newName[30]; // variables for taskName and newName
    int startMonth, endMonth, numOfDep; // variables for other required info
    int taskFound = 0; // Flag to check if task exists

    // Validate task name input
    do {
        printf("Please enter the task name you want to change exactly\n");
        scanf("%29s", taskName);

        // Check if task exists in the Gantt chart
        for (int i = 0; i < taskCount; i++) {
            if (strcmp(data[i].taskName, taskName) == 0) {
                taskFound = 1; // Task exists
                break;
            }
        }

        if (!taskFound) {
            printf("Task not found. Please enter a task name exactly from the Gantt chart.\n"); // Task does not exist
        }
    } while (!taskFound);

    printf("Please enter the new task name or write its old one\n"); // prompt user for new task name
    scanf("%29s", newName);

    // Validate startMonth input
    do {
        printf("Start month (1-12): \n");
        if (scanf("%d", &startMonth) != 1 || startMonth < 1 || startMonth > 12) {
            printf("Invalid input. Please enter a number between 1 and 12 for the start month.\n"); // invalid start month
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (startMonth < 1 || startMonth > 12);

    // Validate endMonth input
    do {
        printf("End month (1-12): \n");
        if (scanf("%d", &endMonth) != 1 || endMonth < 1 || endMonth > 12) {
            printf("Invalid input. Please enter a number between 1 and 12 for the end month.\n"); // invalid end month
            while (getchar() != '\n'); // Clear input buffer
        } else if (endMonth < startMonth) {
            printf("End month cannot be before the start month. Please enter a valid end month.\n"); // end month is before start month
        }
    } while (endMonth < 1 || endMonth > 12 || endMonth < startMonth);

    // Validate number of dependencies input
    do {
        printf("Enter how many dependencies this task has (0-%d):\n", taskCount);
        if (scanf("%d", &numOfDep) != 1 || numOfDep < 0 || numOfDep > 9) {
            printf("Invalid input. Please enter a number between 0 and %d.\n", taskCount); // invalid amount of dependencies
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (numOfDep < 0 || numOfDep > 9);

    int dependencies[MAX_TASKS];

    for (int i = 0; i < numOfDep; i++) {
        int dep;
        int isDuplicate;

        do {
            isDuplicate = 0;
            printf("Enter dependency %d: \n", i + 1);

            if (scanf("%d", &dep) != 1) {
                printf("Invalid input. Please enter a valid dependency.\n"); // dependency is invalid
                while (getchar() != '\n'); // Clear input buffer
                isDuplicate = 1;
                continue;
            }

            // Convert to zero-based index
            dep--;

            // Check if dependency is already entered
            for (int j = 0; j < i; j++) {
                if (dependencies[j] == dep) {
                    printf("Dependency %d has already been entered. Please enter a different dependency.\n", dep + 1); // dependency has already been entered
                    isDuplicate = 1;
                    break;
                }
            }
        } while (isDuplicate);

        dependencies[i] = dep; // Store the valid dependency
    }

    // Modify the task details
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(data[i].taskName, taskName) == 0) {
            strcpy(data[i].taskName, newName); // if task name is different, change name
            data[i].startMonth = startMonth - 1; // Convert to 0-indexed
            data[i].endMonth = endMonth - 1; // Convert to 0-indexed
            data[i].numOfDep = numOfDep;
            memcpy(data[i].dependencies, dependencies, sizeof(dependencies) * numOfDep);
        }
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    displayGannt(data, taskCount);
}


//Depth-First search algorithm - i.e. goes through all the branches / dependencies
int isCircular(int taskIndex, int visited[]) {
    // if visited, then it means there is circular dependency (visits the task twice) -> return 1
    if (visited[taskIndex]) return 1; 

    //mark the task position to visited
    visited[taskIndex] = 1;

    //goes through all the tasks and its dependencies
    for (int i = 0; i < data[taskIndex].numOfDep; i++) {
        //dep is the dependency of the task to be checked if it is circular
        int dep = data[taskIndex].dependencies[i];
        if (isCircular(dep, visited)) {
            printf("%d <- ", taskIndex+1);
            //if isCircular, return 1 as it is true
            return 1; 
        }
    }

    // Remove from recursion stack, if there is no circular Dependency
    visited[taskIndex] = 0; 
    //return 0, meaning there is no circular dependency
    return 0;

}

void printCriticalPath(int taskIndex)
{
    //prints the dependency/task its on
    printf("%d -> ", taskIndex+1);

    //goes through the all the dependencies of the given task
    for (int i = 0; i < data[taskIndex].numOfDep; i++) {
        //dep is the dependency of the task to be checked if it is circular
        int dep = data[taskIndex].dependencies[i];
        //recursion call
        printCriticalPath(dep);
    }
}

void runTest(void) {
    //task name to be tested
    char task[30];
    //assumes that the task doesnt exist
    int taskIndex = -1;

    while (1) {
        printf("Enter the task to be tested:\n");
        scanf("%s", task);

        // Check if the task exists
        for (int i = 0; i < taskCount; i++) {
            if (strcmp(task, data[i].taskName) == 0) {
                //sets the taskIndex to the position of the task in the taskCount
                taskIndex = i;
                break;
            }
        }

        if (taskIndex != -1) {
            break; // Task exists, proceed with testing
        } else {
            printf("This task does not exist in the Gantt chart. Please enter a task name again.\n");
        }
    }


    //array to keep track of the visited tasks
    int visited[MAX_TASKS] = {0};


    //goes through all the tasks and its dependencies
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(task, data[i].taskName) == 0)
        {
            //checks if task is circular || i = taskIndex to be tested, visited - array 
            if (isCircular(i, visited)) {
                printf("!!! Circular Dependency Found in Task %s !!!\n", data[i].taskName);
                return;
            }
            else {
                //if not cirular, print the critical path of the task
                printCriticalPath(i);
            }
        }
    }
    printf("No circular dependencies found.\n");
}
