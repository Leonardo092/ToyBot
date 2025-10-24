CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
LDFLAGS = -L/usr/local/lib

# Sources
SRC = src/toybot.cpp src/main.cpp

# Outputs
BIN = run

.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN)