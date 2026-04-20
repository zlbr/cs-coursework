CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
GTEST_FLAGS = -lgtest -lgtest_main -pthread
# MAC_GTEST_FLAGS = -I /opt/homebrew/include -L /opt/homebrew/lib

all: test_multiset prime_factors

test_multiset: test_multiset.cc multiset.h
	$(CXX) $(CXXFLAGS) ${GTEST_FLAGS} test_multiset.cc -o test_multiset

prime_factors: prime_factors.cc multiset.h
	$(CXX) $(CXXFLAGS) prime_factors.cc -o prime_factors

clean:
	rm test_multiset prime_factors
