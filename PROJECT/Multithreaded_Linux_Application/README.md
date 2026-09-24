Multithreaded Linux Application Using POSIX Threads and Mutexes
Project Overview
This project is a Multithreaded Linux Application developed using the C programming language and POSIX Threads.

The application follows a Producer-Consumer model, where the main thread reads tasks from an input file and adds them to a shared task queue. Three worker threads retrieve and process the tasks concurrently.

The project demonstrates important Operating Systems concepts including:

Process/thread creation
Thread synchronization
Mutexes
Condition variables
Shared resources
Signal handling
Graceful thread termination
Problem Statement
In a multithreaded application, multiple worker threads may need to access the same shared data simultaneously. Without proper synchronization, this can lead to race conditions and inconsistent results.

This project implements a thread-safe task processing system where:

The main thread produces tasks.
Multiple worker threads consume tasks.
A shared circular queue stores pending tasks.
Mutexes protect shared resources.
A condition variable coordinates worker threads.
SIGINT handling provides graceful shutdown.
Processed results are stored in an output file.
Objectives
Implement multithreading using POSIX Threads.
Create and manage multiple worker threads.
Implement a shared circular task queue.
Synchronize access to shared resources using mutexes.
Use condition variables for thread coordination.
Process multiple tasks concurrently.
Store processing results in a file.
Implement graceful shutdown using SIGINT.
Demonstrate practical Operating Systems concepts in Linux.
Technologies Used
Technology	Usage
Programming Language	C
Operating System	Linux / WSL2
Compiler	GCC
Threading	POSIX Threads (pthread)
Synchronization	Mutexes and Condition Variables
Signal Handling	SIGINT
Version Control	Git and GitHub
Project Structure
Multithreaded_Linux_Application/
│
├── src/
│   ├── main.c
│   ├── task_queue.c
│   └── task_queue.h
│
├── data/
│   └── tasks.txt
│
├── output/
│   └── results.txt
│
└── README.md
System Architecture
                    Input File
                  data/tasks.txt
                        │
                        ▼
                ┌───────────────┐
                │  Main Thread  │
                │   Producer    │
                └───────┬───────┘
                        │
                        ▼
                ┌───────────────┐
                │  Shared Task  │
                │     Queue     │
                └───────┬───────┘
                        │
              Mutex + Condition Variable
                        │
            ┌───────────┼───────────┐
            ▼           ▼           ▼
        Worker 1    Worker 2    Worker 3
            │           │           │
            └───────────┼───────────┘
                        ▼
                  Task Processing
                        │
                        ▼
                  value × value
                        │
                        ▼
                output/results.txt
Working Principle
1. Task Input
The application reads integer values from:

data/tasks.txt
Example:

10
20
30
40
50
60
70
80
90
100
2. Task Creation
Each input value is converted into a Task containing:

Task ID
Task value
Example:

Task 1 → 10
Task 2 → 20
Task 3 → 30
3. Shared Task Queue
The tasks are stored in a circular queue implemented in:

src/task_queue.c
src/task_queue.h
The queue maintains:

front
rear
count
The queue size is defined as:

#define QUEUE_SIZE 10
4. Worker Threads
The application creates three worker threads using:

pthread_create()
Each worker retrieves an available task from the shared queue and processes it.

5. Task Processing
For this implementation, each worker calculates the square of the task value.

Examples:

10 → 100
20 → 400
30 → 900
6. Synchronization
A mutex protects the shared task queue and output file.

Workers wait on a condition variable when the queue is empty:

pthread_cond_wait()
When a new task is added, the main thread signals a waiting worker:

pthread_cond_signal()
This prevents unsafe simultaneous access to the shared queue.

7. Result Storage
The processed results are displayed on the terminal and written to:

output/results.txt
Graceful Shutdown
The application handles the SIGINT signal generated when the user presses:

Ctrl+C
The signal handler sets the shutdown flag:

shutdown_requested = 1;
The worker threads detect the shutdown request and terminate safely.

The main thread then waits for all workers using:

pthread_join()
Finally, files and synchronization resources are closed and destroyed.

Normal Execution
When all tasks are processed normally, the application displays:

All tasks completed.
Results saved to output/results.txt
Sample Output
Multithreaded Linux Application
Press Ctrl+C to request shutdown.

Worker 1 processed Task 1: 10 -> 100
Worker 2 processed Task 2: 20 -> 400
Worker 3 processed Task 3: 30 -> 900
Worker 3 processed Task 4: 40 -> 1600
Worker 2 processed Task 5: 50 -> 2500
Worker 1 processed Task 6: 60 -> 3600
Worker 1 processed Task 7: 70 -> 4900
Worker 2 processed Task 8: 80 -> 6400
Worker 3 processed Task 9: 90 -> 8100
Worker 1 processed Task 10: 100 -> 10000

Worker 1 stopped.
Worker 3 stopped.
Worker 2 stopped.

All tasks completed.
Results saved to output/results.txt
Compilation
Navigate to the project directory:

cd ~/OSSP/KGDM_OSSP/FORGEOS/Multithreaded_Linux_Application
Compile the application using GCC:

gcc src/main.c src/task_queue.c -o app -pthread
The -pthread option enables POSIX thread support.

Running the Application
Run the application using:

./app
Testing Graceful Shutdown
Start the application:

./app
While the application is running, press:

Ctrl+C
The application detects SIGINT and safely stops the worker threads.

Expected message:

Shutdown requested by user.
Results saved to output/results.txt
Key Operating System Concepts
POSIX Threads
Multiple worker threads are created using the POSIX Threads API.

Mutex
A mutex provides mutual exclusion and prevents multiple threads from accessing protected shared resources simultaneously.

Condition Variable
A condition variable allows worker threads to wait efficiently until a task becomes available.

Producer-Consumer Model
The main thread produces tasks and places them into the shared queue, while worker threads consume and process those tasks.

Circular Queue
The task queue uses a circular arrangement with front, rear, and count to manage tasks efficiently.

Signal Handling
SIGINT is handled to support controlled and graceful application termination.

Thread Joining
pthread_join() ensures that the main thread waits for all worker threads to finish before the application exits.

Files Description
File	Purpose
main.c	Creates worker threads, produces tasks, handles synchronization and shutdown
task_queue.c	Implements task queue operations
task_queue.h	Defines task and queue structures and function declarations
tasks.txt	Contains input task values
results.txt	Stores processed task results
README.md	Project documentation
Team
Course: Operating Systems and Systems Programming (25CS2104E)

Academic Year: 2026–27 Term: I Section: 08 Team: 06

Team Members
M. Keerthi Sri — 2520030079
N. Greeshma — 2520030080
R. Mythri — 2520030296
D. Darahasini — 2520030289
Project Status
The application has been compiled and tested successfully on Linux/WSL2 with:

Three worker threads
Shared task queue
Mutex synchronization
Condition variables
Task processing
File-based input and output
Normal completion
SIGINT-based graceful shutdown
