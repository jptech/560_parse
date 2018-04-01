$CXX ?= g++
$CXXFLAGS ?= -O3 -g --std=c++11

all: query

clean:
	rm -f query

query: query_main.cpp query.hpp
	$(CXX) $(CXXFLAGS) query_main.cpp -o query
