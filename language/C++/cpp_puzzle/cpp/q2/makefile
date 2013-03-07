APP = test
CXX = g++
CC = gcc

ALL: APP

APP: test

test: main.o
	$(CXX) -o main main.o


clean:
	rm main main.o




.SUFFIXS:
.SUFFIXS: .cc .cpp
.cc.o:
	$(CXX) -c $(CFLAGS) -o $@ $<
.cpp.o:
	$(CXX) -c $(CFLAGS) -o $@ $<
