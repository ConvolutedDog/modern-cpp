
CXX := $(shell command -v clang++ >/dev/null 2>&1 && echo clang++ || echo g++)

UtilityFuncPath = ../utils

CXXFLAGS = -Wall -std=c++2a -O0 -I$(UtilityFuncPath)

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

run:
	./test.exe
