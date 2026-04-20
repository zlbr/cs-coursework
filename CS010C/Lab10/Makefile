CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -lgtest_main -pthread
MAC_GTEST_FLAGS = -I /opt/homebrew/include -L /opt/homebrew/lib
# Default target: build all executables

all: topological_sort

topological_sort: topological_sort.cc topological_sort.h
	$(CXX) $(CXXFLAGS) ${MAC_GTEST_FLAGS} topological_sort.cc -o topological_sort

clean:
	rm topological_sort
