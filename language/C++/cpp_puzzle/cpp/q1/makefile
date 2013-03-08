APP = test
CXX = g++
CC = gcc
CXXFLAGS = -pthread
CXX_LDFLAGS = -lm -lpthread -static

ALL: APP

APP: test

test: singleton.h main.o
	$(CXX) $(CXXFLAGS) $(CXX_LDFLAGS) -o main main.o


clean:
	rm main main.o




.SUFFIXS:
.SUFFIXS: .cc .cpp
.cc.o:
	$(CXX) -c $(CFLAGS) -o $@ $<
.cpp.o:
	$(CXX) -c $(CFLAGS) -o $@ $<
