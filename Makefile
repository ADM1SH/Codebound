# Makefile for Codebound RPG project

CXX = g++
CXXFLAGS = -std=c++17 -Wall
SOURCES = main.cpp Player.cpp Enemy.cpp Character.cpp
HEADERS = Player.h Enemy.h Character.h
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = codebound

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)