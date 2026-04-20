CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -lgtest_main -pthread
# Default target: build all executables

all: postfix_eval test_deque

postfix_eval: postfix_eval.cc stack.h
	$(CXX) $(CXXFLAGS) postfix_eval.cc -o postfix_eval

test_deque: deque.h test_deque.cc
	$(CXX) $(CXXFLAGS) test_deque.cc -o test_deque -lgtest -lgtest_main

clean:
	rm postfix_eval test_deque