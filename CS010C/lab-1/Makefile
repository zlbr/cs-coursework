CXX      := g++
CXXFLAGS := -Wall -Werror -std=c++11

all: out

out: main.o Matrix2D.o
	$(CXX) $(CXXFLAGS) -o out main.o Matrix2D.o

main.o: main.cc Matrix2D.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

Matrix2D.o: Matrix2D.cc Matrix2D.h
	$(CXX) $(CXXFLAGS) -c -o Matrix2D.o Matrix2D.cc

clean:
	rm -f out main.o Matrix2D.o