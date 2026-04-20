GPP = g++ -Wall -g -std=c++17
TESTING_FLAGS = -lgtest -lgtest_main -lpthread
MAC_GTEST_INCLUDE = -I /opt/homebrew/include -L /opt/homebrew/lib # I used this to run gtest locally

all: test_list_doubly_linked run 

test_list_doubly_linked: test_list_doubly_linked.cc list_doubly_linked.h
	$(GPP) $(TESTING_FLAGS) test_list_doubly_linked.cc -o test_list_doubly_linked

run: test_list_doubly_linked
	./test_list_doubly_linked

clean:
	rm -f *.o test_list_doubly_linked