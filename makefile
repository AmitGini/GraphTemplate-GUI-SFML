CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra

all: tree_demo

tree_demo: Demo.o
	$(CXX) $(CXXFLAGS) Demo.o -o tree_demo

Demo.o: Demo.cpp Tree.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp

Tree.o: Tree.cpp Tree.hpp
	$(CXX) $(CXXFLAGS) -c Tree.cpp

clean:
	rm -f *.o tree_demo

.PHONY: all clean
