# Variables
CXX = g++
# With Coverage falgs
#CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML -fprofile-arcs -ftest-coverage
#LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -fprofile-arcs -ftest-coverage
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target
TARGET = Demo

# Source files
SRCS = Demo.cpp Tree.cpp Complex.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Rules
all: $(TARGET) tests

tree: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

tests: Tree.o Complex.o tests.o
	$(CXX) Tree.o Complex.o tests.o -o tests $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

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

