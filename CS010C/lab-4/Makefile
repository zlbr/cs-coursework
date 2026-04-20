CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -lgtest_main -pthread
# Default target: build all executables

all: q1-1 q1-2 q2 test_lab_4

q1-1: q1-1.cc
	$(CXX) $(CXXFLAGS) q1-1.cc -o q1-1

q1-2: q1-2.cc
	$(CXX) $(CXXFLAGS) q1-2.cc -o q1-2

q2: q2.cc
	$(CXX) $(CXXFLAGS) q2.cc -o q2

test_lab_4: test_lab_4.cc
	$(CXX) $(CXXFLAGS) test_lab_4.cc -o test_lab_4 $(GTEST_FLAGS)

clean:
	rm -v q1-1 q1-2 q2 test_lab_4
