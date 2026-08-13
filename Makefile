CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
SRC = src/main.cpp src/Graph.cpp
TARGET = campus_navigator

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) campus_map.csv

.PHONY: all run clean
