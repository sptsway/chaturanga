CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc
SRCS = src/main.cpp src/position/position.cpp
TARGET = chaturanga

all: clean $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
