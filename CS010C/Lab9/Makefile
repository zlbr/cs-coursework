CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
MAC_GTEST_FLAGS = -I /opt/homebrew/include -L /opt/homebrew/lib
GTEST_LIBS = -lgtest -lgtest_main -pthread

test: main.cpp cuckoo_hashing.h
	$(CXX) $(CXXFLAGS) $(MAC_GTEST_FLAGS) -o test main.cpp $(GTEST_LIBS)

clean:
	rm -f test

.PHONY: clean
