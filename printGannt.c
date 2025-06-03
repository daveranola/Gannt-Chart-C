#include <stdio.h>
#include <string.h>
#include "printGannt.h"

#define COLUMNS 13 //how many columns 
#define GAP 15 //the amount of lines each column has

//enum for months -> january = 0 , feb = 1 etc . . . 
typedef enum {JANUARY,FEBRURARY,MARCH,APRIL,MAY,JUNE,JULY,AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER} month; 

//enum for the test data - FIND_BANK = 0, GET_MORTGAGE_APPROVAL = 1 etc . . .
typedef enum {FIND_BANK,GET_MORTGAGE_APPROVAL,DRAW_DOWN,BUILD_FOUNDATION,
BUILD_WALLS,ROOF_AND_CEILING,PLUMBING,ELECTRICS,INSPECT_BUILD,SNAGGING} testTasks; 


void printLine(void)
{
    //goes through each column 
    for (int i = 0; i < COLUMNS+1; i++)
    {
        //prints lines for each element of size GAP
        for (int j = 0; j < GAP; j++)
        {
            //print single '-'
            printf("-"); 
        }
    }
}

void printHeader(void)
{
    //header names for the Gannt chart
    const char *headers[COLUMNS] = {"January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December", "Dependencies"};
    
    //print a line divisor
    printLine();

    //print space for the task names
    printf("\n%-30s", "");
 
    //print the header elements
    for (int i = 0; i<COLUMNS; i++)
    {
        printf("| %-10s ",  headers[i]);
    }

    printf("\n");

    //print a line divisor
    printLine();

    printf("\n");
}

void testDataNoCircular(void) {
    Task temp[10] = {
        {"Find_Bank", JANUARY, FEBRURARY, 0, {0}},
        {"Get_mortgage_approval", FEBRURARY, FEBRURARY, 1, {FIND_BANK}},
        {"Draw_Down", APRIL, JUNE, 2, {FIND_BANK, GET_MORTGAGE_APPROVAL}},
        {"Build_Foundation", MARCH, APRIL, 1, {DRAW_DOWN}},
        {"Build_Walls", APRIL, MAY, 0, {0}},
        {"Roof_and_Ceiling", MAY, JUNE, 2, {BUILD_FOUNDATION, BUILD_WALLS}},
        {"Plumbing", JULY, JULY, 1, {ROOF_AND_CEILING}},
        {"Electrics", AUGUST, SEPTEMBER, 1, {PLUMBING}},
        {"Inspect_Build", SEPTEMBER, OCTOBER, 1, {BUILD_WALLS}},
        {"Snagging", SEPTEMBER, OCTOBER, 2, {ELECTRICS, INSPECT_BUILD}}
    };

    memcpy(data, temp, sizeof(temp));
    displayGannt(data, 10);
}

void testDataCircular(void) {
    Task temp[] = {
        {"Find_Bank", JANUARY, FEBRURARY, 0, {0}},
        {"Get_mortgage_approval", FEBRURARY, FEBRURARY, 1, {FIND_BANK}},
        {"Draw_Down", APRIL, JUNE, 2, {FIND_BANK, GET_MORTGAGE_APPROVAL}},
        {"Build_Foundation", MARCH, APRIL, 2, {DRAW_DOWN, ROOF_AND_CEILING}}, // Circular
        {"Build_Walls", APRIL, MAY, 0, {0}},
        {"Roof_and_Ceiling", MAY, JUNE, 3, {BUILD_FOUNDATION, BUILD_WALLS, PLUMBING}}, // Circular
        {"Plumbing", JULY, JULY, 1, {ROOF_AND_CEILING}}, // Circular
        {"Electrics", AUGUST, SEPTEMBER, 1, {PLUMBING}},
        {"Inspect_Build", SEPTEMBER, OCTOBER, 1, {BUILD_WALLS}},
        {"Snagging", SEPTEMBER, OCTOBER, 2, {ELECTRICS, INSPECT_BUILD}}
    };

    memcpy(data, temp, sizeof(temp));
    displayGannt(data, 10);
}


void displayGannt(Task *data, int taskLen)
{
    //print the header - i.e. the column names
    printHeader();

    for (int i = 0; i < taskLen; i++)
    {
        //print the task name
        printf("%-30s", data[i].taskName);
        //goes through the months
        for (int j = 0; j < COLUMNS-1; j++)
        {
            //finds the duration of the task, if j lies in between start and end date, print XXX
            if (j >= data[i].startMonth && j <= data[i].endMonth)
            {
                printf("| %-10s ", "XXX");
            }
            //if j does not lie in between start and end, print blank
            else 
            {
                printf("| %-10s ", "");
            }
        }

        printf("| ");

        //print the dependencies of the task
        for (int j = 0; j < data[i].numOfDep; j++)
        {
            printf("%d ", data[i].dependencies[j] + 1);
        }

        printf("\n");
        printLine();
        printf("\n");
    }
}