CC=g++
CFLAGS= -Wall
DEBUG= -g

main: main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp
	$(CC) $(CFLAGS) -o main.out main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp

debug: main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o main.out main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp

clean:
	rm -rf main.out