# Variables
CXX = clang++
# With Coverage falgs
#CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML -fprofile-arcs -ftest-coverage
#LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -fprofile-arcs -ftest-coverage
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target
TARGET = Demo

# Object files
OBJS = Tree.o Complex.o Demo.o

TEST_OBJ = Tree.o tests.o

# Rules
all: $(TARGET) tests

tree: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

tests: Tree.o Complex.o tests.o
	$(CXX) Tree.o Complex.o tests.o -o tests $(LDFLAGS)

Tree.o: Tree.cpp Tree.hpp
	$(CXX) -c Tree.cpp -o Tree.o $(CXXFLAGS)

Complex.o: Complex.cpp Complex.hpp
	$(CXX) -c Complex.cpp -o Complex.o $(CXXFLAGS)

Demo.o: Demo.cpp Tree.hpp Complex.hpp
	$(CXX) -c Demo.cpp -o Demo.o $(CXXFLAGS)

tests.o: tests.cpp
	$(CXX) -c tests.cpp -o tests.o $(CXXFLAGS)

# Phony targets
.PHONY: clean all tests coverage html_report

clean:
	rm -f $(OBJS) $(TARGET) tests.o tests *.gcno *.gcda *.gcov coverage.info
	rm -rf out

coverage: all
	./$(TARGET)
	@gcov $(SRCS)

html_report: coverage
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

