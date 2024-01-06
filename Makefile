compileAndRun:
	make compile
	make run

compile:
	gcc -Wall -o main main.c handCount.c

run:
	./main

debug: 
	gcc -g -Wall -o main main.c handCount.c
	gdb main