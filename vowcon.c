//********************************************************************
//
// Thales Lessa
// Simple P-thread programs
// Vowel or Consonant?
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
#include <sched.h> /* Scheduling operations */
#include <stdbool.h> /* Boolean operators */

/* prototype for thread routines */
void vowM ( void *ptr );
void conM ( void *ptr );

int gargc;			//global argc (number of arguments in command line)
char **gargv;			//global argv (array of strings that come from the command line)
bool unlockvow = true;		//global variable that "locks" and "unlocks" the vowel method
int idx = 1;			//global pointer to value inside the arguments array

/* struct to hold data to be passed to a thread
this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
char* message;
} thdata;

//****************************************************************************************************************************
//
// Main Function
// 
// This program reads a text from command line and depending on the starting character of each string, it displays vow/con: character
// through the two threads and their respective functions.
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
// i			int		Loop Iteration Variable
// vowT			pthread_t	Thread that will eventually be used to execute the VowM function
// conT			pthread_t	Thread that will eventually be used to execute the ConM function
// data1		thdata		Thread data struct that holds a string (that's actually not used), is passed to vowT as a parameter
// data2		thdata		Thread data struct that holds a string (that's actually not used), is passed to conT as a parameter
//
//****************************************************************************************************************************

int main(int argc, char *argv[])
{
	/* initialize variables */
	gargc = argc;
	/* gargc has same value as argc */
	gargv = argv;  /* gargv is "pointing" at same array of strings argv is pointing at */
	
	int i;

	pthread_t vowT, conT; /* thread variables */

	thdata data1, data2; /* structs to be passed to threads */

	/* initialize data to pass to thread 1 */
	data1.message = NULL;

	/* initialize data to pass to thread 2 */
	data2.message = NULL;

	/* create threads 1 and 2 */
	pthread_create (&vowT, NULL, (void *) &vowM, (void *) &data1);
	pthread_create (&conT, NULL, (void *) &conM, (void *) &data2);

	/* Main block now waits for both threads to terminate, before it exits
	If main block exits, both threads exit, even if the threads have not
	finished their work */
	pthread_join(vowT, NULL);
	pthread_join(conT, NULL);

	/* exit */
	exit(0);

} /* main() */

//****************************************************************************************************************************
//
// Vowel Checking and Printing function
//
// This function grabs the first character of the word at index "idx" (global variable) of the array "gargv" (global variable) of strings that come
// from the command line. If the first character is a vowel, it prints "Vow :" and the word, if not, relinquish the CPU for the Consonant
// thread to print the word.
//
// Return Value
// -------------------
// void
//
// Function Parameters
// -------------------
// data		void*		value		NULL (is not used)
//
// Local Variables
// -------------------
// strg		char*		String at index idx of the arguments array
// ch		char		First character of the strg string
//
//*****************************************************************************************************************************

void vowM ( void *data )
{		
	while(idx < gargc)
	{
		while (unlockvow){		// as long as vow is unlocked
		if (idx == gargc) break;	/* necessary if index was incremented and vow is still unlocked, so it doesn't leave the unlockvow while loop 							(prevent core dump)*/
		char* strg = gargv[idx];	
		char ch = strg [0];
		if(ch=='a' || ch=='e' || ch=='o' || ch=='i'|| ch=='u' || ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U'){	// check if 1st character is vowel
		printf("Vow: %s\n", strg);	// if so, print string, increase index ("pointer") so we check next argument
		idx++;
		}
		else{
		unlockvow = false;		// if not, lock vow
		}
		sched_yield();
		}
	}
}

//****************************************************************************************************************************
//
// Consonant Checking and Printing function
//
// This function grabs the first character of the word at index "idx" (global variable) of the array "gargv" of strings that come
// from the command line. If the first character is a consonant, it prints "Con :" and the word, if not, relinquish the CPU for the Vowel
// thread to print the word.
//
// Return Value
// -------------------
// void
//
// Function Parameters
// -------------------
// data		void*		value		NULL (is not used)
//
// Local Variables
// -------------------
// strg		char*		String at index idx of the arguments array
// ch		char		First character of the strg string
//
//
//*****************************************************************************************************************************

void conM (void *data )
{
	while (idx < gargc)
	{
		while (!unlockvow){		// as long as vow is not unlocked (it is locked)
		if (idx == gargc) break;	/* necessary if index was incremented and vow is still locked, so it doesn't leave the !unlockvow while loop 							(prevent core dump)*/
		char* strg = gargv[idx];
		char ch = strg [0];
		if(ch=='a' || ch=='e' || ch=='o' || ch=='i'|| ch=='u' || ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U'){ // check if 1st character is vowel
		unlockvow = true;		// if so, unlock vow
		}
		else{
		printf("Con: %s\n", strg);	// if not, word starts with consonant, so print Con: "word" and increase index
		idx++;				// to next word, so we check 1st character all over again
		}
		sched_yield();			// relinquish control of the CPU
		}
	}	
}
