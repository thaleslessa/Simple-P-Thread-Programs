all: hellothreads primeornot vowcon

hellothreads: hellothreads.o
	gcc hellothreads.o -o hellothreads -lpthread
	rm hellothreads.o

hellothreads.o: hellothreads.c
	gcc -c hellothreads.c

primeornot: primeornot.o
	gcc primeornot.o -o primeornot -lpthread
	rm primeornot.o

primeornot.o: primeornot.c
	gcc -c primeornot.c

vowcon: vowcon.o
	gcc vowcon.o -o vowcon -lpthread
	rm vowcon.o

vowcon.o: vowcon.c
	gcc -c vowcon.c
