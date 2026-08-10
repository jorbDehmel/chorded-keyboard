CPP = g++ -pedantic -Wall -std=c++20 -O3 -g
HEADERS = ../schema.hpp

.PHONY:	all
all:	training.out

%.out:	%.o
	$(CPP) -o $@ $^ -lcurses

%.o:	%.cpp $(HEADERS)
	$(CPP) -c -o $@ $<
