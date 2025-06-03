//struct for a task 
typedef struct{
    char taskName[30]; //the name of the task 
    int startMonth; //when the task starts
    int endMonth; //when the task ends
    int numOfDep; //num of dependecncies
    int dependencies[10]; //the dependencies of the task 
}Task;

///define test data in struct array || global array accessible by all files
Task data[10];

void testDataNoCircular(void); //prints the test datas | No circular

void testDataCircular(void); //prints the test datas | Ciruclar

void printLine(void); //prints the dividing lines

void printHeader(void); //prints the header

void displayGannt(Task *data, int taskLen); //display the Gannt
