CC=g++
CFLAGS= -Wall
DEBUG= -g

main: main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp profile.cpp
	$(CC) $(CFLAGS) -o main.out main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp profile.cpp

debug: main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp profile.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o main.out main.cpp always_taken.cpp predictor.cpp twobit.cpp gshare.cpp profile.cpp

clean:
	rm -rf main.out