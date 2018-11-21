.PHONY: clean

CC = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -lssl -lcrypto

all: main

main: main.cpp hash_gen.o
	$(CC) $(CXXFLAGS) main.cpp hash_gen.o -o task4

hash_gen.o: hash_gen.hpp hash_gen.cpp
	$(CC) $(CXXFLAGS) -c -g hash_gen.cpp

clean:
	rm task4 hash_gen.o