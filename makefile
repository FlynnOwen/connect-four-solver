all: main

main:
	g++ -Wall -std=c++17 connect-four-solver/main.cpp -o connect-four 

clean:
	rm -f connect-four