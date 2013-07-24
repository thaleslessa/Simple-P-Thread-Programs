//********************************************************************
//
// Thales Lessa
// Simple P-thread programs
// Hello Threads
//
//********************************************************************

/* Includes */
#include <unistd.h> /* Symbolic Constants */
#include <sys/types.h> /* Primitive System Data Types */
#include <errno.h> /* Errors */
#include <stdio.h> /* Input/Output */
#include <stdlib.h> /* General Utilities */
#include <pthread.h> /* POSIX Threads */
#include <string.h> /* String handling */

/* prototype for thread routine */
void print_message_function ( void *ptr );

/* struct to hold data to be passed to a thread
this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
int thread_no;
char message[100];
} thdata;

//****************************************************************************************************************************
//
// Main Function
// 
// This function reads a number from the command line, creates the same number of pthreads and adds them to an array. The threads
// print a message saying "Thread (number) says hi"/
//
// Return Value
// -------------------
// int				0 to finish execution
//
// Function Parameters
// -------------------
// argc			int		value		Number of arguments coming from the command line
// argv			char**		reference	Pointer to the array of strings that are arguments in the command line
//
// Local Variables
// -------------------
// thread1		pthread_t		Thread that executes print function
// thdata		data1			Thread data struct that contains an integer (thread number) that is printed by thread
// array		pthread_t[]		Array of threads where threads are added as they are created
// i			int			Loop iteration value
// x			int			First argument from command line, after the command itself. Is a string converted to int.
//
//****************************************************************************************************************************

int main(int argc, char *argv[])
{

pthread_t thread1; /* thread variable */
thdata data1; /* struct to be passed to thread */
pthread_t array [10000];

int i;
int x = atoi(argv[1]);
for(i = 0 ; i < x ; i++){

/* initialize data to pass to the thread */
data1.thread_no = i+1;
strcpy(data1.message, "Hello!");

/* create thread */
pthread_create (&thread1, NULL, (void *) &print_message_function, (void *) &data1);

array[i] = thread1;

/* Main block now waits for the thread to terminate, before it exits
If main block exits, the thread exits, even if the thread has not
finished its work */
pthread_join(thread1, NULL);

}

/* exit */
exit(0);
} /* main() */

//****************************************************************************************************************************
//
// Print Message Function
//
// This simple function makes thread display a message where the thread "says hi" and says it's number
//
// Return Value
// -------------------
// void
//
// Function Parameters
// -------------------
// ptr		void*		value		thdata cast into void * containing information passed to thread. Contains thread number
//
// Local Variables
// -------------------
// data		thdata2		Contains thdata coming from main method
//
//****************************************************************************************************************************
void print_message_function ( void *ptr )
{

thdata *data;
data = (thdata *) ptr; /* type cast to a pointer to thdata */

/* do the work */
printf("Thread %d says %s \n", data->thread_no, data->message);

pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */
