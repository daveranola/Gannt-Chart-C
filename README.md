own:

---

# **Gantt Chart Program – Dave Ranola & Shengxin Chen**



---

## **How to Compile the Program**

To compile the Gantt Chart program, use the following command in your terminal:

```bash
gcc -o gantt main.c printGannt.c userInput.c
```

**Explanation:**

* `gcc` — invokes the GNU Compiler Collection.
* `-o gantt` — specifies the output executable file will be named `gantt`.
* `main.c printGannt.c userInput.c` — list of source files used in the program.

After compiling, run the program using:

```bash
./gantt
```

> Ensure all source files are located in the same directory when compiling.

---

## **1. How is the Gantt Chart Displayed?**

**Function:**

```c
void displayGannt(Task *data, int taskLen);
```

**Parameters:**

* `Task *data` – a struct array that holds all the tasks
* `int taskLen` – the number of tasks the user has inputted

**How It Works:**

* Calls the function `printHeader()` to print the Gantt Chart headers
* Enters a `for` loop iterating over all tasks:

  * Prints the task name
  * Prints `"XXX"` for months between the task’s `startMonth` and `endMonth`
  * Prints spaces for months outside this interval
* After printing the task duration, it prints the dependencies by accessing the task's dependency array
* Calls `printLine();` for formatting

---

## **2. How Tasks Are Mapped to Structs**

**Struct Used:**

```c
typedef struct {
    char taskName[30];      // The name of the task
    int startMonth;         // Start month (as a number)
    int endMonth;           // End month (as a number)
    int numOfDep;           // Number of dependencies
    int dependencies[10];   // Array of task dependencies
} Task;
```

**Details:**

* Global struct array: `Task data[10];`
* Shared across all files to allow consistent task access
* Only one definition of the struct and array used across the program

---

## **3. Editing and Changing Tasks**

**Function:**

```c
void editTask(void);
```

**How It Works:**

* Prompts user to input:

  * Task name to edit
  * New task name
  * New start and end months
  * Number of dependencies
  * New dependencies
* Stores values in variables:

  ```c
  char taskName[30], newName[30];
  int startMonth, endMonth, numOfDep;
  int dependencies[MAX_TASKS];
  ```
* Searches the global array with `strcmp` to find the matching task
* If found, updates task fields:

  ```c
  strcpy(data[i].taskName, newName);
  data[i].startMonth = startMonth - 1;
  data[i].endMonth = endMonth - 1;
  data[i].numOfDep = numOfDep;
  memcpy(data[i].dependencies, dependencies, sizeof(dependencies) * numOfDep);
  ```
* Error handling implemented to ensure only valid data is accepted

---

## **4. Searching for Circular Dependencies**

**Function:**

```c
int isCircular(int taskIndex, int visited[]);
```

**Parameters:**

* `taskIndex` – index of the task to be tested
* `visited[]` – initialized to 0, tracks visited tasks

**How It Works:**

* **Recursive implementation**
* **Base case:**

  ```c
  if (visited[taskIndex]) return 1;
  ```

  * If task is already visited, a cycle is detected → return `1`
* Otherwise:

  * Loops through all dependencies of the task
  * Calls `isCircular(dep, visited)` recursively for each dependency
* If no cycles are found:

  * Resets `visited[taskIndex] = 0`
  * Returns `0`

---

## **5. ASCII Art (Gantt Chart Title)**

* The ASCII art used visually represents the title **"GANTT CHART"**
* Created using:
  [patorjk.com ASCII Text Generator](https://patorjk.com/software/taag/#p=display&v=1&f=3D-ASCII&t=GANNT%20CHART)

---

## **6. Git Repository**

**Group Name:** Dave Ranola & Shengxin Chen
**Assignment:** Assignment 2
**Repository URL:**
[https://csgitlab.ucd.ie/Jchen0086/assignment-2.git](https://csgitlab.ucd.ie/Jchen0086/assignment-2.git)
---

