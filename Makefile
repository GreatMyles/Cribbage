compileAndRun:
	make compile
	make run

compile:
	gcc -Wall -o main main.c handCount.c

run:
	./main