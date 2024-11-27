
CXX = clang++
 
CXXFLAGS = -Wall -std=c++2a

SOURCES = test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = test

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS) core.*

run: $(TARGET)
	./$(TARGET)
