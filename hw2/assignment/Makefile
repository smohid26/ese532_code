App.o: App.c App.h
	gcc -O2 -c App.c -o App.o

Compress.o: Compress.c App.h stopwatch_c.h
	gcc -O2 -c Compress.c -o Compress.o

Differentiate.o: Differentiate.c App.h stopwatch_c.h
	gcc -O2 -c Differentiate.c -o Differentiate.o

Filter.o: Filter.c App.h stopwatch_c.h
	gcc -O2 -c Filter.c -o Filter.o

Scale.o: Scale.c App.h stopwatch_c.h
	gcc -O2 -c Scale.c -o Scale.o

stopwatch_c.o: stopwatch_c.cpp stopwatch_c.h stopwatch.h
	g++ -O2 -c stopwatch_c.cpp

all: App.o Compress.o Differentiate.o Filter.o Scale.o stopwatch_c.o
	g++ -O2 App.o Compress.o Differentiate.o Filter.o Scale.o stopwatch_c.o -o App

gprof: App.o Compress.o Differentiate.o Filter.o Scale.o stopwatch_c.o
	g++ -pg -O2 App.o Compress.o Differentiate.o Filter.o Scale.o stopwatch_c.o -o App
clean:
	rm -f App.o Compress.o Differentiate.o Filter.o Scale.o stopwatch_c.o App Output.bin