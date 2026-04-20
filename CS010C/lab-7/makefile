CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -lgtest_main -pthread

all: splaytree_main

splaytree_main: main.cc splaytree.h
	$(CXX) $(CXXFLAGS) ${MAC_GTEST_FLAGS} main.cc -o splaytree_main

clean:
	rm splaytree_main
