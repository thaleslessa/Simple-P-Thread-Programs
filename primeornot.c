//********************************************************************
//
// Thales Lessa
// Simple P-thread programs
// Is it prime or not?
//
//********************************************************************

/* Includes */
#include <unistd.h> 	/* Symbolic Constants */
#include <sys/types.h> 	/* Primitive System Data Types */
#include <errno.h> 	/* Errors */
#include <stdio.h> 	/* Input/Output */
#include <stdlib.h> 	/* General Utilities */
#include <pthread.h> 	/* POSIX Threads */
#include <string.h> 	/* String handling */
#include <stdbool.h>	/* Boolean operators */

/* prototype for thread routine */
void print_message_function ( void *ptr );

/* prototype for primality test algorithm*/
bool isPrime ( void *ptr );

/* struct to hold data to be passed to a thread
this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
	int info;
} thdata;

typedef struct str_thdata2
{
	bool prime;
	int info;
} thdata2;

//****************************************************************************************************************************
//
// Main Function
// 
// The function reads an argument from the command line (the first argument after the command) and sends it to the isPrime thread (thread1).
// With the boolean coming back from it, Main sends the argument and the boolean to the Print thread (thread2).
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
// primeornot		bool		Boolean that takes the returning value of the isPrime function
// x			int		Integer that coming as an argument (to be checked if is prime) from the command line 
// 					(comes as string, has to be converted to integer)
// thread1		pthread_t	Thread that will eventually be used to execute the isPrime function
// thread2		pthread_t	Thread that will eventually be used to execute the print_message_function function
// data1		thdata		Thread data struct that holds an integer, is passed to thread1 as a parameter
// data2		thdata2		Thread data struct that holds an integer and a boolean, is passed to thread2 as a parameter
//
//****************************************************************************************************************************

int main(int argc, char *argv[])
{
	bool primeornot;
	int x = atoi(argv[1]);
	
	pthread_t thread1, thread2; /* thread variables */
	thdata data1; /* structs to be passed to threads */
	thdata2 data2; /* structs to be passed to threads */

	/* initialize data to pass to thread 1 */
	data1.info = x;
	data2.info = x;

	pthread_create (&thread1, NULL, (void *) &isPrime, (void *) &data1);
	
	pthread_join(thread1, (void **)&primeornot);
	
	/* initialize data to pass to thread 2 */
	data2.prime = primeornot;

	pthread_create (&thread2, NULL, (void *) &print_message_function, (void *) &data2);

	pthread_join(thread2, NULL);

	/* exit */
	exit(0);
} /* main() */

//****************************************************************************************************************************
//
// Print Message Function
//
// This function checks if the incoming number is prime or not. Returns
// true if it is prime or false otherwise.
//
// Return Value
// -------------------
// void
//
// Function Parameters
// -------------------
// ptr		void*		value		thdata cast into void * containing information passed to thread. Information here
//						is an int (number that came as argument from command line) and boolean (prime or not)
//
// Local Variables
// -------------------
// data		thdata2		Contains thdata coming from main method
// prime	bool		Boolean data sent from main method (if incoming number is true or not)
//
//****************************************************************************************************************************
void print_message_function ( void *ptr )
{
	thdata2 *data;
	data = (thdata2 *) ptr; /* type cast to a pointer to thdata */
	bool prime = data -> prime;

	if (prime){
		printf("%d is prime\n", data -> info);
	}
	else{
		printf("%d is not prime\n", data -> info);
	}

	pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */

//****************************************************************************************************************************
//
// Is Prime Function
//
// This function checks if the incoming number is prime or not. Returns
// true if it is prime or false otherwise.
//
// Return Value
// -------------------
// bool			true/false if prime
//
// Function Parameters
// -------------------
// ptr		void*		value		thdata cast into void * containing information passed to thread. Information here
//						is just an int (number that came as argument from command line)
// 
// Local Variables
// -------------------
// data		thdata		Contains thdata coming from main method
// i		int		Loop Iteration Variable
// number	int		Integer passed from the main function, contains the number to be determined if is prime or not
//
//****************************************************************************************************************************

bool isPrime ( void *ptr )
{
	thdata *data;
	data = (thdata *) ptr; /* type cast to a pointer to thdata */
	
	int i;
	int number = data -> info;

	if (number <= 1) return false;
	
	for (i=2; i*i<=number; i++) {
        if (number % i == 0) return false;
	}	
	return true;
}
