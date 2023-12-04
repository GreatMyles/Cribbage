compileAndRun:
	make compile
	make run

compile:
	gcc -Wall main.c -o main

run:
	./main