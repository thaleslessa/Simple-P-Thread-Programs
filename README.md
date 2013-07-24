Thales Lessa
Simple Pthread Programs

Contents of Directory:
Makefile - file used to compile all 3 programs at once, and create executable for those as well.
hellothreads.c - Reads one (integer) argument from command line and creates the same number of pthreads, while they display a message.
primeornot.c - Reads one (integer) argument from command line and says if it is prime or not.
vowcon.c - Reads a string from the command line and display if each word starts with vowel or consonant, in order.
README - File specifying contents of directory and solutions to problems.

Solution to problems
a - Simply uses a for loop to create thread, make it display message, add to array, and finish execution of thread and main method.
b - Gets the integer argument, sends it to isPrime thread, gets the returning boolean and sends it with the integer argument to the print thread, which says if the number is prime or not.
c - Gets the string in the command line and sends it to both threads. Vow unlock boolean is true, so it executes first, if the word at the index idx (starts at 1) starts with a vowel, the program displays Vow: (word) and increments index idx, if not, it relinquishes control of the CPU. Con has the same structure but only works if vow unlock boolean is false. They all run while index idx is less than the global number of arguments from the command line. There is an escape statement just in case the program is stuck in the unlockvow (or !unlockvow) and there are no more arguments to be read, which would cause a core dump.
