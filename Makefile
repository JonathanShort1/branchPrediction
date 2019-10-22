CC=g++
CFLAGS= -Wall
DEBUG= -g

main: main.cpp always_taken.cpp predictor.cpp
	$(CC) $(CFLAGS) -o main.out main.cpp always_taken.cpp predictor.cpp

debug: main.cpp always_taken.cpp predictor.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o main.out main.cpp always_taken.cpp predictor.cpp

clean:
	rm -rf main.out