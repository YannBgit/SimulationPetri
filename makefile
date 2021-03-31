run: main.o
	./main.o

main.o: clean main.cpp
	g++ main.cpp -o main.o -g

debug: main.o
	gdb ./main.o

memcheck: main.o
	valgrind ./main.o

clean:
	rm -f *.o