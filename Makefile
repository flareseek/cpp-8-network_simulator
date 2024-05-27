CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first second

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp *.cpp

second.o: scenarios/second.cpp 
	$(CC) $(CFLAGS) -c scenarios/second.cpp *.cpp

first: first.o 
	$(CC) $(CFLAGS) -o first *.o

second: second.o 
	$(CC) $(CFLAGS) -o second *.o

clean:
	rm -f *.o first second
