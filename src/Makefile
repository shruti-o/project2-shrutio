# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g

# Target executable name
TARGET = loadbalancer

# Source files
SRCS = main.cpp LoadBalancer.cpp WebServer.cpp Request.cpp

# Object files (auto-generated)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET) loadbalancer.log

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
