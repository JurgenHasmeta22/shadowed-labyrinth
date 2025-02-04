CXX = g++
CXXFLAGS = -std=c++11 -I./src

SRC = $(wildcard src/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = shadowed-labyrinth

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
