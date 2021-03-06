CXX = g++
CXX_HEADER_PATHS = -isystem/opt/local/include
CXX_FLAGS =  -g -std=c++11 $(CXX_HEADER_PATHS) -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow
LIB_PATHS = -L/opt/local/lib
LIBS = $(LIB_PATHS) -lpqxx -lpq -lcgal -lgmp -lmpfr -lboost_thread-mt -lboost_system-mt
TEST_LIBS = $(LIBS) -lgtest -lgtest_main
OBJECTS = $(filter-out $(addsuffix .o, $(TESTS)), $(addsuffix .o, $(filter-out $(MAIN), $(basename $(wildcard *.cpp)))) $(addsuffix .o, $(basename $(wildcard **/*.cpp))))
TESTS = $(basename $(wildcard *_test.cpp)) $(basename $(wildcard **/*_test.cpp))
MAIN = mec

all: build test

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -o $(MAIN) $(MAIN).cpp $(OBJECTS) $(LIBS)

test: $(TESTS)
	@for t in $(TESTS); do \
		./$$t; \
	done

%_test: %_test.o $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -o $@ $< $(OBJECTS) $(TEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

clean:
	rm -f $(MAIN) $(TESTS) $(OBJECTS)