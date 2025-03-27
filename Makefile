# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Source and Output
SRC = unic.cc
TARGET = unic

# Build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run the program with an input file
run: $(TARGET)
	./$(TARGET) myfile.alias

# Clean compiled files
clean:
	rm -f $(TARGET) output.*

# Rebuild from scratch
rebuild: clean all
