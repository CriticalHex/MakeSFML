TARGET = main.exe
SRC_FILES = main.cpp

CWD = $(shell pwd)

OBJECTS = $(SRC_FILES:.cpp=.o)

INCLUDE_PATH = -I"$(CWD)\..\SFML-2.6.0\include"

LIBS = -lsfml-graphics -lsfml-window -lsfml-system
LIB_PATH = -L"$(CWD)\..\SFML-2.6.0\libs"
CXX = g++

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CXX) -o $@ $^ $(LIB_PATH) $(LIBS)

%.o: %.cpp
	@$(CXX) -c $< -o $@ $(INCLUDE_PATH)

clean:
	@$(RM) $(OBJECTS) $(TARGET)

run:
	@$(TARGET)

.PHONY: clean run