CC=g++
CFLAGS= -Wall
DEBUG= -g

main: main.cpp always_taken.cpp predictor.cpp twobit.cpp
	$(CC) $(CFLAGS) -o main.out main.cpp always_taken.cpp predictor.cpp twobit.cpp

debug: main.cpp always_taken.cpp predictor.cpp twobit.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o main.out main.cpp always_taken.cpp predictor.cpp twobit.cpp

clean:
	rm -rf main.out