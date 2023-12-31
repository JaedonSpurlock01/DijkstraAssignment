CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -std=c++17	# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.

all: prog8
SRCS = graph.cpp main.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

prog9: main.o graph.o
	$(CC) main.o graph.o -o prog9
	
clean:
	rm *.o prog9