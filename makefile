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
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) 
