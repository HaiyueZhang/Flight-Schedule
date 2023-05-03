# Executable Name
EXENAME = main

# Object Types
OBJS = readFile.o main.o interaction.o Airport.o BFS.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include make/customClangEnforcement.mk

# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

BFS.o: main.cpp src/BFS.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/BFS.cpp

readFile.o: main.cpp src/readFile.cpp 
	$(CXX) $(CXXFLAGS) main.cpp src/readFile.cpp 

interaction.o: src/interaction.cpp 
	$(CXX) $(CXXFLAGS) src/interaction.cpp 

Airport.o: src/Airport.cpp 
	$(CXX) $(CXXFLAGS) src/Airport.cpp 

test: output_msg catch/catchmain.cpp tests/tests.cpp src/readFile.cpp src/interaction.cpp src/Airport.cpp src/BFS.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp src/readFile.cpp src/interaction.cpp src/Airport.cpp src/BFS.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test
