CC = g++
FILES = main.cpp Graph.cpp solution.cpp
OPTIONS = -std=c++11

#main section
main: $(FILES)
	$(CC) $(OPTIONS) $(FILES) -o main

clear:
	rm -f main