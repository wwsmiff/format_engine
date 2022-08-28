CC = clang++
CFLAGS = -std=c++17 -pedantic -Wall -Wextra -O0

main: main.o
	${CC} main.o -o main

main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp

.PHONY: clean
clean:
	rm -f main *.o

.PHONY: run
run:
	./main
