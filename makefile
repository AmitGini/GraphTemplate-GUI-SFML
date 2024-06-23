# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target
TARGET = demo

# Source files
SRCS = Demo.cpp Tree.cpp Complex.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Rules
all: $(TARGET) tests

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

tests: Tree.o Complex.o tests.o
	$(CXX) Tree.o Complex.o tests.o -o tests $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: clean all tests

clean:
	rm -f $(OBJS) $(TARGET) tests.o tests
